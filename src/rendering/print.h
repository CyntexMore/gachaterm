#ifndef PRINT_H_
#define PRINT_H_

#include <stdarg.h>

/* Color macros */
#define RESET       "\x1B[0m"
#define BLACK       "\x1B[30m"
#define RED         "\x1B[31m"
#define GREEN       "\x1B[32m"
#define YELLOW      "\x1B[33m"
#define BLUE        "\x1B[34m"
#define PURPLE      "\x1B[35m"
#define CYAN        "\x1B[36m"
#define WHITE       "\x1B[37m"
#define BOLD_BLACK  "\x1B[1;30m"
#define BOLD_RED    "\x1B[1;31m"
#define BOLD_GREEN  "\x1B[1;32m"
#define BOLD_YELLOW "\x1B[1;33m"
#define BOLD_BLUE   "\x1B[1;34m"
#define BOLD_PURPLE "\x1B[1;35m"
#define BOLD_CYAN   "\x1B[1;36m"
#define BOLD_WHITE  "\x1B[1;37m"
#define BG_BLACK    "\x1B[40m"
#define BG_RED      "\x1B[41m"
#define BG_GREEN    "\x1B[42m"
#define BG_YELLOW   "\x1B[43m"
#define BG_BLUE     "\x1B[44m"
#define BG_PURPLE   "\x1B[45m"
#define BG_CYAN     "\x1B[46m"
#define BG_WHITE    "\x1B[47m"

/* Cell macros */
#define CELL_EMPTY  " "
#define CELL_FULL   "█"
#define CELL_LIGHT  "░"
#define CELL_MEDIUM "▒"
#define CELL_DARK   "▓"
#define CELL_H_B    "▄"
#define CELL_H_T    "▀"
#define CELL_H_L    "▌"
#define CELL_H_R    "▐"
#define CELL_F_BL   "▖"
#define CELL_F_BR   "▗"
#define CELL_F_TL   "▘"
#define CELL_F_TR   "▝"
#define CELL_T_BL   "▞"
#define CELL_T_BR   "▚"
#define CELL_T_TL   "▛"
#define CELL_T_TR   "▜"

/* Color type */
typedef enum {
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_PURPLE,
    COLOR_CYAN,
    COLOR_WHITE
} color_t;

/* Cell type */
typedef enum {
    FOURTH,
    THREE,
    HALF,
    FULL
} cell_t;

/* Cell alignment */
typedef enum {
    BL,
    BR,
    TL,
    TR,
    BOTTOM,
    TOP,
    LEFT,
    RIGHT
} alig_t;

/* Terminal color support */
int colors_supported(void);

/* Color code functions */
const char* get_color_code(color_t color, int bold);
const char* get_bg_color_code(color_t color);

/* Printing functions */
void print_colored(color_t color, int bold, const char* format, ...);
void print_colored_bg(color_t color, color_t bg_color, const char* format, ...);
void print_error(const char* format, ...);
void print_success(const char* format, ...);
void print_caution(const char* format, ...);
void print_tip(const char* format, ...);
void print_extra(const char* format, ...);

/* Cell printing functions */
void print_cell(cell_t cell_type, alig_t cell_alignment);
void print_shaded_cell(int strength);

#endif /* PRINT_H_ */
