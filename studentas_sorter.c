/*Author: Mintautas Šatas INFO group I
  Version: 2.0
  Description: Data manager for university students, which can store student 
  name, student surname, course and grade. Additional functionality includes
  sorting and filtering.
  
  Date: 2026-01-22*/


#include <stdio.h>
#include <string.h>
#include "studentas_sorter.h"

void sukeisti_studentus(Studentas *a, Studentas *b){
    Studentas temp = *a;
    *a = *b;
    *b = temp;
}

void rikiuoti_pagal_varda(void){
    if(studentai.kiekis == 0){
        printf("Nera pridetu studentu.\n");
        return;
    }

    for(int i = 0; i < studentai.kiekis - 1; i++){
        for(int j = 0; j < studentai.kiekis - i - 1; j++){
            if(strcmp(studentai.duomenys[j].vardas, studentai.duomenys[j + 1].vardas) > 0){
                sukeisti_studentus(&studentai.duomenys[j], &studentai.duomenys[j + 1]);
            }
        }
    }
    printf("Studentai surikiuoti pagal varda(A-Z).\n");
    listinti_studentus();
}
void rikiuoti_pagal_pavarde(void){
    if(studentai.kiekis == 0){
        printf("Nera pridetu studentu.\n");
        return;
    }

    for(int i = 0; i < studentai.kiekis - 1; i++){
        for(int j = 0; j < studentai.kiekis - i - 1; j++){
            if(strcmp(studentai.duomenys[j].pavarde, studentai.duomenys[j + 1].pavarde) > 0){
                sukeisti_studentus(&studentai.duomenys[j], &studentai.duomenys[j + 1]);
            }
        }
    }
    printf("Studentai surikiuoti pagal pavarde(A-Z).\n");
    listinti_studentus();
}

void rikiuoti_pagal_kursa(void){
    if(studentai.kiekis == 0){
        printf("Nera pridetu studentu.\n");
        return;
    }

    for(int i = 0; i < studentai.kiekis - 1; i++){
        for(int j = 0; j < studentai.kiekis - i - 1; j++){
            if(studentai.duomenys[j].kursas > studentai.duomenys[j + 1].kursas){
                sukeisti_studentus(&studentai.duomenys[j], &studentai.duomenys[j + 1]);
            }
        }
    }
    printf("Studentai surikiuoti pagal kursa(didejancia tvarka).\n");
    listinti_studentus();
}

void rikiuoti_pagal_vidurki(void){
    if(studentai.kiekis == 0){
        printf("Nera pridetu studentu.\n");
        return;
    }

    for(int i = 0; i < studentai.kiekis - 1; i++){
        for(int j = 0; j < studentai.kiekis - i - 1; j++){
            if(studentai.duomenys[j].vidurkis > studentai.duomenys[j + 1].vidurkis){
                sukeisti_studentus(&studentai.duomenys[j], &studentai.duomenys[j + 1]);
            }
        }
    }
    printf("Studentai surikiuoti pagal vidurki(didejancia tvarka).\n");
    listinti_studentus();
}

void rikiuoti_studentus(void){
    int pasirinkimas;
    printf("Pasirinkite rikiavimo kriteriju:\n");
    printf("1. Pagal varda\n");
    printf("2. Pagal pavarde\n");
    printf("3. Pagal kursa\n");
    printf("4. Pagal vidurki\n");
    printf("Jusu pasirinkimas: ");
    scanf("%d", &pasirinkimas);

    switch(pasirinkimas){
        case 1:
            rikiuoti_pagal_varda();
            break;
        case 2:
            rikiuoti_pagal_pavarde();
            break;
        case 3:
            rikiuoti_pagal_kursa();
            break;
        case 4:
            rikiuoti_pagal_vidurki();
            break;
        default:
            printf("Neteisingas pasirinkimas.\n");
    }
}