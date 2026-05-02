#include <stdio.h>
int main()
{
    char input[100];
    printf("请输入任意内容：");
    fgets(input, sizeof(input), stdin);
    printf("你从键盘输入的内容是这个哦：%s", input);
    return 0;
}