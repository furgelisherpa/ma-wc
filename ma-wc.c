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

int get_chars_count(const char *filename) {
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

int get_bytes_count(const char *filename) {
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

int get_lines_count(const char *filename) {
  FILE *file = open_file(filename, "rb");

  int lines_count = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (c == 10)
      lines_count++;
  }

  if (feof(file)) {
    fclose(file);
    return lines_count;
  } else {
    fprintf(stderr, "error: failed to read file\n");
    fclose(file);
  }

  return -1;
}

int get_words_count(const char *filename) {
  FILE *file = open_file(filename, "r");

  int words_count = 0;
  int c;
  bool in_word = true;
  while ((c = fgetc(file)) != EOF) {
    /* i.e space, newline, tabs */
    if (c == 32 || c == 10 || c == 9) {
      if (in_word) {
        words_count++;
        in_word = false;
      }
    } else {
      in_word = true;
    }
  }

  if (in_word) {
    words_count++;
  }

  if (feof(file)) {
    fclose(file);
    return words_count;
  } else {
    fprintf(stderr, "error: failed to read file\n");
    fclose(file);
  }
  return -1;
}

FLAG_TYPE typeof_flag(const char c) {
  FLAG_TYPE flag_type;

  switch (c) {
  case 'c':
    flag_type = BYTES;
    break;
  case 'm':
    flag_type = CHARS;
    break;
  case 'l':
    flag_type = LINES;
    break;
  case 'w':
    flag_type = WORDS;
    break;
  default:
    flag_type = ERROR;
    break;
  }

  return flag_type;
}

FLAG_TYPE get_flag(const char *str) {
  size_t flags_size = strlen(str);
  if (flags_size == 2) {
    if (str[0] == '-') {
      return typeof_flag(str[1]);
    }
  }

  return ERROR;
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

  FLAG_TYPE flag_type = get_flag(flags);

  if (flag_type != ERROR) {
    printf("args: %s\n", flags);

    switch (flag_type) {
    case BYTES:
      printf("bytes: %d\n", get_bytes_count(filename));
      break;
    case CHARS:
      printf("chars: %d\n", get_chars_count(filename));
      break;
    case LINES:
      printf("lines: %d\n", get_lines_count(filename));
      break;
    case WORDS:
      printf("words: %d\n", get_words_count(filename));
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
