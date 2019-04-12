//
//  main.c
//  labolatorium_c_3
//
//  Created by Stanislaw Czembor on 29/03/2019.
//  Copyright © 2019 Stanislaw Czembor. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void dodajNaPoczatekDzien(struct workday **pGlowa);//dodaje nowy dzien na poczatek listy
void dodajNaPoczatekPrzerwe(struct przerwa **pGlowa);//dodaje nowa przerwe na poczatek listy podwieszanej
void wyswietlOdPoczatku(struct workday *pGlowa);//funkcja wyswietla liste od poczatku
const char* ZnajdzDzien(enum weekday dzien);//funkcja wyswietla nazwe dnia w zaleznosci od liczby
void usunListe(struct workday *pGlowa);//funkcja usuwa cala liste podwieszana
void sortowanie(workday **pHead);//funkcja sortuje liste wedlug czasu pracy rosnaca
void zamien(workday **p1,workday **p2);//funkcja zamienia wartosci w danym elemencie listy
int czasPracy(struct workday *pGlowa);//funkcja oblicza czas pracy w danym dniu
//void wczytajDane(void);
int main()
{
    workday* pHead=NULL;
    char wybor;
    printf("'d' - dodaj informacje o dniu pracy\n");
    printf("'s' - posortuj dni wedlug czasu pracy\n");
    printf("'p' - drukuj przebieg pracy\n");
    printf("'q' - zakoncz dzialanie programu\n");
    printf("wybierz: ");
    scanf(" %c",&wybor);
    while(wybor!='q')
    {
        if(wybor=='d')//dodaje dane o dniu pracy
        {
           dodajNaPoczatekDzien(&pHead);
        }
        else if(wybor=='s')//sotrtuje
        {
            sortowanie(&pHead);
        }
        else if(wybor=='p')//wyswietla na ekran
        {
            wyswietlOdPoczatku(pHead);
        }
        else//bledny wybor
        {

        }
        printf("wybierz: ");
        scanf(" %c",&wybor);
    }
    usunListe(pHead);
   return 0;
}
void dodajNaPoczatekDzien(struct workday **pGlowa)
{
    workday *temp = (workday*)malloc(sizeof(struct workday));
    int x;
    int pom;
    printf("\nwprowadz date:(MM) ");
    scanf("%d",&x);
    temp->data = x;
    printf("\npodaj dzien:(1-7 wprowadz jeden dla poniedzialku) ");
    scanf("%d",&x);
    temp->dzien = x;
    printf("\npodaj godzine rozpoczecia:(GGMM  wprowadz 1320 dla 13:20) ");
    scanf("%d",&x);
    temp->pocz.hour = (int)(x/100);
    pom = (int)(x/100);
    temp->pocz.min = (int)(x-(100*pom));
    printf("\nwprowadz godzine zakonczenia:(GGMM) ");
    scanf("%d",&x);
    temp->koniec.hour = (int)(x/100);
    pom = (int)(x/100);
    temp->koniec.min = (int)(x-(100*pom));
    char c;
    przerwa* pPrzerwa = NULL;
    do{
        dodajNaPoczatekPrzerwe(&pPrzerwa);
        printf("\nChcesz dodac nastepna przerwe? t/n :" );
        scanf(" %c",&c);
    }while(c=='t');
    temp->breakk=pPrzerwa;
    temp->next=*pGlowa;
    *pGlowa = temp;
}
void dodajNaPoczatekPrzerwe(struct przerwa **pGlowa)
{
    int x,pom;
    przerwa *temp1 =(przerwa*)malloc(sizeof(struct przerwa));
    printf("\nwprowadz godzine rozpoczecia przerwy:(GGMM) ");
    scanf("%d",&x);
    temp1->start.hour = (int)(x/100);
    pom = (int)(x/100);
    temp1->start.min = (int)(x-(100*pom));
    printf("\nwprowadz godzine zakonczenia przerwy:(GGMM) ");
    scanf("%d",&x);
    temp1->end.hour = (int)(x/100);
    pom = (int)(x/100);
    temp1->end.min = (int)(x-(100*pom));
    temp1->nast = *pGlowa;
    *pGlowa = temp1;
}
void wyswietlOdPoczatku(struct workday *pGlowa)
{
    while(pGlowa!=NULL)
    {
        printf("%d ",pGlowa->data);
        if(pGlowa->dzien>=1 && pGlowa->dzien<=7)
            printf("%s",ZnajdzDzien(pGlowa->dzien));
        printf(" od %d:%d do %d:%d przerwy: ",pGlowa->pocz.hour,pGlowa->pocz.min,pGlowa->koniec.hour,pGlowa->koniec.min);
        przerwa* pPrzerwa = pGlowa->breakk;
        
        while(pPrzerwa!=NULL)
        {
            printf("od %d:%d do %d:%d \n",pPrzerwa->start.hour,pPrzerwa->start.min,pPrzerwa->end.hour,pPrzerwa->end.min);
            pPrzerwa = pPrzerwa->nast;
            
        }
        pGlowa = pGlowa ->next;
    }
}
const char* ZnajdzDzien(enum weekday dzien)
{
    switch (dzien)
    {
        case Pon: return "Poniedzialek";
        case Wto: return "Wtorek";
        case Sro: return "Sroda";
        case Czw: return "Czwartek";
        case Pia: return "Piatek";
        case Sob: return "Sobota";
        case Nie: return "Niedziela";
    }
}
void usunListe(struct workday *pGlowa)
{
    if(!pGlowa)
        return;
    workday* pom = NULL;
    przerwa* pom1 = NULL;
    przerwa* pPrzerwa = pGlowa->breakk;
    while(pGlowa)
    {
        while(pPrzerwa)
        {
            pom1 =pPrzerwa->nast;
            free(pPrzerwa);
            pPrzerwa = pom1;
        }
        pom = pGlowa->next;
        free(pGlowa);
        pGlowa = pom;
    }
}
void sortowanie(workday **pHead)
{
    workday *pTemp = *pHead;
    workday *pPomocnik;
    workday *min;
    while(pTemp && pTemp->next)
    {
        min = pTemp;
        pPomocnik = pTemp->next;
        
        while(pPomocnik)
        {
        /* Find minimum element from array */
            if(czasPracy(min) > czasPracy(pPomocnik))
            {
                min = pPomocnik;
            }
            
            pPomocnik = pPomocnik->next;
        }
        zamien(&pTemp,&min);            // Put minimum element on starting location
        pTemp = pTemp->next;
    }
}

/* swap data field of linked list */
void zamien(workday **p1,workday **p2)
{
    int temp = (*p1)->data;
    (*p1)->data = (*p2)->data;
    (*p2)->data = temp;
    enum weekday temp1 = (*p1)->dzien;
    (*p1)->dzien = (*p2)->dzien;
    (*p2)->dzien = temp1;
    temp = (*p1)->pocz.hour;
    (*p1)->pocz.hour = (*p2)->pocz.hour;
    (*p2)->pocz.hour = temp;
    temp = (*p1)->pocz.min;//
    (*p1)->pocz.min = (*p2)->pocz.min;
    (*p2)->pocz.min = temp;
    temp = (*p1)->koniec.hour;
    (*p1)->koniec.hour = (*p2)->koniec.hour;
    (*p2)->koniec.hour = temp;
    temp = (*p1)->koniec.min;
    (*p1)->koniec.min = (*p2)->koniec.min;
    (*p2)->koniec.min = temp;
    przerwa* pTemp = (*p1)->breakk;
    (*p1)->breakk = (*p2)->breakk;
    (*p2)->breakk = pTemp;
//    workday* pTemp1 = (*p1)->next;
//    (*p1)->next = (*p2);
//    (*p2)->next = pTemp1;
    
}
int czasPracy(struct workday *pGlowa)
{   int czasPrzerwy = 0;
    przerwa* pTemp = pGlowa->breakk;
    while(pTemp)
    {
        czasPrzerwy=+(pTemp->end.hour*60+pTemp->end.min)-(pTemp->start.hour*60+pTemp->start.min);
        pTemp = pTemp->nast;
    }
    return (pGlowa->koniec.hour*60+pGlowa->koniec.min)-(pGlowa->pocz.hour*60+pGlowa->pocz.min)-czasPrzerwy;
}
//void wczytajDane(void)
//{
//    char nazwaPliku[] = "week1.txt";
//    FILE *plik = fopen ( nazwaPliku, "r" );
//
//    if (plik != NULL) {
//        int data,pocz_hour,pocz_min,koniec_hour,koniec_min;
//        char dzien[100000];
//        fscanf(plik,"%d, %3s, %d, %d, %d",&data,dzien,&pocz_hour,&pocz_min,&koniec_hour,&koniec_min);
//
//
//        printf("%d pocz: %d:%d koniec:%d:%d\n",data,pocz_hour,pocz_min,koniec_hour,koniec_min);
//
//        fclose(plik);
//    }
//    else {
//        printf("nie udało się otworzyc pliku");
//    }
//}
