use std::io::BufRead;

struct Computer {
    reg_a: u64,
    reg_b: u64,
    reg_c: u64,
    pointer: usize,
    program: Vec<u64>,
}

impl Computer {
    fn get_combo(&self, operand: u64) -> u64 {
        match operand {
            0..=3 => return operand,
            4 => return self.reg_a,
            5 => return self.reg_b,
            6 => return self.reg_c,
            _ => panic!("Invalid combo operand: {}", operand),
        };
    }

    fn run(&mut self) -> Vec<u64> {
        let mut output: Vec<u64> = Vec::new();

        while self.pointer < self.program.len() - 1 {
            let opcode = self.program[self.pointer];
            let operand = self.program[self.pointer + 1];

            match opcode {
                0 => self.reg_a /= 1 << self.get_combo(operand),
                1 => self.reg_b ^= operand,
                2 => self.reg_b = self.get_combo(operand) % 8,
                3 => {
                    if self.reg_a != 0 {
                        self.pointer = operand as usize;
                        continue;
                    }
                }
                4 => self.reg_b ^= self.reg_c,
                5 => output.push(self.get_combo(operand) % 8),
                6 => self.reg_b = self.reg_a / (1 << self.get_combo(operand)),
                7 => self.reg_c = self.reg_a / (1 << self.get_combo(operand)),
                _ => panic!("Invalid instruction: {}", opcode),
            };

            self.pointer += 2;
        }

        return output;
    }
}

fn read_lines(path: &str) -> Vec<String> {
    let file = std::fs::File::open(path).expect("Error opening input");
    return std::io::BufReader::new(file)
        .lines()
        .map(Result::unwrap)
        .collect();
}

fn parse_computer(lines: &Vec<String>) -> Computer {
    let reg_a: u64 = lines[0][12..].parse().unwrap();
    let reg_b: u64 = lines[1][12..].parse().unwrap();
    let reg_c: u64 = lines[2][12..].parse().unwrap();

    let pointer = 0;
    let program: Vec<u64> = lines[4][9..]
        .split(',')
        .map(|s| s.parse().unwrap())
        .collect();

    return Computer { reg_a, reg_b, reg_c, pointer, program };
}

fn main() {
    let lines = read_lines("day17/input");

    let mut computer = parse_computer(&lines);
    let output = computer.run();
    let answer = output
        .iter()
        .map(|val| val.to_string())
        .collect::<Vec<String>>()
        .join(",");

    println!("{answer}");
}
