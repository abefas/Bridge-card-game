#ifndef project2023a
#define project2023a
#include <stdbool.h>

struct hand{
    char spades[13];
    char hearts[13];
    char diamonds[13];
    char clubs[13];
    int n_spades;
    int n_hearts;
    int n_diamonds;
    int n_clubs;
};

int readFromInput(struct hand *A);

void printHand(struct hand A);

bool balanced(struct hand A);

int hcp(struct hand A);

int getOnerPoints(char *array, int n);

int declarer(struct hand A);

void response(struct hand A);

#endif
