#include <stdio.h>

struct money2
{
    int deposit;
    unsigned short numDeps;
    int withdraw;
    unsigned short numWithdraw;
};

struct money3
{
    int deposit;
    int withdraw;
    unsigned short numDeps;
    unsigned short numWithdraw;
};

struct money4
{
    int deposit;
    unsigned short numDeps;
    unsigned short numWithdraw;
};

struct money5
{
    unsigned short numDeps;
    unsigned short numWithdraw;
    int C;
    int D;
};

struct money6
{
    unsigned short numDeps;
    int B;
    unsigned short numWithdraw;
};

struct money7
{
    unsigned short A;
    unsigned short numDeps;
    unsigned short numWithdraw;
};

struct money8
{
    unsigned long A;
};

struct money9
{
    unsigned long A;
    unsigned long B;
    unsigned short C;
    int D;
};

struct money10
{
    unsigned long A;
    int B;
    unsigned short C;
    double D;
};

struct money11
{
    long A;
    double B;
    unsigned short C;
    unsigned long D;
};

struct money12
{
    unsigned short A;
    double B;
    unsigned short C;
};

int main(int argc, char *argv[])
{
    printf("%lu byte\n", sizeof(float));            //このパソコンの場合、4byte
    printf("%lu byte\n", sizeof(int));              //このパソコンの場合、4byte
    printf("%lu byte\n", sizeof(unsigned short));   //2byte
    printf("%lu byte\n", sizeof(unsigned long));    //4byte
    printf("%lu byte\n", sizeof(double));           //8byte
    printf("%lu byte\n", sizeof(long));             //4byte
    printf("%lu byte2\n", sizeof(struct money2));   //16byte
    printf("%lu byte3\n", sizeof(struct money3));   //12byte
    printf("%lu byte4\n", sizeof(struct money4));   //8byte
    printf("%lu byte5\n", sizeof(struct money5));   //12byte
    printf("%lu byte6\n", sizeof(struct money6));   //12byte
    printf("%lu byte7\n", sizeof(struct money7));   //6byte
    printf("%lu byte8\n", sizeof(struct money8));   //4byte
    printf("%lu byte9\n", sizeof(struct money9));   //16byte
    printf("%lu byte10\n", sizeof(struct money10)); //24byte
    printf("%lu byte11\n", sizeof(struct money11)); //24dyte
    printf("%lu byte12\n", sizeof(struct money12)); //24dyte

    return 0;
}
