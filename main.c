/*
  main.c
  base_64_projekt

  Created by Stanislaw Czembor on 18/04/2019.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*deklaracje funkcji*/
char* odczytPliku(char* nazwaPliku);
void kodowanieBase64(char* nazwaPliku,char* input);/*funkcja przyjmuje tekst do zakodowania i zwraca zakodowany ciag znakow*/
void dekodowanieBase64(char* nazwaPliku,char* input);/*funkcja przyjmuje tekst do odkodowania i zwraca rozkodowany ciag znakow*/
int zapisDoPliku(char* nazwaPliku,char* tekst);/*funckja przyjmuje docelowa nazwe pliku,zakodowany/rozkodowany ciag znakow. Nastepnie tworzy plik, zapisuje tekst i zwraca 1 jesli operacja sie powiodla i 0 jesli cos poszlo nie tak*/
int znajdzWartosc(char znak);
char zestawZnakow[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";/*zestaw znakow do konwersji base64*/
char* input;


int main(int argc, const char * argv[])
{
    char *nazwaPlikWe="domyslnyWe.txt", *nazwaPlikWy = "domyslnyWy.txt";
    int i;
    int k=0,d=0;
    if(argc<=6)
    {
        for(i = 1; i < argc ; i++)/*przelaczniki*/
        {
            if(!strcmp(argv[i],"-i"))/*plik wejsciowy*/
            {
                nazwaPlikWe = (char*)argv[i+1];
            }
            else if (!strcmp(argv[i],"-k"))/*konwersja na base64*/
            {
                k=1;
            }
            else if (!strcmp(argv[i],"-d"))/*konwersja na ASCII*/
            {
                d=1;
            }
            else if (!strcmp(argv[i],"-o"))/*plik wyjsciowy*/
            {
                nazwaPlikWy = (char*)argv[i+1];
            }
        }
        if (k==1)/*konwersja na base64*/
        {
            kodowanieBase64(nazwaPlikWy,odczytPliku(nazwaPlikWe));
        }
        else if (d==1)/*konwersja na ASCII*/
        {
            dekodowanieBase64(nazwaPlikWy,odczytPliku(nazwaPlikWe));
        }
        free(input);
    }
    else
    {
        printf("wprowadzono za dużo przełączników!\n");
    }
    return 0;
}
void kodowanieBase64(char* nazwaPliku,char* input)
{
    int dlInput= (int)strlen(input);/*dlugosc tekstu*/
    char* output = (char*) malloc((4*((dlInput+2)/3)+1)*sizeof(char));
    int i, j,licznik=0,indeks,bity,a=0;
    unsigned int k=0;
    for(i = 0; i<dlInput; i += 3 )
    {
        licznik =0;
        for(j = i; j<dlInput && j <= i +2; j++)
        {
            k = k << 8; /*przesuniecie bitow w lewo*/
            k = k | input[j]; /* operacja lub na bitach*/
            licznik++;
        }
        bity = licznik * 8;
        while (bity > 0)
        {

            if (bity >= 6)
            {
                indeks = (k >> (bity-6)) & 63;/*63 = 111111 odczytanie wartosci indeksow*/
                bity -= 6;
            }
            else
            {
                indeks = (k << (6-bity)) & 63;
                bity = 0;
            }
            output[a++] = zestawZnakow[indeks];
        }
    }
    for (i = 0; i <3-(dlInput%3) ; i++)
    {
        output[a++] = '=';
    }
    output[a] ='\0';
    zapisDoPliku(nazwaPliku, output);
    free(output);
}
void dekodowanieBase64(char* nazwaPliku,char* input)/*dzialaja maksymalnie 7 literowe*/
{
    int i,j,b;
    int dlInput= (int)strlen(input);/*dlugosc tekstu*/
    char* output = (char*) malloc(((dlInput*6)/8)*sizeof(char));
    int iloscBitow=0,indeks,a=0;
    unsigned int k =0;
    for(i = 0; i<dlInput;i+=4)
    {
        j=0;
        for(b=i; b<dlInput && b <= i+3; b++)
        {
            if(input[b]!='=')
            {
                k = k << 6;
                k = k | znajdzWartosc(input[b]);
                j++;
            }
        }
        iloscBitow = j*6;
        while(iloscBitow>0)
        {
            if(iloscBitow>=8)
            {
                indeks = (k>>(iloscBitow-8) & 255);/*255 = 11111111*/
                iloscBitow = iloscBitow -8;
            }
            else
            {
                indeks = (k<<(8-iloscBitow) & 255);/*255 = 11111111*/
                iloscBitow = 0;
            }
            output[a] = (char)indeks;
            a++;
        }
    }
    output[a] = '\0';
    zapisDoPliku(nazwaPliku, output);
    free(output);
}

int znajdzWartosc(char znak)
{
    int i=0;
    while(i<64)
    {
        if(zestawZnakow[i]==znak)
            return i;
        i++;
    }
    return -1;
}
int zapisDoPliku(char* nazwaPliku,char* tekst)
{
    FILE *fPlikWy = fopen(nazwaPliku, "w+");/*proba utworzenia nowego pliku*/
    if (fPlikWy != NULL)/*sprawdzam czy otwarcie pliku powiodlo sie*/
    {
        fprintf(fPlikWy,"%s",tekst);
        fclose(fPlikWy);/*zamykam plik*/
        return 1;/*zapis powiodl sie*/
    }
    else
    {
        printf("nie udało sie utworzyc pliku\n");
        return 0;
    }
}
char* odczytPliku(char* nazwaPliku)
{
    FILE *fPlikWe = fopen(nazwaPliku, "r");
    if(fPlikWe != NULL)
    {
        int dlInput;
        fseek(fPlikWe, 0, SEEK_END);/*ustwienie wskaznika na koniec pliku*/
        dlInput = ftell(fPlikWe);/*sprawdzenie ile bajtow od poczatku do konca*/
        input = (char*) malloc(dlInput*sizeof(char)+sizeof(char));
        fseek (fPlikWe, 0, SEEK_SET);/*ustawienie wskaznika na poczatek pliku*/
        if(input)
        {
            fread(input, sizeof(char), dlInput, fPlikWe);
        }
        fclose(fPlikWe);
        return input;
    }
    else
    {
        printf("nie udalo sie otworzyc pliku\n");
        return "0";
    }
}
                  
                  

