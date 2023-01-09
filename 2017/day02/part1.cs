using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

namespace Day02 { 

	class Part1 { 

		public static void Main(string[] args) { 
			string[] lines = File.ReadAllLines("input");

			int checksum = 0;
			foreach (string line in lines) {
				List<string> words = line.Split('\t').ToList();
				List<int> numbers = words.Select(word => int.Parse(word)).ToList();
				checksum += numbers.Max() - numbers.Min();
			}
			Console.WriteLine(checksum);
		}

	}

}
