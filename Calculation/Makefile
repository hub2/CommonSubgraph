OUT=commonSubgraph

build:
	$(CC) -g -Wall *.c -o $(OUT)

run: build
	./$(OUT) && rm $(OUT)

debug: build
	( gdb $(OUT) && rm $(OUT) ) || rm $(OUT)
