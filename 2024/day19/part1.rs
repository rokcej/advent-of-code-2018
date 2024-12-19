use std::io::BufRead;

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn can_match_design(towels: &Vec<&str>, design: &str) -> bool {
    if design.is_empty() {
        return true;
    }

    for &towel in towels {
        if design.starts_with(towel) && can_match_design(towels, &design[towel.len()..]) {
            return true;
        }
    }

    return false;
}

fn main() {
    let lines = read_lines("day19/input");
    let towels: Vec<&str> = lines[0].split(", ").collect();
    let designs: Vec<&str> = lines.iter().skip(2).map(|s| s.as_str()).collect();

    let mut count: u32 = 0;
    for &design in &designs {
        if can_match_design(&towels, design) {
            count += 1;
        }
    }

    println!("{count}");
}
