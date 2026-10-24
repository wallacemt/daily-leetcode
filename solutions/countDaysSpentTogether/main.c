#include <stdio.h>

int countDaysTogether(char* arriveAlice, char* leaveAlice,
                      char* arriveBob, char* leaveBob) {
    // Número de dias em cada mês
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int prefix[12] = {0};  

    // Calcular o número total de dias até o início de cada mês
    for (int i = 1; i < 12; i++) {
        prefix[i] = prefix[i - 1] + days[i - 1];
    }

    // Função auxiliar para calcular o dia do ano a partir de uma data
    int present(char* date) {
        int month = (date[0] - '0') * 10 + (date[1] - '0');
        int day = (date[3] - '0') * 10 + (date[4] - '0');
        return prefix[month - 1] + day; // Retorna o dia do ano
    }

    // Calcular dias de chegada e partida
    int a = present(arriveAlice);
    int b = present(arriveBob);
    int c = present(leaveAlice);
    int d = present(leaveBob);
 
    int start = a > b ? a : b; // O mais tarde de chegada
    int end = c < d ? c : d;   // O mais cedo de partida

    // Calcular o número de dias em que estão juntos
    return end >= start ? end - start + 1 : 0;
}
 

