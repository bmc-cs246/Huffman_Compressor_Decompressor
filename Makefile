all: huff puff

huff: huff.c huff_tree.c bit.c
	gcc -g huff.c huff_tree.c bit.c -o huff -DDEBUG

puff: puff.c huff_tree.c bit.c
	gcc -g puff.c huff_tree.c bit.c -o puff -DDEBUG

clean:
	rm huff puff

test:
	make huff
	./huff infile.txt outfile.huff

thuff:
	make huff
	./huff infile.txt outfile.huff

tpuff:
	make puff
	./puff outfile.huff puffed.txt

.PHONY: all clean