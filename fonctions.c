#include "Headers.h"

/**********************************
*** FONCTIONS DE NOTIFICATION	***
***********************************/
void print_info (GtkWidget* win, gchar* msg)
{
    GtkWidget *p_dialog = NULL;
    p_dialog = gtk_message_dialog_new (win, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, msg);
    gtk_dialog_run (GTK_DIALOG (p_dialog));
    gtk_widget_destroy (p_dialog);
}

void print_error (GtkWidget* win, gchar* msg)
{
    GtkWidget *p_dialog = NULL;
    p_dialog = gtk_message_dialog_new (win, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, msg);
    gtk_dialog_run (GTK_DIALOG (p_dialog));
    gtk_widget_destroy (p_dialog);
}

void print_warning (GtkWidget* win, gchar* msg)
{
    GtkWidget *p_dialog = NULL;
    p_dialog = gtk_message_dialog_new (win, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE, msg);
    gtk_dialog_run (GTK_DIALOG (p_dialog));
    gtk_widget_destroy (p_dialog);
}

//
Personne* saisir_liste(GtkWidget* wid, Personne* ma_liste)
{
    GtkWidget* win;
    GtkWidget* label;
    GtkWidget* vbox;
    GtkWidget* hbox1;
    GtkWidget* hbox2;
    GtkWidget* hbox3;
    GtkWidget* hbox4;
    GtkWidget* entry_prenom;
    GtkWidget* button;
    Inputs* datas_input;
    GError error;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Saisie de la liste");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 350);
    gtk_window_set_icon_from_file (GTK_WINDOW(win), "icon.ico", &error);
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_destroy, NULL);

    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
    hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
    hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
    hbox3 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
    hbox4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);


    /***********************/
    label = gtk_label_new("<span size='x-large' face='Verdana'> Entrer les valeurs une à une : \n\n</span>");
    gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
    gtk_label_set_justify (label, GTK_JUSTIFY_CENTER);
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox1, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox2, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox3, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox4, FALSE, FALSE, 20);

    label = gtk_label_new("Nom complet : \t");
    gtk_box_pack_start (GTK_BOX (hbox1), label, FALSE, FALSE, 0);
    entry_prenom = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (hbox1), entry_prenom, FALSE, FALSE, 0);
    datas_input = (Inputs*)malloc(sizeof(Inputs));
    datas_input->prenom = entry_prenom;
    datas_input->liste = ma_liste;
    button = gtk_button_new_with_label("Valider");
    gtk_box_pack_start (GTK_BOX (hbox4), button, TRUE, TRUE, 80);
    g_signal_connect (button, "clicked", submit_form, datas_input);

    /***********************/
    gtk_container_add(GTK_CONTAINER(win), vbox);
    gtk_widget_show_all(win);
}

void submit_form(GtkWidget* wid, Inputs* datas)
{
    char* temp_prenom;
    Personne* temp_personne;

    // récupérer les valeurs
    temp_prenom = (char*)malloc(sizeof(char)*NMAX);
    strcpy(temp_prenom, (char*)gtk_entry_get_text(GTK_ENTRY(datas->prenom)) );

    // vider les champs
    gtk_entry_set_text(datas->prenom, "");

    temp_personne = create_cell_personne(temp_prenom);
    datas->liste = ajouter_personne(datas->liste, temp_personne);
}

Personne* create_cell_personne(char* prenom)
{
    Personne* dump = (Personne*)malloc(sizeof(Personne));
    dump->prenom = prenom;
    dump->suiv = NULL;
    return dump;
}

Personne* ajouter_personne(Personne* liste, Personne* a_ajouter)
{
    if (liste == NULL)
        return a_ajouter;
    Personne* courant = liste;
    while (courant->suiv != NULL)
        courant = courant->suiv;
    courant->suiv = a_ajouter;
    return liste;
}

void afficher_liste_cons(Personne* liste)
{
    Personne* courant = liste;
    while (courant != NULL)
    {
        printf("Nom : %s\n", courant->prenom);
        printf("---\n");
        courant = courant->suiv;
    }
}

void afficher_liste(GtkWidget* wid,Personne* liste)
{
    GtkWidget* win;
    GtkWidget* label;
    GtkWidget* vbox;
    GError error;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Saisie de la liste");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 350);
    gtk_window_set_icon_from_file (GTK_WINDOW(win), "icon.ico", &error);
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_widget_destroy, NULL);

    if (liste->suiv == NULL)
    {
        print_error(win, "Liste vide");
    }
    else
    {

        vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
        /***********************/
        label = gtk_label_new("<span size='xx-large' weight='bold' face='Lucida handwriting' foreground='#3F51B5'> Liste des personnes : \n\n</span>");
        gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
        gtk_label_set_justify (label, GTK_JUSTIFY_CENTER);
        gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

        Personne* courant_pers = liste->suiv;
        char* str;
        while (courant_pers != NULL)
        {
            str = g_strdup_printf("Nom : \t %s", courant_pers->prenom);
            label = gtk_label_new(str);
            gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
            label = gtk_label_new("-----");
            gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
            courant_pers = courant_pers->suiv;
        }

        /***********************/
        gtk_container_add(GTK_CONTAINER(win), vbox);
        gtk_widget_show_all(win);
    }
}

void Insertion(pArbre A, gchar *sTexte,GtkTreeStore *pTreeStore,GdkPixbuf *pPixBufA,GtkTreeIter pIter)
{
    GdkPixbuf *pPixBufB;
    GtkTreeIter pIter2;
    //   TEST
    /* Creation du modele */
      pPixBufB = gdk_pixbuf_new_from_file("./icon_directory.png", NULL);
     // FIN TEST

     sprintf(sTexte,"%s",A->Element);
      /* Creation de la nouvelle ligne */

   gtk_tree_store_append(pTreeStore, &pIter2, &pIter);

   // Mise a jour des donnees
   gtk_tree_store_set(pTreeStore, &pIter2,
    BMP_COLUMN, pPixBufB,
    TEXT_COLUMN, sTexte,
    -1);
    if (A->sag != NULL) Insertion(A->sag,sTexte,pTreeStore,pPixBufB,pIter2);
    if (A->sad != NULL) Insertion(A->sad,sTexte,pTreeStore,pPixBufB,pIter2);
}

void afficher_sama_arbre(GtkWidget* wid, Personne* ma_liste)
{
    GtkWidget *pWindow;
    GtkWidget *pTreeView;
    GtkWidget *pScrollbar;
    GtkTreeStore *pTreeStore;
    GtkTreeViewColumn *pColumn;
    GtkCellRenderer *pCellRenderer;
    GdkPixbuf *pPixBufA;
    GdkPixbuf *pPixBufB;
    GtkTreeIter pIter;
    GtkTreeIter pIter2;
    gchar *sTexte;
    /* Creation de la fenetre principale */
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 500, 400);
    gtk_window_set_title(GTK_WINDOW(pWindow), "GtkTreeView et GtkTreeStore");
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    if (ma_liste->suiv == NULL)
    {
        print_error(pWindow,"L'arbre est vide");
    }
    else
    {
        pArbre A=NULL;
        A=saisieArbre(A,ma_liste->suiv);


        /* Creation du modele */
        pTreeStore = gtk_tree_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);

        /* Chargement des images */
        pPixBufA = gdk_pixbuf_new_from_file("./icon_computer.png", NULL);
        pPixBufB = gdk_pixbuf_new_from_file("./icon_directory.png", NULL);


        //Affichage de l'arbre
        sTexte = g_malloc(16);
        sprintf(sTexte,"%s",A->Element);

        /* Creation de la nouvelle ligne */

        gtk_tree_store_append(pTreeStore, &pIter, NULL);

        // Mise a jour des donnees
        gtk_tree_store_set(pTreeStore, &pIter,BMP_COLUMN, pPixBufA,TEXT_COLUMN, sTexte,-1);

        if (A->sag != NULL) Insertion (A->sag,sTexte,pTreeStore,pPixBufA,pIter);
        if (A->sad != NULL) Insertion (A->sad,sTexte,pTreeStore,pPixBufA,pIter);

        // libération de la mémoire
        g_free(sTexte);
        g_object_unref(pPixBufA);
        g_object_unref(pPixBufB);

        /* Creation de la vue */
        pTreeView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(pTreeStore));

        /* Creation de la premiere colonne */
        pCellRenderer = gtk_cell_renderer_pixbuf_new();
        pColumn = gtk_tree_view_column_new_with_attributes(" ",
            pCellRenderer,
            "pixbuf", BMP_COLUMN,
            NULL);

        /* Ajout de la colonne à la vue */
        gtk_tree_view_append_column(GTK_TREE_VIEW(pTreeView), pColumn);

        /* Creation de la deuxieme colonne */
        pCellRenderer = gtk_cell_renderer_text_new();
        pColumn = gtk_tree_view_column_new_with_attributes("Nom",
            pCellRenderer,
            "text", TEXT_COLUMN,
            NULL);

        /* Ajout de la colonne à la vue */
        gtk_tree_view_append_column(GTK_TREE_VIEW(pTreeView), pColumn);

        /* Ajout de la vue a la fenetre */
        pScrollbar = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar),
            GTK_POLICY_AUTOMATIC,
            GTK_POLICY_AUTOMATIC);
        gtk_container_add(GTK_CONTAINER(pScrollbar), pTreeView);
        gtk_container_add(GTK_CONTAINER(pWindow), pScrollbar);
        gtk_widget_show_all(pWindow);
    }
}

void afficher_arbre_largeur(GtkWidget* wid, Personne* ma_liste)
{

    GtkWidget *pWindow;
    GtkWidget* hbox;
    GtkWidget* label;
    char *sTexte;
    sTexte = (char*)malloc(sizeof(char)*NMAX);
    /* Creation de la fenetre principale */
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 500, 400);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Affichage de l'arbre en largeur");
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    if (ma_liste->suiv == NULL)
    {
        print_error(pWindow, "Arbre vide");
    }
    else
    {
        pArbre x = NULL;
        pArbre A;
        A = saisieArbre(x, ma_liste->suiv);
        FileArbre file;
        file.Tete = file.Queue = NULL;
        file.taille = 0;
        file = enfiler(file,A);
        hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_container_add(GTK_CONTAINER(pWindow), hbox);
        while(file.taille != 0)
        {
            x = tete(file);
            sprintf(sTexte, "%s",x->Element);
            label = gtk_label_new(sTexte);
            gtk_box_pack_start (GTK_BOX(hbox), label, TRUE, TRUE, 0);
            if(EstVide(x->sag) != 0)
            {
               file = enfiler(file,x->sag);
            }
            if(EstVide(x->sad) != 0)
            {
                file = enfiler(file,x->sad);
            }
            file = defiler(file);
        }
        gtk_widget_show_all(pWindow);
    }
}
