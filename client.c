#include <gtk/gtk.h>
#include "networkstructure.h"

static int server_socket = -1;
static GtkWidget *chat_label = NULL;

static void clientLogic(GtkEntry *entry, int server_socket){
  char *text = gtk_editable_get_text(GTK_EDITABLE(entry));
  send(server_socket, text, strlen(text), 0);
  char buf[1024];
  int n = recv(server_socket, buf, 1024, 0);
  if (n==0) {
    close(server_socket);
    printf("Client closed\n");
    exit(0);
  }
  buf[n] = '\0';

  char *old = gtk_entry_get_text(GTK_LABEL(chat_label));

  char *new = g_strconcat(old, "\n");
  new = g_strconcat(new, "\n");
  gtk_label_set_text(GTK_LABEL(chat_label), new);
  g_free(new);
  gtk_editable_set_text(GTK_EDITABLE(entry), "");
}

static void connectServer(char* IP){
  int server_socket = client_tcp_handshake(IP);
}

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
  GtkWidget *label = gtk_label_new("Messages will appear here");
  chat_label = label;
  gtk_label_set_xalign(GTK_LABEL(label), 0.0);
  gtk_box_append(GTK_BOX(box), label);
  gtk_window_set_title (GTK_WINDOW (window), "c_chat");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 600);
  buffer = gtk_entry_buffer_new(NULL, -1);
  message = gtk_entry_new_with_buffer(buffer);
  gtk_entry_set_placeholder_text(GTK_ENTRY(message), "Type a message...");
  gtk_widget_set_halign(message, GTK_DIR_RIGHT);
  gtk_widget_set_valign(message, GTK_POS_BOTTOM);
  gtk_box_append(GTK_BOX(box), message);
  g_signal_connect (message, "activate", G_CALLBACK (clientLogic), buffer);  
  gtk_window_present (GTK_WINDOW (window));
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;
  
  char* IP = "127.0.0.1";
  connectServer(IP);  
  app = gtk_application_new ("org.idk.c_chat", G_APPLICATION_DEFAULT_FLAGS);
  g_set_prgname("c_chat");
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
