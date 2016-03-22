# 下载

	git clone --depth 1 https://github.com/zodiac1111/filterc.git
	cd filterc

# 编译

	make

# 使用

	./search.sh "var_b"

运行效果如下:

	$ ./search.sh "var_b"
	=== 1 : ./test/tc1.c ===
	6	: #if A_MODEL
	7	: 	var_b=3
	=== 2 : ./test/tc1.h ===
	1	: #ifndef _TC1_H
	7	: 	int var_b;

# 注意

会在运行的目录下生成tags的文件夹,用于保存生成的预处理tags.其结构与源代码一致.

只搜索c和h文件.只能搜索c语言的token.不能排除注释.基于本文过滤而不是预处理语言过滤.

# 目的

过滤c语言语句的预处理条件.

在用例 tc1 中,变量声明和使用的预处理不一致.

这个工具是为了发现这种问题.

可以发现 `var_b` 在源文件和头文件中预处理不一致,

如果没有定义 `A_MODEL` 宏那么编译就会出错.

网上搜下预处理等关键字都是讲其他内容的,所以就在业余时间弄了这个一个东西.

如果有其他工具可以检查这种问题的话烦请告知.


# 其他

MIT License
测试用例使用他们自己的许可
