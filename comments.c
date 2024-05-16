#include <stdio.h>

int str = 0;
int ch = 0;
int sc = 0;
int lc = 0;
int len = 0;

int stepcheck(char v, char t)
{
    if ((v == '/') && (t == '*'))
    {
        if ((str != 1) && (sc != 1) && (lc != 1) && (ch != 1))
        {
            lc = 1;
            len = 2;
        }
    }
    else if ((v == '/') && (t == '/'))
    {
        if ((str != 1) && (lc != 1) && (sc != 1) && (ch != 1)) sc = 1;
    }
    else if ((v == '*') && (t == '/'))
    {
        if ((lc) && (len == 0)) lc = 3;
    }
    else if ((sc == 1) && (t == '\n'))
    {

        if (v != '\\') sc = 2;
    }
    else if ((str == 1) && (t == '\n'))
    {
        if (v != '\\') str = 2;
    }
    else if ((ch == 1) && (t == '\n'))
    {
        ch = 0;
    }
    else if (t == '"')
    {
        if ((lc != 1) && (sc != 1) && (ch != 1))
        {
            if (str) str = 0;
            else str = 1;
        }
    }
    else if (t == '\'')
    {
        if ((lc != 1) && (sc != 1) && (str != 1))
        {
            if (ch) ch = 0;
            else ch = 1;
        }
    }
}

int check()
{
    if (len) len--;
    if (str)
    {
        if (str == 2) str = 0;
        return 1;
    }
    else if (ch)
    {
        if (ch == 2) ch = 0;
        return 1;
    }
    else if ((sc == 0) && (lc == 0)) return 1;
    else if ((sc) || (lc))
    {
        if (sc == 2) sc = 0;
        else if (lc == 3) lc = 2;
        else if (lc == 2) lc = 0;
        return 0;
    }
}

int main()
{
    FILE * f;
    FILE * ff;
    f = fopen("test.c", "r+t");
    ff = fopen("test.wc", "w");
    char v = 0;
    char t = 0;
    v = fgetc(f);
    while ((t = fgetc(f)) != EOF)
    {
        if (t == 13) t = fgetc(f);
        stepcheck(v,t);
        if (check()) fputc(v,ff);
        v = t;
    }
    if (check()) fputc(v,ff);
    return 0;
}
