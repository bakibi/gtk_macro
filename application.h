
#include "macro.h"




typedef struct FenetreInscription
{
    Table *mother;               // le conteneur oû on va posser notre fenetre
    Cadre *cadre;                // le cadre du contenuer
    Label *nom;                  // la labelle nom
    ZoneSaisi *i_nom;            // la zone de saisie de du nom
    Label *prenom;               // la labelle prenom
    ZoneSaisi *i_prenom;         // la zone de saisie de du prenom
    Label *adresse;              // la labelle adresse
    ZoneSaisi *i_add1,*i_add2;   // la zone de saisie de adresse
    Label *email;                // la labelle email
    ZoneSaisi *i_email;          // la zone de saisie de email
    Label *nomutilisateur;       // la labelle nom utilisateur
    ZoneSaisi *i_nomutilisateur; // la zone de saisie nom utilisateur
    Label *mdp1,*mdp2;                  // la labelle mot de passe
    ZoneSaisi *i_mdp1,*i_mdp2;   // la zone de saisie de mot de passe
    Bouton *valider;             // Le bouton de validite
    Bouton *reset;               // le bouton de vidage de tt les champs
     
    
}FenetreInscription;


/**********************                FenetreInscription   ***************************************/
FenetreInscription *initialiser_FenetreInscription();                          // initialisation des valeur
void creation_FenetreInscription(FenetreInscription *fen);                     // creation des valeur
void reset_FenetreInscription(GtkWidget *bt,FenetreInscription *fen);          // vider tout les chanmps
void valider_FenetreInscription(GtkWidget *bt,FenetreInscription *fen);          // valider tout les chanmps
