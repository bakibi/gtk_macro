
#include "macro.h"



/*****************************Fenetre d'Inscription*************************************/
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


/***************************** LA Structure utilisateur                      *******************************/

typedef struct Utilisateur
{
    char nom[20],prenom[20],email[40],mdp[30],username[30],adresse[100];
}Utilisateur;

typedef struct L_Utilisateur
{
    Utilisateur user;
    struct L_Utilisateur *suivant;
    
}L_Utilisateur;

/******************************LA structure Total******************************/
typedef struct Fenetre_win
{
    FenetreInscription *Finsc;
    Fenetre *Fen;
    L_Utilisateur *lu;
}Fenetre_win;



/*******************************  Fonction de L_utilisateur  ***************************************************/
Utilisateur *creer_utilisateur(char *nom,char *prenom,char *email,char *mdp,char *username,char *adresse);  //creeer un user
L_Utilisateur *ajouter_liste_utilisateur(L_Utilisateur *LU,Utilisateur user);      //ajout utuilisateur au liste
int  existe_utilisateur(L_Utilisateur *LU,char *username,char *mdp);     //verifier si un username existe 




/************************           BOite de dialog                   *******************************/
void afficher_boite_dialog_avec_message(Fenetre_win *fen,char *str);            // afficher une boite de dilaog


/**********************                FenetreInscription   ***************************************/
FenetreInscription *initialiser_FenetreInscription();                          // initialisation des valeur
void creation_FenetreInscription(FenetreInscription *fen);                     // creation des valeur
void reset_FenetreInscription(GtkWidget *bt,Fenetre_win *fen);                 // vider tout les chanmps
void valider_FenetreInscription(GtkWidget *bt,Fenetre_win *fen);               // valider tout les chanmps
