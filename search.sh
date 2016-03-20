#!/usr/bin/env bash

#set -x

# 如果不想在结果处显示行号,这里改为0即可
PRINT_LINE_NO=1

function main {
	OLD_IFS="$IFS"
	IFS="
	"
	# 先获得结果列表,格式 文件名:行号:语句
	commands=$(grep "$@" . -Rn --include=*.h --include=*.c | awk -F: '{print  "./show_define",$1,$2;}')
	# echo "$commands"
	i=0;
	total=${#commands[@]}
	echo "total=$total"
	#exit
	for command in $commands ; do
		i=$(expr $i + 1)
		local exe=$(echo ${command}|awk '{printf $1}')
		local sourcefile=$(echo ${command}|awk '{printf $2}')
		local searchline=$(echo ${command}|awk '{printf $3}')
		local lines=$(eval "${command}")
		echo -e "${CL_GREEN}=== $i : ${sourcefile} ===${CL_END}"
		OLD_IFS="$IFS"
		IFS=",
		"
		for line in $lines ; do
			#echo "line=$line"
			if [ ${PRINT_LINE_NO} -eq 1 ] ;then
				echo -en "${line}\t: "
			fi
			sed -n "${line}p" "${sourcefile}"
		done
		if [ ${PRINT_LINE_NO} -eq 1 ] ;then
			echo -en "${CL_RED}${searchline}${CL_END}\t: "
		fi
		sed -n "${searchline}p" "${sourcefile}"| grep --color=always "$@"
		#echo $exe
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
