#include <stdio.h>
#include <string.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int toUpper(char word[]);
int score(char word[]);

int main(void) {

    char firstWord[50];
    printf("Player 1: ");
    scanf("%s", firstWord);

    char secondWord[50];
    printf("Player 2: ");
    scanf("%s", secondWord);

    printf("Player 1: %s, Player 2: %s\n", firstWord, secondWord);

    toUpper(firstWord);
    toUpper(secondWord);

    int score1 = score(firstWord);
    int score2 = score(secondWord);

    if(score1 > score2) {
        printf("Player 1 wins!\n");
    }
    else if(score1 < score2) {
        printf("Player 2 wins!\n");
    }
    else {
        printf("Tie!\n");
    }

}

int toUpper(char s[]) {

    int length = strlen(s);

    for(int i = 0; i < length; i++) {
        
        if(s[i] >= 'a') {
            s[i] = s[i] - 32;
        }
    }
    return 0;
}

int score(char word[]) {

    int length = strlen(word);
    int score = 0;

    for(int i = 0; i < length; i++) {
       score = score + points[word[i] - 'A'];
    }
    return score; 
}
