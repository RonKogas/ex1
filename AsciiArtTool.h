#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include "RLEList.h"

/**
* Reading writing AsciiArt
*
*
* The following functions are available:
*   asciiArtRead	        - Creates an RLE list for an AsciiArt image.
*   asciiArtPrint		    - prints an AsciiArt image according to an RLE list.
*   asciiArtPrintEncoded    - prints a compressed image according to an RLE list.
*/


/**
* This functions gets a file that contains an AsciiArt image and returns the RLE list of all the characters in the image.
*
* @param in_stream - a pointer to a file that contains an image to compress.
*
* @return RLE list of all the characters in the image
*/
RLEList asciiArtRead(FILE* in_stream);


/**
* This function prints to an output file, an image according the characters in the RLE list.
*
* @param list - RLE list of all the characters in the image.
* @param out_stream - a pointer to an output file.
*
* @return
*   RLE_LIST_NULL_ARGUMENT if one of the parameters is null.
*   RLE_LIST_SUCCESS in case of success.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
* This function prints to an output file the compressed image according the characters in the RLE list.
*
* @param list - RLE list of all the characters in the image.
* @param out_stream - a pointer to an output file.
*
* @return
*   RLE_LIST_NULL_ARGUMENT if one of the parameters is null.
*   RLE_LIST_SUCCESS in case of success.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //HW1_ASCIIARTTOOL_H