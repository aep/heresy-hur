CC = gcc
CFLAGS = -Wall
DEBUGOPTS = -O0 -ggdb -g -rdynamic
SHELL_OBJ = hur-shell.o package.o config.o
CLIENT_OBJ = hur-client.o

shell: $(SHELL_OBJ)
	$(CC) $(CFLAGS) $(DEBUGOPTS) -o hur-shell $(SHELL_OBJ)

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(DEBUGOPTS) -o hur $(CLIENT_OBJ)

clean:
	rm *.o
