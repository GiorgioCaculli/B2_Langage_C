#include "ccacu050.h"

#include <stdio.h>
#include <string.h>

void
ccacu050( void )
{
    struct equipe
    {
        char nom[19];
        int nb_matches;
        int victoires;
        int defaites;
        int nuls;
        int buts_marques;
        int buts_encaisses;
        int points;
    };

    struct equipe equipes[17];

    FILE *fdat_c = fopen( "classement.dat", "r" );
    FILE *fdat_j = fopen( "journee.dat", "r" );
    FILE *fres = fopen( "ccacu050.res", "w" );

    int i = 1;
    int indice[17], place[17];

    while ( !feof( fdat_c ))
    {
        fscanf( fdat_c, "%18s%2d%2d%2d%2d%2d%2d%3d",
                equipes[ i ].nom, &equipes[ i ].nb_matches, &equipes[ i ].victoires, &equipes[ i ].defaites,
                &equipes[ i ].nuls, &equipes[ i ].buts_marques, &equipes[ i ].buts_encaisses, &equipes[ i ].points );
        indice[ i ] = i;
        place[ i ] = i;
        i += 1;
    }

    int nb_classement = i - 1;

    char eq_A[17][19], eq_B[17][19];
    int score_A[17], score_B[17];

    i = 1;

    while ( !feof( fdat_j ))
    {
        fscanf( fdat_j, "%18s%18s%2d%2d", eq_A[ i ], eq_B[ i ], &score_A[ i ], &score_B[ i ] );
        i += 1;
    }

    int nb_journee = i - 1;

    int j;
    for ( i = 1; i < nb_journee; i++ )
    {
        if ( score_A[ i ] > score_B[ i ] )
        {
            for ( j = 1; j < nb_classement; j++ )
            {
                if ( strcmp( equipes[ j ].nom, eq_A[ i ] ) == 0 )
                {
                    equipes[ j ].nb_matches += 1;
                    equipes[ j ].victoires += 1;
                    equipes[ j ].buts_marques += score_A[ i ];
                    equipes[ j ].buts_encaisses += score_B[ i ];
                    equipes[ j ].points += 3;
                } else if ( strcmp( equipes[ j ].nom, eq_B[ i ] ) == 0 )
                {
                    equipes[ j ].nb_matches += 1;
                    equipes[ j ].defaites += 1;
                    equipes[ j ].buts_marques += score_B[ i ];
                    equipes[ j ].buts_encaisses += score_A[ i ];
                }
            }
        } else if ( score_A[ i ] < score_B[ i ] )
        {
            for ( j = 1; j < nb_classement; j++ )
            {
                if ( strcmp( equipes[ j ].nom, eq_B[ i ] ) == 0 )
                {
                    equipes[ j ].nb_matches += 1;
                    equipes[ j ].victoires += 1;
                    equipes[ j ].buts_marques += score_B[ i ];
                    equipes[ j ].buts_encaisses += score_A[ i ];
                    equipes[ j ].points += 3;
                } else if ( strcmp( equipes[ j ].nom, eq_A[ i ] ) == 0 )
                {
                    equipes[ j ].nb_matches += 1;
                    equipes[ j ].defaites += 1;
                    equipes[ j ].buts_marques += score_A[ i ];
                    equipes[ j ].buts_encaisses += score_B[ i ];
                }
            }
        } else
        {
            for ( j = 1; j < nb_classement; j++ )
            {
                if ( strcmp( equipes[ j ].nom, eq_A[ i ] ) == 0 || strcmp( equipes[ j ].nom, eq_B[ i ] ) == 0 )
                {
                    equipes[ j ].nb_matches += 1;
                    equipes[ j ].nuls += 1;
                    equipes[ j ].buts_marques += score_A[ i ];
                    equipes[ j ].buts_encaisses += score_B[ i ];
                    equipes[ j ].points += 1;
                }
            }
        }
    }

    for ( i = 1; i < nb_classement - 1; i++ )
    {
        for( j = i + 1; j < nb_classement; j++ )
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
                    if( equipes[i].buts_marques - equipes[i].buts_marques < equipes[j].buts_marques - equipes[j].buts_encaisses )
                    {
                        indice[0] = indice[i];
                        indice[i] = indice[j];
                        indice[j] = indice[0];
                        place[i] += 1;
                    }
                    else
                    {
                        place[i] += 1;
                    }
                }
            }
        }
    }

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
