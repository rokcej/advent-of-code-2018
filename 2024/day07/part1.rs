use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day07/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn main() {
    let mut valid_result_sum: u64 = 0;
    for line in read_lines() {
        let parts: Vec<&str> = line.split(": ").collect();
        let result: u64 = parts[0].parse().unwrap();
        let values: Vec<u64> = parts[1]
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();

        let mut computations: Vec<u64> = vec![values[0]];
        for &value in &values[1..] {
            let mut new_computations: Vec<u64> = Vec::with_capacity(computations.len() * 2);
            for computation in computations {
                new_computations.push(computation + value);
                new_computations.push(computation * value);
            }
            computations = new_computations;
        }

        if computations.contains(&result) {
            valid_result_sum += result;
        }
    }

    println!("{valid_result_sum}");
}
