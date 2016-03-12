#include "Headers.h"

int main (int argc, char *argv[])
{
  GtkWidget* MainWindow = NULL;
  GtkWidget* vbox = NULL;
  GtkWidget* hbox1 = NULL;
  GtkWidget* hbox2 = NULL;
  GtkWidget* hbox3 = NULL;
  GtkWidget* button = NULL;
  GtkWidget* label = NULL;
  GError error;

  // Initialise GTK+
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  // Crée la fenêtre principale
  MainWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (MainWindow), 8);
  gtk_window_set_title (GTK_WINDOW (MainWindow), "Projet Algo 4 14/15");
  gtk_window_set_default_size(GTK_WINDOW(MainWindow), 800, 400);
  gtk_window_set_icon_from_file (GTK_WINDOW(MainWindow), "icon.ico", &error);
  gtk_window_set_position (GTK_WINDOW (MainWindow), GTK_WIN_POS_CENTER);
  gtk_widget_realize (MainWindow);
  g_signal_connect (MainWindow, "destroy", gtk_main_quit, NULL);

  /*
    création et positionnement des éléments de façon à avoir une fenêtre découpée en trois :
    - l'entête (hbox1)
    - le corps (hbox2)
    - le pied ou la queue (hbox3)
    Tous les trois contenus dans la vbox qui est dans la fenêtre
  */
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 20);
  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  hbox2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
  hbox3 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);

  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_set_border_width (GTK_CONTAINER (hbox1), 5);
  gtk_container_set_border_width (GTK_CONTAINER (hbox2), 5);
  gtk_container_set_border_width (GTK_CONTAINER (hbox3), 5);
  gtk_container_add (GTK_CONTAINER (MainWindow), vbox);

  gtk_box_pack_start (GTK_BOX (vbox), hbox1, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox2, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox3, FALSE, FALSE, 0);

  /********************************/
  /***        EN TÊTE           ***/
  /********************************/
  label = gtk_label_new("<span size='x-large' face='comic sans ms'><b><u>Projet réalisé par</u> : </b> <i>Babacar Cissé Dia, Samsidine Aïdara, Ousmane Bâ</i></span>");
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
  gtk_label_set_justify (label, GTK_JUSTIFY_CENTER);
  gtk_box_pack_start (GTK_BOX (hbox1), label, TRUE, TRUE, 0);

  /********************************/
  /***        CORPS             ***/
  /********************************/
  Personne* ma_liste = create_cell_personne("1er");
  button = gtk_button_new_with_label("Ajouter à la liste");
  g_signal_connect (button, "clicked", saisir_liste, ma_liste);
  gtk_box_pack_start (GTK_BOX (hbox3), button, TRUE, TRUE, 10);

  button = gtk_button_new_with_label("Afficher liste");
  g_signal_connect (button, "clicked", afficher_liste, ma_liste);
  gtk_box_pack_start (GTK_BOX (hbox3), button, TRUE, TRUE, 10);

  button = gtk_button_new_with_label("Afficher arbre en largeur");
  g_signal_connect (button, "clicked", afficher_arbre_largeur, ma_liste);
  gtk_box_pack_start (GTK_BOX (hbox3), button, TRUE, TRUE, 10);

  button = gtk_button_new_with_label("Afficher arbre");
  g_signal_connect (button, "clicked", afficher_sama_arbre, ma_liste);
  gtk_box_pack_start (GTK_BOX (hbox3), button, TRUE, TRUE, 10);



  /********************************/
  /***        PIED              ***/
  /********************************/

  // Boucle événementielle
  gtk_widget_show_all (MainWindow);
  gtk_main ();
  return 0;
}
