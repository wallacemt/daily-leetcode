#include <string.h>
 
int numberOfSubstrings(char* s) {
    int freq_a = 0, freq_b = 0, freq_c = 0;
    int left = 0, res = 0;
    int n = strlen(s);

    for (int i = 0; i < n; i++) { 
        switch (s[i]) {
            case 'a': freq_a++; break;
            case 'b': freq_b++; break;
            case 'c': freq_c++; break;
        }
 
        while (freq_a && freq_b && freq_c) {
            res += n - i;
             
            switch (s[left]) {
                case 'a': freq_a--; break;
                case 'b': freq_b--; break;
                case 'c': freq_c--; break;
            }
            left++;
        }
    }

    return res;
}

 