use std::{collections::HashMap, io::BufRead};

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn try_split(number: u64) -> Option<(u64, u64)> {
    let mut num_digits: u32 = 1;
    let mut order = 10;
    while number >= order {
        order *= 10;
        num_digits += 1;
    }

    if num_digits % 2 != 0 {
        return None;
    }
    let divisor = u64::pow(10, num_digits / 2);
    return Some((number / divisor, number % divisor));
}

fn get_count(stone: u64, remaining_blinks: u8, cache: &mut HashMap<(u64, u8), u64>) -> u64 {
    if remaining_blinks == 0 {
        return 1;
    }
    if let Some(&count) = cache.get(&(stone, remaining_blinks)) {
        return count;
    }

    let mut count = 0;
    if stone == 0 {
        count += get_count(1, remaining_blinks - 1, cache);
    } else if let Some((left, right)) = try_split(stone) {
        count += get_count(left, remaining_blinks - 1, cache);
        count += get_count(right, remaining_blinks - 1, cache);
    } else {
        count += get_count(2024 * stone, remaining_blinks - 1, cache);
    }

    cache.insert((stone, remaining_blinks), count);
    return count;
}

fn main() {
    let lines = read_lines("day11/input");

    let stones: Vec<u64> = lines[0]
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();
    let mut cache: HashMap<(u64, u8), u64> = HashMap::new();

    let mut total_count = 0;
    for &stone in &stones {
        total_count += get_count(stone, 75, &mut cache);
    }

    println!("{total_count}");
}
