import React from "react";
import { View, TouchableOpacity, Text, StyleSheet } from "react-native";
import { WebView } from "react-native-webview";
import { BASE_URL, COLORS } from "../config";

export default function ViewScreen({ jobId, onDone }) {
  const viewUrl = `${BASE_URL}/view/${jobId}`;

  return (
    <View style={styles.container}>
      <WebView
        source={{ uri: viewUrl }}
        style={styles.webview}
        originWhitelist={["*"]}
        allowsInlineMediaPlayback
        javaScriptEnabled
        domStorageEnabled
      />
      <TouchableOpacity style={styles.doneButton} onPress={onDone}>
        <Text style={styles.doneButtonText}>Done</Text>
      </TouchableOpacity>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: COLORS.background,
  },
  webview: {
    flex: 1,
    backgroundColor: COLORS.background,
  },
  doneButton: {
    position: "absolute",
    top: 60,
    right: 20,
    backgroundColor: "rgba(10,10,10,0.75)",
    paddingHorizontal: 18,
    paddingVertical: 10,
    borderRadius: 20,
    borderWidth: 1,
    borderColor: "rgba(255,255,255,0.15)",
  },
  doneButtonText: {
    color: "#fff",
    fontWeight: "700",
    fontSize: 14,
  },
});
