#include "windows.h"
#include "AustinPower.h"
#include <stdio.h>

void main(int argc, char **argv)
{

    if( argc != 3)
    {
        printf("AustinPower.exe <target> <inject-dll>\n");
        return ;
    }
    AustinPower	au;

    au.CreateAustinPower(argv[1], argv[2]);

}