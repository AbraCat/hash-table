.PHONY: all pre run clean valgr rm-valgr

all: main.exe

pre: all
	@./main.exe -p

run: all
	@./main.exe

clean:
	@rm -rf o
	@mkdir o
	@rm main.exe

valgr:
	@valgrind --tool=callgrind --toggle-collect=test_tbl ./main.exe

rm-valgr:
	@rm callgrind*

CC := gcc
FLAGS := -I h -g -O2 -msha
OFILES := o/preproc.o o/table.o o/main.o

main.exe: $(OFILES)
	@gcc $(FLAGS) $(OFILES) -o main.exe

o/preproc.o: src/preproc.c
	@$(CC) $(FLAGS) $< -c -o $@

o/table.o: src/table.c
	@$(CC) $(FLAGS) $< -c -o $@

o/main.o: src/main.c
	@$(CC) $(FLAGS) $< -c -o $@