CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -pedantic
EXEC=model
SRCS=model.cpp
FILES=$(SRCS) Makefile
ZIP=T5_xlasmi00_xlazik00.zip

$(EXEC): $(SRCS)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC) $(ZIP)

zip:
	zip $(ZIP) $(FILES)
