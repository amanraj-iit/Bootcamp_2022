CC = g++
CFLAGS=-I.
DEPS = functions.h
TARGETS = output

output: main.o factorial.o hello.o
	$(CC) main.o factorial.o hello.o -o output

main.o: main.cpp $(DEPS)
	$(CC) -c $@ $< $(CFLAGS)

factorial.o: factorial.cpp $(DEPS)
	$(CC) -c $@ $< $(CFLAGS)

hello.o: hello.cpp $(DEPS)
	$(CC) -c $@ $< $(CFLAGS)

clean:
	rm *.o $(TARGETS)
