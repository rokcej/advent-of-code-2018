use std::io::BufRead;

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

fn main() {
    let lines = read_lines("day11/input");

    let mut stones: Vec<u64> = lines[0]
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();

    for _blink in 0..25 {
        let size = stones.len();
        for i in 0..size {
            let stone = stones[i];
            if stone == 0 {
                stones[i] = 1;
            } else if let Some((left, right)) = try_split(stone) {
                stones[i] = left;
                stones.push(right);
            } else {
                stones[i] *= 2024;
            }
        }
    }

    println!("{}", stones.len());
}
