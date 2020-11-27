#include "ccacu060.h"

#include <stdio.h>
#include <string.h>

typedef struct equipe
{
    char nom[19];
    int nb_matches;
    int victoires;
    int defaites;
    int nuls;
    int buts_marques;
    int buts_encaisses;
    int points;
} equipe;

void
ccacu060( void )
{
    equipe equipes[17];

    void calcul_points( int, int, char [], char [], equipe [], int );
    void classement( equipe [], int [], int[], int );

    FILE *fdat_c = fopen( "classement.dat", "r" );
    FILE *fdat_j = fopen( "journee.dat", "r" );
    FILE *fres = fopen( "ccacu060.res", "w" );

    int indice[17], place[17];

    int i = 1;

    while( !feof( fdat_c ) )
    {
        fscanf( fdat_c, "%18s%2d%2d%2d%2d%2d%2d%3d",
                equipes[i].nom, &equipes[i].nb_matches, &equipes[i].victoires, &equipes[i].defaites, &equipes[i].nuls,
                &equipes[i].buts_marques, &equipes[i].buts_encaisses, &equipes[i].points );
        indice[i] = i;
        place[i] = i;
        i += 1;
    }

    int nb_classement = i - 1;

    char eq_A[17][19], eq_B[17][19];
    int score_A[17], score_B[17];

    i = 1;

    while( !feof( fdat_j ) )
    {
        fscanf( fdat_j, "%18s%18s%2d%2d",
                eq_A[i], eq_B[i], &score_A[i], &score_B[i] );
        i += 1;
    }

    int nb_journee = i - 1;

    for( i = 1; i < nb_journee; i++ )
    {
        calcul_points( score_A[i], score_B[i], eq_A[i], eq_B[i], equipes, nb_classement );
    }

    classement( equipes, indice, place, nb_classement );

    fprintf( fres, "%7s | %-18s | %12s | %14s | %13s | %17s | %17s | %19s | %11s\n",
             "# place", "nom", "# de matches", "# de victoires", "# de défaites", "# de matches nuls", "# de buts marqués", "# de buts encaissés", "# de points");
    fprintf( fres, "--------------------------------------------------------------------------------------------------------------------------------------------------------\n" );

    for( i = 1; i < nb_classement; i++ )
    {
        fprintf( fres, "%7d | %-18s | %12d | %14d | %13d | %17d | %17d | %19d | %11d\n",
                 place[indice[i]], equipes[indice[i]].nom, equipes[indice[i]].nb_matches,
                 equipes[indice[i]].victoires, equipes[indice[i]].defaites, equipes[indice[i]].nuls,
                 equipes[indice[i]].buts_marques, equipes[indice[i]].buts_encaisses, equipes[indice[i]].points );
    }
}

void calcul_points( int score_A, int score_B, char eq_A[], char eq_B[], equipe equipes[], int nb )
{
    void mise_a_jour_info( int, int, char[], char[], equipe[], int );
    int i;
    if( score_A > score_B )
    {
        mise_a_jour_info( score_A, score_B, eq_A, eq_B, equipes, nb );
    } else if( score_A < score_B )
    {
        mise_a_jour_info( score_B, score_A, eq_B, eq_A, equipes, nb );
    } else
    {
        for( i = 1; i < nb; i++ )
        {
            if( strcmp( equipes[i].nom, eq_A ) == 0 || strcmp( equipes[i].nom, eq_B ) == 0 )
            {
                equipes[i].nb_matches += 1;
                equipes[i].nuls += 1;
                equipes[i].buts_marques += score_A;
                equipes[i].buts_encaisses += score_B;
                equipes[i].points += 1;
            }
        }
    }
}

void mise_a_jour_info( int score_win, int score_lose, char eq_win[], char eq_lose[], equipe equipes[], int nb )
{
    int i;
    for( i = 1; i < nb; i++ )
    {
        if( strcmp( equipes[i].nom, eq_win ) == 0 )
        {
            equipes[i].nb_matches += 1;
            equipes[i].victoires += 1;
            equipes[i].buts_marques += score_win;
            equipes[i].buts_encaisses += score_lose;
            equipes[i].points += 3;
        } else if( strcmp( equipes[i].nom, eq_lose ) == 0 )
        {
            equipes[i].nb_matches += 1;
            equipes[i].defaites += 1;
            equipes[i].buts_marques += score_lose;
            equipes[i].buts_encaisses += score_win;
        }
    }
}

void classement( equipe equipes[], int indice[], int place[], int nb )
{
    int i, j;
    for( i = 1; i < nb - 1; i++ )
    {
        for( j = i + 1; j < nb; j++ )
        {
            if( equipes[i].points < equipes[j].points )
            {
                indice[0] = indice[i];
                indice[i] = indice[j];
                indice[j] = indice[0];
                place[i] += 1;
            } else if( equipes[i].points == equipes[j].points )
            {
                if( equipes[i].victoires < equipes[j].victoires )
                {
                    indice[0] = indice[i];
                    indice[i] = indice[j];
                    indice[j] = indice[0];
                    place[i] += 1;
                } else if( equipes[i].victoires == equipes[j].victoires )
                {
                    if( equipes[i].buts_marques - equipes[i].buts_encaisses < equipes[j].buts_marques - equipes[j].buts_encaisses )
                    {
                        indice[0] = indice[i];
                        indice[i] = indice[j];
                        indice[j] = indice[0];
                        place[i] += 1;
                    } else
                    {
                        place[i] += 1;
                    }
                }
            }
        }
    }
}

