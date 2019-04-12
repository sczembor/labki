//
//  structs.h
//  labolatorium_c_3
//
//  Created by Stanislaw Czembor on 29/03/2019.
//  Copyright © 2019 Stanislaw Czembor. All rights reserved.
//

#ifndef structs_h
#define structs_h

enum weekday {Pon=1,Wto,Sro,Czw,Pia,Sob,Nie};
typedef struct czas
{
    int hour;
    int min;
    
}czas;
typedef struct przerwa
{
    struct czas start;
    struct czas end;
    struct przerwa* nast;
}przerwa;
typedef struct workday
{
    int data;
    enum weekday dzien;
    struct czas pocz;
    struct czas koniec;
    struct przerwa* breakk;
    struct workday* next;
}workday;

#endif /* structs_h */
