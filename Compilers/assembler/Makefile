all: venison compile

remake: all run outputs

# Run bison on the ypp file
venison:
	bison \
	src/main.ypp \
	-o src/main.cpp

# Compile into an executable
compile:
	g++ \
	src/*.cpp \
	-std=c++11 \
	-Iinclude \
	-g -o testing

# Run the program on all of the input files
inputs:
	for i in 1 2 3 4 5 6 7 8 9 10 ; do \
		echo "case $$i" ; \
		cat ./inputs/$$i*.myl ; \
	done

run:
	for i in 1 2 3 4 5 6 7 8 9 10 ; do \
		./testing ./inputs/$$i*.myl > ./asm/$$i.asm; \
	done

outputs:
	for i in 1 2 3 4 5 6 7 8 9 10 ; do \
		echo "case $$i" ; \
		cat ./asm/$$i.asm ; \
	done

clean:
	rm -f ./testing ./src/main.cpp

.PHONY: clean
