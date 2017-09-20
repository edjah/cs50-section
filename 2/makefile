crack_dict: crack_dict.c brute.h
	gcc -std=c11 -Ofast crack_dict.c brute.h -o crack -lcrypt

crack_brute: crack_brute.c
	gcc -std=c11 -Ofast crack_brute.c -o crack -lcrypt

%: %.c
	gcc -std=c11 -Ofast -lm $< -o $@ -lcs50 -lcrypt -ggdb
