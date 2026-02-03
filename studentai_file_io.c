/*Author: Mintautas Šatas INFO group I
  Version: 2.0
  Description: Data manager for university students, which can store student 
  name, student surname, course and grade. Additional functionality includes
  sorting and filtering.
  
  Date: 2026-01-22*/


#include <stdio.h>
#include <stdlib.h>
#include "studentai_file_io.h"

void saugoti_i_faila(){
    FILE *fp = fopen("studentai.bin", "wb");
    if(fp == NULL){
        printf("Klaida atidarant faila studentai.bin\n");
        return;
    }

    fwrite(&studentai.kiekis, sizeof(int), 1, fp);
    fwrite(studentai.duomenys, sizeof(Studentas), studentai.kiekis, fp);

    fclose(fp);
    printf("Studentu duomenys issaugoti faile sekmingai.\n");
}
void skaityti_is_failo(){
    FILE *fp = fopen("studentai.bin", "rb");
    if(fp == NULL){
        printf("Klaida atidarant faila studentai.bin\n");
        return;
    }
    int nuskaityas_kiekis;
    fread(&nuskaityas_kiekis, sizeof(int), 1, fp);
    while(studentai.talpa < nuskaityas_kiekis){
        padidinti_talpa();
    }
    fread(studentai.duomenys, sizeof(Studentas), nuskaityas_kiekis, fp);
    studentai.kiekis = nuskaityas_kiekis;

    fclose(fp);
    printf("Studentu duomenys nuskaityti is failo sekmingai.\n");
}