int getCommon(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int s1 = 0;
    int s2 = 0;
    
    while (s1 < nums1Size && s2 < nums2Size) {
        if (nums1[s1] == nums2[s2])
            return nums1[s1];
        else if (nums1[s1] < nums2[s2])
            s1++;
        else
            s2++;
    }
    return -1;
}