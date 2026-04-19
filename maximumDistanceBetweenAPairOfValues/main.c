int maxDistance(int* nums1, int n1, int* nums2, int n2) {
    int j = 0;
    int maxDist = 0;
    
    // Traverse through nums1
    for(int i = 0; i < n1; i++) {
        // Advance j while nums1[i] <= nums2[j]
        while(j < n2 && nums1[i] <= nums2[j]) {
            j++;
        }
        
        // Calculate distance: j - i - 1
        // j é o índice do primeiro elemento > nums1[i]
        // Distância = (índice em nums2) - (índice em nums1) - 1
        int dist = j - i - 1;
        
        // Update maximum
        if(dist > maxDist) {
            maxDist = dist;
        }
    }
    
    return maxDist;
}