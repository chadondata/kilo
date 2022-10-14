#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#define KILO_VERSION "0.0.1"
#define KILO_TAB_STOP 8
#define CTRL_KEY(k) ((k) & 0x1f)
#define INIT_ABUF {NULL, 0}

typedef struct erow {
    int size;
    int rsize;
    char *chars;
    char *render;
} erow;

struct cursor {
    int x;
    int y;
};

struct editorConfig {
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
    int numrows;
    erow *row;
    struct termios orig_termios;
    struct cursor c;
    int rx;
};

struct abuf {
    char *b;
    int len;
};

enum editorKey {
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARRROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

void abAppend(struct abuf *ab, const char *s, int len);
void abFree(struct abuf *ab);
void die(const char *s);
void disableRawMode();
void editorAppendRow(char *s, size_t len);
void editorDrawRows(struct abuf *ab);
void editorRefreshScreen();
void editorMoveCursor(int key);
void editorOpen(char *filename);
void editorProcessKeypress();
int editorReadKey();
int editorRowCxToRx(erow *row, int cx);
void editorScroll();
void editorUpdateRow(erow *row);
void enableRawMode();
int getCursorPosition(int *rows, int *columns);
int getWindowSize(int *rows, int *cols);
void initEditor();
int main();
int getCursorPosition(int *rows, int *columns);
