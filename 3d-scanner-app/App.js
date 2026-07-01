import React, { useState, useRef, useEffect } from 'react';
import { StyleSheet, Text, View, TouchableOpacity, Alert, ActivityIndicator } from 'react-native';
import { CameraView, useCameraPermissions, useMicrophonePermissions } from 'expo-camera';

// ⚠️ REPLACE WITH YOUR CURRENT NGROK URL (NO SLASH AT THE END)
const NGROK_URL = "https://glazing-chaperone-bazooka.ngrok-free.dev";

export default function App() {
  const [cameraPermission, requestCameraPermission] = useCameraPermissions();
  const [micPermission, requestMicPermission] = useMicrophonePermissions();
  
  const cameraRef = useRef(null);
  const [appState, setAppState] = useState('capture'); 
  const [isRecording, setIsRecording] = useState(false);
  const [videoUri, setVideoUri] = useState(null);
  const [serverMessage, setServerMessage] = useState('READY: Center the object.');

  useEffect(() => {
    if (!cameraPermission?.granted) requestCameraPermission();
    if (!micPermission?.granted) requestMicPermission();
  }, [cameraPermission, micPermission]);

  const handleRecordButton = async () => {
    if (isRecording) {
      cameraRef.current?.stopRecording();
      setIsRecording(false);
    } else {
      setIsRecording(true);
      setServerMessage('RECORDING: Move slowly in a circle!');
      try {
        const data = await cameraRef.current?.recordAsync({ maxDuration: 15 });
        setVideoUri(data.uri);
        setAppState('review');
        setServerMessage('Capture complete. Ready to send?');
      } catch (e) {
        setIsRecording(false);
        Alert.alert("Camera Error", e.message);
      }
    }
  };

  const retakeVideo = () => {
    setVideoUri(null);
    setAppState('capture');
    setServerMessage('READY: Center the object.');
  };

  const uploadVideo = async () => {
    if (!videoUri) return;
    setAppState('uploading');
    setServerMessage('Uploading video to server...');

    const formData = new FormData();
    formData.append('file', {
      uri: videoUri,
      name: 'scan.mp4',
      type: 'video/mp4',
    });

    try {
      const response = await fetch(`${NGROK_URL}/upload`, {
        method: 'POST',
        body: formData,
        headers: { 'Content-Type': 'multipart/form-data' },
      });

      const rawText = await response.text(); 
      let data;
      try {
        data = JSON.parse(rawText); 
      } catch (e) {
        throw new Error(`Server returned non-JSON: ${rawText.substring(0, 50)}`);
      }
      
      if (response.ok) {
        setAppState('processing');
        pollStatus(data.job_id);
      } else {
        throw new Error(data.detail || "Upload failed");
      }
    } catch (error) {
      setAppState('review');
      Alert.alert("Server Error", error.message);
      setServerMessage(`Error: ${error.message}`);
    }
  };

  const pollStatus = async (jobId) => {
    try {
      const response = await fetch(`${NGROK_URL}/status/${jobId}`);
      const data = await response.json();

      if (data.status === 'completed') {
        setAppState('done');
        setServerMessage('✅ PIPELINE SUCCESS!');
      } else if (data.status === 'failed') {
        setAppState('review');
        setServerMessage('❌ PIPELINE FAILED.');
      } else {
        setTimeout(() => pollStatus(jobId), 5000);
      }
    } catch (error) {
      setTimeout(() => pollStatus(jobId), 5000);
    }
  };

  if (!cameraPermission || !cameraPermission.granted) {
    return <View style={styles.container}><Text style={{color: 'white', textAlign: 'center', marginTop: 100}}>Grant permissions.</Text></View>;
  }

  return (
    <View style={styles.container}>
      {appState === 'capture' || appState === 'review' ? (
        <CameraView style={StyleSheet.absoluteFillObject} mode="video" ref={cameraRef} />
      ) : (
        <View style={styles.processingBackground}><ActivityIndicator size="large" color="#00ff00" /></View>
      )}

      <View style={styles.overlay}>
        <View style={styles.header}>
          <Text style={styles.title}>3D Scanner</Text>
          <Text style={styles.instructions}>{serverMessage}</Text>
        </View>

        <View style={styles.controls}>
          {appState === 'capture' && (
            <TouchableOpacity style={[styles.button, isRecording && styles.buttonRecording]} onPress={handleRecordButton}>
              <Text style={styles.buttonText}>{isRecording ? "STOP SCAN" : "START SCAN"}</Text>
            </TouchableOpacity>
          )}

          {appState === 'review' && (
             <View style={styles.reviewControls}>
               <TouchableOpacity style={styles.retakeButton} onPress={retakeVideo}><Text style={styles.buttonText}>Retake</Text></TouchableOpacity>
               <TouchableOpacity style={styles.uploadButton} onPress={uploadVideo}><Text style={styles.buttonText}>Upload</Text></TouchableOpacity>
             </View>
          )}

          {appState === 'done' && (
            <TouchableOpacity style={styles.uploadButton} onPress={retakeVideo}><Text style={styles.buttonText}>Start New</Text></TouchableOpacity>
          )}
        </View>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, backgroundColor: '#000' },
  processingBackground: { flex: 1, justifyContent: 'center', alignItems: 'center' },
  overlay: { flex: 1, justifyContent: 'space-between', padding: 20, paddingTop: 60, paddingBottom: 40 },
  header: { alignItems: 'center', backgroundColor: 'rgba(0,0,0,0.6)', padding: 15, borderRadius: 10 },
  title: { fontSize: 24, fontWeight: 'bold', color: 'white' },
  instructions: { color: '#00ff00', fontSize: 16, fontWeight: 'bold', textAlign: 'center' },
  controls: { alignItems: 'center', width: '100%' },
  button: { backgroundColor: '#fff', paddingVertical: 20, paddingHorizontal: 40, borderRadius: 40 },
  buttonRecording: { backgroundColor: '#ff4444' },
  reviewControls: { flexDirection: 'row', justifyContent: 'space-between', width: '100%' },
  retakeButton: { backgroundColor: '#555', paddingVertical: 15, paddingHorizontal: 30, borderRadius: 30 },
  uploadButton: { backgroundColor: '#007AFF', paddingVertical: 15, paddingHorizontal: 30, borderRadius: 30 },
  buttonText: { fontWeight: 'bold', fontSize: 18, color: '#fff' }
});
