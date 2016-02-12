CC=g++
FLAGS=-Wall -std=c++14
OBJECTS=$(subst cpp,o,$(wildcard *.cpp))

main : $(OBJECTS)
	$(CC) $(FLAGS) -o $@ $^

%.o : %.cpp %.h
	$(CC) -c $<

clean :
	rm -f *~ *.o main