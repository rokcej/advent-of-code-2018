use std::io::BufRead;

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn parse_position(line: &String) -> (i32, i32) {
    let (sx, sy) = line.split_once(',').unwrap();
    return (sx.parse().unwrap(), sy.parse().unwrap());
}

fn can_reach_exit(bytes: &Vec<Vec<bool>>, pos_start: (i32, i32), pos_exit: (i32, i32)) -> bool {
    let mut positions = vec![pos_start];
    let mut visited = bytes.clone(); // We can safely interpret inaccessible positions as visited
    let height = visited.len() as i32;
    let width = visited[0].len() as i32;

    while !positions.is_empty() {
        let mut new_positions: Vec<(i32, i32)> = Vec::with_capacity(positions.len());
        for &(x, y) in &positions {
            if (x, y) == pos_exit {
                return true;
            }
            if !(x >= 0 && x < width && y >= 0 && y < height) {
                continue;
            }
            if visited[y as usize][x as usize] {
                continue;
            }
            visited[y as usize][x as usize] = true;

            new_positions.push((x - 1, y));
            new_positions.push((x + 1, y));
            new_positions.push((x, y - 1));
            new_positions.push((x, y + 1));
        }
        std::mem::swap(&mut positions, &mut new_positions);
    }

    return false;
}

fn main() {
    const SIZE: usize = 71;
    const POS_START: (i32, i32) = (0, 0);
    const POS_EXIT: (i32, i32) = (70, 70);
    const SKIP_BYTES: usize = 1024;

    let lines = read_lines("day18/input");
    let byte_positions: Vec<(i32, i32)> = lines.iter().map(parse_position).collect();
    let mut bytes = vec![vec![false; SIZE]; SIZE];

    for &(x, y) in &byte_positions[..SKIP_BYTES] {
        bytes[y as usize][x as usize] = true;
    }

    for &(x, y) in byte_positions.iter().skip(SKIP_BYTES) {
        bytes[y as usize][x as usize] = true;
        if !can_reach_exit(&bytes, POS_START, POS_EXIT) {
            println!("{x},{y}");
            return;
        }
    }

    panic!("No solution!");
}
