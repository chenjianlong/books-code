#include <gtk/gtk.h>

static void load_css(void);

int main (int argc,
          char *argv[])
{
  GtkWidget *window, *vbox, *label, *button, *checkButton, *toggleButton;
 
  gtk_init (&argc, &argv);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "CSS Style");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  //gtk_rc_parse (".gtkrc");
  load_css();

  label = gtk_label_new ("GtkLabel");
  button = gtk_button_new_with_label ("GtkButton");
  checkButton = gtk_check_button_new_with_label ("GtkCheckButton");
  toggleButton = gtk_toggle_button_new_with_label ("GtkToggleButton");

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), checkButton, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), toggleButton, TRUE, TRUE, 0);

  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}

void load_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkScreen *screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_css_provider_load_from_path(provider, "style.css", NULL);
    g_object_unref(provider);
}