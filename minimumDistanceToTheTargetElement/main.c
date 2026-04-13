int getMinDistance(int* nums, int numsSize, int target, int start) {
    int minDistance = INT_MAX; 
    int found = 0; 

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == target) {
            found = 1; 
            int currentDistance = abs(i - start);
            if (currentDistance < minDistance) {
                minDistance = currentDistance;
            }
        }
    }

    return found ? minDistance : -1;
}
