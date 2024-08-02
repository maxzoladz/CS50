#include <stdio.h>

int main(void)
{
   int height;

   //Frage nach einem int Wert für die Höhe der Pyramide
   do
   {
    printf("Enter Height: ");
    scanf("%i", &height);
   } while (height < 1 || height > 8);

   int spaces = height - 1;

   // Pyramide wird erstellt
   for(int i = 0; i < height; i++)
   {

    //Loop um die Spaces für die linksseitige Pyramide zu generieren
    for(int j = 0; j <= spaces; j++)   
    {
        printf(" ");
    }
    
    spaces--;

    // Loop für linksseitige Pyramide
    for(int k = 0; k < i + 1; k++)
    {
        printf("#");
    }

    // Space zwischen beiden Pyramiden
    printf("  "); 

    // Loop für rechtsseitige Pyramide
    for(int m = 0; m < i + 1; m++)
    {
        printf("#");
    }
    printf("\n");
   }
}