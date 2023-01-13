namespace Day04;

class Part2 {

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

	public static bool IsValid(string passphrase) {
		List<string> canonical_words = passphrase.Split(' ').Select(Canonicalize).ToList();
		HashSet<string> set = new HashSet<string>();
		foreach (string word in canonical_words) {
			if (set.Contains(word)) {
				return false;
			}
			set.Add(word);
		}
		return true;
	}

	public static string Canonicalize(string word) {
		char[] characters = word.ToCharArray();
		Array.Sort(characters);
		return new string(characters);
	}

}
