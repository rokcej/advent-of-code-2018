use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day06/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn main() {
    let lines = read_lines();

    let grid: Vec<Vec<bool>> = lines
        .iter()
        .map(|s| s.chars().map(|c| c == '#').collect())
        .collect();
    let size: (i32, i32) = (grid.len() as i32, grid[0].len() as i32);

    let mut pos: (i32, i32) = (|| {
        for (i, line) in lines.iter().enumerate() {
            if let Some(j) = line.chars().position(|c| c == '^') {
                return Some((i as i32, j as i32));
            }
        }
        return None;
    })()
    .unwrap();
    let mut dir: (i32, i32) = (-1, 0);

    let mut visited: Vec<Vec<bool>> = grid
        .iter()
        .map(|v| v.iter().map(|_| false).collect())
        .collect();
    visited[pos.0 as usize][pos.1 as usize] = true;
    let mut visited_count: i32 = 1;

    loop {
        let new_pos = (pos.0 + dir.0, pos.1 + dir.1);
        if !(new_pos.0 >= 0 && new_pos.0 < size.0 && new_pos.1 >= 0 && new_pos.1 < size.1) {
            break;
        }

        if grid[new_pos.0 as usize][new_pos.1 as usize] {
            dir = (dir.1, -dir.0);
        } else {
            if !visited[new_pos.0 as usize][new_pos.1 as usize] {
                visited[new_pos.0 as usize][new_pos.1 as usize] = true;
                visited_count += 1;
            }
            pos = new_pos;
        }
    }

    println!("{visited_count}");
}
