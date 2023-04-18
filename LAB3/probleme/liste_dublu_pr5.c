/*
    Vom implementa un garaj pentru camioane, pe modelul stivei si a cozii.
        Pentru aceasta, folosim 4 proceduri cerute de catre problema, pe care vom incerca sa le asociem cu operatii specifice.


    a) pe_drum(truck_id)                 
    b) intra_in_garaj(truck_id)           
    c) iese_din_garaj(truck_id)
    d) afiseaza_camioane(garaj sau drum)



    Folosim doua "obiecte", o stiva si o coada. Drumul, functioneaza pe principiul first in, first out, intrucat elementul cel mai apropiat de 
    intrarea in garaj va intra primul. Conform problemei, pentru garaj, doar ultimul camion poate sa iasa, deci garajul urmareste modelul last in first out, specific
    stivei.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define _TRUE    1
#define _FALSE   0

typedef struct node {
    int truck_id;
    struct node* next;
} CAMION;

CAMION* creaza_camion(int);
void pe_drum(int);
void intra_in_garaj(int);
void iese_din_garaj(int);
void afiseaza_camioane(CAMION*);


CAMION* garaj = NULL;
CAMION* drum  = NULL;

int main(void) {

    pe_drum(2);
    pe_drum(5);
    pe_drum(10);
    pe_drum(9);
    pe_drum(22);

    afiseaza_camioane(drum);
    afiseaza_camioane(garaj);
    intra_in_garaj(2);
    intra_in_garaj(25);
    intra_in_garaj(10);
    iese_din_garaj(10);
    iese_din_garaj(2);
    afiseaza_camioane(drum);
    afiseaza_camioane(garaj);

    printf("\nCompiled in: %0.3f seconds", clock()*1.0/CLOCKS_PER_SEC);
    free(garaj); garaj = NULL;
    free(drum);  drum  = NULL;
    return 0;
}

CAMION* creaza_camion(int eticheta) {
    CAMION* camion_nou   = (CAMION*)calloc(1,sizeof(CAMION));
    camion_nou->truck_id = eticheta;
    camion_nou->next     = NULL;
    return camion_nou;
}

void pe_drum(int eticheta) {
    if(drum == NULL) {
        drum = creaza_camion(eticheta);
    } else {
        CAMION* temp = drum;
        while(temp->next!=NULL) {
            temp = temp->next;
        }
        temp->next = creaza_camion(eticheta);
    }
}

void intra_in_garaj(int truck_id) {                     /// ca sa fie in garaj, trebuie sa fie pe drum.
    CAMION* temp = drum;
    int ok = _FALSE;


    while(temp != NULL) {
        if(temp->truck_id == truck_id) {
            ok = _TRUE;
            break;
        }

        temp = temp->next;
    }


    if(ok == _FALSE) {
        printf("\nCamionul %d nu se afla pe drum.", truck_id);
        return;
    } else {
        temp = drum;
        CAMION* anterior = NULL;

        while(temp->next != NULL) {
            if(temp->truck_id == truck_id) break;
            anterior = temp;
            temp = temp->next;
        }

        if(temp == drum) drum = drum->next;
        else anterior->next = temp->next;

        CAMION* de_mutat = creaza_camion(truck_id);                 /// as putea sa fac o inserare in fata, si atunci pot sa veriic mai usor functia de iesire din garaj.

        if(garaj==NULL) {
            garaj = de_mutat;
            return;
        } else {
            CAMION* iterator_garaj = garaj;
            while(iterator_garaj->next != NULL) {
                iterator_garaj = iterator_garaj->next;
            }

            iterator_garaj->next = de_mutat;
        }
    }
}

void iese_din_garaj(int truck_id) {
    if(garaj->truck_id != truck_id) {
        printf("\nCamionul %d nu se afla la usa garajului.", truck_id);
        return;
    } else {
        CAMION* temp = garaj;
        garaj = garaj->next;
        free(temp);
        CAMION* de_mutat = creaza_camion(truck_id);

        if(drum==NULL) {
            drum = de_mutat;
        } else {
            CAMION* temp = drum;
            while(temp->next != NULL) {
                temp = temp->next;
            } 

            temp->next = de_mutat;
        }
    }
}
void afiseaza_camioane(CAMION* parameter) {

    if(parameter==NULL) {
        printf("\nAtentie: %s este gol.", (parameter == garaj) ? "Garajul" : "Drumul");
        return;
    }

    printf("\n%s: ", (parameter == garaj) ? "garaj" : "drum");
    while(parameter!=NULL) {
        printf("%d ", parameter->truck_id);
        parameter=parameter->next;
    }
}
