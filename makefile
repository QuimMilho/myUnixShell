NAME=myshell
PCH=pch.hpp.gch

CC=g++
CARGS=-std=c++17

SOURCE=src/
OUTPUT=bin/
OUTPUT_INT=bin-int/
OUTPUT_PCH=$(OUTPUT_INT)include/
INCLUDE_DIR=include/

INCLUDE=-include $(INCLUDE_DIR)pch.hpp -I./$(OUTPUT_PCH) -I./$(INCLUDE_DIR)

all: $(OUTPUT)$(NAME)
	cp $(OUTPUT)$(NAME) ..

prog: $(OUTPUT)$(NAME)

$(OUTPUT)$(NAME): $(OUTPUT) $(OUTPUT_PCH)$(PCH) $(OUTPUT_INT)files.o $(OUTPUT_INT)app.o $(OUTPUT_INT)commands.o $(INCLUDE_DIR)myshell.hpp
	$(CC) $(CARGS) -o $(OUTPUT)$(NAME) $(SOURCE)myshell.cpp $(INCLUDE) $(OUTPUT_INT)files.o $(OUTPUT_INT)app.o $(OUTPUT_INT)commands.o

$(OUTPUT_PCH)$(PCH): $(OUTPUT_PCH) $(INCLUDE_DIR)pch.hpp
	$(CC) $(CARGS) -o $(OUTPUT_PCH)$(PCH) $(INCLUDE_DIR)pch.hpp

$(OUTPUT_INT)files.o: $(OUTPUT_INT) $(SOURCE)file/Files.cpp $(INCLUDE_DIR)file/Files.hpp $(INCLUDE_DIR)myshell.hpp
	$(CC) $(CARGS) -c -o $(OUTPUT_INT)files.o $(SOURCE)file/Files.cpp $(INCLUDE)

$(OUTPUT_INT)app.o: $(OUTPUT_INT) $(SOURCE)app/App.cpp $(INCLUDE_DIR)app/App.hpp $(INCLUDE_DIR)myshell.hpp
	$(CC) $(CARGS) -c -o $(OUTPUT_INT)app.o $(SOURCE)app/App.cpp $(INCLUDE)

$(OUTPUT_INT)commands.o: $(OUTPUT_INT) $(SOURCE)commands/Commands.cpp $(INCLUDE_DIR)commands/Commands.hpp $(INCLUDE_DIR)commands/CommandList.hpp $(INCLUDE_DIR)myshell.hpp
	$(CC) $(CARGS) -c -o $(OUTPUT_INT)commands.o $(SOURCE)commands/Commands.cpp $(INCLUDE)

$(OUTPUT):
	mkdir -p $(OUTPUT)

$(OUTPUT_INT):
	mkdir -p $(OUTPUT_INT)

$(OUTPUT_PCH):
	mkdir -p $(OUTPUT_PCH)

clean:
	rm -r $(OUTPUT) $(OUTPUT_INT)
