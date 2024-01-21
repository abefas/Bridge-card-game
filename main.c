#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include "project2023a.h"
#define MAX 100

int main()
{
    int n=0,i,temp;
    struct hand A[MAX];
    char k,c;
    do
    {
        printf("What would you like to do?\n");
        scanf(" %c",&k);
        switch (k)
        {
            case 'i': n = readFromInput(A);
                break;
            case 's': 
                printf("Which hand would you like to see?\n");
                scanf ("%d",&i);
                if (i>=0 && i<n)
                    printHand(A[i]);
                printf ("\n");
                break;
            case 'r': 
                printf("Which hand would you like to check for response?\n");
                scanf ("%d",&i);
                if (i>=0 && i<n)
                    response(A[i]);
                printf ("\n");
                break;
            case 'p': 
                printf("Which hand would you like to check for points?\n");
                scanf ("%d",&i);
                if (i>=0 && i<n)
                {
                    temp = hcp(A[i]);
                    printf ("%d HCP (%d total)\n",temp,temp+declarer(A[i]));
                }
                printf ("\n");
                break;
            case 'd': 
                printf("Which hand would you like to check for balance?\n");
                scanf ("%d",&i);
                if (i>=0 && i<n)
                {
                    if (balanced(A[i]))
                        printf ("Balanced distribution\n");
                    else
                        printf ("Unbalanced distribution\n");
                }
                printf ("\n");
                break;
        }
    }
    while (k!='q');
    return 0;
}

void response(struct hand A){
    bool bal = balanced(A);
    int onerPoints = hcp(A);

    if(bal && onerPoints >= 15 && onerPoints <= 17){
        printf("1NT\n");
    }else if(bal && onerPoints >= 20 && onerPoints <= 21){
        printf("2NT\n");
    }else if(onerPoints >= 22){
        printf("2 CLUBS\n");
    }else if(onerPoints < 22 && onerPoints + declarer(A) >= 13){
        if(A.n_spades >= 5 && A.n_hearts <= 5){
            printf("1 SPADES\n");
        }else if(A.n_hearts >= 5 && A.n_spades < A.n_hearts){
            printf("1 HEARTS\n");
        }else if(A.n_diamonds >= 4 && A.n_spades < 5 && A.n_hearts < 5 && A.n_clubs < 5){
            printf("1 DIAMONDS\n");
        }else if(A.n_spades < 5 && A.n_hearts < 5 && A.n_diamonds < 4){
            printf("1 CLUBS");
        }
    }else if(onerPoints + declarer(A) < 13){
        printf("PASS\n");
    }
    return;
}

int getOnerPoints(char *array, int n){
    int points = 0, i = 0;
    while(i < n){
        switch(array[i]){
            case 'A': points += 4;
                break;
            case 'K': points += 3;
                break;
            case 'Q': points += 2;
                break;
            case 'J': points += 1;
                break;
        }
        i++;
    }
    
    return points;
}

int hcp(struct hand A){
    int points = 0;
    points += getOnerPoints(A.spades, A.n_spades);
    points += getOnerPoints(A.hearts, A.n_hearts);
    points += getOnerPoints(A.diamonds, A.n_diamonds);
    points += getOnerPoints(A.clubs, A.n_clubs);
    return points;
}


int declarer(struct hand A){
    int points = 0;
    if(A.n_spades - 4 > 0)
        points += A.n_spades - 4;

    if(A.n_hearts - 4 > 0)
        points += A.n_hearts - 4;

    if(A.n_diamonds - 4 > 0)
        points += A.n_diamonds - 4;

    if(A.n_clubs - 4 > 0)
        points += A.n_clubs - 4;

    return points;    
}

bool balanced(struct hand A){

    int i = 0, check = 0, cards2 = 0;

    //check spades
    while(i < A.n_spades){
        check++;
        i++;
    }
    //first condition
    if(check < 2) return false;
    //second condition
    if(check == 2) cards2++;
    
    //check hearts
    i = 0, check = 0;
    while(i < A.n_hearts){
        check++;
        i++;
    }
    if(check < 2) return false;
    if(check == 2){
        cards2++;
        if(cards2 > 1) return false;
    }

    //check diamonds
    i = 0, check = 0;
    while(i < A.n_diamonds){
        check++;
        i++;
    }
    if(check < 2) return false;
    if(check == 2){
        cards2++;
        if(cards2 > 1) return false;
    }

    //check clubs
    i = 0, check = 0;
    while(i < A.n_clubs){
        check++;
        i++;
    }
    if(check < 2) return false;
    if(check == 2){
        cards2++;
        if(cards2 > 1) return false;
    }

    return true;
}

int readFromInput(struct hand *A){
    int n;
    printf("Input number of hands: ");
    scanf("%d", &n);
    getchar();

    for(int i = 0; i < n; i++){
        A[i].n_spades = A[i].n_hearts = A[i].n_diamonds = A[i].n_clubs = 0;
        char input[39]; //13 cards + spaces
        printf("Input hand number %d:", i+1);
        fgets(input, sizeof(input), stdin);
        getchar();
        char *token = strtok(input, " ");
        int counter[4] = {0};   //keep track of how many of each symbols the hand has
        while(token != NULL) {
            switch(token[1]){
                case 'S':
                    A[i].spades[counter[0]] = token[0];
                    counter[0]++;
                    A[i].n_spades++;
                    break;

                case 'H':
                    A[i].hearts[counter[1]] = token[0];
                    counter[1]++;
                    A[i].n_hearts++;
                    break;

                case 'D':
                    A[i].diamonds[counter[2]] = token[0];
                    counter[2]++;
                    A[i].n_diamonds++;
                    break;

                case 'C':
                    A[i].clubs[counter[3]] = token[0];
                    counter[3]++;
                    A[i].n_clubs++;
                    break;

            }
            token = strtok(NULL, " ");  // Get the next token
        }
    }
    return n; 
}

void printHand(struct hand A){

    int counter = 0;

    printf("SPADES:\t\t");
    for(int i = 0; i < A.n_spades; i++){
        printf("%c ", A.spades[i]);
    }

    printf("\nHEARTS:\t\t");
    for(int i = 0; i < A.n_hearts; i++){
        printf("%c ", A.hearts[i]);
    }

    printf("\nDIAMONDS:\t");
    for(int i = 0; i < A.n_diamonds; i++){
        printf("%c ", A.diamonds[i]);
    }

    printf("\nCLUBS:\t\t");
    for(int i = 0; i < A.n_clubs; i++){
        printf("%c ", A.clubs[i]);
    }

    return;
}
