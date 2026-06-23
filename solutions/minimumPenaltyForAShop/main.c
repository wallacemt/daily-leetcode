int bestClosingTime(char* customers) {
    int yCount = 0;
    int len = 0;
    
    for (int i = 0; customers[i] != '\0'; i++) {
        if (customers[i] == 'Y') {
            yCount++;
        }
        len++;
    }
    
    int penalty = yCount;  
    int minPenalty = penalty;
    int minHour = 0;
    
    for (int i = 0; i < len; i++) {
        if (customers[i] == 'Y') {
            penalty--;  
        } else {
            penalty++; 
        }
        
        if (penalty < minPenalty) {
            minPenalty = penalty;
            minHour = i + 1;
        }
    }
    
    return minHour;
}