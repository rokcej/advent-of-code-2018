namespace Day02;

class Part1 {

	public static void Run() {
		string[] lines = File.ReadAllLines("input");

		int checksum = 0;
		foreach (string line in lines) {
			List<string> words = line.Split('\t').ToList();
			List<int> numbers = words.Select(int.Parse).ToList();
			checksum += numbers.Max() - numbers.Min();
		}
		Console.WriteLine(checksum);
	}

}
