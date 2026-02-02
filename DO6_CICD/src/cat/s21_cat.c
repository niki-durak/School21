#include "s21_cat.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cat_args {
  int b;
  int t;
  int v;
  int n;
  int s;
  int e;
};

void output(FILE *file, struct cat_args *args);
int parser(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  if (parser(argc, argv) != 0) {
    return 1;
  }
  return 0;
}

int parser(int argc, char *argv[]) {
  struct cat_args local_args = {0};
  FILE *file;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strlen(argv[i]) > 2 && argv[i][1] == '-') {
        if (strcmp(argv[i], "--number-nonblank") == 0) {
          local_args.b = 1;
        } else if (strcmp(argv[i], "--number") == 0) {
          local_args.n = 1;
        } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
          local_args.s = 1;
        } else {
          fprintf(stderr, "Неизвестный флаг: %s\n", argv[i]);
        }
      } else {
        for (int j = 1; argv[i][j] != '\0'; j++) {
          switch (argv[i][j]) {
            case 'b':
              local_args.b = 1;
              break;
            case 't':
              local_args.t = 1;
              break;
            case 'T':
              local_args.t = 1;
              break;
            case 'v':
              local_args.v = 1;
              break;
            case 'n':
              local_args.n = 1;
              break;
            case 's':
              local_args.s = 1;
              break;
            case 'e':
              local_args.e = 1;
              break;
            case 'E':
              local_args.e = 1;
              break;
            default:
              fprintf(stderr, "Неизвестный флаг: %c\n", argv[i][j]);
              break;
          }
        }
      }
    } else {
      file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, "Не удалось открыть файл: %s\n", argv[i]);
        return 1;
      }
      output(file, &local_args);
      fclose(file);
    }
  }

  return 0;
}

void output(FILE *file, struct cat_args *args) {
  int c;
  char prev_sym1 = -1;
  int line_number = 1;
  int flag_empty_line = 1;
  int any_flag_set =
      args->b || args->n || args->e || args->s || args->t || args->v;

  if (!any_flag_set) {
    while ((c = fgetc(file)) != EOF) {
      putchar(c);
    }
  }

  while ((c = fgetc(file)) != EOF) {
    if (args->b == 1) {
      if (line_number == 1 && c != '\n' && prev_sym1 != '\n') {
        printf("     1\t");
        line_number++;
      }
      if (c != '\n' && prev_sym1 == '\n') {
        printf("     %d\t", line_number);
        line_number++;
      }
      printf("%c", c);
      prev_sym1 = c;
    }

    else if (args->n == 1) {
      if (line_number == 1) {
        printf("     1\t%c", c);
        line_number++;
      } else {
        printf("%c", c);
      }
      if (c == '\n') {
        printf("%6d\t", line_number);
        line_number++;
      }
    }
    if (args->e == 1) {
      if (c >= 0 && c <= 31 && (c != 9 && c != 10)) {
        printf("^%c", c + 64);
        continue;
      } else if (c == 127) {
        printf("^%c", c - 64);
        continue;
      } else if (c == '\n') {
        printf("$");
      }
      printf("%c", c);
    }

    if (args->s == 1) {
      if (c == '\n' && prev_sym1 == '\n') {
        if (flag_empty_line == 1) {
          printf("%c", '\n');
          flag_empty_line = 0;
        } else {
          continue;
        }
      } else {
        printf("%c", c);
        flag_empty_line = 1;
      }
      prev_sym1 = c;
    }

    if (args->t == 1) {
      if (c == '\t') {
        printf("^I");
      } else if (c >= 0 && c <= 31 && (c != 9 && c != 10)) {
        printf("^%c", c + 64);
      } else if (c == 127) {
        printf("^%c", c - 64);
      } else {
        printf("%c", c);
      }
    }

    if (args->v == 1) {
      if (c >= 0 && c <= 31 && (c != 9 && c != 10)) {
        printf("^%c", c + 64);
      } else if (c == 127) {
        printf("^%c", c - 64);
      } else {
        printf("%c", c);
      }
    }
  }
}
