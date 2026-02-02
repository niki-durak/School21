
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e_flag;
  int i_flag;
  int v_flag;
  int c_flag;
  int l_flag;
  int n_flag;
  int h_flag;
  int s_flag;
  int f_flag;
  int o_flag;
  int totalFiles;
  int lineCount;
  int matchCount;
} grep_options;

int parse_arguments(int argc, char **argv, grep_options *opts, char **pattern);
void process_file(char *filepath, grep_options opts, char *pattern);
void handle_option_f(grep_options *opts, char **pattern, char *optarg);
void handle_option_e(grep_options *opts, char **pattern, char *optarg);
void display_summary(grep_options opts, char *filepath);
void display_matched_line(char *line, grep_options *opts, char *pattern,
                          char *filepath);
void display_option_o(regex_t regex, char *line, grep_options opts);
void adjust_options(grep_options *opts, int argc);
int create_pattern(char **pattern, char *optarg);
void append_pattern(char **pattern, char *optarg);
void *resize_string(void *str, int size);
