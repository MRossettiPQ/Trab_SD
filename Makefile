HEADERS = bibliotecas.h cores.h
SERVER_OBJECTS = bibliotecas.o cores.o
CLIENT_OBJECTS = bibliotecas.o cores.o

default: main clean

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

main: $(SERVER_OBJECTS) $(CLIENT_OBJECTS)
	gcc $(SERVER_OBJECTS) -o server
	gcc $(CLIENT_OBJECTS) -o client

clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS)
