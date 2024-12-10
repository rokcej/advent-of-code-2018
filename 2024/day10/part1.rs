use std::io::BufRead;

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn get_score(grid: &Vec<Vec<u8>>, (y, x): (usize, usize), depth: u8, counted: &mut Vec<(usize, usize)>) -> u32 {
    if y >= grid.len() || x >= grid[y].len() || depth != grid[y][x] || counted.contains(&(y, x)) {
        return 0;
    }
    if depth == 9 {
        counted.push((y, x));
        return 1;
    }

    return get_score(grid, (y, x - 1), depth + 1, counted)
        + get_score(grid, (y, x + 1), depth + 1, counted)
        + get_score(grid, (y - 1, x), depth + 1, counted)
        + get_score(grid, (y + 1, x), depth + 1, counted);
}

fn main() {
    let grid: Vec<Vec<u8>> = read_lines("day10/input")
        .into_iter()
        .map(|s| s.chars().map(|c| c.to_digit(10).unwrap() as u8).collect())
        .collect();

    let mut score_sum: u32 = 0;
    for y in 0..grid.len() {
        for x in 0..grid[y].len() {
            score_sum += get_score(&grid, (y, x), 0, &mut Vec::new());
        }
    }

    println!("{score_sum}");
}
