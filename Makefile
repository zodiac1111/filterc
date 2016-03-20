all:show_define
show_define:show_define.c
	gcc show_define.c -o show_define -Wall -g

clean:
	rm -f  show_define


.PHONY : all  show_define

