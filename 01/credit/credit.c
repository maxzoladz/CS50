#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){

    long long int cardNumberInt;
    printf("Number: ");
    scanf("%lld", &cardNumberInt);

    int length = floor(log10(llabs(cardNumberInt))) + 1;

    if(length < 13 || length > 16 || length == 14){
        printf("INVALID");
    }
    else{
        char cardNumber[length];
        sprintf(cardNumber, "%lld", cardNumberInt);

        int checksum = 0;

        printf("Length: %lu", sizeof(cardNumber));

        printf("\n");

        for(int i = length - 2; i >= 0; i -= 2){
            if((cardNumber[i] - 48) * 2 >= 10){
                checksum = checksum + ((((cardNumber[i] - 48) * 2) / 10) + (((cardNumber[i] - 48) * 2) % 10));
            }
            else{
                checksum = checksum + (cardNumber[i] - 48) * 2;
            }
        }

        for(int j = length - 1; j >= 0; j -= 2){
            checksum = checksum + (cardNumber[j] - 48);
        }

        printf("Checksum: %i", checksum);

        printf("\n");

        if(checksum % 10 == 0){
            printf("Carrier: ");
            if(length == 15 && (cardNumberInt / 100000000000000 == 34 || cardNumberInt / 100000000000000 == 37)){
                printf("AMEX\n");
            }
            else if((length == 16 || length == 13) && cardNumberInt / 1000000000000000 == 4){
                printf("VISA\n");
            }
            else if(length == 16 && (cardNumberInt / 100000000000000 >= 51 && cardNumberInt / 100 <= 55)){
                printf("MASTERCARD");
            }
        }
        else{
            printf("INVALID");
        }
    }

    printf("\n");
    
}