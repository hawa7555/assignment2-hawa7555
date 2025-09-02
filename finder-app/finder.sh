#!/bin/sh
if [ $# -ne 2 ]; then
      echo "Invalid Number of arguments, please specify directory and text"
      exit 1
else
	filesdir=$1
	searchstr=$2
	if [ ! -d "$filesdir" ]; then
		echo "Directory not found, please check"
		exit 1
	else
		number_of_lines=$(grep -r "$searchstr" "$filesdir" | wc -l)
		#number_of_match_files=$(grep -r -l "$searchstr" "$filesdir" | wc -l)
    number_of_files=$(find -L "$filesdir" -type f | wc -l)

		echo "The number of files are $number_of_files and the number of matching lines are $number_of_lines"
	fi
fi
