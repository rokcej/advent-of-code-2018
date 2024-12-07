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
    let re = Regex::new(r"mul\((\d{1,3}),(\d{1,3})\)").unwrap();

    let mut result: i32 = 0;
    for line in lines {
        for captures in re.captures_iter(&line) {
            let first: i32 = captures[1].parse().unwrap();
            let second: i32 = captures[2].parse().unwrap();
            result += first * second;
        }
    }
    println!("{result}");
}
