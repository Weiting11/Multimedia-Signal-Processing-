#include <stdio.h>
#include <stdlib.h>
unsigned char input[252380];
int input2[252380];
int ncode[252380][35];
int main(int argc,char *argv[])
{
    unsigned char c[35];
    int s[2357],temp[2357];
    int m,i,j;
    unsigned int code[2357][35];

    FILE *fin;
    fin = fopen(argv[1],"rb");
    //fin = fopen("CEmix_Input.txt","rb");
    fread(&input,sizeof(input),1,fin);
    fclose(fin);

    /*
    for(i=0;i<20;i++){
        printf("%d ",input[i]);
        //printf("\n");
    }*/

    FILE *fcode;
    fcode = fopen(argv[2],"r");
    //fcode = fopen("codebook.txt","rb");
    for(m=0;m<2357;m++)//�Ncodebook�@��@��Ū�æs�barray
    {
        if(fgets(c,35,fcode)!= NULL)
        {
            for(i=0;i<35;i++)
            {
                if(c[i] == ' ')
                {
                    s[m] = i;
                    //printf("%d\n",s[m]);
                }
                if(c[i] == NULL)
                {
                    temp[m] = i-1;
                    //printf("%d ",temp[m]);
                    break;
                }
            }
            for(j=0;j<temp[m];j++)
            {
                code[m][j] = c[j];
                //printf("%c",code[m][j]);
            }
            //printf("\n");
        }
    }

    //printf("%d %d %d",code[0][0],code[0][1],code[0][2]);
    /*
    for(m=0;m<2357;m++){
        printf("%d\n",s[m]);
    }*/

    fclose(fcode);
    int p,b;
    int sum;
    char num[2357][35];
    int symbol[2357];
    for(m=0;m<2357;m++)//�NŪ�J��symbol�r���ন�Ʀr�A�N�C��symbol��code�s�b�t�~��array
    {
        sum=0;
        p = s[m] + 1;
        for(i=s[m]+1;i<temp[m];i++)
        {
            num[m][i-p] = code[m][i];
            //printf("%c",code[m][i]);
            //printf("%c",num[m][i-p]);
        }
        if(s[m]==7)
        {
            b =(code[m][0]-48);
            sum = sum + b*100;
            b =(code[m][1]-48);
            sum = sum + b*10;
            b =(code[m][2]-48);
            sum = sum + b;
            symbol[m] = abs(sum);
            //printf("%d",symbol[m]);
        }
        if(s[m]==6)
        {
            b =(code[m][0]-48);
            sum = sum + b*10;
            b =(code[m][1]-48);
            sum = sum + b;
            symbol[m] = abs(sum);
            //printf("%d",symbol[m]);
        }
        //printf("\n");
    }
    int y,t=0,f=0;
    int re[8];
    unsigned char com;
    int cim;
    FILE *fout;
    fout = fopen(argv[3],"wb");
    //fout = fopen("compress.txt","wb");
    for(i=0;i<252380;i++)//���intput�̭�������symbol�A�÷Ӷ��ǥ��N�o��symbol������code�s�_�ӡA�A�K�Ӥ@�ơA�B�̫�@�Ӥ���8�Ӫ��e����0�A�A�N�o���ন�Q�i��g�Jcompress

    {
        //printf("%d ",input[i]);
        input2[i] = input[i];
        //printf("%d \n",input2[i]);
        for(m=0;m<2357;m++)
        {
            //printf("%d %d\n",m,symbol[m]);
            if(input2[i] == symbol[m])
            {
                //printf("*********%d*****\n",m);
                //printf("%d %d ",temp[m],s[m]);
                for(j=0;j<temp[m]-s[m]-1;j++)
                {
                    y = num[m][j]-48;
                    //printf("%d",y);
                    ncode[i][j] = y;
                    re[t] = ncode[i][j];
                    //printf("%d ",re[t]);
                    t = t + 1;
                    if(t == 8)
                    {
                        sum = 0;
                        sum = sum + re[0]*128;
                        sum = sum + re[1]*64;
                        sum = sum + re[2]*32;
                        sum = sum + re[3]*16;
                        sum = sum + re[4]*8;
                        sum = sum + re[5]*4;
                        sum = sum + re[6]*2;
                        sum = sum + re[7]*1;
                        com = sum ;
                        //printf("%d ",sum);
                        //printf("%d ",com);
                        fprintf(fout,"%c",com);
                        t=0;
                        f = f + 1;
                        //printf("\n");
                    }
                }
                //printf("\n");
            }
        }
        /*
        if(f == 371204)
        {
            printf("%d %d",re[0],re[1]);
        }*/
    }
    //printf("%d",f);
    sum = 0;
    com = sum ;
    fprintf(fout,"%c",com);
    fclose(fout);
    return 0;
}
