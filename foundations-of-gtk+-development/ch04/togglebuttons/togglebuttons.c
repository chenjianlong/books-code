#include <gtk/gtk.h>

static void button_toggled (GtkToggleButton*, GtkWidget*);

int main (int argc,
          char *argv[])
{
  GtkWidget *window, *vbox, *toggle1, *toggle2;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Toggle Buttons");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_set_homogeneous (GTK_BOX (vbox), TRUE);
  toggle1 = gtk_toggle_button_new_with_mnemonic ("_Deactivate the other one!");
  toggle2 = gtk_toggle_button_new_with_mnemonic ("_No! Deactivate that one!");

  g_signal_connect (G_OBJECT (toggle1), "toggled",
                    G_CALLBACK (button_toggled),
                    (gpointer) toggle2);
  g_signal_connect (G_OBJECT (toggle2), "toggled",
                    G_CALLBACK (button_toggled),
                    (gpointer) toggle1);

  gtk_box_pack_start (GTK_BOX (vbox), toggle1, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), toggle2, TRUE, TRUE, 0);

  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}

/* If the toggle button was activated, set the other as disabled. Otherwise,
 * enable the other toggle button. */
static void
button_toggled (GtkToggleButton *toggle,
                GtkWidget *other_toggle)
{
  if (gtk_toggle_button_get_active (toggle))
    gtk_widget_set_sensitive (other_toggle, FALSE);
  else
    gtk_widget_set_sensitive (other_toggle, TRUE);
}