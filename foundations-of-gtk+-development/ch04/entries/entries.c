#include <gtk/gtk.h>
int main (int argc,
          char *argv[])
{
  GtkWidget *window, *vbox, *hbox, *question, *label, *pass;
  g_autofree gchar *str = NULL;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Password?");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  str = g_strconcat ("What is the password for ", g_get_user_name(), "?", NULL);
  question = gtk_label_new (str);
  label = gtk_label_new ("Password:");

  /* Create a new GtkEntry widget and hide its content from view. */
  pass = gtk_entry_new ();
  gtk_entry_set_visibility (GTK_ENTRY (pass), FALSE);
  gtk_entry_set_invisible_char (GTK_ENTRY (pass), '*');

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), pass, TRUE, TRUE, 0);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start (GTK_BOX (vbox), question, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);

  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}