#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { BYTES = 0, CHARS, LINES, WORDS, ERROR } FLAG_TYPE;

FILE *open_file(const char *filename, const char *mod) {
  FILE *file = fopen(filename, mod);
  if (file == NULL) {
    perror("error: failed to open file\n");
    return NULL;
  }
  return file;
}

int get_char_counts(const char *filename) {
  FILE *file = open_file(filename, "r");

  int c;
  int char_count = 0;
  while ((c = fgetc(file)) != EOF) {
    char_count++;
  }

  if (feof(file)) {
    fclose(file);
    return char_count;
  } else {
    fprintf(stderr, "error: failed to read file\n");
    fclose(file);
  }

  return -1;
}

int get_bytes_counts(const char *filename) {
  FILE *file = open_file(filename, "rb");

  int byte;
  int bytes_count = 0;

  while ((byte = fgetc(file)) != EOF)
    bytes_count++;

  if (feof(file)) {
    fclose(file);
    return bytes_count;
  } else {
    fprintf(stderr, "error: failed to read file\n");
    fclose(file);
  }

  return -1;
}

FLAG_TYPE get_typeof_flag(const char *str) {
  FLAG_TYPE flag;

  size_t flags_size = strlen(str);
  if (flags_size == 2) {
    if (str[0] == '-') {
      switch (str[1]) {
      case 'c':
        flag = BYTES;
        break;
      case 'm':
        flag = CHARS;
        break;
      case 'l':
        flag = LINES;
        break;
      case 'w':
        flag = WORDS;
        break;
      default:
        flag = ERROR;
        break;
      }
    }
  } else {
    flag = ERROR;
  }
  return flag;
}

int main(int argc, char *argv[]) {
  assert(argc > 1 && "TODO: implement show help function\n");

  size_t n_argument = argc - 1;

  if (n_argument == 1) {
    assert(false && "TODO: directly print all the datas");
    return -1;
  }

  if (n_argument >= 3) {
    assert(false && "TODO: handle more than 3 arguments");
    return -1;
  }

  const char *flags = argv[1];
  const char *filename = argv[2];

  FLAG_TYPE flag_type = get_typeof_flag(flags);

  if (flag_type != ERROR) {
    printf("args: %s\n", flags);

    switch (flag_type) {
    case BYTES:
      printf("chars: %d\n", get_bytes_counts(filename));
      break;
    case CHARS:
      printf("chars: %d\n", get_char_counts(filename));
      break;
    case LINES:
      assert(false && "TODO: implement lines count");
      break;
    case WORDS:
      assert(false && "TODO: implement words count");
      break;
    case ERROR:
      assert(false && "TODO: implement error handaling");
      break;
    }
  } else {
    fprintf(stderr, "error: invalid argument type\n");
  }

  return 0;
}
