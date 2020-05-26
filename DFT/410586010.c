#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define pi 3.1415926

//wave �����Y��
struct waveHeader{
    unsigned char chumkID[4]; //RIFF
    unsigned int chunkSize;
    unsigned char format[4];
    unsigned char subchunkID[4];
    unsigned int subchunkSize;
    unsigned short audioFormat;
    unsigned short numChannels; //�n�D�ƶq
    unsigned int sampleRate;
    unsigned int byteRate;
    unsigned short blockAlign; //�C��block�������j�p = numChannels * bits_per_sample/8
    unsigned short bits_per_sample;
    unsigned char subchunk2ID[4];//data
    unsigned int subchunk2Size; //���T��Ƥj�p

}header;

int sampleNum;//�ŧi���˼�

int main(int argc,char *argv[]){
    FILE *wav=fopen(argv[1],"rb");//��argv[1]Ū��wav��
    FILE *magnitude=fopen("magnitude.txt","wb");
    FILE *phase=fopen("phase.txt","wb");

    //Ū�Jwav��
    fread(&header,sizeof(header),1,wav);

    //��X���˼�
    sampleNum=header.subchunk2Size/(header.numChannels*(header.bits_per_sample/8));

    short *data=malloc(sizeof(short)*sampleNum);

    int i=0;
    short t=0;

    //Ū�J wav data
    for(i=0;i<sampleNum;i++){
        fread(&t,2,1,wav);
        data[i]=(short)t;
    }
    int n,k;
    float *Mag=malloc(sizeof(float)*sampleNum);
    float *angle=malloc(sizeof(float)*sampleNum);
    float Xre;
    float Xim;

    //��DFT�B��
    for(k=0;k<sampleNum;k++){
        Xre=0;
        Xim=0;
        for(n=0;n<sampleNum;n++){
            Xre+=data[n]*cos(2*pi*n*k/sampleNum);
            Xim-=data[n]*sin(2*pi*n*k/sampleNum);

        }
        Mag[k]=20*log10(sqrt(Xre*Xre+Xim*Xim));
        angle[k]=atan(Xim/Xre);
    }
    //�N���׼g�J�ɮפ�
    fwrite(Mag,sizeof(float),sampleNum,magnitude);
    fwrite(angle,sizeof(float),sampleNum,phase);
    //����O����
    free(data);
    free(Mag);
    free(angle);
    //�����ɮ�
    fclose(magnitude);
    fclose(phase);

    return 0;
}
