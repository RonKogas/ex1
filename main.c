#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"
/**
 * @brief takes image from file source and write it 
 * in encoded format to target
 * @param source - the file containing the image
 * @param target - the file to write the encoded format into
 * @return RLEListResult 
 * RLE_LIST_NULL_ARGUMENT if one of the parameters is null.
 * RLE_LIST_SUCCESS in case of success.
 */
RLEListResult writeEncoded(FILE* source,FILE* target);
/**
 * @brief takes image from file source and write it 
 * in inverted (and not encoded) format to target
 * ' ' replaced with '@' and vice versa and every other char remain the same
 * @param source - the file containing the image
 * @param target - the file to write the encoded format into
 * @return RLEListResult 
 * RLE_LIST_NULL_ARGUMENT if one of the parameters is null.
 * RLE_LIST_SUCCESS in case of success.
 */
RLEListResult writeInverted(FILE* source,FILE* target);
/**
 * @brief convert ' '(space) to '@'
 * and '@' to ' '. rest of the chars remain
 * @param c - the char to invert
 * @return char 
 * ' ' if c=='@'
 * '@' if c==' '
 * c otherwise
 */
char charInverter(char c);
int main(int argc, char** argv)
{
    //check that there are enough arguments
    if(argc!=4)
    {
        return 0;
    }
    //open the source and target files
    FILE* source = fopen(argv[2], "r");
	if (!source) {
		return 0;
	}
	FILE* target = fopen(argv[3], "w");
	if (!target) {
		fclose(source);
		return 0;
	}
    if(!strcmp(argv[1],"-e"))
    {
        writeEncoded(source,target);
    }
    else if(!strcmp(argv[1],"-i"))
    {
        writeInverted(source,target);
    }
    fclose(source);
    fclose(target);
    return 0;
}


RLEListResult writeEncoded(FILE* source,FILE* target)
{
    RLEList image=asciiArtRead(source);
    return asciiArtPrintEncoded(image, target);
}


RLEListResult writeInverted(FILE* source,FILE* target)
{
    RLEList image=asciiArtRead(source);
    if(RLEListMap(image, charInverter)!=RLE_LIST_SUCCESS)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    return asciiArtPrint(image, target);
}

char charInverter(char c)
{
    if(c==' ')
    {
        return '@';
    }
    else if(c=='@')
    {
        return ' ';
    }
    return c;
}