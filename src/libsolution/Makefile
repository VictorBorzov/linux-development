all: lib

lib: solution.c
	gcc -shared solution.c -fPIC -o libsolution.so

clean:
	- rm libsolution.so 2>/dev/null
