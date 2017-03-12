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
    Fenetre_win fen;
            fen.Fen = initialiser_fenetre();
              creer_fenetre(fen.Fen);
    
     
                        fen.Finsc = initialiser_FenetreInscription();
                        creation_FenetreInscription(fen.Finsc);
    
    
    
    gtk_fixed_put(GTK_FIXED(fen.Fen->fixed),GTK_WIDGET(fen.Finsc->mother->table),0,0);
    
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_widget_add_events(GTK_WIDGET(fen.Fen->idFenetre), GDK_CONFIGURE);

    ajouter_signal(G_OBJECT(fen.Fen->idFenetre),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    ajouter_signal(G_OBJECT(fen.Finsc->reset->idBouton),"clicked",G_CALLBACK(reset_FenetreInscription),&fen);
    ajouter_signal(G_OBJECT(fen.Finsc->valider->idBouton),"clicked",G_CALLBACK(valider_FenetreInscription),&fen);
    gtk_window_set_resizable(GTK_WINDOW(fen.Fen->idFenetre),FALSE);
    afficher_tout(fen.Fen->idFenetre);
    boucle_evenement();
    
    
    
    return (EXIT_SUCCESS);
}

