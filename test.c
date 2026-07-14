#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数声明
void unsafe_copy(char *dest, const char *src);
int divide(int a, int b);
void memory_leak_example(void);

int main(void) {
    char buffer[10];
    // 1. 潜在缓冲区溢出：源字符串长度超过目标缓冲区大小
    unsafe_copy(buffer, "This is a very long string that will overflow the buffer");

    // 2. 除零错误：b可能为0
    int result = divide(10, 0);
    printf("Result: %d\n", result);

    // 3. 内存泄漏：分配内存后未释放
    memory_leak_example();

    // 4. 使用未初始化的变量
    int uninitialized_var;
    printf("Uninitialized value: %d\n", uninitialized_var);

    // 5. 悬空指针
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    *ptr = 100; // 使用已释放的内存

    return 0;
}

// 不安全的字符串拷贝，没有边界检查
void unsafe_copy(char *dest, const char *src) {
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

// 未检查除数是否为零
int divide(int a, int b) {
    return a / b;
}

// 分配内存后忘记释放
void memory_leak_example(void) {
    char *leak = (char *)malloc(100);
    strcpy(leak, "This memory will never be freed");
    // 缺少 free(leak);
}