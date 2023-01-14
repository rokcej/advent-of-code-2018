namespace Day06;

class Part2 {

	public static void Run() {
		string[] lines = File.ReadAllLines("input");
		List<int> banks = lines[0].Split('\t').Select(int.Parse).ToList();

		int cycles = 0;
		for (int iteration = 0; iteration < 2; ++iteration) {
			cycles = 0;
			HashSet<string> set = new HashSet<string>();
			while (set.Add(string.Join(",", banks))) {
				int i_max = banks.IndexOf(banks.Max());
				int blocks = banks[i_max];
				banks[i_max] = 0;
				for (int i = 1; i <= Math.Min(blocks, banks.Count); ++i) {
					banks[(i_max + i) % banks.Count] += 1 + (blocks - i) / banks.Count;
				}
				++cycles;
			}
		}
		Console.WriteLine(cycles);
	}

}
