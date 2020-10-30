/***********************************************************
*
*A simple GTK example
*simple.c: show a 2x2 board and move the king by clicking
*author: Weiwei Chen(Bianca Doronila, Michael Barbosa)
*initial version: 01/22/13 EECS22L Winter 2013
*
* Modifications:
* 	01/30/2018 MB: added more labels for row/cols of board
* 	02/01/2018 MB: added output textArea to view moveLog
*
***********************************************************/

#include "gui.h"
#include "string.h"
#include <gtk/gtk.h>

/*Global Variables */

/* WINDOWS */
GtkWidget *Menu 	;
GtkWidget *PlayGame	;
/* PICTURES */
GtkWidget *chess_icon 	,
	  *title_icon	; 
/* TABLES */
GtkWidget *table	,	 	
	  *gametable	;
/* TEXT ENTRIES */
GtkWidget *enter_move	,
	  *desired_move ,
	  *prev_move	,
	  *scrolltext	,
	  *viewport	,
	  *move_entry	;
GtkAdjustment	  *horizontal	,
	  	  *vertical	;
/* BUTTONS */
GtkWidget *AIvAIbutton, *PvAIbutton,  *PvPbutton,
	  *EASYbutton,  *NORMbutton,  *HARDbutton, 
       	  *BLACKbutton, *WHITEbutton;
/* CHESS LABELS */
GtkWidget *A ,*B ,*C ,*D ,*E ,*F ,*G ,*H,
	  *r1,*r2,*r3,*r4,*r5,*r6,*r7,*r8;
/* MAIN BUTTON + TITLE LABELS */
GtkWidget *PLAYbutton,
	  *QUITbutton,
	  *WELCOMElabel,
	  *PLAYlabel,
	  *QUITlabel,
	  *TIMElabel;

PangoFontDescription *df;

GtkWidget *textArea;
GtkWidget *scrolledwindow;
GtkWidget *textEntry;

/* timer properties */
static gboolean continue_timer = FALSE;
static gboolean start_timer = FALSE;
static int sec_expired = 0;

enum GRID Board[8][8];
int x = 0;
int y = 0;
int hr, min, sec;

/* reset the chess */
void InitBoard()
{
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
    			if ((x+y)%2 == 0)
			{ 
				Board[x][y] = WHITE; 
			}
    			else
			{ 
				Board[x][y] = BLACK; 
			}
		}
	}	
	for(y = 6; y < 8; y++)
	{
	for(x = 0; x < 8; x++)
	{	
		if(y == 6)
		{
		    Board[x][y] = W_PAWN;
                }
		else if(x == 0 && y == 7){
		    Board[x][y] = W_ROOK;
		    //chess_board.board[x][y] = NewPiece('R', 1, rook, x, y);
		}
		else if(x == 1 && y == 7){
		    Board[x][y] = W_BISHOP;		
		    //chess_board.board[x][y] = NewPiece('H', 1, bishop, x, y);
		}
		else if(x == 2 && y == 7){
		    Board[x][y] = W_KNIGHT;
		    //chess_board.board[x][y] = NewPiece('B', 1, knight, x, y);
		}
		else if(x == 3 && y == 7){
		    Board[x][y] = W_KING;
		    //chess_board.board[x][y] = NewPiece('Q', 1, king, x, y);
		}	
		else if(x == 4 && y == 7){
		    Board[x][y] = W_QUEEN;	
	   	    //chess_board.board[x][y] = NewPiece('K', 1, queen, x, y);		
		}
		else if(x == 5 && y == 7){
		    Board[x][y] = W_KNIGHT;
		    //chess_board.board[x][y] = NewPiece('B', 1, knight, x, y);
		}
		else if(x == 6 && y == 7){
		    Board[x][y] = W_BISHOP; 
		    //chess_board.board[x][y] = NewPiece('H', 1, bishop, x, y);
		}
		else if(x == 7 && y == 7){
		    Board[x][y] = W_ROOK;
		    //chess_board.board[x][y] = NewPiece('R', 1, rook, x, y);	
		}
	} 
	}
	for(y = 0; y < 2; y++)
	{
	for(x = 0; x < 8; x++)
	{	
		if(y == 1)
		{
		    Board[x][y] = B_PAWN;
                }
		else if(x == 0 && y == 0){
		    Board[x][y] = B_ROOK;
		    //chess_board.board[x][y] = NewPiece('R', 1, rook, x, y);
		}
		else if(x == 1 && y == 0){
		    Board[x][y] = B_BISHOP;		
		    //chess_board.board[x][y] = NewPiece('H', 1, bishop, x, y);
		}
		else if(x == 2 && y == 0){
		    Board[x][y] = B_KNIGHT;
		    //chess_board.board[x][y] = NewPiece('B', 1, knight, x, y);
		}
		else if(x == 3 && y == 0){
		    Board[x][y] = B_KING;
		    //chess_board.board[x][y] = NewPiece('Q', 1, king, x, y);
		}	
		else if(x == 4 && y == 0){
		    Board[x][y] = B_QUEEN;	
	   	    //chess_board.board[x][y] = NewPiece('K', 1, queen, x, y);		
		}
		else if(x == 5 && y == 0){
		    Board[x][y] = B_KNIGHT;
		    //chess_board.board[x][y] = NewPiece('B', 1, knight, x, y);
		}
		else if(x == 6 && y == 0){
		    Board[x][y] = B_BISHOP; 
		    //chess_board.board[x][y] = NewPiece('H', 1, bishop, x, y);
		}
		else if(x == 7 && y == 0){
		    Board[x][y] = B_ROOK;
		    //chess_board.board[x][y] = NewPiece('R', 1, rook, x, y);	
		}
	}
	}
}

void ResetBoard()
{
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			if ((x+y)%2 == 0)
			{ 
				Board[x][y] = WHITE; 
			}
    			else
			{ 
				Board[x][y] = BLACK; 
			}
		}
	}
}

void ReverseGridColor(int g_x, int g_y)
{
	if(Board[g_x][g_y] == BLACK)
	{
		Board[g_x][g_y] = WHITE;
	}
	else
	{
		Board[g_x][g_y] = BLACK;
	}
}


void MoveThePiece()
{
/* Initial Chess Piece Location */

/* Move to Desired Location */
}


void DrawBoard()
{
	int i, j;

	for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			switch(Board[i][j])
			{
				case BLACK:
					chess_icon = gtk_image_new_from_file("./chess_icon/Bsquare.jpg");
					break;
				case WHITE:
					chess_icon = gtk_image_new_from_file("./chess_icon/Wsquare.jpg") ;
					break;
				case B_ROOK:
					chess_icon = gtk_image_new_from_file("./chess_icon/Rblack.png");
					break;
				case W_ROOK:
					chess_icon = gtk_image_new_from_file("./chess_icon/Rwhite.png");
					break;
				case B_KNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icon/Nblack.png");
					break;
				case W_KNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icon/Nwhite.png");
					break;
				case B_BISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icon/Bblack.png");
					break;
				case W_BISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icon/Bwhite.png");
					break;
				case B_QUEEN:
					chess_icon = gtk_image_new_from_file("./chess_icon/Qblack.png");
					break;
				case W_QUEEN:
					chess_icon = gtk_image_new_from_file("./chess_icon/Qwhite.png");
					break;
				case B_KING:
					chess_icon = gtk_image_new_from_file("./chess_icon/Kblack.png");
					break;
				case W_KING:
					chess_icon = gtk_image_new_from_file("./chess_icon/Kwhite.png");
					break;
				case B_PAWN:
					chess_icon = gtk_image_new_from_file("./chess_icon/Pblack.png");
					break;
				case W_PAWN:
					chess_icon = gtk_image_new_from_file("./chess_icon/Pwhite.png");
					break;
				default:
					break;	
			}
			gtk_table_attach(GTK_TABLE(gametable), chess_icon , i+1, i + 2, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}
}

/*
void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
	*g_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	*g_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
}
*/

// exit on close of game window
static gboolean on_delete_event (GtkWidget *widget, GdkEvent *event, GtkWidget *button, gpointer data)
{
    /*Set to -1 instead of 0 since timer will be trigged +1 before Expiring*/
    sec_expired    = -1;
    continue_timer = FALSE;
    start_timer    = FALSE;

	g_print ("Thanks for playing ZotMate Chess!\n"); 
	gtk_main_quit();
 return TRUE;
}

/* timer label update */
static gboolean timelabel_update(gpointer data)
{
    	GtkLabel *TIMElabel = data;
    	char buf[256];
    	memset(&buf, 0x0, 256);
    	++sec_expired;

    	hr  = (sec_expired%86400) / 3600;
    	min = (sec_expired%3600)  /   60;
    	sec = (sec_expired%3600)  %   60;

    	snprintf(buf, 255, "Time Elapsed: %02d:%02d:%02d ", hr, min, sec);
    	gtk_label_set_label(TIMElabel, buf);
    	return continue_timer;
}

/*Pressing PLAY button*/
static void FUNCstart(GtkWidget *button, gpointer data)
{
	gtk_widget_hide(Menu);
	gtk_widget_show_all(PlayGame);
    	(void) button;
    	GtkWidget *TIMElabel = data;
    	if(!start_timer)
    	{
		g_timeout_add_seconds(1, timelabel_update, TIMElabel);
		start_timer = TRUE;
		continue_timer = TRUE;
    	}
}

/*
gint area_click(GtkWidget* w, GdkEvent *event, gpointer data)
{
	int x1, y1;
	char words[MAX_MSGLEN];
	
	int coord_x, coord_y, grid_x, grid_y;

	struct BOARD *chess_board;
	struct SQUARE *chess_piece;
	struct SQUARE *piece_dest;

	GdkModifierType state;
	gdk_window_get_pointer(w->PlayGame, &coord_x, &coord_y, &state);
	CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);

	printf("InitPos_XY: %d,%d, FinPos_XY: %d,%d", grid_x, grid_y, grid_x, grid_y);
	MoveTheKing(grid_x, grid_y);


	return TRUE;
}
*/


//PvP
static void PvPbutton_toggled(GtkToggleButton *PvPbutton, GtkWidget *w)
{
    	if (gtk_toggle_button_get_active((GtkToggleButton*)PvPbutton))
    	{	
   		g_print("Player vs Player game type chosen\n");
		gtk_widget_set_sensitive(EASYbutton, FALSE);
		gtk_widget_set_sensitive(NORMbutton, FALSE);
		gtk_widget_set_sensitive(HARDbutton, FALSE);
  		gtk_toggle_button_set_active((GtkToggleButton*)PvAIbutton, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*)AIvAIbutton, FALSE);
    	}
	else
	{
		gtk_widget_set_sensitive(EASYbutton, TRUE);
		gtk_widget_set_sensitive(NORMbutton, TRUE);
		gtk_widget_set_sensitive(HARDbutton, TRUE);
	}
}

// PvAI
static void PvAIbutton_toggled(GtkToggleButton *PvAIbutton, GtkWidget *w)
{

    	if (gtk_toggle_button_get_active((GtkToggleButton*)PvAIbutton))
    	{	
   		g_print("Player vs AI game type chosen\n");
		gtk_widget_set_sensitive(EASYbutton, TRUE);
		gtk_widget_set_sensitive(NORMbutton, TRUE);
		gtk_widget_set_sensitive(HARDbutton, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*)AIvAIbutton, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*)PvPbutton, FALSE);
   	}
}

// AIvAI
static void AIvAIbutton_toggled(GtkToggleButton *AIvAIbutton, GtkWidget *w)
{
   	if (gtk_toggle_button_get_active((GtkToggleButton*)AIvAIbutton))
    	{	
   		g_print("AI vs AI game type chosen\n");
		gtk_widget_set_sensitive(EASYbutton, TRUE);
		gtk_widget_set_sensitive(NORMbutton, TRUE);
		gtk_widget_set_sensitive(HARDbutton, TRUE);
		gtk_toggle_button_set_active((GtkToggleButton*)PvAIbutton, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*)PvPbutton, FALSE);
    	}
}

// EASY mode
static void EASYbutton_toggled(GtkToggleButton *EASYbutton, GtkWidget *w)
{
   	if (gtk_toggle_button_get_active((GtkToggleButton*)EASYbutton))
    	{	
   		g_print("Easy game difficulty chosen\n");
		gtk_toggle_button_set_active((GtkToggleButton*)NORMbutton, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*)HARDbutton, FALSE);
    	}
}

// NORMAL mode
static void NORMbutton_toggled(GtkToggleButton *NORMbutton, GtkWidget *w)
{
   	if (gtk_toggle_button_get_active((GtkToggleButton*)NORMbutton))
    	{	
   		g_print("Normal game difficulty chosen\n");
		gtk_toggle_button_set_active((GtkToggleButton*)EASYbutton, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*)HARDbutton, FALSE);
    	}
}

// HARD mode
static void HARDbutton_toggled(GtkToggleButton *HARDbutton, GtkWidget *w)
{
   	if (gtk_toggle_button_get_active((GtkToggleButton*)HARDbutton))
    	{	
   		g_print("Hard game difficulty chosen\n");
		gtk_toggle_button_set_active((GtkToggleButton*)EASYbutton, FALSE);
		gtk_toggle_button_set_active((GtkToggleButton*)NORMbutton, FALSE);
    	}
}

// BLACK team 
static void BLACKbutton_toggled(GtkToggleButton *BLACKbutton, GtkWidget *w)
{
   	if (gtk_toggle_button_get_active((GtkToggleButton*)BLACKbutton))
    	{	
   	printf("Black team selected. Player will move second.\n");
	gtk_toggle_button_set_active((GtkToggleButton*)WHITEbutton, FALSE);
	}
}

// WHITE team
static void WHITEbutton_toggled(GtkToggleButton *WHITEbutton, GtkWidget *w)
{
   	if (gtk_toggle_button_get_active((GtkToggleButton*)WHITEbutton))
    	{	
   	printf("White team selected. Player will move second.\n");
	gtk_toggle_button_set_active((GtkToggleButton*)BLACKbutton, FALSE);
	}
}

//Move Entry
static void move_function(GtkButton *button, GtkWidget *w, gpointer data)
{
     GtkTextBuffer *buffer;
     GtkTextMark *mark;
     GtkTextIter iter;
     const gchar *text;

     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (prev_move));
     text = gtk_entry_get_text (GTK_ENTRY (move_entry));

    mark = gtk_text_buffer_get_insert(buffer);
    gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);

    gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
    if (gtk_text_buffer_get_char_count(buffer))
    {
	gtk_text_buffer_insert (buffer, &iter, "\n", 1);
    }
 
    gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(prev_move), mark);   
    
    gtk_text_buffer_insert (buffer, &iter, text, -1);

}
static void QUITbutton_callback(GtkWidget *button, gpointer data)
{
	/*reset timer*/
    (void) button;
    (void) data  ;
    /*Set to -1 instead of 0 since timer will be trigged +1 before Expiring*/
    sec_expired    = -1;
    continue_timer = FALSE;
    start_timer    = FALSE;
	/*reset timer*/

    gtk_widget_hide(PlayGame);
    gtk_widget_show_all(Menu);
}

int main (int   argc,    char *argv[])
{
        df = pango_font_description_from_string("Serif");
        pango_font_description_set_size(df,20*PANGO_SCALE);
  
	gtk_init(&argc, &argv) ;
	ResetBoard();       
	
	/*create a new window */
	Menu = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  	gtk_widget_set_size_request(Menu, WINDOW_WIDTH, WINDOW_HEIGHT) ; 
  	gtk_container_set_border_width (GTK_CONTAINER(Menu), WINDOW_BORDER) ; 
  	gtk_window_set_position(GTK_WINDOW(Menu), GTK_WIN_POS_CENTER) ; 
  	gtk_window_set_title(GTK_WINDOW(Menu), "ZotMate!") ; 
	gtk_window_set_resizable(GTK_WINDOW(Menu), FALSE) ; 
	
	/*create the play window */
	PlayGame = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(PlayGame, WINDOW_WIDTH, WINDOW_HEIGHT);
	gtk_container_set_border_width(GTK_CONTAINER(PlayGame), WINDOW_BORDER);
	gtk_window_set_position(GTK_WINDOW(PlayGame),GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(PlayGame), "Now Playing ZotMate!");
	gtk_window_set_resizable(GTK_WINDOW(PlayGame), FALSE);
	
	/*create a table and draw the board*/
  	table = gtk_table_new (9, 19, TRUE) ; 
  	gtk_table_set_homogeneous(GTK_TABLE(table), TRUE);
 	gtk_container_add(GTK_CONTAINER(Menu), table);
	title_icon = gtk_image_new_from_file("./chess_icon/zotmate3.png");
	gtk_table_attach(GTK_TABLE(table), title_icon, 0, 9, 0, 10, GTK_EXPAND, GTK_EXPAND, 2, 2);
	
	/*create label*/
	WELCOMElabel = gtk_label_new("Welcome to ZotMate!"          );
	gtk_widget_modify_font(WELCOMElabel, df);
	gtk_table_attach_defaults(GTK_TABLE(table), WELCOMElabel, 10, 18, 0, 1);
	WELCOMElabel = gtk_label_new("Choose your settings: ");
	gtk_table_attach_defaults(GTK_TABLE(table), WELCOMElabel, 10, 18, 1, 2);
	/* label creation done */
	
	gametable = gtk_table_new(9, 19, TRUE);
	gtk_table_set_homogeneous(GTK_TABLE(gametable), TRUE);
	gtk_container_add(GTK_CONTAINER(PlayGame), gametable);

	InitBoard();
	DrawBoard();

	/* make all buttons */
	PLAYbutton = gtk_button_new();
	PLAYlabel  = gtk_label_new("PLAY");
	gtk_widget_modify_font(PLAYlabel, df);
	gtk_container_add(GTK_CONTAINER(PLAYbutton), PLAYlabel); 
	gtk_table_attach_defaults(GTK_TABLE(table), PLAYbutton, 12, 15, 6, 8);
	/* button settings */
	
	// Labels for row/cols on board and make them bold	
	A = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(A), "<b>0</b>");
	B = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(B), "<b>1</b>");
	C = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(C), "<b>2</b>");
	D = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(D), "<b>3</b>");
	E = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(E), "<b>4</b>");
	F = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(F), "<b>5</b>");
	G = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(G), "<b>6</b>");
	H = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(H), "<b>7</b>");
	
	r1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(r1), "<b>0</b>");
	r2 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(r2), "<b>1</b>");
	r3 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(r3), "<b>2</b>");
	r4 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(r4), "<b>3</b>");
	r5 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(r5), "<b>4</b>");
	r6 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(r6), "<b>5</b>");
	r7 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(r7), "<b>6</b>");
	r8 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(r8), "<b>7</b>");

	// Add col labels to window 
	gtk_table_attach_defaults(GTK_TABLE(gametable), r8, 0, 1, 0, 1);	
	gtk_table_attach_defaults(GTK_TABLE(gametable), r7, 0, 1, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(gametable), r6, 0, 1, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(gametable), r5, 0, 1, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(gametable), r4, 0, 1, 4, 5);
	gtk_table_attach_defaults(GTK_TABLE(gametable), r3, 0, 1, 5, 6);
	gtk_table_attach_defaults(GTK_TABLE(gametable), r2, 0, 1, 6, 7);
	gtk_table_attach_defaults(GTK_TABLE(gametable), r1, 0, 1, 7, 8);
  	
	// row labels to window
	gtk_table_attach_defaults(GTK_TABLE(gametable), A, 1, 2, 8, 9);
	gtk_table_attach_defaults(GTK_TABLE(gametable), B, 2, 3, 8, 9);
	gtk_table_attach_defaults(GTK_TABLE(gametable), C, 3, 4, 8, 9);
	gtk_table_attach_defaults(GTK_TABLE(gametable), D, 4, 5, 8, 9);
	gtk_table_attach_defaults(GTK_TABLE(gametable), E, 5, 6, 8, 9);
	gtk_table_attach_defaults(GTK_TABLE(gametable), F, 6, 7, 8, 9);
	gtk_table_attach_defaults(GTK_TABLE(gametable), G, 7, 8, 8, 9);
	gtk_table_attach_defaults(GTK_TABLE(gametable), H, 8, 9, 8, 9);
  	
	/*create a button in the window */
  	PvPbutton = gtk_toggle_button_new_with_mnemonic("Player vs Player");
  	gtk_table_attach_defaults(GTK_TABLE(table), PvPbutton ,  9, 12, 2, 3);

  	PvAIbutton = gtk_toggle_button_new_with_mnemonic("Player vs AI");
  	gtk_table_attach_defaults(GTK_TABLE(table), PvAIbutton, 12,15,2,3);

  	AIvAIbutton = gtk_toggle_button_new_with_mnemonic("AI vs AI");
  	gtk_table_attach_defaults(GTK_TABLE(table), AIvAIbutton, 15,18,2,3);

  	EASYbutton = gtk_toggle_button_new_with_label("Easy");
  	gtk_table_attach_defaults(GTK_TABLE(table), EASYbutton, 9,12,3,4);

  	NORMbutton = gtk_toggle_button_new_with_label("Normal");
  	gtk_table_attach_defaults(GTK_TABLE(table), NORMbutton, 12,15,3,4);

  	HARDbutton = gtk_toggle_button_new_with_label("Hard");
  	gtk_table_attach_defaults(GTK_TABLE(table), HARDbutton, 15,18,3,4);

  	BLACKbutton = gtk_toggle_button_new_with_label("Black");
  	gtk_table_attach_defaults(GTK_TABLE(table), BLACKbutton, 10,13,4,5);
  	
	WHITEbutton = gtk_toggle_button_new_with_label("White");
  	gtk_table_attach_defaults(GTK_TABLE(table), WHITEbutton, 14,17,4,5);
  	
	QUITbutton = gtk_button_new();
	QUITlabel = gtk_label_new("QUIT");
  	gtk_widget_modify_font(QUITlabel, df);
	gtk_container_add(GTK_CONTAINER(QUITbutton), QUITlabel); 
	gtk_table_attach_defaults(GTK_TABLE(gametable), QUITbutton, 12, 15, 7, 8);

	/*register event handlers*/  
  	g_signal_connect(Menu, "delete_event", G_CALLBACK(on_delete_event), NULL) ; 
  	gtk_widget_set_events(Menu, GDK_BUTTON_PRESS_MASK);
	
	/* TIMER WIDGET */
	TIMElabel = gtk_label_new("Time Elapsed: 00:00:00 ");
	gtk_table_attach_defaults(GTK_TABLE(gametable), TIMElabel, 11, 16, 6, 7);


	/* move entries box */
	desired_move = gtk_label_new("Enter desired move: (EX. 33 : 45)");
	move_entry = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(move_entry), 7); 

	scrolltext = gtk_scrolled_window_new(NULL, NULL);
	prev_move = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(prev_move), FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(prev_move), FALSE);
	gtk_container_add(GTK_CONTAINER(scrolltext), prev_move);

	gtk_table_attach_defaults(GTK_TABLE(gametable), desired_move, 10, 17, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(gametable), move_entry, 13, 15, 2, 3);
	

	gtk_table_attach_defaults(GTK_TABLE(gametable), scrolltext, 13, 15, 3, 6); 
	enter_move = gtk_button_new_with_label("OK");
	
	gtk_table_attach_defaults(GTK_TABLE(gametable), enter_move, 16, 17, 2, 3);

/*  horizontal = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (scrolltext));
  vertical = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (scrolltext));
  viewport = gtk_viewport_new (horizontal, vertical);
*/
  	/*initalize player 1, no difficulty, and player 1 is white*/ 
	gtk_toggle_button_set_active((GtkToggleButton*)PvPbutton, TRUE);
	gtk_toggle_button_set_active((GtkToggleButton*)WHITEbutton, TRUE);  	
	gtk_widget_set_sensitive(EASYbutton, FALSE);
	gtk_widget_set_sensitive(NORMbutton, FALSE);
	gtk_widget_set_sensitive(HARDbutton, FALSE);
	/*register event handlers*/

	/*close*/
	g_signal_connect(Menu, "delete_event", G_CALLBACK(on_delete_event), NULL) ; 
	gtk_widget_set_events(Menu, GDK_BUTTON_PRESS_MASK);
	
	/* start game and timer */
	g_signal_connect(G_OBJECT(PLAYbutton) , "clicked", G_CALLBACK(FUNCstart), TIMElabel);
	
	/* toggle PvP,PvAI,AIvAI button*/
	g_signal_connect(G_OBJECT(PvPbutton)  , "toggled", G_CALLBACK(PvPbutton_toggled)  ,NULL	);
  	g_signal_connect(G_OBJECT(PvAIbutton) , "toggled", G_CALLBACK(PvAIbutton_toggled) ,NULL );
	g_signal_connect(G_OBJECT(AIvAIbutton), "toggled", G_CALLBACK(AIvAIbutton_toggled), NULL);
	/* toggle difficulty modes */
  	g_signal_connect(EASYbutton, "toggled", G_CALLBACK(EASYbutton_toggled), NULL);
  	g_signal_connect(NORMbutton, "toggled", G_CALLBACK(NORMbutton_toggled), NULL);
  	g_signal_connect(HARDbutton, "toggled", G_CALLBACK(HARDbutton_toggled), NULL);
	/* toggle player mode */
  	g_signal_connect(BLACKbutton,"toggled", G_CALLBACK(BLACKbutton_toggled), NULL);
  	g_signal_connect(WHITEbutton,"toggled", G_CALLBACK(WHITEbutton_toggled), NULL);
	/* enter the move */
	g_signal_connect(G_OBJECT(enter_move), "key_press_event", G_CALLBACK(move_function), NULL);
	//quit
	g_signal_connect(QUITbutton,"clicked", G_CALLBACK(QUITbutton_callback), NULL);

	gtk_widget_show_all(Menu);
	gtk_main();
  	return 0 ;
}
