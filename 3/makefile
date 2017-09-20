benchmark: benchmark.c bst.c bst.h
	gcc -std=c11 -O1 benchmark.c bst.c -o benchmark -ggdb

find_seed: find_seed.c
	gcc -std=c11 -O1 find_seed.c -o find_seed -ggdb

%: %.c
	gcc -std=c11 -O1 -lm $< -o $@ -lcs50 -ggdb

clean:
	rm benchmark find_seed
