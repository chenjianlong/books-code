#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
    GtkWidget *window, *hpaned, *button1, *button2;
    
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Panes");
    
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 225, 150);
    
    hpaned = gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);
    button1 = gtk_button_new_with_label ("Resize");
    button2 = gtk_button_new_with_label ("Me!");
    
    g_signal_connect_swapped (G_OBJECT (button1), "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              (gpointer) window);
    g_signal_connect_swapped (G_OBJECT (button2), "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              (gpointer) window);
                              
    /* Pack both buttons as the two children of the GtkHPaned widget. */
    gtk_paned_pack1 (GTK_PANED (hpaned), button1, FALSE, TRUE);
    gtk_paned_pack2 (GTK_PANED (hpaned), button2, TRUE, TRUE);
    
    gtk_container_add (GTK_CONTAINER (window), hpaned);
    gtk_widget_show_all (window);

    gtk_main ();
    return 0;
}
