#include <stdio.h>
#include <string.h>
#include <math.h>

int countLetters(char text[]);
int countWords(char text[]);
int countSentences(char text[]);


int main(void) {

    char text[1000];

    printf("Enter Text: ");
    fgets(text, sizeof(text), stdin);

    int letters = countLetters(text);
    int words = countWords(text);
    int sentences = countSentences(text);

    int index = roundf(0.0588 * (((float) letters / (float) words) * 100.0) - 0.296 * (((float) sentences / (float) words) * 100.0) - 15.8);

    if(index >= 16) {
        printf("Grade 16+\n");
    }
    else if(index < 1) {
        printf("Before Grade 1\n");
    }
    else {
        printf("Grade %i\n", index);
    }

}

int countLetters(char text[]) {

    int length = strlen(text);
    int count = 0;

    for(int i = 0; i < length; i++) {
        if((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a'&& text[i]<= 'z')) {
            count++;
        }
    }
    return count;

}

int countWords(char text[]) {

    int length = strlen(text);
    int count = 0;

    for(int i = 0; i < length; i++) {
        if(text[i] == 32) {
            count++;
        }
    }

    if(count == 0) {
        count++;
    }

    return count += 1;

}

int countSentences(char text[]) {

    int length = strlen(text);
    int count = 0;

    for(int i = 0; i< length; i++) {
        if(text[i] == 33 || text[i] == 63 || text[i] == 46) {
            count++;
        }
    }

    return count;

}