all: exe

exe: main.c
	gcc main.c -o0 -g3 -fPIC -Wall -o main

deploy: main.c
	cp main.c solution.c

clean:
	- rm main solution.c 2>/dev/null
