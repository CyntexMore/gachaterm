\page shader_lang GachaShade Language Reference

# The GachaShade Language

**GachaShade** isn't a new language, but rather a specific way of writing C code that can be dynamically loaded by the GachaTerm engine. Every shader is a self-contained C file compiled into a shared library (`.so`).

## The Shader Entry Point

Every shader must implement the `execute` function, which is called by the engine on every frame.

```c
void execute(Canvas* canvas, float time);
```

- `canvas`: A pointer to the main canvas framebuffer. You draw to the screen by modifying this object.
- `time`: A floating-point value representing the time in seconds since the engine started. This is your primary "uniform" for creating animations.

## Built-in Types and Functions

Your shaders have access to all standard C functions (`<math.h>`, etc.) plus the following helpers defined in `gachashade.h`:

### Types

- `vec2`: A simple struct to hold 2D coordinates.

```c
typedef struct { float x, y; } vec2;
```

### Core API

- `canvas_set_pixel()`: The primary drawing function.

```c
void canvas_set_pixel(Canvas* canvas, int x, int y, const char* character, color_t fg, color_t bg);
```

This function sets the character and color for a single cell at coordinates `(x, y)`.

