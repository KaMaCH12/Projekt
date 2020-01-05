#include <stdlib.h>
#include <gtk/gtk.h>

#define win_height 800
#define win_width 800

void win_init()
{
    GtkWidget *window,*grid;
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    grid=gtk_grid_new();
    
    for(int i=0;i<win_height;i++)
    {
	gtk_grid_insert_row(grid,i);
	gtk_grid_insert_column(grid,i);
    }

    gtk_window_set_default_size(GTK_WINDOW(window),win_height,win_width);    
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_container_add (GTK_CONTAINER(window),grid);
    
    g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_widget_show(window);
    gtk_widget_show(grid);
}

int main(int argc,char *argv[])
{
    gtk_init(&argc,&argv);
    win_init();
    gtk_main();
}
