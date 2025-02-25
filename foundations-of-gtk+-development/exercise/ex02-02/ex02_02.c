#include <gtk/gtk.h>

#define FIRST_NAME "Jack"
#define LAST_NAME "Ma"

static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);
static void key_press(GtkWindow*, GdkEvent*, gpointer);
static void title_change(GtkWindow*, GdkEvent*, gpointer);

int main (int argc, char *argv[])
{
    GtkWidget *window, *label;

    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_object_set(window, "title", FIRST_NAME, "border-width", 10,
        "width-request", 300, "height-request", 100, NULL);

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
        G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
        G_CALLBACK (delete_event), NULL);

    /* Create a new GtkLabel widget that is selectable. */
    label = gtk_label_new (LAST_NAME);
    g_object_set(label, "selectable", TRUE, NULL);
    
    /* Add the label as a child widget of the window. */
    gtk_container_add (GTK_CONTAINER (window), label);

    g_signal_connect (G_OBJECT (window), "key-press-event",
        G_CALLBACK (key_press), label);
    g_signal_connect (G_OBJECT (window), "notify::title",
        G_CALLBACK (title_change), NULL);
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

static void key_press(GtkWindow *window, GdkEvent *event, gpointer label)
{
    gchar *text;
    g_object_get (label, "label", &text, NULL);

    if (g_ascii_strcasecmp (text, FIRST_NAME) == 0)
    {
        g_object_set (window, "title", FIRST_NAME, NULL);
        g_object_set (label, "label", LAST_NAME, NULL);
    }
    else
    {
        g_object_set (window, "title", LAST_NAME, NULL);
        g_object_set (label, "label", FIRST_NAME, NULL);
    }
}

static void title_change(GtkWindow *window, GdkEvent *event, gpointer data)
{
    gchar *title;
    g_object_get (window, "title", &title, NULL);
    g_message("title_change, now is: %s", title);
}