.PHONY: all pre run

all: main.exe

pre: all
	@./main.exe -p

run: all
	@./main.exe

CC := gcc
FLAGS := -I h -O0 -g
OFILES := o/preproc.o o/table.o o/main.o

main.exe: $(OFILES)
	@gcc $(FLAGS) $(OFILES) -o main.exe

o/preproc.o: src/preproc.c
	@$(CC) $(FLAGS) $< -c -o $@

o/table.o: src/table.c
	@$(CC) $(FLAGS) $< -c -o $@

o/main.o: src/main.c
	@$(CC) $(FLAGS) $< -c -o $@