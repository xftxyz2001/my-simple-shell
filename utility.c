#include "myshell.h"

// 字符串分词
extern int string_tokenizer(char *str, char tokens[][BUFFER_LEN])
{
    const char delimiter[2] = " ";
    int tokens_count = 0;
    char *token = strtok(str, delimiter);
    while (token != NULL)
    {
        strcpy(tokens[tokens_count], token);
        tokens_count++;
        token = strtok(NULL, delimiter);
    }
    return tokens_count;
    // const char delimiter[2] = " ";
    // const char *split = " ";
    // int tokens_count = 0;
    // char *p;
    // p = strtok(str, split);
    // while (p != NULL)
    // {
    //     printf("%s\n", p);
    //     p = strtok(NULL, split);
    // }
    // char *token = NULL;
    // while ((token = strtok(str, delimiter)) != NULL)
    // {
    //     // DEBUG
    //     printf("token: %s\n", token);

    //     strcpy(tokens[tokens_count++], token);
    //     printf("%s\n", str);
    //     str++;
    // }
    // return tokens_count;
}

// 返回当前目录
extern void get_currentDir(char *pwd)
{
    getcwd(pwd, BUFFER_LEN);
}

// 改变当前目录
extern void change_dir(FILE *xf_fpout, char *pwd, char *path)
{
    int changed = chdir(path);
    if (strcmp(path, "") != 0)
    {
        if (changed == 0)
        {
            get_currentDir(pwd);
        }
        else
        {
            fprintf(xf_fpout, "%s> No such path exists!\n", pwd);
        }
    }
}

// 清空控制台
extern void clear_screen(void)
{
    system("cls||clear");
}

// 暂停
extern void pause_shell(FILE *xf_fpout)
{
    // Pause operation of the shell until 'Enter' is pressed
    fprintf(xf_fpout, "\n\nShell is now paused. Please press ENTER key to continue....\n\n");
    char code = (char)getchar();
    while ((code = (char)getchar()) != '\n')
        ;
}

// 显示目录
extern void display_dir(FILE *xf_fpout, char *path)
{
    struct dirent *de;
    DIR *dr = NULL;
    if (strcmp(path, "") == 0)
    {
        dr = opendir(".");
    }
    else
    {
        dr = opendir(path);
    }
    if (dr == NULL)
    {
        fprintf(xf_fpout, "Could not find the directory specified!\n");
    }
    while ((de = readdir(dr)) != NULL)
    {
        fprintf(xf_fpout, "%s\n", de->d_name);
    }
    closedir(dr);
}

// 显示环境变量
extern void display_environs(FILE *xf_fpout, char env[][BUFFER_LEN])
{
    fprintf(xf_fpout, "%s\n%s\n", env[0], env[1]);
}

// 显示帮助
extern void display_help(FILE *xf_fpout)
{
    fprintf(xf_fpout, "\nList of available commands:\n\n");
    fprintf(xf_fpout, "help - Lists the help menu.\n");
    fprintf(xf_fpout, "cd <directory> - Change the current default directory to <directory>. If the <directory> argument is not present, report the current directory. If the directory does not exist an appropriate error should be reported. This command should also change the PWD environment variable.\n");
    fprintf(xf_fpout, "clr - Clear the screen.\n");
    fprintf(xf_fpout, "dir <directory> - List the contents of directory <directory>.\n");
    fprintf(xf_fpout, "environ - List all the environment strings.\n");
    fprintf(xf_fpout, "echo <comment> - Display <comment> on the display followed by a new line (multiple spaces/tabs may be reduced to a single space).\n");
    fprintf(xf_fpout, "pause - Pause operation of the shell until 'Enter' is pressed.\n");
    fprintf(xf_fpout, "quit - Quit the shell.\n");
    // if (xf_fpout != NULL)
    // {
    //     // 关闭输出文件
    //     fclose(xf_fpout);
    // }
}
