#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>

// global widgets
GtkWidget *image;
GtkWidget *button_flip;
bool button_state = false;

// generate random coin
static void on_button_flip_click()
{
  if (button_state == false)
  {
    button_state = true;
    bool coinflipped = rand() % (2);
    switch(coinflipped)
    {
      case 0:
        gtk_image_set_from_resource(image, "/org/coinflip/res/heads.png");
        break;
      case 1:
        gtk_image_set_from_resource(image, "/org/coinflip/res/tails.png");
        break;
    }
    gtk_button_set_label(button_flip, "Reset Coin");
  }
  else
  {
    button_state = false;
    gtk_image_clear(image);
    gtk_button_set_label(button_flip, "Flip Coin");
  }
}

// run application
static void on_activate(GtkApplication *app) 
{
  // create widgets
  GtkWidget *window = gtk_application_window_new(app);
  GtkWidget *box = gtk_box_new(0, 1);
  image = gtk_image_new();
  button_flip = gtk_button_new_with_label("Flip Coin");

  // run configuration functions
  gtk_image_set_pixel_size(image, 128);
  g_signal_connect_swapped(button_flip, "clicked", G_CALLBACK(on_button_flip_click), window);
  gtk_box_append(box, button_flip);
  gtk_box_append(box, image);
  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_window_present(GTK_WINDOW(window));
}

int main (int argc, char *argv[]) 
{
  // create new application
  GtkApplication *app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK(on_activate), NULL);
  return g_application_run (G_APPLICATION(app), argc, argv);
}
