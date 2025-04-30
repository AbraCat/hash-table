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
FLAGS := -fno-pie -no-pie -I h -g -O2 -march=native
OFILES := o/preproc.o o/table.o o/test.o o/main.o o/my_lst_find.o

main.exe: $(OFILES)
	@gcc $(FLAGS) $(OFILES) -o main.exe

o/preproc.o: src/preproc.c
	@$(CC) $(FLAGS) $< -c -o $@

o/table.o: src/table.c
	@$(CC) $(FLAGS) $< -c -o $@

o/test.o: src/test.c
	@$(CC) $(FLAGS) $< -c -o $@

o/main.o: src/main.c
	@$(CC) $(FLAGS) $< -c -o $@

o/my_lst_find.o: src/my_lst_find.asm
	@nasm -f elf64 -F dwarf -g $< -o $@