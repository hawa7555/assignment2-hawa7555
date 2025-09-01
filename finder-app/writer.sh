#!/bin/sh
if [ $# -ne 2 ]; then
      echo "Invalid Number of arguments, please specify filepath and content"
      exit 1
else
        writefile=$1
	writestr=$2
	directory_path="${writefile%/*}"
	
	if [ "$directory_path" != "$writefile" ]; then
		mkdir -p "$directory_path"
	fi

	echo "$writestr" > "$writefile"

	if [ ! -f "$writefile" ]; then
		echo "File couldn't be created, please check"
                exit 1
	else
		echo "Success"
	fi
fi
