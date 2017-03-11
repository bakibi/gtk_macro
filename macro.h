

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>



//enumeration Fenetre
enum {W_TOPLEVEL,W_POPUP};// type
enum {W_NONE,W_CENTER,W_MOUSE,W_CENTER_ALWAYS,W_ON_PARENT};//position initiale
enum {TOUJOURS,AUTO,JAMAIS};//barre défilement

enum {VERTICAL,HORIZONTAL};//BOX type
enum {DEBUT,FIN};//BOX insertion

enum {FIXED,HBOX, VBOX};//conteneur

//enumeration Bouton
enum {B_VIDE,B_LABEL,B_MNEMONIC,B_IMAGE,B_ADD,B_DELETE,B_OPEN,B_CLOSE,
      B_ABOUT,B_FILECH, B_COLOR,B_FONTCH, B_APPLY};// type
enum {BR_NORMAL, BR_NONE=2};// type de relief

//enumeration Onglet
enum {O_LEFT,O_RIGHT,O_TOP,O_BOTTOM};

//enumeration Cadre
enum {C_SHADOW_IN,C_SHADOW_OUT,C_SHADOW_ETCHED_IN,C_SHADOW_ETCHED_IN_OUT};


enum {LEFT,CENTER,RIGHT};//justify du label

//enum scale
enum {S_LEFT,S_RIGHT,S_TOP,S_BOTTOM};



/*********              LES STRUCTURES DE DONNEES       *****************/



/* position */
typedef struct
{
    int x;//position sur l'abscisse
    int y;//position sur l'ordonnée
}Position;
/* taille  */
typedef struct
{
    int h;//hauteur
    int w;//largeur
}Taille;
/**   Images   **/
/* image */
typedef struct img
{
    GtkWidget *idImage;//widget image
    char *chemin;//chemin de l'image
    Position iPos;//position de l'image
}Image;
/****************************  STRUCTURE FENETRE ************************/
typedef struct fenetre
{
    GtkWidget *idFenetre;//identifiant de la fenetre
    GtkWidget *fixed;//widget du conteneur
    GtkWidget *wBox;
    Image *wIBg;
    int wPosDebut;//0...4
    int wType;// 0 toplevel 1 popup
    gchar *icone;//chemin de l'icone
    char *wTitre;//titre de la fenetre
    Position wPos;//position de la fenetre
    GdkColor wBg;//couleur
    Taille wTaille;//taille
    int wBarredefilement;
    int wConteneur;

}Fenetre;

/**     STRUCTURES ONGLETS     **/
typedef struct pageonglet
{
  GtkWidget *poFixed;//widget page onglet
  char *poLabel;//label de la page

}PageOnglet;

typedef struct onglet
{
    GtkWidget *idNotebook;//widget qui contiendra lesp ages
    int oPosOnglets;//pos des pages
    int oSetScrollable;//bouton navigation si trop de pages (0,1)
    Taille oTaille;//taille
    Position oPos;//position
    GdkColor oColor;//couleur

}Onglet;


/* boutons*/
typedef struct bouton
{
    GtkWidget* idBouton;
    int bRelief;//0 normal , 1 half
    gchar* bIcone;// choisi du stock
    int bType ;// label,mnemonic,image,ou bien from stock
    char * bLabel;//label du bouton
    Image bImg;//image
    GdkColor bColor;//couleur
    Position bPos;//position
    Taille bTaille;//taille
}Bouton;
/* label */
/* style ou formatage du text */
typedef struct style
{
    char tPolice[40];//pour definir la police utilsee
    char tSize[4];/*pour definir la taille du text*/
    char tStyle[20];/*pour definir le style du text*/
    char tWeight[20];/*pour definir l'epaisseur du text*/
    char tColor[10];/*pour definir la couleur du text*/
    char fColor[10];/*pour definir la couleur du fond*/
    char tUnderline[10];/*pour le soulignement du text*/
    char tBarer[10];/*pour barrer le text*/
}Style;
typedef struct label
{
    GtkWidget* idLabel;//widget du label
    char *lTexte;//texte du label
    int lJustify;//1 LEFT 2 RIGHT 3 CENTER
    Position lPos;//position
    Style lFormat;//format
    int lStyle;// utiliser un format ou pas
}Label;

/*************************** STRUCTURE TABLE ****************************/

typedef struct table
{
  GtkWidget *table;//widget de la table
  int nbLignes;//nombre de lignes de la table
  int nbColonnes;//nombre de colonnes de la table
  int homogene;//1 si tout les widgets occupent le même espace, 0 si non
  Position posTable;//position

}Table;


/*********************** STRUCTURE ZONE DE SAISI ************************/
typedef struct zonesaisi
{
    GtkWidget* idZone;//widget de la zone de saisi
    Position zPos;//position
    int zMaxlenght;//la longueur maximale du texte à saisir dans la zone
    Taille zTaille;//taille
    char* zText;//texte présent initialement
    char zTremp;// texte du remplissage au cas où un texte sera visible
    int zCursorposition;//position du curseur
    int zVisible; // 0 si oui 1 non
    int zAlign;//(float!!)0 en cas de gauche et 1 cas de droite
}ZoneSaisi;

/************************ STRUCTURE CADRE *******************************/

typedef struct cadre
{
  GtkWidget *idCadre;//widget du cadre
  GtkWidget *cFixed;//conteneur du cadre
  char *cLabel;//label du cadre
  int cStyle;//style cadre, ombre etc..
  float cPosTexteX;//position horizontale label cadre
  float cPosTexteY;//position verticale label cadre
  GdkColor cCouleur;//couleur du cadre
  Taille cTaille;//taille du cadre
  Position cPos;//position du cadre

}Cadre;


/*******************************  EVENT BOX *****************************/
typedef struct event
{
    GtkWidget *idEvent;//widget de l'event box
    Position evPos;//position de l'event box
    int evEvent;
}EventBox;

/**************************   CHECK BOX *********************************/
typedef struct check
{
    GtkWidget* idCheck;//widget de la check box
    Position cPos;//position du checkbox
    char* cLabel;//lable du checkbox
}CheckBox;

/************************** COMBO BOX  **********************************/
typedef struct cmbbox
{
   GtkWidget *idComboBox;//widget de la combobox
   Position cbPos;//position
}ComboBox;
/***************************** STRUCTURE SCALE **************************/

typedef struct scal
{
   GtkWidget *idScale;//widget du scale
   int type;// VERTICAL , HORIZONTAL
   int afficherValeur;//0:n'affiche pas la valeur correspondante;1affiche
   int scaleDigit;//nombre de chiffres après la virgule;è
   int posValeur;//position du label:4pos possible haut,bas,gauche,droite
   int min;//valeur minimale
   int max;//valeur maximale
   int pas;//pas utilisé quand on déplace avec fleche clavier
   Taille sTaille;//taille du SCALE
   Position sPosition;//position du SCALE
}Scale;


/**************************** BOUTONS RADIO *****************************/
typedef struct rad
{
   GtkWidget *idBoutonRadio;//widget du bouton radio
   Position rPos;//position du bouton radio

}BoutonRadio;

/************************ Structures de la barre de menus ****************/

typedef struct menuItem
{
    GtkWidget *menuItem;
    char *label;//label du menu
    int type;
    int separateur;//si le menu item est suivi par un séparateur
    struct menuItem *sous_menu;//liste sous menu lié à un menu item
    struct menuItem *suivant;

}MenuItem;

typedef struct menu
{
    char *label;
    int tearOff;//si le menu est détachable
    MenuItem *listeMenuItem;//liste des menu items
    struct menu *suivant;

}Menu;
typedef struct menuBar
{
    GtkWidget *menuBar;//barre de menu
    Menu *listeMenu;//liste des menus
}MenuBar;

/************** STRUCTURE BARRE D'OUTILS *******************/
typedef struct toolbar
{
    GtkWidget *idToolbar;
    Position tbPos;
    Taille tbTaille;
    int tbOrientation;// Horizontal, Vertical
    int tbType;// -1 à personnaliser sinon prédéfini
}ToolBar;
/************** STRUCTURE SEPARATEUR  **********************/

typedef struct sep
{
   GtkWidget *idSeparateur;//widget du séparateur
   int type;// 0 : séparateur horizontal ; 1 : séparateur verticale
   Taille sTaille;/*taille du séparateur: pour horizontal spécifier que
                    le parametre W, H pour le vertical*/
   Position sPosition;//position du séparateur

}Separateur;

/*** ***** STRUCTURE BOX ***********************/

typedef struct box
{
  GtkWidget *idVBox;//widget de la box
  int bType;//hbox ou bien vbox
  int bHomogene;//si tout les widget occupe le même espace
  int bSpacing;//espacement entre les widgets contenu dans la box
  Taille bTaille;//taille
  Position bPos;//position
}Box;
/********************** BOUTON POUSSOIR *********************************/
typedef struct bp
{
    GtkWidget* idBoutonPoussoir;
    char * bpLabel;//label du bouton
    GdkColor bpColor;//couleur
    Position bpPos;//position
    Taille bpTaille;//taille
    int bpEtat;//etat du bouton (enfoncé, relaché)
}BoutonPoussoir;

/*********** STRUCTURE BOITE DE DIALOGUE ********/
typedef struct dial
{
   GtkWidget *idDialog;//widget de la boite de dialogue
   char *dLabel;//titre de la boite de dialogue
   int flag;//type boite dialogue : modal, destroy with parent, no separator


}Dialog;
/************* STRUCTURE BOUTON SPIN *************/
typedef struct spin
{
    GtkWidget *idSpin;
    gdouble sMin;
    gdouble sMax;
    gdouble sPas;
    Position sPos;
    Taille sTaille;
}BoutonSpin;



/********************* Prototypes des fonctions ******************/
void initialiser ( int argc, char *argv[] );
void afficher(GtkWidget *wid);
void afficher_tout (GtkWidget* wid);
void cacher(GtkWidget *wid);
void cacher_tout (GtkWidget* wid);
void boucle_evenement();

Fenetre* initialiser_fenetre();
void creer_fenetre(Fenetre *win);

void intialiser_image(Image *img);
void creer_image(Image *img);

Bouton* initialiser_bouton();
void creer_bouton(Bouton *button);


Onglet* initialiser_onglet ();
void creer_onglet(Onglet *onglet);
void ajouter_page_onglet(Onglet *onglet,PageOnglet *page);

Label* initialiser_label();
void creer_label(Label *label);

ZoneSaisi* initialiser_entry();
void creer_entry(ZoneSaisi *zone);

Cadre* initialiser_cadre();
void creer_cadre(Cadre *cadre);

void creer_event_box(EventBox *event);
void ajouter_element_event_box(EventBox *event , GtkWidget *element);

Scale *initialiser_scale();
void creer_scale(Scale *scale);

void creer_table(Table *table);
void ajouter_element_table (Table *table, GtkWidget *element, int ligne,
                      int nbColonnesOccupe, int colonne,int nbLigneOccupe
                      );

void creer_cadre(Cadre *cadre);
void ajouter_element_cadre (Cadre *cadre, GtkWidget *element,Position pos);

void creer_checkbox(CheckBox *checkbox);

void creer_combo_box(ComboBox *comboBox);
void ajouter_element_combo_box(ComboBox *comboBox,char *element);

void creer_bouton_radio(BoutonRadio *radioButtonGrp,
                        BoutonRadio *radioButton,
                        char *element);
void ajouter_element_bouton_radio (BoutonRadio *radioButton,char *element);

void creer_toolbar(ToolBar *toolbar);
void associer_element(GtkWidget *conteneur,GtkWidget *elem,Position pos);

MenuBar* nouveau_menu_bar ();
void inserer_menu (MenuBar *menuBar, char *label);
void  inserer_menu_item (Menu *menu,char *labelMenu,MenuItem *mI);
void creer_menu (MenuBar *menuBar);



void creer_separateur (Separateur *separateur);


BoutonPoussoir* initialiser_bouton_poussoir();
void creer_bouton_poussoir(BoutonPoussoir *button);

void creer_bouton_spin( BoutonSpin* spin);


void creer_box(Box *box);
void ajouter_element_box(GtkWidget *box,GtkWidget *element,int position,
                         int expand,int fill, int padding);

void boite_dialogue(Dialog *dial, GtkWidget *parent);
 void ajouter_signal(GtkWidget *declencheur , gchar *action,
                      void (*callback) , gpointer *data);


