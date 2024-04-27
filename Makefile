CFLAGS = -Wall -Werror -std=c99
email.exe:
	gcc $(CFLAGS) -o email.exe email.c

test: email.exe
	.\email.exe

clean:
	rm -rf *.exe