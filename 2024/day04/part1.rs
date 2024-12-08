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
    let pattern: String = String::from("XMAS");
    let pattern_rev: String = pattern.chars().rev().collect();

    let mut count: u32 = 0;
    for i in 0..lines.len() {
        for j in 0..lines[i].len() {
            let mut candidates: Vec<String> = Vec::with_capacity(4);

            let horizontal: String = (0..pattern.len())
                .map(|k| lines[i].chars().nth(j + k).unwrap_or('\0'))
                .collect();
            candidates.push(horizontal);

            if i <= lines.len() - pattern.len() {
                let vertical: String = (0..pattern.len())
                    .map(|k| lines[i + k].chars().nth(j).unwrap_or('\0'))
                    .collect();
                candidates.push(vertical);

                let diagonal: String = (0..pattern.len())
                    .map(|k| lines[i + k].chars().nth(j + k).unwrap_or('\0'))
                    .collect();
                candidates.push(diagonal);

                let diagonal2: String = (0..pattern.len())
                    .map(|k| {
                        lines[i + k]
                            .chars()
                            .nth(j + pattern.len() - 1 - k)
                            .unwrap_or('\0')
                    })
                    .collect();
                candidates.push(diagonal2);
            }

            for candidate in candidates {
                if candidate.eq(&pattern) || candidate.eq(&pattern_rev) {
                    count += 1;
                }
            }
        }
    }
    println!("{count}");
}
