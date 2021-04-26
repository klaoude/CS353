#include <stdlib.h> 
#include <stdio.h> 

typedef struct client 
{ 
	int numero; 
	int prixAppel; 
	int nbAppel; 
	struct client* gauche;
	struct client* droite;
 
} Client;

// Nombre total de lignes dans le fichier
#ifndef NBLOGLINE
#define NBLOGLINE    1000
#endif
// Nombre de clients
#ifndef NBCLIENT
#define NBCLIENT    20
#endif


Client* creerClient(int numeroTel, int nbAppel,int cout)
{
    Client* ret = (Client*)malloc(sizeof(Client));
    ret->numero = numeroTel;
    ret->prixAppel = cout;
    ret->nbAppel = nbAppel;
    ret->gauche = NULL;
    ret->droite = NULL;
}

Client* chercher(Client* abr,int numeroTel)
{
    while(abr != NULL)
    {
        if(abr->numero == numeroTel)
            return abr;
        
        if(abr->numero < numeroTel)
            abr = abr->droite;
        else
            abr = abr->gauche;
    }
    return NULL;
}

Client* ins(Client* abr, int num, int prix)
{

}

Client* inserer(Client** abr, int numeroTel, int prixAppel)
{
    if(*abr == NULL)
    {
        *abr = creerClient(numeroTel, 1, prixAppel);
        return *abr;
    }

    Client* c = *abr; 
    
    if(c->numero > numeroTel)
        c->gauche = inserer(&(c->gauche), numeroTel, prixAppel);
    else if(c->numero < numeroTel)
        c->droite = inserer(&(c->droite), numeroTel, prixAppel);

    return c;
}

Client* supprimerClient(Client** abr, int numeroTel)
{
    if(*abr == NULL)
        return *abr;
    
    Client* c = *abr;

    if(c->numero > numeroTel)
        c->gauche = supprimerClient(&(c->gauche), numeroTel);
    else if(c->numero < numeroTel)
        c->droite = supprimerClient(&(c->droite), numeroTel);
    else
    {
        if(c->gauche == NULL)
        {
            Client* tmp = c->droite;
            free(c);
            return tmp;
        }
        else if(c->droite == NULL)
        {
            Client* tmp = c->gauche;
            free(c);
            return tmp;
        }

        Client* tmp = c->droite;
        while(tmp != NULL && tmp->gauche != NULL)
            tmp = tmp->gauche;
        
        c->numero = tmp->numero;
        c->droite = supprimerClient(&(c->droite), tmp->numero);
    }
    return c;
}

void parcourirInfixe(Client* abr)
{
    if(abr == NULL)
        return;
    
    if(abr->gauche != NULL)
        parcourirInfixe(abr->gauche);

    printf("Client %d, %d appels %0.2f €\n", abr->numero, abr->nbAppel, abr->prixAppel / 100.f);

    if(abr->droite != NULL)
        parcourirInfixe(abr->droite);
}	

Client* createSampleTree()
{
    Client* abr = NULL;
    inserer(&abr, 15, 0);
    inserer(&abr, 12, 0);
    inserer(&abr, 8, 0);
    inserer(&abr, 10, 0);
    inserer(&abr, 14, 0);
    inserer(&abr, 13, 0);
    inserer(&abr, 20, 0);
    inserer(&abr, 16, 0);
    inserer(&abr, 17, 0);
    inserer(&abr, 21, 0);
    return abr;
}


int main() 
{
    /*
    Client* abr = createSampleTree();
    parcourirInfixe(abr);
    */

    Client* liste = NULL; 

    int i;
    int numeroTel;
    int prixAppel;

    // Aide au calcul du pourcentage d'avancement
    int pas = NBLOGLINE/100;
    for(i=0;i<NBLOGLINE;i++)
    {

        // Génération d'un numéro de telephone portable
        numeroTel = 600000000+(rand() % NBCLIENT);

        // Donne un prix d'appel compris entre 0.01 et 4 euros
        prixAppel = (rand() % 400)+1;

        // Ajout de cette ligne de log dans la liste des clients
   	    if (inserer(&liste ,numeroTel,prixAppel)==NULL) 
           break; 

        // Affichage du pourcentage d'avancement
        if ((i % pas)==0)
        {
            printf("Done  = %d %%...\n",i/pas);
        }
    }

    printf("****** Facturation appels telephoniques ******\n");

    parcourirInfixe(liste);

    printf("****** Suppression de la facturation appels telephoniques ******\n");

    for (i=0; i < NBCLIENT; i++) 
	    supprimerClient(&liste, 600000000+i);

    printf("****** Fin Facturation appels telephoniques ******\n");    
}