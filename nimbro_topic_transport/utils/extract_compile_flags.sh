#!/bin/bash

set -e

OUTPUT_FILE="$1"
COMPILER="$2"

shift # output file
shift # compiler

declare -a Parameters=("$@")

echo "// AUTOGENERATED FILE" > $OUTPUT_FILE
echo "#ifndef TT_COMPILE_FLAGS_H" >> $OUTPUT_FILE
echo "#define TT_COMPILE_FLAGS_H" >> $OUTPUT_FILE

echo -n "#define TT_COMPILE_FLAGS " >> $OUTPUT_FILE

for ((i=0; i <= ${#Parameters[@]}; i++)) do
	arg="${Parameters[i]}"
	case "$arg" in
		-c*)
			;;
		-o*)
			((i++))
			;;
		-x*)
			((i++))
			;;
		-*)
			arg=$(echo $arg | sed 's/"/\\"/g')
			echo -n ", \"$arg\"" >> $OUTPUT_FILE
			;;
	esac
done

echo "" >> $OUTPUT_FILE
echo "#endif" >> $OUTPUT_FILE

exec $COMPILER "$@"