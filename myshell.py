import os
import sys

workspace = os.getcwd()
whoami = os.popen("whoami").read().replace("\n", "").split('\\')[-1]
print('Welcome to myshell!')

help_dict = {
    'cd <directory>': 'cd <目录>—将当前的默认目录修改为<目录>。如果<目录>参数不存在，则报告当前目录。如果目录不存在，则应该报告适当的错误。这个命令还应该更改PWD环境变量。',
    'clr': '清空控制台。',
    'dir <directory>': '列出目录 <directory> 的内容，包含文件和文件夹。',
    'environ': '列出所有环境字符串。',
    'echo <comment>': '在屏幕上显示 <comment> ，后面跟着一个新行(多个空格/制表符可以减少到一个空格)。',
    'help': '显示所有的命令。',
    'pause': '暂停shell的操作，这个时候无法进行其他的操作，直到按下\'Enter\'。',
    'quit': '退出Shell。关闭当前程序。'
}

while True:
    command = input(whoami + ' ' + workspace.split('\\')[-1] + '>').split()
    gt = len(command)
    fpout = None
    for i in range(len(command)):
        if command[i] == '>' and i+1 < len(command):
            gt = i
            fpout = open(command[i+1], 'w')
            sys.stdout = fpout
    if len(command) == 0:
        continue
    if command[0] == 'exit' or command[0] == 'quit':
        break
    elif command[0] == 'pwd':
        print(workspace)
    elif command[0] == 'dir' or command[0] == 'ls':
        for i in os.listdir():
            print(i)
    elif command[0] == 'cd':
        os.chdir(command[1])
        workspace = os.getcwd()
    elif command[0] == 'echo':
        print(' '.join(command[1:gt]))
    elif command[0] == 'env' or command[0] == 'environ':
        for k, v in os.environ.items():
            print(f'{k}={v}')
    elif command[0] == 'whoami':
        print(whoami)
    elif command[0] == 'cls' or command[0] == 'clear' or command[0] == 'clr':
        os.system('cls||clear')
    elif command[0] == 'pause':
        os.system('pause')
    elif command[0] == 'help':
        for k, v in help_dict.items():
            print(f'{k} {v}')
    elif command[0] == 'cat':
        fp = open(command[1], 'r')
        print(fp.read())
        fp.close()
    else:
        print('Command not found!')

    sys.stdout = sys.__stdout__
    if fpout is not None:
        fpout.close()

print('Bye!')
