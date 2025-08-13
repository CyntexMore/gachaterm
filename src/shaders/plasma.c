#include <math.h>
#include "gachashade.h"

void execute(Canvas* canvas, float time) {
  for (int y = 0; y < canvas->height; y++) {
    for (int x = 0; x < canvas->width; x++) {
      float val = sin(x / 16.0 + time) +
                  sin(y / 8.0 + time) +
                  sin((x + y) / 16.0 + time) +
                  sin(sqrt(x*x + y*y) / 8.0 + time);

      int color_index = (int)((val + 4.0) / 8.0 * 4.0);
      const char* shade;
      switch (color_index) {
        case 0: shade = CELL_EMPTY; break;
        case 1: shade = CELL_LIGHT; break;
        case 2: shade = CELL_MEDIUM; break;
        case 3: shade = CELL_DARK; break;
        default: shade = CELL_FULL; break;
      }

      canvas_set_pixel(canvas, x, y, shade, COLOR_CYAN, COLOR_BLACK);
    }
  }
}
