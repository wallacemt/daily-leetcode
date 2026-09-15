#include <string.h>
#include <stdbool.h>
 
bool isPalindrome(char* s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Encontra máximo de palindromes não-sobrepostas com tamanho >= k
int maxPalindromes(char* s, int k) {
    if (!s || k <= 0) {
        return 0;
    }

    int n = strlen(s);
    
    // k não pode ser maior que a string
    if (k > n) {
        return 0;
    }

    int count = 0;
    int lastEnd = 0;  // Próxima posição disponível

    // Itera por cada posição final possível
    for (int right = k - 1; right < n; right++) { 
        int left = right - k + 1;

        if (left >= lastEnd && isPalindrome(s, left, right)) {
            count++;
            lastEnd = right + 1;
        } 
        else if (left - 1 >= lastEnd && isPalindrome(s, left - 1, right)) {
            count++;
            lastEnd = right + 1;
        }
    }

    return count;
}