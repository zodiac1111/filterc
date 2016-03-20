#!/usr/bin/env bash

#set -x

function main {
	# 先获得结果列表,格式 文件名:行号:语句
	commands=$(grep "$@" . -Rn --include=*.h --include=*.c | awk -F: '{print  "./show_define",$1,$2;}')
	echo "$commands"
	OLD_IFS="$IFS"
	IFS="
	"
	for command in $commands ; do
		local exe=$(echo ${command}|awk '{printf $1}')
		local sourcefile=$(echo ${command}|awk '{printf $2}')
		local searchline=$(echo ${command}|awk '{printf $3}')
		local lines=$(eval "${command}")
		echo "在文件:${sourcefile}"
		for line in $lines ; do
			#echo "line=$line"
			sed -n "${line}p" "${sourcefile}"
		done
		sed -n "${searchline}p" "${sourcefile}"
		echo $exe
		#exit
	done
	IFS="$OLD_IFS"
}



# tty color define
CL_RED="\033[31m"
CL_YELLOW="\033[33m"
CL_GREEN="\033[32m"
CL_PURP="\033[35m"
CL_END="\033[0m"


main "$@"
