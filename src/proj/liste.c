#include "liste.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct client
{
    int num;
    char nom[21];
    float somme;
    struct client *suivant;
}client;

void liste( void )
{
    FILE *fdat;
    int i,n=0,numero,place;
    fdat=fopen("liste.dat","r");
    client *deb,*courant,*suivant,*intercale;
    courant=malloc(sizeof(client));
    deb=courant;

    // lecture des données avec allocation de mémoire au fil du remplissage
    // de la liste chaînée
    fscanf(fdat,"%3d",&courant->num);
    while(!feof(fdat))
    {
        fscanf(fdat,"%s %f",&courant->nom,&courant->somme);
        suivant=malloc(sizeof(client));
        (*courant).suivant=suivant;
        n++;
        printf("%d   %x  %d  %-20s %6.2f %x\n",
               n,courant,courant->num,courant->nom,courant->somme,courant->suivant);
        printf("            %d  %-20s %6.2f\n\n",
               (*courant).num,(*courant).nom,(*courant).somme);
        courant=suivant;
        fscanf(fdat,"%3d",&courant->num);
    }

    // on termine la liste avec l'adresse NULL
    courant=deb;
    for(i=1;i<n;i++)
        courant=courant->suivant;
    (*courant).suivant=NULL;
    // on a demandé de la mémoire qu'on n'utilise pas --> free()
    free(suivant);
    // impression de la liste
    courant=deb;
    for(i=1;i<=n;i++)
    {
        printf("*** %d   %x %-20s %d %x ***\n",
               i,courant,courant->nom,courant->num,courant->suivant);
        courant=courant->suivant;
    }

    // ajout d'un client en une position bien précise
    printf("ajout d'une personne en quelle position ?\n");
    scanf("%d",&place);
    if(place>=1 && place<=n+1)
    {
        intercale=malloc(sizeof(client));
        if(place!=1)
        {
            courant=deb;
            // on se déplace jusqu'à la bonne adresse
            for(i=1;i<place-1;i++)
            {
                courant=courant->suivant;
            }
            // on change les deux pointeurs
            intercale->suivant=courant->suivant;
            courant->suivant=intercale;
        }
        else
        {
            // l'adresse de début devient la nouvelle adresse générée
            intercale->suivant=deb;
            deb=intercale;
        }
        printf("Entrez le num du nouveau client : \n");
        scanf("%d",&intercale->num);       // encoder 999
        printf("Entrez le nom du nouveau client : \n");
        scanf("%s",&intercale->nom); 	  // encoder NOUVEAU
        printf("Entrez la somme due par ce nouveau client :\n");
        scanf("%f",&intercale->somme);     // encoder 999.99

        n++;
    }
    else printf("impossible\n");

    // impression de la liste complétée
    courant=deb;
    for(i=1;i<=n;i++)
    {
        printf("*** %d   %x %-20s %d %x ***\n",
               i,courant,courant->nom,courant->num,courant->suivant);
        courant=courant->suivant;
    }

    // suppression d'un client en une position bien précise
    printf("suppression d'une personne en quelle position ?\n");
    scanf("%d",&place);
    if(place>=1 && place<=n)
    {
        if(place==1)
        {
            intercale=deb;
            deb=deb->suivant;
            free(intercale);
        }
        else
        {
            courant=deb;
            // on se déplace jusqu'à  la bonne adresse
            for(i=1;i<place-1;i++)
            {
                courant=courant->suivant;
            }
            if(place != n)
            {
                // on fait disparaître un maillon de la chaine
                intercale=courant->suivant;
                courant->suivant=intercale->suivant;
                free(intercale);
            }
            else
            {
                intercale=courant->suivant;
                courant->suivant=NULL;
                free(intercale);
            }
        }
        n--;
    }
    else printf("impossible\n");

    // impression de la liste finale
    courant=deb;
    for(i=1;i<=n;i++)
    {
        printf("*** %d   %x %-20s %d %x ***\n",
               i,courant,courant->nom,courant->num,courant->suivant);
        courant=courant->suivant;
    }
}
