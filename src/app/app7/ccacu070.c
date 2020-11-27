#include "ccacu070.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void ccacu070(void)
{
    char nom[4][4][31][13];
    char prenom[4][4][31][12];
    int point[4][4][31];
    int nb[4][4];

    FILE *fdat_e = fopen( "etudiants.dat", "r" );
    FILE *fdat_p = fopen( "points.dat", "r" );
    FILE *fres = fopen( "ccacu070.res", "w" );

    int nb_tot = 1;

    while( !feof(fdat_e) )
    {
        int annee, classe, num;
        char nom_temp[24];
        fscanf( fdat_e, "%1d%1d%2d", &annee, &classe, &num );
        fgets( nom_temp, 24, fdat_e);

        int i, j;

        nom[annee][classe][num][0] = nom_temp[0];
        for( i = 1; i < 24; i++ )
        {
            if( isupper(nom_temp[i]) )
            {
                int k = 0;
                for( j = i; j < 24; j++ )
                {
                    if( nom_temp[j] == '\n' )
                    {
                        nom_temp[j] = '\0';
                    }
                    prenom[annee][classe][num][k] = nom_temp[j];
                    k += 1;
                }
                break;
            }
            nom[annee][classe][num][i] = nom_temp[i];
        }
        nom[annee][classe][num][i] = '\0';

        nb[annee][classe] += 1;

        nb_tot += 1;
    }

    int ind[4][4][31];

    int i = 1;
    while( !feof(fdat_p) )
    {
        int annee, classe, num;
        fscanf( fdat_p, "%1d%1d%2d", &annee, &classe, &num );
        fscanf( fdat_p, "%2d\n", &point[annee][classe][num] );
        ind[annee][classe][num] = i;
        i += 1;
    }

    int j, k;

    void tri(int pts[][4][31], int index[][4][31], int nb );

    for( i = 1; i < 4; i++ )
    {
        for( j = 1; j < 4; j++ )
        {
            if( nb[i][j] == 0 )
            {
                continue;
            }
            fprintf( fres, "ANNEE %d\n", i );
            fprintf( fres, "=========\n" );
            fprintf( fres, "CLASSE %d : %d ETUDIANTS\n", j, nb[i][j] );
            for( k = 1; k < nb[i][j]; k++ )
            {
                tri(point, ind, nb[i][j]);
                fprintf( fres, "%-12s %-11s %d ", nom[i][j][k], prenom[i][j][k], point[i][j][k] );
                if( k % 2 == 0 )
                {
                    fprintf( fres, "\n" );
                }
            }
            fprintf( fres, "\n" );
        }
    }
}

void tri( int point[][4][31], int ind[][4][31], int nb )
{
    int i, j, k, l;
    for( i = 1; i < 4; i++ )
    {
        for( j = 1; j < 4; j++ )
        {
            for( k = 1; k < nb - 1; k++ )
            {
                for( l = k + 1; l < nb; l++ )
                {
                    if(point[i][j][ind[i][j][k]] < point[i][j][ind[i][j][l]])
                    {
                        ind[i][j][0] = ind[i][j][k];
                        ind[i][j][k] = ind[i][j][l];
                        ind[i][j][l] = ind[i][j][0];
                    }
                }
            }
        }
    }
}
