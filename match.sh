


SHOW_LINE="-n"
#set -x

SEARCH_FILE="/home/zodiac1111/tmp/条件编译测试/1.c"
function main {
	SERCH_STRING="int defined_d;"
	SERCH_STRING="$@"
	# 先把之前的语句获得
	#todo=$(grep ${SHOW_LINE} --color=auto -E "(#.*)|(.*${SERCH_STRING}.*)" \
	#	-o "${SEARCH_FILE}" \
	#	| grep -m1 --color=auto -B9999999 "${SERCH_STRING}")
	#echo "todo=${todo}"
	# 以下需要转义15个 \ [ ] ( ) { } + ^ ? $ | / * .
	SERCH_STRING_R=$(echo "${SERCH_STRING}" \
	| sed -e 's/\\/\\\\/g'	\
	| sed -e 's/\[/\\[/g'	\
	| sed -e 's/\]/\\]/g'	\
	| sed -e 's/(/\\(/g'	\
	| sed -e 's/)/\\)/g'	\
	| sed -e 's/{/\\{/g'	\
	| sed -e 's/}/\\}/g'	\
	| sed -e 's/+/\\+/g'	\
	| sed -e 's/\^/\\\^/g'	\
	| sed -e 's/\?/\\\?/g'	\
	| sed -e 's/\//\\\//g'	\
	| sed -e 's/\*/\\\*/g'	\
	| sed -e 's/\./\\\./g'	\
	| sed -e 's/\$/\\\$/g'	\
	| sed -e 's/|/\\|/g'	\
	)
	#echo -en "Regex:	${CL_GREEN}"
	#echo -n  "${SERCH_STRING_R}"
	#echo -en "${CL_END}"
	todo=$(grep ${SHOW_LINE} --color=auto -E "(#.*)|(.*${SERCH_STRING_R}.*)" -o "${SEARCH_FILE}" | grep -m1 --color=always -B9999999 -E "${SERCH_STRING_R}")
	#exit
	if_index=0;
	else_index=0;
	end_index=0;

	level=-1; # 层次,指示if语句的深度
	#echo -e "todo ${CL_YELLOW}${todo}${CL_END}"
	need_to_print=0;
	out_array=();
	else_qty=();
	# 3个栈. 开始 中间 结束

	echo -e "${CL_GREEN}***************************** Preprocessing *****************************${CL_END}"
	#echo -en "${CL_PURP}"
	while read LINE ; do
		#echo -e "check ${CL_GREEN}${LINE}${CL_END}"
		# if语句开始
		echo "${LINE}" | grep -q -E "(#\s*if.*$)|(#\s*ifdef.*$)|(#\s*ifndef.*$)"
		if [ $? -eq 0 ] ; then
			if_index=$((if_index + 1))
			# 一层if 深度+1
			level=$((level + 1))
			out_array[${need_to_print}]="$(printf_new2 ${level})${LINE}"
			need_to_print=$((need_to_print + 1))
			#printf_new "_" ${level}
			printf_new2 ${level}
			echo "${LINE}"
			continue;
		fi

		# 中间语句
		echo "${LINE}" | grep -q -E "(#\s*else.*$)|(#\s*elif.*$)"
		if [ $? -eq 0 ] ; then
			else_index=$((else_index + 1))
			else_qty[${level}]=$((else_qty[${level}] + 1))
			out_array[${need_to_print}]="$(printf_new2 ${level})${LINE}"
			need_to_print=$((need_to_print + 1))
			#echo "E"$LINE
			# else 深度不增加
			#printf_new "_" ${level}
			printf_new2 ${level}
			echo "${LINE}"
			continue;
		fi

		# 结束语句
		echo "${LINE}" | grep -q -E "(#\s*endif.*$)"
		if [ $? -eq 0 ] ; then
			end_index=$((end_index + 1))
			#echo "M"$LINE
			#printf_new "_" ${level}
			printf_new2 ${level}
			echo "$(printf_new2 ${level})${LINE}"
			need_to_print=$((need_to_print - 1)) # if 删除
			need_to_print=$((need_to_print - else_qty[${level}])) # 如果有,else的删除
			else_qty[${level}]=0; # 重置此层打印数量
			# 一次end 深度-1
			level=$((level - 1))
			continue;
		fi
		# 搜索的语句,一定会在最后输出
		echo "${LINE}" | grep -q -E ".*${SERCH_STRING_R}.*"
		if [ $? -eq 0 ] ; then
			# 控制c语句要不要缩进
			#out_array[${need_to_print}]="${LINE}"
			out_array[${need_to_print}]="$(printf_new2 ${level})${LINE}"
			need_to_print=$((need_to_print + 1))
			#printf_new "_" ${level}
			#printf_new2 ${level}
			echo "${LINE}"
			continue;
		fi
	done <<< "$(echo "${todo}")"

	#echo -en "${CL_END}"
###### for debug  ####
#	echo "if_index=$if_index"
#	echo "else_index=$else_index"
#	echo "end_index=$end_index"
#	echo "need_to_print=$need_to_print"


	echo -e "${CL_GREEN}***************************** output start *****************************${CL_END}"
	#echo ${out_array[@]}
	echo -en "${CL_PURP}"
	printf '%s\n' "${out_array[@]:0:${need_to_print}}"
	echo -en "${CL_END}"
	echo -e "${CL_GREEN}***************************** output end *****************************${CL_END}"
}

printf_new2() {
 num=$1
 for((i=1;i<=${num};i++));do
	echo -n "   ";
 done
}

printf_new() {
 str="_"
 num=$2
 v=$(printf "%-${num}s" "${str}")
 echo -n "${v// /${str}}"
}

# tty color define
CL_RED="\033[31m"
CL_YELLOW="\033[33m"
CL_GREEN="\033[32m"
CL_PURP="\033[35m"
CL_END="\033[0m"
## start script
main $@
