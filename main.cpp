#include <stdio.h>
#include <stdlib.h>

#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/core/core_c.h"

typedef unsigned char uchar;

/****************************************************************************
*   Die Funktion copyIplImageToArray kopiert unser Graubild in ein Array    *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Graubild: IplImage *i                                                   *
*   temporäres Array: uchar ** t                                            *
****************************************************************************/
int copyIplImageToArray(int h, int w, IplImage *i, uchar ** t){
    CvScalar scalar;
    int y,x;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            scalar= cvGet2D(i,y,x);
            t[y][x] = (uchar) scalar.val[0];
        }
    }
    return 0;
}


/****************************************************************************
*   Die Funktion saveArrayToImage überträgt den Inhalt eines Arrays         *
*   in ein Bild                                                             *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** a                                                  *
*   Zielbild: IplImage *i                                                   *
****************************************************************************/
int saveArrayToImage(int h, int w, uchar ** a, IplImage *i){
    CvScalar scalar;
    int y,x;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            scalar.val[0] = a[y][x];
            cvSet2D(i, y,x, scalar);
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion invertGray ändert den Grauwert jedes "Pixels" eines Arrays *
*   nach dem Schema: MAXIMALER Grauwert - AKTUELLER Grauewert               *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int invertGray(int h, int w, uchar ** t, uchar ** a){
    int x,y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            // 255 = maximaler Grauwert
            a[y][x]=255-t[y][x];
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion rotate90 vertauscht X und Y Koordinaten beim übertragen    *
*   des Quellarrays in unser Zielarray (Drehung um 90° nach links)          *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int rotate90(int h, int w, uchar ** t, uchar ** a){
    int x,y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            a[x][y]=t[y][x];
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion rotate180 dreht X und Y Koordinaten beim übertragen        *
*   des Quellarrays in unser Zielarray um 180° nach links.                  *
*   Schema: ZIELARRAY[MAXHOEHE-1-Y][MAXBREITE-1-X] = QUELLARRAY[Y][X]       *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int rotate180(int h, int w, uchar ** t, uchar ** a){
    int x,y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            a[h-1-y][w-1-x]=t[y][x];
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion rotate270 dreht X und Y Koordinaten beim übertragen        *
*   des Quellarrays in unser Zielarray um 270° nach links.                  *
*   Schema: ZIELARRAY[MAXHOEHE-1-X][MAXBREITE-1-Y] = QUELLARRAY[Y][X]       *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int rotate270(int h, int w, uchar ** t, uchar ** a){
    int x,y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            a[h-1-x][w-1-y]=t[y][x];
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion flipvertical spiegelt X und Y Koordinaten beim übertragen  *
*   des Quellarrays in unser Zielarray vertikal.                            *
*   Schema: ZIELARRAY[Y][MAXBREITE-1-X] = QUELLARRAY[Y][X]                  *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int flipvertical(int h, int w, uchar ** t, uchar ** a){
    int x,y;Parameter:
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            a[y][w-1-x]=t[y][x];
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion fliphorizontal spiegelt X und Y Koordinaten beim übertragen*
*   des Quellarrays in unser Zielarray horizontal.                          *
*   Schema: ZIELARRAY[MAXHOEHE-1-Y][X] = QUELLARRAY[Y][X]                  *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int fliphorizontal(int h, int w, uchar ** t, uchar ** a){
    int x,y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            a[h-1-y][x]=t[y][x];
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion flipboth spiegelt X und Y Koordinaten beim übertragen      *
*   des Quellarrays in unser Zielarray horizontal und vertikal.             *
*   Schema: ZIELARRAY[MAXHOEHE-1-Y][MAXBREITE-1-X] = QUELLARRAY[Y][X]       *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int flipboth(int h, int w, uchar ** t, uchar ** a){
    int x,y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            a[h-1-y][w-1-x]=t[y][x];
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion scale2 skaliert X und Y Koordinaten beim übertragen        *
*   des Quellarrays in unser Zielbild um den Faktor 2.                      *
*   Schema: ZIELBILD[Y*2][X*2] = ZIELBILD[Y*2+1][X*2] = ZIELBILD[Y*2][X*2+1]*
*   = ZIELBILD[Y*2+1][X*2+1] = QUELLARRAY[Y][X]                             *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielbild: IplImage *scaledImage                                         *
****************************************************************************/
int scale2(int h, int w, uchar ** t, IplImage *scaledImage){
    int x,y;
    CvScalar scalar;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            scalar.val[0] = t[y][x];
            cvSet2D(scaledImage, y*2,x*2, scalar);
            cvSet2D(scaledImage, y*2+1,x*2, scalar);
            cvSet2D(scaledImage, y*2,x*2+1, scalar);
            cvSet2D(scaledImage, y*2+1,x*2+1, scalar);
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion scalehalf skaliert X und Y Koordinaten beim übertragen     *
*   des Quellarrays in unser Zielbild um den Faktor 1/2.                    *
*   Schema: ZIELBILD[Y][X] = QUELLARRAY[Y*2][X*2]                           *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielbild: IplImage *scaledImage                                         *
****************************************************************************/
int scalehalf(int h, int w, uchar ** t, IplImage *scaledImage){
    int x,y;
    CvScalar scalar;
    for (y = 0; y < h/2; y++)
    {
        for (x = 0; x < w/2; x++)
        {
            scalar.val[0] = t[y*2][x*2];
            cvSet2D(scaledImage, y,x, scalar);
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion grayhor setzt bei einer Grauwertdifferenz von 15 zum       *
*   nächsten(horizontal) den Grauwert des aktuellen Pixels auf 0(MINIMUM),  *
*   falls nicht, 255(MAXIMUM).                                              *
*   Schema: ZIELARRAY[Y][X] = 0 WENN QUELLARRAY[Y][X+1] - QUELLARRAY[Y][X]  *
*   >=15 SONST ZIELARRAY[Y][X] = 255                                        *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int grayhor(int h, int w, uchar ** t, uchar ** a){
    int x,y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x-1 < w; x++)
        {
            if(t[y][x+1]-t[y][x]>=15)
                a[y][x]=0;
            else a[y][x]=255;
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion grayvert setzt bei einer Grauwertdifferenz von 15 zum      *
*   nächsten(vertikal) den Grauwert des aktuellen Pixels auf 0(MINIMUM),    *
*   falls nicht, 255(MAXIMUM).                                              *
*   Schema: ZIELARRAY[Y][X] = 0 WENN QUELLARRAY[Y+1][X]                     *
*   - QUELLARRAY[Y][X]>=15 SONST ZIELARRAY[Y][X] = 255                      *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int grayvert(int h, int w, uchar ** t, uchar ** a){
    int x,y;
    for (y = 0; y < h-1; y++)
    {
        for (x = 0; x < w; x++)
        {
            if(t[y+1][x]-t[y][x]>=15)
                a[y][x]=0;
            else a[y][x]=255;

        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion graytotal setzt bei einer Grauwertdifferenz von 15 zum     *
*   nächsten(vertikal oder horizontal) den Grauwert des aktuellen Pixels    *
*   auf 0(MINIMUM), falls nicht, 255(MAXIMUM).                              *
*   Schema: ZIELARRAY[Y][X] = 0 WENN                                        *
*   (QUELLARRAY[Y+1][X] - QUELLARRAY[Y][X]>=15) ODER                        *
*   (QUELLARRAY[Y][X+1] - QUELLARRAY[Y][X]>=15)                             *
*   SONST ZIELARRAY[Y][X] = 255                                             *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int graytotal(int h, int w, uchar ** t, uchar ** a){
    int x,y;
    for (y = 0; y < h-1; y++)
    {
        for (x = 0; x < w-1; x++)
        {
            if(t[y][x+1]-t[y][x]>=15 || t[y+1][x]-t[y][x]>=15)
                a[y][x]=0;
            else a[y][x]=255;

        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion mid2x2 bestimmt den mittleren Grauwert für jeweils 2x2     *
*   Felder folgend auf jeden Pixel und weist ihm diesen zu                  *
*                                                                           *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int mid2x2(int h, int w, uchar ** t, uchar ** a){
    int x,y,s;
    for (y = 0; y < h-1; y++)
    {
        for (x = 0; x < w-1; x++)
        {
            s=(t[y][x]+t[y+1][x]+t[y][x+1]+t[y+1][x+1])/4;
            a[y][x]=s;
            a[y][x+1]=s;
            a[y+1][x]=s;
            a[y+1][x+1]=s;
        }
    }
    return 0;
}

/****************************************************************************
*   Die Funktion mid3x3 bestimmt den mittleren Grauwert für jeweils 3x3     *
*   Felder folgend auf jeden Pixel und weist ihm diesen zu                  *
*                                                                           *
*   Parameter:                                                              *
*   Höhe: int h                                                             *
*   Breite: int w                                                           *
*   Quellarray: uchar ** t                                                  *
*   Zielarray: uchar ** a                                                   *
****************************************************************************/
int mid3x3(int h, int w, uchar ** t, uchar ** a){
    int x,y,s;
    for (y = 0; y < h-2; y++)
    {
        for (x = 0; x < w-2; x++)
        {
            s=( t[y][x] + t[y][x+1] + t[y][x+2] + t[y+1][x] + t[y+1][x+1] + t[y+1][x+2] + t[y+2][x] + t[y+2][x+1] + t[y+2][x+2] )/9;
            a[y][x]=s;
            a[y][x+1]=s;
            a[y][x+2]=s;
            a[y+1][x]=s;
            a[y+1][x+1]=s;
            a[y+1][x+2]=s;
            a[y+2][x]=s;
            a[y+2][x+1]=s;
            a[y+2][x+2]=s;
        }
    }
    return 0;
}


int main()
{
// load image and get some image properties
    IplImage *p_image = cvLoadImage("lena.jpg");
    //IplImage *p_image = cvLoadImage("obama_90_sw.bmp");

    // create new image structure
    // for the grayscale output image
    IplImage *p_grayImage = cvCreateImage(cvSize( p_image->width, p_image->height ), IPL_DEPTH_8U, 1 );
    // set type CV_RGB2GRAY to convert
    // RGB image to grayscale
    cvCvtColor(p_image, p_grayImage,CV_RGB2GRAY);

// some local variables
    int width      = p_grayImage->width;
    int height     = p_grayImage->height;
    int width_step = p_grayImage->widthStep;
    int x,y;
    printf("width:     %i\n", width);
    printf("heigth:    %i\n", height);

// allocation of a two-dimensional array
    uchar ** array    = (uchar **) malloc(sizeof(uchar *) * height);
    uchar ** tmpArray = (uchar **) malloc(sizeof(uchar *) * height);
    for (y = 0; y < height; y++)
    {
        array[y]    = (uchar *) malloc(sizeof(uchar ) * width);
        tmpArray[y] = (uchar *) malloc(sizeof(uchar ) * width);
    }

// copy IplImage to allocated array
    copyIplImageToArray(height,width,p_grayImage,tmpArray);


// implementation of algorithm 1
    invertGray(height,width,tmpArray,array);

// save result
    saveArrayToImage(height,width,array,p_grayImage);

// create a new image (90 Grad Drehung)
    IplImage *p_rotate90 = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    rotate90(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_rotate90);
// create a new image (180 Grad Drehung)
    IplImage *p_rotate180 = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    rotate180(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_rotate180);
// create a new image (270 Grad Drehung)
    IplImage *p_rotate270 = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    rotate270(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_rotate270);
// create a new image (Vertikale Spiegelung)
    IplImage *p_flipvertical = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    flipvertical(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_flipvertical);
// create a new image (Horizontale Spiegelung)
    IplImage *p_fliphorizontal = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    fliphorizontal(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_fliphorizontal);
// create a new image (Beide Spiegelungen)
    IplImage *p_flipboth = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    flipboth(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_flipboth);
// create a new image (Skalierung Faktor 2)
    IplImage *p_scale2 = cvCreateImage(cvSize(width*2, height*2), IPL_DEPTH_8U, 1);
    scale2(height,width,tmpArray,p_scale2); //Speichert auch
// create a new image (Skalierung Faktor 1/2)
    IplImage *p_scalehalf = cvCreateImage(cvSize(width/2, height/2), IPL_DEPTH_8U, 1);
    scalehalf(height,width,tmpArray,p_scalehalf); //Speichert auch
// create a new image (GrauwertSprünge horizontal)
    IplImage *p_grayhor = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    grayhor(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_grayhor);
// create a new image (GrauwertSprünge vertikal)
    IplImage *p_grayvert = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    grayvert(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_grayvert);
// create a new image (GrauwertSprünge beide)
    IplImage *p_grayboth = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    graytotal(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_grayboth);
// create a new image (Mittelung 2x2)
    IplImage *p_mid2x2 = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    mid2x2(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_mid2x2);
// create a new image (Mittelung 2x2)
    IplImage *p_mid3x3 = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    mid3x3(height,width,tmpArray,array);
    saveArrayToImage(height,width,array,p_mid3x3);



    // show images
    cvNamedWindow("original", 1);
    cvShowImage("original", p_image);
    cvNamedWindow("invertedGray", 1);
    cvShowImage("invertedGray", p_grayImage);
    cvNamedWindow("Drehung 90 Grad", 1);
    cvShowImage("Drehung 90 Grad", p_rotate90);
    cvNamedWindow("Drehung 180 Grad", 1);
    cvShowImage("Drehung 180 Grad", p_rotate180);
    cvNamedWindow("Drehung 270 Grad", 1);
    cvShowImage("Drehung 270 Grad", p_rotate270);
    cvNamedWindow("Spiegelung vertikal", 1);
    cvShowImage("Spiegelung vertikal", p_flipvertical);
    cvNamedWindow("Spiegelung horizontal", 1);
    cvShowImage("Spiegelung horizontal", p_fliphorizontal);
    cvNamedWindow("Beide Spiegelungen", 1);
    cvShowImage("Beide Spiegelungen", p_flipboth);
    cvNamedWindow("Skalierung Faktor 2", 1);
    cvShowImage("Skalierung Faktor 2", p_scale2);
    cvNamedWindow("Skalierung Faktor 1/2", 1);
    cvShowImage("Skalierung Faktor 1/2", p_scalehalf);
    cvNamedWindow("Grauwertsprünge horizontal", 1);
    cvShowImage("Grauwertsprünge horizontal", p_grayhor);
    cvNamedWindow("Grauwertsprünge vertikal", 1);
    cvShowImage("Grauwertsprünge vertikal", p_grayvert);
    cvNamedWindow("Grauwertsprünge beide", 1);
    cvShowImage("Grauwertsprünge beide", p_grayboth);
    cvNamedWindow("Mittelung 2x2", 1);
    cvShowImage("Mittelung 2x2", p_mid2x2);
    cvNamedWindow("Mittelung 3x3", 1);
    cvShowImage("Mittelung 3x3", p_mid3x3);

    // wait for 'esc' key
    cvWaitKey(0);

    // clean up
    cvReleaseImage(&p_grayImage);
    cvDestroyWindow("invertedGray");
    cvReleaseImage(&p_image);
    cvDestroyWindow("original");
    cvReleaseImage(&p_rotate90);
    cvDestroyWindow("Drehung 90 Grad");
    cvReleaseImage(&p_rotate180);
    cvDestroyWindow("Drehung 180 Grad");
    cvReleaseImage(&p_rotate270);
    cvDestroyWindow("Drehung 270 Grad");
    cvReleaseImage(&p_flipvertical);
    cvDestroyWindow("Spiegelung vertikal");
    cvReleaseImage(&p_fliphorizontal);
    cvDestroyWindow("Spiegelung horizontal");
    cvReleaseImage(&p_flipboth);
    cvDestroyWindow("Beide Spiegelungen");
    cvReleaseImage(&p_scale2);
    cvDestroyWindow("Skalierung Faktor 2");
    cvReleaseImage(&p_scalehalf);
    cvDestroyWindow("Skalierung Faktor 1/2");
    cvReleaseImage(&p_grayhor);
    cvDestroyWindow("Grauwertsprünge horizontal");
    cvReleaseImage(&p_grayvert);
    cvDestroyWindow("Grauwertsprünge vertikal");
    cvReleaseImage(&p_grayboth);
    cvDestroyWindow("Grauwertsprünge beide");
    cvReleaseImage(&p_mid2x2);
    cvDestroyWindow("Mittelung 2x2");
    cvReleaseImage(&p_mid3x3);
    cvDestroyWindow("Mittelung 3x3");



    for (y = 0; y < height; y++)
    {
        free(array[y]);
        free(tmpArray[y]);
    }
    free(array);
    free(tmpArray);

//cvSaveImage
    // bye bye
    printf("Goodbye\n");

    return 0;
}
