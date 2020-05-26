#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TEXT{
    int Count;
    unsigned char Byte[4];
}character;

void swap_P(float *p1,float *p2);//swap p1,p2
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
    float P[2500];//Probability array
    for(i=0;i<2500;i++){
        P[i]=0;
    }
    /***Probability of each character***/
    for(i=0;i<N_data;i++){
        P[i]=ch[i].Count/(float)N;//P(x) = # of x / N
    }

    /***Sorting data from big to small by function swap***/
    for(i=0;i<N_data;i++){
        for(j=i;j<N_data;j++){
            if(P[j]>P[i]){
                swap_P(&P[j],&P[i]);
                swap_Count(&ch[j].Count,&ch[i].Count);
                swap_char(&ch[j].Byte[0],&ch[i].Byte[0]);
                swap_char(&ch[j].Byte[1],&ch[i].Byte[1]);
                swap_char(&ch[j].Byte[2],&ch[i].Byte[2]);
                swap_char(&ch[j].Byte[3],&ch[i].Byte[3]);
            }
        }
    }

    /***Writing sorted data to the output file***/
    for(i=0;i<N_data;i++){
        if(ch[i].Byte[0]<=0x7F){
            if(ch[i].Byte[0]=='\n'){
                fprintf(fout,"\\n   %4d   %.6f\r\n",ch[i].Count,P[i]);
            }
            else if(ch[i].Byte[1]=='\r'){
                fprintf(fout,"\\r   %4d   %.6f\r\n",ch[i].Count,P[i]);
            }
            else{
                fprintf(fout,"%2c   %4d   %.6f\r\n",ch[i].Byte[0],ch[i].Count,P[i]);//1 Byte
            }
        }
        else if(ch[i].Byte[0]>=0xC0 && ch[i].Byte[0]<=0xDF ){
            fprintf(fout,"%c%c   %4d   %.6f\r\n",ch[i].Byte[0],ch[i].Byte[1],ch[i].Count,P[i]);//2 Bytes
        }
        else if(ch[i].Byte[0]>=0xE0 && ch[i].Byte[0]<=0xEF){
            fprintf(fout,"%c%c%c   %4d   %.6f\r\n",ch[i].Byte[0],ch[i].Byte[1],ch[i].Byte[2],ch[i].Count,P[i]);//3 Bytes
        }
        else{
            fprintf(fout,"%c%c%c%c   %4d   %.6f\r\n",ch[i].Byte[0],ch[i].Byte[1],ch[i].Byte[2],ch[i].Byte[3],ch[i].Count,P[i]);//4 Bytes
        }
    }

    /***Close File***/
    fclose(fin);
    fclose(fout);
    //printf("%d  %d",N,N_data);//N=95313;N_data=2357

    return 0;
}

void swap_P(float *p1,float *p2){
    float Max_P;
    Max_P = *p2;
    *p2 = *p1;
    *p1 = Max_P;
};
void swap_Count(int *c1,int *c2){
    int Max_Count;
    Max_Count = *c2;
    *c2 = *c1;
    *c1 = Max_Count;
};
void swap_char(unsigned char *CH1,unsigned char *CH2){
    unsigned char Max_char;
    Max_char = *CH2;
    *CH2 = *CH1;
    *CH1 = Max_char;
};

