// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
  char *start = str;
  char *end;

  // 跳过前导空格
  while (*start && isspace(*start)) start++;

  if (*start == 0) {
    *str = 0;
    return;
  }

  // 找到末尾
  end = start + strlen(start) - 1;
  while (end > start && isspace(*end)) end--;

  // 移动字符串
  memmove(str, start, end - start + 2);
  str[end - start + 1] = 0;
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
    trim(line);

    if (line[0] == '#') {
      // 新词条开始
      if (current_word[0] != '\0' && current_translation[0] != '\0') {
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
      }
      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_word[sizeof(current_word) - 1] = '\0';
      current_translation[0] = '\0';
    } else if (line[0] != '\0') {
      // 翻译内容（可能多行）
      if (current_translation[0] != '\0') {
        strncat(current_translation, " ", sizeof(current_translation) - strlen(current_translation) - 1);
      }
      strncat(current_translation, line, sizeof(current_translation) - strlen(current_translation) - 1);
    }
  }

  // 处理最后一个词条
  if (current_word[0] != '\0' && current_translation[0] != '\0') {
    hash_table_insert(table, current_word, current_translation);
    (*dict_count)++;
  }

  fclose(file);
  return 0;
}

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

int __cmd_mytrans(const char* filename) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  
  // 构建词典路径：相对于可执行文件的位置
  char dict_path[1024] = {0};
  char *exe_path = getenv("PWD");
  if (exe_path) {
    snprintf(dict_path, sizeof(dict_path), "%s/src/mytrans/dict.txt", exe_path);
  } else {
    strcpy(dict_path, "src/mytrans/dict.txt");
  }
  
  if (load_dictionary(dict_path, table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 %s。\n", filename);
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        continue;
    }

    // 使用 strtok 按空格分割单词
    char *word = strtok(line, " ");
    while (word != NULL) {
      const char *translation = hash_table_lookup(table, word);
      printf("原文: %s\t", word);
      if (translation) {
          printf("翻译: %s\n", translation);
      } else {
          printf("未找到该单词的翻译。\n");
      }

      word = strtok(NULL, " ");
    }
  }

  fclose(file);
  free_hash_table(table);
  return 0;
}
