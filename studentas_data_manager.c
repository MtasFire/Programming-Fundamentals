/*Author: Mintautas Šatas INFO group I
  Version: 2.0
  Description: Data manager for university students, which can store student 
  name, student surname, course and grade. Additional functionality includes
  sorting and filtering.
  
  Date: 2026-01-22*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdarg.h>
#include "studentai_file_io.h"
#include "studentas_data_manager.h"
#include "studentas_sorter.h"

static const char *LOG_FILE = "program.log";
static time_t g_start_time;

static void log_event(const char *event, ...){
    FILE *log_fp = fopen(LOG_FILE, "a");
    if(log_fp == NULL){
        printf("Klaida atidarant log faila.\n");
        return;
    }
    time_t now = time(NULL);
#ifdef _WIN32
    struct tm tmNow;
    localtime_s(&tmNow, &now);
    fprintf(log_fp, "[%04d-%02d-%02d %02d:%02d:%02d] ",
        tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday,
        tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);
#else
    struct tm *tmNow = localtime(&now);
    fprintf(log_fp, "[%04d-%02d-%02d %02d:%02d:%02d] ",
        tmNow->tm_year + 1900, tmNow->tm_mon + 1, tmNow->tm_mday,
        tmNow->tm_hour, tmNow->tm_min, tmNow->tm_sec);
#endif
    va_list args;
    va_start(args, event);
    vfprintf(log_fp, event, args);
    va_end(args);
    fputc('\n', log_fp);
    fclose(log_fp);
}
static void on_exit_log(void){
    time_t end = time(NULL);
    double secs = difftime(end, g_start_time);
    int hours = (int)(secs / 3600);
    int minutes = (int)((secs - hours * 3600) / 60);
    int seconds = (int)(secs - hours * 3600 - minutes * 60);
    log_event("Programos veikimo laikas: %02d:%02d:%02d", hours, minutes, seconds);
}

StudentuMasyvas studentai;



int main(){
    init_masyvas();
    time(&g_start_time);
    atexit(on_exit_log);
    log_event("Programa paleista.");
    meniu();
    free_masyvas();
    return 0;
}

void test_vardo_tikrinimas(){
    printf("Testuojama vardo_tikrinimas funkcija:\n");
    assert(vardo_tikrinimas("Jonas") == 1);
    assert(vardo_tikrinimas("jonas") == 0);
    assert(vardo_tikrinimas("J0nas") == 0);
    assert(vardo_tikrinimas("") == 0);
}
void test_kurso_tikrinimas(){
    printf("Testuojama kurso_tikrinimas funkcija:\n");
    assert(kurso_tikrinimas(1) == 1);
    assert(kurso_tikrinimas(6) == 1);
    assert(kurso_tikrinimas(0) == 0);
    assert(kurso_tikrinimas(7) == 0);
}

void test_vidurkio_tikrinimas(){
    printf("Testuojama vidurkio_tikrinimas funkcija:\n");
    assert(vidurkio_tikrinimas(0.0) == 1);
    assert(vidurkio_tikrinimas(10.0) == 1);
    assert(vidurkio_tikrinimas(-1.0) == 0);
    assert(vidurkio_tikrinimas(11.0) == 0);
}

void paleisti_testus(){
    test_vardo_tikrinimas();
    test_kurso_tikrinimas();
    test_vidurkio_tikrinimas();
    printf("Visi testai sekmingai ivykdyti.\n");
}

void init_masyvas(){
    studentai.duomenys = (Studentas*)malloc(INITIAL_CAPACITY * sizeof(Studentas));
    if(studentai.duomenys == NULL){
        printf("Klaida skiriant atmintyje pradiniam studentu masyvui.\n");
        exit(1);
    }
    studentai.kiekis = 0;
    studentai.talpa = INITIAL_CAPACITY;
}

void free_masyvas(){
    free(studentai.duomenys);
    studentai.duomenys = NULL;
    studentai.kiekis = 0;
    studentai.talpa = 0;
}

void padidinti_talpa(){
    studentai.talpa += CAPACITY_INCREMENT;
    Studentas *naujas = (Studentas*)realloc(studentai.duomenys, studentai.talpa * sizeof(Studentas));
    if(naujas == NULL){
        printf("Klaida didinant studentu masyvo talpa.\n");
        exit(1);
    }
    studentai.duomenys = naujas;
}


int vardo_tikrinimas(const char *vardas){
    if(strlen(vardas) == 0) return 0;
    if(!isupper(vardas[0])) return 0;

    for (int i = 1; vardas[i] != '\0'; i++){
        if(!isalpha(vardas[i])) return 0;
    }
    return 1;
}

int kurso_tikrinimas(int kursas){
    if(kursas >= 1 && kursas <= 6) return 1;
    else return 0;
}

int vidurkio_tikrinimas(double vidurkis){
    if(vidurkis >= 0.0 && vidurkis <= 10.0) return 1;
    else return 0;
}

void prideti_studenta(){
    if (studentai.kiekis >= studentai.talpa){
        padidinti_talpa();
    }

 Studentas s;

 do {
    printf("Vardas: ");
    scanf("%s", s.vardas);
    if(!vardo_tikrinimas(s.vardas)){
        printf("Neteisingas vardas. Bandykite dar karta.\n");
    }
 } while (!vardo_tikrinimas(s.vardas));

 do {
    printf("Pavarde: ");
    scanf("%s", s.pavarde);
    if(!vardo_tikrinimas(s.pavarde)){
        printf("Neteisinga pavarde. Bandykite dar karta.\n");
    }
 } while (!vardo_tikrinimas(s.pavarde));

 do {
    printf("Kursas (1-6): ");
    int result = scanf("%d", &s.kursas);
    if (result != 1) {
        while(getchar() != '\n');
        printf("Neteisingas kursas. Bandykite dar karta.\n");
        s.kursas = 0;
    } else if (!kurso_tikrinimas(s.kursas)){
        printf("Neteisingas kursas. Bandykite dar karta.\n");
    }
 } while (!kurso_tikrinimas(s.kursas));
 do {
    printf("Vidurkis (0.0-10.0): ");
    int result = scanf("%lf", &s.vidurkis);
    if (result != 1) {
        while(getchar() != '\n');
        printf("Neteisingas vidurkis. Bandykite dar karta.\n");
        s.vidurkis = -1.0;
    } else if (!vidurkio_tikrinimas(s.vidurkis)){
        printf("Neteisingas vidurkis. Bandykite dar karta.\n");
    }
 } while (!vidurkio_tikrinimas(s.vidurkis));

 studentai.duomenys[studentai.kiekis++] = s;
 printf("Studentas pridetas sekmingai.\n");


}

void listinti_studentus(){
    if(studentai.kiekis == 0){
        printf("Nera pridetu studentu.\n");
        return;
    }

    printf("Prideti studentai:\n");
    for(int i = 0; i < studentai.kiekis; i++){
        printf("%d. %s %s, Kursas: %d, Vidurkis: %.2f\n", 
               i + 1, 
               studentai.duomenys[i].vardas, 
               studentai.duomenys[i].pavarde, 
               studentai.duomenys[i].kursas, 
               studentai.duomenys[i].vidurkis);
    }
}

void trinti_studenta() {
    int skaicius;
    printf("Iveskite studento numeri, kuri norite istrinti: ");
    scanf("%d", &skaicius);
    skaicius--;
    if (skaicius < 0 || skaicius >= studentai.kiekis) {
        printf("Neteisingas studento numeris.\n");
        return;
    }
    for (int i = skaicius; i < studentai.kiekis - 1; i++) {
        studentai.duomenys[i] = studentai.duomenys[i + 1];
    }
    studentai.kiekis--;
    printf("Studentas istrintas sekmingai.\n");
}

void redaguoti_studenta(){

    int skaicius;
    printf("Iveskite studento numeri, kuri norite redaguoti: ");
    int result = scanf("%d", &skaicius);
    if(result != 1){
        while(getchar() != '\n'); // Clear invalid input
        printf("Neteisingas studento numeris.\n");
        return;
    }
    skaicius--;

    if (skaicius < 0 || skaicius >= studentai.kiekis) {
        printf("Neteisingas studento numeris.\n");
        return;
    }
    Studentas *s = &studentai.duomenys[skaicius];
    printf("Esamas vardas: %s\n Naujas vardas: ", s->vardas);
    scanf("%s", s->vardas);
    while (!vardo_tikrinimas(s->vardas)) {
        printf("Neteisingas vardas. Bandykite dar karta: ");
        scanf("%s", s->vardas);
    }


    printf("Esama pavarde: %s\n Nauja pavarde: ", s->pavarde);
    scanf("%s", s->pavarde);
    while (!vardo_tikrinimas(s->pavarde)) {
        printf("Neteisinga pavarde. Bandykite dar karta: ");
        scanf("%s", s->pavarde);
    }
    do {
        printf("Esamas kursas: %d\n Naujas kursas (1-6): ", s->kursas);
        int result = scanf("%d", &s->kursas);
        if (result != 1) {
            while(getchar() != '\n'); // Clear invalid input
            printf("Neteisingas kursas. Bandykite dar karta: ");
            s->kursas = 0;
        } else if (!kurso_tikrinimas(s->kursas)) {
            printf("Neteisingas kursas. Bandykite dar karta: ");
        }
    } while (!kurso_tikrinimas(s->kursas));
    do {
    printf("Esamas vidurkis: %.2f\n Naujas vidurkis (0.0-10.0): ", s->vidurkis);
    int result = scanf("%lf", &s->vidurkis);
    if (result != 1) {
        while(getchar() != '\n'); // Clear invalid input
        printf("Neteisingas vidurkis. Bandykite dar karta.\n");
        s->vidurkis = -1.0;
    } else if (!vidurkio_tikrinimas(s->vidurkis)){
        printf("Neteisingas vidurkis. Bandykite dar karta.\n");
    }
    } while (!vidurkio_tikrinimas(s->vidurkis));

    printf("Studento duomenys atnaujinti sekmingai.\n");
}

void filtruoti_pagal_varda(void){
    if(studentai.kiekis == 0){
        printf("Nera pridetu studentu.\n");
        return;
    }
    char ieskomas_vardas[30];
    printf("Iveskite varda, pagal kuri filtruoti: ");
    scanf("%s", ieskomas_vardas);

    int rasta=0;
    printf("Studentai su vardu %s:\n", ieskomas_vardas);
    for(int i = 0; i < studentai.kiekis; i++){
        if(strcmp(studentai.duomenys[i].vardas, ieskomas_vardas) == 0){
            printf("%d. %s %s, Kursas: %d, Vidurkis: %.2f\n", 
                   i + 1, 
                   studentai.duomenys[i].vardas, 
                   studentai.duomenys[i].pavarde, 
                   studentai.duomenys[i].kursas, 
                   studentai.duomenys[i].vidurkis);
            rasta = 1;
        }
    }
    if(!rasta){
        printf("Nerasta studentu su vardu %s.\n", ieskomas_vardas);
    }
}

void filtruoti_pagal_pavarde(void){
    if(studentai.kiekis == 0){
        printf("Nera pridetu studentu.\n");
        return;
    }
    char ieskoma_pavarde[30];
    printf("Iveskite pavarde, pagal kuria filtruoti: ");
    scanf("%s", ieskoma_pavarde);

    int rasta=0;
    printf("Studentai su pavarde %s:\n", ieskoma_pavarde);
    for(int i = 0; i < studentai.kiekis; i++){
        if(strcmp(studentai.duomenys[i].pavarde, ieskoma_pavarde) == 0){
            printf("%d. %s %s, Kursas: %d, Vidurkis: %.2f\n", 
                   i + 1, 
                   studentai.duomenys[i].vardas, 
                   studentai.duomenys[i].pavarde, 
                   studentai.duomenys[i].kursas, 
                   studentai.duomenys[i].vidurkis);
            rasta = 1;
        }
    }
    if(!rasta){
        printf("Nerasta studentu su pavarde %s.\n", ieskoma_pavarde);
    }
}

void filtruoti_pagal_kursa(void){
    if(studentai.kiekis == 0){
        printf("Nera pridetu studentu.\n");
        return;
    }
    int kursas_nuo, kursas_iki;
    printf("Iveskite kursu intervala pvz (1 3) arba (1 1): ");
    scanf("%d %d", &kursas_nuo, &kursas_iki);
    if (kursas_nuo > kursas_iki || !kurso_tikrinimas(kursas_nuo) || !kurso_tikrinimas(kursas_iki)){
        printf("Neteisingas kursu intervalas.\n");
        return;
    }

    int rasta=0;
    printf("Studentai kurso %d-%d:\n", kursas_nuo, kursas_iki);
    for(int i = 0; i < studentai.kiekis; i++){
        if(studentai.duomenys[i].kursas >= kursas_nuo && 
            studentai.duomenys[i].kursas <= kursas_iki){
            printf("%d. %s %s, Kursas: %d, Vidurkis: %.2f\n", 
                   i + 1, 
                   studentai.duomenys[i].vardas, 
                   studentai.duomenys[i].pavarde, 
                   studentai.duomenys[i].kursas, 
                   studentai.duomenys[i].vidurkis);
            rasta = 1;
        }
    }
    if(!rasta){
        printf("Nerasta studentu kurso %d-%d.\n", kursas_nuo, kursas_iki);
    }
}
void filtruoti_pagal_vidurki(void){
    if(studentai.kiekis == 0){
        printf("Nera pridetu studentu.\n");
        return;
    }
    double vidurkis_nuo, vidurkis_iki;
    printf("Iveskite vidurkiu intervala pvz (5.0 8.0) arba (7.5 7.5): ");
    scanf("%lf %lf", &vidurkis_nuo, &vidurkis_iki);
    if (vidurkis_nuo > vidurkis_iki || !vidurkio_tikrinimas(vidurkis_nuo) || !vidurkio_tikrinimas(vidurkis_iki)){
        printf("Neteisingas vidurkiu intervalas.\n");
        return;
    }

    int rasta=0;
    printf("Studentai su vidurkiu %.2f-%.2f:\n", vidurkis_nuo, vidurkis_iki);
    for(int i = 0; i < studentai.kiekis; i++){
        if(studentai.duomenys[i].vidurkis >= vidurkis_nuo && 
            studentai.duomenys[i].vidurkis <= vidurkis_iki){
            printf("%d. %s %s, Kursas: %d, Vidurkis: %.2f\n", 
                   i + 1, 
                   studentai.duomenys[i].vardas, 
                   studentai.duomenys[i].pavarde, 
                   studentai.duomenys[i].kursas, 
                   studentai.duomenys[i].vidurkis);
            rasta = 1;
        }
    }
    if(!rasta){
        printf("Nerasta studentu su vidurkiu %.2f-%.2f.\n", vidurkis_nuo, vidurkis_iki);
    }
}
void filtruoti_studenta(){
    int pasirinkimas;
    printf("Pasirinkite filtravimo kriteriju:\n");
    printf("1. Pagal varda\n");
    printf("2. Pagal pavarde\n");
    printf("3. Pagal kursa\n");
    printf("4. Pagal vidurki\n");
    printf("Jusu pasirinkimas: ");
    scanf("%d", &pasirinkimas);

    switch(pasirinkimas){
        case 1:
            filtruoti_pagal_varda();
            break;
        case 2:
            filtruoti_pagal_pavarde();
            break;
        case 3:
            filtruoti_pagal_kursa();
            break;
        case 4:
            filtruoti_pagal_vidurki();
            break;
        default:
            printf("Neteisingas pasirinkimas.\n");
    }
}

void meniu(){
    int pasirinkimas;
    do {
        printf("\n--- Studentu Valdymo Sistema ---\n");
        printf("1. Prideti studenta\n");
        printf("2. Listinti studentus\n");
        printf("3. Redaguoti studenta\n");
        printf("4. Trinti studenta\n");
        printf("5. Filtruoti studentus\n");
        printf("6. Rikiuoti studentus\n");
        printf("7. Saugoti i faila\n");
        printf("8. Skaityti is failo\n");
        printf("9. Paleisti testus\n");
        printf("0. Iseiti\n");
        printf("Pasirinkite veiksma: ");
        scanf("%d", &pasirinkimas);

        switch(pasirinkimas){
            case 1:
                prideti_studenta();
                break;
            case 2:
                listinti_studentus();
                break;
            case 3:
                redaguoti_studenta();
                break;
            case 4:
                trinti_studenta();
                break;
            case 5:
                filtruoti_studenta();
                break;
            case 6:
                rikiuoti_studentus();
                break;
            case 7:
                saugoti_i_faila();
                break;
            case 8:
                skaityti_is_failo();
                break;
            case 9:
                paleisti_testus();
                break;
            case 0:
                printf("Iseinama is programos.\n");
                break;
            default:
                printf("Neteisingas pasirinkimas. Bandykite dar karta.\n");
        }
    } while(pasirinkimas != 0);
}