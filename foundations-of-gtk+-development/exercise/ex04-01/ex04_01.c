#include <stdio.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>

typedef struct {
  GtkEntry *entry;
  GtkButton *button;
  GtkFileChooser *chooser;
  GtkLabel *label;
} RenameWidget;

static void file_changed (GtkFileChooser*, RenameWidget*);
static void button_click (GtkButton*, RenameWidget*);
static void quit_cb (GtkWidget*, gpointer);

int main (int argc,
          char *argv[])
{
  GtkWidget *window, *chooser, *entry, *button, *hbox, *label, *vbox;
  GtkFileFilter *filter1;
  RenameWidget rename;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "ex04-01");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  entry = gtk_entry_new ();
  gtk_widget_set_sensitive (entry, FALSE);

  button = gtk_button_new_with_mnemonic ("_Rename");
  gtk_widget_set_sensitive (button, FALSE);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

  /* Create two buttons, one to select a folder and one to select a file. */
  chooser = gtk_file_chooser_button_new ("Chooser a Folder",
                                          GTK_FILE_CHOOSER_ACTION_OPEN);

  label = gtk_label_new ("");

  rename.entry = GTK_ENTRY (entry);
  rename.button = GTK_BUTTON (button);
  rename.chooser = GTK_FILE_CHOOSER (chooser);
  rename.label = GTK_LABEL (label);

  g_signal_connect (G_OBJECT (chooser), "selection_changed",
                    G_CALLBACK (file_changed),
                    (gpointer) &rename);

  g_signal_connect (G_OBJECT (button), "clicked",
                    G_CALLBACK (button_click),
                    (gpointer) &rename);

  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (quit_cb), NULL);

  /* Set file chooser buttons to the location of the user's home directory. */
  gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (chooser),
                                       g_get_home_dir());

  filter1 = gtk_file_filter_new ();
  gtk_file_filter_set_name (filter1, "All Files");
  gtk_file_filter_add_pattern (filter1, "*");

  gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (chooser), filter1);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start (GTK_BOX (vbox), chooser, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, TRUE, 0);

  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}

/* When a file is selected, display the full path in the GtkLabel widget. */
static void
file_changed (GtkFileChooser *chooser,
              RenameWidget *rename)
{
  g_autofree gchar *path = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
  g_autofree gchar *file = g_path_get_basename (path);

  gtk_entry_set_text (rename->entry, file);
  gtk_widget_set_sensitive (GTK_WIDGET (rename->entry), TRUE);
  gtk_widget_set_sensitive (GTK_WIDGET (rename->button), TRUE);
}

static void
button_click (GtkButton *button,
              RenameWidget *widget)
{
  g_autofree gchar *path = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (widget->chooser));
  g_autofree gchar *dir = g_path_get_dirname (path);
  g_autofree gchar *file = g_path_get_basename (path);
  const gchar *dst_file = gtk_entry_get_text (widget->entry);
  g_autofree gchar *dst = g_build_path ("/", dir, dst_file, NULL);
  g_autoptr (GString) label_text = g_string_new("");

  if (g_rename (path, dst) == 0)
  {
    g_string_printf (label_text,
                     "Rename %s->%s successful",
                     file,
                     dst_file);
  }
  else
  {
    g_string_printf (label_text,
                     "Rename %s->%s failure, err=%d, %s",
                     file,
                     dst_file,
                     errno,
                     g_strerror (errno));
  }

  gtk_widget_set_sensitive (GTK_WIDGET (widget->entry), FALSE);
  gtk_widget_set_sensitive (GTK_WIDGET (button), FALSE);
  gtk_label_set_label (widget->label, label_text->str);
}

static void
quit_cb (GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}