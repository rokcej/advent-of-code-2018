use std::collections::HashMap;
use std::io::BufRead;

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn count_possible_designs<'a>(towels: &Vec<&str>, design: &'a str, cache: & mut HashMap<&'a str, u64>) -> u64 {
    if design.is_empty() {
        return 1;
    }

    if let Some(&cached_count) = cache.get(design) {
        return cached_count;
    }

    let mut count: u64 = 0;
    for &towel in towels {
        if design.starts_with(towel) {
            count += count_possible_designs(towels, &design[towel.len()..], cache);
        }
    }

    cache.insert(design, count);
    return count;
}

fn main() {
    let lines = read_lines("day19/input");
    let towels: Vec<&str> = lines[0].split(", ").collect();
    let designs: Vec<&str> = lines.iter().skip(2).map(|s| s.as_str()).collect();

    let mut count: u64 = 0;
    for &design in &designs {
        count += count_possible_designs(&towels, design, &mut HashMap::new());
    }

    println!("{count}");
}
