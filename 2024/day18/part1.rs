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

fn get_steps_to_exit(bytes: &Vec<Vec<bool>>, pos_start: (i32, i32), pos_exit: (i32, i32)) -> i32 {
    let mut positions = vec![pos_start];
    let mut visited = bytes.clone(); // We can safely interpret inaccessible positions as visited
    let height = visited.len() as i32;
    let width = visited[0].len() as i32;

    for step in 0.. {
        let mut new_positions: Vec<(i32, i32)> = Vec::with_capacity(positions.len());
        for &(x, y) in &positions {
            if (x, y) == pos_exit {
                return step;
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

    return -1;
}

fn main() {
    const SIZE: usize = 71;
    const POS_START: (i32, i32) = (0, 0);
    const POS_EXIT: (i32, i32) = (70, 70);
    const MAX_BYTES: usize = 1024;

    let lines = read_lines("day18/input");
    let byte_positions: Vec<(i32, i32)> = lines.iter().map(parse_position).collect();
    let mut bytes = vec![vec![false; SIZE]; SIZE];

    for &(x, y) in &byte_positions[..MAX_BYTES] {
        bytes[y as usize][x as usize] = true;
    }

    let steps = get_steps_to_exit(&bytes, POS_START, POS_EXIT);
    println!("{steps}");
}
