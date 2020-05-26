#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TEXT{
    int Count;
    unsigned char Byte[4];
}character;


void swap_Count(int *c1,int *c2);//swap c1,c2
void swap_char(unsigned char *CH1,unsigned char *CH2);//swap CH1,CH2



int main(int argc, char *argv[]){

    FILE *fin = fopen(argv[1],"rb");
    //FILE *fin = fopen("CEmix_Input.txt","rb");//for test
    FILE *fout = fopen(argv[2],"wb");
    //FILE *fout = fopen("output.txt","wb");//for test


    character ch[2500];//input file's character
    int i,j;
    /***Initialize the structure ch variable:Count and Byte[4]***/
    for(i=0;i<2500;i++){
        for(j=0;j<4;j++){
            ch[i].Byte[j]=0;
        }
        ch[i].Count=0;
    }

    unsigned char data;//save the input data
    unsigned char data2[4]={0};//save the bytes of input data and initialize it as 0 first.
    unsigned int Bt2=0,Bt3=0,Bt4=0,Bt_num=0;//Byte 2; Byte 3; Byte 4; Recording for what value (Bytes) computer saved.
    int N=0,N_data=0;//# of data(Sample);# of data character

    while(!feof(fin)){
        fread(&data,sizeof(unsigned char),1,fin);//read one character from fin and save to variable data
        /***Start from U+0000 to U+007F =>1 Bytes(0xxxxxxx)***/
        if(data<= 0x7F && Bt2 == 0 && Bt3 == 0 && Bt4 == 0){
            for(i=0;i<2500;i++){
               if(ch[i].Byte[0] == 0){
                    ch[i].Byte[0] =data;
                    ch[i].Count++;
                    N++;
                    N_data++;
                    break;
                }
                else if(data == ch[i].Byte[0]){
                    ch[i].Count++;
                    N++;
                    break;
                }
            }
        }
        /***Start from U+0080 to U+07FF =>2 Bytes(110xxxxx 10xxxxxx)***/
        else if((data >= 0xC0 && data <= 0xDF && Bt3 == 0 && Bt4 == 0) || Bt2 == 1){
                if(Bt2==0){
                    data2[0]=data;
                    Bt2=1;
                }
                else{
                    data2[1]=data;
                    for(i=0;i<2500;i++){
                        if(ch[i].Byte[0]==0){
                            ch[i].Byte[0]=data2[0];
                            ch[i].Byte[1]=data2[1];
                            ch[i].Count++;
                            N++;
                            N_data++;
                            break;
                        }
                        else if(ch[i].Byte[0] == data2[0] && ch[i].Byte[1] == data2[1]){
                            ch[i].Count++;
                            N++;
                            break;
                        }
                    }
                    Bt2=0;
                }
        }
        /***Start from U+0800 to U+FFFF =>3 Bytes(1110xxxx 10xxxxxx 10xxxxxx)***/
        else if((data >= 0xE0 && data <= 0xEF && Bt4 == 0) || Bt3 == 1){
               if(Bt3==0){
                    data2[0]=data;
                    Bt_num=1;//1th Byte has been saved
                    Bt3=1;
               }
               else if(Bt_num==1){
                    data2[1]=data;
                    Bt_num=2;//2th Byte has been saved
               }
               else{
                    data2[2]=data;
                    for(i=0;i<2500;i++){
                        if(ch[i].Byte[0]==0){
                            ch[i].Byte[0]=data2[0];
                            ch[i].Byte[1]=data2[1];
                            ch[i].Byte[2]=data2[2];
                            ch[i].Count++;
                            N++;
                            N_data++;
                            break;
                        }
                        else if(ch[i].Byte[0] == data2[0] && ch[i].Byte[1] == data2[1] && ch[i].Byte[2] == data2[2]){
                            ch[i].Count++;
                            N++;
                            break;
                        }
                    }
                    Bt_num=0;
                    Bt3=0;
               }
        }
        /***Start from U+10000 to U+1FFFFF =>4 Bytes(11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)***/
        else if((data >= 0xF0 && data <= 0xF7)|| Bt4 == 1){
                if(Bt4==0){
                    data2[0]=data;
                    Bt_num=1;//1th Byte has been saved
                    Bt4=1;
                }
                else if(Bt_num==1){
                    data2[1]=data;
                    Bt_num=2;//2th Byte has been saved
                }
                else if(Bt_num==2){
                    data2[2]=data;
                    Bt_num=3;//3th Byte has been saved
                }
                else{
                    data2[3]=data;
                    for(i=0;i<2500;i++){
                        if(ch[i].Byte[0]==0){
                            ch[i].Byte[0]=data2[0];
                            ch[i].Byte[1]=data2[1];
                            ch[i].Byte[2]=data2[2];
                            ch[i].Byte[3]=data2[3];
                            ch[i].Count++;
                            N++;
                            N_data++;
                            break;
                        }
                        else if(ch[i].Byte[0] == data2[0] && ch[i].Byte[1] == data2[1] && ch[i].Byte[2] == data2[2] && ch[i].Byte[3] == data2[3]){
                            ch[i].Count++;
                            N++;
                            break;
                        }

                    }
                    Bt_num=0;
                    Bt4=0;
                }

        }
    }

    /***Sorting data from small to big by function swap***/
    for(i=0;i<N_data;i++){
        for(j=i;j<N_data;j++){
            if(ch[j].Count < ch[i].Count){
                swap_Count(&ch[j].Count,&ch[i].Count);
                swap_char(&ch[j].Byte[0],&ch[i].Byte[0]);
                swap_char(&ch[j].Byte[1],&ch[i].Byte[1]);
                swap_char(&ch[j].Byte[2],&ch[i].Byte[2]);
                swap_char(&ch[j].Byte[3],&ch[i].Byte[3]);
            }
        }
    }

    int k;
    int sum=0;
    int pos[N_data-1];

    /***Make the huffman tree by adding two smallest values and arrange it until the end.Moreover,recording the position of two adding values ***/
    for(k=0;k<N_data-1;k++){
        for(i=1;i<N_data;i++){
            sum = ch[0].Count+ ch[1].Count;
            if(sum>=ch[i].Count&&sum<=ch[i+1].Count){
                pos[k]=i-1;
                for(j=0;j<i-1;j++){
                    ch[j].Count = ch[j+2].Count;
                }
                ch[i-1].Count = sum;
                for(j=i;j<N_data-1-k;j++){
                    ch[j].Count = ch[j+1].Count;
                }
                break;
            }
            if(sum>ch[N_data-1-k].Count){
                pos[k]=N_data-2-k;
                for(j=0;j<N_data-2-k;j++){
                    ch[j].Count = ch[j+2].Count;
                }
                ch[N_data-2-k].Count = sum;
                break;
            }
        }
    /*
        printf("******%d******** ",b[k]);
        for(i=0;i<2356-k;i++){
            printf("%d ",ch[i].Count);
        }
        printf("\n");*/
    }


    int m;
    int temp;
    int TEM[N_data];
    int cc1[N_data];
    int pr[N_data][18];
    int code[N_data][18];

    /***Make huffman codes of each symbols***/
    for(m=0;m<N_data;m++){
        temp = 0;
        for(k=0;k<N_data;k++){
            cc1[0] = m;
            if(cc1[k]==0){
                pr[m][temp] = 0;
                temp = temp + 1;
                cc1[k+1] = pos[k];
            }
            else if(cc1[k]==1){
                pr[m][temp] = 1;
                temp = temp + 1;
                cc1[k+1] = pos[k];
            }
            else if(cc1[k]-2>=pos[k]){
                cc1[k+1] = cc1[k] - 1;
            }
            else if(cc1[k]-2<pos[k]){
                cc1[k+1] = cc1[k] - 2;
            }
        }
        TEM[m] = temp;
        for(k=0;k<temp;k++){
            code[m][k] = pr[m][temp-1-k];
        }
    }

    /***Sorting word from big to small because the word had high frequency has shorter code than the other***/
    for(i=0;i<N_data;i++){
        for(j=i;j<N_data;j++){
            swap_char(&ch[j].Byte[0],&ch[i].Byte[0]);
            swap_char(&ch[j].Byte[1],&ch[i].Byte[1]);
            swap_char(&ch[j].Byte[2],&ch[i].Byte[2]);
            swap_char(&ch[j].Byte[3],&ch[i].Byte[3]);
        }
    }


    /***Writing word and its huffman code to the output file***/
    for(m=0;m<N_data;m++){
        if(ch[m].Byte[0]<=0x7F){
            if(ch[m].Byte[0]=='\n'){
                fprintf(fout,"\\n     ");
                    for(k=1;k<TEM[N_data-1-m];k++){
                        fprintf(fout,"%d",code[N_data-1-m][k]);
                    }
                fprintf(fout,"\r\n");
            }
            else if(ch[m].Byte[1]=='\r'){
                fprintf(fout,"\\r     ");
                    for(k=1;k<TEM[N_data-1-m];k++){
                        fprintf(fout,"%d",code[N_data-1-m][k]);
                    }
                fprintf(fout,"\r\n");
            }
            else{
                fprintf(fout,"%2c     ",ch[m].Byte[0]);//1 Byte
                    for(k=1;k<TEM[N_data-1-m];k++){
                        fprintf(fout,"%d",code[N_data-1-m][k]);
                    }
                fprintf(fout,"\r\n");
            }
        }
        else if(ch[m].Byte[0]>=0xC0 && ch[m].Byte[0]<=0xDF ){
            fprintf(fout,"%c%c     ",ch[m].Byte[0],ch[m].Byte[1]);//2 Bytes
                for(k=1;k<TEM[N_data-1-m];k++){
                    fprintf(fout,"%d",code[N_data-1-m][k]);
                }
            fprintf(fout,"\r\n");
        }
        else if(ch[m].Byte[0]>=0xE0 && ch[m].Byte[0]<=0xEF){
            fprintf(fout,"%c%c%c     ",ch[m].Byte[0],ch[m].Byte[1],ch[m].Byte[2]);//3 Bytes
                for(k=1;k<TEM[N_data-1-m];k++){
                    fprintf(fout,"%d",code[N_data-1-m][k]);
                }
            fprintf(fout,"\r\n");
        }
        else{
            fprintf(fout,"%c%c%c%c     ",ch[m].Byte[0],ch[m].Byte[1],ch[m].Byte[2],ch[m].Byte[3]);//4 Bytes
                for(k=1;k<TEM[N_data-1-m];k++){
                    fprintf(fout,"%d",code[N_data-1-m][k]);
                }
            fprintf(fout,"\r\n");
        }
    }

    /***Close File***/
    fclose(fin);
    fclose(fout);

    return 0;

}

void swap_Count(int *c1,int *c2){
    int temp_Count;
    temp_Count = *c2;
    *c2 = *c1;
    *c1 = temp_Count;
};
void swap_char(unsigned char *CH1,unsigned char *CH2){
    unsigned char temp_char;
    temp_char = *CH2;
    *CH2 = *CH1;
    *CH1 = temp_char;
};
