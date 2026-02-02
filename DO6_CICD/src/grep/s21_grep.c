#include "s21_grep.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    char *pattern = NULL;
    grep_options opts = {0};

    for (int x = parse_arguments(argc, argv, &opts, &pattern); x < argc; x++)
      process_file(argv[x], opts, pattern);

    if (pattern != NULL) free(pattern);
  }
  return 0;
}

int parse_arguments(int argc, char **argv, grep_options *opts, char **pattern) {
  for (int opt = 0; (opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1;) {
    switch (opt) {
      case 'i':
        opts->i_flag = 1;
        break;
      case 'v':
        opts->v_flag = 1;
        break;
      case 'c':
        opts->c_flag = 1;
        break;
      case 'l':
        opts->l_flag = 1;
        break;
      case 'n':
        opts->n_flag = 1;
        break;
      case 'h':
        opts->h_flag = 1;
        break;
      case 's':
        opts->s_flag = 1;
        break;
      case 'o':
        opts->o_flag = 1;
        break;
      case 'e':
        handle_option_e(opts, pattern, optarg);
        break;
      case 'f':
        handle_option_f(opts, pattern, optarg);
        break;
    }
  }
  if ((opts->e_flag || opts->f_flag) == 0) {
    create_pattern(pattern, argv[optind]);
    optind++;
  }
  adjust_options(opts, argc);
  return optind;
}

void process_file(char *filepath, grep_options opts, char *pattern) {
  FILE *file = fopen(filepath, "r");
  if (file != NULL) {
    for (char ch = '0'; (ch = getc(file)) != EOF;) {
      char *line = calloc(256, 1);
      opts.lineCount++;

      int len = 0;
      for (line[len] = '\0'; ch != EOF && ch != '\n'; ch = getc(file)) {
        line[len] = ch;
        line[len += 1] = '\0';
        if (len % 255 == 0) line = resize_string(line, len + 256);
      }

      display_matched_line(line, &opts, pattern, filepath);
      free(line);
    }
    display_summary(opts, filepath);
    fclose(file);
  }
}

void handle_option_f(grep_options *opts, char **pattern, char *optarg) {
  FILE *file = fopen(optarg, "r");
  if (file != NULL) {
    for (char ch = '0'; (ch = getc(file)) != EOF;) {
      int len = 0;
      char *line = calloc(256, 1);

      for (line[len] = '\0'; ch != EOF && ch != '\n'; ch = getc(file)) {
        line[len] = ch;
        line[len += 1] = '\0';
        if (len % 255 == 0) line = (char *)resize_string(line, len + 256);
      }

      if (!(opts->e_flag || opts->f_flag))
        opts->f_flag = create_pattern(pattern, line);
      else
        append_pattern(pattern, line);
      free(line);
    }
    fclose(file);
  }
}

void handle_option_e(grep_options *opts, char **pattern, char *optarg) {
  if (!(opts->e_flag || opts->f_flag))
    opts->e_flag = create_pattern(pattern, optarg);
  else
    append_pattern(pattern, optarg);
}

void display_summary(grep_options opts, char *filepath) {
  if (opts.c_flag) {
    if (opts.l_flag) {
      opts.totalFiles > 1 ? printf("%s:1\n", filepath) : printf("1\n");
    } else {
      if (opts.totalFiles > 1) printf("%s:", filepath);
      printf("%i\n", opts.matchCount);
    }
  }
  if (opts.l_flag && opts.matchCount) printf("%s\n", filepath);
}

void display_matched_line(char *line, grep_options *opts, char *pattern,
                          char *filepath) {
  regex_t regex;
  if (regcomp(&regex, pattern, opts->i_flag ? REG_ICASE : REG_EXTENDED) == 0) {
    if (regexec(&regex, line, 0, NULL, 0) == opts->v_flag) {
      opts->matchCount++;
      if ((opts->c_flag || opts->l_flag) == 0) {
        if (opts->totalFiles > 1 && !(opts->h_flag)) printf("%s:", filepath);
        if (opts->n_flag) printf("%i:", opts->lineCount);
        if (!opts->o_flag)
          printf("%s\n", line);
        else
          display_option_o(regex, line, *opts);
      }
    }
    regfree(&regex);
  }
}

void display_option_o(regex_t regex, char *line, grep_options opts) {
  while (regexec(&regex, line, 0, NULL, 0) == opts.v_flag) {
    char *temp = (char *)calloc(strlen(line) + 1, 1);
    strcpy(temp, line);
    int end = strlen(line);
    while (regexec(&regex, temp, 0, NULL, 0) == opts.v_flag) {
      end--;
      temp[strlen(temp) - 1] = 0;
    }
    temp[strlen(temp)] = line[strlen(temp)];
    int start = 0;
    while (regexec(&regex, temp, 0, NULL, 0) == opts.v_flag &&
           strlen(temp) > 0) {
      start++;
      int j = 0;
      while (temp[j] != 0) {
        temp[j] = temp[j + 1];
        j++;
      }
    }
    start--;
    int i = strlen(temp);
    while (i != 0) {
      temp[i] = temp[i - 1];
      i--;
    }
    temp[0] = line[start];
    printf("%s\n", temp);
    free(temp);
    i = start + 1;
    while (line[i] != 0) {
      line[i - start - 1] = line[i];
      i++;
    }
    line[i - start - 1] = 0;
  }
}

void adjust_options(grep_options *opts, int argc) {
  if (opts->o_flag && (opts->l_flag || opts->v_flag || opts->c_flag))
    opts->o_flag = 0;
  opts->totalFiles = argc - optind;
}

int create_pattern(char **pattern, char *optarg) {
  *pattern = calloc(strlen(optarg) + 1, 1);
  if (*pattern) strcpy(*pattern, optarg);
  return pattern ? 1 : 0;
}

void append_pattern(char **pattern, char *optarg) {
  *pattern = resize_string(*pattern, strlen(*pattern) + strlen(optarg) + 2);
  if (*pattern) strcat(strcat(*pattern, "|"), optarg);
}

void *resize_string(void *str, int size) {
  char *temp = realloc(str, size);
  return temp;
}