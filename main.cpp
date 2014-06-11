#include <stdio.h>
#include <stdlib.h>

#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/core/core_c.h"


typedef unsigned char uchar;


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

int saveArrayToImage(int h, int w, uchar ** t, IplImage *i){
    CvScalar scalar;
    int y,x;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            scalar.val[0] = t[y][x];
            cvSet2D(i, y,x, scalar);
        }
    }
    return 0;
}

int main()
{
// greetings to the world
    printf("Hello world!\n");

// load image and get some image properties
    IplImage *p_image = cvLoadImage("lena.jpg");
    //IplImage *p_image = cvLoadImage("obama_90_sw.bmp");

    // create new image structure
    // for the grayscale output image
    IplImage *p_grayImage = cvCreateImage(cvSize( p_image->width, p_image->height ), IPL_DEPTH_8U, 1 );

    CvScalar s;

    // set type CV_RGB2GRAY to convert
    // RGB image to grayscale
    cvCvtColor(p_image, p_grayImage,CV_RGB2GRAY);


// some local variables
    int width      = p_grayImage->width;
    int height     = p_grayImage->height;
    int width_step = p_grayImage->widthStep;
    int y=0,x=0;

    printf("width:     %i\n", width);
    printf("heigth:    %i\n", height);

// allocation of a two-dimensional array
    uchar ** array    = (uchar **) malloc(sizeof(uchar *) * height);
    uchar ** tmpArray = (uchar **) malloc(sizeof(uchar *) * height);
    uchar ** tmpoArray = (uchar **) malloc(sizeof(uchar *) * height);

    for (y = 0; y < height; y++)
    {
        array[y]    = (uchar *) malloc(sizeof(uchar ) * width);
        tmpArray[y] = (uchar *) malloc(sizeof(uchar ) * width);
        tmpoArray[y] = (uchar *) malloc(sizeof(uchar ) * width);
    }

// copy IplImage to allocated array
    copyIplImageToArray(height,width,p_grayImage,tmpoArray);

// implementation of algorithm 1
    int maxY= height;
    int maxX= width;
    int minY= 0;
    int minX= 0;
    printf("Algorithm 1\n");
    for (y = minY; y < maxY; y++)
    {
        for (x = minX; x < maxX; x++)
        {
            tmpArray[y][x]=255-tmpoArray[y][x];
        }
    }

// save result
    saveArrayToImage(height,width,tmpArray,p_grayImage);
//
//Ptr to image data
    uchar *p_data = (uchar *)p_grayImage->imageData;

// create a new image
    IplImage *p_rotateleft = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

    width      = p_rotateleft->width;
    height     = p_rotateleft->height;
    width_step = p_rotateleft->widthStep;

    uchar *p_new_data = (uchar *)p_rotateleft->imageData;
    uchar *p_tmp1, p_tmp2;

    cvCvtColor(p_image, p_rotateleft,CV_RGB2GRAY);
// copy IplImage to allocated array
    copyIplImageToArray(height,width,p_image,tmpoArray);

// implementation of rotate 90 degree left
    printf("rotate 90 degree left");
    for (y = minY; y < maxY; y++)
    {
        for (x = minX; x < maxX; x++)
        {
            tmpArray[x][y]=tmpoArray[y][x];

        }
    }

// save rotated image
    saveArrayToImage(height,width,tmpArray,p_rotateleft);



// create a new image
    IplImage *p_upsidedown = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

    width      = p_upsidedown->width;
    height     = p_upsidedown->height;
    width_step = p_upsidedown->widthStep;

//   uchar *p_new_data2 = (uchar *)p_upsidedown->imageData;
//   uchar *p_tmp1, p_tmp2;

cvCvtColor(p_image, p_upsidedown,CV_RGB2GRAY);
copyIplImageToArray(height,width,p_image,tmpoArray);
// implementation of turn upside down
    printf("turn upside down %i,%i",maxX,maxY);
    for (y = minY; y < maxY; y++)
    {
        for (x = minX; x < maxX; x++)
        {
            tmpArray[maxY-y][maxX-x]=tmpoArray[y][x];
        }
    }
    saveArrayToImage(height,width,tmpArray,p_upsidedown);
/*
// create a new image
    IplImage *p_rotateright = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

    width      = p_rotateright->width;
    height     = p_rotateright->height;
    width_step = p_rotateright->widthStep;

cvCvtColor(p_image, p_rotateright,CV_RGB2GRAY);
copyIplImageToArray(height,width,p_image,tmpArray2);
// implementation of turn upside down
    printf("rotate 270 degree left");
    for (y = minY; y < maxY; y++)
    {
        for (x = minX; x < maxX; x++)
        {
            tmpArray[maxX-x][maxY-y]=tmpArray2[y][x];
        }
    }
    saveArrayToImage(height,width,tmpArray,p_rotateright);

// create a new image
    IplImage *p_flipvertical = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

    width      = p_flipvertical->width;
    height     = p_flipvertical->height;
    width_step = p_flipvertical->widthStep;

cvCvtColor(p_image, p_flipvertical,CV_RGB2GRAY);
copyIplImageToArray(height,width,p_image,tmpArray2);
// implementation of flip vertical
    printf("flip vertical");
    for (y = minY; y < maxY; y++)
    {
        for (x = minX; x < maxX; x++)
        {
            tmpArray[y][maxX-x]=tmpArray2[y][x];
        }
    }
    saveArrayToImage(height,width,tmpArray,p_flipvertical);
/*
// create a new image
    IplImage *p_fliphorizontal= cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

    width      = p_fliphorizontal->width;
    height     = p_fliphorizontal->height;
    width_step = p_fliphorizontal->widthStep;

cvCvtColor(p_image, p_fliphorizontal,CV_RGB2GRAY);
copyIplImageToArray(height,width,p_image,tmpArray2);
// implementation of flip horizontal
    printf("flip horizontal");
    for (y = minY; y < maxY; y++)
    {
        for (x = minX; x < maxX; x++)
        {
            tmpArray[maxY-y][x]=tmpArray2[y][x];
        }
    }
    saveArrayToImage(height,width,tmpArray,p_fliphorizontal);

// create a new image
    IplImage *p_reflected= cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

    width      = p_reflected->width;
    height     = p_reflected->height;
    width_step = p_reflected->widthStep;

cvCvtColor(p_image, p_reflected,CV_RGB2GRAY);
copyIplImageToArray(height,width,p_image,tmpArray2);
// implementation of flip horizontal
    printf("reflected");
    for (y = minY; y < maxY; y++)
    {
        for (x = minX; x < maxX; x++)
        {
            tmpArray[maxY-y][maxX-x]=tmpArray2[y][x];
        }
    }
    saveArrayToImage(height,width,tmpArray,p_reflected);

// create a new image
    IplImage *p_scale2= cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

    width      = p_scale2->width;
    height     = p_scale2->height;
    width_step = p_scale2->widthStep;

cvCvtColor(p_image, p_scale2,CV_RGB2GRAY);
copyIplImageToArray(height,width,p_image,tmpArray2);
// implementation of flip horizontal
    printf("scale2");
    for (y = minY; y < maxY; y++)
    {
        for (x = minX; x < maxX; x++)
        {
            tmpArray[maxY-y][maxX-x]=tmpArray2[y][x];
        }
    }
    saveArrayToImage(height,width,tmpArray,p_scale2);
*/

    // show original and resized image
    cvNamedWindow("original", 1);
    cvShowImage("original", p_image);
    cvNamedWindow("grayscale", 1);
    cvShowImage("grayscale", p_grayImage);
    cvNamedWindow("rotate 90 degree left", 1);
    cvShowImage("rotate 90 degree left", p_rotateleft);
    cvNamedWindow("turn upside down", 1);
    cvShowImage("turn upside down", p_upsidedown);
/*    cvNamedWindow("rotate 270 degree left", 1);
    cvShowImage("rotate 270 degree left", p_rotateright);
    cvNamedWindow("flip vertical", 1);
    cvShowImage("flip vertical", p_flipvertical);
    cvNamedWindow("flip horizontal", 1);
/*    cvShowImage("flip horizontal", p_fliphorizontal);
    cvNamedWindow("reflected", 1);
    cvShowImage("reflected", p_reflected);
    cvNamedWindow("scale2", 1);
    cvShowImage("scale2", p_scale2);*/
    // wait for 'esc' key
    cvWaitKey(0);

    // clean up
    cvReleaseImage(&p_grayImage);
    cvDestroyWindow("grayscale");
    cvReleaseImage(&p_image);
    cvDestroyWindow("original");
    cvReleaseImage(&p_rotateleft);
    cvDestroyWindow("rotate 90 degree left");
    cvReleaseImage(&p_upsidedown);
    cvDestroyWindow("turn upside down");
/*  cvReleaseImage(&p_rotateright);
/*  cvDestroyWindow("rotate 270 degree left");
    cvReleaseImage(&p_flipvertical);
    cvDestroyWindow("flip vertical");
/*    cvReleaseImage(&p_fliphorizontal);
    cvDestroyWindow("flip horizontal");
    cvReleaseImage(&p_reflected);
    cvDestroyWindow("reflected");*/

    for (y = 0; y < height; y++)
    {
        free(array[y]);
        free(tmpArray[y]);
        free(tmpoArray[y]);
    }
    free(array);
    free(tmpArray);
    free(tmpoArray);

//cvSaveImage
    // bye bye
    printf("Goodbye\n");

    return 0;
}
