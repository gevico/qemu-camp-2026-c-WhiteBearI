#include "mywc.h"

// 创建哈希表
WordCount **wc_create_hash_table() {
  WordCount **hash_table = calloc(HASH_SIZE, sizeof(WordCount *));
  return hash_table;
}

// 简单的哈希函数
unsigned int hash(const char *word) {
  unsigned long hash = 5381;
  int c;
  while ((c = *word++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash % HASH_SIZE;
}

// 检查字符是否构成单词的一部分
bool is_valid_word_char(char c) { return isalpha(c) || c == '\''; }

// 转换为小写
char to_lower(char c) { return tolower(c); }

// 添加单词到哈希表
void add_word(WordCount **hash_table, const char *word) {
  unsigned int index = hash(word);
  WordCount *entry = hash_table[index];

  // 检查单词是否已存在
  while (entry != NULL) {
    if (strcmp(entry->word, word) == 0) {
      entry->count++;
      return;
    }
    entry = entry->next;
  }

  // 单词不存在，创建新节点
  entry = (WordCount *)malloc(sizeof(WordCount));
  if (!entry) return;
  strncpy(entry->word, word, MAX_WORD_LEN - 1);
  entry->word[MAX_WORD_LEN - 1] = '\0';
  entry->count = 1;
  entry->next = hash_table[index];
  hash_table[index] = entry;
}

// 打印单词统计结果
void print_word_counts(WordCount **hash_table) {
  printf("Word Count Statistics:\n");
  printf("======================\n");

  // 收集所有单词和计数
  WordCount **all_entries = malloc(sizeof(WordCount *) * 10000);
  int count = 0;
  
  for (int i = 0; i < HASH_SIZE; i++) {
    WordCount *entry = hash_table[i];
    while (entry != NULL) {
      all_entries[count++] = entry;
      entry = entry->next;
    }
  }

  // 按计数排序（简单冒泡排序）
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (all_entries[j]->count < all_entries[j + 1]->count) {
        WordCount *temp = all_entries[j];
        all_entries[j] = all_entries[j + 1];
        all_entries[j + 1] = temp;
      }
    }
  }

  // 打印前20个最常见的单词
  for (int i = 0; i < count; i++) {
    printf("%-21s%d\n", all_entries[i]->word, all_entries[i]->count);
  }
  
  free(all_entries);
}

// 释放哈希表内存
void wc_free_hash_table(WordCount **hash_table) {
  for (int i = 0; i < HASH_SIZE; i++) {
    WordCount *entry = hash_table[i];
    while (entry != NULL) {
      WordCount *temp = entry;
      entry = entry->next;
      free(temp);
    }
  }
  free(hash_table);
}

// 处理文件并统计单词
void process_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  WordCount **hash_table = wc_create_hash_table();
  char word[MAX_WORD_LEN];
  int word_pos = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (is_valid_word_char(c)) {
      if (word_pos < MAX_WORD_LEN - 1) {
        word[word_pos++] = to_lower(c);
      }
    } else {
      if (word_pos > 0) {
        word[word_pos] = '\0';
        add_word(hash_table, word);
        word_pos = 0;
      }
    }
  }

  // 处理文件末尾的最后一个单词
  if (word_pos > 0) {
    word[word_pos] = '\0';
    add_word(hash_table, word);
  }

  fclose(file);
  print_word_counts(hash_table);
  wc_free_hash_table(hash_table);
}

int __cmd_mywc(const char* filename) {
  process_file(filename);
  return 0;
}