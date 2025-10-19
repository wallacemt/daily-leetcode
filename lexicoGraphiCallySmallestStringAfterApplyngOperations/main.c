#include <stdio.h>
#include <string.h>

#define MAXN 105

static inline int calculate_gcd(int a, int b) {
    while (b) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

static inline void increment_digits_at_positions(char *s, int times, int increment_value, int start_position) {
    if (times == 0) return;
    
    int n = strlen(s);
    int total_increment = (times * increment_value) % 10;
    
    if (total_increment == 0) return;
    
    for (int i = start_position; i < n; i += 2) {
        int digit = s[i] - '0';
        s[i] = '0' + ((digit + total_increment) % 10);
    }
}

static inline void rotate_string(const char *source, int rotation, char *destination) {
    int n = strlen(source);
    
    if (n == 0) {
        destination[0] = '\0';
        return;
    }
    
    rotation %= n;
    
    int split_point = (n - rotation + n) % n;
    memcpy(destination, source + split_point, n - split_point);
    memcpy(destination + (n - split_point), source, split_point);
    destination[n] = '\0';
}

static inline int compare_and_update_minimum(const char *candidate, char *current_min) {
    if (strcmp(candidate, current_min) < 0) {
        strcpy(current_min, candidate);
        return 1;
    }
    return 0;
}

char* findLexSmallestString(char* s, int a, int b) {
    static char ans[MAXN];
    strcpy(ans, s);
    
    int n = strlen(s);
    int gcd = calculate_gcd(n, b);
    int rotation_cycle = n / gcd; 
    
    char rotated[MAXN], temp_odd[MAXN], temp_even[MAXN];
    int is_odd_rotation = (b % 2 == 1);

    for (int k = 0, current_rotation = 0; k < rotation_cycle; k++, current_rotation = (current_rotation + b) % n) {
        rotate_string(s, current_rotation, rotated);

        for (int odd_increments = 0; odd_increments < 10; odd_increments++) {
            strcpy(temp_odd, rotated);
            increment_digits_at_positions(temp_odd, odd_increments, a, 1); 

            if (is_odd_rotation) {
                for (int even_increments = 0; even_increments < 10; even_increments++) {
                    strcpy(temp_even, temp_odd);
                    increment_digits_at_positions(temp_even, even_increments, a, 0); 
                    compare_and_update_minimum(temp_even, ans);
                }
            } else {
                compare_and_update_minimum(temp_odd, ans);
            }
        }
    }

    return ans;
}