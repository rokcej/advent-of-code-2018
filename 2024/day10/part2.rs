use std::io::BufRead;

fn read_lines() -> Vec<String> {
    let file = std::fs::File::open("day10/input").expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn get_score(grid: &Vec<Vec<u8>>, (y, x): (usize, usize), depth: u8) -> u32 {
    if y >= grid.len() || x >= grid[y].len() || depth != grid[y][x] {
        return 0;
    }
    if depth == 9 {
        return 1;
    }

    return get_score(grid, (y, x - 1), depth + 1)
        + get_score(grid, (y, x + 1), depth + 1)
        + get_score(grid, (y - 1, x), depth + 1)
        + get_score(grid, (y + 1, x), depth + 1);
}

fn main() {
    let grid: Vec<Vec<u8>> = read_lines()
        .into_iter()
        .map(|s| s.chars().map(|c| c.to_digit(10).unwrap() as u8).collect())
        .collect();

    let mut score_sum: u32 = 0;
    for y in 0..grid.len() {
        for x in 0..grid[y].len() {
            score_sum += get_score(&grid, (y, x), 0);
        }
    }

    println!("{score_sum}");
}
