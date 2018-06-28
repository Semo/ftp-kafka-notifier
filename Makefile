CC=g++
CFLAGS=-O0
LDFLAGS=-lcrypto

.PHONY: clean

main: 	main.cpp
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -rf *.o
	rm -rf main
