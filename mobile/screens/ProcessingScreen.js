import React from "react";
import { View, Text, ActivityIndicator, StyleSheet, TouchableOpacity } from "react-native";
import { COLORS } from "../config";

// stage: "uploading" | "processing" | "error"
export default function ProcessingScreen({ stage, errorMessage, onRetry }) {
  if (stage === "error") {
    return (
      <View style={styles.container}>
        <Text style={styles.errorTitle}>Something went wrong</Text>
        <Text style={styles.errorMessage}>{errorMessage || "Please try again."}</Text>
        <TouchableOpacity style={styles.retryButton} onPress={onRetry}>
          <Text style={styles.retryButtonText}>Back to Home</Text>
        </TouchableOpacity>
      </View>
    );
  }

  const label = stage === "uploading" ? "Uploading..." : "Processing 3D Model...";
  const sublabel =
    stage === "uploading"
      ? "Sending your scan to the server"
      : "This can take a few minutes depending on scan length";

  return (
    <View style={styles.container}>
      <ActivityIndicator size="large" color={COLORS.accent} />
      <Text style={styles.label}>{label}</Text>
      <Text style={styles.sublabel}>{sublabel}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: COLORS.background,
    justifyContent: "center",
    alignItems: "center",
    paddingHorizontal: 32,
  },
  label: {
    color: COLORS.textPrimary,
    fontSize: 20,
    fontWeight: "700",
    marginTop: 24,
  },
  sublabel: {
    color: COLORS.textSecondary,
    fontSize: 14,
    marginTop: 8,
    textAlign: "center",
  },
  errorTitle: {
    color: COLORS.textPrimary,
    fontSize: 20,
    fontWeight: "700",
  },
  errorMessage: {
    color: COLORS.textSecondary,
    fontSize: 14,
    marginTop: 8,
    textAlign: "center",
  },
  retryButton: {
    marginTop: 28,
    backgroundColor: COLORS.accent,
    paddingVertical: 14,
    paddingHorizontal: 28,
    borderRadius: 14,
  },
  retryButtonText: {
    color: "#fff",
    fontWeight: "700",
    fontSize: 15,
  },
});
