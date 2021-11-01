#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct _osoba {
    char ime[MAX];
    char prezime[MAX];
    int godina;
    struct _osoba* next;

} osoba;

int UnosPocetak(osoba*);
int Ispis(osoba*);
int UnosKraj(osoba*);
osoba* PronadiZadnji(osoba*);
osoba* PronadiPrezime(osoba* ,char*);
osoba* PronadiPrethodni(osoba*, osoba*);
int ObrisiElement(osoba* ,osoba*);


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

    while(odabir != 0){

        printf("Odaberite koju radnju zelite napraviti: \n");
        printf("0 - Prekid");
        printf("1 - Dinamički dodaje element na pocetak liste \n");
        printf("2 - Ispis liste \n");
        printf("3 - Dinamicki dodaje element na kraj liste \n");
        printf("4 - Pronalazi element liste(po prezimenu) \n");
        printf("5 - Brise odredeni element iz liste \n");

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
        else{
        printf("Kriv unos");
        }
    }
    
    return 0;
}

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
