#!/usr/bin/env bash

lab_number=""
read -p "Enter the lab number: " lab_number

lab_dir="$HOME/git-repos/ankara-university-data-structures/blm2067/lab$lab_number"

if [ ! -d "$lab_dir" ]; then
    echo "Lab directory is not found!"
    exit 1
fi

cd "$lab_dir"

file_name="lab$lab_number.c"

# Default file name is studentnum.c
student_number=""
read -p "Enter the student number: " student_number

if [ ! -z "$student_number" ]; then
    file_name="$student_number.c"
else
    file_name="lab$lab_number.c"
    unset student_number
fi

if [ ! -f "$file_name" ]; then
    echo "File is not found!"
    exit 1
fi

gcc "$file_name"

# You should be careful about input/output directory
io_dir="$(pwd)/IO"

if [ ! -d "$io_dir" ]; then
    echo "IO directory is not found!"
    exit 1
fi

input_count=$(ls "$io_dir" | grep -c "input")

rm -i -f "$io_dir/myout*"

format=""

if ls "$io_dir" | grep -q "\.txt$"; then
    format=".txt"
fi

for ((i = 1; i <= input_count; i++)); do
    ./a.out <"$io_dir/input$i$format" >"$io_dir/myout$i$format"
done

for ((i = 1; i <= input_count; i++)); do
    diff -w "$io_dir/myout$i$format" "$io_dir/output$i$format"
done

echo "Done!"
