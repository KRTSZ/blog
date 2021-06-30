#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isJpg(string);
int writeJpg(int);

int main(int argc, char *argv[])
{
 if (argc > 2)
 {
     printf("Please write just: recover filename\n");
     return 1;
 }

 FILE *raw = NULL;
 int count = 0;

 if ( !(raw = fopen(argv[1], "r")))
 {
     printf("Couldn't open file.\n");
     return 1;
 }

 raw = fopen(argv[1],"r");

 string tmp[512] = {0};
 fread(tmp[], 512, number, raw);
 if (isJpg(tmp[]))
 {
     writeJpg(count);
     count++;
 }
 return 0;
}

bool isJpg(string)
{
    if ((int)tmp[0] == 0xff)
    {
        if ((int)tmp[1] == 0xd8)
        {
            if ((int)tmp[2] == 0xff)
            {
                if (((int)tmp[3] >= 0xe0) && ((int)tmp[3] <= 0xef))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int writejpg(int);
{
    string FileName = combine(tmp, count + ".jpg");
    File.Create(Filename);
    return 0;
}
