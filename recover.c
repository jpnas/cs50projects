#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    FILE *f = fopen(argv[1], "r");

    //Counter and variable for the JPEG file name
    int count = 0;
    char filename[8];
    
    // Creating the buffer for the bytes
    BYTE buffer[512];
    
    //Pointer to the JPEG file
    FILE *img;
    
    
    while (fread(buffer, sizeof(buffer), 1, f) == 1)
    {
        //Checking if the header is indicating a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Check if it is the first JPEG and start writing
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(buffer), 1, img);
                count++;
            }
            //If it is not the first, close the current file and start the next
            else if (count > 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(buffer), 1, img);
                count++;
            }
        }
        //If the header doesn't indicate a new JPEG, keep writing the current file
        else if (count > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }


    }
    fclose(img);
    fclose(f);
    return 0;
}
