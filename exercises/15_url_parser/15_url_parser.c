#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 * 格式：key = xxx, value = xxx
 */

int parse_url(const char* url) {
    int err = 0;
    
    // 查找问号的位置
    const char *question_mark = strchr(url, '?');
    if (question_mark == NULL) {
        printf("No parameters found in the URL\n");
        goto exit;
    }
    
    // 指向查询字符串的开始
    const char *p = question_mark + 1;
    
    // 手动解析参数
    while (*p != '\0') {
        // 提取 key
        char key[256];
        int key_len = 0;
        while (*p != '\0' && *p != '=' && *p != '&') {
            key[key_len++] = *p++;
        }
        key[key_len] = '\0';
        
        // 跳过等号
        char value[256] = "";
        if (*p == '=') {
            p++; // 跳过等号
            // 提取 value
            int value_len = 0;
            while (*p != '\0' && *p != '&') {
                value[value_len++] = *p++;
            }
            value[value_len] = '\0';
        }
        
        // 输出
        printf("key = %s, value = %s\n", key, value);
        
        // 跳过 & 符号
        if (*p == '&') {
            p++;
        }
    }

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";
    
    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");
    
    parse_url(test_url);
    
    return 0;
}