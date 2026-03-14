#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int cnt;
    int tar;
    char* res;
    bool check;
} State;

void backtrack(char* curr, int depth, char last, int n, State* state) {
    if (state->check) {
        return;
    }

    if (depth == n) {
        state->cnt++;
        if (state->cnt == state->tar) {
            curr[n] = '\0';
            memcpy(state->res, curr, n + 1);  // Mais rápido que strcpy
            state->check = true;
        }
        return;
    }

    for (int i = 0; i < 3; i++) {
        char option = (i == 0) ? 'a' : (i == 1) ? 'b' : 'c';
        if (option != last) {
            curr[depth] = option;
            backtrack(curr, depth + 1, option, n, state);
            if (state->check) {
                return;
            }
        }
    }
}

char* getHappyString(int n, int k) {
    char* ans = (char*)malloc((n + 1) * sizeof(char));
    char* temp_str = (char*)malloc((n + 1) * sizeof(char));
    
    State state = {0, k, ans, false};

    backtrack(temp_str, 0, 'd', n, &state);

    free(temp_str);

    if (state.check) {
        return ans;
    } else {
        free(ans);
        return "";
    }
}