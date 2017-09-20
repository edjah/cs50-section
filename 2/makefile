brute1: brute.c brute.h
	gcc -std=c11 -Ofast brute.c brute.h -o brute -lcrypt

brute2: brute.c brute.h
	gcc -std=c11 -Ofast brute.c brute.h -o brute -lcrypt -lm -ggdb


crack1: crack.c brute.h
	gcc -std=c11 -Ofast crack.c brute.h -o crack -lcrypt

crack2: crack.c brute2.h
	gcc -std=c11 -Ofast crack.c brute2.h -o crack -lcrypt

%: %.c
	gcc -std=c11 -Ofast -lm $< -o $@ -lcs50 -lcrypt -ggdb
