// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void to_lowercase(char *str);

void trim(char *str) {
    if (!str) return;
    char *p = str;
    // 去掉前导空白
    while (isspace((unsigned char)*p)) p++;
    if (p != str) {
        memmove(str, p, strlen(p) + 1);
    }
    // 去掉尾部空白
    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};

  while (fgets(line, sizeof(line), file)) {
    // 去掉换行符
    line[strcspn(line, "\n")] = '\0';

    if (line[0] == '#') {
      // 先处理上一个条目
      if (strlen(current_word) > 0 && strlen(current_translation) > 0) {
        to_lowercase(current_word);
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
      }
      // 新单词：#word -> word
      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_translation[0] = '\0';
    } else if (strncmp(line, "Trans:", 6) == 0) {
      // 翻译行：Trans:xxx -> xxx
      const char *trans = line + 6;
      if (strlen(current_translation) > 0) {
        strncat(current_translation, " ", sizeof(current_translation) - strlen(current_translation) - 1);
      }
      strncat(current_translation, trans, sizeof(current_translation) - strlen(current_translation) - 1);
    }
  }

  // 处理最后一个条目
  if (strlen(current_word) > 0 && strlen(current_translation) > 0) {
    to_lowercase(current_word);
    hash_table_insert(table, current_word, current_translation);
    (*dict_count)++;
  }

  fclose(file);
  return 0;
}
