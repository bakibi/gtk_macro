
#include "application.h"



 
/*
 
 * Cette fonction initialise la structure FenetreInscription
 * ENTREES   : NONE
 * SORTIE : FenetreInscription Initialise
 */
FenetreInscription *initialiser_FenetreInscription()
{
    FenetreInscription *fen;
    fen = (FenetreInscription *)malloc(sizeof(FenetreInscription));
    
    //initialisation de la table
    fen->mother =(Table *)malloc(sizeof(Table));
    
    
    //initialisation des label
    fen->adresse = initialiser_label();
    fen->email = initialiser_label();
    fen->mdp1 = initialiser_label();
    fen->mdp2 = initialiser_label();
    fen->nom = initialiser_label();
    fen->nomutilisateur = initialiser_label();
    fen->prenom = initialiser_label();
    
    //initialisation des zone de saisie
    fen->i_add1 = initialiser_entry();
    fen->i_add2 = initialiser_entry();
    fen->i_email = initialiser_entry();
    fen->i_mdp1 = initialiser_entry();
    fen->i_mdp2 = initialiser_entry();
    fen->i_nom = initialiser_entry();
    fen->i_nomutilisateur = initialiser_entry();
    fen->i_prenom  = initialiser_entry();
    
    //initialisation des bouton;
    fen->valider = initialiser_bouton();
    fen->reset = initialiser_bouton();
    
    //initialisation du cadre
    fen->cadre = initialiser_cadre();
    
    return (FenetreInscription *)fen;
}//fin de la fonction



/*
 Cette fonction cree la fenetre qui contient Les inforamtion de l inscrition
 ENTREES : FenetreInscription
 SORTIES : NONE 
 */
void creation_FenetreInscription(FenetreInscription *fen)
{
   
    //creation des label
    fen->adresse->lTexte = (char *)malloc(sizeof(char)*10);
    fen->email->lTexte = (char *)malloc(sizeof(char)*10);
    fen->mdp1->lTexte = (char *)malloc(sizeof(char)*20);
    fen->mdp2->lTexte = (char *)malloc(sizeof(char)*20);
    fen->nom->lTexte = (char *)malloc(sizeof(char)*10);
    fen->nomutilisateur->lTexte = (char *)malloc(sizeof(char)*10);
    fen->prenom->lTexte = (char *)malloc(sizeof(char)*10);
     
    strcpy(fen->adresse->lTexte,"Adresse :");
    strcpy(fen->email->lTexte,"*Email :");
    strcpy(fen->mdp1->lTexte,"*Mot de passe :");
    strcpy(fen->mdp2->lTexte,"*Confirmation Mot de passe :");
    strcpy(fen->nom->lTexte,"Nom :");
    strcpy(fen->nomutilisateur->lTexte,"*Nom d'utilisateur :");
    strcpy(fen->prenom->lTexte,"Prenom :");
    creer_label(fen->adresse);
    creer_label(fen->email);
    creer_label(fen->mdp1);
    creer_label(fen->mdp2);
    creer_label(fen->nom);
    creer_label(fen->nomutilisateur);
    creer_label(fen->prenom);
   
    //creation des zone de saisie
    creer_entry(fen->i_add1);
    creer_entry(fen->i_add2);
    creer_entry(fen->i_email);
    creer_entry(fen->i_mdp1);
    creer_entry(fen->i_mdp2);
    gtk_entry_set_visibility(GTK_ENTRY(fen->i_mdp1->idZone),FALSE);
    gtk_entry_set_visibility(GTK_ENTRY(fen->i_mdp2->idZone),FALSE);
    creer_entry(fen->i_nom);
    creer_entry(fen->i_nomutilisateur);
    creer_entry(fen->i_prenom);
   
    //creation des bouton
    fen->valider->bType = B_LABEL;
    fen->reset->bType = B_LABEL;
    fen->valider->bLabel = (char *)malloc(sizeof(char)*10);
    fen->reset->bLabel = (char *)malloc(sizeof(char)*10);
    strcpy(fen->valider->bLabel,"Valider");
    strcpy(fen->reset->bLabel,"Reset");
    creer_bouton(fen->valider);
    creer_bouton(fen->reset);
    
    //creation de cadre
    //strcpy(fen->cadre->cLabel,"Inscription");
    creer_cadre(fen->cadre);
    
    //creation de la table : mother
    fen->mother->homogene = 0;
    fen->mother->nbLignes = 4;
    fen->mother->nbColonnes = 4;
    creer_table(fen->mother);
    
    
    //manipulation
  
    
    Box b1,b2,bh1,bh2;
    
    b1.bHomogene = 0;
    b1.bSpacing = 30;
    b1.bTaille.h = 500;
    b1.bTaille.w = 600;
    b1.bType = VERTICAL;
    
    b2.bHomogene = 0;
    b2.bSpacing = 20;
    b2.bTaille.h = 500;
    b2.bTaille.w = 600;
    b2.bType = VERTICAL;
    
    creer_box(&b1);
    creer_box(&b2);
    
    ajouter_element_box(b1.idVBox,fen->nom->idLabel,DEBUT,0,0,0);
    ajouter_element_box(b1.idVBox,fen->i_nom->idZone,DEBUT,0,0,0);
    ajouter_element_box(b1.idVBox,fen->prenom->idLabel,DEBUT,0,0,0);
    ajouter_element_box(b1.idVBox,fen->i_prenom->idZone,DEBUT,0,0,0);
    ajouter_element_box(b1.idVBox,fen->adresse->idLabel,DEBUT,0,0,0);
    ajouter_element_box(b1.idVBox,fen->i_add1->idZone,DEBUT,0,0,0);
    ajouter_element_box(b1.idVBox,fen->i_add2->idZone,DEBUT,0,0,0);
    ajouter_element_box(b1.idVBox,fen->email->idLabel,DEBUT,0,0,0);
    ajouter_element_box(b1.idVBox,fen->i_email->idZone,DEBUT,0,0,0);
    
    ajouter_element_box(b2.idVBox,fen->nomutilisateur->idLabel,DEBUT,0,0,0);
    ajouter_element_box(b2.idVBox,fen->i_nomutilisateur->idZone,DEBUT,0,0,0);
    ajouter_element_box(b2.idVBox,fen->mdp1->idLabel,DEBUT,0,0,0);
    ajouter_element_box(b2.idVBox,fen->i_mdp1->idZone,DEBUT,0,0,0);
    ajouter_element_box(b2.idVBox,fen->mdp2->idLabel,DEBUT,0,0,0);
    ajouter_element_box(b2.idVBox,fen->i_mdp2->idZone,DEBUT,0,0,0);
    GtkWidget *remarque = gtk_label_new("Remarque :\n - Tout les champs qui precede par (*) sont obligatoires .");
    ajouter_element_box(b2.idVBox,remarque,DEBUT,0,0,0);
    bh1.bHomogene = 0;
    bh1.bSpacing = 100;
    bh1.bTaille.h = 0;
    bh1.bTaille.w = 0;
    bh1.bType = HORIZONTAL;
    
    bh2.bHomogene = 0;
    bh2.bSpacing = 10;
    bh2.bTaille.h = 20;
    bh2.bTaille.w = 10;
    bh2.bType = HORIZONTAL;
    creer_box(&bh1);
    creer_box(&bh2);
    
    
            ajouter_element_box(bh1.idVBox,b1.idVBox,DEBUT,0,0,10);
            ajouter_element_box(bh1.idVBox,b2.idVBox,DEBUT,0,0,10);
            
            ajouter_element_box(bh2.idVBox,fen->reset->idBouton,DEBUT,1,1,100);
            ajouter_element_box(bh2.idVBox,fen->valider->idBouton,DEBUT,1,1,100);
            
    GtkWidget *titre = gtk_label_new("\nInscription\n\n");
    ajouter_element_table(fen->mother,titre,1,1,2,1);
    ajouter_element_table(fen->mother,bh1.idVBox,2,2,2,2);
    ajouter_element_table(fen->mother,bh2.idVBox,4,1,2,1);
   
   
    
    
    
   
}//fin de la fonction




/*
 Cette fontion permer de vider tout les champs de texte situant dans le fentre inscription
 * ENTREES : Button, FenetreInscription sd
 * SORTIES : NONE
 
 
 */
void reset_FenetreInscription(GtkWidget *bt,FenetreInscription *fen)
{
    
    gtk_entry_set_text(GTK_ENTRY(fen->i_add1->idZone),"");
    gtk_entry_set_text(GTK_ENTRY(fen->i_add2->idZone),"");
    gtk_entry_set_text(GTK_ENTRY(fen->i_email->idZone),"");
    gtk_entry_set_text(GTK_ENTRY(fen->i_mdp1->idZone),"");
    gtk_entry_set_text(GTK_ENTRY(fen->i_mdp2->idZone),"");
    gtk_entry_set_text(GTK_ENTRY(fen->i_nom->idZone),"");
    gtk_entry_set_text(GTK_ENTRY(fen->i_prenom->idZone),"");
    gtk_entry_set_text(GTK_ENTRY(fen->i_nomutilisateur->idZone),"");
    
    
    
}






/*
 Cette fontion permer de valider tout les champs de texte situant dans le fentre inscription
 * ENTREES :  Button,FenetreInscription sd
 * SORTIES : NONE
 
 
 */
void valider_FenetreInscription(GtkWidget *bt,FenetreInscription *fen)
{
    char nom[20],prenom[20],adresse[100],email[30],username[20],mdp1[20],mdp2[20];
    
    strcpy(adresse,gtk_entry_get_text(GTK_ENTRY(fen->i_add1->idZone)));
    strcat(adresse," ");
    strcat(adresse,gtk_entry_get_text(GTK_ENTRY(fen->i_add2->idZone)));
    strcpy(nom,gtk_entry_get_text(GTK_ENTRY(fen->i_nom->idZone)));
    strcpy(prenom,gtk_entry_get_text(GTK_ENTRY(fen->i_prenom->idZone)));
    strcpy(email,gtk_entry_get_text(GTK_ENTRY(fen->i_email->idZone)));
    strcpy(username,gtk_entry_get_text(GTK_ENTRY(fen->i_nomutilisateur->idZone)));
    strcpy(mdp1,gtk_entry_get_text(GTK_ENTRY(fen->i_mdp1->idZone)));
    strcpy(mdp2,gtk_entry_get_text(GTK_ENTRY(fen->i_mdp2->idZone)));
    
    Dialog dial;
    GtkWidget *content;
    if(strcmp(mdp1,mdp2)==0)
    {
        gtk_main_quit();
    }
    else {
        
        dial.dLabel = (char *)malloc(sizeof(char)*20);
        strcpy(dial.dLabel,"Erreur ! les mots de passe ne sont pas les meme !");
        //boite_dialogue(&dial,gtk_widget_get_parent_window(bt));
        GtkDialogFlags flags = GTK_DIALOG_MODAL ;
        dial.idDialog =  gtk_dialog_new_with_buttons ("Erreur d'inscription",
                                      gtk_widget_get_parent(bt),
                                      flags,
                                      ("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      NULL);
         g_signal_connect_swapped (dial.idDialog,
                           "response",
                           G_CALLBACK (gtk_widget_destroy),
                           dial.idDialog);
         content = gtk_dialog_get_content_area (GTK_DIALOG (dial.idDialog));
         GtkWidget *label = gtk_label_new (" Les 2 mdp ne sont pas identiques");
          gtk_container_add (GTK_CONTAINER (content), label);
          gtk_widget_show_all(dial.idDialog);
    }
    
    
}