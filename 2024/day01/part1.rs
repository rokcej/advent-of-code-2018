use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day01/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn main() {
    let lines = read_lines();

    let mut left_list: Vec<i32> = Vec::new();
    let mut right_list: Vec<i32> = Vec::new();
    for line in lines {
        let mut iter = line.split_whitespace();
        left_list.push(iter.next().unwrap().parse().unwrap());
        right_list.push(iter.next().unwrap().parse().unwrap());
    }

    left_list.sort();
    right_list.sort();

    let mut total_distance: i32 = 0;
    for (left, right) in left_list.into_iter().zip(right_list) {
        total_distance += (right - left).abs();
    }
    println!("{total_distance}");
}
