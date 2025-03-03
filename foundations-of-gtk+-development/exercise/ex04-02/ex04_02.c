#include <gtk/gtk.h>

typedef struct {
  GtkSpinButton *spin;
  GtkScale *scale;
  gboolean sync;
} PrivData;

static void spin_value_changed (GtkSpinButton*, PrivData*);
static void scale_change_value (GtkRange*, GtkScrollType*, gdouble, PrivData*);
static void toggled_cb (GtkToggleButton* self, PrivData*);

static void quit_cb (GtkWidget*, gpointer);
PrivData priv;

int main (int argc,
          char *argv[])
{
  GtkWidget *window, *spin, *hscale, *check_btn, *hbox, *vbox;
  PrivData priv;
  gdouble min = 1.0, max = 10.0, step = 1.0;

  if (argc > 1)
  {
    min = g_strtod (argv[1], NULL);
  }

  if (argc > 2)
  {
    max = strtod (argv[2], NULL);
  }

  if (argc > 3)
  {
    step = strtod (argv[3], NULL);
  }

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "ex04-02");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  spin = gtk_spin_button_new_with_range (min, max, step);
  hscale = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, min, max, step);
  check_btn = gtk_check_button_new_with_mnemonic ("_Sync");

  priv.scale = GTK_SCALE (hscale);
  priv.spin = GTK_SPIN_BUTTON (spin);
  priv.sync = FALSE;

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);

  gtk_box_pack_start (GTK_BOX (vbox), spin, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hscale, TRUE, TRUE, 0);

  gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (hbox), check_btn, FALSE, TRUE, 0);

  g_signal_connect (G_OBJECT (spin), "value-changed",
                    G_CALLBACK (spin_value_changed),
                    (gpointer) &priv);
  g_signal_connect (G_OBJECT (hscale), "change-value",
                    G_CALLBACK (scale_change_value),
                    (gpointer) &priv);
  g_signal_connect (G_OBJECT (check_btn), "toggled",
                    G_CALLBACK (toggled_cb),
                    (gpointer) &priv);
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (quit_cb), NULL);

  gtk_container_add (GTK_CONTAINER (window), hbox);
  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}

static void
spin_value_changed (GtkSpinButton *spin,
                    PrivData *priv)
{
  if (priv->sync)
  {
    gtk_range_set_value (GTK_RANGE (priv->scale), gtk_spin_button_get_value (spin));
  }
}

static void
scale_change_value (GtkRange *range,
                    GtkScrollType *scroll,
                    gdouble val,
                    PrivData *priv)
{
  if (priv->sync)
  {
    gtk_spin_button_set_value (priv->spin, val);
  }
}

static void
toggled_cb (GtkToggleButton *self, PrivData *priv)
{
  priv->sync = gtk_toggle_button_get_active (self);
  if (priv->sync)
  {
    gtk_range_set_value (GTK_RANGE (priv->scale), gtk_spin_button_get_value (priv->spin));
  }
}

static void
quit_cb (GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}