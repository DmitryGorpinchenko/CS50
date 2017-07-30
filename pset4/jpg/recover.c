/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 512

int main(int argc, char* argv[])
{
    FILE* file = fopen("card.raw", "r");
    
    uint8_t block[BLOCK_SIZE];
    
    int jpgs = 0;
    
    FILE* jpg = NULL;
    
    while(fread(block, BLOCK_SIZE, 1, file) == 1)
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            char filename[8];
            sprintf(filename, "%.3i.jpg", jpgs);
            
            if (jpg != NULL)
            {
                fclose(jpg);
            }
            
            jpg = fopen(filename, "w");
            jpgs++;
            fwrite(block, BLOCK_SIZE, 1, jpg);
        }
        else if(jpgs)
        {
            fwrite(block, BLOCK_SIZE, 1, jpg);
        }
    }
    fclose(jpg);
    fclose(file);
}
