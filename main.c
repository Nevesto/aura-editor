#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "editor.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    Editor *editor = editor_init(filename);
    if (editor == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return 1;
    }

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    editor_run(editor);

    endwin();
    editor_free(editor);

    return 0;
}
