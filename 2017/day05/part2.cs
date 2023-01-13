namespace Day05;

class Part2 {

	public static void Run() {
        int[] offsets = File.ReadAllLines("input").Select(int.Parse).ToArray();

        int steps = 0;
        for (int i = 0; i >= 0 && i < offsets.Length;) {
            if (offsets[i] >= 3) {
                i += offsets[i]--;
            } else {
                i += offsets[i]++;
            }
            ++steps;
        }
        Console.WriteLine(steps);
    }

}
