#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define NUM_OF_ARGUMENTS (4)
#define SOURCE_ARGUMENT (2)
#define TARGET_ARGUMENT (3)
#define FLAG_ARGUMENT (1)

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
    if(argc!=NUM_OF_ARGUMENTS)
    {
        return 0;
    }
    //open the source and target files
    FILE* source = fopen(argv[SOURCE_ARGUMENT], "r");
	if (!source) {
		return 0;
	}
	FILE* target = fopen(argv[TARGET_ARGUMENT], "w");
	if (!target) {
		fclose(source);
		return 0;
	}
    if(!strcmp(argv[FLAG_ARGUMENT],"-e"))
    {
        writeEncoded(source,target);
    }
    else if(!strcmp(argv[FLAG_ARGUMENT],"-i"))
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
    RLEListResult returnValue = asciiArtPrintEncoded(image, target);
    RLEListDestroy(image);
    return returnValue;
}


RLEListResult writeInverted(FILE* source,FILE* target)
{
    RLEList image = asciiArtRead(source);
    if( RLEListMap(image, charInverter) != RLE_LIST_SUCCESS )
    {
        RLEListDestroy(image);
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult returnValue = asciiArtPrint(image, target);
    RLEListDestroy(image);
    return returnValue;
}

char charInverter(char c)
{
    if( c == ' ' )
    {
        return '@';
    }
    else if( c == '@' )
    {
        return ' ';
    }
    return c;
}
