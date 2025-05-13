.PHONY: all pre run hash msr clean valgr rm-valgr

all: main.exe

pre: all
	@./main.exe -p

run: all
	@./main.exe

msr: all
	@./main.exe -m

hash: all
	@./main.exe -h

clean:
	@rm -rf o
	@mkdir o
	@rm main.exe

valgr:
	@valgrind --tool=callgrind --toggle-collect=test_tbl ./main.exe

rm-valgr:
	@rm callgrind*

CC := gcc
FLAGS := -fno-pie -no-pie -lm -I h -O3 -mavx2
ASM_FLAGS := -f elf64 -F dwarf
OFILES := o/preproc.o o/table.o o/test.o o/main.o o/utils.o o/list.o o/unrolled_list.o o/my_lst_find.o o/my_unr_find.o

main.exe: $(OFILES)
	@$(CC) $(FLAGS) $(OFILES) -lm -o main.exe

o/preproc.o: src/preproc.c
	@$(CC) $(FLAGS) $< -c -o $@

o/table.o: src/table.c
	@$(CC) $(FLAGS) $< -c -o $@

o/test.o: src/test.c
	@$(CC) $(FLAGS) $< -c -o $@

o/main.o: src/main.c
	@$(CC) $(FLAGS) $< -c -o $@

o/utils.o: src/utils.c
	@$(CC) $(FLAGS) $< -c -o $@

o/list.o: src/list.c
	@$(CC) $(FLAGS) $< -c -o $@

o/unrolled_list.o: src/unrolled_list.c
	@$(CC) $(FLAGS) $< -c -o $@

o/my_lst_find.o: src/my_lst_find.asm
	@nasm $(ASM_FLAGS) $< -o $@

o/my_unr_find.o: src/my_unr_find.asm
	@nasm $(ASM_FLAGS) $< -o $@