%: %.c
	gcc -std=c11 -O1 -lm $< -o $@ -lcs50 -ggdb

clean:
	ls | grep -v "\.\|makefile" | xargs rm -f
