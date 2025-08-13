#ifndef CANVAS_H_
#define CANVAS_H_

typedef struct {
  int width;
  int height;
  int background_strength;
  int border;
  int autosize;
} Canvas;

void draw_canvas(Canvas* canvas);
Canvas init_canvas(int width, int height, int background_strength, int border, int autosize);
void clear_canvas(Canvas* canvas);

#endif

