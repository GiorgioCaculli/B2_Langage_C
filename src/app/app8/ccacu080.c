#include "ccacu080.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct film
{
    int num_salle;
    char titre[24];
    int nb_places;
    int duree;
    char type[2];
} film;

typedef struct spectateur
{
    char nom[10];
    int num_salle;
    int nb_places_achetees;
} spectateur;

void ccacu080( void )
{
    FILE *fdat = fopen( "cinema.dat", "r" );
    FILE *fres = fopen( "ccacu080.res", "w" );

    fprintf( fres, "Fichier de résultats application 8 - Caculli Giorgio LA196672\n" );

    int i;

    film films[10];
    spectateur spectateurs[51];

    int nb_films = 9;

    for( i = 1; i <= nb_films; i++ )
    {
        int id;
        fscanf( fdat, "%1d", &id );
        films[id].num_salle = id;
        fscanf( fdat, "%24s %3d %3d %2s",
                films[id].titre, &films[id].nb_places, &films[id].duree, films[id].type );
    }

    i = 1;
    fscanf( fdat, "%9s", spectateurs[i].nom );
    while( strcmp( spectateurs[i].nom, "zzzzzzzzz" ) != 0 )
    {
        fscanf( fdat, "%1d %1d",
                &spectateurs[ i ].num_salle, &spectateurs[ i ].nb_places_achetees );
        i += 1;
        fscanf( fdat, "%9s", spectateurs[ i ].nom );
    }

    int nb_spectateurs = i;

    int places_disponibles( film, spectateur[], int );

    int places_dispo[10];

    fprintf( fres, "\nInformations sur les films\n" );

    fprintf( fres, "%-9s | %-24s | %-18s | %-14s | %-14s | %-4s\n",
             "Num salle", "Titre du film", "Places disponibles", "Places vendues", "Durée (en min)", "Type" );

    fprintf( fres, "--------------------------------------------------------------------------------------------------\n" );

    for( i = 1; i <= nb_films; i++ )
    {
        places_dispo[i] = places_disponibles( films[i], spectateurs, nb_spectateurs );
        int places_vendues = films[i].nb_places - places_dispo[i];
        fprintf( fres, "%9d | %-24s | %18d | %14d | %14d | %4s\n",
                 films[i].num_salle, films[i].titre, places_dispo[i], places_vendues, films[i].duree, films[i].type );
    }

    int tot_places_vendues = 0;

    for( i = 1; i <= nb_films; i++ )
    {
        tot_places_vendues += films[i].nb_places - places_dispo[i];
    }

    fprintf( fres, "Nombre total de places vendues: %d\n", tot_places_vendues );

    fprintf( fres, "\nInformations sur les spectateurs\n" );
    fprintf( fres, "----------------------------------------------------------------------------------------------------\n" );

    for( i = 1; i <= nb_spectateurs; i++ )
    {
        int j;
        for( j = 1; j <= nb_films; j++ )
        {
            if( spectateurs[i].num_salle == films[j].num_salle )
            {
                fprintf( fres, "%-10s | %-24s | %-4s | %1d    ",
                         spectateurs[i].nom, films[j].titre, films[j].type, spectateurs[i].nb_places_achetees );
            }
        }
        if( i % 2 == 0 )
        {
            fprintf( fres, "\n" );
        }
    }

    fprintf( fres, "\n" );
}

int places_disponibles( film film, spectateur spectateur[], int nb )
{
    int i;
    int nb_places = film.nb_places;
    for( i = 1; i < nb; i++ )
    {
        if( spectateur[i].num_salle == film.num_salle )
        {
            nb_places -= spectateur[i].nb_places_achetees;
        }
    }
    return nb_places;
}
