#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

//DEKLARACIJA STRUKTRUE

typedef struct _osoba {
    char ime[MAX];
    char prezime[MAX];
    int godina;
    struct _osoba* next;

} osoba;

//DEKLARACIJA FUNCKIJE

int UnosPocetak(osoba*);
int Ispis(osoba*);
int UnosKraj(osoba*);
osoba* PronadiZadnji(osoba*);
osoba* PronadiPrezime(osoba* ,char*);
osoba* PronadiPrethodni(osoba*, osoba*);
int ObrisiElement(osoba* , osoba*);
int DodajIzaElementa(osoba*, osoba*);
int DodajIspredElementa(osoba* , osoba*);
int UpisUDatoteku(osoba*);
int CitanjeIzDatoteke(osoba*);


int main(){

    osoba* head;
    head = (osoba*)malloc(sizeof(osoba));
    head -> next = NULL;

    int odabir;

    char prezime[MAX];
    osoba* nadi_prezime = NULL;
    nadi_prezime = (osoba*)malloc(sizeof(osoba));

    char obrisi[MAX];
    osoba* obrisi_element = NULL;
    obrisi_element = (osoba*)malloc(sizeof(osoba));

    char iza[MAX];
    osoba* dodaj_iza = NULL;
    dodaj_iza = (osoba*)malloc(sizeof(osoba));

    char ispred[MAX];
    osoba* dodaj_ispred = NULL;
    dodaj_ispred = (osoba*)malloc(sizeof(osoba));

    //ODABIR RADNJE

    while(odabir != 0){

        printf("Odaberite koju radnju zelite napraviti: \n");
        printf("0 - Prekid");
        printf("1 - Dinamički dodaje element na pocetak liste \n");
        printf("2 - Ispis liste \n");
        printf("3 - Dinamicki dodaje element na kraj liste \n");
        printf("4 - Pronalazi element liste(po prezimenu) \n");
        printf("5 - Brise odredeni element iz liste \n");
        printf("6 - Dodaje element iza odredenog elementa \n");
        printf("7 - Dodaje novi element ispred odredenog elementa \n");
        printf("8 - Sortitranje lste \n");
        printf("9 - Upisuje Listu u datoteku \n");
        printf("10 - Citanje liste iz datoteke \n");

        printf("Odabir: ");
        scanf("%d", &odabir);

        if(odabir == 0){
            printf("Prekid");
            break;
        }
        else if(odabir == 1){
                UnosPocetak(head);
                break;
        }
        else if(odabir == 2){
                Ispis(head);
                break;
        }
        else if(odabir == 3){
                UnosKraj(head);
                break;
         }
        else if(odabir == 4){
                printf("Koje prezime zelize pronaci: ");
                scanf("%s", prezime);
                nadi_prezime = PronadiPrezime(head, prezime);
                printf("Osoba koju ste trazili:\n Ime: %s \nPrezime: %s\nGodina rodenja: %d\n", nadi_prezime->ime, nadi_prezime->prezime, nadi_prezime->godina);
                break;
        }
        else if(odabir == 5){
                printf("Koji element liste zelite obrisati: ");
                scanf("%s", obrisi);
                obrisi_element = PronadiPrezime(head, obrisi);
                ObrisiElement(head,obrisi_element);
                break;
        }
        else if(odabir == 6){
                printf("Iza kojeg elementa zelite dodati element: ");
                scanf("%s", iza);
                dodaj_iza = PronadiPrezime(head, iza);
                DodajIzaElementa(head, dodaj_iza);
                break;
        }
        else if(odabir == 7){
            printf("Ispred kojeg elementa zelite dodati element: ");
            scanf("%s", ispred);
            dodaj_ispred = PronadiPrezime(head, ispred);
            DodajIspredElementa(head, dodaj_ispred);
            break;
        }
        else if(odabir == 9){
            UpisUDatoteku(head);
        }
        else if(odabir == 10){
            CitanjeIzDatoteke(head);
            break;
        }
        else{
        printf("Kriv unos");
        }
    }
    
    return 0;
}

//REALIZACIJA FUNCKIJA

int UnosPocetak(osoba* head)
{
    osoba* o;
    o = (osoba*)malloc(sizeof(osoba));

    o->next = head->next;
    head->next = o;

    printf("Unesite podatke: \n");
    printf("Ime: ");
    scanf(" %s", o->ime);
    printf("\nPrezime: ");
    scanf(" %s", o->prezime);
    printf("\n Godina rodenja: ");
    scanf("%d", &o->godina);
    printf("\n");

    return 0;
}

int Ispis(osoba* head)
{   
    osoba* o = head->next;

    if(head->next == NULL){
        printf("\nLista je prazna");
        return -1;
    }

    while(o->next != NULL){
            printf("\tIme: %s \n", o->ime);
            printf("\tPrezime: %s \n", o->prezime);
            printf("\tGodina rodenja: %d \n", o->godina);
            printf("\n");
            o = o->next;
    }

    return 0;
}

int UnosKraj(osoba* head)
{
    osoba* o;
    o = (osoba*)malloc(sizeof(osoba));

    osoba* p;
    p = (osoba*)malloc(sizeof(osoba));

    p = PronadiZadnji(head);

    o->next = NULL;
    p->next = o;

    printf("Unesite podatke: \n");
    printf("Ime: ");
    scanf(" %s", o->ime);
    printf("\nPrezime: ");
    scanf(" %s", o->prezime);
    printf("\n Godina rodenja: ");
    scanf("%d", &o->godina);
    printf("\n");

}

osoba* PronadiZadnji(osoba* head)
{
    osoba* p = head;

    while(p != NULL && p->next != NULL){
        p = p->next;
    }

    return p;
}

osoba* PronadiPrezime(osoba* head ,char* prezime)
{
    osoba* p = head->next;

    while(p != NULL && strcmp(p->prezime,prezime))
        p = p->next;
    
    return p;
}

int ObrisiElement(osoba* head, osoba* element)
{
    osoba* p = NULL;
    osoba* q = NULL;
    
    p = (osoba*)malloc(sizeof(osoba));
    q = (osoba*)malloc(sizeof(osoba));

    q = element;

    p = PronadiPrethodni(head, element);

    p->next = q->next;

    free(q);

    return 0;
}

osoba* PronadiPrethodni(osoba* head, osoba* element)
{

    osoba* p;
    
    p = head;

    while(p != NULL && p->next != element)
        p = p->next;

    return p;
}

int DodajIzaElementa(osoba* head, osoba* element)
{
    osoba* nova;
    nova = (osoba*)malloc(sizeof(osoba));

    printf("Unesite podatke: \n");
    printf("Ime: ");
    scanf(" %s", nova->ime);
    printf("\nPrezime: ");
    scanf(" %s", nova->prezime);
    printf("\n Godina rodenja: ");
    scanf("%d", &nova->godina);
    printf("\n");

    nova->next = element->next;
    element->next = nova;

    return 0;
}

int DodajIspredElementa(osoba* head, osoba* element)
{
    osoba* nova;
    nova = (osoba*)malloc(sizeof(osoba));

    osoba* p;
    p = (osoba*)malloc(sizeof(osoba));

    p = PronadiPrezime(head, element);

    printf("Unesite podatke: \n");
    printf("Ime: ");
    scanf(" %s", nova->ime);
    printf("\nPrezime: ");
    scanf(" %s", nova->prezime);
    printf("\n Godina rodenja: ");
    scanf("%d", &nova->godina);
    printf("\n");

    p->next = nova;
    nova->next = element;

}

int UpisUDatoteku(osoba* head)
{
    osoba* q = NULL;
    q = (osoba*)malloc(sizeof(osoba));
    q = head->next;


    FILE* fp = NULL;
    fp = fopen("osoba1.txt", "w");

    if(fp == NULL){
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    while(q != NULL){
        fprintf(fp, "Ime: %s \n Prezime: %s \n Godina rodenja: %d \n", q->ime, q->prezime, q->godina);
        q = q->next;
    }

    fclose(fp);

    return 0;
}


int CitanjeIzDatoteke(osoba* head)
{
    int i, br;
    char buffer[MAX] = { 0 };
    osoba* q;
    osoba* p = PronadiZadnji(head);

    FILE* fp = NULL;
    fp = fopen("osoba.txt", "r");

    if(fp == NULL){
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    while(fgets(buffer, MAX, fp)){
        br++;
    }

    for(i = 0; i < br; i++){
        q = (osoba*)malloc(sizeof(osoba));

        q->next = NULL;
        p->next = q;
        p = p->next;

        fscanf(fp," %s %s %d", q->ime, q->prezime, &q->godina);
    }

    fclose(fp);

    return 0;
}
