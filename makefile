target: main.c orderbook.c
	gcc -o orderbook main.c orderbook.c 
clean:
	rm -f orderbook
