#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<complex.h>
#define pi 3.1415926

//wave �����Y��
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
�ŧi�bmain�̭��A�|�]���}�C�Ӥj�ɭP������檺���D�A��Ӧ��ϥ�static���覡�ŧi�A���o�X�Ӫ��n���|�������C
��ӤW���d��O���ŧi�bmain�~���A�~���|��proccess exacution�C
*/
//���˼Ƭ�105000�A�����W�v��48000Hz(�ϥ�Matlab�o��)
short data[105000];
double data2[105000];
double Xre[105000];//Real Part
double Xim[105000];//Imaginary Part
double a[105000];//array for save Real Part of IDFT
double b[105000];//array for save Imaginary Part of IDFT

int main(int argc,char *argv[]){
    //FILE *wav=fopen(argv[1],"rb");//��argv[1]Ū��wav��
    FILE *wav=fopen("HW2_1008.wav","rb");//for test

    header houtput;//�ŧiwav�����Y��

    fread(&houtput,sizeof(header),1,wav);//Ū�Jwav��

    int i=0;
    short t=0;
    //Ū�J wav data
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
    //�N�Q�o�i���o��������=0;��L���a��T����b
    //��(k/N)*fs=7000Hz�������D�Xk=15312.5�A�ҥH�n�N15312~(105000-15312)�o�Ӱ϶��o���C
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
    short output=0;//�ŧi�@��output�Ӧs��data2�}�C���ȡA�bfwrite�ɨϥ�
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

    //�]�������ഫ�᪽���O�����A�ҥH�n�N�쥻���t���ȥ[�W�t��
    for(k=0;k<105000;k++){
        if(a[k]<0){
            data2[k]*=(-1);
        }
    }
    printf("Writing data...\n");

    //�إ߿�X�ɮ�
    //FILE *output_wav=fopen(argv[2],"wb");
    FILE *output_wav=fopen("output.wav","wb");
    //�N���׼g�J�ɮפ�
    fwrite(&houtput,sizeof(header),1,output_wav);
    for(k=0;k<105000;k++){
        output=(short)data2[k];
        fwrite(&output,sizeof(short),1,output_wav);
    }
    printf("ALL is Well.");



    //�����ɮ�
    fclose(output_wav);
    fclose(wav);
    return 0;
}
