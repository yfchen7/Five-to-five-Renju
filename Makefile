src=$(wildcard *.c)  
obj=$(patsubst %.c, %.o, $(src))
CFLAGS= -O3
CC=gcc
tar=renju

$(tar): $(obj) 
	$(CC) -o $(tar) $(obj) 
%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o 

.PHONY: clean  
clean:  
	rm -f renju $(obj)
