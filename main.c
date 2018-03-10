#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char in[10][10];
    int time;
} hash[500];
hash hashh;
int num2[4],num3[4];
char opcode[500][5];
char nopcode[500][5];
char symtab[100][10];
void jopcode(char opcode[500][5],char nopcode[500][5]);
void copy(int,int,int,int);
void to16(int,int);
void t16(int,int);
int main()
{
    jopcode(opcode,nopcode);
    FILE *stream;
    stream=fopen("code.txt","r");

    char *t = " ",B[5]= {'1','0','0','0','\0'};
    char A[500],symnum[50][10],symtab[50][10];
    char *test;
    int i=0,j=0,all,k,sym=0,l,len[50];
    all=0;
    while(fgets(A,30,stream)!=NULL)
    {
        A[strlen(A)-1]=' ';
        test = strtok(A,t);
        while (test != NULL)
        {
            strcpy(hashh[all].in[hashh[all].time++],test);
            test = strtok(NULL,t);
        }
        all++;
    }
    strcpy(hashh[0].in[3],B);
    strcpy(hashh[1].in[3],B);
    for(i=1; i<all; i++)
    {
        int jud=1,jud1=1;
        if(hashh[i].time==2||hashh[i].time==1)
            jud=0;
        if(hashh[i+1].time==2||hashh[i+1].time==1)
            jud1=0;

        if(!strcmp(hashh[i].in[jud],"WORD"))
        {
            strcpy(hashh[i+1].in[jud1+2],hashh[i].in[jud+2]);
            hashh[i+1].in[jud1+2][3]+=3;
            to16(i+1,jud1);
        }
        else if(!strcmp(hashh[i].in[jud],"RESW"))
        {
            strcpy(hashh[i+1].in[jud1+2],hashh[i].in[jud+2]);
            hashh[i+1].in[jud1+2][3]+=atoi(hashh[i].in[jud+1])*3;
            to16(i+1,jud1);
        }
        else if(!strcmp(hashh[i].in[jud],"RESB"))
        {
            int num;
            strcpy(hashh[i+1].in[jud1+2],hashh[i].in[jud+2]);
            num=atoi(hashh[i].in[jud+1]);
            t16(i,num);
            for(k=0; k<4; k++)
                hashh[i+1].in[jud1+2][k]+=num2[k];
            to16(i+1,jud1);
        }
        else if(!strcmp(hashh[i].in[jud],"BYTE"))
        {
            strcpy(hashh[i+1].in[jud1+2],hashh[i].in[jud+2]);
            char a[5][5];
            if(hashh[i].in[jud+1][0]=='C')
            {
                for(j=2; j<strlen(hashh[i].in[jud+1])-1; j++)
                {
                    num3[j-2]=hashh[i].in[jud+1][j];
                    itoa(num3[j-2],a[j-2],16);
                    strcat(hashh[i].in[jud+3],a[j-2]);
                }
                hashh[i+1].in[jud1+2][3]+=strlen(hashh[i].in[jud+3])/2;

            }
            if(hashh[i].in[jud+1][0]=='X')
            {
                for(j=2; j<strlen(hashh[i].in[jud+1])-1; j++)
                    hashh[i].in[jud+3][j-2]=hashh[i].in[jud+1][j];
                hashh[i+1].in[jud1+2][3]+=strlen(hashh[i].in[jud+3])/2;

            }
            to16(i+1,jud1);
        }
        else
        {
            strcpy(hashh[i+1].in[jud1+2],hashh[i].in[jud+2]);
            hashh[i+1].in[jud1+2][3]+=3;
            to16(i+1,jud1);
        }
    }
    for(i=0; i<all; i++)
    {
        if(hashh[i].time==3)
        {
            strcpy(symtab[sym],hashh[i].in[0]);
            strcpy(symnum[sym++],hashh[i].in[3]);
        }
    }
    for(i=1; i<all; i++)
    {
        int jud=1,num;
        if(hashh[i].time==2||hashh[i].time==1)
            jud=0;
        if(!strcmp(hashh[i].in[jud],"WORD"))
        {
            num=strlen(hashh[i].in[jud+1]);
            for(j=0; j<6; j++)
                hashh[i].in[jud+3][j]='0';
            for(j=0; j<num; j++)
                hashh[i].in[jud+3][5-j]=hashh[i].in[jud+1][num-j-1];
        }
        for(j=0; j<26; j++)
        {
            int gg=0;
            if(!strcmp(opcode[j],hashh[i].in[jud]))
            {
                strcat(hashh[i].in[jud+3],nopcode[j]);
                if(hashh[i].in[jud+1][strlen(hashh[i].in[jud+1])-1]=='X'&&hashh[i].in[jud+1][strlen(hashh[i].in[jud+1])-2]==',')
                {
                    hashh[i].in[jud+1][strlen(hashh[i].in[jud+1])-2]='\0';
                    gg=1;
                }
                for(k=0; k<sym; k++)
                    if(!strcmp(symtab[k],hashh[i].in[jud+1]))
                        strcat(hashh[i].in[jud+3],symnum[k]);
                if(gg)
                {
                    hashh[i].in[jud+1][strlen(hashh[i].in[jud+1])+1]='X';
                    hashh[i].in[jud+1][strlen(hashh[i].in[jud+1])]=',';
                    hashh[i].in[jud+3][2]+=8;
                }
                if(hashh[i].time==1)
                    for(l=2; l<6; l++)
                        hashh[i].in[jud+3][l]='0';
            }
        }
    }
    printf("H%s 001000,00",hashh[0].in[0]);
    char C[4];
    strcpy(C,hashh[all-2].in[3]);
    C[0]-=1;
    C[3]+=1;
    int num;
    if(C[3]>'F')
    {
        num=C[3]-'F';
        C[3]=num+'0'-1;
        C[2]++;
    }
    else if(C[3]>'9'&&C[3]<'A')
    {
        num=C[3]-'9';
        C[3]=num+'A'-1;
    }
    for(i=0; i<4; i++)
        printf("%c",C[i]);
        printf("\n");
    int jud,sum,total=0,a,b;
    char D[10][10];
    printf("T,00%s,",hashh[1].in[3]);
    for(i=1; i<all; i++)
    {
        int jud=4;
        if(hashh[i].time==2||hashh[i].time==1)
            jud=3;
        sum+=strlen(hashh[i].in[jud]);
        if(i%10==0)
        {
            jud=4;
            if(hashh[i+1].time==2||hashh[i+1].time==1)
                jud=3;
            len[total++]=sum/2;
            sum=0;
        }
    }
    len[total++]=sum/2;
    for(i=0; i<total; i++)
        itoa(len[i],D[i],16);
        for(i=0; i<total; i++)
        if(strlen(D[i])<2)
        {
            D[i][1]=D[i][0];
            D[i][0]='0';
            D[i][2]='\0';
        }
        total=1;
        printf("%s,",strupr(D[0]));
    for(i=1; i<all; i++)
    {
        int jud=4;
        if(hashh[i].time==2||hashh[i].time==1)
            jud=3;
        printf("%s",hashh[i].in[jud]);
        sum+=strlen(hashh[i].in[jud]);
        if(i%10==0)
        {
            printf("\n");
            jud=4;
            if(hashh[i+1].time==2||hashh[i+1].time==1)
                jud=3;
            printf("T,00%s,%s,",hashh[i+1].in[jud-1],strupr(D[total++]));
        }
    }
    printf("\nE,001000");
    return 0;
}
void to16(int i,int jud1)
{
    int num;
    if(hashh[i].in[jud1+2][3]>'F')
    {
        num=hashh[i].in[jud1+2][3]-'F';
        hashh[i].in[jud1+2][3]=num+'0'-1;
        hashh[i].in[jud1+2][2]++;
    }
    else if(hashh[i].in[jud1+2][3]>'9'&&hashh[i].in[jud1+2][3]<'A')
    {
        num=hashh[i].in[jud1+2][3]-'9';
        hashh[i].in[jud1+2][3]=num+'A'-1;
    }
}
void t16(int i,int num)
{
    int num3[4]= {4096,256,16,1},j=0;

    num2[0]=num2[1]=num2[2]=num2[3]=0;
    while(num)
    {
        num2[j]=num/num3[j];
        num%=num3[j++];
    }
}
void jopcode(char opcode[500][5],char nopcode[500][5])
{
    strcpy(opcode[0],"ADD");
    strcpy(nopcode[0],"18");
    strcpy(opcode[1],"DIV");
    strcpy(nopcode[1],"24");
    strcpy(opcode[2],"JGT");
    strcpy(nopcode[2],"34");
    strcpy(opcode[3],"LDA");
    strcpy(nopcode[3],"00");
    strcpy(opcode[4],"LDX");
    strcpy(nopcode[4],"04");
    strcpy(opcode[5],"RD");
    strcpy(nopcode[5],"D8");
    strcpy(opcode[6],"STCH");
    strcpy(nopcode[6],"54");
    strcpy(opcode[7],"STX");
    strcpy(nopcode[7],"10");
    strcpy(opcode[8],"TIX");
    strcpy(nopcode[8],"2C");
    strcpy(opcode[9],"AND");
    strcpy(nopcode[9],"40");
    strcpy(opcode[10],"J");
    strcpy(nopcode[10],"3C");
    strcpy(opcode[11],"JLT");
    strcpy(nopcode[11],"38");
    strcpy(opcode[12],"LDCH");
    strcpy(nopcode[12],"50");
    strcpy(opcode[13],"MUL");
    strcpy(nopcode[13],"20");
    strcpy(opcode[14],"RSUB");
    strcpy(nopcode[14],"4C");
    strcpy(opcode[15],"STL");
    strcpy(nopcode[15],"14");
    strcpy(opcode[16],"SUB");
    strcpy(nopcode[16],"1C");
    strcpy(opcode[17],"WD");
    strcpy(nopcode[17],"DC");
    strcpy(opcode[18],"COMP");
    strcpy(nopcode[18],"28");
    strcpy(opcode[19],"JEQ");
    strcpy(nopcode[19],"30");
    strcpy(opcode[20],"JSUB");
    strcpy(nopcode[20],"48");
    strcpy(opcode[21],"LDL");
    strcpy(nopcode[21],"08");
    strcpy(opcode[22],"OR");
    strcpy(nopcode[22],"44");
    strcpy(opcode[23],"STA");
    strcpy(nopcode[23],"0C");
    strcpy(opcode[24],"STSW");
    strcpy(nopcode[24],"18");
    strcpy(opcode[25],"TD");
    strcpy(nopcode[25],"10");
}
