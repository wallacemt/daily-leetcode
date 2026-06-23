#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long long* balance;
    int n;
} Bank;

Bank* bankCreate(long long* balance, int balanceSize) {
    Bank* bank = (Bank*)malloc(sizeof(Bank));
    if (!bank) return NULL;
    
    bank->n = balanceSize;
    bank->balance = (long long*)malloc(balanceSize * sizeof(long long));
    if (!bank->balance) {
        free(bank);
        return NULL;
    }
    
    for (int i = 0; i < balanceSize; i++) {
        bank->balance[i] = balance[i];
    }
    
    return bank;
}

bool bankTransfer(Bank* obj, int account1, int account2, long long money) {

    if (account1 < 1 || account1 > obj->n || 
        account2 < 1 || account2 > obj->n) {
        return false;
    }
    
    if (money < 0) {
        return false;
    }
    
    if (obj->balance[account1 - 1] < money) {
        return false;
    }
    
    obj->balance[account1 - 1] -= money;
    obj->balance[account2 - 1] += money;
    
    return true;
}

bool bankDeposit(Bank* obj, int account, long long money) {
  
    if (account < 1 || account > obj->n) {
        return false;
    }
    
    if (money < 0) {
        return false;
    }
    
    obj->balance[account - 1] += money;
    
    return true;
}

bool bankWithdraw(Bank* obj, int account, long long money) {
 
    if (account < 1 || account > obj->n) {
        return false;
    }
    if (money < 0) {
        return false;
    }
    
    if (obj->balance[account - 1] < money) {
        return false;
    }
    
    obj->balance[account - 1] -= money;
    
    return true;
}

void bankFree(Bank* obj) {
    if (obj) {
        if (obj->balance) {
            free(obj->balance);
        }
        free(obj);
    }
}