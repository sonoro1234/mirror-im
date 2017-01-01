/** \file
 * \brief HSI Color Manipulation
 *
 * See Copyright Notice in im_lib.h
 */


#include <math.h>

#include "im_colorhsi.h"
#include "im_color.h"

static const double rad60 =  1.0471975;
static const double rad120 = 2.0943951;
static const double rad180 = 3.1415926;
static const double rad240 = 4.1887902;
static const double rad300 = 5.2359877;
static const double rad360 = 6.2831853;

static const double sqrt3 = 1.73205080757;
static const double rad2deg = 57.2957795131;


static double iColorNormHue(double H)
{
  while (H < 0.0) 
    H += rad360;

  if (H > rad360)  
    H = fmod(H, rad360);

  return H;
}

/**********************************/               
/*         HSI MAX S              */
/**********************************/               
               
static void iColorSmax01(double h, double hr, double hb, double hg, double *h0, double *h1)
{
  if (h < rad120)
    *h0 = hb;
  else if (h < rad240)
    *h0 = hr;
  else
    *h0 = hg;
 
  if (h < rad60 || h > rad300)
    *h1 = hr;
  else if (h < rad180)
    *h1 = hg;
  else
    *h1 = hb;
}

static double iColorHSI_Smax(double h, double cosH, double sinH, double i)
{
  double hr, hb, hg, imax, h0, h1;

  /* i here is normalized between 0-1 */
  
  if (i == 0.0 || i == 1.0)
    return 0.0;

  /* Making r=0, g=0, b=0, r=1, g=1 or b=1 in the parametric equations and 
     writing s in function of H and I. */

  hr = cosH / 1.5;
  hg = (-cosH + sinH*sqrt3) / 3.0;
  hb = (-cosH - sinH*sqrt3) / 3.0;

  /* at bottom */
  if (i <= 1.0/3.0)
  {
    /* face B=0 */
    if (h < rad120)
      return i / fabs(hb);

    /* face R=0 */
    if (h < rad240)
      return i / fabs(hr);

    /* face G=0 */
    return i / fabs(hg);
  }

  /* at top */
  if (i >= 2.0/3.0)
  {
    /* face R=1 */
    if (h < rad60 || h > rad300)
      return (1.0 - i) / fabs(hr);

    /* face G=1 */
    if (h < rad180)
      return (1.0 - i) / fabs(hg);

    /* face B=1 */
    return (1.0 - i) / fabs(hb);
  }

  /* in the middle */

  iColorSmax01(h, hr, hb, hg, &h0, &h1);

  if (h == 0.0 || h == rad120 || h == rad240)
    imax = 1.0/3.0;
  else if (h == rad60 || h == rad180 || h == rad300)
    imax = 2.0/3.0;
  else
    imax = h0 / (h0 - h1);

  if (i < imax) 
    return i / fabs(h0);
  else
    return (1.0 - i) / fabs(h1);
}

/* Given H, returns I where S is max,
   BUT the maximum S here is 1 at the corners of the cube. */
double imColorHSI_ImaxS(double h, double cosH, double sinH)
{
  double i, h0, h1;
  double hr, hb, hg;

  if (h == 0.0 || h == rad120 || h == rad240)
    return 1.0 / 3.0;

  if (h == rad60 || h == rad180 || h == rad300)
    return 2.0/3.0;

  hr = cosH / 1.5;
  hg = (-cosH + sinH*sqrt3) / 3.0;
  hb = (-cosH - sinH*sqrt3) / 3.0;

  iColorSmax01(h, hr, hb, hg, &h0, &h1);

  i = h0 / (h0 - h1);

  return i;
}

/**********************************/               
/*         RGB 2 HSI              */
/**********************************/               

void imColorRGB2HSI(double R, double G, double B, double *fh, double *fs, double *fi)
{            
  double v, u;
  double I, S, H;

  /* Parametric equations */
  v = R - (G + B)/2;
  u = (G - B) * (sqrt3/2);

  I = (R + G + B)/3;   /* already normalized to 0-1 */
  S = sqrt(v*v + u*u);  /* s is between 0-1, it is linear in the cube and it is in u,v space. */
  
  if (S == 0)
    H = 360.0;  /* by definition */
  else
  {
    H = atan2(u, v);
    H = iColorNormHue(H);
    H = H * rad2deg;

    /* must scale S from 0-Smax to 0-1 */
    double Smax = iColorHSI_Smax(H, cos(H), sin(H), I);
    if (Smax == 0.0)
      S = 0.0;
    else
    {
      S /= Smax;
      if (S > 1.0) /* because of round problems when calculating S and Smax */
        S = 1.0;
    }
  }

  *fi = I;
  *fs = S;
  *fh = H;
}

void imColorRGB2HSIbyte(unsigned char r, unsigned char g, unsigned char b, double *fh, double *fs, double *fi)
{
  double fr = imColorReconstruct(r, (imbyte)0, (imbyte)255);
  double fg = imColorReconstruct(g, (imbyte)0, (imbyte)255);
  double fb = imColorReconstruct(b, (imbyte)0, (imbyte)255);
  
  imColorRGB2HSI(fr, fg, fb, fh, fs, fi);
}

/**********************************/               
/*         HSI 2 RGB              */
/**********************************/               

void imColorHSI2RGB(double H, double S, double I, double *r, double *g, double *b)
{
  double cosH, sinH, v, u, R, G, B;

  if (I < 0) I = 0;
  else if (I > 1) I = 1;
  
  if (S < 0) S = 0;
  else if (S > 1) S = 1;

  if (S == 0.0 || I == 1.0 || I == 0.0 || H == 360.0)
  {
    *r = I;
    *g = I;
    *b = I;
    return;
  }

  H = H/rad2deg;
  H = iColorNormHue(H);

  cosH = cos(H);
  sinH = sin(H);
    
  /* must scale S from 0-1 to 0-Smax */
  double Smax = iColorHSI_Smax(H, cosH, sinH, I);
  S *= Smax;
  if (S > 1.0) /* because of round problems when calculating S and Smax */
    S = 1.0;

  v = S * cosH;
  u = S * sinH;

  /* Inverse of the Parametric equations, using I normalized to 0-1 */
  R = I + v/1.5;
  G = I - (v - u*sqrt3)/3.0;
  B = I - (v + u*sqrt3)/3.0;

  /* fix round errors */
  if (R < 0) R = 0;
  if (G < 0) G = 0;
  if (B < 0) B = 0;

  if (R > 1) R = 1.0;
  if (G > 1) G = 1.0;
  if (B > 1) B = 1.0;

  *r = R;
  *g = G;
  *b = B;
}

void imColorHSI2RGBbyte(double h, double s, double i, unsigned char *r, unsigned char *g, unsigned char *b)
{
  double fr, fg, fb;
  
  imColorHSI2RGB(h, s, i, &fr, &fg, &fb);
  
  *r = imColorQuantize(fr, (imbyte)0, (imbyte)255);
  *g = imColorQuantize(fg, (imbyte)0, (imbyte)255);
  *b = imColorQuantize(fb, (imbyte)0, (imbyte)255);
}
