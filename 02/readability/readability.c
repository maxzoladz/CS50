#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

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

    int gradeLevel = roundf(0.0588 * (((float) letters / (float) words) * 100.0) - 0.296 * (((float) sentences / (float) words) * 100.0) - 15.8);

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

    int textLength = strlen(text);
    int count = 0;

    for(int textIndex = 0; textIndex < textLength; textIndex++) {
        bool characterIsAlphabetical = (text[textIndex] >= 'A' && text[textIndex] <= 'Z') || (text[textIndex] >= 'a'&& text[textIndex] <= 'z');

        if(characterIsAlphabetical) {
            count++;
        }
    }

    return count;
}

int countWords(char text[]) {

    int textLength = strlen(text);
    int count = 0;

    for(int textIndex = 0; textIndex < textLength; textIndex++) {
        
        bool characterIsSpace = text[textIndex] == ' ';

        if(characterIsSpace) count++;
    }

    if(count == 0) count++;

    return count += 1;
}

int countSentences(char text[]) {

    int textLength = strlen(text);
    int count = 0;

    for(int textIndex = 0; textIndex< textLength; textIndex++) {

        bool characterIsExclamationMark = text[textIndex] == '!';
        bool characterIsQuestionMark = text[textIndex] == '?';
        bool characterIsPeriod = text[textIndex] == '.';

        if(characterIsExclamationMark || characterIsQuestionMark || characterIsPeriod) {
            count++;
        }
    }

    return count;
}