#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<complex.h>
#define pi 3.1415926

//wave 的標頭檔
typedef struct waveHeader{
    unsigned char chumkID[4];
    unsigned int chunkSize;
    unsigned char format[4];
    unsigned char subchunkID[4];
    unsigned int subchunkSize;
    unsigned short audioFormat;
    unsigned short numChannels;
    unsigned int sampleRate;
    unsigned int byteRate;
    unsigned short blockAlign;
    unsigned short bits_per_sample;
    unsigned char subchunk2ID[4];
    unsigned int subchunk2Size;
}header;

/*
宣告在main裡面，會因為陣列太大導致不能執行的問題，後來有使用static的方式宣告，但濾出來的聲音會有雜音。
後來上網查到是說宣告在main外面，才不會有proccess exacution。
*/
//取樣數為105000，取樣頻率為48000Hz(使用Matlab得知)
short data[105000];
double data2[105000];
double Xre[105000];//Real Part
double Xim[105000];//Imaginary Part
double a[105000];//array for save Real Part of IDFT
double b[105000];//array for save Imaginary Part of IDFT

int main(int argc,char *argv[]){
    //FILE *wav=fopen(argv[1],"rb");//用argv[1]讀取wav檔
    FILE *wav=fopen("HW2_1008.wav","rb");//for test

    header houtput;//宣告wav的標頭檔

    fread(&houtput,sizeof(header),1,wav);//讀入wav檔

    int i=0;
    short t=0;
    //讀入 wav data
    for(i=0;i<105000;i++){
        fread(&t,2,1,wav);
        data[i]=(short)t;
    }
    printf("Read data Done.\n");
    /*********************DFT*****************/
    int n,k;
    for(k=0;k<105000;k++){
        Xre[k]=0;
        Xim[k]=0;
        for(n=0;n<105000;n++){
            Xre[k]+=data[n]*cos((2*pi)*n*k/105000);
            Xim[k]-=data[n]*sin((2*pi)*n*k/105000);
        }
        printf("%d\n",k);
    }
    printf("DFT Done.\n");
    /*********************LPF*****************/
    //將被濾波器濾掉的部分=0;其他的地方訊號減半
    //用(k/N)*fs=7000Hz的公式求出k=15312.5，所以要將15312~(105000-15312)這個區間濾掉。
    for(k=0;k<105000;k++){
        if((k>=15312)&&(k<=89687)){
            Xre[k]=0;
            Xim[k]=0;
        }
        else{
            Xre[k]=Xre[k]/2;
            Xim[k]=Xim[k]/2;
        }
        printf("%d\n",k);
    }
    printf("LPF Done.\n");

    /*********************IDFT*****************/
    short output=0;//宣告一個output來存放data2陣列的值，在fwrite時使用
    for(k=0;k<105000;k++){
        a[k]=0;
        b[k]=0;
        for(n=0;n<105000;n++){
            a[k]+=Xre[n]*cos((2*pi)*n*k/105000)-Xim[n]*sin((2*pi)*n*k/105000);
            b[k]+=Xim[n]*cos((2*pi)*n*k/105000)+Xre[n]*sin((2*pi)*n*k/105000);
        }
        printf("%d\n",k);
    }
    for(k=0;k<105000;k++){
        a[k]/=105000;
        b[k]/=105000;
        data2[k]=(short)(sqrt(a[k]*a[k]+b[k]*b[k]));
    }
    printf("IDFT Done.\n");

    //因為做完轉換後直都是正的，所以要將原本為負的值加上負號
    for(k=0;k<105000;k++){
        if(a[k]<0){
            data2[k]*=(-1);
        }
    }
    printf("Writing data...\n");

    //建立輸出檔案
    //FILE *output_wav=fopen(argv[2],"wb");
    FILE *output_wav=fopen("output.wav","wb");
    //將答案寫入檔案中
    fwrite(&houtput,sizeof(header),1,output_wav);
    for(k=0;k<105000;k++){
        output=(short)data2[k];
        fwrite(&output,sizeof(short),1,output_wav);
    }
    printf("ALL is Well.");



    //關閉檔案
    fclose(output_wav);
    fclose(wav);
    return 0;
}
