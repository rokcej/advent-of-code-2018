use std::io::BufRead;

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

struct Region {
    area: u64,
    perimeter: u64
}

fn explore_region(grid: &Vec<Vec<char>>, counted: &mut Vec<Vec<bool>>, y: usize, x: usize) -> Region {
    let id = grid[y][x];
    let mut region = Region { area: 1, perimeter: 0 };
    counted[y][x] = true;

    let parallel_neighbors = [(y, x-1), (y, x+1), (y-1, x), (y+1, x)];
    for (y2, x2) in parallel_neighbors {
        if y2 >= grid.len() || x2 >= grid[y2].len() || grid[y2][x2] != id {
            region.perimeter += 1;
            continue;
        }
        if counted[y2][x2] {
            continue;
        }

        let new_region = explore_region(grid, counted, y2, x2);
        region.area += new_region.area;
        region.perimeter += new_region.perimeter;
    }

    return region;
}

fn main() {
    let lines = read_lines("day12/input");

    let grid: Vec<Vec<char>> = lines.iter().map(|s| s.chars().collect()).collect();
    let mut counted: Vec<Vec<bool>> = grid.iter().map(|row| vec![false; row.len()]).collect();

    let mut total_price: u64 = 0;
    for y in 0..grid.len() {
        for x in 0..grid[y].len() {
            if counted[y][x] {
                continue;
            }

            let region = explore_region(&grid, &mut counted, y, x);
            total_price += region.area * region.perimeter;
        }
    }

    println!("{}", total_price);
}
