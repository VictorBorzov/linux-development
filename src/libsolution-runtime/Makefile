all: exe lib

exe: solution.c
	gcc -o solution -fPIC -Wall ./solution.c

lib: solution.c
	gcc -shared solution.c -fPIC -o libsolution.so

clean:
	- rm libsolution.so solution 2>/dev/null

