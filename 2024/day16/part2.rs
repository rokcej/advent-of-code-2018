use std::cmp::Ordering;
use std::collections::{BinaryHeap, HashMap, HashSet};
use std::io::BufRead;
use std::u64;

struct Maze {
    walls: Vec<Vec<bool>>,
    x_start: i32,
    y_start: i32,
    x_end: i32,
    y_end: i32,
}

#[derive(PartialEq, Eq)]
struct State {
    x: i32,
    y: i32,
    dx: i32,
    dy: i32,
    score: u64,
    path: Vec<(i32, i32)>,
}

impl State {
    fn new(x: i32, y: i32, dx: i32, dy: i32, score: u64, mut path: Vec<(i32, i32)>) -> Self {
        path.push((x, y));
        return Self { x, y, dx, dy, score, path };
    }
}

impl Ord for State {
    fn cmp(&self, other: &Self) -> Ordering {
        return other.score.cmp(&self.score);
    }
}

impl PartialOrd for State {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        return Some(self.cmp(other));
    }
}

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn parse_maze(lines: &Vec<String>) -> Maze {
    let walls: Vec<Vec<bool>> = lines
        .iter()
        .map(|s| s.chars().map(|c| c == '#').collect())
        .collect();

    let (mut x_start, mut y_start) = (-1, -1);
    let (mut x_end, mut y_end) = (-1, -1);
    for (y, line) in lines.iter().enumerate() {
        if let Some(x) = line.chars().position(|c| c == 'S') {
            (x_start, y_start) = (x as i32, y as i32);
        } else if let Some(x) = line.chars().position(|c| c == 'E') {
            (x_end, y_end) = (x as i32, y as i32);
        }
    }

    return Maze { walls, x_start, y_start, x_end, y_end };
}

fn find_best_tile_count(maze: &Maze) -> u64 {
    let mut heap: BinaryHeap<State> = BinaryHeap::new();
    heap.push(State::new(maze.x_start, maze.y_start, 1, 0, 0, Vec::new()));
    let mut visited: HashMap<(i32, i32, i32, i32), u64> = HashMap::new();
    let mut best_tiles: HashSet<(i32, i32)> = HashSet::new();
    let mut lowest_score = u64::MAX;

    while let Some(State { x, y, dx, dy, score, path }) = heap.pop() {
        if score > lowest_score {
            break;
        }
        if x == maze.x_end && y == maze.y_end {
            lowest_score = score;
            best_tiles.extend(HashSet::<(i32, i32)>::from_iter(path));
            continue;
        }
        if maze.walls[y as usize][x as usize] {
            continue;
        }
        if let Some(&visited_score) = visited.get(&(x, y, dx, dy)) {
            if score > visited_score {
                continue;
            }
        }
        visited.insert((x, y, dx, dy), score);

        heap.push(State::new(x + dx, y + dy, dx, dy, score + 1, path.clone()));
        heap.push(State::new(x, y, dy, -dx, score + 1000, path.clone()));
        heap.push(State::new(x, y, -dy, dx, score + 1000, path.clone()));
    }

    return best_tiles.len() as u64;
}

fn main() {
    let lines = read_lines("day16/input");
    let maze = parse_maze(&lines);

    println!("{}", find_best_tile_count(&maze));
}
