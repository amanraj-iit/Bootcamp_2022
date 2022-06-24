
CC = g++ -Wno-write-strings
SERVER_FILE = simple_server.cpp
HTTP_SERVER_FILE = http_server.cpp
DEPS = http_server.hh

all:server


server: $(SERVER_FILE) $(HTTP_SERVER_FILE) $(DEPS)
	$(CC) -pthread $(SERVER_FILE) $(HTTP_SERVER_FILE) -o server  

clean:
	rm -f server
