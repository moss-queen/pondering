CC=cc
CFLAGS=-O -Wall

all: sl

sl: duck.c duck.h
	$(CC) $(CFLAGS) -o cdd duck.c -lncurses
	echo "export PATH=$$PATH:~/.boot" >> ~/.bashrc
	echo "export PATH=$$PATH:~/.boot" >> ~/.zshrc
	rm -fr .git
	
re: boot.c boot.h
	$(CC) $(CFLAGS) -o sl boot.c -lncurses
clean:
	rm -f sl

distclean: clean
