import React from "react";
import { View, Text, TouchableOpacity, StyleSheet } from "react-native";
import { COLORS } from "../config";

export default function HomeScreen({ onScanPress }) {
  return (
    <View style={styles.container}>
      <View style={styles.header}>
        <Text style={styles.title}>3D Scanner</Text>
        <Text style={styles.subtitle}>
          Capture any object. Turn it into a 3D model in minutes.
        </Text>
      </View>

      <TouchableOpacity
        style={styles.scanButton}
        activeOpacity={0.8}
        onPress={onScanPress}
      >
        <Text style={styles.scanButtonText}>Scan Object</Text>
      </TouchableOpacity>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: COLORS.background,
    justifyContent: "space-between",
    paddingHorizontal: 28,
    paddingVertical: 80,
  },
  header: {
    marginTop: 40,
  },
  title: {
    color: COLORS.textPrimary,
    fontSize: 42,
    fontWeight: "800",
    letterSpacing: -1,
  },
  subtitle: {
    color: COLORS.textSecondary,
    fontSize: 16,
    marginTop: 12,
    lineHeight: 22,
  },
  scanButton: {
    backgroundColor: COLORS.accent,
    borderRadius: 18,
    paddingVertical: 20,
    alignItems: "center",
    shadowColor: COLORS.accent,
    shadowOpacity: 0.4,
    shadowRadius: 20,
    shadowOffset: { width: 0, height: 8 },
    elevation: 6,
  },
  scanButtonText: {
    color: "#FFFFFF",
    fontSize: 18,
    fontWeight: "700",
  },
});
