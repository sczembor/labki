//
//  main.c
//  labolatorium_c_2
//
//  Created by Stanislaw Czembor on 15/03/2019.
//  Copyright © 2019 Stanislaw Czembor. All rights reserved.
//  wczytac dwie liczby i miedzy tymi liczbami znalezc parę liczb które są liczbami pierwszmi
// stworzyc tablice dwuwymiarowa i do kazdego wiersza wpisac dzielniki kazdej liczby z zakresu
// nastepnie sprawdzic czy jakies dzielniki sie nie powtarzaja i wypisywac wszystkie pary które są wzglednie pierwsze


// podaje liczby od x1 do x2 sito eratostenesa
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"




int main()
{
    int x1, x2;
    printf("Podaj dolny zakres: ");
    scanf("%d",&x1);
    printf("Podaj gorny zakres: ");
    scanf("%d",&x2);
    int ilosc = 0;
    printf("\n\nPary liczb względnie pierwszych:\n");
    
    for(int i = x1; i<=x2; i++)
    {
        for(int j = i; j<=x2; j++)
        {
            if(wzgledniePierwsze(i,j)==1)//sprawdzenie wszyskich par liczb z zakresu oraz wyswietlenie tych ktore sa wzglednie pierwsze
            {
                ilosc ++;
                printf("%d - %d\n",i,j);
            }
        }
    }
    printf("Ilość par liczb względnie pierwszych: %d\n\n",ilosc);
    
    sitoErastotenesa(x1, x2);
    
    
    
   
    return 0;
}
