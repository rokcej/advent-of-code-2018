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
    corners: u64
}

fn explore_region(grid: &Vec<Vec<char>>, counted: &mut Vec<Vec<bool>>, y: usize, x: usize) -> Region {
    let id = grid[y][x];
    let mut region = Region { area: 1, corners: 0 };
    counted[y][x] = true;

    let is_valid = |row: usize, col: usize| -> bool {
        return row < grid.len() && col < grid[row].len() && grid[row][col] == id;
    };

    let parallel_neighbors = [(y, x-1), (y, x+1), (y-1, x), (y+1, x)];
    for (y2, x2) in parallel_neighbors {
        if !is_valid(y2, x2) || counted[y2][x2] {
            continue;
        }

        let new_region = explore_region(grid, counted, y2, x2);
        region.area += new_region.area;
        region.corners += new_region.corners;
    }

    let diagonal_neighbors = [(y-1 , x-1), (y-1, x+1), (y+1, x-1), (y+1, x+1)];
    for (y2, x2) in diagonal_neighbors {
        let horizontal = is_valid(y, x2);
        let vertical = is_valid(y2, x);
        let diagonal = is_valid(y2, x2);

        if !horizontal && !vertical || horizontal && vertical && !diagonal {
            region.corners += 1;
        }
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
            let sides = region.corners; // Number of sides == number of corners
            total_price += region.area * sides;
        }
    }

    println!("{}", total_price);
}
