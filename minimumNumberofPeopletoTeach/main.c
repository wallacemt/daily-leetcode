#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shareLanguage(int* lang1, int size1, int* lang2, int size2) {
    if (!lang1 || !lang2 || size1 <= 0 || size2 <= 0) return 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (lang1[i] == lang2[j]) {
                return 1;
            }
        }
    }

    return 0;
}

int minimumTeachings(int n, int** languages, int languagesSize, int* languagesColSize, int** friendships, int friendshipsSize, int* friendshipsColSize) {
   
    int cannotCommunicate[500][2];
    int cannotCommunicateSize = 0;
    
    for (int i = 0; i < friendshipsSize; i++) {
        int user1 = friendships[i][0] - 1; 
        int user2 = friendships[i][1] - 1;
        
        if (!shareLanguage(languages[user1], languagesColSize[user1], 
                          languages[user2], languagesColSize[user2])) {
            cannotCommunicate[cannotCommunicateSize][0] = user1;
            cannotCommunicate[cannotCommunicateSize][1] = user2;
            cannotCommunicateSize++;
        }
    }
    
    if (cannotCommunicateSize == 0) return 0;
    
    int minTeach = languagesSize;

    for (int lang = 1; lang <= n; lang++) {
        int usersToTeach[500] = {0};
        int teachCount = 0;
        for (int i = 0; i < cannotCommunicateSize; i++) {
            int user1 = cannotCommunicate[i][0];
            int user2 = cannotCommunicate[i][1];
            
            int user1Knows = 0;
            for (int j = 0; j < languagesColSize[user1]; j++) {
                if (languages[user1][j] == lang) {
                    user1Knows = 1;
                    break;
                }
            }
            
            int user2Knows = 0;
            for (int j = 0; j < languagesColSize[user2]; j++) {
                if (languages[user2][j] == lang) {
                    user2Knows = 1;
                    break;
                }
            }
            
            if (!user1Knows && !usersToTeach[user1]) {
                usersToTeach[user1] = 1;
                teachCount++;
            }
            if (!user2Knows && !usersToTeach[user2]) {
                usersToTeach[user2] = 1;
                teachCount++;
            }
        }
        
        if (teachCount < minTeach) {
            minTeach = teachCount;
        }
    }
    
    return minTeach;
}