#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    // 找到第一个分隔符后的 old 字符串起始位置
    const char* old_start = cmd + 2;
    
    // 找到 old 字符串的结束位置（下一个 '/'）
    const char* old_end = strchr(old_start, '/');
    if (old_end == NULL) {
        return -1;
    }
    
    // 计算 old 字符串长度
    int old_len = old_end - old_start;
    
    // 分配内存并复制 old 字符串
    *old_str = (char*)malloc(old_len + 1);
    if (*old_str == NULL) {
        return -1;
    }
    strncpy(*old_str, old_start, old_len);
    (*old_str)[old_len] = '\0';
    
    // new 字符串起始位置
    const char* new_start = old_end + 1;
    
    // 找到 new 字符串的结束位置（最后一个 '/'）
    const char* new_end = strchr(new_start, '/');
    if (new_end == NULL) {
        free(*old_str);
        *old_str = NULL;
        return -1;
    }
    
    // 计算 new 字符串长度
    int new_len = new_end - new_start;
    
    // 分配内存并复制 new 字符串
    *new_str = (char*)malloc(new_len + 1);
    if (*new_str == NULL) {
        free(*old_str);
        *old_str = NULL;
        return -1;
    }
    strncpy(*new_str, new_start, new_len);
    (*new_str)[new_len] = '\0';
    
    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // 查找第一次出现的位置
    char* pos = strstr(str, old);
    if (pos == NULL) {
        return;  // 没找到，不做替换
    }
    
    // 计算替换后的字符串长度
    int old_len = strlen(old);
    int new_len = strlen(new);
    int str_len = strlen(str);
    
    // 如果新旧字符串长度不同，需要移动字符串内容
    if (new_len != old_len) {
        memmove(pos + new_len, pos + old_len, str_len - (pos - str) - old_len + 1);
    }
    
    // 复制新字符串
    memcpy(pos, new, new_len);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }
    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}