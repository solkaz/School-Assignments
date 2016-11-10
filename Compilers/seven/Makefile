# 2-in-1 command to completely compile project
all: venison compile

# Run bison on the ypp file
venison:
	bison -L c++ \
	src/main.ypp

# Compile into an executable
compile:
	g++ main.tab.cpp \
	src/*.cpp \
	-std=c++11 \
	-I./include \
	-g -o testing 

# Run the program on all of the input files
run:
	./testing p3test1.myl && echo "" &&\
	./testing p3test2.myl && echo "" &&\
	./testing p3test3.myl && echo ""

# Output the contents of the expected output files
expected:
	cat p3test1.out && echo "" &&\
	cat p3test2.out && echo "" &&\
	cat p3test3.out && echo ""

