use std::io::BufRead;

struct Robot {
    px: i64,
    py: i64,
    vx: i64,
    vy: i64,
}

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn parse_robot(line: &String) -> Robot {
    let equations: Vec<&str> = line.split_whitespace().collect();
    let parse_coords = |equation: &str| -> (i64, i64) {
        let coords: Vec<i64> = equation
            .split('=')
            .nth(1)
            .unwrap()
            .split(',')
            .map(|s| s.parse().unwrap())
            .collect();
        return (coords[0], coords[1]);
    };

    let (px, py) = parse_coords(equations[0]);
    let (vx, vy) = parse_coords(equations[1]);
    return Robot { px, py, vx, vy };
}

// Greatest common divisor
fn gcd(a: u64, b: u64) -> u64 {
    if b == 0 {
        return a;
    }
    return gcd(b, a % b);
}

// Least common multiple
fn lcm(a: u64, b: u64) -> u64 {
    return (a * b) / gcd(a, b);
}

fn main() {
    let mut robots: Vec<Robot> = read_lines("day14/input").iter().map(parse_robot).collect();

    const WIDTH: i64 = 101;
    const HEIGHT: i64 = 103;

    // Calculate how many steps are needed to reach the initial state again
    // We know the christmas tree has to appear exactly once before this happens
    let mut max_steps: u64 = 1;
    for robot in &robots {
        let (mut px, mut py) = (robot.px, robot.py);
        for step in 1.. {
            px = (px + robot.vx).rem_euclid(WIDTH);
            py = (py + robot.vy).rem_euclid(HEIGHT);
            if px == robot.px && py == robot.py {
                max_steps = lcm(max_steps, step);
                break;
            }
        }
    }

    // Count how many neighbours robots have on each step (how many robots are "touching")
    // Any meaningful drawing should have a much higher neighbor count compared to random arrangements
    // (An alternative solution would be to find size of the largest connected group of robots)
    let mut grid = [[false; WIDTH as usize]; HEIGHT as usize];
    let mut neighbor_counts: Vec<u64> = vec![0; max_steps as usize];
    for step in 0..max_steps {
        for robot in &robots {
            grid[robot.py as usize][robot.px as usize] = true;
        }

        for robot in &robots {
            for y in [robot.py - 1, robot.py, robot.py + 1] {
                if y < 0 || y >= HEIGHT {
                    continue;
                }
                for x in [robot.px - 1, robot.px, robot.px + 1] {
                    if x < 0 || x >= WIDTH {
                        continue;
                    }
                    if !(x == robot.px && y == robot.py) && grid[y as usize][x as usize] {
                        neighbor_counts[step as usize] += 1;
                    }
                }
            }
        }

        for robot in &mut robots {
            grid[robot.py as usize][robot.px as usize] = false;
            robot.px = (robot.px + robot.vx).rem_euclid(WIDTH);
            robot.py = (robot.py + robot.vy).rem_euclid(HEIGHT);
        }
    }

    // Find step with the highest neighbor count
    let best_step = neighbor_counts
        .iter()
        .enumerate()
        .max_by_key(|(_, &count)| count)
        .map(|(step, _)| step)
        .unwrap();
    println!("{best_step}");
}
