use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day02/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn is_safe(report: &Vec<i32>) -> bool {
    if report.len() < 2 {
        return false;
    }

    let sign = (report[1] - report[0]).signum();
    if sign == 0 {
        return false;
    }

    for i in 1..report.len() {
        let diff = report[i] - report[i - 1];
        if !(diff.signum() == sign && diff.abs() <= 3) {
            return false;
        }
    }

    return true;
}

fn main() {
    let lines = read_lines();

    let mut safe_count: u32 = 0;
    for line in lines {
        let report: Vec<i32> = line
            .split_whitespace()
            .map(|s| s.parse::<i32>().unwrap())
            .collect();
        if is_safe(&report) {
            safe_count += 1;
        }
    }
    println!("{safe_count}");
}
