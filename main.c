#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

#define ROUNDS 10

void clearScreen() {
    system("@cls||clear");
}

typedef struct {
    int player1_score;
    int player2_score;
} RoundData;

int getValue() {
    int value = -12;
    int direction = 0;
    int keyPressed = 0;
    clearScreen();
    while (!keyPressed) {
        if (value == -12) {
            printf("[||================================================]");
        } else if (value == -11) {
            printf("[==||==============================================]");
        } else if (value == -10) {
            printf("[====||============================================]");
        } else if (value == -9) {
            printf("[======||==========================================]");
        } else if (value == -8) {
            printf("[========||========================================]");
        } else if (value == -7) {
            printf("[==========||====================================||]");
        } else if (value == -6) {
            printf("[============||====================================]");
        } else if (value == -5) {
            printf("[==============||==================================]");
        } else if (value == -4) {
            printf("[================||================================]");
        } else if (value == -3) {
            printf("[==================||==============================]");
        } else if (value == -2) {
            printf("[====================||============================]");
        } else if (value == -1) {
            printf("[======================||==========================]");
        } else if (value == 0) {
            printf("[========================||========================]");
        } else if (value == 1) {
            printf("[==========================||======================]");
        } else if (value == 2) {
            printf("[============================||====================]");
        } else if (value == 3) {
            printf("[==============================||==================]");
        } else if (value == 4) {
            printf("[================================||================]");
        } else if (value == 5) {
            printf("[==================================||==============]");
        } else if (value == 6) {
            printf("[====================================||============]");
        } else if (value == 7) {
            printf("[======================================||==========]");
        } else if (value == 8) {
            printf("[========================================||========]");
        } else if (value == 9) {
            printf("[==========================================||======]");
        } else if (value == 10) {
            printf("[============================================||====]");
        } else if (value == 11) {
            printf("[==============================================||==]");
        } else if (value == 12) {
            printf("[================================================||]");
        }

        if (kbhit()) {
            keyPressed = 1;
        }

        if (direction == 0) {
            value++;
        } else {
            value--;
        }
        if (value == -12 || value == 12) {
            direction = !direction;
        }

        usleep(20000);
        clearScreen();
    }

    return abs(abs(value) - 12);
}

void printScore(const char *player1_name, const char *player2_name, RoundData *rounds, int current_round) {
    clearScreen();
    printf("Pontuacao das Rodadas:\n");
    for (int i = 0; i < current_round; i++) {
        printf("Rodada %d:\n", i + 1);
        printf("%s: %d\n", player1_name, rounds[i].player1_score);
        printf("%s: %d\n\n", player2_name, rounds[i].player2_score);
    }
    printf("Pontuacao Total ate a Rodada %d:\n", current_round);
    int total_score1 = 0, total_score2 = 0;
    for (int i = 0; i < current_round; i++) {
        total_score1 += rounds[i].player1_score;
        total_score2 += rounds[i].player2_score;
    }
    printf("%s: %d\n", player1_name, total_score1);
    printf("%s: %d\n", player2_name, total_score2);
    printf("\nPressione qualquer tecla para continuar...\n");
    getch();
}

int main() {
    RoundData rounds[ROUNDS];
    int round;

    char player1_name[50];
    char player2_name[50];

    printf("Bem-vindos ao Jogo de Boliche!\n\n");
    printf("Jogador 1, por favor, insira seu nome: ");
    scanf("%s", player1_name);
    printf("Jogador 2, por favor, insira seu nome: ");
    scanf("%s", player2_name);

    for (round = 0; round < ROUNDS; round++) {

        clearScreen();
        printf("Rodada %d...", round + 1);
        usleep(1000000);
        clearScreen();

        int choice;
        do {
            clearScreen();
            printf("Menu:\n");
            printf("1. Jogar com %s\n", player1_name);
            scanf("%d", &choice);

            if (choice == 1) {
                printf("%s, pressione qualquer tecla para jogar...\n\nClique quando o indicador estiver no meio para maior pontuacao!",
                       player1_name);
                getch();
                int score1 = getValue();
                rounds[round].player1_score = score1;
                clearScreen();
            }
        } while (choice != 1);


        do {
            clearScreen();
            printf("Menu:\n");
            printf("1. Jogar com %s\n", player2_name);
            scanf("%d", &choice);

            if (choice == 1) {
                printf("%s, pressione qualquer tecla para jogar...\n\nClique quando o indicador estiver no meio para maior pontuacao!",
                       player2_name); // Mudança aqui
                getch();
                int score2 = getValue();
                rounds[round].player2_score = score2;
                clearScreen();
            }
        } while (choice != 1);

        printScore(player1_name, player2_name, rounds, round + 1);
        usleep(3000000);

        int choice2;
        do {
            clearScreen();
            printf("Menu:\n");
            printf("1. Abrir Placar\n");
            printf("2. Continuar Jogando\n");
            printf("Escolha a opcao desejada: ");
            scanf("%d", &choice2);

            if (choice2 == 1) {
                printScore(player1_name, player2_name, rounds, round + 1);
            }
        } while (choice2 != 2);
    }

    printf("Fim do jogo!\n\n");
    printf("Pontuacao Final:\n");
    int total_score1 = 0, total_score2 = 0;
    for (round = 0; round < ROUNDS; round++) {
        total_score1 += rounds[round].player1_score;
        total_score2 += rounds[round].player2_score;
    }
    printf("%s: %d\n", player1_name, total_score1);
    printf("%s: %d\n\n", player2_name, total_score2);

    if (total_score1 > total_score2) {
        printf("%s venceu!\n", player1_name);
    } else if (total_score1 < total_score2) {
        printf("%s venceu!\n", player2_name);
    } else {
        printf("Empate!\n");
    }

    int final_choice;
    printf("\nDeseja jogar novamente?\n");
    printf("1. Sim\n");
    printf("2. Nao (Encerrar)\n");
    printf("Escolha a opcao desejada: ");
    scanf("%d", &final_choice);

    if (final_choice == 1) {
        main();
    } else {
        printf("Obrigado por jogar!\n");
    }

    usleep(1000000);
    return 0;
}
