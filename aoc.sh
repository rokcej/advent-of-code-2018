#!/bin/bash

# Script for managing Advent of Code solutions
#   run - Compile and run solutions
#   setup - Generate solution template and download input

# Default values

language="python"	# Programming language
year="2022"			# Puzzle year
day=""				# Puzzle day

# The login session cookie is required for downloading puzzle inputs
# This value should not be hard-coded in public repositories, as it allows anyone to access your account
# In order to safely store it, create a '.session' file and the contents will be used to set the session variable (remove any newline characters)
session=""			# Login session cookie

# Functions

function help {
	echo -e "Usage:"
	echo -e "  $(basename $0) <options> <command>"
	echo -e ""
	echo -e "Options:"
	echo -e "  -l [cpp, python]        Select language"
	echo -e "  -y <2015..>             Select year"
	echo -e "  -d <1..25>              Select day"
	echo -e ""
	echo -e "Commands:"
	echo -e "  setup                   Setup directory and download input"
	echo -e "  run [1, 2]              Compile and run solutions"
}

function run {
	local language="$1"
	local year="$2"
	local day="$3"
	local part="$4"

	local dir="$(printf "$year/day%02d" $day)"
	local file="part$part"

	echo "================"
	echo "==== Part $part ===="
	echo "================"
	echo ""

	case "$language" in
		cpp|c++)
			if $(g++ -O2 -o "$dir/$file" "$dir/$file.cpp"); then
				(cd "$dir" ; time "./$file" < "input")
			else
				echo "Error compiling $dir/$file.cpp"
			fi
			;;
		python|py)
			(cd "$dir" ; time python3 "$file.py" < "input")
			;;
		*)
			echo "Error: Unsupported language $language"
			help
			exit 1
			;;
	esac

	echo ""
}

function setup {
	local language="$1"
	local year="$2"
	local day="$3"
	local session="$4"

	# Select file extension and content based on language
	local extension=""
	local content=""
	case "$language" in
		cpp|c++)
			extension="cpp"
			content="#include <iostream>\n\nint main() {\n\t\n\n\treturn 0;\n}\n"
			;;
		python|py)
			extension="py"
			content="\n"
			;;
		*)
			echo "Error: Unsupported language $language"
			help
			exit 1
			;;
	esac

	# Create directory
	local dir="$(printf "$year/day%02d" $day)"
	echo -n -e "Creating directory: \t"
	if [ ! -d "$dir" ]; then
		if ! $(mkdir -p "$dir"); then
			echo "Error: Unable to create $dir"
			exit 1
		fi
		echo "Done"
	else
		echo "Already exists"
	fi

	# Create code file
	for i in 1 2; do
		echo -n -e "Creating part $i: \t"
		if [ ! -f "$dir/part$i.$extension" ]; then
			if ! $(touch "$dir/part$i.$extension"); then
				echo "Error: Unable to create $dir/part$i.$extension"
				exit 1
			fi
			echo -e -n "$content" >> "$dir/part$i.$extension"
			echo "Done"
		else
			echo "Already exists"
		fi
	done

	# Download input
	echo -n -e "Downloading input: \t"
	if [ ! -f "$dir/input" ]; then
		if ! $(curl https://adventofcode.com/$year/day/$day/input -b "session=$session" -o "$dir/input" -s); then
			echo "Error: Unable to download $dir/input"
			exit 1
		fi
		echo "Done"
	else
		echo "Already exists"
	fi

	echo "Setup for day $day of year $year complete"
}


# Main script

# Print usage
if [ $# -lt 1 ]; then
	help
	exit 1
fi

# Parse options
while getopts ":l:y:d:" opt; do
	case "$opt" in
	l)
		language="$OPTARG"
		;;
	y)
		year="$OPTARG"
		if ! ( [ "$year" -ge 2015 ] && [ "$year" -le 2099 ] ); then
			echo "Invalid -$opt argument: Wrong year number $year" >&2
			help
			exit 1
		fi
		;;
	d)
		day="$OPTARG"
		if ! ( [ "$day" -ge 1 ] && [ "$day" -le 25 ] ); then
			echo "Invalid -$opt argument: Wrong day number $day" >&2
			help
			exit 1
		fi
		;;
	\?)
		echo "Invalid option: -$OPTARG" >&2
		help
		exit 1
		;;
	:)
		echo "Missing argument: -$OPTARG requires an argument" >&2
		help
		exit 1
		;;
	esac
done
shift $((OPTIND -1))

if [ -z "$language" ]; then
	echo "Missing option: -l is required" >&2
	help
	exit 1
fi
if [ -z "$year" ]; then
	echo "Missing option: -y is required" >&2
	help
	exit 1
fi
if [ -z "$day" ]; then
	echo "Missing option: -d is required" >&2
	help
	exit 1
fi

# Parse commands
subcommand="$1"
shift
case "$subcommand" in
	setup)
		# Read session cookie
		if [ -z "$session"]; then
			if [ ! -f "./.session" ]; then
				echo "Error: Please create a .session file containing only your login session cookie (no newline characters)"
				exit 1
			fi
			session="$(<./.session)"
		fi
		setup $language $year $day $session
		;;
	run)
		if [ $# -lt 1 ]; then
			run $language $year $day 1
			run $language $year $day 2
		else
			part=$1
			shift
			if ! ( [ "$part" -eq 1 ] || [ "$part" -eq 2 ] ); then
				echo "Invalid $subcommand argument: Wrong part number $part" >&2
				exit 1
			fi
			run $language $year $day $part
		fi
		;;
	*)
		echo "Error: Invalid command"
		help
		exit 1
		;;
esac
