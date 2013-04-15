all:
	gcc -Wall -Wextra -pedantic -std=c99 main.c  -o p
clean:
	rm main.c
