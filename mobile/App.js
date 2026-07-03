import React, { useState, useRef, useEffect, useCallback } from "react";
import { StatusBar } from "expo-status-bar";
import { SafeAreaView, StyleSheet } from "react-native";

import HomeScreen from "./screens/HomeScreen";
import CaptureScreen from "./screens/CaptureScreen";
import ProcessingScreen from "./screens/ProcessingScreen";
import ViewScreen from "./screens/ViewScreen";
import { BASE_URL, COLORS } from "./config";

const POLL_INTERVAL_MS = 5000;

// Screens: "home" | "capture" | "processing" | "view"
export default function App() {
  const [screen, setScreen] = useState("home");
  const [jobId, setJobId] = useState(null);
  const [processingStage, setProcessingStage] = useState("uploading"); // uploading | processing | error
  const [errorMessage, setErrorMessage] = useState(null);
  const pollTimerRef = useRef(null);

  const clearPolling = () => {
    if (pollTimerRef.current) {
      clearInterval(pollTimerRef.current);
      pollTimerRef.current = null;
    }
  };

  const pollStatus = useCallback((id) => {
    clearPolling();
    pollTimerRef.current = setInterval(async () => {
      try {
        const res = await fetch(`${BASE_URL}/status/${id}`);
        if (!res.ok) throw new Error(`Status check failed (${res.status})`);
        const data = await res.json();

        if (data.status === "done") {
          clearPolling();
          setScreen("view");
        } else if (data.status === "error" || data.status === "failed") {
          clearPolling();
          setProcessingStage("error");
          setErrorMessage("Processing failed on the server.");
        }
        // otherwise keep polling silently while status === "processing"
      } catch (err) {
        console.error("Polling error:", err);
        clearPolling();
        setProcessingStage("error");
        setErrorMessage(err.message);
      }
    }, POLL_INTERVAL_MS);
  }, []);

  // CaptureScreen calls this in three ways:
  //  onUploadStarted()                       -> upload begins, show "uploading"
  //  onUploadStarted(job_id, "processing")    -> upload succeeded, start polling
  //  onUploadStarted(null, "error", message)  -> upload failed
  const handleUploadStarted = (id, status, message) => {
    if (id === undefined && status === undefined) {
      setProcessingStage("uploading");
      setErrorMessage(null);
      setScreen("processing");
      return;
    }

    if (status === "error") {
      setProcessingStage("error");
      setErrorMessage(message);
      setScreen("processing");
      return;
    }

    setJobId(id);
    setProcessingStage("processing");
    setScreen("processing");
    pollStatus(id);
  };

  useEffect(() => {
    return () => clearPolling(); // cleanup on unmount
  }, []);

  const resetToHome = () => {
    clearPolling();
    setJobId(null);
    setErrorMessage(null);
    setScreen("home");
  };

  return (
    <SafeAreaView style={styles.safeArea}>
      <StatusBar style="light" />
      {screen === "home" && (
        <HomeScreen onScanPress={() => setScreen("capture")} />
      )}

      {screen === "capture" && (
        <CaptureScreen
          onUploadStarted={handleUploadStarted}
          onCancel={resetToHome}
        />
      )}

      {screen === "processing" && (
        <ProcessingScreen
          stage={processingStage}
          errorMessage={errorMessage}
          onRetry={resetToHome}
        />
      )}

      {screen === "view" && jobId && (
        <ViewScreen jobId={jobId} onDone={resetToHome} />
      )}
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  safeArea: {
    flex: 1,
    backgroundColor: COLORS.background,
  },
});
