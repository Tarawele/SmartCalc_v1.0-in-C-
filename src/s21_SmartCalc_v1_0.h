#ifndef SRC_S21_SMARTCALC_V1_0_H_
#define SRC_S21_SMARTCALC_V1_0_H_

#include <gtk/gtk.h>

#include "s21_polish.h"

GtkWidget *LCD;
FILE *temp;
FILE *gnuplotPipe;
GtkWidget *spinbox1;
GtkWidget *spinbox2;
GtkWidget *spinbox1Y;
GtkWidget *spinbox2Y;
GtkWidget *spinbox1_credit;
GtkWidget *spinbox2_credit;
GtkWidget *spinbox3_credit;
GtkWidget *spinbox4_credit;
GtkWidget *spinbox5_credit;
GtkWidget *spinbox6_credit;
GtkWidget *downwidget;

GtkWidget *spinbox1_dep;
GtkWidget *spinbox2_dep;
GtkWidget *spinbox3_dep;
GtkWidget *spinbox4_dep;
GtkWidget *spinbox5_dep;
GtkWidget *spinbox6_dep;
GtkWidget *spinbox7_dep;
GtkWidget *spinbox8_dep;
GtkWidget *spinbox9_dep;
GtkWidget *spinbox10_dep;
GtkWidget *spinbox11_dep;

typedef struct application {
  GtkApplication *app;

  GtkWidget *boxMain;
  GtkWidget *boxEntry;
  GtkWidget *boxGrid;
  GtkWidget *window;
  GtkWidget *entry;
  GtkWidget *grid;
  GtkEntryBuffer *bufferEntry;

  GtkWidget *boxOpenButtons;
  GtkWidget *trigs;
  GtkWidget *actions;
  GtkWidget *graph;

  GtkWidget *errorWindow;

  GtkWidget *boxMainDialog;
  GtkWidget *dialog;
  GtkWidget *entryDialogPosX;
  GtkWidget *entryDialogNegX;
  GtkWidget *labelPosX;
  GtkWidget *labelNegX;
  GtkWidget *dialogGrid;
  GtkEntryBuffer *bufferEntryDialogPosX;
  GtkEntryBuffer *bufferEntryDialogNegX;
} App;

gchar *labels[3][4] = {
    {"7", "4", "1", "."}, {"8", "5", "2", "0"}, {"9", "6", "3", "="}};

gchar *trigLabels[2][5] = {{"acos", "asin", "atan", "sqrt", "ln"},
                           {"cos", "sin", "tan", "log", "x"}};

gchar *actionLabels[2][4] = {{"/", "*", "-", "+"}, {"%", "^", "(", ")"}};

static void Credit_Calc();
static void Credit();
static void Deposit();
static void Deposit_Calc();
static void CreateErrorWindow(App *application);
static void DestroyGraphWindow(GtkWidget *button, App *application);
static double GetStepsCount(int xRange);
static void DrawCoordLines(cairo_t *cr, double x1, double y1, double x2,
                           double y2, const gchar *text);
static double ApplyDrawSettings(cairo_t *cr, double xLength, double xStPos,
                                int width, int height);
static void DrawGraph(GtkDrawingArea *drawing_area, cairo_t *cr, int width,
                      int height, App *application);
static void CreateGraphWindow(GtkWidget *button, App *application);
static void DestroyDialogWindow(GtkWidget *dialog, App *application);
static void DestroyApp(GtkWidget *window, App *application);
static void AdditionNegX(GtkWidget *button, App *application);
static void SubstractionNegX(GtkWidget *button, App *application);
static void AdditionPosX(GtkWidget *button, App *application);
static void SubstractionPosX(GtkWidget *button, App *application);
static void AddElementsToTheDialogGrid(App *application);
static void CreateDialogButtons(App *application);
static void CreateDialogGrid(App *application);
static void CreateDialogLabels(App *application);
static void CreateDialogEntries(App *application);
static void CreateDialogElements(App *application);
static void CreateDialogWindow(GtkWidget *button, App *application);
static void Calc(GtkWidget *button, App *application);
static void PrintToEntry(GtkWidget *button, App *application);
static void AddButtonsToTheGrid(App *application);
static void CreateGrid(App *application);
static void CreateEntry(App *application);
static void CreateElements(App *application);
static void CreateApp(GtkApplication *app, App *application);
static int RunApp(int argc, char **argv);
bool IsCorrectString(char *str);
bool isCorrectTrigString(char *str);

#endif // SRC_S21_SMARTCALC_V1_0_H_
