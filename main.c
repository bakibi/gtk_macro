/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: elk
 *
 * Created on 6 mars 2017, 09:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "macro.h"
#include "application.h"

int main(int argc, char** argv) {

    initialiser(argc,argv);
    Fenetre *fen;
            fen = initialiser_fenetre();
              creer_fenetre(fen);
    
     FenetreInscription *feni;
                        feni = initialiser_FenetreInscription();
                        creation_FenetreInscription(feni);
    
    
    
    gtk_fixed_put(GTK_FIXED(fen->fixed),GTK_WIDGET(feni->mother->table),0,0);
    
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_widget_add_events(GTK_WIDGET(fen->idFenetre), GDK_CONFIGURE);

    ajouter_signal(G_OBJECT(fen->idFenetre),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    ajouter_signal(G_OBJECT(feni->reset->idBouton),"clicked",G_CALLBACK(reset_FenetreInscription),feni);
    ajouter_signal(G_OBJECT(feni->valider->idBouton),"clicked",G_CALLBACK(valider_FenetreInscription),feni);
    gtk_window_set_resizable(GTK_WINDOW(fen->idFenetre),FALSE);
    afficher_tout(fen->idFenetre);
    boucle_evenement();
    
    
    
    return (EXIT_SUCCESS);
}

