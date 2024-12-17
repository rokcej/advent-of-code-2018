// This solution is hard-coded for the program from my input (2,4,1,1,7,5,4,0,0,3,1,6,5,5,3,0).
// I solved it by manually decompiling and analyzing the program.
//
// do {
//     B = A % 8;
//     B = B ^ 1;
//     C = A / (1 << B);
//     B = B ^ C;
//     A = A / 8;
//     B = B ^ 6;
//     output(B % 8);
// } while (A != 0);
//
// Observation:
// * A gets divided by 8 in every loop iteration. The program keeps looping until A becomes 0.
// Solution:
// * Start at the last iteration and find values of A that generate the correct output.
// * Move on to the "previous" iteration and multiply A by 8.

use std::io::BufRead;

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn main() {
    let lines = read_lines("day17/input");
    let program: Vec<u64> = lines[4][9..]
        .split(',')
        .map(|s| s.parse().unwrap())
        .collect();

    let mut candidates: Vec<u64> = vec![0];
    for &expected_output in program.iter().rev() {
        let mut new_candidates: Vec<u64> = vec![];
        for &prev_reg_a in &candidates {
            for value in 0..=7 {
                let reg_a = (prev_reg_a * 8) | value;
                let temp = (reg_a % 8) ^ 1;
                let output = (temp ^ (reg_a / (1 << temp)) ^ 6) % 8;
                if output == expected_output {
                    new_candidates.push(reg_a);
                }
            }
        }
        std::mem::swap(&mut candidates, &mut new_candidates);
    }

    let lowest_initial_a = candidates.iter().min().unwrap();
    println!("{lowest_initial_a}");
}
