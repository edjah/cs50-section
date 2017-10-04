sort: sort.c sorts.h
	gcc -std=c11 -Ofast sort.c sorts.h -o sort -ggdb

find_seed: find_seed.c
	gcc -std=c11 -O1 find_seed.c -o find_seed -ggdb

memory: memory.c
	gcc -std=c11 -O1 memory.c -o memory -ggdb

rand: rand.c
	gcc -std=c11 -O1 rand.c -o rand -ggdb

clean:
	rm -f find_seed rand sort memory

%: %.c
	gcc -std=c11 -O1 -lm $< -o $@ -lcs50 -ggdb
