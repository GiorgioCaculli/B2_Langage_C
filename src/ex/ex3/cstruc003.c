#include "cstruc003.h"

#include <stdio.h>

typedef struct
{
    int numero;
    char nom[10];
    char prenom[8];
    int age;
    int code_postal;
} client;

void cstruc003( void )
{
    client client_plus_age( client [], int );
    void tri_clients( client [], int );
    FILE *fdat = fopen( "cstruc001.dat", "r" );
    FILE *fres = fopen( "cstruc003.res", "w" );

    client clients[10];

    int i = 1;

    while( !feof( fdat ) )
    {
        fscanf( fdat, "%d %s %s %d %d",
                &clients[i].numero, clients[i].nom, clients[i].prenom, &clients[i].age, &clients[i].code_postal );
        i += 1;
    }

    int nb_clients = i - 1;

    client c_plus_age = client_plus_age( clients, nb_clients );

    fprintf( fres, "Le client plus agé est: %d %s %s %d ans.\n",
             c_plus_age.numero, c_plus_age.nom, c_plus_age.prenom, c_plus_age.age );

    fprintf( fres, "Liste des clients sans tri.\n" );

    for( i = 1; i < nb_clients; i++ )
    {
        fprintf( fres, "%3d %-10s %-8s %2d %4d\n",
                clients[i].numero, clients[i].nom, clients[i].prenom, clients[i].age, clients[i].code_postal );
    }

    tri_clients( clients, nb_clients );

    fprintf( fres, "Clients dans l'ordre croissant des âges.\n" );

    for( i = 1; i < nb_clients; i++ )
    {
        fprintf( fres, "%3d %-10s %-8s %2d %4d\n",
                 clients[i].numero, clients[i].nom, clients[i].prenom, clients[i].age, clients[i].code_postal );
    }
}

client client_plus_age( client clients[], int nb )
{
    client c = clients[0];
    int i;
    for( i = 1; i < nb; i++ )
    {
        if( clients[i].age > c.age )
        {
            c = clients[i];
        }
    }
    return c;
}

void tri_clients( client clients[], int nb )
{
    int i, j;
    for( i = 1; i < nb - 1; i++ )
    {
        for( j = i + 1; j < nb; j++ )
        {
            if( clients[i].age > clients[j].age )
            {
                clients[0] = clients[i];
                clients[i] = clients[j];
                clients[j] = clients[0];
            }
        }
    }
}
