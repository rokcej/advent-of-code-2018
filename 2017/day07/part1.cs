namespace Day07;

class Part1 {

	public static void Run() {
		string[] lines = File.ReadAllLines("input");

		HashSet<string> parents = new HashSet<string>();
		HashSet<string> children = new HashSet<string>();
		foreach (string line in lines) {
			string[] parts = line.Split(" -> ");
			if (parts.Length == 2) {
				parents.Add(parts[0].Split(' ')[0]);
				children.UnionWith(parts[1].Split(", "));
			}
		}
		Console.WriteLine(parents.Except(children).First()); // Set difference should contain one element
	}

}
