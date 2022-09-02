#include <stdio.h>
#include <string.h>
//系统函数
#include <stdlib.h>
#include <ctype.h>

/*声明变量*/
char ch = '0';
char filename[256] = "";
FILE *fp =NULL;
FILE *fptemp = NULL;
char password[12] = "123456";
const char tempfile[256] = "temp123456.temp";
int pwdlen = 0;
int i = 0;

/*封装函数*/
void mean();
void inputpass(char *pass);

/*函数实现*/
void inputpass(char *pass)
{
    scanf("%s",pass);
};

void mean ()
{
    printf("*******************************************\n");
    printf("*******************安全********************\n");
    printf("*******************************************\n");
    printf("**输入要加密文件的路径**\n");
    printf("**例如：/user/test/test.txt**\n");

    /*一、打开一个文件夹或目录*/
    gets(filename);
    if(NULL == (fp = fopen(filename,"rb")))
    {
        printf("文件不存在\n");
        exit(1);
    };
    printf("文件存在，输入密码\n");
    inputpass(password);
    pwdlen = (int)strlen(password);
    if(0 == pwdlen)
    {
        printf("密码长度不能为0\n");
        exit(2);
    };

    /*二、读出文件中的内容进行加密*/
    fptemp = fopen(tempfile,"wb");
    /*三、将加密的信息写入数据中覆盖原来的数据*/
    while(1)
    {
        ch = getc(fp);
        if(feof(fp))
        {
            break;
        }
        /*每取出一个字符就加密*/
        ch^=password[i++];
        fputc(ch,fptemp);
        if(i == pwdlen)
        {
            i = 0;
        }
    }
    fclose(fp);
    fclose(fptemp);
    remove(filename);
    rename(tempfile,filename);
    printf("加密或解密成功");
};
/*主函数 程序入口地址*/
int main(int argc, char const*argv[])
{
    mean();
    /*函数地址*/
    return 0;
};