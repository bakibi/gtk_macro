#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "macro.h"


/***                      FONCTION INITIALISER                        ***/

/*
Nom:
     initialiser ( int argc, char *argv[] )
Entrees:
    int argc : argument du main
    char *argv[] : argument du main
Sorties:
      gtk initialisé
Type:
    void
Description:
    Cette fonction permet d'initialiser gtk
*/
void initialiser ( int argc, char *argv[] )
{
    gtk_init(&argc , &argv);
}//Fin de la fonction initialiser



/***                    FONCTION INITIALISER  IMAGE                   ***/

/*
Nom:
     vintialiser_image(Image *img)
Entrees:
    Image *img : variable de type Image à initialiser
Sorties:
    Img *img : variable image initialisé
Type:
    void
Description:
    Cette fonction permet d'initialiser une variable de type Image
*/
void intialiser_image(Image *img)
{
    //initialisation du chemin
    img->chemin=NULL;
    //initialisation de la position
    img->iPos.x = 0;
    img->iPos.y = 0;
}//fin de la fonction initialiser_image

/***                        FONCTION CREER IMAGE                      ***/
/*
Nom:
      creer_image(Image *img)
Entrees:
    Image *img : variable contenant les paramètres de l'image à créer
Sorties:
    Image *img : nouvelle image
Type:
    void
Description:
    Cette fonction permet de créer une nouvelle image
*/
void creer_image(Image *img)
{
    //on récupère l'image à partir du chemin en paramètre de la variable
    //et on crée l'image
    img->idImage = gtk_image_new_from_file(img->chemin);
    //position de l'image
    img->iPos.x=img->iPos.x;
    img->iPos.y=img->iPos.y;
}// fin de la fonction creer_image

/************************* CREATION FENETRE  ****************************/
/***                    FONCTION INITIALISER  FENETRE                  **/
/*
Nom:
     intialiser_fenetre()
Entrees:
    Pas d'entrées
Sorties:
    Fenetre *fenetre : une variable de type fenetre initialisée
Type:
    Fenetre* : pour retourner la variable initialisée
Description:
    Cette fonction permet d'initialiser une variable de type Fenetre
*/
Fenetre* initialiser_fenetre()
{
 //déclaration d'une variable de type Fenetre
 Fenetre *fenetre= (Fenetre*)malloc(sizeof(Fenetre));
 //test sur l'allocation
 if(!fenetre)
  {
    printf("\nEchec d'allocation (Fonction : initialiser_fenetre)");
    exit(EXIT_FAILURE);
  }// fin du if(!fenetre)
  // creation de la fenetre
  fenetre->idFenetre = gtk_window_new (W_TOPLEVEL);
  fenetre->fixed = gtk_fixed_new();//creation du fixed
  //initialisation des paramétres de la fenêtre
  //taille
  fenetre->wTaille.w=200;
  fenetre->wTaille.h=200;
  //titre
  fenetre->wTitre=strdup("Nouvelle fenêtre");
  //type
  fenetre->wType= W_TOPLEVEL;
  //pos debut
  fenetre->wPosDebut= W_CENTER;
  //position
  fenetre->wPos.x=-1;
  fenetre->wPos.y=-1;
  //couleur
  fenetre->wBg.blue=0xcccc;
  fenetre->wBg.red=0xcccc;
  fenetre->wBg.green=0xcccc;
  //icone
  fenetre->icone=NULL;
  //barre de défilement
  fenetre->wBarredefilement=JAMAIS;
  fenetre->wIBg = NULL;
  //et on retourne la variable initialisée
  return ((Fenetre*)fenetre);
}// fin de la fonction intialiser_fenetre

/***                      FONCTION CREER  FENETRE                     ***/
/*
Nom:
     creer_fenetre(Fenetre *win)
Entrees:
    Fenetre *win : variable qui contient les paramètres de la fenêtre
                   à créer
Sorties:
    Fenetre *win : fenêtre avec les paramètres donnés
Type:
    void
Description:
        Cette fonction permet de créer une fenêtre en appliquant
    les paramètres fournit
*/
void creer_fenetre(Fenetre *win)
{
  //définition du type
  win->idFenetre = gtk_window_new (win->wType);
  //definition du titre
  gtk_window_set_title(GTK_WINDOW(win->idFenetre),win->wTitre);
  // Taille de la fenêtre
  gtk_window_set_default_size(GTK_WINDOW(win->idFenetre),
                              win->wTaille.w,win->wTaille.h
                              );
  /*
   si  l'abscisse et l'ordonnée sont < à 0 on utilise une position p
   rédéfinie
    - 0 position aléatoire
    - 1 position centrée
    - 2 position de la souris
    - 3 position figée au centre
    - 4 position centre par rapport au parent
   */
  if((win->wPos.x < 0) && (win->wPos.y < 0))
    gtk_window_set_position(GTK_WINDOW(win->idFenetre),win->wPosDebut);
  else
  //sinon ça sera les coordonées saisies par l'utilisateur
    gtk_window_move(GTK_WINDOW(win->idFenetre), win->wPos.x, win->wPos.y);
  //modification de la couleur de fond
  gtk_widget_modify_bg(win->idFenetre, GTK_STATE_NORMAL,&(win->wBg));
  //association de l'icone à la fenêtre
  if(win->icone)
    gtk_window_set_icon_from_file(GTK_WINDOW(win->idFenetre),
                                  win->icone,NULL
                                  );
  if(win->wIBg)
  {
      GtkWidget *img = gtk_image_new_from_file(win->wIBg->chemin);
      gtk_container_add(GTK_CONTAINER(win->idFenetre),img);
  }
  // association du fixed à la fenêtre
  if(win->wBarredefilement != JAMAIS)
  {
      GtkWidget *barre;
      barre=gtk_scrolled_window_new(NULL,NULL);
      gtk_container_add(GTK_CONTAINER(win->idFenetre),barre);
      gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(barre),
                                            win->fixed
                                            );
      gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(barre),
                                     win->wBarredefilement,
                                     win->wBarredefilement
                                     );
  }//Fin if(win->wBarredefilement==1)
  else if (win->wConteneur == VBOX)
  {
    win->wBox=gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(win->idFenetre),win->wBox);
  }
  else if (win->wConteneur == HBOX)
  {
    win->wBox=gtk_hbox_new(TRUE,0);
    gtk_container_add(GTK_CONTAINER(win->idFenetre),win->wBox);
  }
  else
    gtk_container_add(GTK_CONTAINER(win->idFenetre),win->fixed);

 }//Fin de la fonction creer_fenetre

/**************************  CREATION ONGLETS  **************************/
/***                    FONCTION INITIALISER ONGLET                   ***/
/*
Nom:
     initialiser_onglet ()
Entrees:
    Pas d'entrées
Sorties:
    Onglet *onglet : une variable de type Onglet initialisée
Type:
    Onglet* : pour retourner la variable initialisée
Description:
    Cette fonction permet d'initialiser une variable de type Onglet
*/
Onglet* initialiser_onglet ()
{
    //déclaration de la variable
    Onglet *onglet=malloc(sizeof(Onglet));

    //Test sur l'allocation
    if(!onglet)
    {
      printf("\nEchec d'allocation (Fonction : initialiser_onglet)");
      exit(EXIT_FAILURE);
    }// fin du if(!onglet)
     //Initialisation des paramètres
    onglet->idNotebook=gtk_notebook_new();
    //position des onglets ( les pages )
    onglet->oPosOnglets=O_TOP;
    //bouton pour naviguer si trop de pageqs
    onglet->oSetScrollable=0;
    //position
    onglet->oPos.x=0;
    onglet->oPos.y=0;
    //couleur
    onglet->oColor.blue=0xcccc;
    onglet->oColor.red=0xcccc;
    onglet->oColor.green=0xcccc;

    //on retourne la variable paramétrée
    return ((Onglet*)onglet);
}//Fin de la fonction initialiser_onglet

/***                    FONCTION CREER ONGLET                   ***/
/*
Nom:
      creer_onglet(Onglet *onglet)
Entrees:
    Onglet *onglet : variable de type onglet contenant les paramètres
Sorties:
    Onglet *onglet : un onglet paramétré
Type:
    void
Description:
    Cette fonction permet de créer une variable paramétrée de type onglet,
  variable qui va permettre de contenir les pages d'onglets

*/
void creer_onglet(Onglet *onglet)
{
    //position des pages d'onglets
    if(onglet->oPosOnglets != -1)
        gtk_notebook_set_tab_pos(GTK_NOTEBOOK(onglet->idNotebook),
                                 onglet->oPosOnglets
                                 );
    // boutons navigations
    if(onglet->oSetScrollable)
         gtk_notebook_set_scrollable (GTK_NOTEBOOK(onglet->idNotebook),
                                       TRUE
                                     );
    //couleur
    gtk_widget_modify_bg(onglet->idNotebook, GTK_STATE_NORMAL,
                         &(onglet->oColor)
                         );
}//Fin de la fonction creer_onglet
/***                     FONCTION AJOUT PAGE ONGLET                   ***/
/*
Nom:
      jouter_page_onglet(Onglet *onglet,PageOnglet *page)
Entrees:
    Onglet *onglet : variable qui va contenir les pages d'onglet
    PageOnglet *page : la page qu'on veut insérer
Sorties:
    Onglet *onglet : un onglet avec une page en plus
Type:
    void
Description:
    Cette fonction permet d'insérer une page dans la variable onglet
*/
void ajouter_page_onglet(Onglet *onglet,PageOnglet *page)
{
   GtkWidget *labelPageOnglet;
   //initialisation conteneur de la page
   page->poFixed=gtk_fixed_new();
   //initialisation nom de la page
   labelPageOnglet=gtk_label_new(page->poLabel);
   //ajout de la page
   gtk_notebook_append_page(GTK_NOTEBOOK(onglet->idNotebook),
                            page->poFixed, labelPageOnglet
                            );
   //définition de la taille de la page
   gtk_widget_set_size_request(page->poFixed,
                               onglet->oTaille.w,onglet->oTaille.h
                               );
}//Fin de la fonction ajouter_page_onglet



/************************ CREATION BOUTON *******************************/
/***                    FONCTION INITIALISATION BOUTON                ***/
/*
Nom:
      initialiser_bouton()
Entrees:
    Pas d'entrées
Sorties:
    Bouton *button : une variable de type Bouton initialisée
Type:
    Bouton* : pour retourner la variable initialisée
Description:
    Cette fonction permet d'initialiser une variable de type Bouton
*/
Bouton* initialiser_bouton()
{
    //déclaration de la variable
    Bouton *button=malloc(sizeof(Bouton));

    //test sur l'allocation
    if(!button)
    {
      printf("\nEchec d'allocation (Fonction : initialiser_bouton)") ;
      exit(EXIT_FAILURE);
    }//Fin if(!button)

    //Initialisation des paramètres
    //position
    button->bPos.x= -1;
    button->bPos.y= -1;
    //taille
    button->bTaille.h = -1;
    button->bTaille.w = -1;
    //couleur
    button->bColor.blue=0xcccc;
    button->bColor.red=0xcccc;
    button->bColor.green=0xcccc;
    //type(avec ou sans reliefs)
    button->bRelief= BR_NORMAL;

    //on retourne le bouton initialisé
    return ((Bouton*)button);
}// fin de la fonction initialiser_bouton

/***                       FONCTION CREER BOUTON                      ***/
/*
Nom:
      creer_bouton(Bouton *button)
Entrees:
    Bouton *button : variable de type Bouton contenant les paramètres
Sorties:
    Bouton *button : un nouveau bouton paramétré
Type:
    void
Description:
    Cette fonction permet de créer une variable paramétrée de type Bouton
*/
void creer_bouton(Bouton *button)
{
  //la création d'un bouton, selon le type du boutton
  switch(button->bType)
  {
    //le type 0 bouton vide
    case B_VIDE://on crée un bouton vide
        button->idBouton=gtk_button_new();break;

    // le type 1 bouton avec un label
    case B_LABEL://on crée un bouton avec un label
        button->idBouton = gtk_button_new_with_label(button->bLabel);
        break;

    //le type avec raccourcis
    case B_MNEMONIC:
        button->idBouton = gtk_button_new_with_mnemonic(button->bLabel);
        break;

    //type bouton avec image
    case B_IMAGE :
        //création du bouton
        button->idBouton = gtk_button_new();
        //création de l'image
        button->bImg.idImage=gtk_image_new_from_file(button->bImg.chemin);
        //insértion de l'image dans le bouton
        gtk_button_set_image(GTK_BUTTON(button->idBouton),
                              button->bImg.idImage
                             );
        break;

    //le type bouton prédéfini du stock (image + nom + raccourci)
    //cas d'un bouton ajout
    case B_ADD:
        button->idBouton = gtk_button_new_from_stock(GTK_STOCK_ADD);
        break;
    //cas d'un bouton suppression
    case B_DELETE:
        button->idBouton = gtk_button_new_from_stock(GTK_STOCK_DELETE);
        break;
    //cas d'un bouton ouverture
    case B_OPEN:
        button->idBouton = gtk_button_new_from_stock(GTK_STOCK_OPEN);
        break;
    //cas d'un bouton fermeture
    case B_CLOSE:
        button->idBouton = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
        break;
    //cas d'un bouton information
    case B_ABOUT:
        button->idBouton = gtk_button_new_from_stock(GTK_STOCK_ABOUT);
        break;
    case B_FILECH:
        button->idBouton = gtk_file_chooser_button_new("Parcourir ...",
                                          GTK_FILE_CHOOSER_ACTION_OPEN);
        break;
    case B_COLOR:
        button->idBouton = gtk_color_button_new();
        break;
    case B_FONTCH:
         button->idBouton = gtk_font_button_new();
        break;
    case B_APPLY:
        button->idBouton = gtk_button_new_from_stock(GTK_STOCK_APPLY);
        break;
   }
   //Fin switch(button->bType)

    //relief du bouton
  //gtk_button_set_relief(GTK_BUTTON(button->idBouton),(button->bRelief));
  //couleur du bouton state normal
  gtk_widget_modify_bg(button->idBouton,GTK_STATE_NORMAL,
                       &(button->bColor)
                       );
  //taille du bouton
  if((button->bTaille.h >=0) && (button->bTaille.w>=0 ))
    //si c'est une image, on ne définit pas la taille,
    //elle sera détérminée selon la taille de l'image
    if(button->bType != B_IMAGE)
      gtk_widget_set_size_request(GTK_WIDGET(button->idBouton),
                                  button->bTaille.w,button->bTaille.h);

}// fin de la fonction creer_bouton

/****************************** CREATION LABEL **************************/
/***                    FONCTION INITIALISATION LABEL                 ***/
/*
Nom:
     initialiser_label()
Entrees:
    Pas d'entrées
Sorties:
    Label *label : une variable de type Label initialisée
Type:
    Label* : pour retourner la variable initialisée
Description:
    Cette fonction permet d'initialiser une variable de type Label
*/
Label* initialiser_label()
{
    //déclaration de la variable
    Label *label;
    label= (Label*)malloc(sizeof(Label));
    //test sur l'allocation
    if(!label)
    {
      printf("\nEchec d'allocation (Fonction : initialiser_label)") ;
      exit(EXIT_FAILURE);
    }//Fin if(!label)
    //paramétrage
    //texte du label
    label->lTexte = NULL;
    label->idLabel = gtk_label_new(label->lTexte);
    //position
    label->lPos.x = 0;
    label->lPos.y = 0;
    label->lJustify= LEFT;
    //style
    label->lStyle = 0;

    //on retourne la variable initialisée
    return ((Label*)label);
}// fin de la fonction intialiser_label

/***                      FONCTION CREER LABEL                        ***/
/*
Nom:
      creer_label(Label *label)
Entrees:
    Label *label : variable de type Label contenant les paramètres
Sorties:
    Label *label : un nouveau label paramétré
Type:
    void
Description:
    Cette fonction permet de créer une variable paramétrée de type Label
*/
void creer_label(Label *label)
{
    //Variable qui va contenir le texte converti
    gchar *TexteConverti;

    //converstion du texte, au cas où il comporterait un caractère accentué
     TexteConverti = g_locale_to_utf8(label->lTexte, -1, NULL, NULL, NULL);
    //Alignement du texte
    gtk_label_set_justify(GTK_LABEL(label->idLabel),(label->lJustify));
    // utiliser du format ou  pas
    //si un format n'a pas été demandé, on crée le label
     if(!(label->lStyle))
    {
      gtk_label_set_label(GTK_LABEL(label->idLabel),TexteConverti);
    }//Fin if(!(label->lStyle))
    //Sinon on affecte le format au text et on crée le label
    if(label->lStyle == 1)
    {
      char format[200];
      strcpy(format,"<span font_desc=\"");
      strcat(format,label->lFormat.tPolice);
      strcat(format," ");
      strcat(format,label->lFormat.tStyle);
      strcat(format," ");
      strcat(format,label->lFormat.tSize);
      strcat(format,"\"");
      strcat(format," weight=\"");
      strcat(format,label->lFormat.tWeight);
      strcat(format,"\"");
      strcat(format," foreground=\"#");
      strcat(format,label->lFormat.tColor);
      strcat(format,"\"");
      strcat(format," background=\"#");
      strcat(format,label->lFormat.fColor);
      strcat(format,"\"");
      strcat(format," underline=\"");
      strcat(format,label->lFormat.tUnderline);
      strcat(format,"\"");
      strcat(format," strikethrough=\"");
      strcat(format,label->lFormat.tBarer);
      strcat(format,"\">");
      strcat(format,TexteConverti);
      strcat(format,"</span>");
      //application du format

      gtk_label_set_markup(GTK_LABEL(label->idLabel),format);

    }// fin if (label->lstyle == 1)

  g_free(TexteConverti);

}// fin de la fonction creer_label


/*********************** FONCTION DE CREATION D'UNE TABLE ***************/
/***                      FONCTION CREER TABLE                        ***/
/*
Nom:
      creer_table(Table *table)
Entrees:
    Table *table : variable de type Table à créer
Sorties:
    Table *table : une nouvelle table
Type:
    void
Description:
    Cette fonction permet de créer une variable  de type Table
 (une variable de type Table peut aider à organiser ses widgets)
*/
void creer_table(Table *table)
{
 //creation de la table,nombre de ligne et colonne contenu dans la variable
 table->table=gtk_table_new(table->nbLignes,table->nbColonnes,
                            table->homogene
                            );
}//Fin de la fonction creer_table
/***                    FONCTION AJOUTER ELEMENT TABLE                ***/
/*
Nom:
      ajouter_element_table (Table *table, GtkWidget *element, int ligne,
                      int nbColonnesOccupe, int colonne,int nbLigneOccupe
                      )
Entrees:
    Table *table : table dans laquelle on va insérer un widget
    GtkWidget *element : le widget à insérer
    int ligne : la ligne où le widget doit être inséré
    int nbColonnesOccupe : nombre de colonne que le widget va occuper
    int colonne : la colonne où le widget doit être inséré
    int nbLigneOccupe : le nombre de ligne que le widget va occuper
Sorties:
    Table *table : la table avec un élément en plus
Type:
    void
Description:
    Cette fonction permet d'insérer un widget dans une table
*/
void ajouter_element_table (Table *table, GtkWidget *element, int ligne,
                      int nbColonnesOccupe, int colonne,int nbLigneOccupe
                      )
{
 //ajout du widget dans la table
  gtk_table_attach_defaults(GTK_TABLE(table->table),element,
                             (colonne-1),(colonne+nbColonnesOccupe-1),
                             (ligne-1),(ligne+nbLigneOccupe-1)
                            );
}//Fin de la fonction ajouter_element


/************************ Creation des zones de saisies  ****************/
/***               FONCTION INITIALISATION ZONE SAISI                 ***/
/*
Nom:
     initialiser_entry()
Entrees:
    Pas d'entrées
Sorties:
    ZoneSaisi *entry : une variable de type ZoneSaisi initialisée
Type:
    ZoneSaisi* : pour retourner la variable initialisée
Description:
    Cette fonction permet d'initialiser une variable de type ZoneSaisi
*/
ZoneSaisi* initialiser_entry()
{
    //déclaration de la variable
    ZoneSaisi *entry=(ZoneSaisi*)malloc(sizeof(ZoneSaisi));

    //test sur l'allocation
    if(!entry)
    {
      printf("\nEchec d'allocation (Fonction : initialiser_entry)") ;
      exit(EXIT_FAILURE);
    }//Fin if(!entry)
    //initialisation des paramètres
    //text présent dans la zone
    entry->zText = NULL;
    //position
    entry->zPos.x=0;
    entry->zPos.y=0;
    //taille
    entry->zTaille.h =20;
    entry->zTaille.w =100;
    //visibilité du texte
    entry->zVisible =1;
    //nombre de caractères max
    entry->zMaxlenght=60;
    //position du curseur
    entry->zCursorposition=0;
    //caractère affiché si visibilité à 0
    entry->zTremp='*';

    //on retourne la variable initialisée
    return ((ZoneSaisi*)entry);
}// fin de la fonction initialiser_entry
/***                      FONCTION CREER ZONE SAISI                   ***/
/*
Nom:
      creer_entry(ZoneSaisi *zone)
Entrees:
    ZoneSaisi *zone : variable de type ZoneSaisi contenant les paramètres
Sorties:
    ZoneSaisi *zone : une nouvelle zone de saisi paramétré
Type:
    void
Description:
  Cette fonction permet de créer une variable paramétrée de type ZoneSaisi
*/
void creer_entry(ZoneSaisi *zone)
{
    //création de la zone de saisie, avec la taille max en paramètre
    zone->idZone=gtk_entry_new_with_max_length(zone->zMaxlenght);
    //texte présent initialement dans la zone
    if(zone->zText)
       gtk_entry_set_text(GTK_ENTRY(zone->idZone),zone->zText);
    //Fin if(zone->zText)

    //position curseur
    gtk_entry_set_position (GTK_ENTRY(zone->idZone),zone->zCursorposition);
    //taille de la zone
    gtk_widget_set_size_request(GTK_WIDGET(zone->idZone),zone->zTaille.w,zone->zTaille.h);
    //si le texte saisi doit être affiché ou pas
    if(zone->zVisible == 0)
    {
      gtk_entry_set_visibility(GTK_ENTRY(zone->idZone),FALSE);
      gtk_entry_set_invisible_char(GTK_ENTRY(zone->idZone),zone->zTremp);
    }//fin if(zone->zVisible == 0)

    //alignement du texte
    gtk_entry_set_alignment(GTK_ENTRY(zone->idZone),zone->zCursorposition);
}// fin de la fonction creer_entry


/******************************* FONCTION CREATION CADRE ****************/
/***                  FONCTION INITIALISATION CADRE                   ***/
/*
Nom:
     initialiser_cadre()
Entrees:
    Pas d'entrées
Sorties:
    Cadre *cadre: une variable de type Cadre initialisée
Type:
    Cadre* : pour retourner la variable initialisée
Description:
    Cette fonction permet d'initialiser une variable de type Cadre
*/
Cadre* initialiser_cadre()
{
    //déclaration de la variable
    Cadre *cadre=(Cadre*)malloc(sizeof(Cadre));

    //test sur l'allocation
    if(!cadre)
    {
      printf("\nEchec d'allocation (Fonction : initialiser_cadre)");
      exit(EXIT_FAILURE);
    }//Fin if(!cadre)

    //initialisation du conteneur
    cadre->cFixed=gtk_fixed_new();
    //définition du label
    cadre->idCadre=gtk_frame_new("Cadre");
    //initialisation des autres parametres
    cadre->cLabel=NULL;
    //couleur
    cadre->cCouleur.blue=0xcccc;
    cadre->cCouleur.red=0xcccc;
    cadre->cCouleur.green=0xcccc;
    //position du texte
    cadre->cPosTexteX=0.0;
    cadre->cPosTexteY=0.5;
    //style du cadre
    cadre->cStyle=C_SHADOW_ETCHED_IN_OUT;
    //taille du cadre
    cadre->cTaille.h=100;
    cadre->cTaille.w=100;

    //on retourne la variable initialisée
    return ((Cadre*)cadre);
}//Fin de la fonction initialiser_cadre
/***                        FONCTION CREER CADRE                      ***/
/*
Nom:
      creer_entry(ZoneSaisi *zone)
Entrees:
    Cadre *cadre : variable de type Cadre contenant les paramètres
Sorties:
    Cadre *cadre : un nouveau cadre paramétré
Type:
    void
Description:
  Cette fonction permet de créer une variable paramétrée de type Cadre
*/
void creer_cadre(Cadre *cadre)
{
    //label du cadre
    gtk_frame_set_label(GTK_FRAME(cadre->idCadre),cadre->cLabel);
    //style du cadre
    gtk_frame_set_shadow_type(GTK_FRAME(cadre->idCadre),cadre->cStyle);
    //mise en place du conteneur du cadre
    gtk_container_add(GTK_CONTAINER(cadre->idCadre),cadre->cFixed);
    //position du texte
    gtk_frame_set_label_align(GTK_FRAME(cadre->idCadre),
                              cadre->cPosTexteX,cadre->cPosTexteY
                              );
   //définition de la couleur
   gtk_widget_modify_bg(cadre->idCadre,GTK_STATE_NORMAL,&cadre->cCouleur);
   //définition de la taille
   gtk_widget_set_size_request(cadre->cFixed,cadre->cTaille.w,
                               cadre->cTaille.h
                            );
}//Fin de la fonction creer cadre

/******************* FONCTIONS CREATION EVENT BOX ***********************/
/***                        CREER EVENT BOX                           ***/
/*
Nom:
      creer_event_box(EventBox *event)
Entrees:
    EventBox *event : variable de type EventBox
Sorties:
    EventBox *event : une nouvelle event box
Type:
    void
Description:
   Cette fonction permet de créer une event box. Les events box permettent
 d'associer des événements à des widgets qui ne peuvent pas en avoir
 naturellement (les labels par exemple)
*/
void creer_event_box(EventBox *event)
{
    //création de l'event box
    event->idEvent = gtk_event_box_new();
}//Fin de la fonction creer_event_box
/***                    AJOUT ELEMENT EVENT BOX                       ***/
/*
Nom:
      ajouter_element_event_box(EventBox *event , GtkWidget *element)
Entrees:
    EventBox *event : l'EventBox qui va contenir le widget
    GtkWidget *element : l'element à insérer dans l'event box
Sorties:
    EventBox *event : l'event box avec un element en plus
Type:
    void
Description:
   Cette fonction permet d'insérer un widget dans l'event box
*/
void ajouter_element_event_box(EventBox *event , GtkWidget *element)
{
    gtk_container_add(GTK_CONTAINER (event->idEvent),element);
    gtk_widget_set_events(event->idEvent,event->evEvent);
}//Fin de la fonction ajouter_element_event_box


/*************************** FONCTION CREATION SCALE ********************/
/***                  FONCTION INITIALISATION SCALE                   ***/
/*
Nom:
     initialiser_scale()
Entrees:
    Pas d'entrées
Sorties:
    Scale *scale: une variable de type Scale initialisée
Type:
    Scale* : pour retourner la variable initialisée
Description:
    Cette fonction permet d'initialiser une variable de type Scale. Une
  telle variable va permettre de creer un sélécteur de valeurs numériques.
*/
Scale* initialiser_scale()
{
  //déclaration de la variable
  Scale *scale=(Scale*)malloc(sizeof(Scale));
  //test sur l'allocation
  if(!scale)
    {
      printf("\nEchec d'allocation (Fonction : initialiser_scale)") ;
      exit(EXIT_FAILURE);
    }//Fin if(!scale)
  //paramétrage
  //si la valeur va être affiché
  scale->afficherValeur=1;
  // l'intervalle
  scale->min=0;
  scale->max=100;
  //le pas
  scale->pas=1;
  //la taille
  scale->sTaille.w=200;
  scale->sTaille.h=30;
  //position des valeurs
  scale->posValeur=S_TOP;
  //type de scale(horizontal ou vertical)
  scale->type=HORIZONTAL;
  //nombre de chiffres après la virgule (initialement pas de chiffres)
  scale->scaleDigit=-1;

  //on retourne la variable initialisée
  return ((Scale*)scale);
}//Fin de la fonction initialiser_scale

/***                       FONCTION CREER SCALE                       ***/
/*
Nom:
     creer_scale(Scale *scale)
Entrees:
    Scale *scale : variable contenant les paramètres du scale à créer
Sorties:
    Scale *scale: un nouveau scale
Type:
   Void
Description:
    Cette fonction permet de créer une variable paramétrée de type Scale
*/
void creer_scale(Scale *scale)
{
    //définition type scale (vertical ou bien horizontal
    if(scale->type == HORIZONTAL)//scale horizontal
      scale->idScale=gtk_hscale_new_with_range(scale->min,
                                               scale->max,scale->pas
                                               );
    else//scale vertical
      scale->idScale=gtk_vscale_new_with_range(scale->min,scale->max,
                                               scale->pas
                                               );

    //affichage ou pas des valeurs associées
    gtk_scale_set_draw_value(GTK_SCALE(scale->idScale),
                             scale->afficherValeur
                             );
    //nombre de chiffres après la virgule
    if(scale->scaleDigit > 0)
      gtk_scale_set_digits(GTK_SCALE(scale->idScale),scale->scaleDigit);
    //position valeur
    gtk_scale_set_value_pos(GTK_SCALE(scale->idScale),scale->posValeur);
    //taille du scale
    gtk_widget_set_size_request(scale->idScale,scale->sTaille.w,
                                scale->sTaille.h
                                );

}//Fin de la fonction creer_scale

/**************************** CREATION CHECK BOX ************************/
/*
Nom:
     creer_checkbox(CheckBox *checkbox)
Entrees:
    CheckBox *checkbox: variable qui va contenir la checkbox
Sorties:
    Checkbox *checkbox : nouvelle checkbox
Type:
   Void
Description:
    Cette fonction permet de créer une variable  de type CheckBox
*/
void creer_checkbox(CheckBox *checkbox)
{
 //création de la checkbox
   checkbox->idCheck=gtk_check_button_new_with_label(checkbox->cLabel);
}//fin de la fonction creer_checkbox

/***************************** CREATION COMBO BOX************************/
/***                       FONCTION CREER COMBO BOX                   ***/
/*
Nom:
     creer_combo_box(ComboBox *comboBox)
Entrees:
    ComboBox *comboBox: variable qui va contenir la combboox
Sorties:
    ComboBox *comboBox : nouvelle combobox
Type:
   Void
Description:
    Cette fonction permet de créer une variable  de type ComboBox
*/
void creer_combo_box(ComboBox *comboBox)
{
   comboBox->idComboBox=gtk_combo_box_new_text();
}//Fin de la fonction creer_combo_box

/***                FONCTION AJOUTER ELEMENT COMBO BOX                ***/
/*
Nom:
     ajouter_element_combo_box(ComboBox *comboBox,char *element)
Entrees:
    ComboBox *comboBox: la combobox dans laquelle on veut insérer un elmt
    char *element : l'élement à insérer
Sorties:
    ComboBox *comboBox : combobox avec un élément en plus
Type:
   Void
Description:
    Cette fonction permet d'insérer un élément dans une combobox
*/
void ajouter_element_combo_box(ComboBox *comboBox,char *element)
{
  gtk_combo_box_append_text(GTK_COMBO_BOX(comboBox->idComboBox),element);
}//Fin de la fonction ajouter_element_combo_box


/********************* CREATION BOUTON RADIO ****************************/
/***                     FONCTION CREER BOUTON RADIO                  ***/
/*
Nom:
     creer_bouton_radio(BoutonRadio *radioButtonGrp,
                        BoutonRadio *radioButton,
                        char *element)
Entrees:
    BoutonRadio *radioButtonGrp : le radio bouton initial, permet
                                 déterminer le groupe auquel appartient
                                 un bouton radio
    BoutonRadio *radioButton : le radio bouton à insérer
    char *element : le label du bouton radio

Sorties:
    ComboBox *comboBox : nouvelle combobox
Type:
   Void
Description:
    Cette fonction permet de créer un nouveau bouton radio.
  -Si le paramètre radioButtonGrp est égal à NULL, on crée un nouveau
    un nouveau group de radio bouton sera crée, avec en tete
    l'élément qu'on aura inséré
  -Si le paramètre n'est pas NULL, on récupère le groupe du bouton
    et c'est dans ce dernier que le nouveau bouton radio sera inséré
*/
void creer_bouton_radio(BoutonRadio *radioButtonGrp,
                        BoutonRadio *radioButton,
                        char *element)
{
 //Si radioButtonGrp est égale à nulL, ça veut dire qu'on crée un nouveau
 //groupe de bouton radio
 if(radioButtonGrp == NULL)
  radioButton->idBoutonRadio=gtk_radio_button_new_with_label(NULL,element);
 //sinon on insert dans le groupe representé par radioButtonGrp
 else
  radioButton->idBoutonRadio=gtk_radio_button_new_with_label_from_widget
                                        (GTK_RADIO_BUTTON
                                         (radioButtonGrp->idBoutonRadio),
                                          element
                                        );
}//Fin de la fonction creer_bouton_radio


/************************* FONCTIONS D'AFFICHAGE ************************/
/***                      FONCTION AFFICHER TOUT                      ***/
/*
Nom:
     afficher_tout (GtkWidget* wid)
Entrees:
    GtkWidget* wid : le widget à afficher
Sorties:
   GtkWidget* wid : le widget et tout ses descendants affiché
Type:
   Void
Description:
    Cette fonction permet d'afficher un widget et tout ceux qu'il contient
*/
void afficher_tout (GtkWidget* wid)
{
    gtk_widget_show_all(wid);
}//Fin de la fonction afficher_tout
/***                       FONCTION AFFICHER                          ***/
/*
Nom:
     afficher_tout (GtkWidget* wid)
Entrees:
    GtkWidget* wid : le widget à afficher
Sorties:
   GtkWidget* wid : le widget affiché
Type:
   Void
Description:
    Cette fonction permet d'afficher un widget
*/
void afficher(GtkWidget *wid)
{
   gtk_widget_show(wid);
}//Fin de la fonction afficher
/***                        FONCTION CACHER TOUT                      ***/
/*
Nom:
    cacher_tout (GtkWidget* wid)
Entrees:
    GtkWidget* wid : le widget à cacher
Sorties:
   GtkWidget* wid : le widget et tout ses descendants cachés
Type:
   Void
Description:
    Cette fonction permet de cacher un widget et tout ceux qu'il contient
*/
void cacher_tout (GtkWidget* wid)
{
    gtk_widget_hide_all(wid);
}//fin de la fonction cacher_tout
/***                        FONCTION CACHER                           ***/
/*
Nom:
    cacher_tout (GtkWidget* wid)
Entrees:
    GtkWidget* wid : le widget à cacher
Sorties:
   GtkWidget* wid : le widget  cachés
Type:
   Void
Description:
    Cette fonction permet de cacher un widget
*/
void cacher(GtkWidget *wid)
{
   gtk_widget_hide(wid);
}//Fin de la fonction cacher


/**********************     FONCTION BOUCLE EVENEMENT   *****************/
/*
Nom:
    boucle_evenement()
Entrees:
    Pas d'entrées
Sorties:
   Pas de sorties
Type:
   Void
Description:
    Cette fonction permet de faire entrer Gtk+ dans une boucle infi
*/
void boucle_evenement()
{
    gtk_main();
}//Fin de la fonction boucle_evenement


/************* ******************************/



/********** FONCTIONS CREATION MENU ***************/

/********** FONCTIONS CREATION MENU ***************/
MenuBar* nouveau_menu_bar ()
{
    MenuBar *nMenuBar=malloc(sizeof(MenuBar));

    if(!nMenuBar)
    {
        printf("\nEchec de l'allocation.");
        exit(EXIT_FAILURE);
    }

    nMenuBar->menuBar=gtk_menu_bar_new();
    nMenuBar->listeMenu=NULL;

    return ((MenuBar*)nMenuBar);
}

void inserer_menu (MenuBar *menuBar, char *label)
{
    Menu *courant=menuBar->listeMenu;
    Menu *elem=malloc(sizeof(Menu));/** VERIFIER ALLOCATION **/

    elem->label=g_strdup_printf("%s",label);
    elem->listeMenuItem=NULL;
    elem->suivant=NULL;

    if(!courant)
        menuBar->listeMenu=elem;

    else
    {
        while(courant->suivant)
            courant=courant->suivant;
        courant->suivant=elem;
    }
}//Fin de la fonction inserer_menu

void  inserer_menu_item (Menu *menu,char *labelMenu,MenuItem *mI)
{
   Menu *courant=menu;
   MenuItem *parcours;
//   MenuItem *menuItem=malloc(sizeof(MenuItem));/** FAIRE TEST ALLOCATION **/
   int existe=0;

   //On vérifie que le labelMenu entrée existe bien, pour
   // ensuite insérer le menuItem
   while(courant)
   {
       if( !strcmp(courant->label,labelMenu))
       {
           existe=1;
           break;
       }//Fin if( !strcmp(courant->label,labelMenu))
     courant=courant->suivant;
   }//Fin while(courant)

   if(existe)
   {

      if(!mI->type)
         mI->menuItem = gtk_menu_item_new_with_label(mI->label);
      if(mI->type)
         mI->menuItem = gtk_menu_item_new_with_mnemonic(mI->label);

       mI->sous_menu=NULL;
       mI->suivant=NULL;

       parcours=courant->listeMenuItem;

       if(!parcours)
         courant->listeMenuItem=mI;
       else
       {
          while(parcours->suivant)
            parcours=parcours->suivant;
          parcours->suivant=mI;
       }

   }//Fin if(existe)

}//Fin de la fonction inserer_menu_item

void creer_menu (MenuBar *menuBar)
{
   GtkWidget *pMenu;
   GtkWidget *pMenuItem;
   GtkWidget *separateur;

   Menu *courantMenu=menuBar->listeMenu;
   MenuItem *courantMenuItem;


  while(courantMenu)
  {
    courantMenuItem=courantMenu->listeMenuItem;

    pMenu = gtk_menu_new();

    pMenuItem = gtk_menu_item_new_with_label(courantMenu->label);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar->menuBar), pMenuItem);


    while(courantMenuItem)
    {
      //si séparateur
      if(courantMenuItem->separateur)
      {
        separateur=gtk_separator_menu_item_new();
        gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), separateur);
      }

      gtk_menu_shell_append(GTK_MENU_SHELL(pMenu),
                            courantMenuItem->menuItem);
      courantMenuItem=courantMenuItem->suivant;
    }//Fin while(courantMenuItem)

     courantMenu=courantMenu->suivant;
   }//Fin while(courantMenu)

}//Fin de la fonction creer_menu




/////////////////////////////


/******************** Fonction création séparateur **********************/
/*
Nom:
     creer_separateur (Separateur *separateur)
Entrees:
    Separateur *separateur: variable qui va contenir le séparateur
Sorties:
    Separateur *separateur : nouveau séparateur
Type:
   Void
Description:
    Cette fonction permet de créer un séparateur(vertical ou bien
   horizontal)
*/
void creer_separateur (Separateur *separateur)
{
    //on définit le type de séparateur demandé
    if(!separateur->type)//horizontal
        separateur->idSeparateur=gtk_hseparator_new();
    else//vertical
        separateur->idSeparateur=gtk_vseparator_new();
    //on définit la taille du séparateur
    gtk_widget_set_size_request(separateur->idSeparateur,
                                separateur->sTaille.w,separateur->sTaille.h
                                );
}//Fin de la fonction creer_separateur


/**********************   FONCTION ASSOCIER ELEMENT   *******************/
/*
Nom:
     associer_element(GtkWidget *conteneur,GtkWidget *elem,Position pos)
Entrees:
    GtkWidget *conteneur : le conteneur où sera placé le widget
    GtkWidget *elem : le widget à insérer dans le conteneur
    Position pos : position du widget à insérer
Sorties:
    GtkWidget *conteneur : le conteneur avec un élément en plus
Type:
   Void
Description:
    Cette fonction permet d'insérer un widget dans un conteneur de type
  fixed
*/
void associer_element(GtkWidget *conteneur,GtkWidget *elem,Position pos)
{
    //on insert un widget dans un conteneur de type fixed
    if((pos.x>=0)&&(pos.y>=0))
     gtk_fixed_put(GTK_FIXED(conteneur),elem,pos.x,pos.y);
    //si une position incorrecte est fournie, on affiche
    //un message d'erreur
    else
    {
      printf("\nErreur : Position de l'element incorrecte!!");
      printf(" (Fonction : associer_element)");
    }//Fin else

}//Fin de la fonction associer_separateur


/*********************** FONCTIONS CREATION BOX *************************/
/***                        FONCTION CREER BOX                        ***/
/*
Nom:
     creer_box(Box *box)
Entrees:
    Box *box : variable qui va contenir la box
Sorties:
    Box *box : une nouvelle box
Type:
   Void
Description:
    Cette fonction permet de créer un conteneur de type box (horizontal
  ou bien vertical)
*/
void creer_box(Box *box)
{
    //on crée une box selon le type souhaité
    //création d'une box verticale
    if(box->bType == VERTICAL)
       box->idVBox=gtk_vbox_new(box->bHomogene,box->bSpacing);
    //création d'une box horizontale
    if(box->bType == HORIZONTAL)
       box->idVBox=gtk_hbox_new(box->bHomogene,box->bSpacing);
    //taille de la box
    gtk_widget_set_size_request(box->idVBox,box->bTaille.w,
                                box->bTaille.h);
}//Fin de la fonction creer_box

/***                    FONCTION AJOUTER ELEMENT BOX                  ***/
/*
Nom:
     ajouter_element_box(GtkWidget *box,GtkWidget *element,int position,
                         int expand,int fill,int padding)
Entrees:
    GtkWidget *box : la box où on veut insérer un widget
    GtkWidget *element : le widget à insérer
    int position : position où on veut insérer (debut,fin)
    int expand : si le widget va occupper toute l'espace disponible
    int fill  : si le widget va remplir toute l'espace qui lui est résérvé
    int padding : parge intérieur

Sorties:
    Box *box : une nouvelle box
Type:
   Void
Description:
    Cette fonction permet de créer un conteneur de type box (horizontal
  ou bien vertical)
*/
void ajouter_element_box(GtkWidget *box,GtkWidget *element,int position,
                         int expand,int fill,int padding)
{
    //on place l'élément selon la position souhaitée
    //on place ici l'element en debut de box
    if(position == DEBUT)
        gtk_box_pack_start(GTK_BOX(box),element,expand,fill,padding);
    //on place ici l'element en fin de box
    if(position == FIN)
        gtk_box_pack_end(GTK_BOX(box),element,expand,fill,padding);
}//fin de la fonction inserer_element_box




void boite_dialogue(Dialog *dial, GtkWidget *parent)
{


    dial->idDialog=gtk_dialog_new_with_buttons(dial->dLabel,
                                   GTK_WINDOW(parent),
                                   GTK_DIALOG_MODAL,
                                   GTK_STOCK_OK,GTK_RESPONSE_OK,
                                   NULL
                                    );
    gtk_widget_show_all(dial->idDialog);




    switch (gtk_dialog_run(GTK_DIALOG(dial->idDialog)))
    {
       //case GTK_RESPONSE_OK:
       /* L utilisateur annule */
       //case GTK_RESPONSE_CANCEL:
       //case GTK_RESPONSE_NONE:
    }

   // gtk_widget_destroy(dial->idDialog);
}//Fin de la fonction boite_dialogue

/*************************** CREATION BOUTON POUSSOIR *******************/
/***              FONCTION INITIALISATION BOUTON POUSSOIR             ***/
/*
Nom:
      initialiser_bouton_poussoir()
Entrees:
    Pas d'entrées
Sorties:
  BoutonPoussoir *button : une variable de type BoutonPoussoir initialisée
Type:
    BoutonPoussoir* : pour retourner la variable initialisée
Description:
   Cette fonction permet d'initialiser une variable de type BoutonPoussoir
*/
BoutonPoussoir* initialiser_bouton_poussoir()
{
    BoutonPoussoir *button=malloc(sizeof(BoutonPoussoir));

    //Test sur l'allocation
    if(!button)
    {
      printf("\nEchec d'allocation (Fonction : initialiser_bouton_poussoir)");
      exit(EXIT_FAILURE);
    }// fin du if(!button)

    //on initialise la variable
    button->bpLabel=NULL;
    button->bpPos.x=-1;
    button->bpPos.y=-1;
    button->bpTaille.h=-1;
    button->bpTaille.w=-1;
    button->bpColor.blue=0xcccc;
    button->bpColor.green=0xcccc;
    button->bpColor.red=0xcccc;
    button->bpEtat=FALSE;//button relaché

    //on retourne la variable initialisée
    return ((BoutonPoussoir*)button);
}//Fin de la fonction initialiser_bouton_poussoir

/***                 FONCTION CREER BOUTON POUSSOIR                   ***/
/*
Nom:
      creer_bouton_poussoir(BoutonPoussoir *button)
Entrees:
    BoutonPoussoir *button : variable de type BoutonPoussoir
                                contenant les paramètres
Sorties:
    BoutonPoussoir *button : un nouveau bouton paramétré
Type:
    void
Description:
    Cette fonction permet de créer une variable paramétrée de type
  BoutonPoussoir
*/
void creer_bouton_poussoir(BoutonPoussoir *button)
{
 //on crée le bouton
  button->idBoutonPoussoir=
             gtk_toggle_button_new_with_label(button->bpLabel);

  //couleur du bouton state normal
 gtk_widget_modify_bg(button->idBoutonPoussoir,GTK_STATE_NORMAL,
                       &(button->bpColor)
                       );
  //taille du bouton
  if((button->bpTaille.h >=0) && (button->bpTaille.w>=0 ))
      gtk_widget_set_size_request(GTK_WIDGET(button->idBoutonPoussoir),
                                  button->bpTaille.w,button->bpTaille.h);
  //l'état du bouton
 gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button->idBoutonPoussoir),
                                button->bpEtat
                             );
}// fin de la fonction creer_bouton

/************************* FONCTION CREER SPIN ***************************/
void creer_bouton_spin( BoutonSpin* spin)
{
    spin->idSpin = gtk_spin_button_new_with_range(spin->sMin,spin->sMax,
                                                  spin->sPas);
    gtk_widget_set_size_request(spin->idSpin , spin->sTaille.w , spin->sTaille.h);
}


/**************************   FONCTION SIGNAL   *************************/
/***                                                                  ***/
/*
Nom:
      creer_toolbar_principale(Toolbar *toolbar)
Entrees:
   Toolbar *toolbar: variable de type toolbar
Sorties:
    Une barre d outils paramétrée
Type:
    void
Description:
    Cette fonction permet de créer une variable de type toolbar pour la
    fenêtre principale.
*/
 void ajouter_signal(GtkWidget *declencheur , gchar *action,
                      void (*callback) , gpointer *data)
 {
     g_signal_connect(G_OBJECT(declencheur),action,G_CALLBACK(callback),
                      data);
 }
