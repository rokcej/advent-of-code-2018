# Script for managing Advent of Code solutions
# Run the script with parameter -h to display more info
# To add support for new languages, modify the TEMPLATES and COMMANDS variables

import argparse
from pathlib import Path
import requests
import subprocess
import time

# Code templates
TEMPLATES = {
	# C++
	"cpp": lambda year, day, part:
		f"#include <iostream>\n\n" \
		f"int main() {{\n" \
		f"	// TODO\n\n" \
		f"	return 0;\n" \
		f"}}\n",
	# C#
	"cs": lambda year, day, part:
		f"using System;\n" \
		f"using System.IO;\n\n" \
		f"namespace Day{day:02} {{\n\n" \
		f"	class Part{part} {{\n\n" \
		f"		public static void Main(string[] args) {{\n" \
		f"			// TODO \n" \
		f"		}}\n\n" \
		f"	}}\n\n" \
		f"}}\n",
	# Python
	"py": lambda year, day, part: "# TODO\n"
}

# Commands for compiling and executing solutions
COMMANDS = {
	# C++
	"cpp": (
		lambda part: ["g++", "-std=c++17", "-O2", "-o", f"part{part}", f"part{part}.cpp"],
		lambda part: [f"./part{part}"]
	),
	# C#
	"cs": (
		lambda part: ["mcs", f"-out:part{part}", f"part{part}.cs"], # Linux only
		lambda part: [f"./part{part}"]
	),
	# Python
	"py": (
		None, # No compilation
		lambda part: ["python3", f"part{part}.py"] # Linux only
	)
}


def setup(language, year, day, session):
	dir_path = Path(f"{year}/day{day:02}")

	# Create directory
	print("Creating directory:     ", end="")
	if dir_path.is_dir():
		print("Already exists")
	else:
		dir_path.mkdir(parents=True)
		print("Done")

	# Create parts 1 and 2
	for part in [1, 2]:
		print(f"Creating part {part}:        ", end="")
		file_path = dir_path / f"part{part}.{language}"
		if file_path.is_file():
			print("Already exists")
		else:
			with file_path.open("w") as f:
				f.write(TEMPLATES[language](year, day, part))
			print("Done")

	# Download input
	print("Downloading input:      ", end="")
	input_path = dir_path / "input"
	if input_path.is_file():
		print("Already exists")
	else:
		response = requests.get(url=f"https://adventofcode.com/{year}/day/{day}/input", cookies={"session": session})
		if response.status_code == 200:
			with input_path.open("w") as f:
				f.write(response.text)
			print("Done")
		else:
			print(f"Error {response.status_code}: {response.reason}")


def run(language, year, day, part):
	print(f"================")
	print(f"==== Part {part} ====")
	print(f"================\n")

	dir_path = Path(f"{year}/day{day:02}")
	get_compile_args, get_execute_args = COMMANDS[language]

	# Compile
	if get_compile_args is not None:
		compile = subprocess.run(get_compile_args(part), cwd=dir_path)
		if compile.returncode != 0:
			print()
			print(f"Error: Unable to compile {dir_path}/part{part}.{language}")
			print()
			return

	# Execute
	with open(dir_path / "input", "r") as f:
		time_start = time.time()
		execute = subprocess.run(get_execute_args(part), stdin=f.fileno(), cwd=dir_path, text=True)
		duration = time.time() - time_start	
	print()
	print(f"Time: {duration:.3f}s")
	if execute.returncode != 0:
		print()
		print(f"Error: Exited with return code {execute.returncode}")
	print()


def main():
	parser = argparse.ArgumentParser(description="Advent of Code solution manager")
	parser.add_argument("-l", required=True, type=str, choices=["cpp", "cs", "py"], help="select language")
	parser.add_argument("-y", required=True, type=int, choices=range(2015, 2023), metavar="{2015,...}", help="select year")
	parser.add_argument("-d", required=True, type=int, choices=range(1, 26), metavar="{1,...,25}", help="select day")
	parser.add_argument("command", type=str, choices=["setup", "run"], help="setup directory or run solution(s)")
	parser.add_argument("part", type=int, choices=[1, 2], nargs="?", help="(optional) choose solution part")

	args = parser.parse_args()
	match args.command:
		case "setup":
			if not Path(".session").is_file():
				print("Error: Please create a \".session\" file containing your login session cookie")
				return
			with open(".session", "r") as f:
				session = f.read().strip()
			setup(args.l, args.y, args.d, session)
		case "run":
			if args.part is None:	
				run(args.l, args.y, args.d, 1)
				run(args.l, args.y, args.d, 2)
			else:
				run(args.l, args.y, args.d, args.part)


if __name__ == "__main__":
	main()
