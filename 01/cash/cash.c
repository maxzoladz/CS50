#include <stdio.h>

int main(void) {

    int change;
    int coinCounter = 0;

    printf("Change Owed: ");
    scanf("%i", &change);

        while(change >= 25){
            change -= 25;
            coinCounter++;
        }

        while(change >= 10){
            change -= 10;
            coinCounter++;
        }

        while(change >= 5){
            change -= 5;
            coinCounter++;
        }

        while(change >= 1){
            change -= 1;
            coinCounter++;
        }

    printf("%i", coinCounter);
    printf("\n");

}