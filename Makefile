SRC= olugLang.tab.cpp lex.yy.c main.cpp handlers.cpp
all: olangc

olangc: ${SRC} 
	clang++ -pthread -w -g -std=c++11 -I${HOME}/lib/boost/boost_1_58_0/ ${SRC} `llvm-config --cppflags --ldflags --libs core mcjit native bitwriter --system-libs` -O0 -o olangc

lex.yy.c: lexer.l
	flex lexer.l

olugLang.tab.cpp: olugLang.ypp
	bison -d olugLang.ypp 
clean:
	rm -rf lex.yy.c olangc olugLang.tab.cpp olugLang.tab.hpp lex.yy.c
