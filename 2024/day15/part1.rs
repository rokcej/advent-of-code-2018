use std::io::BufRead;

#[derive(PartialEq, Clone, Copy)]
enum Entity {
    None,
    Wall,
    Box,
    Robot,
}

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn is_valid(grid: &Vec<Vec<Entity>>, x: i32, y: i32) -> bool {
    // Underflow is your friend
    return (y as usize) < grid.len() && (x as usize) < grid[0].len();
}

fn try_move_box(grid: &mut Vec<Vec<Entity>>, x: i32, y: i32, dx: i32, dy: i32) -> bool {
    let (x2, y2) = (x + dx, y + dy);
    if !is_valid(grid, x2, y2) {
        return false;
    }

    match grid[y2 as usize][x2 as usize] {
        Entity::None => {
            grid[y2 as usize][x2 as usize] = Entity::Box;
            grid[y as usize][x as usize] = Entity::None;
            return true;
        }
        Entity::Box => {
            if try_move_box(grid, x2, y2, dx, dy) {
                grid[y2 as usize][x2 as usize] = Entity::Box;
                grid[y as usize][x as usize] = Entity::None;
                return true;
            }
        }
        _ => {}
    }

    return false;
}

fn main() {
    let lines = read_lines("day15/input");
    let i_empty_line = lines.iter().position(|s| s.is_empty()).unwrap();

    let mut grid: Vec<Vec<Entity>> = lines[..i_empty_line]
        .iter()
        .map(|s| {
            s.chars()
                .map(|c| match c {
                    '.' => Entity::None,
                    '#' => Entity::Wall,
                    'O' => Entity::Box,
                    '@' => Entity::Robot,
                    _ => panic!("Error parsing map"),
                })
                .collect()
        })
        .collect();

    let moves: Vec<(i32, i32)> = lines[i_empty_line + 1..]
        .iter()
        .map(|s| {
            s.chars().map(|c| match c {
                '<' => (-1, 0),
                '>' => (1, 0),
                '^' => (0, -1),
                'v' => (0, 1),
                _ => panic!("Error parsing moves"),
            })
        })
        .flatten()
        .collect();

    let (mut x, mut y) = (|| {
        for iy in 0..grid.len() {
            for ix in 0..grid[0].len() {
                if grid[iy][ix] == Entity::Robot {
                    return (ix as i32, iy as i32);
                }
            }
        }
        panic!("Missing robot position");
    })();
    grid[y as usize][x as usize] = Entity::None; // No need to keep track of the robot in 2 places

    for &(dx, dy) in &moves {
        let (x2, y2) = (x + dx, y + dy);
        if !is_valid(&grid, x2, y2) {
            continue;
        }

        match grid[y2 as usize][x2 as usize] {
            Entity::None => (x, y) = (x2, y2),
            Entity::Wall => (), // Nothing to do
            Entity::Box => {
                if try_move_box(&mut grid, x2, y2, dx, dy) {
                    (x, y) = (x2, y2);
                }
            }
            Entity::Robot => panic!("This shouldn't happen"),
        }
    }

    let mut gps_coordinate_sum: u64 = 0;
    for iy in 0..grid.len() {
        for ix in 0..grid[iy].len() {
            if grid[iy][ix] == Entity::Box {
                gps_coordinate_sum += 100 * (iy as u64) + (ix as u64);
            }
        }
    }

    println!("{gps_coordinate_sum}");
}
