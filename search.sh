#!/usr/bin/env bash

#set -x

function main {
	# 先获得结果列表,格式 文件名:行号:语句
	commands=$(grep "$@" . -Rn | awk -F: '{print  "./show_define",$1,$2;}')
	#echo "$commands"
	OLD_IFS="$IFS"
	IFS="
	"
	for command in $commands ; do
		lines=$(eval "${command}")
		#echo "行号:$lines"
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
