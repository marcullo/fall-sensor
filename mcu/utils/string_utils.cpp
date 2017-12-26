#include "string_utils.h"
#include <ctype.h>

int strncasecmp(const char* str1, const char* str2)
{
    if (!str1 || !str1)
        return 1;
    
    while(*str1)
    {
        if (tolower(*str1++) != tolower(*str2++))
            return 1;
    }
    return *str2 != 0;
}

int strinarrayid(const char* str, const char** array)
{
    if (!str || *str == '\0' || !array)
        return -1;
    
    uint32_t i = 0;
    while (*array)
    {
        const char* elem = array[i];
        if (strncasecmp(str, elem) == 0) {
            return i;
        }
        i++;
    }
    
    return -1;
}
