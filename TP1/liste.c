#include <stdlib.h> 
#include <stdio.h> 

typedef struct client 
{ 
	int numero; 
	int prixAppel; 
	int nbAppel; 
	struct client* suivant; 
} Client; 

// Nombre total de lignes dans le fichier
#ifndef NBLOGLINE 
#define NBLOGLINE 200
#endif 

// Nombre de clients
#ifndef NBCLIENT 
#define NBCLIENT 20
#endif

Client* createClient(int numero, int nbAppel, int prixAppel) 
{
	Client* ret = (Client*)malloc(sizeof(Client));

     if(ret == NULL)
          return NULL;

     ret->numero = numero;
     ret->nbAppel = nbAppel;
     ret->prixAppel = prixAppel;
     ret->suivant = NULL;
     return ret;
}

int insert(Client** list, Client* newClient)
{
     if (*list == NULL || (*list)->numero >= newClient->numero) 
     {
          newClient->suivant = *list;
          *list = newClient;
          return 1;
     }

     Client* tmp = *list;
     while (tmp->suivant != NULL && tmp->suivant->numero < newClient->numero) 
          tmp = tmp->suivant;

     newClient->suivant = tmp->suivant;
     tmp->suivant = newClient;

     return 1;
}

int addLogLine(Client** liste, int numero, int prixAppel) 
{
     Client* tmp = *liste;
     while(tmp != NULL)
     {
          if(tmp->numero == numero)
          { 
               tmp->nbAppel += 1;
               tmp->prixAppel += prixAppel;
               return 1;
          }
          tmp = tmp->suivant;
     }

     Client* nc = createClient(numero, 1, prixAppel);
     if(nc == NULL)
          return 0;

     return insert(liste, nc);
}

void dumpListe(Client* liste) 
{
     Client* tmp = liste;
     while(tmp != NULL)
     {
          printf("Client %d, %d appels %0.2f €\n", tmp->numero, tmp->nbAppel, tmp->prixAppel / 100.f);
          tmp = tmp->suivant;
     }
}	

int main() 
{
    Client* liste = NULL; 

    int i;
    int numeroTel;
    int prixAppel;

    // Aide au calcul du pourcentage d'avancement
    int pas = NBLOGLINE/100;

    printf("****** Facturation appels telephoniques ******\n");


    for(i=0;i<NBLOGLINE;i++)
    {
          // Génération d'un numéro de telephone portable
          numeroTel = 600000000 + (rand() % NBCLIENT);

          // Donne un prix d'appel compris entre 0.01 et 4 euros
          prixAppel = (rand() % 400) + 1;

          // Ajout de cette ligne de log dans la liste des clients
   	     if (!addLogLine(&liste, numeroTel, prixAppel)) 
             break; 


          // Affichage du pourcentage d'avancement
          if ((i % pas)==0)
               printf("Done  = %d %%...\n",i/pas);
    }

   dumpListe(liste);	
   printf("======= Facturation appels telephoniques ======\n");

   return 0;
}