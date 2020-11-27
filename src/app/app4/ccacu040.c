/*#include "ccacu040.h"

#include <stdio.h>
#include <string.h>

void
ccacu040( void )
{
    void calcul_points( char [][19], char [], char [], int, int, int[], int[], int[], int[], int[], int[], int[], int );
    void classement( int[], int[], int[], int[], int[], int[], int );
    FILE *fdat_c = fopen( "classement.dat", "r" );
    FILE *fdat_j = fopen( "journee.dat", "r" );
    FILE *fres = fopen( "ccacu040.res", "w" );
    char eq_nom[17][19], eq_A[17][19], eq_B[17][19];
    int eq_mat[17], eq_vic[17], eq_def[17], eq_nul[17], eq_buts_m[17], eq_buts_e[17], eq_pts[17], eq_score_A[17], eq_score_B[17];
    int indice[17], place[17];

    int i = 1;
    while( !feof(fdat_c) )
    {
        fscanf( fdat_c, "%18s%2d%2d%2d%2d%2d%2d%3d", eq_nom[i], &eq_mat[i], &eq_vic[i], &eq_def[i], &eq_nul[i], &eq_buts_m[i], &eq_buts_e[i], &eq_pts[i] );
        indice[i] = i;
        place[i] = i;
        i += 1;
    }

    int nb_classement = i - 1;

    i = 1;
    while( !feof(fdat_j) )
    {
        fscanf( fdat_j, "%18s%18s%2d%2d", eq_A[i], eq_B[i], &eq_score_A[i], &eq_score_B[i] );
        i += 1;
    }

    int nb_journee = i - 1;

    for( i = 1; i < nb_journee; i++ )
    {
        calcul_points( eq_nom, eq_A[i], eq_B[i], eq_score_A[i], eq_score_B[i], eq_mat, eq_vic, eq_def, eq_nul, eq_buts_m, eq_buts_e, eq_pts, nb_classement );
    }

    classement( eq_pts, eq_vic, eq_buts_m, eq_buts_e, indice, place, nb_classement );

    fprintf( fres, "%7s | %-18s | %12s | %14s | %13s | %17s | %17s | %19s | %11s\n",
             "# Place", "Nom", "# de matches", "# de victoires", "# de défaites", "# de matches nuls", "# de buts marqués", "# de buts encaissés", "# de points");
    fprintf( fres, "--------------------------------------------------------------------------------------------------------------------------------------------------------\n" );
    for( i = 1; i < nb_classement; i++ )
    {
        fprintf( fres, "%7d | %-18s | %12d | %14d | %13d | %17d | %17d | %19d | %11d\n",
                 place[indice[i]], eq_nom[indice[i]], eq_mat[indice[i]], eq_vic[indice[i]], eq_def[indice[i]], eq_nul[indice[i]], eq_buts_m[indice[i]], eq_buts_e[indice[i]], eq_pts[indice[i]] );
    }
}

void calcul_points( char eq_nom[][19], char eq_A[], char eq_B[], int score_A, int score_B,
                    int eq_mat[], int eq_vic[], int eq_def[], int eq_nul[], int eq_buts_m[], int eq_buts_e[], int eq_pts[],
                    int nb_classement )
{
    void mise_a_jour_info( int, int, char [], char [], char [][19], int [], int [], int [], int [], int [], int [], int );
    int i;
    if( score_A > score_B )
    {
        mise_a_jour_info( score_A, score_B, eq_A, eq_B,
                          eq_nom, eq_mat, eq_vic, eq_def, eq_buts_m, eq_buts_e, eq_pts, nb_classement );
    } else if( score_A < score_B )
    {
        mise_a_jour_info( score_B, score_A, eq_B, eq_A,
                          eq_nom, eq_mat, eq_vic, eq_def, eq_buts_m, eq_buts_e, eq_pts, nb_classement );
    }
    else
    {
        for( i = 1; i < nb_classement; i++ )
        {
            if( strcmp( eq_A, eq_nom[i] ) == 0  || strcmp( eq_B, eq_nom[i] ) == 0 )
            {
                eq_mat[i] += 1;
                eq_nul[i] += 1;
                eq_buts_m[i] += score_A;
                eq_buts_e[i] += score_B;
                eq_pts[i] += 1;
            }
        }
    }
}

void
mise_a_jour_info( int score_win, int score_lose, char eq_win[], char eq_lose[],
                  char eq_nom[][19], int eq_mat[], int eq_vic[], int eq_def[], int eq_buts_m[], int eq_buts_e[], int eq_pts[], int nb )
{
    int i;
    for( i = 1; i < nb; i++ )
    {
        if( strcmp( eq_win, eq_nom[i] ) == 0 )
        {
            eq_mat[i] += 1;
            eq_vic[i] += 1;
            eq_buts_m[i] += score_win;
            eq_buts_e[i] += score_lose;
            eq_pts[i] += 3;
        } else if( strcmp( eq_lose, eq_nom[i] ) == 0 )
        {
            eq_mat[i] += 1;
            eq_def[i] += 1;
            eq_buts_m[i] += score_lose;
            eq_buts_e[i] += score_win;
        }
    }
}

void classement( int eq_pts[], int eq_vic[], int eq_buts_m[], int eq_buts_e[], int indice[], int place[], int nb )
{
    void transpose( int, int, int[] );
    int i, j;
    for( i = 1; i < nb - 1; i++ )
    {
        for( j = i + 1; j < nb; j++ )
        {
            if( eq_pts[indice[i]] < eq_pts[indice[j]] )
            {
                transpose( indice[i], indice[j], indice );
                place[indice[i]] += 1;
            } else if( eq_pts[indice[i]] == eq_pts[indice[j]] )
            {
                if( eq_vic[indice[i]] < eq_vic[indice[j]] )
                {
                    transpose( indice[i], indice[j], indice );
                    place[indice[i]] += 1;
                } else if( eq_vic[indice[i]] == eq_vic[indice[j]] )
                {
                    if( eq_buts_m[indice[i]] - eq_buts_e[indice[i]] < eq_buts_m[indice[j]] - eq_buts_e[indice[j]] )
                    {
                        transpose( indice[i], indice[j], indice );
                        place[indice[i]] += 1;
                    } else
                    {
                        place[indice[i]] += 1;
                    }
                }
            }
        }
    }
}

void transpose( int i, int j, int indice[] )
{
    indice[0] = i;
    i = j;
    j = indice[0];
}
*/
