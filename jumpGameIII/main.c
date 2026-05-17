#pragma optimize("O3, unroll-loops")
int q[50000];
int front=0, back=0;// for queue 
static bool canReach(int* arr, int n, int start) {
    front=back=0;// reset q
    q[back++]=start;
    while(front<back){
        const int i=q[front++];// pop the q, obtain i
        const int x=arr[i], l=i-x, r=i+x;
        if (x==-1) continue;
        if (x==0) return 1;
        arr[i]=-1;
        if (l>=0 && arr[l]>=0) q[back++]=l;// push l to q
        if (r<n  && arr[r]>=0) q[back++]=r;// push r to q
    }
    return 0;
}