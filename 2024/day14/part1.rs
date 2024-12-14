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

fn main() {
    let mut robots: Vec<Robot> = read_lines("day14/input").iter().map(parse_robot).collect();

    const WIDTH: i64 = 101;
    const HEIGHT: i64 = 103;
    const STEPS: i64 = 100;

    let mut quadrants: [u64; 4] = [0, 0, 0, 0];
    for robot in &mut robots {
        robot.px = (robot.px + robot.vx * STEPS).rem_euclid(WIDTH);
        robot.py = (robot.py + robot.vy * STEPS).rem_euclid(HEIGHT);

        if robot.px == WIDTH / 2 || robot.py == HEIGHT / 2 {
            continue;
        }

        let qx = (robot.px > (WIDTH / 2)) as usize;
        let qy = (robot.py > (HEIGHT / 2)) as usize;
        quadrants[2 * qy + qx] += 1;
    }

    let safety_factor: u64 = quadrants.iter().product();
    println!("{safety_factor}");
}
