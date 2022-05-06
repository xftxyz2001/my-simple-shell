#include "myshell.h"

int main(int argc, char *argv[])
{
    // 变量声明
    char environ_[2][BUFFER_LEN] = {0}; // 环境变量
    char pwd[BUFFER_LEN] = {0};         // 目录
    char myshell[BUFFER_LEN] = {0};

    char buffer[BUFFER_LEN] = {0};             // 输入缓冲区
    char command[BUFFER_LEN] = {0};            // 命令
    char tokens[MAX_TOKENS][BUFFER_LEN] = {0}; // 分词结果
    int token_count = 0;                       // 分词结果条数

    // 流
    FILE *xf_fpin = NULL;  // 输入源
    FILE *xf_fpout = NULL; // 输出源
    int out_flags = 0;

    // 3. shell必须能够从文件中获取命令行输入。也就是说，如果使用命令行参数调用shell:
    // myshell batchfile
    // 然后，假设batchfile包含一组shell要处理的命令行。
    // 当到达文件结束符时，shell应该退出。
    // 显然，如果在没有命令行参数的情况下调用shell，它将通过显示提示符向用户请求输入。

    // 解析使用argc和argv提供的命令，获取输入
    if (argc > 1) // argc>1说明传入了batchfile
    {
        xf_fpin = fopen(argv[1], "r");
        if (xf_fpin == NULL)
        {
            fprintf(xf_fpout, "Error opening batch file...\n");
            return 1;
        }
    }
    else
    {
        xf_fpin = stdin;
    }

    xf_fpout = stdout;

    // 显示相关信息
    fprintf(xf_fpout, "------------------------------------------------------------\nWelcome to the shell!, type help to discover more commands\n\n");

    // 获取环境变量
    get_currentDir(pwd);
    get_currentDir(myshell);

    // 加载environ_数组
    strcpy(environ_[0], "PWD: ");
    strcat(environ_[0], pwd);

    // shell环境应该包含shell=/myshell
    // 其中/myshell是shell可执行文件的完整路径(不是回您的目录的硬连接路径，而是从它被执行的路径)。
    strcpy(environ_[1], "MYSHELL: ");
    strcat(environ_[1], myshell);

    // 6. 命令行提示符必须包含当前目录的路径名。
    fprintf(xf_fpout, "%s> ", pwd);

    // 执行一个无限循环从用户获取命令输入，存放到buffer中
    while (fgets(buffer, BUFFER_LEN, xf_fpin) != NULL)
    {
        // printf("--%s", buffer);
        // 获取一行指令并将结尾的换行替换为字符串终止标记
        int index = 0;
        while (buffer[index] != '\n')
        {
            index++;
        }
        buffer[index] = '\0';

        // DEBUG
        // printf("%s\n", "字符串终止标记...");
        // printf("%s\n", buffer);

        // DEBUG
        // printf("%s\n", "输出源设置完毕...");

        // 执行字符串标记化以获得命令tokens[0]和参数tokens[1:token_count]
        token_count = string_tokenizer(buffer, tokens);
        strcpy(command, tokens[0]);

        for (int i = 0; i < token_count; i++)
        {
            if (strcmp(tokens[i], ">") == 0 && i + 1 < token_count)
            {
                // 将输出源设置为文件
                xf_fpout = fopen(tokens[i + 1], "w");
                out_flags = 1;
                if (xf_fpout == NULL)
                {
                    fprintf(xf_fpout, "Error opening file...\n");
                    return 1;
                }
            }
        }

        // DEBUG
        // printf("%s\n", "字符串标记化完毕...");

        // 检查该命令是什么并执行该命令的对应操作

        // cd <目录>：将当前的默认目录修改为<目录>。
        if (strcmp(command, "cd") == 0)
        {
            // 如果<目录>参数不存在，则报告当前目录。如果目录不存在，则应该报告适当的错误。
            // 这个命令还应该更改PWD环境变量。
            // 详见change_dir实现
            change_dir(xf_fpout, pwd, tokens[1]);
            strcpy(environ_[0], "PWD: ");
            strcat(environ_[0], pwd);
        }

        // clr：清空控制台
        else if (strcmp(command, "clr") == 0 || strcmp(command, "clear") == 0 || strcmp(command, "cls") == 0)
        {
            clear_screen();
        }

        // dir <directory>：列出目录 <directory> 的内容
        else if (strcmp(command, "dir") == 0 || strcmp(command, "ls") == 0)
        {
            //     // 如果<目录>参数不存在，则报告当前目录。如果目录不存在，则应该报告适当的错误。
            //     // 详见list_dir实现
            //     list_dir(xf_fpout, tokens[1]);
            display_dir(xf_fpout, tokens[1]);
            // fprintf(xf_fpout, "\n");
        }

        // environ：列出所有环境字符串。
        else if (strcmp(command, "environ") == 0 || strcmp(command, "env") == 0)
        {
            display_environs(xf_fpout, environ_);
        }

        // echo <comment>：在屏幕上显示 <comment>，后面跟着一个新行(多个空格/制表符可以减少到一个空格)。
        else if (strcmp(command, "echo") == 0)
        {
            // fprintf(xf_fpout, "%s> ", pwd);
            for (int i = 1; i < token_count; i++)
            {
                if (strcmp(tokens[i], ">") == 0)
                {
                    // tokens[i] 是 >
                    i++;
                    // tokens[i] 是重定向输出的文件名
                    continue;
                    // for循环再++指向下一个参数
                }

                fprintf(xf_fpout, "%s ", tokens[i]);
            }
            fprintf(xf_fpout, "\n");
        }

        // help：显示所有可用命令的帮助信息。
        else if (strcmp(command, "help") == 0)
        {
            display_help(xf_fpout);
        }

        // pause：暂停shell的操作，直到按下'Enter'。
        else if (strcmp(command, "pause") == 0)
        {
            pause_shell(xf_fpout);
        }

        // quit：退出 shell
        else if (strcmp(tokens[0], "quit") == 0 || strcmp(tokens[0], "exit") == 0)
        {
            fprintf(xf_fpout, "Bye!\n");
            return 0;
        }

        // 不支持的命令
        else
        {
            fprintf(xf_fpout, "%s> ", pwd);
            fprintf(xf_fpout, "Unsupported command, use help to display the manual\n");
        }

        // 清空buffer、tokens、command供下次输入
        memset(buffer, 0, sizeof(buffer));
        memset(command, 0, sizeof(command));
        for (int i = 0; i < MAX_TOKENS; i++)
        {
            memset(tokens[i], 0, sizeof(tokens[i]));
        }

        if (out_flags)
        {
            // 关闭输出文件
            fclose(xf_fpout);
            out_flags = 0;
        }

        // 重置输出源
        xf_fpout = stdout;

        // 显示相关信息
        fprintf(xf_fpout, "%s> ", pwd);
    }
    return 0;
}
