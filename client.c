#include <gtk/gtk.h>
#include "networkstructure.h"

void clientLogic(int server_socket){
  send(server_socket, buf, strlen(buf), 0);
  int n = recv(server_socket, buf, 1024, 0);
  if (n==0) {
    close(server_socket);
    printf("Client closed\n");
    exit(0);
  }
  buf[n] = '\0';
}



static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  char buf[1024];
  printf("Enter a username: \n");
  if (fgets(buf, 1024, stdin) == NULL) {
    close(server_socket);
    printf("Client closed\n");
    exit(0);
  }
  send(server_socket, buf, strlen(buf), 0);
  clientLogic(server_socket);
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *message;
  GtkEntryBuffer *buffer;
  window = gtk_application_window_new (app);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  gtk_window_set_child(GTK_WINDOW(window), box);
  GtkWidget *label = gtk_label_new("Messages will appear here");
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
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  while(1) {
    clientLogic(server_socket);
  }
  
  
  app = gtk_application_new ("org.idk.c_chat", G_APPLICATION_DEFAULT_FLAGS);
  g_set_prgname("c_chat");
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
