  #include <gtk/gtk.h>
  #include <glib-unix.h>
  #include "networkstructure.h"

  static int server_socket = -1;
  static GtkTextBuffer *chat_buffer = NULL;


  static gboolean on_server_readable(gint fd, GIOCondition cond, gpointer data) {
    if (cond & (G_IO_HUP | G_IO_ERR)) return FALSE;

    char buf[1024];
    int n;

    while ((n = recv(fd, buf, sizeof(buf)-1, MSG_DONTWAIT)) > 0) {
      buf[n] = '\0';

      GtkTextIter end;
      gtk_text_buffer_get_end_iter(chat_buffer, &end);
      gtk_text_buffer_insert(chat_buffer, &end, buf, -1);
      gtk_text_buffer_insert(chat_buffer, &end, "\n", -1);
    }

    return 1;
  }



  static void clientLogic(GtkEntry *entry, gpointer user_data){
    user_data = NULL;
    const char *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    if (!text || !*text) {
      return;
    }
    send(server_socket, text, strlen(text), 0);
    send(server_socket, "\n", 1, 0);
    gtk_editable_set_text(GTK_EDITABLE(entry), "");
  }

  static void connectServer(char* IP){
    server_socket = client_tcp_handshake(IP);
    fcntl(server_socket, F_SETFL, O_NONBLOCK);
    GIOChannel *ch = g_io_channel_unix_new(server_socket);
    g_unix_fd_add(server_socket, G_IO_IN | G_IO_HUP | G_IO_ERR, on_server_readable, NULL);
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
    GtkWidget *view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view), FALSE);
    chat_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_box_append(GTK_BOX(box), view);
    char* IP = "127.0.0.1";
    connectServer(IP);
    gtk_window_set_title (GTK_WINDOW (window), "c_chat");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 600);
    buffer = gtk_entry_buffer_new(NULL, -1);
    message = gtk_entry_new_with_buffer(buffer);
    gtk_entry_set_placeholder_text(GTK_ENTRY(message), "Type a message...");
    gtk_widget_set_halign(message, GTK_ALIGN_END);
    gtk_widget_set_valign(message, GTK_ALIGN_END);
    gtk_box_append(GTK_BOX(box), message);
    g_signal_connect (message, "activate", G_CALLBACK (clientLogic), NULL);
    gtk_window_present (GTK_WINDOW (window));
  }

  int
  main (int    argc,
        char **argv)
  {
    GtkApplication *app;
    int status;
    app = gtk_application_new ("org.idk.c_chat", G_APPLICATION_NON_UNIQUE);
    g_set_prgname("c_chat");
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
  }
