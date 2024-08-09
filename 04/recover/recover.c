#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    int blockSize = 512;
    u_int8_t buffer[blockSize];
    FILE *output = NULL;
    int picture = 0;

    while(fread(buffer, 1, 512, card) == 512) {

        bool isJPEG = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef);

        if(isJPEG){
            
            if(output != NULL) fclose(output);

            sprintf(argv[1], "%03i.jpg", picture);
            output = fopen(argv[1], "w");
            picture++;
        }
        
        if(output != NULL) fwrite(buffer, 1, blockSize, output);
    }

    if (output != NULL) fclose(output);

    fclose(card);
}