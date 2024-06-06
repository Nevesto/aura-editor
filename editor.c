#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "editor.h"

Editor* editor_init(const char *filename) {
    Editor *editor = malloc(sizeof(Editor));
    if (editor == NULL) return NULL;

    editor->filename = strdup(filename);
    if (editor->filename == NULL) {
        free(editor);
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        free(editor->filename);
        free(editor);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    editor->size = ftell(file);
    fseek(file, 0, SEEK_SET);

    editor->content = malloc(editor->size + 1);
    if (editor->content == NULL) {
        fclose(file);
        free(editor->filename);
        free(editor);
        return NULL;
    }

    fread(editor->content, 1, editor->size, file);
    fclose(file);
    editor->content[editor->size] = '\0';

    editor->cx = 0;
    editor->cy = 0;

    return editor;
}

void editor_run(Editor *editor) {
    int ch;
    while ((ch = getch()) != 'q') { 
        switch (ch) {
            case KEY_UP:
                if (editor->cy > 0) editor->cy--;
                break;
            case KEY_DOWN:
                if (editor->cy < LINES - 1) editor->cy++;
                break;
            case KEY_LEFT:
                if (editor->cx > 0) editor->cx--;
                break;
            case KEY_RIGHT:
                if (editor->cx < COLS - 1) editor->cx++;
                break;
        }

        clear();
        mvprintw(editor->cy, editor->cx, "%s", editor->content);
        refresh();
    }
}

void editor_free(Editor *editor) {
    free(editor->filename);
    free(editor->content);
    free(editor);
}
