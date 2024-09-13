#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "exo1_prot.h"

int main()
{
    char *ip=allocate(ip);
    char *mask=allocate(mask);
    char *chaine=allocate(chaine);
    int *bin3=NULL, *bin1=NULL, *bin2=NULL, *bin4=NULL;
    int *bin30=NULL, *bin10=NULL, *bin20=NULL, *bin40=NULL;
    get_ip(&ip);
    get_mask(&mask);
    affectation(mask, &bin1, &bin2, &bin3, &bin4);
    concate(&chaine, bin1,bin2,bin3,bin4);
    condition(chaine, mask, bin10, bin20, bin30, bin40);
    calcul_reseau(ip, mask);
    calcul_broadcast(ip, chaine);
    calcul_nbr_machine(chaine);
    return 0;
}
