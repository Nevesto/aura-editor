#ifndef EDITOR_H
#define EDITOR_H

typedef struct {
    char *filename;
    char *content;
    size_t size;
    int cx, cy;
} Editor;

Editor* editor_init(const char *filename);
void editor_run(Editor *editor);
void editor_free(Editor *editor);

#endif