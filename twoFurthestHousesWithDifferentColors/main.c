#pragma optimize("O3, unroll-loops")
int maxDistance(int* colors, int n) {
    int c0=colors[0], cN=colors[n-1];
    int lMax=0, rMax=0;
    for(int i=0; i<n; i++){
        int c=colors[i];
        if (c0!=c) lMax=fmax(lMax, i);
        if (cN!=c) rMax=fmax(rMax, n-1-i);
    }
    return fmax(lMax, rMax);
}
