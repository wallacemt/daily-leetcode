#define maxf(a, b) ((a) > (b) ? (a) : (b))

int recursion(int* arr, int* arrJump, int arrSize, int d, int ind){
    if(arrJump[ind]) return arrJump[ind];

    arrJump[ind] = 1;

    for(int i = 1; i <= d && ind + i < arrSize; i++){
        if(arr[ind + i] < arr[ind])
            arrJump[ind] = maxf(recursion(arr, arrJump, arrSize, d, ind + i) + 1, arrJump[ind]);
        else break;
    }
    
    for(int i = 1; i <= d && ind - i >= 0; i++){
        if(arr[ind - i] < arr[ind])
            arrJump[ind] = maxf(recursion(arr, arrJump, arrSize, d, ind - i) + 1, arrJump[ind]);
        else break;
    }

    return arrJump[ind];
}

int maxJumps(int* arr, int arrSize, int d) {
    int *arrJump = (int *)calloc(arrSize, sizeof(int)); 
    
    int res = 0;

    for(int i = 0; i < arrSize; i++){
        res = maxf(recursion(arr, arrJump, arrSize, d, i), res);
    }

    free(arrJump);

    return res;
}
