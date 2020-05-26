#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
float PI=3.1415927;

/*construct a structure of BMP header*/
typedef struct Bmpheader{
    unsigned short identifier; // 0x0000
    unsigned int filesize; // 0x0002
    unsigned short reserved; // 0x0006
    unsigned short reserved2;
    unsigned int bitmap_dataoffset; // 0x000A
    unsigned int bitmap_headersize; // 0x000E
    unsigned int width; // 0x0012
    unsigned int height; // 0x0016
    unsigned short planes; // 0x001A
    unsigned short bits_perpixel; // 0x001C
    unsigned int compression; // 0x001E
    unsigned int bitmap_datasize; // 0x0022
    unsigned int hresolution; // 0x0026
    unsigned int vresolution; // 0x002A
    unsigned int usedcolors; // 0x002E
    unsigned int importantcolors; // 0x0032
    unsigned int palette; // 0x0036
} Bitmap;


/*construct a structure of RGB*/
typedef struct RGB{
    int R;
    int G;
    int B;
} ImgRGB;

Bitmap readheader(FILE* fp);
ImgRGB** malloc_2D(int row, int col);
void InputData(FILE* fp,ImgRGB **array,int H,int W);
void output_bmp(ImgRGB **RGB,FILE* outfile,Bitmap bmpheader);

typedef struct YCbCr{
    float Y;
    float Cb;
    float Cr;
} ImgYCbCr;


typedef struct YCbCrDCT{
    float YDCT;
    float CbDCT;
    float CrDCT;
} ImgYCbCrDCT;


typedef struct YCbCrQuan{
    float YQuan;
    float CbQuan;
    float CrQuan;
} ImgYCbCrQuan;


Bitmap readheader(FILE* fp);
ImgRGB** malloc_2D(int row, int col);
ImgYCbCr **malloc_YCbCr(int row, int col);
ImgYCbCrDCT** malloc_YCbCrDCT(int row, int col);
ImgYCbCrQuan** malloc_YCbCrQuan(int row, int col);

void InputData(FILE* fp,ImgRGB **array,int H,int W);
void output_bmp(ImgRGB **RGB,FILE* outfile,Bitmap bmpheader);
void RGBToYCbCr (ImgRGB **RGBArray, ImgYCbCr**YCbCrArray, int H, int W);
void FDCT(ImgYCbCr **YCbCrArray,ImgYCbCrDCT **YCbCrDCTArray,int H,int W);
void Quan(ImgYCbCrDCT **YCbCrDCTArray,ImgYCbCrQuan **YCbCrQuanArray,int H,int W);
void DQuan(ImgYCbCrQuan **YCbCrQuanArray,ImgYCbCrDCT **YCbCrDCTArray,int H, int W );
void IDCT(ImgYCbCrDCT **YCbCrDCTArray,ImgYCbCr **YCbCrArray,int H,int W);
void YCbCrToRGB (ImgYCbCr **YCbCrArray, ImgRGB **RGBArray, int H, int W);

#define Height_8X 4032
#define Width_8X 3024



int main(int argc, char *argv[])
{
	FILE* fp=fopen(argv[1],"rb");
	//FILE* fp=fopen("input.bmp","rb");
    FILE *fw=fopen(argv[2],"wb");
    //FILE *fw=fopen("out.bmp","wb");
	int i,j;


    //read header
    Bitmap bmpheader=readheader(fp);

    ImgRGB **Data_RGB=malloc_2D(bmpheader.height,bmpheader.width);

	ImgYCbCr **Data_YCbCr=malloc_YCbCr(Height_8X, Width_8X);

    ImgYCbCrDCT **Data_YCbCrDCT=malloc_YCbCrDCT(Height_8X, Width_8X);

	ImgYCbCrQuan **Data_YCbCrQuan=malloc_YCbCrQuan(Height_8X, Width_8X);


	//read data
    InputData(fp,Data_RGB,bmpheader.height,bmpheader.width);

	//printf("\n     first RGB 8x8\n");

	/*for(i=0;i<4;i++){
		for(j=0;j<4;j++){

			printf("%d ",Data_RGB[i][j].R);
			printf("%d ",Data_RGB[i][j].G);
			printf("%d     ",Data_RGB[i][j].B);

        }
		printf("\n");
    }
    */


    /***========RGB->YCbCr=========***/
	RGBToYCbCr (Data_RGB, Data_YCbCr, bmpheader.height,bmpheader.width);

	/*printf("\n first YCbCr 8x8\n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){

			printf("%f ",Data_YCbCr[i][j].Y);
			printf("%f ",Data_YCbCr[i][j].Cb);
			printf("%f      ",Data_YCbCr[i][j].Cr);

        }
		printf("\n");
    }*/
    /***=============DCT==============***/
	FDCT(Data_YCbCr,Data_YCbCrDCT,Height_8X, Width_8X) ;
	/*for(i=0;i<4;i++){
		for(j=0;j<4;j++){

			printf("%f ",Data_YCbCrDCT[i][j].YDCT);
			printf("%f ",Data_YCbCrDCT[i][j].CbDCT);
			printf("%f     ",Data_YCbCrDCT[i][j].CrDCT);

        }
		printf("\n");
    }*/

    /***============Quantization===========***/
	Quan(Data_YCbCrDCT,Data_YCbCrQuan,Height_8X, Width_8X);
    /*for(i=0;i<4;i++){
        for(j=0;j<4;j++){

			printf("%f ",Data_YCbCrQuan[i][j].YQuan);
			printf("%f ",Data_YCbCrQuan[i][j].CbQuan);
			printf("%f ",Data_YCbCrQuan[i][j].CrQuan);

        }
		printf("\n");
    }
*/

    /***=======Inverse Quantization=========***/
	DQuan(Data_YCbCrQuan,Data_YCbCrDCT,Height_8X, Width_8X);

   /*
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){

			printf("%f ",Data_YCbCrDCT[i][j].YDCT);
			printf("%f ",Data_YCbCrDCT[i][j].CbDCT);
			printf("%f     ",Data_YCbCrDCT[i][j].CrDCT);

        }
		printf("\n");
    }
*/
    /***============= IDCT ============***/
    IDCT(Data_YCbCrDCT,Data_YCbCr,Height_8X,Width_8X);
/*

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){

			printf("%f ",Data_YCbCr[i][j].Y);
			printf("%f ",Data_YCbCr[i][j].Cb);
			printf("%f      ",Data_YCbCr[i][j].Cr);
        }
		printf("\n");
    }
*/
    /***======Invert to RGB 8x8=======***/
	YCbCrToRGB (Data_YCbCr, Data_RGB, bmpheader.height,bmpheader.width);
/*
    for(i=0;i<4;i++){
		for(j=0;j<4;j++){

			printf("%d ",Data_RGB[i][j].R);
			printf("%d ",Data_RGB[i][j].G);
			printf("%d     ",Data_RGB[i][j].B);

        }
		printf("\n");
    }
*/

    /***====output bmp===***/
    printf("output bmp...\n");
	output_bmp(Data_RGB,fw,bmpheader);
    printf("Done.");

	free(Data_RGB);
	free(Data_YCbCr);
	free(Data_YCbCrDCT);
	free(Data_YCbCrQuan);

	return 0;
}


/*read header*/
Bitmap readheader(FILE* fp){
    Bitmap x;
    fread(&x.identifier,sizeof(x.identifier),1,fp);
    fread(&x.filesize,sizeof(x.filesize),1,fp);
    fread(&x.reserved,sizeof(x.reserved),1,fp);
    fread(&x.reserved2,sizeof(x.reserved2),1,fp);
    fread(&x.bitmap_dataoffset,sizeof(x.bitmap_dataoffset),1,fp);
    fread(&x.bitmap_headersize,sizeof(x.bitmap_headersize),1,fp);
    fread(&x.width,sizeof(x.width),1,fp);
    fread(&x.height,sizeof(x.height),1,fp);
    fread(&x.planes,sizeof(x.planes),1,fp);
    fread(&x.bits_perpixel,sizeof(x.bits_perpixel),1,fp);
    fread(&x.compression,sizeof(x.compression),1,fp);
    fread(&x.bitmap_datasize,sizeof(x.bitmap_datasize),1,fp);
    fread(&x.hresolution,sizeof(x.hresolution),1,fp);
    fread(&x.vresolution,sizeof(x.vresolution),1,fp);
    fread(&x.usedcolors,sizeof(x.usedcolors),1,fp);
    fread(&x.importantcolors,sizeof(x.importantcolors),1,fp);
    return x;
}

/*put input data without header into RGB structure*/
int H,W,i,j;
void InputData(FILE* fp,ImgRGB **array,int H,int W){
    int temp;
    for( i=0;i<H;i++){
        for( j=0;j<W;j++){
            temp=fgetc(fp);
            array[i][j].B=temp;
            temp=fgetc(fp);
            array[i][j].G=temp;
            temp=fgetc(fp);
            array[i][j].R=temp;
        }
    }
}

/***making two dimensions memory locate array***/
ImgRGB** malloc_2D(int row, int col){
    ImgRGB **Array, *Data;
    int i;
    Array=(ImgRGB**)malloc(row*sizeof(ImgRGB *));
    Data=(ImgRGB*)malloc(row*col*sizeof(ImgRGB));
    for(i=0; i<row; i++,Data+=col){
        Array[i] = Data;
    }
    return Array;
}

/***memory for YCbCr***/
ImgYCbCr** malloc_YCbCr(int row, int col){
    ImgYCbCr **Array, *Data;
    int i;
    Array=(ImgYCbCr**)malloc(row*sizeof(ImgYCbCr *));
    Data=(ImgYCbCr*)calloc(row*col,sizeof(ImgYCbCr));
    for(i=0; i<row; i++,Data+=col){
        Array[i] = Data;
    }
    return Array;
}


ImgYCbCrDCT** malloc_YCbCrDCT(int row, int col){
    ImgYCbCrDCT **Array, *Data;
    int i;
    Array=(ImgYCbCrDCT**)malloc(row*sizeof(ImgYCbCrDCT *));
    Data=(ImgYCbCrDCT*)calloc(row*col,sizeof(ImgYCbCrDCT));
    for(i=0; i<row; i++,Data+=col){
        Array[i] = Data;
    }
    return Array;
}

ImgYCbCrQuan** malloc_YCbCrQuan(int row, int col){
    ImgYCbCrQuan **Array, *Data;
    int i;
    Array=(ImgYCbCrQuan**)malloc(row*sizeof(ImgYCbCrQuan *));
    Data=(ImgYCbCrQuan*)calloc(row*col,sizeof(ImgYCbCrQuan));
    for(i=0; i<row; i++,Data+=col){
        Array[i] = Data;
    }
    return Array;
}

void RGBToYCbCr (ImgRGB **RGBArray, ImgYCbCr**YCbCrArray, int H, int W) {
	int i,j;

   for( i=0;i<H;i++){
        for( j=0;j<W;j++){
            YCbCrArray[i][j].Y=0.299*RGBArray[i][j].R + 0.587*RGBArray[i][j].G + 0.114*RGBArray[i][j].B-128;
			YCbCrArray[i][j].Cb= 0.596*RGBArray[i][j].R  - 0.275*RGBArray[i][j].G - 0.321*RGBArray[i][j].B-128;
			YCbCrArray[i][j].Cr= 0.212*RGBArray[i][j].R - 0.523*RGBArray[i][j].G +0.311*RGBArray[i][j].B-128;
        }
    }
	return ;
}
void YCbCrToRGB (ImgYCbCr**YCbCrArray, ImgRGB **RGBArray, int H, int W) {
	int i,j;
	float R,G,B;


   for( i=0;i<H;i++){
       for( j=0;j<W;j++){
            YCbCrArray[i][j].Y=YCbCrArray[i][j].Y+128;
		    YCbCrArray[i][j].Cb=YCbCrArray[i][j].Cb+128;
		    YCbCrArray[i][j].Cr=YCbCrArray[i][j].Cr+128;

            R=YCbCrArray[i][j].Y + 0.956*YCbCrArray[i][j].Cb + 0.620*YCbCrArray[i][j].Cr;

            if(R>255.0) {R=255.0;}
            else if(R<0){R=0.0;}
        	RGBArray[i][j].R=(int)R;

            //printf("R= %f  %d\n",R, RGBArray[i][j].R);

			G=YCbCrArray[i][j].Y - 0.272*YCbCrArray[i][j].Cb - 0.647*YCbCrArray[i][j].Cr;
			if(G>255.0) {G=255.0;}
            else if(G<0){G=0.0;}
            RGBArray[i][j].G=(int)G;

            //printf("G= %f  %d\n",G, RGBArray[i][j].G);

            B=YCbCrArray[i][j].Y - 1.108*YCbCrArray[i][j].Cb +1.705*YCbCrArray[i][j].Cr;
            if(B>255.0) {B=255.0;}
            else if(B<0){B=0.0;}
            RGBArray[i][j].B=(int)B;

            //printf("B= %f  %d\n",B, RGBArray[i][j].B);

        }
    }
	return ;
}

/*output header and data*/
void output_bmp(ImgRGB **RGB,FILE* outfile,Bitmap bmpheader){

    fwrite(&bmpheader.identifier, sizeof(short), 1 , outfile);
    fwrite(&bmpheader.filesize, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.reserved, sizeof(short), 1 , outfile);
    fwrite(&bmpheader.reserved2, sizeof(short), 1 , outfile);
    fwrite(&bmpheader.bitmap_dataoffset, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.bitmap_headersize, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.width, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.height, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.planes, sizeof(short), 1 , outfile);
    fwrite(&bmpheader.bits_perpixel, sizeof(short), 1 , outfile);
    fwrite(&bmpheader.compression, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.bitmap_datasize, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.hresolution, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.vresolution, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.usedcolors, sizeof(int), 1 , outfile);
    fwrite(&bmpheader.importantcolors, sizeof(int), 1 , outfile);
    int x,y;
    for ( x=0; x<bmpheader.height; x++){
        for( y=0; y<bmpheader.width; y++){
            fwrite(&RGB[x][y].B, sizeof(char),1,outfile);
            fwrite(&RGB[x][y].G, sizeof(char),1,outfile);
            fwrite(&RGB[x][y].R, sizeof(char),1,outfile);
        }
    }
}

#define PI 3.141592658

void FDCT(ImgYCbCr **YCbCrArray,ImgYCbCrDCT **YCbCrDCTArray,int H,int W)
{
    int i,j,u,v,m,n;
    float sqrt_2 = sqrt(2.0);
    for(m=0;m<H;m+=8){
		//printf("m=%d ", m);
        for(n=0;n<W;n+=8){
		//printf("n=%d ", n);
            for(u=0;u<8;u++){
				//printf("u=%d ", u);
                for(v=0;v<8;v++){
					   for(i=0;i<8;i++){ //height
							for(j=0;j<8;j++){ //width
							//printf("j=%d ", j);
								YCbCrDCTArray[m+u][n+v].YDCT += YCbCrArray[m+i][n+j].Y* cos((2*i+1)*(u)*PI/(2*8)) * cos((2*j+1)*(v)*PI/(2*8))/4;
								YCbCrDCTArray[m+u][n+v].CbDCT += YCbCrArray[m+i][n+j].Cb* cos((2*i+1)*(u)*PI/(2*8)) * cos((2*j+1)*(v)*PI/(2*8))/4;
								YCbCrDCTArray[m+u][n+v].CrDCT += YCbCrArray[m+i][n+j].Cr* cos((2*i+1)*(u)*PI/(2*8)) * cos((2*j+1)*(v)*PI/(2*8))/4;
							}//for (j
						}//for (i
                    if(u==0){
                        YCbCrDCTArray[m+u][n+v].YDCT /= sqrt_2;
                        YCbCrDCTArray[m+u][n+v].CbDCT /= sqrt_2;
                        YCbCrDCTArray[m+u][n+v].CrDCT /= sqrt_2;
                    }
                    if(v==0){
                        YCbCrDCTArray[m+u][n+v].YDCT /= sqrt_2;
                        YCbCrDCTArray[m+u][n+v].CbDCT /= sqrt_2;
                        YCbCrDCTArray[m+u][n+v].CrDCT /= sqrt_2;
					}
                }
            }

        }
  }
}

void Quan(ImgYCbCrDCT **YCbCrDCTArray,ImgYCbCrQuan **YCbCrQuanArray,int H,int W)
{
	int m,n,i,j;
    int a[8][8]={
        {16,11,10,16,24,40,51,61},
        {12,12,14,19,26,58,60,55},
        {14,13,16,24,40,57,69,56},
        {14,17,22,29,51,87,80,62},
        {18,22,37,56,68,109,103,77},
        {24,35,55,64,81,104,113,92},
        {49,64,78,87,103,121,120,101},
        {72,92,95,98,112,100,103,99}
     };
     int b[8][8] ={
        {17,18,24,47,99,99,99,99},
        {18,21,26,66,99,99,99,99},
        {24,26,56,99,99,99,99,99},
        {47,66,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99}
    };
    for(m=0;m<Height_8X;m+=8){
        for(n=0;n+8<Width_8X;n+=8){
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){
					YCbCrQuanArray[i+m][j+n].YQuan = round(YCbCrDCTArray[i+m][j+n].YDCT /a[i][j]) ;
					YCbCrQuanArray[i+m][j+n].CbQuan = round(YCbCrDCTArray[i+m][j+n].CbDCT /b[i][j]);
					YCbCrQuanArray[i+m][j+n].CrQuan = round(YCbCrDCTArray[i+m][j+n].CrDCT/b[i][j]);

                }
            }
        }
    }

	return;
}

void DQuan(ImgYCbCrQuan **YCbCrQuanArray,ImgYCbCrDCT **YCbCrDCTArray,int H, int W )
{
	int m,n,i,j;
    int a[8][8]={
        {16,11,10,16,24,40,51,61},
        {12,12,14,19,26,58,60,55},
        {14,13,16,24,40,57,69,56},
        {14,17,22,29,51,87,80,62},
        {18,22,37,56,68,109,103,77},
        {24,35,55,64,81,104,113,92},
        {49,64,78,87,103,121,120,101},
        {72,92,95,98,112,100,103,99}
     };
     int b[8][8] ={
        {17,18,24,47,99,99,99,99},
        {18,21,26,66,99,99,99,99},
        {24,26,56,99,99,99,99,99},
        {47,66,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99},
        {99,99,99,99,99,99,99,99}
    };

    for(m=0;m<Height_8X;m+=8){
        for(n=0;n+8<Width_8X;n+=8){
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){
					YCbCrDCTArray[i+m][j+n].YDCT = YCbCrQuanArray[i+m][j+n].YQuan*a[i][j];
					YCbCrDCTArray[i+m][j+n].CbDCT = YCbCrQuanArray[i+m][j+n].CbQuan*b[i][j];
					YCbCrDCTArray[i+m][j+n].CrDCT = YCbCrQuanArray[i+m][j+n].CrQuan*b[i][j];

                }
            }
        }
    }



}



void IDCT(ImgYCbCrDCT **YCbCrDCTArray,ImgYCbCr **YCbCrArray,int H,int W)
{
    int i,j,u,v,m,n;
    float sqrt_2 = sqrt(2.0);
    float tempY,tempCb,tempCr;
    for(m=0;m<H;m+=8){
		//printf("m=%d ", m);
        for(n=0;n<W;n+=8){
		//printf("n=%d ", n);
            for(i=0;i<8;i++){
				//printf("u=%d ", u);
                for(j=0;j<8;j++){
                		YCbCrArray[m+i][n+j].Y = 0;
                		YCbCrArray[m+i][n+j].Cb = 0;
                		YCbCrArray[m+i][n+j].Cr = 0;
					   for(u=0;u<8;u++){ //height
							for(v=0;v<8;v++){ //width
							//printf("j=%d ", j);
								tempY = YCbCrDCTArray[m+u][n+v].YDCT* cos((2*i+1)*(u)*PI/16) * cos((2*j+1)*(v)*PI/16);
								tempCb = YCbCrDCTArray[m+u][n+v].CbDCT* cos((2*i+1)*(u)*PI/16) * cos((2*j+1)*(v)*PI/16);
								tempCr = YCbCrDCTArray[m+u][n+v].CrDCT* cos((2*i+1)*(u)*PI/16) * cos((2*j+1)*(v)*PI/16);
                        		if(u==0){
	                        		tempY /= sqrt_2;
	                        		tempCb /= sqrt_2;
	                        		tempCr /= sqrt_2;
                        		}
                        		if(v==0){
	                        		tempY /= sqrt_2;
	                        		tempCb /= sqrt_2;
	                        		tempCr /= sqrt_2;
                        		}
								YCbCrArray[m+i][n+j].Y += tempY;
								YCbCrArray[m+i][n+j].Cb += tempCb;
								YCbCrArray[m+i][n+j].Cr += tempCr;
                            }

						}
                        YCbCrArray[m+i][n+j].Y /= 4;
                        YCbCrArray[m+i][n+j].Cb /= 4;
                        YCbCrArray[m+i][n+j].Cr /= 4;
                }
            }


        }
  }
}

