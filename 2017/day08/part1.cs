namespace Day08;

class Part1 {

	public static void Run() {
		string[] lines = File.ReadAllLines("input");

		Dictionary<string, int> memory = new Dictionary<string, int>();

		foreach (string line in lines) {
			string[] parts = line.Split(' ');

			string reg_write = parts[0];
			string operation = parts[1];
			int delta = int.Parse(parts[2]);
			string reg_read = parts[4];
			string comparator = parts[5];
			int condition = int.Parse(parts[6]);

			if (!memory.ContainsKey(reg_read)) {
				memory[reg_read] = 0;
			}

			bool success;
			switch (comparator) {
				case "<":  success = memory[reg_read] <  condition; break;
				case "<=": success = memory[reg_read] <= condition; break;
				case ">":  success = memory[reg_read] >  condition; break;
				case ">=": success = memory[reg_read] >= condition; break;
				case "==": success = memory[reg_read] == condition; break;
				case "!=": success = memory[reg_read] != condition; break;
				default:
					throw new Exception($"Unsupported comparator {comparator}");
			}

			if (success) {
				if (!memory.ContainsKey(reg_write)) {
					memory[reg_write] = 0;
				}

				switch (operation) {
					case "inc": memory[reg_write] += delta; break;
					case "dec": memory[reg_write] -= delta; break;
					default:
						throw new Exception($"Unsupported operation {operation}");
				}
			}
		}

		Console.WriteLine(memory.Values.Max());
	}

}
