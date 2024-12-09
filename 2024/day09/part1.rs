use std::fs::File;
use std::io::{BufRead, BufReader};

fn read_lines() -> Vec<String> {
    let file = File::open("day09/input").expect("Error opening input");
    return BufReader::new(file)
        .lines()
        .map(|l| l.expect("Error reading line"))
        .collect();
}

fn main() {
    let lines = read_lines();

    let disk_map: Vec<usize> = lines[0]
        .chars()
        .map(|c| c.to_digit(10).unwrap() as usize)
        .collect();
    let disk_size: usize = disk_map.iter().map(|&x| x as usize).sum();

    let mut disk: Vec<i32> = vec![-1; disk_size];
    {
        // Write data to disk
        let mut disk_offset: usize = 0;
        let mut file_id: i32 = 0;
        for (i, &count) in disk_map.iter().enumerate() {
            if i % 2 == 0 {
                for j in 0..count {
                    disk[disk_offset + j] = file_id;
                }
                file_id += 1;
            }
            disk_offset += count as usize;
        }
    }

    {
        // Move file blocks
        let mut head: usize = 0;
        let mut tail: usize = disk.len() - 1;

        while head < tail {
            if disk[head] >= 0 {
                head += 1;
                continue;
            }
            if disk[tail] < 0 {
                tail -= 1;
                continue;
            }

            disk.swap(head, tail);
            head += 1;
            tail -= 1;
        }
    }

    let mut checksum: usize = 0;
    for (i, &val) in disk.iter().enumerate() {
        if val < 0 {
            break;
        }
        checksum += i * (val as usize);
    }

    println!("{checksum}");
}
