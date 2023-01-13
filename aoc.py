# Script for managing Advent of Code solutions
# Run the script with parameter -h to display more info
# To add support for new languages, modify the get_template and get_commands functions

import argparse
from pathlib import Path
import requests
import subprocess
import time
import textwrap

# Solution code templates
def get_template(language, year, day, part):
	match language:
		case "cpp":
			return textwrap.dedent(f"""\
				#include <iostream>

				int main() {{
					// TODO

					return 0;
				}}
				""")

		case "cs":
			return textwrap.dedent(f"""\
				namespace Day{day:02};
					
				class Part{part} {{
					
					public static void Run() {{
						// TODO
					}}

				}}
				""")
				
		case "py":
			return "# TODO\n"

	assert False, f"Template not found for language {language}"

# Commands for compiling and executing solutions
def get_commands(language, year, day, part):
	match language:
		case "cpp":
			return {
				"dir":     f"./{year}/day{day:02}",
				"compile": ["g++", "-std=c++17", "-O2", "-o", f"part{part}", f"part{part}.cpp"],
				"execute": [f"./part{part}"]
			}
		case "cs":
			return {
				"dir":     f"./{year}",
				"compile": ["dotnet", "build", "-o", "./bin/build", "--nologo", "-v", "q", "-clp:NoSummary"],
				"execute": ["dotnet", f"./bin/build/{year}.dll", f"{day}", f"{part}"]
			}
		case "py":
			return {
				"dir":     f"./{year}/day{day:02}",
				"compile": None,
				"execute": ["python", f"part{part}.py"]
			}

	assert False, f"Commands not found for language {language}"


# Setup solution template and input
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
				f.write(get_template(language, year, day, part))
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

# Compile and execute solution
def run(language, year, day, part):
	print(f"================")
	print(f"==== Part {part} ====")
	print(f"================\n")

	commands = get_commands(language, year, day, part)

	# Compile
	if commands["compile"] is not None:
		try:
			compile = subprocess.run(commands["compile"], cwd=commands["dir"])
		except FileNotFoundError:
			print(f"Error: Compiler '{commands['compile'][0]}' not found\n")
			return
		if compile.returncode != 0:
			print(f"\nError: Unable to compile '{year}/day{day:02}/part{part}.{language}'\n")
			return

	# Execute
	with open(f"{year}/day{day:02}/input", "r") as f:
		time_start = time.time()
		try:
			execute = subprocess.run(commands["execute"], stdin=f.fileno(), cwd=commands["dir"], text=True)
		except FileNotFoundError:
			print(f"Error: Executable '{commands['execute'][0]}' not found\n")
			return
		duration = time.time() - time_start
	print(f"\nTime: {duration:.3f}s\n")
	if execute.returncode != 0:
		print(f"Error: Exited with return code {execute.returncode}\n")

# Parse command line arguments
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
				print("Error: Please create a '.session' file containing your login session cookie")
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
