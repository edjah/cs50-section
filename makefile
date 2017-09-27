%: %.c
	gcc -std=c11 -O1 -lm $< -o $@ -lcs50 -ggdb
