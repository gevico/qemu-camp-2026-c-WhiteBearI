#include "mysed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    // 检查输入参数有效性
    if (!cmd || !old_str || !new_str) {
        return -1;
    }
    
    // 初始化输出参数
    *old_str = NULL;
    *new_str = NULL;
    
    // 检查格式是否为 s/old/new/
    if (cmd[0] != 's') return -1;
    if (cmd[1] != '/') return -1;
    
    char *p = (char *)(cmd + 2);
    char *first_slash = strchr(p, '/');
    if (!first_slash) return -1;
    
    *old_str = strndup(p, first_slash - p);
    
    char *second_slash = strchr(first_slash + 1, '/');
    if (!second_slash) {
      free(*old_str);
      *old_str = NULL;
      return -1;
    }
    
    *new_str = strndup(first_slash + 1, second_slash - first_slash - 1);
    
    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // 检查输入参数有效性
    if (!str || !old || !new) {
        return;
    }
    
    char *pos = strstr(str, old);
    if (!pos) return;
    
    char temp[1024];
    int offset = pos - str;
    
    // 复制替换点之前的部分
    strncpy(temp, str, offset);
    temp[offset] = '\0';
    
    // 添加新字符串
    strcat(temp, new);
    
    // 添加替换点之后的部分
    strcat(temp, pos + strlen(old));
    
    // 复制回原字符串
    strcpy(str, temp);
}

int __cmd_mysed(const char* rules, const char* str) {
    // 检查输入参数有效性
    if (!rules || !str) {
        fprintf(stderr, "Error: NULL rules or str parameter\n");
        return 1;
    }

    printf("rules: %s\n", rules);
    printf("str: %s\n", str);

    char* old_str = NULL;
    char* new_str = NULL;

    // 解析规则，例如 "s/old/new/"
    if (parse_replace_command(rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    if (!old_str || !new_str) {
        fprintf(stderr, "Error: Failed to parse old/new strings from rules\n");
        free(old_str);
        free(new_str);
        return 1;
    }

    // 复制原始字符串，因为我们可能会修改它（避免修改输入参数）
    char line[1024];
    strncpy(line, str, sizeof(line) - 1);
    line[sizeof(line) - 1] = '\0';  // 确保终止

    // 执行替换：在 line 中把 old_str 替换为 new_str（第一次出现）
    replace_first_occurrence(line, old_str, new_str);

    // 输出结果（建议加上换行，除非 str 本身带了）
    printf("%s\n", line);

    // 释放动态分配的内存
    free(old_str);
    free(new_str);

    return 0;
}
