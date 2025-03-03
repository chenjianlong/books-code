#include <gtk/gtk.h>

int main (int argc,
          char *argv[])
{
  GtkWidget *window, *vbox, *radio1, *radio2, *radio3, *radio4;
 
  gtk_init (&argc, &argv);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Radio Buttons");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* Create three radio buttons where the second two join radio1's group. */
  radio1 = gtk_radio_button_new_with_label (NULL, "I want to be clicked!");
  radio2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1),
                                                        "Click me instead!");
  radio3 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1),
                                                       "No! Click me!");

  /* Note: The radio button you create the new widget from does not matter as
   * long as it is already a member of the group! */
  radio4 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio3),
                                                        "No! Click me instead!");

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start (GTK_BOX (vbox), radio1, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), radio2, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), radio3, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), radio4, TRUE, TRUE, 0);

  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}