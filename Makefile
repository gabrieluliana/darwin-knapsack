

all:
	gcc main.c darwin.c -o main
run:
	./main
clean:
	rm main