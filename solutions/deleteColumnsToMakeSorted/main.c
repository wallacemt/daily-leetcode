int minDeletionSize(char ** strs, int strsSize){
    int remove = 0;
    for(int i=0 ; i<strlen(strs[0]);++i)
        for(int j=0;j<strsSize-1;++j)
            if(strs[j][i] > strs[j+1][i]){
                ++remove;
                break;
            }
    return remove;}