#include <stdio.h>

int main(void) {

    int change;
    int coinCounter = 0;

    printf("Change Owed: ");
    scanf("%i", &change);

    if(change >= 25){
        while(change >= 25){
            change -= 25;
            coinCounter++;
        }
    }

    if(change >= 10){
        while(change >= 10){
            change -= 10;
            coinCounter++;
        }
    }

    if(change >= 5){
        while(change >= 5){
            change -= 5;
            coinCounter++;
        }
    }

    if(change >= 1){
        while(change >= 1){
            change -= 1;
            coinCounter++;
        }
    }

    printf("%i", coinCounter);
    printf("\n");
    
}