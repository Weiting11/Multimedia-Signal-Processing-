#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265
struct wavHeader {

    char ChunkID[4];
    int ChunkSize;
    char Format[4];
    char Subchunk1ID[4];
    int Subchunk1Size;
    short AudioFormat;
    short NumChannels;
    int SampleRate;
    int ByteRate;
    short BlockAlign;
    short BitsPerSample;
    char Subchunk2ID[4];
    int Subchunk2Size;

} header16k;

struct wavHeader8k {

    char ChunkID[4];
    int ChunkSize;
    char Format[4];
    char Subchunk1ID[4];
    int Subchunk1Size;
    short AudioFormat;
    short NumChannels;
    int SampleRate;
    int ByteRate;
    short BlockAlign;
    short BitsPerSample;
    char Subchunk2ID[4];
    int Subchunk2Size;

} header8k;

 int main()
{
    int a,t,n,k,i,m,j;
    float Re,Im;
    short vowel16kdata[53000];
    short vowel8kdata[30000];
	short wav1[16000];
    short wav2[16000];
    short wav3[16000];
    short wav4[16000];
    short wav5[8000];
    short wav6[8000];
    short wav7[8000];
    short wav8[8000];
    float wav1ham[16000];
    float wav1set1dft[16000];
    float wav5ham[8000];
    float wav5set1dft[8000];
    float vowel16kham[53000];
    float vowel16kset1dft[53000];
    float vowel8kham[30000];
    float vowel8kset1dft[30000];

    FILE *fp16k;
    FILE *fp8k;
    fp16k = fopen("vowel-16k.wav", "rb");   //  Open file for  reading binary
    if (!fp16k) {
        printf("can't open audio file vowel-16k.wav\n");
        return 0;
    }
    fp8k = fopen("vowel-8k.wav", "rb");   // Open file for  reading binary
    if (!fp8k) {
        printf("can't open audio file vowek-8k.wav\n");
        return 0;
    }

    fread(&header16k, sizeof(header16k), 1 ,fp16k);//fread 16k header
    fread(&header8k, sizeof(header8k), 1 ,fp8k);//fread 8k header

    for(a=0;a<53000;a++){
        fread(&vowel16kdata[a],sizeof(short),1,fp16k);

    }
    for(a=0;a<30000;a++){
        fread(&vowel8kdata[a],sizeof(short),1,fp8k);
        //fprintf(fp8k,"%hd",vowel16kdata[a]);
    }


    /***Generate 8 sine waves ***/
    for(t=0;t<16000;t++){
	wav1[t]=(short)(10000*cos(2*PI*50.0*(float)t/16000));
	wav2[t]=(short)(10000*cos(2*PI*200.0*(float)t/16000));
	wav3[t]=(short)(10000*cos(2*PI*55.0*(float)t/16000));
	wav4[t]=(short)(10000*cos(2*PI*220.0*(float)t/16000));
	}
	for(t=0;t<8000;t++){
	wav5[t]=(short)(10000*cos(2*PI*50.0*(float)t/8000));
	wav6[t]=(short)(10000*cos(2*PI*200.0*(float)t/8000));
	wav7[t]=(short)(10000*cos(2*PI*55.0*(float)t/8000));
	wav8[t]=(short)(10000*cos(2*PI*220.0*(float)t/8000));
	}

	/***Write 8 sine waves to wav file ***/
    //cos_050Hz_16k
    FILE* cos_050Hz16k =fopen("cos_050Hz-16k.wav","wb+");
    if (!cos_050Hz16k){
        printf("cos_050Hz16k fail\n");
        return 0;
    }
    else{
        fwrite(&header16k, sizeof(header16k), 1 ,cos_050Hz16k );//Write the header of Wav_RIFF
        fwrite(wav1, sizeof(short), 16000 ,cos_050Hz16k );//Data writing®×
    }
    fclose(cos_050Hz16k);


    //cos_200Hz_16k
    FILE* cos_200Hz16k =fopen("cos_200Hz-16k.wav","wb+");
    if (!cos_200Hz16k){
        printf("cos_200Hz16k fail\n");
        return 0;
    }
    else{
        fwrite(&header16k, sizeof(header16k), 1 ,cos_200Hz16k );
        fwrite(&wav2, sizeof(short), 16000 ,cos_200Hz16k );
    }
    fclose(cos_200Hz16k);


    //cos_055Hz_16k
    FILE* cos_055Hz16k =fopen("cos_055Hz-16k.wav","wb+");
    if (!cos_055Hz16k){
        printf("cos_055Hz16k fail\n");
        return 0;
    }
    else{
        fwrite(&header16k, sizeof(header16k), 1 ,cos_055Hz16k );
        fwrite(wav3, sizeof(short), 16000 ,cos_055Hz16k );
    }
    fclose(cos_055Hz16k);


    //cos_220Hz_16k
    FILE* cos_220Hz16k =fopen("cos_220Hz-16k.wav","wb+");
    if (!cos_220Hz16k){
        printf("cos_220Hz16k fail\n");
        return 0;
    }
    else{
        fwrite(&header16k, sizeof(header16k), 1 ,cos_220Hz16k );
        fwrite(wav4, sizeof(short), 16000 ,cos_220Hz16k );
    }
    fclose(cos_220Hz16k);


    //cos_050Hz_8k
    FILE* cos_050Hz8k =fopen("cos_050Hz-8k.wav","wb+");
    if (!cos_050Hz8k){
        printf("cos_050Hz8k fail\n");
        return 0;
    }
    else{
        fwrite(&header8k, sizeof(header8k), 1 ,cos_050Hz8k );
        fwrite(wav5, sizeof(short), 8000 ,cos_050Hz8k );
    }
    fclose(cos_050Hz8k);


    //cos_200Hz_8k
    FILE* cos_200Hz8k =fopen("cos_200Hz-8k.wav","wb+");
    if (!cos_200Hz8k){
        printf("cos_200Hz8k fail\n");
        return 0;
    }
    else{
        fwrite(&header8k, sizeof(header8k), 1 ,cos_200Hz8k );
        fwrite(wav6, sizeof(short), 8000 ,cos_200Hz8k );
    }
    fclose(cos_200Hz8k);


    //cos_055Hz_8k
    FILE* cos_055Hz8k =fopen("cos_055Hz-8k.wav","wb+");
    if (!cos_055Hz8k){
        printf("cos_055Hz8k fail\n");
        return 0;
    }
    else{
        fwrite(&header8k, sizeof(header8k), 1 ,cos_055Hz8k );
        fwrite(wav7, sizeof(short), 8000 ,cos_055Hz8k );
    }
    fclose(cos_055Hz8k);


    //cos_220Hz_8k
    FILE* cos_220Hz8k =fopen("cos_220Hz-8k.wav","wb+");
    if (!cos_220Hz8k){
        printf("cos_220Hz8k fail\n");
        return 0;
    }
    else{
        fwrite(&header8k, sizeof(header8k), 1 ,cos_220Hz8k );
        fwrite(wav8, sizeof(short), 8000 ,cos_220Hz8k );
    }
    fclose(cos_220Hz8k);

    //Create text files for saving set1~set4 ascii files
    FILE* fwav1set1 = fopen("cos_050Hz-16k.Set1.txt","wb+");
    FILE* fwav1set2 = fopen("cos_050Hz-16k.Set2.txt","wb+");
    FILE* fwav1set3 = fopen("cos_050Hz-16k.Set3.txt","wb+");
    FILE* fwav1set4 = fopen("cos_050Hz-16k.Set4.txt","wb+");

    //cos050Hz16k_set1:rectangular function window
    for(i=0;i+80<16000;i+=80){

            for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav1[n+i]*cos((2*PI*n*k) / 128); //DFT
                        Im+=wav1[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav1set1,"%f,",wav1set1dft[k+i]);
            }
            fprintf(fwav1set1,"\n");
    }
    fclose(fwav1set1);

    //cos050Hz16k_set2:hamming window
    for(i=0;i+80<16000;i+=80){

            for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav1ham[n+i]=wav1[n+i]*(0.54-0.46*cos((2*PI*n)/79));
                        Re+=wav1ham[n+i]*cos((2*PI*n*k) / 128);
                        Im+=wav1ham[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav1set2,"%f,",wav1set1dft[k+i]);

            }
            fprintf(fwav1set2,"\n");
    }
    fclose(fwav1set2);

    //cos050Hz16k_set3:rectangular function window
    for(i=0;i+160<16000;i+=160){

            for(k=0;k<512;k++){

           		for(n=0 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav1[n+i]*cos((2*PI*n*k) / 512);
                        Im-=wav1[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav1set3,"%f,",wav1set1dft[k+i]);
            }
            fprintf(fwav1set3,"\n");

    }
    fclose(fwav1set3);

    //cos050Hz16k_set4:hamming window
    for(i=0;i+160<16000;i+=160){

           for(k=0;k<512;k++){

                for(n=0 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav1ham[n+i]=wav1[n+i]*(0.54-0.46*cos((2*PI*n)/319));
                        Re+=wav1ham[n+i]*cos((2*PI*n*k) / 512);
                        Im-=wav1ham[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav1set4,"%f,",wav1set1dft[k+i]);

            }

            fprintf(fwav1set4,"\n");
    }
    fclose(fwav1set4);

    //Create text files for saving set1~set4 ascii files
    FILE* fwav2set1 = fopen("cos_200Hz-16k.Set1.txt","wb+");
    FILE* fwav2set2 = fopen("cos_200Hz-16k.Set2.txt","wb+");
    FILE* fwav2set3 = fopen("cos_200Hz-16k.Set3.txt","wb+");
    FILE* fwav2set4 = fopen("cos_200Hz-16k.Set4.txt","wb+");

    //cos200Hz16k_set1:rectangular function window
    for(i=0;i+80<16000;i+=80){

        for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav2[n+i]*cos((2*PI*n*k) / 128);
                        Im+=wav2[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav2set1,"%f,",wav1set1dft[k+i]);
            }
            fprintf(fwav2set1,"\n");
    }
    fclose(fwav2set1);

    //cos200Hz16k_set2:hamming window
    for(i=0;i+80<16000;i+=80){

        for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav1ham[n+i]=wav2[n+i]*(0.54-0.46*cos((2*PI*n)/79));
                        Re+=wav1ham[n+i]*cos((2*PI*n*k) / 128);
                        Im+=wav1ham[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav2set2,"%f,",wav1set1dft[k+i]);

            }
            fprintf(fwav2set2,"\n");
    }
    fclose(fwav2set2);

    //cos200Hz16k_set3:rectangular function window
    for(i=0;i+160<16000;i+=160){

        for(k=0;k<512;k++){

                for(n=0 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav2[n+i]*cos((2*PI*n*k) / 512);
                        Im+=wav2[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav2set3,"%f,",wav1set1dft[k+i]);
            }
            fprintf(fwav2set3,"\n");

    }
    fclose(fwav2set3);

    //cos200Hz16k_set4:hamming window
    for(i=0;i+160<16000;i+=160){

        for(k=0;k<512;k++){

                for(n=0 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                        else{wav1ham[n+i]=wav2[n+i]*(0.54-0.46*cos((2*PI*n)/319));
                        Re+=wav1ham[n+i]*cos((2*PI*n*k) / 512);
                        Im+=wav1ham[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav2set4,"%f,",wav1set1dft[k+i]);

            }
            fprintf(fwav2set4,"\n");
    }
    fclose(fwav2set4);

    //Create text files for saving set1~set4 ascii files
    FILE* fwav3set1 = fopen("cos_055Hz-16k.Set1.txt","wb+");
    FILE* fwav3set2 = fopen("cos_055Hz-16k.Set2.txt","wb+");
    FILE* fwav3set3 = fopen("cos_055Hz-16k.Set3.txt","wb+");
    FILE* fwav3set4 = fopen("cos_055Hz-16k.Set4.txt","wb+");

    //cos055Hz16k_set1:rectangular function window
    for(i=0;i+80<16000;i+=80){

            for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav3[n+i]*cos((2*PI*n*k) / 128);
                        Im+=wav3[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav3set1,"%f,",wav1set1dft[k+i]);
            }
            fprintf(fwav3set1,"\n");
    }
    fclose(fwav3set1);

    //cos055Hz16k_set2:hamming window
    for(i=0;i+80<16000;i+=80){

            for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav1ham[n+i]=wav3[n+i]*(0.54-0.46*cos((2*PI*n)/79));
                        Re+=wav1ham[n+i]*cos((2*PI*n*k) / 128);
                        Im+=wav1ham[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav3set2,"%f,",wav1set1dft[k+i]);

            }
            fprintf(fwav3set2,"\n");
    }
    fclose(fwav3set2);

    //cos055Hz16k_set3:rectangular function window
    for(i=0;i+160<16000;i+=160){

            for(k=0;k<512;k++){

                for(n=0 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav3[n+i]*cos((2*PI*n*k) / 512);
                        Im+=wav3[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav3set3,"%f,",wav1set1dft[k+i]);
            }
            fprintf(fwav3set3,"\n");

    }
    fclose(fwav3set3);

    //cos055Hz16k_set4:hamming window
    for(i=0;i+160<16000;i+=160){

        for(k=0;k<512;k++){

                for(n=0 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav1ham[n+i]=wav3[n+i]*(0.54-0.46*cos((2*PI*n)/319));
                        Re+=wav1ham[n+i]*cos((2*PI*n*k) / 512);
                        Im+=wav1ham[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav3set4,"%f,",wav1set1dft[k+i]);

            }
            fprintf(fwav3set4,"\n");
    }
    fclose(fwav3set4);

    //Create text files for saving set1~set4 ascii files
    FILE* fwav4set1 = fopen("cos_220Hz-16k.Set1.txt","wb+");
    FILE* fwav4set2 = fopen("cos_220Hz-16k.Set2.txt","wb+");
    FILE* fwav4set3 = fopen("cos_220Hz-16k.Set3.txt","wb+");
    FILE* fwav4set4 = fopen("cos_220Hz-16k.Set4.txt","wb+");

    //cos220Hz16k_set1:rectangular function window
    for(i=0;i+80<16000;i+=80){

            for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav4[n+i]*cos((2*PI*n*k) / 128);
                        Im+=wav4[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav4set1,"%f,",wav1set1dft[k+i]);
            }
            fprintf(fwav4set1,"\n");
    }
    fclose(fwav4set1);

    //cos220Hz16k_set2:hamming window
    for(i=0;i+80<16000;i+=80){

            for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav1ham[n+i]=wav4[n+i]*(0.54-0.46*cos((2*PI*n)/79));
                        Re+=wav1ham[n+i]*cos((2*PI*n*k) / 128);
                        Im+=wav1ham[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav4set2,"%f,",wav1set1dft[k+i]);

            }
            fprintf(fwav4set2,"\n");
    }
    fclose(fwav4set2);

    //cos220Hz16k_set3:rectangular function window
    for(i=0;i+160<16000;i+=160){

            for(k=0;k<512;k++){

                for(n=0 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav4[n+i]*cos((2*PI*n*k) / 512);
                        Im+=wav4[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav4set3,"%f,",wav1set1dft[k+i]);
            }
            fprintf(fwav4set3,"\n");

    }
    fclose(fwav4set3);

    //cos220Hz16k_set4:hamming window
    for(i=0;i+160<16000;i+=160){

        for(k=0;k<512;k++){

                for(n=10 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav1ham[n+i]=wav4[n+i]*(0.54-0.46*cos((2*PI*n)/319));
                        Re+=wav1ham[n+i]*cos((2*PI*n*k) / 512);
                        Im+=wav1ham[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                wav1set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav4set4,"%f,",wav1set1dft[k+i]);

            }
            fprintf(fwav4set4,"\n");
    }
    fclose(fwav4set4);

    //Create text files for saving set1~set4 ascii files
    FILE* fwav5set1 = fopen("cos_050Hz-8k.Set1.txt","wb+");
    FILE* fwav5set2 = fopen("cos_050Hz-8k.Set2.txt","wb+");
    FILE* fwav5set3 = fopen("cos_050Hz-8k.Set3.txt","wb+");
    FILE* fwav5set4 = fopen("cos_050Hz-8k.Set4.txt","wb+");

   //cos050Hz8k_set1:rectangular function window
    for(i=0;i+40<8000;i+=40){

            for(k=0;k<64;k++){

                for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                    if(n>40){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav5[n+i]*cos((2*PI*n*k) / 64);
                        Im+=wav5[n+i]*sin((2*PI*n*k) / 64);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav5set1,"%f,",wav5set1dft[k+i]);
            }
            fprintf(fwav5set1,"\n");
    }
    fclose(fwav5set1);

    //cos050Hz8k_set2:hamming window
    for(i=0;i+40<8000;i+=40){


            for(k=0;k<64;k++){

                for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                    if(n>40){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav5ham[n+i]=wav5[n+i]*(0.54-0.46*cos((2*PI*n)/39));
                        Re+=wav5ham[n+i]*cos((2*PI*n*k) / 64 );
                        Im+=wav5ham[n+i]*sin((2*PI*n*k) / 64 );
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav5set2,"%f,",wav5set1dft[k+i]);

            }
            fprintf(fwav5set2,"\n");
    }
    fclose(fwav5set2);

    //cos050Hz8k_set3:rectangular function window
    for(i=0;i+80<8000;i+=80){

            for(k=0;k<256;k++){

           		for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                    if(n>160){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav5[n+i]*cos((2*PI*n*k) / 256);
                        Im+=wav5[n+i]*sin((2*PI*n*k) / 256);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav5set3,"%f,",wav5set1dft[k+i]);
            }
            fprintf(fwav5set3,"\n");

    }
    fclose(fwav5set3);

    //cos050Hz8k_set4:hamming window
    for(i=0;i+80<8000;i+=80){

            for(k=0;k<256;k++){

                for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                    if(n>160){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav5ham[n+i]=wav5[n+i]*(0.54-0.46*cos((2*PI*n)/159));
                        Re+=wav5ham[n+i]*cos((2*PI*n*k) / 256);
                        Im+=wav5ham[n+i]*sin((2*PI*n*k) / 256);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav5set4,"%f,",wav5set1dft[k+i]);

            }
            fprintf(fwav5set4,"\n");
    }
    fclose(fwav5set4);

    //Create text files for saving set1~set4 ascii files
    FILE* fwav6set1 = fopen("cos_200Hz-8k.Set1.txt","wb+");
    FILE* fwav6set2 = fopen("cos_200Hz-8k.Set2.txt","wb+");
    FILE* fwav6set3 = fopen("cos_200Hz-8k.Set3.txt","wb+");
    FILE* fwav6set4 = fopen("cos_200Hz-8k.Set4.txt","wb+");

   //cos200Hz8k_set1:rectangular function window
    for(i=0;i+40<8000;i+=40){

            for(k=0;k<64;k++){

                for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                    if(n>40){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav6[n+i]*cos((2*PI*n*k) / 64);
                        Im+=wav6[n+i]*sin((2*PI*n*k) / 64);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav6set1,"%f,",wav5set1dft[k+i]);
            }
            fprintf(fwav6set1,"\n");
    }
    fclose(fwav6set1);

    //cos200Hz8k_set2:hamming window
    for(i=0;i+40<8000;i+=40){

            for(k=0;k<64;k++){

                for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                    if(n>40){
                        Re+=0;
                        Im+=0;
                    }
                    else{wav5ham[n+i]=wav6[n+i]*(0.54-0.46*cos((2*PI*n)/39));
                        Re+=wav5ham[n+i]*cos((2*PI*n*k) / 64 );
                        Im+=wav5ham[n+i]*sin((2*PI*n*k) / 64 );
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav6set2,"%f,",wav5set1dft[k+i]);

            }
            fprintf(fwav6set2,"\n");
    }
    fclose(fwav6set2);

    //cos200Hz8k_set3:rectangular function window
    for(i=0;i+80<8000;i+=80){

            for(k=0;k<256;k++){

           		for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                    if(n>160){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav6[n+i]*cos((2*PI*n*k) / 256);
                        Im+=wav6[n+i]*sin((2*PI*n*k) / 256);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav6set3,"%f,",wav5set1dft[k+i]);
            }
            fprintf(fwav6set3,"\n");

    }
    fclose(fwav6set3);

    //cos200Hz8k_set4:hamming window
    for(i=0;i+80<8000;i+=80){

            for(k=0;k<256;k++){

                for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                    if(n>160){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav5ham[n+i]=wav6[n+i]*(0.54-0.46*cos((2*PI*n)/159));
                        Re+=wav5ham[n+i]*cos((2*PI*n*k) / 256);
                        Im+=wav5ham[n+i]*sin((2*PI*n*k) / 256);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav6set4,"%f,",wav5set1dft[k+i]);

            }
            fprintf(fwav6set4,"\n");
    }
    fclose(fwav6set4);


    //Create text files for saving set1~set4 ascii files
    FILE* fwav7set1 = fopen("cos_055Hz-8k.Set1.txt","wb+");
    FILE* fwav7set2 = fopen("cos_055Hz-8k.Set2.txt","wb+");
    FILE* fwav7set3 = fopen("cos_055Hz-8k.Set3.txt","wb+");
    FILE* fwav7set4 = fopen("cos_055Hz-8k.Set4.txt","wb+");

    //cos055Hz8k_set1:rectangular function window
    for(i=0;i+40<8000;i+=40){

            for(k=0;k<64;k++){

                for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                    if(n>40){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav7[n+i]*cos((2*PI*n*k) / 64);
                        Im+=wav7[n+i]*sin((2*PI*n*k) / 64);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav7set1,"%f,",wav5set1dft[k+i]);
            }
            fprintf(fwav7set1,"\n");
    }
    fclose(fwav7set1);

    //cos055Hz8k_set2:hamming window
    for(i=0;i+40<8000;i+=40){

            for(k=0;k<64;k++){

                for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                    if(n>40){
                        Re+=0;
                        Im+=0;
                    }
                    else{wav5ham[n+i]=wav7[n+i]*(0.54-0.46*cos((2*PI*n)/39));
                        Re+=wav5ham[n+i]*cos((2*PI*n*k) / 64 );
                        Im+=wav5ham[n+i]*sin((2*PI*n*k) / 64 );
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav7set2,"%f,",wav5set1dft[k+i]);

            }
            fprintf(fwav7set2,"\n");
    }
    fclose(fwav7set2);

    //cos055Hz8k_set3:rectangular function window
    for(i=0;i+80<8000;i+=80){

            for(k=0;k<256;k++){

           		for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                    if(n>160){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav7[n+i]*cos((2*PI*n*k) / 256);
                        Im+=wav7[n+i]*sin((2*PI*n*k) / 256);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav7set3,"%f,",wav5set1dft[k+i]);
            }
            fprintf(fwav7set3,"\n");

    }
    fclose(fwav7set3);

    //cos055Hz8k_set4:hamming window
    for(i=0;i+80<8000;i+=80){

            for(k=0;k<256;k++){

                for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                    if(n>160){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav5ham[n+i]=wav7[n+i]*(0.54-0.46*cos((2*PI*n)/159));
                        Re+=wav5ham[n+i]*cos((2*PI*n*k) / 256);
                        Im+=wav5ham[n+i]*sin((2*PI*n*k) / 256);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav7set4,"%f,",wav5set1dft[k+i]);

            }
            fprintf(fwav7set4,"\n");
    }
    fclose(fwav7set4);

   //Create text files for saving set1~set4 ascii files
    FILE* fwav8set1 = fopen("cos_220Hz-8k.Set1.txt","wb+");
    FILE* fwav8set2 = fopen("cos_220Hz-8k.Set2.txt","wb+");
    FILE* fwav8set3 = fopen("cos_220Hz-8k.Set3.txt","wb+");
    FILE* fwav8set4 = fopen("cos_220Hz-8k.Set4.txt","wb+");

    //cos220Hz8k_set1:rectangular function window
    for(i=0;i+40<8000;i+=40){

            for(k=0;k<64;k++){

                for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                    if(n>40){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav8[n+i]*cos((2*PI*n*k) / 64);
                        Im+=wav8[n+i]*sin((2*PI*n*k) / 64);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav8set1,"%f,",wav5set1dft[k+i]);
            }
            fprintf(fwav8set1,"\n");
    }
    fclose(fwav8set1);

    //cos220Hz8k_set2:hamming window
    for(i=0;i+40<8000;i+=40){

            for(k=0;k<64;k++){

                for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                    if(n>40){
                        Re+=0;
                        Im+=0;
                    }
                    else{wav5ham[n+i]=wav8[n+i]*(0.54-0.46*cos((2*PI*n)/39));
                        Re+=wav5ham[n+i]*cos((2*PI*n*k) / 64 );
                        Im+=wav5ham[n+i]*sin((2*PI*n*k) / 64 );
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav8set2,"%f,",wav5set1dft[k+i]);

            }
            fprintf(fwav8set2,"\n");
    }
    fclose(fwav8set2);

    //cos220Hz8k_set3:rectangular function window
    for(i=0;i+80<8000;i+=80){

            for(k=0;k<256;k++){

                for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                    if(n>160){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=wav8[n+i]*cos((2*PI*n*k) / 256);
                        Im+=wav8[n+i]*sin((2*PI*n*k) / 256);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav8set3,"%f,",wav5set1dft[k+i]);
            }
            fprintf(fwav8set3,"\n");

    }
    fclose(fwav8set3);

    //cos220Hz8k_set4:hamming window
    for(i=0;i+80<8000;i+=80){

            for(k=0;k<256;k++){

                for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                    if(n>160){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        wav5ham[n+i]=wav8[n+i]*(0.54-0.46*cos((2*PI*n)/159));
                        Re+=wav5ham[n+i]*cos((2*PI*n*k) / 256);
                        Im+=wav5ham[n+i]*sin((2*PI*n*k) / 256);
                    }
                }
                wav5set1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fwav8set4,"%f,",wav5set1dft[k+i]);

            }
            fprintf(fwav8set4,"\n");
    }
    fclose(fwav8set4);


   //Create text files for saving set1~set4 ascii files
    FILE* fvowel16kset1 = fopen("vowel-16k.Set1.txt","wb+");
    FILE* fvowel16kset2 = fopen("vowel-16k.Set2.txt","wb+");
    FILE* fvowel16kset3 = fopen("vowel-16k.Set3.txt","wb+");
    FILE* fvowel16kset4 = fopen("vowel-16k.Set4.txt","wb+");

    //vowel-16k_set1:rectangular function window
    for(i=0;i+80<53000;i+=80){

           for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=vowel16kdata[n+i]*cos((2*PI*n*k) / 128);
                        Im+=vowel16kdata[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                vowel16kset1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fvowel16kset1,"%f,",vowel16kset1dft[k+i]);
            }
            fprintf(fvowel16kset1,"\n");
    }
    fclose(fvowel16kset1);

    //vowel-16k_set2:hamming window
    for(i=0;i+80<53000;i+=80){

        for(k=0;k<128;k++){

                for(n=0 , Re=0 , Im=0 ; n<128 ;n++){
                    if(n>80){
                        Re+=0;
                        Im+=0;
                    }
                    else{vowel16kham[n+i]=vowel16kdata[n+i]*(0.54-0.46*cos((2*PI*n)/79));
                        Re+=vowel16kham[n+i]*cos((2*PI*n*k) / 128);
                        Im+=vowel16kham[n+i]*sin((2*PI*n*k) / 128);
                    }
                }
                vowel16kset1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fvowel16kset2,"%f,",vowel16kset1dft[k+i]);

            }
            fprintf(fvowel16kset2,"\n");
    }
    fclose(fvowel16kset2);

    //vowel-16k_set3:rectangular function window
    for(i=0;i+160<53000;i+=160){

            for(k=0;k<512;k++){

           		for(n=0 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=vowel16kdata[n+i]*cos((2*PI*n*k) / 512);
                        Im+=vowel16kdata[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                vowel16kset1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fvowel16kset3,"%f,",vowel16kset1dft[k+i]);
            }
            fprintf(fvowel16kset3,"\n");

    }
    fclose(fvowel16kset3);

    //vowel-16k_set4:hamming window
    for(i=0;i+160<53000;i+=160){

            for(k=0;k<512;k++){

                for(n=0 , Re=0 , Im=0 ; n<512 ;n++){
                    if(n>320){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        vowel16kham[n+i]=vowel16kdata[n+i]*(0.54-0.46*cos((2*PI*n)/319));
                        Re+=vowel16kham[n+i]*cos((2*PI*n*k) / 512);
                        Im+=vowel16kham[n+i]*sin((2*PI*n*k) / 512);
                    }
                }
                vowel16kset1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fvowel16kset4,"%f,",vowel16kset1dft[k+i]);

            }
            fprintf(fvowel16kset4,"\n");
    }
    fclose(fvowel16kset4);

    //Create text files for saving set1~set4 ascii files
    FILE* fvowel8kset1 = fopen("vowel-8k.Set1.txt","wb+");
    FILE* fvowel8kset2 = fopen("vowel-8k.Set2.txt","wb+");
    FILE* fvowel8kset3 = fopen("vowel-8k.Set3.txt","wb+");
    FILE* fvowel8kset4 = fopen("vowel-8k.Set4.txt","wb+");

    //vowel-8k_set1:rectangular function window
    for(i=0;i+40<30000;i+=40){

            for(k=0;k<64;k++){

                for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                    if(n>40){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        Re+=vowel8kdata[n+i]*cos((2*PI*n*k) / 64);
                        Im+=vowel8kdata[n+i]*sin((2*PI*n*k) / 64);
                    }
                }
                vowel8kset1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fvowel8kset1,"%f,",vowel8kset1dft[k+i]);
            }
            fprintf(fvowel8kset1,"\n");
    }
    fclose(fvowel8kset1);

    //vowel-8k_set2:hamming window
    for(i=0;i+40<30000;i+=40){

        for(k=0;k<64;k++){

                    for(n=0 , Re=0 , Im=0 ; n<64 ;n++){
                        if(n>40){
                            Re+=0;
                            Im+=0;
                        }
                        else{
                            vowel8kham[n+i]=vowel8kdata[n+i]*(0.54-0.46*cos((2*PI*n)/39));
                            Re+=vowel8kham[n+i]*cos((2*PI*n*k) / 64);
                            Im+=vowel8kham[n+i]*sin((2*PI*n*k) / 64);
                        }
                    }
                    vowel8kset1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                    fprintf(fvowel8kset2,"%f,",vowel8kset1dft[k+i]);
            }
            fprintf(fvowel8kset2,"\n");
    }
    fclose(fvowel8kset2);

    //vowel-8k_set3:rectangular function window
    for(i=0;i+80<30000;i+=80){

            for(k=0;k<256;k++){

                    for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                        if(n>160){
                            Re+=0;
                            Im+=0;
                        }
                        else{
                            Re+=vowel8kdata[n+i]*cos((2*PI*n*k) / 256);
                            Im+=vowel8kdata[n+i]*sin((2*PI*n*k) / 256);
                        }
                    }
                    vowel8kset1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                    fprintf(fvowel8kset3,"%f,",vowel8kset1dft[k+i]);
            }
            fprintf(fvowel8kset3,"\n");

    }
    fclose(fvowel8kset3);

    //vowel-8k_set4:hamming window
    for(i=0;i+80<30000;i+=80){

            for(k=0;k<256;k++){

                for(n=0 , Re=0 , Im=0 ; n<256 ;n++){
                    if(n>160){
                        Re+=0;
                        Im+=0;
                    }
                    else{
                        vowel8kham[n+i]=vowel8kdata[n+i]*(0.54-0.46*cos((2*PI*n)/159));
                        Re+=vowel8kham[n+i]*cos((2*PI*n*k) / 256);
                        Im+=vowel8kham[n+i]*sin((2*PI*n*k) / 256);
                    }
                }
                vowel8kset1dft[k+i] = 20 * log10(sqrt(pow(Re,2)+pow(Im,2)));
                fprintf(fvowel8kset4,"%f,",vowel8kset1dft[k+i]);

            }
            fprintf(fvowel8kset4,"\n");
    }
    fclose(fvowel8kset4);
	
	printf("All is well.\n");
	
return 0;

}
