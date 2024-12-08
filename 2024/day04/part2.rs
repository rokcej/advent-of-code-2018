use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day04/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn main() {
    let lines = read_lines();
    let pattern: String = String::from("MAS");
    let pattern_rev: String = pattern.chars().rev().collect();

    let mut count: u32 = 0;
    for i in 0..lines.len() - pattern.len() + 1 {
        for j in 0..lines[i].len() - pattern.len() + 1 {
            let diagonal: String = (0..pattern.len())
                .map(|k| lines[i + k].chars().nth(j + k).unwrap())
                .collect();
            let diagonal2: String = (0..pattern.len())
                .map(|k| lines[i + k].chars().nth(j + pattern.len() - 1 - k).unwrap())
                .collect();

            if [diagonal, diagonal2]
                .into_iter()
                .all(|s| s.eq(&pattern) || s.eq(&pattern_rev))
            {
                count += 1;
            }
        }
    }
    println!("{count}");
}
