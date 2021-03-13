VPATH=src:./src
CXXFLAGS+=-std=c++14

default: BasicTest

test:: BasicTest
	@./BasicTest

BasicTest: DescParser.cpp DescWriter.cpp BasicTest.cpp

clean::
	rm -f *.o BasicTest
