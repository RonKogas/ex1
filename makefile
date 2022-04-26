CC = gcc
OBJS = RLEList.o tool/AsciiArtTool.o tool/main.o
EXEC = AsciiArtTool
COMP_FLAG = -std=c99 -I/home/mtm/public/2122b/ex1 -I/tool -Wall -Werror -pedantic-errors -DNDEBUG


$(EXEC) : $(OBJS)
	$(CC)  $(OBJS) -o AsciiArtTool
RLEList.o : RLEList.c RLEList.h
	$(CC) -c  $(COMP_FLAG) RLEList.c
tool/AsciiArtTool.o : tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c  $(COMP_FLAG) tool/AsciiArtTool.c -o tool/AsciiArtTool.o
tool/main.o : tool/main.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c  $(COMP_FLAG) tool/main.c -o tool/main.o
clean:
	rm -f $(OBJS) $(EXEC)
