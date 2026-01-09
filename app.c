#include <gtk/gtk.h>

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *message;
  GtkEntryBuffer *buffer;
  
  window = gtk_application_window_new (app);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  gtk_window_set_child(GTK_WINDOW(window), box);
  GtkWidget *label = gtk_label_new("WIP: messages will appear here");
  gtk_label_set_xalign(GTK_LABEL(label), 0.0);
  gtk_box_append(GTK_BOX(box), label);
  gtk_window_set_title (GTK_WINDOW (window), "c_chat");
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 200);
  buffer = gtk_entry_buffer_new(NULL, -1);
  message = gtk_entry_new_with_buffer(buffer);
  gtk_widget_set_halign(message, GTK_ALIGN_RIGHT);
  gtk_widget_set_valign(message, GTK_ALIGN_BOTTOM);
  gtk_box_append(GTK_BOX(box), message);

  gtk_window_present (GTK_WINDOW (window));
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.idk.c_chat", G_APPLICATION_DEFAULT_FLAGS);
  g_set_prgname("c_chat");
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
