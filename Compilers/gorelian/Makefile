all:
	g++ src/main.cpp \
	src/new_city.cpp \
	-I./include \
	-std=c++11 -g -o testing

run:
	./testing < input.txt

valgrind:
	valgrind ./testing < input.txt

clean:
	rm -f testing

.PHONY: clean
