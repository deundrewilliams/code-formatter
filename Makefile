CC = g++ -std=c++17

SRC_CODE = token.cpp lexer.cpp analyzer.cpp driver.cpp

all: $(SRC_CODE)
		$(CC) $(SRC_CODE) -lm
