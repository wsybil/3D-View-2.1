CXX = g++
STD = -std=c++17
CFLAG = -Wall -Werror -Wextra
TEST = -o test -I Model/.
TFILES = Tests/test.cc Model/parser.cc
DIST = 3D_Viewer_v2.tar.gz
GTEST_LIBS := -lgtest -pthread
OS := $(shell uname -s)

all: install tests

install:
		mkdir build
		cd ./build/; qmake6 ../; make
		mkdir $(HOME)/3D_Viewer_v2/
		cp -rf build/3D_Viewer_v2.app $(HOME)/3D_Viewer_v2/

uninstall:
		rm -rf $(HOME)/3D_Viewer_v2

clean:

dvi:
ifeq ($(OS), Darwin)
	open ./documentation.html
else
	xdg-open ./documentation.html
endif

gcov_report:
	$(CXX) $(CFLAG) $(TFILES) $(STD) -fprofile-arcs -ftest-coverage -lgtest -o test -pthread
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info
	rm -rf *.gc* *.info test
ifeq ($(OS), Darwin)
	# open report/index.html
else
	xdg-open report/index.html
endif

dist: clean
		cd ..; tar -cvzf $(DIST) src; mv $(DIST) src

test:
		$(CXX) $(STD) $(CFLAG) $(TEST) $(TFILES) $(GTEST_LIBS); mv test Tests/
		./Tests/test

clean:
	rm -rf *.o *.gc* 3D_Viewer_v2.tar.gz report Tests/test *.a test test.info build

check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cc *.h Model/*.cc Tests/*.cc Model/*.h settings/*.cc settings/*.h; rm -rf .clang-format
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- Tests/test
else
	valgrind --show-leak-kinds=all Tests/test
endif
	make clean