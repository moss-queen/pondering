#include "duck.h"
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>



int add_D51(int x, int y);
int add_D21(int x, int y);
void add_smoke(int y, int x);
void add_snoke(int y, int x);
void option(char *str);
int my_mvaddstr(int y, int x, char *str);

int ACCIDENT = 0;
int LOGO = 0;
int FLY = 0;
int C51 = 0;

int my_mvaddstr(int y, int x, char *str) {
  for (; x < 0; ++x, ++str)
    if (*str == '\0')
      return ERR;
  for (; *str != '\0'; ++str, ++x)
    if (mvaddch(y, x, *str) == ERR)
      return ERR;
  return OK;
}

void option(char *str) {
  extern int ACCIDENT, LOGO, FLY, C51;

  while (*str != '\0') {
    switch (*str++) {
    case 'a':
      ACCIDENT = 1;
      break;
    case 'F':
      FLY = 1;
      break;
    case 'l':
      LOGO = 1;
      break;
    case 'c':
      C51 = 1;
      break;
    default:
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  int x, x2, i,v, w,s,t;

  for (i = 1; i < argc; ++i) {
    if (*argv[i] == '-') {
      option(argv[i] + 1);
    }
  }
  initscr();
    start_color();
  init_pair(3,COLOR_YELLOW,COLOR_BLUE);
  bkgd(COLOR_PAIR(3));
  refresh();

  signal(SIGINT, SIG_IGN);
  noecho();
  curs_set(0);
  nodelay(stdscr, TRUE);
  leaveok(stdscr, TRUE);
  scrollok(stdscr, FALSE);
  s = 1;
  t = 0;
v = (int)(rand() % LINES);
w = (int)(rand() % LINES);
x = COLS - 1;
x2 = COLS - 1;
while(1)
{
    mvwaddstr(stdscr,(LINES/2),((COLS-1)/2) - 6, "MUCH TO PONDER");
if(s == 1)
{
s = 1;
    if(x < ((COLS - 1)/2))
	t = 1;
    if (add_D51(x,v) == ERR)
        break;
    x--;
    if(x == 0)
    {
    	v = (int)(rand() % LINES);
    	s = 0;
    	x = COLS - 1;
    }
}
if(t == 1)
{
t = 1;
    if(x2 < ((COLS - 1)/2))
        s = 1;
    if (add_D21(COLS-1-x2,w) == ERR)
        break;
    x2--;
    if(x2 == 0)
    {
    	w = (int)(rand() % LINES);
    	t = 0;
    	x2 = COLS - 1;
    }
}
    getch();
    refresh();
    usleep(40000);
}
  mvcur(0, COLS - 1, LINES - 1, 0);
  endwin();
  return 0;
}

int add_D51(int x, int y) {
  static char *d51[D51PATTERNS][D51HEIGHT + 1] = {
      {D51STR1, D51STR2, D51STR3, D51STR4, D51STR5, D51DEL}};
  int i = 0;

  if (x < -D51LENGTH)
    return ERR;

  for (i = 0; i <= D51HEIGHT; ++i) {
    my_mvaddstr(y + i, x - 12, d51[(D51LENGTH + x) % D51PATTERNS][i]);
  }
  add_smoke(y + 3, x - 3);
  return OK;
}
void add_smoke(int y, int x)
#define SMOKEPTNS 2
{
  static struct smokes {
    int y, x;
    int ptrn, kind;
  } S[1000];
  static int sum = 0;
  static char *Smoke[1][SMOKEPTNS] = {
      {"~^","~^~^~^~^~"}};
  static char *Eraser[SMOKEPTNS] = {"  ","         "};
  static int dy[SMOKEPTNS] = {0,0};
  static int dx[SMOKEPTNS] = {-2, -1};
  int i;

  if (x % 4 == 0) {
    for (i = 0; i < sum; ++i) {
      my_mvaddstr(S[i].y, S[i].x, Eraser[S[i].ptrn]);
      S[i].y -= dy[S[i].ptrn];
      S[i].x += dx[S[i].ptrn];
      S[i].ptrn += (S[i].ptrn < SMOKEPTNS - 1) ? 1 : 0;
      my_mvaddstr(S[i].y, S[i].x, Smoke[S[i].kind][S[i].ptrn]);
    }
    my_mvaddstr(y, x, Smoke[sum % 2][0]);
    S[sum].y = y;
    S[sum].x = x;
    S[sum].ptrn = 0;
    S[sum].kind = sum % 2;
    sum++;
  }
}

int add_D21(int x, int y) {
  static char *d21[D21PATTERNS][D21HEIGHT + 1] = {
      {D21STR1, D21STR2, D21STR3, D21STR4, D21STR5, D21DEL}};
  int i = 0;

  if (x > COLS)
    return ERR;

  for (i = 0; i <= D21HEIGHT; ++i) {
    my_mvaddstr(y + i, x + 1, d21[(D21LENGTH - x) % D21PATTERNS][i]);
  }
  add_snoke(y + 3, x - D21FUNNEL);
  return OK;
}
void add_snoke(int y, int x)
#define SNOKEPTNS 2
{
  static struct snokes {
    int y, x;
    int ptrn, kind;
  } S[1000];
  static int sum = 0;
  static char *Snoke[1][SNOKEPTNS] = {
      {"~^","~^~^~^~^~"}};
  static char *Eraser[SNOKEPTNS] = {"  ","         "};
  static int dy[SNOKEPTNS] = {0,0};
  static int dx[SNOKEPTNS] = {2, 1};
  int i;

  if (x % 4 == 0) {
    for (i = 0; i < sum; ++i) {
      my_mvaddstr(S[i].y, S[i].x, Eraser[S[i].ptrn]);
      S[i].y -= dy[S[i].ptrn];
      S[i].x += dx[S[i].ptrn];
      S[i].ptrn += (S[i].ptrn < SNOKEPTNS - 1) ? 1 : 0;
      my_mvaddstr(S[i].y, S[i].x, Snoke[S[i].kind][S[i].ptrn]);
    }
    my_mvaddstr(y, x, Snoke[sum % 2][0]);
    S[sum].y = y;
    S[sum].x = x;
    S[sum].ptrn = 0;
    S[sum].kind = sum % 2;
    sum++;
  }
}

