#include <gtk/gtk.h>

int main (int argc,
          char *argv[])
{
  GtkWidget *window, *scale_int, *scale_float, *vbox;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Scales");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request (window, 250, -1);

  /* Create a scale that scrolls integers and one that scrolls floating point. */
  scale_int = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0.0, 10.0, 1.0);
  scale_float = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0.0, 1.0, 0.1);

  /* Set the number of decimal places to display for each widget. */
  gtk_scale_set_digits (GTK_SCALE (scale_int), 0);
  gtk_scale_set_digits (GTK_SCALE (scale_float), 1);

  /* Set the position of the value with respect to the widget. */
  gtk_scale_set_value_pos (GTK_SCALE (scale_int), GTK_POS_RIGHT);
  gtk_scale_set_value_pos (GTK_SCALE (scale_float), GTK_POS_LEFT);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start (GTK_BOX (vbox), scale_int, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), scale_float, TRUE, TRUE, 0);

  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}