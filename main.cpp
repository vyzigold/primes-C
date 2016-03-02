/* 
 * File:   main.cpp
 * Author: jarda
 *
 * Created on 28. listopad 2015, 20:04
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>

int kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
FILE *soubor;

    long long unsigned int maxGap=0;
    long long unsigned int gapAfter = 0;
    long long unsigned int afterIndex;
    long long unsigned int gapBefore = 0;
    long long unsigned int beforeIndex;
    long long unsigned int neco;
    
    long long unsigned int zkouseneCislo, delitel,vysledek,predtim,index;

void fce(void)
{
    if(soubor->_flags!=0)
        fclose(soubor);
    soubor = fopen("statistika.txt","w");
    fprintf(soubor,"pocet cisel = %llu\nnejvetsi mezera: %llu    mezi: %llu a %llu na indexech %llu a %llu",index,maxGap,gapBefore,gapAfter,beforeIndex,afterIndex);
    fclose(soubor);
    
    return;
}

int main(int argc, char** argv) {
    bool prime = false;
    soubor = fopen("seznam.txt","r");
    while(fscanf(soubor,"%llu; %llu",&index,&zkouseneCislo)>0);
    fclose(soubor);
    predtim = zkouseneCislo;
    while(!kbhit())
    {
        soubor = fopen("seznam.txt","r");
        fscanf(soubor,"%llu; %llu",&neco,&delitel);
        while(zkouseneCislo%delitel !=0)
        {
            vysledek = ceil(zkouseneCislo/delitel);
            fscanf(soubor,"%llu; %llu",&neco,&delitel);
            if(delitel>vysledek)
            {
                printf("%llu\n",zkouseneCislo);
                prime = true;
                break;
            }
        }
        fclose(soubor);
        soubor = fopen("seznam.txt","a+");
        if(prime)
        {
                fprintf(soubor,"%llu; %llu\n",index,zkouseneCislo);
                prime = false;
                if(zkouseneCislo-predtim>maxGap)
                {
                    maxGap=zkouseneCislo-predtim;
                    gapBefore = predtim;
                    gapAfter = zkouseneCislo;
                    beforeIndex = index-1;
                    afterIndex = index;
                }
            index++;
            predtim = zkouseneCislo;
        }
        zkouseneCislo+=2;
        fclose(soubor);
    }
    atexit(fce);
    return 0;
}

