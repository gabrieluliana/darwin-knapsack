flags = -lglut -lGLU -lGL -Wall -lm

all:
	gcc main.c darwin.c -o main $(flags)
run:
	./main
clean:
	rm main