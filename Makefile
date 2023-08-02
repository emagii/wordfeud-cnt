CC = gcc


all:	wordfeud-cnt run

run:    document.txt
	cat document.txt | ./wordfeud-cnt 

wordfeud-cnt:	wordfeud-cnt.c
	$(CC) -g -o $@ $<

clean:
	rm -fr wordfeud-cnt *.o
