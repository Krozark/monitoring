SRC = $(wildcard *.c*)
OBJ = $(SRC:.cpp=.o) $(SRC:*.cpp=.o)

.cpp.o:
	$(CC) $(FLAGS) -o $@ -c $<
	@cp $@ $(OBJ_DIR)

.c.o:
	$(CC) $(FLAGS) -o $@ -c $<
	@cp $@ $(OBJ_DIR)

all: $(OBJ)

clean:
	@rm -f *.o
	@rm -f *.exe
