#ifndef CANVAS_H_
#define CANVAS_H_

#include "print.h"

typedef struct {
  char character[8];
  color_t fg_color;
  color_t bg_color;
  int bold;
} Cell;

typedef struct {
  int width;
  int height;
  int background_strength;
  int border;
  int autosize;
  Cell* cells;
} Canvas;

void draw_canvas(Canvas* canvas);
Canvas init_canvas(int width, int height, int background_strength, int border, int autosize);
void clear_canvas(Canvas* canvas);
void canvas_set_pixel(Canvas* canvas, int x, int y, const char* character, color_t fg, color_t bg);

#endif

