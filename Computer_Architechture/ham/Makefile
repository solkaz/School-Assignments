all:
	g++ -std=c++11 \
	src/*.cpp \
	-Iinclude \
	-g -o testing

run:
	./testing < Data2.txt

print:
	make -s run > output.txt

clean:
	rm -f ./testing

.PHONY: clean
