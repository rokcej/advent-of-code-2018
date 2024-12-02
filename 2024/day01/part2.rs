use std::collections::HashMap;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("input").expect("Error opening input");
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

    let mut id_counts: HashMap<i32, i32> = HashMap::new();
    for id in right_list {
        *id_counts.entry(id).or_insert(0) += 1;
    }

    let mut score: i32 = 0;
    for id in left_list {
        score += id * (id_counts.get(&id).unwrap_or(&0));
    }
    println!("{score}");
}
