use std::collections::HashMap;
use std::io::BufRead;

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn get_next_secret_number(mut secret_number: i64) -> i64 {
    secret_number ^= secret_number * 64;
    secret_number %= 16777216;

    secret_number ^= secret_number / 32;
    secret_number %= 16777216;

    secret_number ^= secret_number * 2048;
    secret_number %= 16777216;

    return secret_number;
}

fn get_sequence_id(diffs: &Vec<i64>) -> i64 {
    let mut sequence_id = 0;
    for &diff in &diffs[diffs.len() - 4..] {
        sequence_id = sequence_id * 19 + diff + 9;
    }
    return sequence_id;
}

fn main() {
    let lines = read_lines("day22/input");
    let seeds: Vec<i64> = lines.iter().map(|s| s.parse().unwrap()).collect();

    let mut total_counts: HashMap<i64, i64> = HashMap::new();
    for &seed in &seeds {
        let mut secret_number = seed;
        let mut count = secret_number % 10;

        let mut diffs: Vec<i64> = Vec::with_capacity(2000);
        let mut counts: HashMap<i64, i64> = HashMap::new();
        for _ in 0..2000 {
            let next_secret_number = get_next_secret_number(secret_number);
            let next_count = next_secret_number % 10;

            diffs.push(next_count - count);
            if diffs.len() >= 4 {
                let id = get_sequence_id(&diffs);
                counts.entry(id).or_insert(next_count);
            }

            secret_number = next_secret_number;
            count = next_count;
        }

        for (&id, &count) in counts.iter() {
            *total_counts.entry(id).or_insert(0) += count;
        }
    }

    let (_, max_count) = total_counts.iter().max_by_key(|(_, &count)| count).unwrap();
    println!("{max_count}");
}
