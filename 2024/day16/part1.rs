use std::cmp::Ordering;
use std::collections::{BinaryHeap, HashSet};
use std::io::BufRead;

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
}

impl State {
    fn new(x: i32, y: i32, dx: i32, dy: i32, score: u64) -> Self {
        return Self { x, y, dx, dy, score };
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

fn find_lowest_score(maze: &Maze) -> u64 {
    let mut heap: BinaryHeap<State> = BinaryHeap::new();
    heap.push(State::new(maze.x_start, maze.y_start, 1, 0, 0));
    let mut visited: HashSet<(i32, i32, i32, i32)> = HashSet::new();

    while let Some(State { x, y, dx, dy, score }) = heap.pop() {
        if x == maze.x_end && y == maze.y_end {
            return score;
        }
        if maze.walls[y as usize][x as usize] {
            continue;
        }
        if visited.contains(&(x, y, dx, dy)) {
            continue;
        }
        visited.insert((x, y, dx, dy));

        heap.push(State::new(x + dx, y + dy, dx, dy, score + 1));
        heap.push(State::new(x, y, dy, -dx, score + 1000));
        heap.push(State::new(x, y, -dy, dx, score + 1000));
    }

    panic!("No solution!");
}

fn main() {
    let lines = read_lines("day16/input");
    let maze = parse_maze(&lines);

    println!("{}", find_lowest_score(&maze));
}
