all:show_define
show_define:
	gcc show_define.c -o show_define -Wall -g

clean:
	rm -f createtag printnode

.PHONY : all createtag printnode

