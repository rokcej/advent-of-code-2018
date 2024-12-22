use std::io::BufRead;

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn get_next_secret_number(mut secret_number: u64) -> u64 {
    secret_number ^= secret_number * 64;
    secret_number %= 16777216;

    secret_number ^= secret_number / 32;
    secret_number %= 16777216;

    secret_number ^= secret_number * 2048;
    secret_number %= 16777216;

    return secret_number;
}

fn main() {
    let lines = read_lines("day22/input");
    let seeds: Vec<u64> = lines.iter().map(|s| s.parse().unwrap()).collect();

    let mut secret_number_sum = 0;
    for &seed in &seeds {
        let mut secret_number = seed;
        for _ in 0..2000 {
            secret_number = get_next_secret_number(secret_number);
        }
        secret_number_sum += secret_number;
    }

    println!("{secret_number_sum}");
}
