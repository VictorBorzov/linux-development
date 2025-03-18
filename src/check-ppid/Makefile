all: exe deploy

exe: main.c
	gcc main.c -O0 -g3 -ggdb -fPIC -Wall -o main

deploy: main.c
	cp main.c solution.c

clean:
	- rm main solution.c 2>/dev/null
