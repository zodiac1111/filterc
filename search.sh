#!/usr/bin/env bash

#set -x

# 如果不想在结果处显示行号,这里改为0即可
PRINT_LINE_NO=1

# 最短检索长度,太长可能搜到太多东西.
MIN_SEARCH_LENGTH=3

function main {
	if [ $# -ne 1 ] ;then
		echo -e "Usage: ./search <string>"
		exit
	fi
	length=${#1}
	if [ $length -lt  $MIN_SEARCH_LENGTH ] ; then
		echo -e "${CL_RED}Search string($1) is too short($length) to search.${CL_END}";
		echo -e "At least ${CL_GREEN}$MIN_SEARCH_LENGTH${CL_END}.";
		exit;
	fi
	# 检查是否属于c语言tonken.目前仅支持c语言token
	# 找到非token字符则提示并禁止继续查找.
	echo "$@" | grep -q -E "[^0-9a-zA-Z_]"
	if [ $? -eq 0 ] ; then
		echo -e "Just support C Language token 0-9a-zA-Z_ (space is not allowed)"
		echo -e "${CL_RED}Abandon search.${CL_END}"
		echo "$@" | grep -E --color=always "[^0-9a-zA-Z_]"
		exit
	fi

	OLD_IFS="$IFS"
	IFS="
	"
	# 先获得结果列表,格式 文件名:行号:语句
	commands=$(grep -w "$1" . -Rn --include=*.h --include=*.c | awk -F: '{print  "./show_define",$1,$2;}')
	# echo "$commands"
	i=0;
	# total=${#commands[@]} 总计数貌似不可用
	# echo "total=$total"
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
			echo -en "${CL_PURP}"
			sed -n "${line}p" "${sourcefile}"
			echo -en "${CL_END}"
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
