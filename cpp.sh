#!/bin/bash

# Default values

session="" 		# Login session cookie
year="2020" 	# Puzzle year
day="" 			# Puzzle day


# Functions

function help {
	echo -e "Usage:"
	echo -e "  $(basename $0) <options> <command>"
	echo -e ""
	echo -e "Options:"
	echo -e "  -y <2015..> \t\t Select year"
	echo -e "  -d <1..25> \t\t Select day"
	echo -e ""
	echo -e "Commands:"
	echo -e "  setup \t\t Setup directory and download input"
	echo -e "  run [1, 2] \t\t Compile and run solutions"
}

function run {
	local year="$1"
	local day="$2"
	local part="$3"

	local dir="$(printf "$year/day%02d" $day)"
	local file="part$part"

	echo "================"
	echo "==== Part $part ===="
	echo "================"
	echo ""

	if $(g++ "$dir/$file.cpp" -o "$dir/$file"); then
		"$dir/$file" < "$dir/input"
	else
		echo "Error compiling $dir/$file.cpp"
	fi

	echo ""
}

function setup {
	local year="$1"
	local day="$2"
	local session="$3"

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

	for i in 1 2; do
		echo -n -e "Creating part $i: \t"
		if [ ! -f "$dir/part$i.cpp" ]; then
			if ! $(touch "$dir/part$i.cpp"); then
				echo "Error: Unable to create $dir/part$i.cpp"
				exit 1
			fi
			echo "Done"
		else
			echo "Already exists"
		fi
	done

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

	echo "Setup for year $year, day $day complete"
}


# Script

# Read session cookie
if [ -z "$session"]; then
	if [ ! -f "./.session" ]; then
		echo "Error: Please create a .session file containing your login session cookie (no newline)"
		exit 1
	fi
	session="$(<./.session)"
fi

# Parse options
while getopts ":y:d:" opt; do
	case "$opt" in
	y)
		year="$OPTARG"
		if ! [ "$year" -ge 2015 ]; then
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
		setup $year $day $session
		;;
	run)
		if [ $# -lt 1 ]; then
			run $year $day 1
			run $year $day 2
		else
			part=$1
			shift
			if ! ( [ "$part" -eq 1 ] || [ "$part" -eq 2 ] ); then
				echo "Invalid $subcommand argument: Wrong part number $part" >&2
			fi
			run $year $day $part
		fi
		;;
	*)
		echo "Invalid command"
		help
		exit 1
		;;
esac
