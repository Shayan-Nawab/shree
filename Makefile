all: main.c shree.c
		gcc -Wall main.c shree.c -o shree
clean:
		rm shree

