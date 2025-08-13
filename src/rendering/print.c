#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "print.h"

/**
 * @brief Determines if the terminal supports colors.
 */
int colors_supported(void) {
  return isatty(STDOUT_FILENO);
}

/**
 * @brief Pairs a value of `color_t` to a color macro.
 * * This functions pairs a value of `color_t` with a `BOLD_` or normal color macro.
 * * @param color A value of `color_t`. The desired color.
 * @param bold `0` or `1`. Determines if the text is bold or not.
 */
const char* get_color_code(color_t color, int bold) {
  if (bold) {
    switch (color) {
      case COLOR_BLACK:   return BOLD_BLACK;
      case COLOR_RED:     return BOLD_RED;
      case COLOR_GREEN:   return BOLD_GREEN;
      case COLOR_YELLOW:  return BOLD_YELLOW;
      case COLOR_BLUE:    return BOLD_BLUE;
      case COLOR_PURPLE:  return BOLD_PURPLE;
      case COLOR_CYAN:    return BOLD_CYAN;
      case COLOR_WHITE:   return BOLD_WHITE;
      default:            return "";
    }
  } else {
    switch (color) {
      case COLOR_BLACK:   return BLACK;
      case COLOR_RED:     return RED;
      case COLOR_GREEN:   return GREEN;
      case COLOR_YELLOW:  return YELLOW;
      case COLOR_BLUE:    return BLUE;
      case COLOR_PURPLE:  return PURPLE;
      case COLOR_CYAN:    return CYAN;
      case COLOR_WHITE:   return WHITE;
      default:            return "";
    }
  }
}

/**
 * @brief Pairs a value of `color_t` with a `BG_` color macro.
 * * This functions pairs a value of `color_t` with a `BG_` color macro.
 * * @param color A value of `color_t`. The background color.
 */
const char* get_bg_color_code(color_t color) {
  switch (color) {
    case COLOR_BLACK:     return BG_BLACK;
    case COLOR_RED:       return BG_RED;
    case COLOR_GREEN:     return BG_GREEN;
    case COLOR_YELLOW:    return BG_YELLOW;
    case COLOR_BLUE:      return BG_BLUE;
    case COLOR_PURPLE:    return BG_PURPLE;
    case COLOR_CYAN:      return BG_CYAN;
    case COLOR_WHITE:     return BG_WHITE;
    default:              return "";
  }
}

/**
 * @brief Prints a colored formatted string to the standard output.
 * * This function formats and prints a colored string to the standard output.
 * * @param color A value of type `color_t`. Text color.
 * @param bold `0` or `1`. Determines if the text is bold or not.
 * @param format A format string for the message.
 * @param ... A variable number of arguments for the format string.
 */
void print_colored(color_t color, int bold, const char* format, ...) {
  va_list args;
  va_start(args, format);

  if (colors_supported()) {
    printf("%s", get_color_code(color, bold));
    vprintf(format, args);
    printf("%s", RESET);
  } else {
    vprintf(format, args);
  }

  va_end(args);
}

/**
 * @brief Prints a colored formatted string to the standard output with a colored background.
 * * This function formats and prints a colored string to the standard output with a colored background.
 * * @param color A value of type `color_t`. Text color.
 * @param bg_color A value of type `color_t`. Background color.
 * @param format A format string for the message.
 * @param ... A variable number of arguments for the format string.
 */
void print_colored_bg(color_t color, color_t bg_color, const char* format, ...) {
  va_list args;
  va_start(args, format);

  if (colors_supported()) {
    printf("%s%s", get_color_code(color, 0), get_bg_color_code(bg_color));
    vprintf(format, args);
    printf("%s", RESET);
  } else {
    vprintf(format, args);
  }

  va_end(args);
}

/**
 * @brief Prints a formatted error message with a red "ERROR" prefix.
 * * This function formats and prints a message to the standard output.
 * The "ERROR" prefix is printed in bold red, followed by the user-
 * provided message in the default terminal color.
 * * @param format A format string for the message.
 * @param ... A variable number of arguments for the format string.
 */
void print_error(const char* format, ...) {
  va_list args;
  va_start(args, format);

  if (colors_supported()) {
    printf("%sERROR%s   : ", get_color_code(COLOR_RED, 1), RESET);
    vprintf(format, args);
  } else {
    vprintf(format, args);
  }

  va_end(args);
}

/**
 * @brief Prints a formatted error message with a green "SUCCESS" prefix.
 * * This function formats and prints a message to the standard output.
 * The "SUCCESS" prefix is printed in bold green, followed by the user-
 * provided message in the default terminal color.
 * * @param format A format string for the message.
 * @param ... A variable number of arguments for the format string.
 */
void print_success(const char* format, ...) {
  va_list args;
  va_start(args, format);

  if (colors_supported()) {
    printf("%sSUCCESS%s : ", get_color_code(COLOR_GREEN, 1), RESET);
    vprintf(format, args);
  } else {
    vprintf(format, args);
  }

  va_end(args);
}

/**
 * @brief Prints a formatted caution message with a yellow "CAUTION" prefix.
 * * This function formats and prints a message to the standard output.
 * The "CAUTION" prefix is printed in bold yellow, followed by the user-
 * provided message in the default terminal font.
 * * @param format A format string for the message.
 * @param ... A variable number of arguments for the format string.
 */
void print_caution(const char* format, ...) {
  va_list args;
  va_start(args, format);

  if (colors_supported()) {
    printf("%sCAUTION%s : ", get_color_code(COLOR_YELLOW, 1), RESET);
    vprintf(format, args);
  } else {
    vprintf(format, args);
  }
  
  va_end(args);
}

/**
 * @brief Prints a formatted tip message with a blue "TIP" prefix.
 * * This function formats and prints a message to the standard output.
 * The "TIP" prefix is printed in bold blue, followed by the user-
 * provided message in the default terminal font.
 * * @param format A format string for the message.
 * @param ... A variable number of arguments for the format string.
 */
void print_tip(const char* format, ...) {
  va_list args;
  va_start(args, format);

  if (colors_supported()) {
    printf("%sTIP%s     : ", get_color_code(COLOR_BLUE, 1), RESET);
    vprintf(format, args);
  } else {
    vprintf(format, args);
  }

  va_end(args);
}

/**
 * @brief Prints a formatted side ntoe with a white (greyish) color.
 * * This function formats and prints a message to the standard output.
 * * @param format A format string for the message.
 * @param ... A variable number of arguments for the format string.
 */
void print_extra(const char* format, ...) {
  va_list args;
  va_start(args, format);
  
  if (colors_supported()) {
    printf("%s", get_color_code(COLOR_WHITE, 0));
    vprintf(format, args);
    printf("%s", RESET);
  } else {
    vprintf(format, args);
  }

  va_end(args);
}

/**
 * @brief Prints a cell to the standard output.
 * * This function a unicode block character to the standard output.
 * Refer to `print_shaded_cell()` for a shaded variant.
 * * @param cell_type A value of type `cell_t`. Defines the type of the cell.
 * @param cell_alignment A value of type `alig_t`. Defines the alignment of the
 * cell in a cell (?).
 */
void print_cell(cell_t cell_type, alig_t cell_alignment) {
  switch (cell_type) {
    case FOURTH:
      switch (cell_alignment) {
        case BL:
          printf(CELL_F_BL);
          break;
        case BR:
          printf(CELL_F_BR);
          break;
        case TL:
          printf(CELL_F_TL);
          break;
        case TR:
          printf(CELL_F_TR);
          break;
        default:
          printf(CELL_F_BL);
          break;
      }
      break;
    case THREE:
      switch (cell_alignment) {
        case BL:
          printf(CELL_T_BL);
          break;
        case BR:
          printf(CELL_T_BR);
          break;
        case TL:
          printf(CELL_T_TL);
          break;
        case TR:
          printf(CELL_T_TR);
          break;
        default:
          printf(CELL_T_BL);
          break;
      }
      break;
    case HALF:
      switch (cell_alignment) {
        case BOTTOM:
          printf(CELL_H_B);
          break;
        case TOP:
          printf(CELL_H_T);
          break;
        case LEFT:
          printf(CELL_H_L);
          break;
        case RIGHT:
          printf(CELL_H_R);
          break;
        default:
          printf(CELL_H_B);
          break;
      }
      break;
    case FULL:
      printf(CELL_FULL);
      break;
    default:
      printf(CELL_FULL);
      break;
  }
}

/**
 * @brief Prints a shaded cell to the standard output.
 * * This function prints a shaded full-width unicode character to the standard output.
 * * @param strength Can be a number between `0` and `12` (inclusive). Determines the
 * shade of the cell. `0` is transparent.
 */
void print_shaded_cell(int strength) {
  switch (strength) {
    case 0:
      printf(CELL_EMPTY);
      break;
    case 1:
      print_colored(COLOR_BLACK, 0, CELL_LIGHT);
      break;
    case 2:
      print_colored(COLOR_BLACK, 0, CELL_MEDIUM);
      break;
    case 3:
      print_colored(COLOR_BLACK, 0, CELL_DARK);
      break;
    case 4:
      print_colored(COLOR_BLACK, 0, CELL_FULL);
      break;
    case 5:
      print_colored(COLOR_WHITE, 0, CELL_LIGHT);
      break;
    case 6:
      print_colored(COLOR_WHITE, 0, CELL_MEDIUM);
      break;
    case 7:
      print_colored(COLOR_WHITE, 0, CELL_DARK);
      break;
    case 8:
      print_colored(COLOR_WHITE, 0, CELL_FULL);
      break;
    case 9:
      printf(CELL_LIGHT);
      break;
    case 10:
      printf(CELL_MEDIUM);
      break;
    case 11:
      printf(CELL_DARK);
      break;
    case 12:
      printf(CELL_FULL);
      break;
    default:
      printf(CELL_FULL);
      break;
  }
}

