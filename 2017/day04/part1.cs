namespace Day04;

class Part1 {

	public static void Run() {
		string[] lines = File.ReadAllLines("input");

		int num_valid = 0;
		foreach (string line in lines) {
			if (IsValid(line)) {
				++num_valid;
			}
		}
		Console.WriteLine(num_valid);
	}

	private static bool IsValid(string passphrase) {
		string[] words = passphrase.Split(' ');
		HashSet<string> set = new HashSet<string>();
		foreach (string word in words) {
			if (set.Contains(word)) {
				return false;
			}
			set.Add(word);
		}
		return true;
	}

}
