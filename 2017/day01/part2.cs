namespace Day01;

public class Part2 {

	public static void Run() {
		string captcha = File.ReadAllLines("input")[0];

		int sum = 0;
		for (int i = 0; i < captcha.Length; i++) {
			char c = captcha[i];
			char c2 = captcha[(i + captcha.Length / 2) % captcha.Length];
			if (c == c2) {
				sum += c - '0';
			}
		}
		Console.WriteLine(sum);
	}

}
