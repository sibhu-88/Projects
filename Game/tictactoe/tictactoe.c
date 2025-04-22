//sudo apt update
//sudo apt install libgtk-3-dev


#include <gtk/gtk.h>

static int flag = 0,score1=0,score2=0;
char game_state[9] = {'\0'};
GtkWidget *buttons[9];

gboolean check_win(char symbol) {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // Rows
        {0,3,6}, {1,4,7}, {2,5,8}, // Columns
        {0,4,8}, {2,4,6}           // Diagonals
    };

    for (int i = 0; i < 8; ++i) {
        if (game_state[wins[i][0]] == symbol &&
            game_state[wins[i][1]] == symbol &&
            game_state[wins[i][2]] == symbol) {
            return TRUE;
        }
    }
    return FALSE;
}

void on_reset_clicked(GtkButton *button, gpointer user_data)
{
    for (int i = 0; i < 9; ++i)
    {
        gtk_button_set_label(GTK_BUTTON(buttons[i]), "");
        GtkStyleContext *context = gtk_widget_get_style_context(buttons[i]);

        gtk_style_context_remove_class(context, "Blue-button");
        gtk_style_context_remove_class(context, "Red-button");
        gtk_style_context_add_class(context, "default-button");

        game_state[i] = '\0';
    }
    flag = 0;
    score1=0;
    score2=0;
}

void apply_css(const gchar *css_data)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css_data, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

static void on_button_clicked(GtkButton *button, gpointer user_data)
{
   // GtkWidget **widgets = (GtkWidget **)user_data;
    const char *label = gtk_button_get_label(button);
    if (label && *label != '\0')
        return;

    GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(button));
    int index = *((int *)user_data);
    gtk_style_context_remove_class(context, "default-button");
    if (flag == 0)
    {
        gtk_button_set_label(button, "X");
        gtk_style_context_add_class(context, "Blue-button");
        flag = 1;
        game_state[index] = 'X';
    }else if (flag == 1)
    {
        gtk_button_set_label(button, "O");
        gtk_style_context_add_class(context, "Red-button");
        flag = 0;
        game_state[index] = 'O';
    }

    if (check_win(game_state[index])) {
        GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent_window), 
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Player %c wins!", game_state[index]);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        for (int i = 0; i < 9; ++i)
        {
            gtk_button_set_label(GTK_BUTTON(buttons[i]), "");
            GtkStyleContext *context = gtk_widget_get_style_context(buttons[i]);

            gtk_style_context_remove_class(context, "Blue-button");
            gtk_style_context_remove_class(context, "Red-button");
            gtk_style_context_add_class(context, "default-button");

            game_state[i] = '\0';
        }
        flag = 0;
    }
}

static void on_activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Tic-Tac-Toe");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 600);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *Rst_button = gtk_button_new_with_label("Reset");
    gtk_widget_set_size_request(Rst_button, 80, 30);
    gtk_widget_set_halign(Rst_button, GTK_ALIGN_END);
    gtk_widget_set_margin_end(Rst_button, 50); 
    gtk_box_pack_start(GTK_BOX(vbox), Rst_button, FALSE, FALSE, 20);
    g_signal_connect(Rst_button, "clicked", G_CALLBACK(on_reset_clicked), NULL);

    const gchar *css =
        ".default-button { background-color: #8bc34a; border-radius: 10px; font-weight: bold; color: white; font-size: 16px; }"
        ".Blue-button { background:rgb(102, 148, 247); color: white; font-size: 16px; }"
        ".Red-button { background:rgb(252, 81, 81); color: white; font-size: 16px; }"
        ".score-label1 { font-size: 30px; color: rgb(102, 148, 247); font-weight: bold; }"
        ".score-label2 { font-size: 30px; color: rgb(252, 81, 81); font-weight: bold; }";

    apply_css(css);

    GtkWidget *score_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(score_box, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(score_box, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), score_box, FALSE, FALSE, 0);


    GtkWidget *player1 = gtk_label_new("Player X ");
    GtkWidget *player2 = gtk_label_new("Player O ");


    GtkStyleContext *context1 = gtk_widget_get_style_context(player1);
    gtk_style_context_add_class(context1, "score-label1");
    GtkStyleContext *context2 = gtk_widget_get_style_context(player2);
    gtk_style_context_add_class(context2, "score-label2");

    GtkWidget *player1_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(player1_box), player1, FALSE, FALSE, 0);
    gtk_widget_set_margin_start(player1_box, 30);

    GtkWidget *player2_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(player2_box), player2, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(score_box), player1_box, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(score_box), player2_box, FALSE, FALSE, 0);
    gtk_widget_set_margin_end(player2_box, 30);
    
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(grid, 350, 350);
    //gtk_widget_set_margin_top(grid, -100);

    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    for (int i = 0; i < 9; ++i)
    {
        GtkWidget *button = gtk_button_new();

        gtk_widget_set_size_request(button, 80, 80);
        gtk_widget_set_hexpand(button, TRUE);
        gtk_widget_set_vexpand(button, TRUE);
        gtk_widget_set_margin_top(button, 0);
        gtk_widget_set_margin_start(button, 0);

        GtkStyleContext *context = gtk_widget_get_style_context(button);
        gtk_style_context_add_class(context, "default-button");
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        buttons[i] = button;

        int *index = g_new(int, 1);
        *index = i;
        g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), index);
    }
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("com.example.tictactoe", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
