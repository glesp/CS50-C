#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


bool found_jpeg = false;
char filename[8];
FILE *img = NULL;
int counter = 0;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }


    FILE *card = fopen(argv[1], "r");
    if(card == NULL)
    {
        printf("Couldn't find file");
    }

    uint8_t buffer[512];

    // jpeg signature bits = 0xff 0xd8 0xff and 0xe0 to 0xef
    // ie. 11111111 11011000 11111111 1110 in binary
    // 1111111111011000111111111110 - total 28 bits

    while(fread(buffer, 1, 512, card))
    {

        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            found_jpeg = true;
        }
        if(found_jpeg == true)
        {
            if(counter != 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            fwrite(buffer, 1, 512, img);
            found_jpeg = false;
            counter++;
        }
        else if(counter != 0)
        {
            fwrite(buffer, 1, 512, img);
        }



    }
    fclose(img);
    fclose(card);

}

