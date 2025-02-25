#include <gtk/gtk.h>

static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);
static void key_press(GtkWindow*, GdkEvent*, gpointer);

int main (int argc, char *argv[])
{
    GtkWidget *window, *label;

    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Jack");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 300, 100);
    
    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
        G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
        G_CALLBACK (delete_event), NULL);

    /* Create a new GtkLabel widget that is selectable. */
    label = gtk_label_new ("Ma");
    gtk_label_set_selectable (GTK_LABEL (label), TRUE);
    
    /* Add the label as a child widget of the window. */
    gtk_container_add (GTK_CONTAINER (window), label);

    g_signal_connect (G_OBJECT (window), "key-press-event",
        G_CALLBACK (key_press), label);
    gtk_widget_show_all (window);
    
    gtk_main ();
    return 0;
}

/* Stop the GTK+ main loop function when the window is destroyed. */
static void destroy (GtkWidget *window, gpointer data)
{
    gtk_main_quit ();
}

/* Return FALSE to destroy the widget. By returning TRUE, you can cancel
 * a delete-event. This can be used to confirm quitting the application. */
static gboolean delete_event (GtkWidget *window,
                              GdkEvent *event, gpointer data)
{
    return FALSE;
}

static void key_press(GtkWindow *window, GdkEvent *event, gpointer data)
{
    GtkLabel *label = (GtkLabel*)data;
    g_autofree gchar *title = g_strdup(gtk_window_get_title(window));
    g_autofree gchar *label_text = g_strdup(gtk_label_get_label(label));

    gtk_window_set_title(window, label_text);
    gtk_label_set_label(label, title);
}