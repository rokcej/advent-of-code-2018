use regex::Regex;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day03/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn main() {
    let lines = read_lines();
    let re = Regex::new(r"(mul\((\d{1,3}),(\d{1,3})\))|(do\(\))|(don't\(\))").unwrap();

    let mut result: i32 = 0;
    let mut enabled: bool = true;
    for line in lines {
        for captures in re.captures_iter(&line) {
            if captures.get(1).is_some() { // mul(first, second)
                if enabled {
                    let first: i32 = captures[2].parse().unwrap();
                    let second: i32 = captures[3].parse().unwrap();
                    result += first * second;
                }
            } else if captures.get(4).is_some() { // do()
                enabled = true;
            } else if captures.get(5).is_some() { // don't()
                enabled = false;
            }
        }
    }
    println!("{result}");
}
