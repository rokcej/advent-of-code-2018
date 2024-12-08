use std::collections::HashMap;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day08/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn main() {
    let lines = read_lines();

    let mut antennas: HashMap<char, Vec<(i32, i32)>> = HashMap::new();
    let mut antinodes: Vec<Vec<bool>> = lines
        .iter()
        .map(|s| s.chars().map(|_| false).collect())
        .collect();
    let mut antinode_count: i32 = 0;

    let height = antinodes.len() as i32;
    let width = antinodes[0].len() as i32;

    // Get antenna locations
    for (y, line) in lines.iter().enumerate() {
        for (x, character) in line.char_indices() {
            if character == '.' {
                continue;
            }
            antennas
                .entry(character)
                .or_insert(Vec::new())
                .push((y as i32, x as i32));
        }
    }

    // Find antinodes
    for positions in antennas.values() {
        for (i, (y0, x0)) in positions.iter().enumerate() {
            for (y1, x1) in &positions[i + 1..] {
                let (dy, dx) = (y1 - y0, x1 - x0);
                for (y, x) in [(y0 - dy, x0 - dx), (y1 + dy, x1 + dx)] {
                    if !(y >= 0 && y < height && x >= 0 && x < width) {
                        continue;
                    }
                    if !antinodes[y as usize][x as usize] {
                        antinodes[y as usize][x as usize] = true;
                        antinode_count += 1;
                    }
                }
            }
        }
    }

    println!("{antinode_count}");
}
