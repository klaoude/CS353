/******************************************************************************
 * Implementation du module gestion de stock d'un magasin
 * avec une table de hachage
 ******************************************************************************/

#include "store.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 * Variable globale contenant le tableau
 *----------------------------------------------------------------------------*/
Item hash_table[TABLE_SIZE];

/*----------------------------------------------------------------------------
 * Cette fonction initialise le tableau hash_table
 * en positionnant tous les elements à NULL_ITEM
 *----------------------------------------------------------------------------*/
void init()
{
    int i;
    for(i=0;i<TABLE_SIZE;i++)
    {
        hash_table[i].status = NULL_ITEM;
        hash_table[i].price = 0.00f;
        hash_table[i].code = 0;
    }
}


/*----------------------------------------------------------------------------
 * Cette fonction calcule la valeur de hachage pour le produit itemCode
 *----------------------------------------------------------------------------*/
uint32_t hashkey(uint32_t itemCode,uint32_t nbTry)
{
    return (((itemCode%TABLE_SIZE)+nbTry*(1+itemCode%(TABLE_SIZE -1)))%TABLE_SIZE); 
}

/*----------------------------------------------------------------------------
 * Cette fonction insère le produit indiqué dans la table de hachage.
 * Si le produit est inséré avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit existe déjà dans la table, alors la fonction retourne INSERT_ALREADY_EXIST (-1),
 * et la table de hachage n'est pas modifiée
 * Si la table est pleine, alors la fonction retourne TABLE_FULL (-2).
 *----------------------------------------------------------------------------*/
int insertItem(uint32_t itemCode, char* itemName, float itemPrice)
{ 
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        uint32_t hash = hashkey(itemCode, i);
        if(hash_table[hash].code == itemCode)
            return INSERT_ALREADY_EXIST;
        if(hash_table[hash].status == NULL_ITEM || hash_table[hash].status == DELETED_ITEM)
        {
            hash_table[hash].status = USED_ITEM;
            hash_table[hash].price = itemPrice;
            hash_table[hash].code = itemCode;
            strncpy(hash_table[hash].name, itemName, ITEM_NAME_SIZE);
            return SUCCESS;
        }
    }
    return TABLE_FULL;
}

/*----------------------------------------------------------------------------
 * fonction de suppression d'un produit du magasin
 * Si le produit est supprimé avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit n'existe pas, alors la fonction retourne DELETE_NO_ROW (-4)
 *----------------------------------------------------------------------------*/
int suppressItem(unsigned int itemCode)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        uint32_t hash = hashkey(itemCode, i);
        if(hash_table[hash].code == itemCode)
        {
            free(hash_table[hash].name);
            hash_table[hash].status = DELETED_ITEM;
            hash_table[hash].code = 0;
            hash_table[hash].price = 0.f;
            return SUCCESS;
        }
    }
    return DELETE_NO_ROW;
}

/*----------------------------------------------------------------------------
 * Pour chaque produit, cette fonction affiche sur une ligne
 * le code du produit
 * son libellé
 * son prix
 * son index dans la table de hashage
 * sa valeur de hash
 *----------------------------------------------------------------------------*/
void dumpItems()
{
    printf("[CODE\t%20s\tPRIX\tINDEX\t]\n", "LIBELLE");
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        Item it = hash_table[i];
        if(it.status != NULL_ITEM)
            printf("[%d\t%20s\t%0.02f€\t%d\t]\n", it.code, it.name, it.price, i);
    }
}


/*----------------------------------------------------------------------------
 * Cette fonction trouve le produit dont le code est itemCode.
 * Cette fonction retourne NULL si le produit n'existe pas.
 * Cette fonction retourne un pointeur vers le produit si le produit existe.
 *----------------------------------------------------------------------------*/
Item *getItem(unsigned int itemCode)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        uint32_t hash = hashkey(itemCode, i);
        if(hash_table[hash].code == itemCode)
            return &(hash_table[hash]);
    }
    return NULL;    
}

float getPrice(int itemCode)
{
    Item* it = getItem(itemCode);
    if(it == NULL)
        return SELECT_NO_ROW;
    return it->price;
}

/*----------------------------------------------------------------------------
 *  fonction de mise à jour d'un produit :
 * Si le produit est mis à jour avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit n'existe pas, alors la fonction retourne UPDATE_NO_ROW (-5)
 *----------------------------------------------------------------------------*/
int updateItem(unsigned int itemCode, char *itemName, float itemPrice)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        uint32_t hash = hashkey(itemCode, i);
        if(hash_table[hash].code == itemCode)
        {
            strncpy(hash_table[hash].name, itemName, ITEM_NAME_SIZE);
            hash_table[hash].price = itemPrice;
            return SUCCESS;
        }
    }
    return UPDATE_NO_ROW;
}

/*----------------------------------------------------------------------------
 * la fonction de réorganisation in situ:
 *----------------------------------------------------------------------------*/
void rebuildTable()
{

}