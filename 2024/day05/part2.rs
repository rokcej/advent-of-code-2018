use std::collections::HashMap;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day05/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn get_invalid_indices(pages: &Vec<i32>, ordering: &HashMap<i32, Vec<i32>>) -> Option<(usize, usize)> {
    let indices: HashMap<i32, usize> = pages.iter().cloned().enumerate().map(|(i, p)| (p, i)).collect();

    for (index, page) in pages.iter().enumerate() {
        for later_page in ordering[page].iter() {
            if let Some(&later_index) = indices.get(later_page) {
                if index >= later_index {
                    return Some((index, later_index));
                }
            }
        }
    }

    return None;
}

fn main() {
    let lines = read_lines();
    let index = lines.iter().position(|s| s.is_empty()).unwrap();

    let ordering_lines = &lines[..index];
    let update_lines = &lines[index + 1..];

    let mut ordering: HashMap<i32, Vec<i32>> = HashMap::new();
    for line in ordering_lines {
        let pages: Vec<i32> = line.split('|').map(|s| s.parse().unwrap()).collect();
        ordering.entry(pages[0]).or_insert(Vec::new()).push(pages[1]);
    }

    let mut result: i32 = 0;
    for line in update_lines {
        let mut pages: Vec<i32> = line.split(',').map(|s| s.parse().unwrap()).collect();

		let mut was_valid = true;
        while let Some((i, j)) = get_invalid_indices(&pages, &ordering) {
            pages.swap(i, j);
			was_valid = false;
        }

		if !was_valid {
        	result += pages[pages.len() / 2];
		}
    }

    println!("{result}");
}
