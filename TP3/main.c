/******************************************************************************
 * Programme de test du gestionnaire de magasin                               *                                                               *
 ******************************************************************************/

#include "store.h"
#include <stdio.h>


int main()
{
    //
    printf("****** Gestionnaire de magasin ******\n");
    init();
    //
    printf("=======Gestionnaire de magasin ======\n");
    insertItem(10001, "Sucre", 1.2f);
    insertItem(10002, "Farine", .8f);
    insertItem(10003, "Confiture fraise", 2.5f);
    insertItem(10004, "Sel", .5f);

    dumpItems();

    return 0;
}

