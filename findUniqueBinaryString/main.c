#include <stdlib.h>
#include <string.h>

char* findDifferentBinaryString(char** nums, int numsSize) 
{
   
    if (!nums || numsSize <= 0) {
        return NULL;
    }

    char* result = (char*)malloc((numsSize + 1) * sizeof(char));
    
     if (!result) {
        return NULL;
    }
  for (int i = 0; i < numsSize; i++) {
        // Inverte o bit diagonal: '0' → '1', '1' → '0'
        result[i] = (nums[i][i] == '0') ? '1' : '0';
    }
    
    // Null terminator
    result[numsSize] = '\0';
    
    return result;
}