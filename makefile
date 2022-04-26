CC = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
EXEC = AsciiArtTool 
COMP_FLAG = -std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -Werror -pedantic-errors -DNDEBUG


$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o AsciiArtTool
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) RLEList.c
AsciiArtTool.o : AsciiArtTool.c AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) AsciiArtTool.c
main.o : main.c AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) main.c
clean:
	rm -f $(OBJS) $(EXEC)
