#include <dlfcn.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "rendering/print.h"
#include "rendering/canvas.h"

typedef void (*shader_execute_func)(Canvas*, float);

/**
 * @brief The main loop.
 */
int main(void) {
  if (!colors_supported()) {
    print_error("Colors are not supported in your terminal!");
  }

  /* Load shader */
  void* shader_handle = dlopen("./plasma.so", RTLD_LAZY);
  if (!shader_handle) {
    print_error("Cannot load shader: %s\n", dlerror());
    return 1;
  }

  shader_execute_func shader_execute = (shader_execute_func)dlsym(shader_handle, "execute");
  char* error = dlerror();
  if (error != NULL) {
    print_error("Cannot find 'execute' function in shader: %s\n", error);
    dlclose(shader_handle);
    return 1;
  }

  Canvas canvas = init_canvas(64, 64, 0, 1, 0);
  struct timespec start, current;
  clock_gettime(CLOCK_MONOTONIC, &start);

  while (1) {
    clock_gettime(CLOCK_MONOTONIC, &current);
    float time_elapsed = (current.tv_sec - start.tv_sec) + (current.tv_nsec - start.tv_nsec) / 1e9f;

    printf("\x1B[H");

    shader_execute(&canvas, time_elapsed);

    draw_canvas(&canvas);
    fflush(stdout);

    usleep(16666);
  }

  dlclose(shader_handle);
  free(canvas.cells);

  return 0;
}
