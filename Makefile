all:createtag printnode

createtag:
	gcc createtag.c -o createtag -Wall -g
printnode:
	gcc printnode.c -o printnode -Wall -g

clean:
	rm -f createtag printnode

.PHONY : all createtag printnode

