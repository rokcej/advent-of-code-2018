use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day09/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

struct Entity {
    offset: usize,
    size: usize,
}

fn main() {
    let lines = read_lines();

    let disk_map: Vec<usize> = lines[0]
        .chars()
        .map(|c| c.to_digit(10).unwrap() as usize)
        .collect();
    let disk_size: usize = disk_map.iter().map(|&x| x as usize).sum();

    let mut files: Vec<Entity> = Vec::with_capacity((disk_size + 1) / 2);
    let mut spaces: Vec<Entity> = Vec::with_capacity(disk_size / 2);
    {
        // Parse files and spaces
        let mut disk_offset: usize = 0;
        for (i, &size) in disk_map.iter().enumerate() {
            let target = if i % 2 == 0 { &mut files } else { &mut spaces };
            target.push(Entity {
                offset: disk_offset,
                size: size,
            });
            disk_offset += size;
        }
    }

    {
        // Move files
        for file in files.iter_mut().rev() {
            for space in &mut spaces {
                if space.offset >= file.offset {
                    break;
                }
                if space.size >= file.size {
                    file.offset = space.offset;
                    space.offset += file.size;
                    space.size -= file.size; // TODO: Remove space if size == 0
                    break;
                }
            }
        }
    }

    let mut checksum: usize = 0;
    for (id, file) in files.iter().enumerate() {
        for i in 0..file.size {
            checksum += id * (file.offset + i);
        }
    }

    println!("{checksum}");
}
