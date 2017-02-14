CC = g++
CFLAGS = -std=c++14 -I..
SRCS = driver.cpp

driver.o: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o driver.o

clean:
	Del "C:\Users\Ethan Rivers\Documents\linked-list-single-ethanatortx\driver.o"