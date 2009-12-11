CC = gcc
CFLAGS = -Wall
SHELL_OBJ = hur-shell.o package.o
CLIENT_OBJ = hur-client.o

shell: $(SHELL_OBJ)
	$(CC) $(CFLAGS) -o hur-shell $(SHELL_OBJ)

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o hur $(CLIENT_OBJ)

clean:
	rm *.o
