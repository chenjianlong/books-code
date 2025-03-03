#include <gtk/gtk.h>

static void previous_page (GtkButton*, GtkNotebook*);
static void next_page (GtkButton*, GtkNotebook*);
static void quit_cb (GtkWidget*, gpointer);

int main (int argc,
          char *argv[])
{
  GtkWidget *window, *vpane, *notebook, *hbox;
  GtkWidget *label[4], *child[4], *button[4];
  GtkWidget *button1, *button2;
  char* page_text[] = {
    "Page One",
    "Page Two",
    "Page Three",
    "Page Four"
  };

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Notebook");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request (window, 250, 200);

  vpane = gtk_paned_new (GTK_ORIENTATION_VERTICAL);

  notebook = gtk_notebook_new ();
  for (gint i = 0; i < 4; ++i)
  {
    label[i] = gtk_label_new (page_text[i]);
    child[i] = gtk_expander_new_with_mnemonic (page_text[i]);
    button[i] = gtk_button_new_with_mnemonic ("_NextPage");

    gtk_container_add (GTK_CONTAINER (child[i]), button[i]);
    gtk_expander_set_expanded (GTK_EXPANDER (child[i]), TRUE);

    g_signal_connect (G_OBJECT (button[i]), "clicked",
                      G_CALLBACK (next_page),
                      (gpointer) notebook);

    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), child[i], label[i]);
  }

  gtk_notebook_set_show_tabs (GTK_NOTEBOOK (notebook), FALSE);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
  button1 = gtk_button_new_with_mnemonic ("_Previous");
  button2 = gtk_button_new_with_mnemonic ("_Quit");

  g_signal_connect (G_OBJECT (button1), "clicked",
                    G_CALLBACK (previous_page),
                    (gpointer) notebook);
  g_signal_connect (G_OBJECT (button2), "clicked",
                    G_CALLBACK (quit_cb),
                    (gpointer) NULL);
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (quit_cb), NULL);

  gtk_box_pack_start (GTK_BOX (hbox), button1, TRUE, TRUE, 5);
  gtk_box_pack_start (GTK_BOX (hbox), button2, TRUE, TRUE, 5);

  gtk_paned_pack1 (GTK_PANED (vpane), notebook, TRUE, FALSE);
  gtk_paned_pack2 (GTK_PANED (vpane), hbox, FALSE, FALSE);
  gtk_container_add (GTK_CONTAINER (window), vpane);
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}

/* Switch to the next GtkNotebook page. */
static void
next_page (GtkButton *button,
           GtkNotebook *notebook)
{
  gint page = gtk_notebook_get_current_page (notebook);
  gtk_notebook_set_current_page (notebook, (page + 1) % 4);
}

static void
previous_page (GtkButton *button,
               GtkNotebook *notebook)
{
  gint page = gtk_notebook_get_current_page (notebook);
  gtk_notebook_set_current_page (notebook, page == 0 ? 3 : page - 1);
}

static void
quit_cb (GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}