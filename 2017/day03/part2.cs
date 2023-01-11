using System;
using System.IO;
using System.Collections.Generic;

namespace Day03 { 

	class Part2 { 

		public static void Main(string[] args) {
			int input = int.Parse(File.ReadAllLines("input")[0]);

			var grid = new Dictionary<(int, int), int>();
			grid[(0, 0)] = 1;

			var dirs = new (int, int)[] {(+1, 0), (0, +1), (-1, 0), (0, -1)};
			int i_dir = 0;

			var pos = (0, 0);
			for (int steps = 1;; steps += 1) {
				for (int i = 0; i < 2; ++i) {
					var dir = dirs[i_dir++ % 4];
					for (int step = 0; step < steps; ++step) {
						pos = (pos.Item1 + dir.Item1, pos.Item2 + dir.Item2);
						grid[pos] = SumNeighbors(pos, grid);
						if (grid[pos] > input) {
							Console.WriteLine(grid[pos]);
							return;
						}
					}
				}
			}

		}

		private static int SumNeighbors((int, int) pos, Dictionary<(int, int), int> grid) {
			int sum = 0;
			var deltas = new (int, int)[] {(-1, -1), (0, -1), (+1, -1), (-1, 0), (+1, 0), (-1, +1), (0, +1), (+1, +1)};
			foreach ((int, int) delta in deltas) {
				var pos2 = (pos.Item1 + delta.Item1, pos.Item2 + delta.Item2);
				if (grid.ContainsKey(pos2)) {
					sum += grid[pos2];
				}
			}
			return sum;
		}

	}

}
