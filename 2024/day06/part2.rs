use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day06/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn is_loop(grid: &Vec<Vec<bool>>, start_pos: (i32, i32)) -> bool {
    let size: (i32, i32) = (grid.len() as i32, grid[0].len() as i32);

    let mut pos = start_pos;
    let dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)];
    let mut i_dir: usize = 0;

    let mut visited: Vec<Vec<[bool; 4]>> = grid
        .iter()
        .map(|v| v.iter().map(|_| [false; 4]).collect())
        .collect();
    visited[pos.0 as usize][pos.1 as usize][i_dir] = true;

    loop {
        {
            let new_pos = (pos.0 + dirs[i_dir].0, pos.1 + dirs[i_dir].1);
            if !(new_pos.0 >= 0 && new_pos.0 < size.0 && new_pos.1 >= 0 && new_pos.1 < size.1) {
                return false;
            }

            if grid[new_pos.0 as usize][new_pos.1 as usize] {
                i_dir = (i_dir + 1) % dirs.len();
            } else {
                pos = new_pos;
            }
        }

        if visited[pos.0 as usize][pos.1 as usize][i_dir] {
            return true;
        }
        visited[pos.0 as usize][pos.1 as usize][i_dir] = true;
    }
}

fn main() {
    let lines = read_lines();

    let mut grid: Vec<Vec<bool>> = lines
        .iter()
        .map(|s| s.chars().map(|c| c == '#').collect())
        .collect();

    let start_pos: (i32, i32) = (|| {
        for (i, line) in lines.iter().enumerate() {
            if let Some(j) = line.chars().position(|c| c == '^') {
                return Some((i as i32, j as i32));
            }
        }
        return None;
    })()
    .unwrap();

    let mut loop_count: i32 = 0;
    for i in 0..grid.len() {
        for j in 0..grid[i].len() {
            if grid[i][j] {
                continue;
            }
            if (i as i32, j as i32) == start_pos {
                continue;
            }

            grid[i][j] = true;
            if is_loop(&grid, start_pos) {
                loop_count += 1;
            }
            grid[i][j] = false;
        }
    }

    println!("{loop_count}");
}
