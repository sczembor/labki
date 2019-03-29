//
//  functions.c
//  labolatorium_c_2
//
//  Created by Stanislaw Czembor on 15/03/2019.
//  Copyright © 2019 Stanislaw Czembor. All rights reserved.
//

#include "functions.h"

int wzgledniePierwsze(int a, int b)
{
    int rozmiarTab1 = 0;
    int n = a;
    int k =2;
    while(n>1)
    {
        while(n%k==0) //dopóki liczba jest podzielna przez k
        {
            rozmiarTab1 ++;
            n/=k;
        }
        ++k;
    }
    int *arr1 = malloc(sizeof(int)*rozmiarTab1);
    rozmiarTab1 = 0;
    n = a;
    k =2;
    while(n>1)
    {
        while(n%k==0) //dopóki liczba jest podzielna przez k
        {
            arr1[rozmiarTab1] = k;
            rozmiarTab1++;
            n/=k;
        }
        ++k;
    }
    n=b;
    k=2;
    int rozmiarTab2 = 0;
    while(n>1)
    {
        while(n%k==0) //dopóki liczba jest podzielna przez k
        {
            rozmiarTab2 ++;
            n/=k;
        }
        ++k;
    }
    int *arr2 = malloc(sizeof(int)*rozmiarTab2);
    rozmiarTab2 = 0;
    n = b;
    k =2;
    while(n>1)
    {
        while(n%k==0) //dopóki liczba jest podzielna przez k
        {
            arr2[rozmiarTab2] = k;
            rozmiarTab2++;
            n/=k;
        }
        ++k;
    }
    for(int a = 0;a<rozmiarTab1;a++)//porownywanie po kolei wszytkich czynnikow liczb
    {
        for(int b=0;b<rozmiarTab2;b++)
        {
            if(arr1[a]==arr2[b])
            {
                free(arr1);
                free(arr2);
                return 0;
            }
        }
    }
    free(arr1);//zwolnienie pamieci
    free(arr2);
    
    return 1;
}
void sitoErastotenesa(int a,int b)
{
    int *arr = malloc(sizeof(int)*(b+1));
    
    for(int i =0; i<=b;i++)//ustawiam wszystkie komorki tablicy na wartosc jeden. jeden oznacza liczbe pierwsza
    {
        arr[i] = 1;
    }
    arr[0] = arr[1 ]= 0;//ustawiam 1 i 2 na 0 co oznacza ze liczby nie sa pierwszymi
    for(int i = 2; i<=b;i++)
        if(arr[i]==1)
        {
            for(int j =2;j<=b;j++)
            {
                arr[i*j]=0;//ustawiam wszystkie wielokrotnosci liczb ktore nie sa pierwsze na 0
            }
        }
    printf("\n\nliczby pierwsze z przedzialu od %d do %d :\n",a,b);
    for(int i=a;i<=b;i++)//wyswietlam liczby z przedzialu o ktore prosil uzytkownik
    {
        if(arr[i]==1)
        {
            printf("%d\t",i);
        }
    }
    free(arr);//zwolnienie pamieci
}
