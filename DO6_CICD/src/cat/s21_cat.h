#ifdef S21_CAT_H
#define S21_CAT_H

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

#endif