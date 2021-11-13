#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define M 50
#define MAX 1024

struct _Polinom;
typedef struct _Polinom *Pozicija;
typedef struct _Polinom
{
    int koef;
    int eksp;
    Pozicija next;
} polinom;


int UcitajIzDatoteke(Pozicija p1, Pozicija p2);                     
int UnosUListu(Pozicija head, char *red);                          
int Sortiranje(Pozicija head);                                  
int IspisiPolinom(Pozicija prvi);                                    
int ZbrojiPolinome(Pozicija head1, Pozicija head2, Pozicija headzb); 
int ViseElemenataSIstimEksp(Pozicija prvi, Pozicija head);
Pozicija PronadiPrethodnog(Pozicija head, int eksp);
int PomnoziPolinome(Pozicija head1, Pozicija head2, Pozicija headumn);

int main()
{
    polinom head1 = {.koef = 0, .eksp = 0, .next = NULL};
    polinom head2 = {.koef = 0, .eksp = 0, .next = NULL};
    polinom headZbroj = {.koef = 0, .eksp = 0, .next = NULL};
    polinom headUmnozak = {.koef = 0, .eksp = 0, .next = NULL};
    Pozicija p1 = &head1;
    Pozicija p2 = &head2;
    Pozicija p_zbr = &headZbroj;
    Pozicija p_umn = &headUmnozak;
    int a = 0;
    a = UcitajIzDatoteke(p1, p2);
    if (a == EXIT_FAILURE)
    {
        return 0;
    }
    Sortiranje(p1);
    ViseElemenataSIstimEksp(p1->next, p1);
    Sortiranje(p2);
    ViseElemenataSIstimEksp(p2->next, p2);
    printf("\nPRVI POLINOM...\n");
    IspisiPolinom(p1->next);
    printf("\nDRUGI POLINOM...\n");
    IspisiPolinom(p2->next);
    ZbrojiPolinome(p1, p2, p_zbr);
    Sortiranje(p_zbr);
    ViseElemenataSIstimEksp(p_zbr->next, p_zbr);
    printf("\nZROJ DVA POLINOMA...\n");
    IspisiPolinom(p_zbr->next);
    PomnoziPolinome(p1, p2, p_umn);
    Sortiranje(p_umn);
    ViseElemenataSIstimEksp(p_umn->next, p_umn);
    printf("\nUMNOZAK DVA POLINOMA...\n");
    IspisiPolinom(p_umn->next);

    return EXIT_SUCCESS;
}

int UcitajIzDatoteke(Pozicija p1, Pozicija p2)
{
    FILE *fp = NULL;
    char dat[M] = {0};
    char red[MAX] = {0};
    int status = 0;
    printf("\nIz koje datoteke zelite ucitati polinome?\n");
    scanf(" %s", dat);
    fp = fopen(dat, "r");
    if (fp == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke %s !\n", dat);
        return EXIT_FAILURE;
    }
    fgets(red, MAX, fp); //UPISIVANJE U PRVU LISTU
    status = UnosUListu(p1, red);
    if (status != EXIT_SUCCESS)
    {
        printf("\nGRESKA U UPISIVANJU PRVOG POLINOMA U LISTU\n\n");
        return -5;
    }
    fgets(red, MAX, fp); //UPISIVANJE U DRUGU LISTU
    status = UnosUListu(p2, red);
    if (status != EXIT_SUCCESS)
    {
        printf("\nGRESKA U UPISIVANJU DRUGOG POLINOMA U LISTU\n\n");
        return -5;
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int UnosUListu(Pozicija head, char *red)
{
    int koef_pom = 0;
    int ekspo_pom = 0;
    int bajtovi = 0;
    int status = 2;
    char *pomoc = red;
    Pozicija Novi_Element = NULL;
    while (strlen(pomoc) > 0)
    {
        status = sscanf(pomoc, " %d %d %n", &koef_pom, &ekspo_pom, &bajtovi);
        if (status != 2)
        {
            return EXIT_FAILURE;
        }
        Novi_Element = (Pozicija)malloc(sizeof(polinom));
        if (!Novi_Element)
        {
            perror("\nAlokacija memorije neuspjesna!\n");
            return EXIT_FAILURE;
        }
        Novi_Element->eksp = ekspo_pom;
        Novi_Element->koef = koef_pom;
        Novi_Element->next = head->next;
        head->next = Novi_Element;
        pomoc += bajtovi;
    }

    return EXIT_SUCCESS;
}

int Sortiranje(Pozicija head)
{
    Pozicija i = NULL, j = NULL, prosli_j = NULL, pomoc = NULL, kraj = NULL;
    i = head;
    while (i->next != kraj)
    {
        prosli_j = i;
        j = i->next;
        while (j->next != kraj)
        {
            if (j->eksp > j->next->eksp)
            {
                pomoc = j->next;
                prosli_j->next = pomoc;
                j->next = pomoc->next;
                pomoc->next = j;
                j = pomoc;
            }
            prosli_j = j;
            j = j->next;
        }
        kraj = j;
    }

    return EXIT_SUCCESS;
}

int IspisiPolinom(Pozicija prvi)
{
    Pozicija pomoc = NULL;
    pomoc = prvi;
    int brojac = 0;
    do
    {
        if (brojac != 0)
        {
            if (pomoc->koef >= 0)
            {
                printf("  +  ");
            }
            else
            {
                printf("  -  ");
            }
        }
        if (pomoc->eksp >= 0)
        {
            printf("%dx^%d", abs(pomoc->koef), pomoc->eksp);
        }
        else
        {
            printf("%dx^(%d)", abs(pomoc->koef), pomoc->eksp);
        }
        pomoc = pomoc->next;
        brojac++;
    } while (pomoc != NULL);
    printf("\n");

    return EXIT_SUCCESS;
}
int ZbrojiPolinome(Pozicija head1, Pozicija head2, Pozicija headzb)
{
    Pozicija pom1 = NULL;
    Pozicija pom2 = NULL;
    Pozicija Novi_Element = NULL;
    for (pom1 = head1->next; pom1 != NULL; pom1 = pom1->next)
    {
        Novi_Element = (Pozicija)malloc(sizeof(polinom));
        if (!Novi_Element)
        {
            perror("\nAlokacija memorije neuspjesna!\n");
            return EXIT_FAILURE;
        }
        Novi_Element->eksp = pom1->eksp;
        Novi_Element->koef = pom1->koef;
        Novi_Element->next = headzb->next;
        headzb->next = Novi_Element;
    }
    for (pom2 = head2->next; pom2 != NULL; pom2 = pom2->next)
    {
        Novi_Element = (Pozicija)malloc(sizeof(polinom));
        if (!Novi_Element)
        {
            perror("\nAlokacija memorije neuspjesna!\n");
            return EXIT_FAILURE;
        }
        Novi_Element->eksp = pom2->eksp;
        Novi_Element->koef = pom2->koef;
        Novi_Element->next = headzb->next;
        headzb->next = Novi_Element;
    }

    return EXIT_SUCCESS;
}

int ViseElemenataSIstimEksp(Pozicija prvi, Pozicija head)
{
    Pozicija pomoc = NULL;
    Pozicija Prethodni = NULL;
    Pozicija Novi_Element = NULL;
    for (pomoc = prvi; pomoc->next != NULL; pomoc = pomoc->next)
    {
        if (pomoc->eksp == pomoc->next->eksp)
        {
            Novi_Element = (Pozicija)malloc(sizeof(polinom));
            if (!Novi_Element)
            {
                perror("\nAlokacija memorije neuspjesna!\n");
                return EXIT_FAILURE;
            }
            Prethodni = PronadiPrethodnog(head, pomoc->eksp);
            Novi_Element->eksp = pomoc->eksp;
            Novi_Element->koef = pomoc->koef + pomoc->next->koef;
            Novi_Element->next = pomoc->next->next;
            Prethodni->next = Novi_Element;
        }
    }

    return EXIT_SUCCESS;
}

Pozicija PronadiPrethodnog(Pozicija head, int eksp)
{
    Pozicija prosli = NULL, trenutni = NULL;
    prosli = head;
    trenutni = prosli->next;
    while (trenutni != NULL && trenutni->eksp != eksp)
    {
        prosli = trenutni;
        trenutni = prosli->next;
    }
    if (trenutni == NULL)
    {
        return NULL;
    }

    return prosli;
}

int PomnoziPolinome(Pozicija head1, Pozicija head2, Pozicija headumn)
{
    Pozicija pom1 = NULL;
    Pozicija pom2 = NULL;
    Pozicija Novi_Element = NULL;
    for (pom1 = head1->next; pom1 != NULL; pom1 = pom1->next)
    {
        for (pom2 = head2->next; pom2 != NULL; pom2 = pom2->next)
        {
            Novi_Element = (Pozicija)malloc(sizeof(polinom));
            if (!Novi_Element)
            {
                perror("\nAlokacija memorije neuspjesna!\n");
                return EXIT_FAILURE;
            }
            Novi_Element->eksp = pom1->eksp + pom2->eksp;
            Novi_Element->koef = pom1->koef * pom2->koef;
            Novi_Element->next = headumn->next;
            headumn->next = Novi_Element;
        }
    }

    return EXIT_SUCCESS;
}