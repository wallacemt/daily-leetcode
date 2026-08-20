 
#pragma GCC optimize("O3,unroll-loops")
int* resultArray(int* nums, int numsSize, int* returnSize) {
    // Alocação de dois arrays temporários
    int* arr1 = (int*)malloc(numsSize * sizeof(int));
    int* arr2 = (int*)malloc(numsSize * sizeof(int));
    if (!arr1 || !arr2) return NULL;
     
    int last1 = nums[0];
    int last2 = nums[1];
    int idx1 = 1;
    int idx2 = 1;
    
    arr1[0] = nums[0];
    arr2[0] = nums[1];
     
    for (int i = 2; i < numsSize; i++) {
        if (last1 > last2) {
            arr1[idx1++] = nums[i];
            last1 = nums[i];
        } else {
            arr2[idx2++] = nums[i];
            last2 = nums[i];
        }
    }
     
    int* result = (int*)malloc(numsSize * sizeof(int));
    if (!result) return NULL;
    
    int pos = 0;
    for (int i = 0; i < idx1; i++) {
        result[pos++] = arr1[i];
    }
    for (int i = 0; i < idx2; i++) {
        result[pos++] = arr2[i];
    }
    
    free(arr1);
    free(arr2);
    
    *returnSize = numsSize;
    return result;
}