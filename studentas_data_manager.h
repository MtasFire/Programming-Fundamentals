#ifndef STUDENTAI_DATA_MANAGER_H
#define STUDENTAI_DATA_MANAGER_H

#define INITIAL_CAPACITY 10
#define CAPACITY_INCREMENT 5

typedef struct{
    char vardas[30];
    char pavarde[30];
    int kursas;
    double vidurkis;
} Studentas;

typedef struct{
    Studentas *duomenys;
    int kiekis;
    int talpa;
} StudentuMasyvas;

extern StudentuMasyvas studentai;

int vardo_tikrinimas(const char *vardas);
int kurso_tikrinimas(int kursas);
int vidurkio_tikrinimas(double vidurkis);

void prideti_studenta(void);
void listinti_studentus(void);
void trinti_studenta(void);
void redaguoti_studenta(void);

void saugoti_i_faila(void);
void skaityti_is_failo(void);
void meniu(void);

void init_masyvas(void);
void free_masyvas(void);
void padidinti_talpa(void);

void filtruoti_pagal_varda(void);
void filtruoti_pagal_pavarde(void);
void filtruoti_pagal_kursa(void);
void filtruoti_pagal_vidurki(void);

void filtruoti_studenta(void);

void paleisti_testus(void);
void test_vardo_tikrinimas(void);
void test_kurso_tikrinimas(void);
void test_vidurkio_tikrinimas(void);
#endif