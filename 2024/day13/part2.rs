use regex::Regex;
use std::io::BufRead;

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn main() {
    let lines = read_lines("day13/input");

    let button_regex = Regex::new(r"X\+(\d*), Y\+(\d*)").unwrap();
    let parse_button = |line: &str| -> (i64, i64) {
        let captures = button_regex.captures(line).unwrap();
        return (captures[1].parse().unwrap(), captures[2].parse().unwrap());
    };

    let prize_regex = Regex::new(r"X=(\d*), Y=(\d*)").unwrap();
    let parse_prize = |line: &str| -> (i64, i64) {
        const OFFSET: i64 = 10000000000000;
        let captures = prize_regex.captures(line).unwrap();
        return (
            captures[1].parse::<i64>().unwrap() + OFFSET,
            captures[2].parse::<i64>().unwrap() + OFFSET,
        );
    };

    let mut total_tokens = 0;
    for i in (0..lines.len()).step_by(4) {
        let (x_a, y_a) = parse_button(&lines[i]);
        let (x_b, y_b) = parse_button(&lines[i + 1]);
        let (x, y) = parse_prize(&lines[i + 2]);

        // Definition:
        // a * x_a + b * x_b = x
        // a * y_a + b * y_b = y
        // Derivation:
        // a = (x - b * x_b) / x_a = (y - b * y_b) / y_a
        // x * y_a - b * x_b * y_a = y * x_a - b * y_b * x_a
        // b * (y_b * x_a - x_b * y_a) = y * x_a - x * y_a
        // b = (y * x_a - x * y_a) / (y_b * x_a - x_b * y_a)

        let b_numerator = y * x_a - x * y_a;
        let b_denominator = y_b * x_a - x_b * y_a;
        if b_numerator % b_denominator != 0 {
            continue; // b is not an integer
        }
        let b = b_numerator / b_denominator;

        let a_numerator = x - b * x_b;
        let a_denominator = x_a;
        if a_numerator % a_denominator != 0 {
            continue; // a is not an integer
        }
        let a = a_numerator / a_denominator;

        total_tokens += 3 * a + b;
    }

    println!("{total_tokens}");
}
