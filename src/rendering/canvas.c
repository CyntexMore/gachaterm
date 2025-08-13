#include <stdlib.h>
#include <stdio.h>

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

  for (int i = 0; i < canvas->height; i++) {
    printf("\n");
    if (canvas->border) printf("│");

    for (int ii = 0; canvas->autosize == 1 ? ii < canvas->width*2 : ii < canvas->width; ii++) {
      print_shaded_cell(canvas->background_strength);
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

/**
 * @brief Initializes a `Canvas` object.
 * * This function initializes a `Canvas` object based on the arguments
 * passed to it. The only reason to use this instead of making a struct
 * directly is that this function validates input. 
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
