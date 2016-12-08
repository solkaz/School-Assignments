all: venison compile

remake: all translate outputs

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
		cat ./inputs/$$i\_*.myl ; \
	done

translate:
	for i in 1 2 3 4 5 6 7 8 9 10 ; do \
		rm -f ./asm/$$i.s; \
		cat preamble.s > ./asm/$$i.s; \
		./testing ./inputs/$$i\_*.myl >> ./asm/$$i.s; \
	done

outputs:
	for i in 1 2 3 4 5 6 7 8 9 10 ; do \
		echo "case $$i" ; \
		cat ./asm/$$i.s ; \
	done

compile-output:
	for i in 1 2 3 4 5 6 7 8 9 10 ; do \
		echo "case $$i" ; \
		gcc ./asm/$$i.s -o ./bin/$$i.out ; \
	done
clean:
	rm -f ./testing ./src/main.cpp

.PHONY: clean
