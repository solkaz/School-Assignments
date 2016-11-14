# 2-in-1 command to completely compile project
all: venison compile

remake: clean all run

# Run bison on the ypp file
venison:
	bison \
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
	./testing p3test1.myl && echo "---" &&\
	./testing p3test2.myl && echo "---" &&\
	./testing p3test3.myl && echo "---"

inputs:
	cat p3test1.myl && echo "------" && \
	cat p3test2.myl && echo "------" && \
	cat p3test3.myl

clean:
	rm -f ./testing ./main.tab.cpp

.PHONY: clean
