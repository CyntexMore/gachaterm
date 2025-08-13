#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "print.h"
#include "canvas.h"

/**
 * @brief Draw a canvas.
 * * This function draws a canvas from a `Canvas` object. Note that
 * `width` is multiplied by two, to even out size difference between
 * cells that come from the height of cells being bigger than their
 * width. If you don't want this to happen, set `autosize` to `0`.
 * * @param canvas A value of type `Canvas` (`Canvas*`).
 */
void draw_canvas(Canvas* canvas) {
  if (canvas->border) {
    printf("┌");

    for (int i = 0; canvas->autosize == 1 ? i < canvas->width*2 : i < canvas->width; i++) {
      printf("─");
    }

    printf("┐");
  }

  for (int y = 0; y < canvas->height; y++) {
    printf("\n");
    if (canvas->border) printf("│");

    for (int x = 0; canvas->autosize == 1 ? x < canvas->width*2 : x < canvas->width; x++) {
      Cell* cell = &canvas->cells[y * canvas->width + x];
      print_colored_bg(cell->fg_color, cell->bg_color, "%s", cell->character);
    }

    if (canvas->border) printf("│");
  }

  if (canvas->border) {
    printf("\n└");

    for (int i = 0; canvas->autosize == 1 ? i < canvas->width*2 : i < canvas->width; i++) {
      printf("─");
    }

    printf("┘");
  }
}

void canvas_set_pixel(Canvas* canvas, int x, int y, const char* character, color_t fg, color_t bg) {
  if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height) {
    Cell* cell = &canvas->cells[y * canvas->width + x];
    strcpy(cell->character, character);
    cell->fg_color = fg;
    cell->bg_color = bg;
  }
}

/**
 * @brief Initializes a `Canvas` object.
 * * This function initializes a `Canvas` object based on the arguments
 * passed to it. The only reason to use this instead of making a struct
 * directly is that this function validates input and allocates memory
 * for cells automatically. 
 * * @param width A value of type `int`. The canvas's width.
 * @param height A value of type `int`. The canvas's height.
 * @param background_strength A value of type `int`. The canvas's background's
 * cell shading strength. `0` is transparent, `12` is normal text. (See:
 * `print_shaded_cell()` for shading information.)
 * @param border Can be `0` or `1`. Determines if the canvas should have a
 * border or not.
 * @param autosize Can be `0` or `1`. Determines if auto strecthing should be
 * applied to the `width` or not.
 */
Canvas init_canvas(int width, int height, int background_strength, int border, int autosize) {
  if (width > 128) {
    width = 128;
  } else if (width <= 0) {
    width = 1;
  }

  if (height > 128) {
    height = 128;
  } else if (height <= 0) {
    height = 1;
  }

  if (background_strength < 0) {
    background_strength = 0;
  } else if (background_strength > 12) {
    background_strength = 12;
  }

  if (border < 0) {
    border = 0;
  } else if (border > 1) {
    border = 1;
  }

  if (autosize < 0) {
    autosize = 0;
  } else if (autosize > 1) {
    autosize = 1;
  }

  Canvas canvas = {width, height, background_strength, border, autosize};

  canvas.cells = malloc(width * height * sizeof(Cell));

  for (int i = 0; i < width * height; i++) {
    strcpy(canvas.cells[i].character, " ");
    canvas.cells[i].fg_color = COLOR_WHITE;
    canvas.cells[i].bg_color = COLOR_BLACK;
    canvas.cells[i].bold = 0;
  }

  return canvas;
}

/**
 * @brief Clears the canvas.
 * * This function clears the canvas of all objects, then re-renders it.
 * * @param canvas A value of type `Canvas` (`Canvas*`). The canvas to
 * be cleared.
 */
void clear_canvas(Canvas* canvas) {
  system("clear");
  printf("\n");
  draw_canvas(canvas);
}
