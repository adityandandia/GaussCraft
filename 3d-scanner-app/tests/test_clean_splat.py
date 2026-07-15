import unittest
import tempfile
import struct
from pathlib import Path
import numpy as np

# Import the production functions
from backend.tasks import clean_splat, _read_ply

class TestCleanSplatRegression(unittest.TestCase):
    def setUp(self):
        """Set up a temporary isolated directory for the test."""
        self.test_dir = tempfile.TemporaryDirectory()
        self.input_ply = Path(self.test_dir.name) / "mock_raw_splat.ply"
        self.output_ply = Path(self.test_dir.name) / "mock_cleaned_splat.ply"
        
        # Generate the synthetic test data
        self._generate_mock_ply(self.input_ply)

    def tearDown(self):
        """Clean up the temporary directory after the test finishes."""
        self.test_dir.cleanup()

    def _generate_mock_ply(self, path: Path):
        """
        Creates a deterministic FastGS-formatted binary PLY file.
        Injects 800 'good' points and 200 'bad' points to test the filters.
        """
        num_good = 800
        num_bad = 200
        total = num_good + num_bad

        header = (
            "ply\n"
            "format binary_little_endian 1.0\n"
            f"element vertex {total}\n"
            "property float x\n"
            "property float y\n"
            "property float z\n"
            "property float opacity\n"
            "property float scale_0\n"
            "property float scale_1\n"
            "property float scale_2\n"
            "end_header\n"
        )

        with open(path, "wb") as f:
            f.write(header.encode("utf-8"))
            
            # --- 1. Generate Good Points ---
            # Tight cluster around origin, high opacity, small scale
            for _ in range(num_good):
                x, y, z = np.random.normal(0, 0.5, 3)
                opacity = 5.0  # Sigmoid(5) is ~0.99 (solid)
                s0, s1, s2 = np.log([0.01, 0.01, 0.01])
                f.write(struct.pack("7f", x, y, z, opacity, s0, s1, s2))

            # --- 2. Generate Bad Points (Floaters, Dust, Bloat) ---
            # Spread far out, low opacity, huge scale
            for _ in range(num_bad):
                x, y, z = np.random.normal(15, 5, 3)  # Far from origin (fails radial crop)
                opacity = -5.0  # Sigmoid(-5) is ~0.006 (fails opacity filter)
                s0, s1, s2 = np.log([1.5, 1.5, 1.5])  # Huge scale (fails bloat filter)
                f.write(struct.pack("7f", x, y, z, opacity, s0, s1, s2))

    def test_clean_splat_survival_rate(self):
        """
        Tests that clean_splat removes the bad points but keeps the valid geometry.
        """
        print("\n--- Starting Regression Test ---")
        
        # 1. Run the production cleaner
        clean_splat(self.input_ply, self.output_ply)
        
        # 2. Verify the output was created
        self.assertTrue(self.output_ply.exists(), "Output PLY was not created.")
        
        # 3. Read the cleaned output
        _, _, _, final_vertex_count = _read_ply(self.output_ply)
        
        # 4. Assertions
        # 200 bad points are removed by Stage 2.
        # Stage 3 universally chops the outer 20% of the remaining 800 points (160 points).
        # Expected survival is ~640.
        expected_min = 600
        expected_max = 660
        
        self.assertTrue(
            expected_min <= final_vertex_count <= expected_max,
            f"Regression failure: Final point count ({final_vertex_count}) fell outside "
            f"the expected safe range ({expected_min} - {expected_max})."
        )
        print(f"--- Test Passed: {final_vertex_count} points survived out of 1000 ---")

if __name__ == "__main__":
    unittest.main()