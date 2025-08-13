#include <stdarg.h>
#include <unistd.h>

#include "rendering/print.h"
#include "rendering/canvas.h"


/**
 * @brief The main loop.
 */
int main(void) {
  if (!colors_supported()) {
    print_error("Colors are not supported in your terminal!");
  }

  Canvas canvas = init_canvas(32, 32, 0, 1, 1);
  draw_canvas(&canvas);
  // clear_canvas(&canvas);

  return 0;
}
