import React, { useRef, useState, useEffect, useCallback } from "react";
import { View, Text, TouchableOpacity, StyleSheet, Alert } from "react-native";
import { CameraView, useCameraPermissions } from "expo-camera";
import { BASE_URL } from "../config";
import { COLORS } from "../config";

const RECORD_SECONDS = 180; // 03:00

function formatTime(totalSeconds) {
  const m = Math.floor(totalSeconds / 60)
    .toString()
    .padStart(2, "0");
  const s = Math.floor(totalSeconds % 60)
    .toString()
    .padStart(2, "0");
  return `${m}:${s}`;
}

export default function CaptureScreen({ onUploadStarted, onCancel }) {
  const cameraRef = useRef(null);
  const [permission, requestPermission] = useCameraPermissions();
  const [isRecording, setIsRecording] = useState(false);
  const [secondsLeft, setSecondsLeft] = useState(RECORD_SECONDS);
  const stoppingRef = useRef(false); // guards against double-stop

  useEffect(() => {
    if (!permission) {
      // permission state not loaded yet
      return;
    }
    if (!permission.granted) {
      requestPermission();
    }
  }, [permission]);

  const startRecording = useCallback(async () => {
    if (!cameraRef.current) return;
    stoppingRef.current = false;
    setIsRecording(true);
    setSecondsLeft(RECORD_SECONDS);

    try {
      const video = await cameraRef.current.recordAsync({
        maxDuration: RECORD_SECONDS,
      });
      // recordAsync resolves once recording stops (either by timer or manual stop)
      if (video?.uri) {
        handleUpload(video.uri);
      }
    } catch (err) {
      console.error("Recording error:", err);
      Alert.alert("Recording failed", err.message || "Unknown error");
    }
  }, []);

  useEffect(() => {
    // auto-start recording as soon as the camera + permission are ready
    if (permission?.granted && !isRecording) {
      startRecording();
    }
  }, [permission, startRecording]);

  useEffect(() => {
    if (!isRecording) return;
    if (secondsLeft <= 0) {
      stopRecording();
      return;
    }
    const timer = setTimeout(() => setSecondsLeft((s) => s - 1), 1000);
    return () => clearTimeout(timer);
  }, [isRecording, secondsLeft]);

  const stopRecording = async () => {
    if (stoppingRef.current || !cameraRef.current) return;
    stoppingRef.current = true;
    setIsRecording(false);
    try {
      await cameraRef.current.stopRecording();
    } catch (err) {
      console.error("Stop recording error:", err);
    }
  };

  const handleUpload = async (videoUri) => {
    onUploadStarted(); // tell parent to switch to the processing overlay

    try {
      const formData = new FormData();
      formData.append("file", {
        uri: videoUri,
        name: "scan.mp4",
        type: "video/mp4",
      });

      const response = await fetch(`${BASE_URL}/upload`, {
        method: "POST",
        body: formData,
        headers: {
          "Content-Type": "multipart/form-data",
        },
      });

      if (!response.ok) {
        throw new Error(`Upload failed with status ${response.status}`);
      }

      const data = await response.json();
      if (!data.job_id) {
        throw new Error("No job_id returned from server");
      }

      onUploadStarted(data.job_id, "processing");
    } catch (err) {
      console.error("Upload error:", err);
      onUploadStarted(null, "error", err.message);
    }
  };

  if (!permission) {
    return <View style={styles.container} />;
  }

  if (!permission.granted) {
    return (
      <View style={[styles.container, styles.centered]}>
        <Text style={styles.permissionText}>
          Camera access is required to scan objects.
        </Text>
        <TouchableOpacity style={styles.permissionButton} onPress={requestPermission}>
          <Text style={styles.permissionButtonText}>Grant Permission</Text>
        </TouchableOpacity>
      </View>
    );
  }

  return (
    <View style={styles.container}>
      <CameraView
        ref={cameraRef}
        style={StyleSheet.absoluteFill}
        facing="back"
        mode="video"
      />

      <View style={styles.topBanner}>
        <View style={styles.recordingDot} />
        <Text style={styles.timerText}>{formatTime(secondsLeft)}</Text>
      </View>

      <TouchableOpacity style={styles.cancelButton} onPress={onCancel}>
        <Text style={styles.cancelButtonText}>Cancel</Text>
      </TouchableOpacity>

      <TouchableOpacity
        style={styles.stopButton}
        activeOpacity={0.85}
        onPress={stopRecording}
      >
        <Text style={styles.stopButtonText}>Stop & Upload</Text>
      </TouchableOpacity>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#000",
  },
  centered: {
    justifyContent: "center",
    alignItems: "center",
    paddingHorizontal: 32,
  },
  permissionText: {
    color: COLORS.textPrimary,
    fontSize: 16,
    textAlign: "center",
    marginBottom: 20,
  },
  permissionButton: {
    backgroundColor: COLORS.accent,
    paddingVertical: 14,
    paddingHorizontal: 28,
    borderRadius: 14,
  },
  permissionButtonText: {
    color: "#fff",
    fontWeight: "700",
    fontSize: 15,
  },
  topBanner: {
    position: "absolute",
    top: 60,
    alignSelf: "center",
    flexDirection: "row",
    alignItems: "center",
    backgroundColor: "rgba(10,10,10,0.7)",
    paddingHorizontal: 18,
    paddingVertical: 10,
    borderRadius: 24,
    borderWidth: 1,
    borderColor: "rgba(255,255,255,0.15)",
  },
  recordingDot: {
    width: 8,
    height: 8,
    borderRadius: 4,
    backgroundColor: COLORS.danger,
    marginRight: 8,
  },
  timerText: {
    color: "#fff",
    fontSize: 16,
    fontWeight: "700",
    fontVariant: ["tabular-nums"],
  },
  cancelButton: {
    position: "absolute",
    top: 60,
    left: 20,
    backgroundColor: "rgba(10,10,10,0.7)",
    paddingHorizontal: 14,
    paddingVertical: 8,
    borderRadius: 20,
  },
  cancelButtonText: {
    color: "#fff",
    fontSize: 14,
    fontWeight: "600",
  },
  stopButton: {
    position: "absolute",
    bottom: 50,
    alignSelf: "center",
    backgroundColor: COLORS.accent,
    paddingVertical: 18,
    paddingHorizontal: 40,
    borderRadius: 40,
    shadowColor: COLORS.accent,
    shadowOpacity: 0.5,
    shadowRadius: 16,
    shadowOffset: { width: 0, height: 6 },
    elevation: 6,
  },
  stopButtonText: {
    color: "#fff",
    fontSize: 17,
    fontWeight: "700",
  },
});
