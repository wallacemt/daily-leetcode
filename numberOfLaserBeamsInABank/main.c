int numberOfBeams(char** bank, int bankSize) {
    int totalBeams = 0;
    int prevDevices = 0;
    
    for (int i = 0; i < bankSize; i++) {
        int currentDevices = 0;
        
        for (int j = 0; bank[i][j] != '\0'; j++) {
            if (bank[i][j] == '1') {
                currentDevices++;
            }
        }
        
        if (currentDevices > 0) {
            totalBeams += prevDevices * currentDevices;
            prevDevices = currentDevices;
        }
    }
    
    return totalBeams;
}
