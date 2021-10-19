#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX 1024
#define M 64

typedef struct _Stud {
    char ime[M];
    char prezime[M];
    double bodovi;
} student;


int BrojStudenata(char*);          //Racuna broj studenata
double RelativniBodovi(double, double);    //Racuna relativne bodove

int main()
{

    int br_Stud = 0;
    int i;
    double max_bodovi = 0;
    student* s = NULL;          //inicijaliziraj!
    char dat[M] = { 0 };        //inicijaliziraj na 0!!
    FILE* fp = NULL;
    char IME[M] = { "IME" },
        PREZIME[M] = { "PREZIME" },
        Bd1[M] = { "BODOVI(apsolutno)" },
        Bd2[M] = { "BODOVI(relativno)" };

    printf("\nUnesite naziv datoteke koju zelite procitati:\t");
    scanf(" %s", &dat);

    br_Stud = BrojStudenata(dat);

    printf("\nUkupan broj studenata je %d\n", br_Stud);

    fp = fopen(dat, "r");
    s = (student*)malloc(br_Stud * sizeof(student));

    for (i = 0; i < br_Stud; i++)    //ucitavanje podataka studenata
    {
        fscanf(fp, "%s %s %lf", s[i].ime, s[i].prezime, &s[i].bodovi);
    }

    for (i = 0; i < br_Stud; i++)    //pronalazi maksimalan broj bodova
    {
        if (s[i].bodovi >= max_bodovi)
        {
            max_bodovi = s[i].bodovi;
        }
    }

    printf("%-25s %-25s %-25s %-25s\n\n", IME, PREZIME, Bd1, Bd2);

    for (i = 0; i < br_Stud; i++)
    {
        double rel_bod = 0.0;
        rel_bod = RelativniBodovi(s[i].bodovi, max_bodovi);
        printf("\n%-25s %-25s %-25.2lf %-25.2lf ", s[i].ime, s[i].prezime, s[i].bodovi, rel_bod);
    }

    fclose(fp);             //funkciju za zatvaranje datoteke napisat cim je otvorimo

    printf("\n\n");

    return 0;
}

int BrojStudenata(char* dat)
{
    int br = 0;
    char red[MAX] = { 0 };      //inicijaliziraj opet sve
    FILE* fp = NULL;

    fp = fopen(dat, "r");

    if (fp == NULL)
    {
        printf("\nGreska pri otvaranju datoteke -> %s\n", dat);
        return -1;
    }
    while (!feof(fp))
    {
        fgets(red, MAX, fp);
       
    }
    fclose(fp);    //napisi funkciju za zatvaranje datoteke cim je otvoris

    return br;
}
double RelativniBodovi(double x, double y)
{
    double bod = 0.0;

    bod = (x / y) * 100;

    return bod;
}