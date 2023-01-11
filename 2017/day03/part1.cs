using System;
using System.IO;

namespace Day03;

class Part1 {

	public static void Run() {
		int input = int.Parse(File.ReadAllLines("input")[0]);

		int side = 1;
		while (side * side < input) {
			side += 2;
		}
		int offset = (side * side - input) % (side - 1);
		int radius = (side - 1) / 2;
		Console.WriteLine(Math.Abs(offset - radius) + radius);
	}

}
