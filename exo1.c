#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "exo1_prot.h"

char *allocate(char *a)
{
    a=(char*)malloc(1000*sizeof(char));
    return a;
}


void get_ip(char **ip)
{
    *ip=(char*)malloc(500*sizeof(char));
    int a, b, c, d ;
    try:
    printf("Entrer l'addrress IP: ");
    scanf("%s", *ip);
    while (sscanf(*ip, "%d.%d.%d.%d", &a, &b, &c, &d)!=4)
    {
        get_ip(ip);
    }
        if(a>255 || b>255 || c>255 || d>255)
        {
            goto try;
        }
    printf("\n");
}

void get_mask(char **mask)
{
    *mask=(char*)malloc(500*sizeof(char));
    int x, y, z, o ;
    try:
    printf("Entrer le masque sous réseau\n");
    printf("MSR: ");
    scanf("%s", *mask);
    while(sscanf(*mask, "%d.%d.%d.%d", &x, &y, &z, &o) != 4)
        {
            get_mask(mask);
        }
    if(x>255 || y>255 || z>255 || o>255)
        {
            goto try;
        }
}

void calcul_reseau(char *ip, char *mask)
{
    int x, y, z, o ;
    int a, b, c, d ;
    int one, two, three, four;
    int broad1, broad2, broad3, broad4;
    if(sscanf(mask, "%d.%d.%d.%d", &x, &y, &z, &o) == 4 && (sscanf(ip, "%d.%d.%d.%d", &a, &b, &c, &d) ==4 ))
        {
            one = a & x ;
            two = b & y ;
            three = c & z ;
            four = d & o ;
        }
    printf("Adress réseau: %d.%d.%d.%d\n", one, two, three, four);

}

void calcul_broadcast(char *ip, char *chaine)
{
    int a, b, c, d ;
    int broad1, broad2, broad3, broad4 ;
    char *net1, *net2, *net3, *net4 ;
    net1=(char*)malloc(8*sizeof(char));
    net2=(char*)malloc(8*sizeof(char));
    net3=(char*)malloc(8*sizeof(char));
    net4=(char*)malloc(8*sizeof(char));

    int i, j ;
    for(i=0, j=0; i<8, j<8; i++, j++)
        {
            net1[i]=chaine[j];
        }
    for(i=0, j=8; i<8, j<16; i++, j++)
        {
            net2[i]=chaine[j];
        }
    for(i=0, j=16; i<8, j<24; i++, j++)
        {
            net3[i]=chaine[j];
        }
    for(i=0, j=24; i<8, j<32; i++, j++)
        {
            net4[i]=chaine[j];
        }
    int b1=strtol(net1, NULL, 2);
    int b2=strtol(net2, NULL, 2);
    int b3=strtol(net3, NULL, 2);
    int b4=strtol(net4, NULL, 2);
    if (sscanf(ip, "%d.%d.%d.%d", &a, &b, &c, &d) ==4 )
        {
            broad1 = b1 | a ;
            broad2 = b2 | b ;
            broad3 = b3 | c ;
            broad4 = b4 | d ;
        }
    printf("Adress de broadcast: %d.%d.%d.%d\n", broad1, broad2, broad3, broad4);
}

void calcul_nbr_machine(char *chaine)
{
    int i, k=0;
    int result;
    for(i=0; i<32; i++)
        {
            if(chaine[i]=='0')
                {
                    k++;
                }
        }
    result=pow(2,k)-2;
    printf("Nombre de machine possible: %d\n", result);
}


// Fonction pour convertir un nombre décimal en binaire et l'afficher
int *decimale_en_binaire(int nombre)
{
    // Créer un tableau pour stocker les chiffres binaires
    int *binaire=NULL;
    binaire=(int*)malloc(8*sizeof(int));

    int index = 0;

    // Convertir le nombre en binaire
    while ( index <= 8) {
        binaire[index] = nombre % 2;
        nombre = nombre / 2;
        index++;
    }

    // Afficher le nombre binaire à l'envers
    // for (int i = 7; i >= 0; i--) {
    //     printf("%d", binaire[i]);
    // }
    return binaire;
}

void affectation(char *mask, int **bin1, int **bin2, int **bin3, int **bin4)
{
    int x, y, z, o ;
    if(sscanf(mask, "%d.%d.%d.%d", &x, &y, &z, &o) == 4)
        {
            *bin1=decimale_en_binaire(x);
            *bin2=decimale_en_binaire(y);
            *bin3=decimale_en_binaire(z);
            *bin4=decimale_en_binaire(o);
        }
}
void concate(char **chaine, int *bin1, int *bin2, int *bin3, int *bin4)
{
    *chaine=(char*)malloc(33*sizeof(char));
    char *buffer;
    buffer=(char*)malloc(33*sizeof(char));
    int i;
    for(i=7; i>=0; i--)
    {
        sprintf(buffer,"%d", bin1[i]);
        strcat(*chaine,buffer);
    }
    for(i=7; i>=0 ; i--)
    {
        sprintf(buffer,"%d", bin2[i]);
        strcat(*chaine,buffer);
    }
    for(i=7; i>=0; i--)
    {
        sprintf(buffer,"%d", bin3[i]);
        strcat(*chaine,buffer);
    }
    for(i=7; i>=0; i--)
    {
        sprintf(buffer,"%d", bin4[i]);
        strcat(*chaine,buffer);
    }
}

void condition(char *chaine, char *mask, int *bin10, int *bin20, int *bin30, int *bin40)
{
    int count=1;
    int i;
    if(verify(chaine))
        {
            count=0;
        }
    else
        {
            while(count != 0 )
                {
                    REDO:
                    get_mask(&mask);
                    affectation(mask, &bin10, &bin20, &bin30, &bin40);
                    concate(&chaine, bin10, bin20, bin30, bin40);
                    if(verify(chaine))
                    {
                        count=0;
                    }
                    else
                    {
                        goto REDO;
                    }
                }
        }

}

int  verify(char *chaine)
{
    int n=0, b=0, i;
    int valeur=1;
    for(i=0; i<32; i++)
        {
            if(chaine[i]=='0')
                {
                    b=i;
                    for(n=b+1; n<32; n++)
                        {
                            if(chaine[n]=='1')
                                {
                                    valeur=0;
                                }
                        }
                }
        }
    return (valeur);

}
