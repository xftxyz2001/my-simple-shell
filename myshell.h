#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>

// #include <unistd.h>
#include <io.h>
#include <process.h>

#include "dirent.h"

#include <sys/types.h>
#include <string.h>

// 常量定义
#define BUFFER_LEN 1024
#define MAX_TOKENS 10

// 这里包含会用到的函数的声明

// 字符串分词
extern int string_tokenizer(char *str, char tokens[][BUFFER_LEN]);

// 返回当前目录
extern void get_currentDir(char *pwd);

// 改变当前目录
extern void change_dir(FILE *xf_fpout, char *pwd, char *path);

// 清空控制台
extern void clear_screen(void);

// 暂停
extern void pause_shell(FILE *xf_fpout);

// 显示目录
extern void display_dir(FILE *xf_fpout, char *path);

// 显示环境变量
extern void display_environs(FILE *xf_fpout, char env[][BUFFER_LEN]);

// 显示帮助
extern void display_help(FILE *xf_fpout);

#endif // _MY_SHELL_H_
