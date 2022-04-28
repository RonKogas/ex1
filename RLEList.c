#include "RLEList.h"
#include <stdlib.h>
#define ERROR_INT (-1)
#define MIN_CHARS_FOR_LINE (2)
#define EMPTY_NODE_VALUE (0)
#define EMPTY_NODE_NUMOFAPPEARENCES (0)

struct RLEList_t{
    char value;
    int numOfAppearences;
    struct RLEList_t* nextRLE;
    //TODO: implement
};

//implement the functions here

/**
 * @brief count the number of nodes in given RLEList
 * for example: W2,A13,v4 return 3
 * 
 * @param list - the list to count his nodes
 * @return int - the number of the nodes
 */
static int RLENumOfNodes(RLEList list);

/**
 * @brief calculate the size of the RLEListExportToString()
 * return value
 * @param list - the list that will be exported to string
 * @return int - the size of the 'encode' string
 */
static int findStringSize(RLEList list);

/**
 * @brief put the num represented as chars in Str and
 * for example: if num=135
 * *str=1 *(str+1)=3 *(str+2)=5
 * @param Str adress to put the digits of num
 *       note: the function assumes enough memory allocated from Str 
 * @param num - natural number
 */
static void numToString(char* Str, int num);

/**
 * @brief calculate the amount of digits of num
 * for example: findNumToStringSize(126)==3
 *              findNumToStringSize(0)==1
 * @param num - natural number
 * @return int - number of digits
 */
static int findNumToStringSize(int num);

static void numToString(char* str, int num)
{
    if(num==0)
    {
        str[0]='0';
        return;
    }
    int i=findNumToStringSize(num)-1;
    while(num)
    {
        str[i--] = (num % 10) + '0';
        num /= 10;
    }
}

static int findStringSize(RLEList list)
{
    int size = 1;
    while(list)
    {
        size += MIN_CHARS_FOR_LINE;
        int num = list->numOfAppearences;
        size += findNumToStringSize(num);
        list = list->nextRLE;
    }
    return size;
}

static int findNumToStringSize(int num)
{
    if(num==0)
    {
        return 1;
    }
    int size = 0;
    while(num)
    {
        size++;
        num /= 10;
    }
    return size;
}


static int RLENumOfNodes(RLEList list)
{
    int result=0;
    while(list)
    {
        result++;
        list = list->nextRLE;
    }
    return result;
}

RLEList RLEListCreate()
{
    RLEList ptr=malloc( sizeof(*ptr) );
    if(!ptr)
    {
        return NULL;
    }
    ptr->numOfAppearences = EMPTY_NODE_NUMOFAPPEARENCES;
    ptr->nextRLE = NULL;
    ptr->value = EMPTY_NODE_VALUE;
    return ptr;
}

void RLEListDestroy(RLEList list)
{
    while(list)
    {
        RLEList nextList = list->nextRLE;
        free(list);
        list = nextList;
    }
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if(!list || !value)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while(list->nextRLE != NULL)
    {
        list = list->nextRLE; 
    }
    if(list->value == value)
    {
        list->numOfAppearences += 1;
        return RLE_LIST_SUCCESS;
    }
    else if(list->numOfAppearences == 0)
    {
        list->numOfAppearences = 1;
        list->value = value;
        return RLE_LIST_SUCCESS;
    }
    RLEList newRLE = RLEListCreate();
    if(!newRLE)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    list->nextRLE = newRLE;
    newRLE->value = value;
    newRLE->numOfAppearences = 1;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if(!list)
    {
        return ERROR_INT;
    }
    int sum = 0;
    while(list)
    {
        sum += list->numOfAppearences;
        list = list->nextRLE;
    }
    return sum;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index < 0 || index >= RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    //count the maximal index of the next RLE
    int indexSoFar = list->numOfAppearences-1;   
    RLEList head = list;  
    while(indexSoFar < index)
    {
        indexSoFar += (list->nextRLE)->numOfAppearences;
        if(indexSoFar < index)
        {
            list = list->nextRLE;
        }
    }

    //in this case the index was in the first node
    if(list == head && index+1 <= list->numOfAppearences)
    {
        if(list->numOfAppearences == 1 && list->nextRLE)
        {
            RLEList secondRLE = list->nextRLE;
            list->value = (list->nextRLE)->value;
            list->numOfAppearences = (list->nextRLE)->numOfAppearences;
            list->nextRLE = (list->nextRLE)->nextRLE;
            free(secondRLE);
        }
        else
        {
            list->numOfAppearences -= 1;
        }
        return RLE_LIST_SUCCESS;
    }

    //in this case the index was in the next nodes
    if((list->nextRLE)->numOfAppearences==1)
    {
        RLEList secondRLE= list->nextRLE;
        list->nextRLE = (list->nextRLE)->nextRLE;
        free(secondRLE);
        while(list->nextRLE && list->value == (list->nextRLE)->value)
        {
            RLEList secondRLE= list->nextRLE;
            list->numOfAppearences+=(list->nextRLE)->numOfAppearences;
            list->nextRLE = (list->nextRLE)->nextRLE;
            free(secondRLE);
        }
    }
    else
    {
        (list->nextRLE)->numOfAppearences -= 1;
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(!list && result)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if( result && (index < 0 || index >= RLEListSize(list)) )
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    if(result)
    {
        *result = RLE_LIST_SUCCESS;
    }
    int indexSoFar = 0; 

    while(indexSoFar < index)
    {
        indexSoFar += list->numOfAppearences;
        if(indexSoFar <= index)
        {
            list = list->nextRLE;
        }
    }
    char returnValue = list->value;
    return returnValue;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(!list && result)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    if(result)
    {
        *result = RLE_LIST_SUCCESS;
    }
    const int numOfNodes = RLENumOfNodes(list);
    char* outString = (char*)malloc(sizeof(char) * findStringSize(list));
    int i = 0;
    for (int line = 0; line < numOfNodes; ++line)
    {
        outString[i++] = list->value;
        numToString(outString+i, list->numOfAppearences);
        i += findNumToStringSize(list->numOfAppearences);
        outString[i++] = '\n';
        list = list->nextRLE;
    }
    outString[i] = '\0';
    return outString;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(!list || !map_function)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    const int numOfNodes = RLENumOfNodes(list);
    for (int line=0; line<numOfNodes; ++line)
    {
        list->value = map_function(list->value);
        list = list->nextRLE;
    }
    return RLE_LIST_SUCCESS;
}
