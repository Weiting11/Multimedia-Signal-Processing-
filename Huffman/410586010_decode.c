#include <stdio.h>
#include <stdlib.h>
unsigned char input[120839];
int compress[120839];
unsigned char output[252380];
int main(int argc,char *argv[])
{
    FILE *fin;
    fin = fopen(argv[1],"rb");
    //fin = fopen("compress.txt","rb");
    fread(&input,sizeof(input),1,fin);
    int i,j;
    for(i=0;i<120839;i++)
    {
        //printf("%d ",input[i]);
        compress[i] = input[i];
        //printf("%d \n",compress[i]);
    }
    fclose(fin);
    int b[8],a,t,g,m,sum,p;
    int o;
    int re[24],s[2357],temp[2357];
    int symbol[2357];
    unsigned char c[35];
    unsigned int code[2357][35];
    FILE *fcode;
    fcode = fopen(argv[2],"rb");
    //fcode = fopen("codebook.txt","rb");
    for(m=0;m<2357;m++)
    {
        if(fgets(c,35,fcode)!= NULL)
        {
            for(i=0;i<35;i++)
            {
                if(c[i] == ' ')//s[m]和temp[m]將會在後面用來計算每個symbol的code的長度
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
            for(j=0;j<temp[m]-s[m]-2;j++)//將每個symbol的code存在另外的array
            {
                g = s[m]+1;
                code[m][j] = c[j+g]-48;
                //printf("%d",code[m][j]);
            }
            //printf("\n");
            sum=0;
            p = s[m] + 1;
            if(s[m]==7)//將symbol改成數字輸出
            {
                o =(c[0]-48);
                sum = sum + o*100;
                o =(c[1]-48);
                sum = sum + o*10;
                o =(c[2]-48);
                sum = sum + o;
                symbol[m] = abs(sum);
                //printf("%d\n",symbol[m]);
            }
            if(s[m]==6)
            {
                o =(c[0]-48);
                sum = sum + o*10;
                o =(c[1]-48);
                sum = sum + o;
                symbol[m] = abs(sum);
                //printf("%d\n",symbol[m]);
            }
        }
    }

    fclose(fcode);
    int r,x,flag,e=0;
    t=0;//用來計算暫存code的長度，最高只會到16+8
    int k=0;

    for(i=0;i<252380;i++)//解碼
    {
        while(t<17)//如果暫存array小於17，要繼續補8個二進位
        {
            //printf("@@@@@@@@@%d\n",compress[k]);
            b[7] = compress[k]%2;
            a = compress[k]/2;
            b[6] = a%2;
            a = a/2;
            b[5] = a%2;
            a = a/2;
            b[4] = a%2;
            a = a/2;
            b[3] = a%2;
            a = a/2;
            b[2] = a%2;
            a = a/2;
            b[1] = a%2;
            a = a/2;
            b[0] = a%2;//把compress讀到的字元，轉成數字，再轉成二進位
            for(j=0;j<8;j++)
            {
                re[t+j] = b[j];
                //printf("#########%d \n",re[t+j]);
            }
            t = t + 8;
            for(j=0;j<t;j++)
            {
                //printf("%d",re[j]);
            }

            //printf("**%d***\n",t);
            k++;
        }
        if(t>=17)//如果暫存array大於等於17，就代表可以開始對照codebook中的symbol，找到相應的symbol，還原出input的值
        {
            flag = 0;
            for(m=0;m<2357;m++)
            {
                p=0;
                for(r=0;r<temp[m]-s[m]-2;r++)
                {
                    if(re[r] == code[m][r])
                    {
                        p = p + 1;
                    }
                    else
                    {
                        break;
                    }

                }
                if(p == temp[m]-s[m]-2)
                    break;
            }
            //printf("%d ",symbol[m]);
            output[e] = symbol[m];
            e = e + 1;
            //printf("%d ",output[m]);
            t = t - p;
            for(x=0;x<t;x++)
            {
                //printf("***%d",t);
                re[x] = re[x+p];
                //printf("%d",re[x]);
            }

        }
        //printf("/////\n");
    }


    FILE *fout;//將還原出的symbol寫入output
    fout = fopen(argv[3],"wb");
    //fout = fopen("decode.txt","wb");
    for(i=0;i<252380;i++)
    {
        fprintf(fout,"%c",output[i]);
    }
    fclose(fout);

    //printf("%d",k);
    //printf("%d",e);
    /*for(e=0;e<5000;e++)
    {
        printf("%d",output[e]);
    }*/


    return 0;
}
