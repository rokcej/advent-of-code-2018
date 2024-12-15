use std::io::BufRead;

#[derive(PartialEq, Clone, Copy)]
enum Entity {
    None,
    Wall,
    BoxLeft,
    BoxRight,
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

fn try_move_box_horizontally(grid: &mut Vec<Vec<Entity>>, x: i32, y: i32, dx: i32) -> bool {
    let (x2, x3) = (x + dx, x + 2 * dx);
    if !is_valid(grid, x3, y) {
        return false;
    }

    match grid[y as usize][x3 as usize] {
        Entity::None => {
            let row = &mut grid[y as usize];
            row[x3 as usize] = row[x2 as usize];
            row[x2 as usize] = row[x as usize];
            row[x as usize] = Entity::None;
            return true;
        }
        Entity::BoxLeft | Entity::BoxRight => {
            if try_move_box_horizontally(grid, x3, y, dx) {
                let row = &mut grid[y as usize];
                row[x3 as usize] = row[x2 as usize];
                row[x2 as usize] = row[x as usize];
                row[x as usize] = Entity::None;
                return true;
            }
            return false;
        }
        _ => return false,
    }
}

fn can_move_box_vertically(grid: &Vec<Vec<Entity>>, x: i32, y: i32, dy: i32) -> bool {
    if !is_valid(grid, x, y + dy) {
        return false;
    }

    let x2 = if grid[y as usize][x as usize] == Entity::BoxLeft {
        x + 1
    } else {
        x - 1
    };

    let pushed = grid[(y + dy) as usize][x as usize];
    let pushed2 = grid[(y + dy) as usize][x2 as usize];
    if pushed == Entity::Wall || pushed2 == Entity::Wall {
        return false;
    }
    if pushed == Entity::BoxLeft || pushed == Entity::BoxRight {
        if !can_move_box_vertically(grid, x, y + dy, dy) {
            return false;
        }
    }
    if pushed2 == Entity::BoxLeft || pushed2 == Entity::BoxRight {
        if !can_move_box_vertically(grid, x2, y + dy, dy) {
            return false;
        }
    }

    return true;
}

fn move_box_vertically(grid: &mut Vec<Vec<Entity>>, x: i32, y: i32, dy: i32) {
    if !is_valid(grid, x, y + dy) {
        return;
    }

    let x2 = if grid[y as usize][x as usize] == Entity::BoxLeft {
        x + 1
    } else {
        x - 1
    };

    let pushed = grid[(y + dy) as usize][x as usize];
    if pushed == Entity::BoxLeft || pushed == Entity::BoxRight {
        move_box_vertically(grid, x, y + dy, dy);
    }

    let pushed2 = grid[(y + dy) as usize][x2 as usize];
    if pushed2 == Entity::BoxLeft || pushed2 == Entity::BoxRight {
        move_box_vertically(grid, x2, y + dy, dy);
    }

    grid[(y + dy) as usize][x as usize] = grid[y as usize][x as usize];
    grid[(y + dy) as usize][x2 as usize] = grid[y as usize][x2 as usize];
    grid[y as usize][x as usize] = Entity::None;
    grid[y as usize][x2 as usize] = Entity::None;
}

fn try_move_box(grid: &mut Vec<Vec<Entity>>, x: i32, y: i32, dx: i32, dy: i32) -> bool {
    if dx != 0 {
        return try_move_box_horizontally(grid, x, y, dx);
    } else {
        if can_move_box_vertically(grid, x, y, dy) {
            move_box_vertically(grid, x, y, dy);
            return true;
        }
        return false;
    }
}

fn main() {
    let lines = read_lines("day15/input");
    let i_empty_line = lines.iter().position(|s| s.is_empty()).unwrap();

    let mut grid: Vec<Vec<Entity>> = lines[..i_empty_line]
        .iter()
        .map(|s| {
            s.chars()
                .map(|c| match c {
                    '.' => [Entity::None, Entity::None],
                    '#' => [Entity::Wall, Entity::Wall],
                    'O' => [Entity::BoxLeft, Entity::BoxRight],
                    '@' => [Entity::Robot, Entity::None],
                    _ => panic!("Error parsing map"),
                })
                .flatten()
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
            Entity::BoxLeft | Entity::BoxRight => {
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
            if grid[iy][ix] == Entity::BoxLeft {
                gps_coordinate_sum += 100 * (iy as u64) + (ix as u64);
            }
        }
    }

    println!("{gps_coordinate_sum}");
}
