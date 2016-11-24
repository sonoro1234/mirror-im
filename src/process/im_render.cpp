/** \file
 * \brief Synthetic Image Render
 *
 * See Copyright Notice in im_lib.h
 */


#include <im.h>
#include <im_util.h>
#include <im_math.h>
#include <im_math_op.h>
#include <im_color.h>

#include "im_process_counter.h"
#include "im_process_pnt.h"

#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>


template <class T> 
static int DoRenderCondOp(T *map, int width, int height, int d, imRenderCondFunc render_func, float* param, int counter)
{
  IM_INT_PROCESSING;

#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINHEIGHT(height))
#endif
  for(int y = 0; y < height; y++)
  {
#ifdef _OPENMP
#pragma omp flush (processing)
#endif
    IM_BEGIN_PROCESSING;

    int offset = y * width;

    for(int x = 0; x < width; x++)
    {
      int cond = 1;
      T Value = (T)(render_func(x, y, d, &cond, param));
      if (cond) map[offset + x] = Value;
    }
  
    IM_COUNT_PROCESSING;
#ifdef _OPENMP
#pragma omp flush (processing)
#endif
    IM_END_PROCESSING;
  }

  return processing;
}

int imProcessRenderCondOp(imImage* image, imRenderCondFunc render_func, const char* render_name, float* param)
{
  int ret = 0;

  int counter = imProcessCounterBegin(render_name);
  imCounterTotal(counter, image->depth*image->height, "Rendering...");

  for (int d = 0; d < image->depth; d++)
  {
    switch(image->data_type)
    {
    case IM_BYTE:
      ret = DoRenderCondOp((imbyte*)image->data[d], image->width, image->height, d, render_func, param, counter);
      break;                                                                                
    case IM_SHORT:                                                                           
      ret = DoRenderCondOp((short*)image->data[d], image->width, image->height, d, render_func, param, counter);
      break;                                                                                
    case IM_USHORT:                                                                           
      ret = DoRenderCondOp((imushort*)image->data[d], image->width, image->height, d, render_func, param, counter);
      break;                                                                                
    case IM_INT:                                                                           
      ret = DoRenderCondOp((int*)image->data[d], image->width, image->height, d, render_func, param, counter);
      break;                                                                                
    case IM_FLOAT:                                                                           
      ret = DoRenderCondOp((float*)image->data[d], image->width, image->height, d, render_func, param, counter);
      break;                                                                                
    case IM_DOUBLE:
      ret = DoRenderCondOp((double*)image->data[d], image->width, image->height, d, render_func, param, counter);
      break;
    }

    if (!ret) 
      break;
  }

  imProcessCounterEnd(counter);

  return ret;
}

template <class T> 
static int DoRenderOp(T *map, int width, int height, int d, imRenderFunc render_func, float* param, int counter, int plus)
{
  IM_INT_PROCESSING;

#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINHEIGHT(height))
#endif
  for(int y = 0; y < height; y++)
  {
#ifdef _OPENMP
#pragma omp flush (processing)
#endif
    IM_BEGIN_PROCESSING;

    int offset = y * width;

    for(int x = 0; x < width; x++)
    {
      if (plus)
      {
        int size_of = sizeof(imbyte);
        float value = (float)map[offset + x] + render_func(x, y, d, param);
        if (sizeof(T) == size_of)
          map[offset + x] = (T)IM_BYTECROP(value);
        else
          map[offset + x] = (T)value;

      }
      else
        map[offset + x] = (T)render_func(x, y, d, param);
    }
  
    IM_COUNT_PROCESSING;
#ifdef _OPENMP
#pragma omp flush (processing)
#endif
    IM_END_PROCESSING;
  }

  return processing;
}

int imProcessRenderOp(imImage* image, imRenderFunc render_func, const char* render_name, float* param, int plus)
{
  int ret = 0;

  int counter = imProcessCounterBegin(render_name);
  imCounterTotal(counter, image->depth*image->height, "Rendering...");

  for (int d = 0; d < image->depth; d++)
  {
    switch(image->data_type)
    {
    case IM_BYTE:
      ret = DoRenderOp((imbyte*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;                                                                                
    case IM_SHORT:                                                                           
      ret = DoRenderOp((short*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;                                                                                
    case IM_USHORT:                                                                           
      ret = DoRenderOp((imushort*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;                                                                                
    case IM_INT:                                                                           
      ret = DoRenderOp((int*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;                                                                                
    case IM_FLOAT:                                                                           
      ret = DoRenderOp((float*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;                                                                                
    case IM_DOUBLE:
      ret = DoRenderOp((double*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;
    }

    if (!ret) 
      break;
  }

  imProcessCounterEnd(counter);

  return ret;
}

static float do_add_specklenoise(int, int, int, int *cond, float* param)
{
  float rnd = float(rand()) / RAND_MAX;
  if (rnd < param[1])
  {
    *cond = 1;
    return (rand() * param[0]) / RAND_MAX;
  }
  else
  {
    *cond = 0;
    return 0;
  }
}

int imProcessRenderAddSpeckleNoise(const imImage* src_image, imImage* dst_image, float percent)
{
  float param[2];
  param[0] = (float)imColorMax(src_image->data_type);
  param[1] = percent / 100.0f;
  srand((unsigned)time(NULL));
  imImageCopyData(src_image, dst_image);
  return imProcessRenderCondOp(dst_image, do_add_specklenoise, "RenderAddSpeckleNoise", param);
}

static float do_add_gaussiannoise(int, int, int, float* param)
{
  float rnd, x1, x2;
    
  do
  {
    x1 = float(rand()) / RAND_MAX;  /* [0,1]  */
    x2 = float(rand()) / RAND_MAX;  /* [0,1]  */
    x1 = 2*x1 - 1;                   /* [-1,1] */
    x2 = 2*x2 - 1;                   /* [-1,1] */
    rnd = x1*x1 + x2*x2;
  } while( rnd >= 1 || rnd == 0);

  rnd = (float)sqrt(-2 * log(rnd) / rnd) * x1;
  return rnd * param[1] + param[0];
}

int imProcessRenderAddGaussianNoise(const imImage* src_image, imImage* dst_image, float mean, float stddev)
{
  float param[2];
  param[0] = mean;
  param[1] = stddev;
  srand((unsigned)time(NULL));
  imImageCopyData(src_image, dst_image);
  return imProcessRenderOp(dst_image, do_add_gaussiannoise, "RenderAddGaussianNoise", param, 1);
}
   
static float do_add_uniformnoise(int, int, int, float* param)
{
  float rnd = float(rand()) / RAND_MAX;
  rnd = 2*rnd - 1;                          /* [-1,1] */
  return 1.7320508f * rnd * param[1] + param[0];
}

int imProcessRenderAddUniformNoise(const imImage* src_image, imImage* dst_image, float mean, float stddev)
{
  float param[2];
  param[0] = mean;
  param[1] = stddev;
  srand((unsigned)time(NULL));
  imImageCopyData(src_image, dst_image);
  return imProcessRenderOp(dst_image, do_add_uniformnoise, "RenderAddUniformNoise", param, 1);
}
   
static float do_const(int, int, int d, float* param)
{
  return param[d];
}

int imProcessRenderConstant(imImage* image, float* value)
{
  return imProcessRenderOp(image, do_const, "RenderConstant", value, 0);
}

static float do_noise(int, int, int, float* param)
{
  return (rand() * param[0]) / RAND_MAX;
}

int imProcessRenderRandomNoise(imImage* image)
{
  static float param[1];
  param[0] = (float)imColorMax(image->data_type);
  srand((unsigned)time(NULL));
  return imProcessRenderOp(image, do_noise, "RenderRandomNoise", param, 0);
}

static float do_cosine(int x, int y, int, float* param)
{
  return float((cos(param[1]*(x-param[3])) * cos(param[2]*(y-param[4])) + param[5]) * param[0]);
}

int imProcessRenderCosine(imImage* image, float xperiod, float yperiod)
{
  float param[6];
  param[0] = (float)imColorMax(image->data_type);

  if (xperiod == 0.0f) param[1] = 0.0;
  else param[1] = 2.0f * 3.1416f / xperiod;

  if (yperiod == 0.0f) param[2] = 0.0;
  else param[2] = 2.0f * 3.1416f / yperiod;

  param[3] = image->width/2.0f;
  param[4] = image->height/2.0f;

  if (image->data_type < IM_FLOAT)
    param[0] = param[0] / 2.0f;

  if (image->data_type == IM_BYTE)
    param[5] = 1.0f;
  else
    param[5] = 0.0f;

  return imProcessRenderOp(image, do_cosine, "RenderCosine", param, 0);
}

static float do_gaussian(int x, int y, int, float* param)
{
  int xd = x - (int)param[2];
  int yd = y - (int)param[3];
  xd *= xd;
  yd *= yd;
  return float(exp((xd + yd)*param[1])*param[0]);
}

int imProcessRenderGaussian(imImage* image, float stddev)
{
  float param[4];
  param[0] = (float)imColorMax(image->data_type);
  param[1] = -1.0f / (2.0f * stddev * stddev);
  param[2] = image->width/2.0f;
  param[3] = image->height/2.0f;
  return imProcessRenderOp(image, do_gaussian, "RenderGaussian", param, 0);
}

static float do_lapgauss(int x, int y, int, float* param)
{
  int xd = x - (int)param[2];
  int yd = y - (int)param[3];
  xd *= xd;
  yd *= yd;
  xd += yd;
  return float((xd - param[4])*exp(xd*param[1])*param[0]);
}

int imProcessRenderLapOfGaussian(imImage* image, float stddev)
{
  float param[5];
  param[0] = (float)imColorMax(image->data_type);
  param[1] = -1.0f / (2.0f * stddev * stddev);
  param[2] = image->width/2.0f;
  param[3] = image->height/2.0f;
  param[4] = 2.0f * stddev * stddev;
  param[0] /= param[4];
  return imProcessRenderOp(image, do_lapgauss, "RenderLapOfGaussian", param, 0);
}

static inline float sinc(float x)
{
  if (x == 0.0f)
    return 1.0f;
  else
    return float(sin(x)/x);
}

static float do_sinc(int x, int y, int, float* param)
{
  return float((sinc((x - param[3])*param[1])*sinc((y - param[4])*param[2]) + param[5])*param[0]);
}

int imProcessRenderSinc(imImage* image, float xperiod, float yperiod)
{
  float param[6];
  param[0] = (float)imColorMax(image->data_type);

  if (xperiod == 0.0f) param[1] = 0.0;
  else param[1] = 2.0f * 3.1416f / xperiod;

  if (yperiod == 0.0f) param[2] = 0.0;
  else param[2] = 2.0f * 3.1416f / yperiod;

  param[3] = image->width/2.0f;
  param[4] = image->height/2.0f;

  if (image->data_type < IM_FLOAT)
    param[0] = param[0] / 1.3f;

  if (image->data_type == IM_BYTE)
    param[5] = 0.3f;
  else
    param[5] = 0.0f;

  return imProcessRenderOp(image, do_sinc, "RenderSinc", param, 0);
}

static float do_box(int x, int y, int, float* param)
{
  int xr = x - (int)param[3];
  int yr = y - (int)param[4];
  if (xr < -(int)param[1] || xr > (int)param[1] ||
      yr < -(int)param[2] || yr > (int)param[2])
    return 0;
  else
    return param[0];
}

int imProcessRenderBox(imImage* image, int width, int height)
{
  float param[5];
  param[0] = (float)imColorMax(image->data_type);
  param[1] = width/2.0f;
  param[2] = height/2.0f;
  param[3] = image->width/2.0f;
  param[4] = image->height/2.0f;
  return imProcessRenderOp(image, do_box, "RenderBox", param, 0);
}

static float do_ramp(int x, int y, int, float* param)
{
  if (param[3])
  {
    if (y < param[1])
      return 0;
    if (y > param[2])
      return 0;

    return (y-param[1])*param[0];
  }
  else
  {
    if (x < param[1])
      return 0;
    if (x > param[2])
      return 0;

    return (x-param[1])*param[0];
  }
}

int imProcessRenderRamp(imImage* image, int start, int end, int dir)
{
  float param[4];
  param[0] = (float)imColorMax(image->data_type);
  param[1] = (float)start;
  param[2] = (float)end;
  param[3] = (float)dir;
  param[0] /= float(end-start);
  return imProcessRenderOp(image, do_ramp, "RenderRamp", param, 0);
}

static inline int Tent(int t, int T)
{
  if (t < 0)
    return (t + T);
  else
    return (T - t);
}

static float do_tent(int x, int y, int, float* param)
{
  int xr = x - (int)param[3];
  int yr = y - (int)param[4];
  if (xr < -(int)param[1] || xr > (int)param[1] ||
      yr < -(int)param[2] || yr > (int)param[2])
    return 0;
  else
    return Tent(xr, (int)param[1]) * Tent(yr, (int)param[2]) * param[0];
}

int imProcessRenderTent(imImage* image, int width, int height)
{
  float param[5];
  param[0] = (float)imColorMax(image->data_type);
  param[1] = width/2.0f;
  param[2] = height/2.0f;
  param[0] /= param[1]*param[2];
  param[3] = image->width/2.0f;
  param[4] = image->height/2.0f;
  return imProcessRenderOp(image, do_tent, "RenderTent", param, 0);
}

static float do_cone(int x, int y, int, float* param)
{
  int xr = x - (int)param[2];
  int yr = y - (int)param[3];
  int radius = imRound(sqrt((double)(xr*xr + yr*yr)));
  if (radius > (int)param[1])
    return 0;
  else
    return ((int)param[1] - radius)*param[0];
}

int imProcessRenderCone(imImage* image, int radius)
{
  float param[4];
  param[0] = (float)imColorMax(image->data_type);
  param[1] = (float)radius;
  param[0] /= param[1];
  param[2] = image->width/2.0f;
  param[3] = image->height/2.0f;
  return imProcessRenderOp(image, do_cone, "RenderCone", param, 0);
}

static float do_wheel(int x, int y, int, float* param)
{
  int xr = x - (int)param[3];
  int yr = y - (int)param[4];
  int radius = imRound(sqrt((double)(xr*xr + yr*yr)));
  if (radius < (int)param[1] || radius > (int)param[2])
    return 0;
  else
    return param[0];
}

int imProcessRenderWheel(imImage* image, int int_radius, int ext_radius)
{
  float param[5];
  param[0] = (float)imColorMax(image->data_type);
  param[1] = (float)int_radius;
  param[2] = (float)ext_radius;
  param[3] = image->width/2.0f;
  param[4] = image->height/2.0f;
  return imProcessRenderOp(image, do_wheel, "RenderWheel", param, 0);
}

static float do_grid(int x, int y, int, float* param)
{
  int xr = x - (int)param[3];
  int yr = y - (int)param[4];
  if (xr % (int)param[1] == 0 && yr % (int)param[2] == 0)
    return param[0];
  else
    return 0;
}

int imProcessRenderGrid(imImage* image, int x_space, int y_space)
{
  float param[5];
  param[0] = (float)imColorMax(image->data_type);
  param[1] = (float)x_space;
  param[2] = (float)y_space;
  param[3] = image->width/2.0f;
  param[4] = image->height/2.0f;
  return imProcessRenderOp(image, do_grid, "RenderGrid", param, 0);
}

static float do_chessboard(int x, int y, int, float* param)
{
  int xr = x - (int)param[3];
  int yr = y - (int)param[4];
  int xp = xr % (int)param[1];
  int yp = yr % (int)param[2];
  int xc = (int)param[1]/2;
  int yc = (int)param[2]/2;
  if (xr < 0) xc = -xc;
  if (yr < 0) yc = -yc;
  if ((xp < xc && yp < yc) ||
      (xp > xc && yp > yc))
    return param[0];
  else
    return 0;
}

int imProcessRenderChessboard(imImage* image, int x_space, int y_space)
{
  float param[5];
  param[0] = (float)imColorMax(image->data_type);
  param[1] = (float)x_space*2;
  param[2] = (float)y_space*2;
  param[3] = image->width/2.0f;
  param[4] = image->height/2.0f;
  return imProcessRenderOp(image, do_chessboard, "RenderChessboard", param, 0);
}


/*******************************************************************************************************/


struct xyStackArray
{
  int* xy_data;
  int max_count, count;
};

static inline xyStackArray* xyStackArrayCreate()
{
  xyStackArray* stack = new xyStackArray;

  stack->count = 0;
  stack->max_count = 1000;  /* 500 points */
  stack->xy_data = (int*)malloc(stack->max_count * sizeof(int));

  return stack;
}

static inline void xyStackArrayDestroy(xyStackArray* stack)
{
  free(stack->xy_data);
  delete stack;
}

static inline int xyStackArrayHasData(xyStackArray* stack)
{
  return stack->count;
}

static inline void xyStackArrayPush(xyStackArray* stack, int x, int y)
{
  if (stack->count + 2 > stack->max_count)
  {
    stack->max_count += 1000;  /* +500 points */
    stack->xy_data = (int*)realloc(stack->xy_data, stack->max_count * sizeof(int));
  }

  stack->xy_data[stack->count+0] = x;
  stack->xy_data[stack->count+1] = y;
  stack->count += 2;
}

static inline void xyStackArrayPop(xyStackArray* stack, int &x, int &y)
{
  stack->count -= 2;
  x = stack->xy_data[stack->count + 0];
  y = stack->xy_data[stack->count + 1];
}

template <class T>
static inline int color_is_similar(const T* color, const T& r, const T& g, const T& b, T tol)
{
  T sqr_dist = (T)sqrt_op((color[0] - r)*(color[0] - r) + (color[1] - g)*(color[1] - g) + (color[2] - b)*(color[2] - b));
  if (sqr_dist < tol)
    return 1;
  else
    return 0;
}

template <class T>
static inline int color_equal(const T* color, const T& r, const T& g, const T& b)
{
  if (color[0] == r && color[1] == g && color[2] == b)
    return 1;
  else
    return 0;
}

template <class T>
static inline void color_init(T* color, const T& r, const T& g, const T& b)
{
  color[0] = r;
  color[1] = g;
  color[2] = b;
}

template <class T>
static inline void color_copy(const T* color, T& r, T& g, T& b)
{
  r = color[0];
  g = color[1];
  b = color[2];
}

template <class T>
static inline void fill_color(xyStackArray* stack, const T* replace_color, const T* target_color, T* r, T* g, T* b, int width, int x, int y, T tol)
{
  int offset = y * width + x;
  if (!color_equal(replace_color, r[offset], g[offset], b[offset]) && color_is_similar(target_color, r[offset], g[offset], b[offset], tol))
  {
    xyStackArrayPush(stack, x, y);
    color_copy(replace_color, r[offset], g[offset], b[offset]);
  }
}

template <class T>
static void DoRenderFloodFillRGB(T** data, int width, int height, int start_x, int start_y, float* replace_data, float tolerance)
{
  T *r = data[0], *g = data[1], *b = data[2];
  int offset, x, y;
  T target_color[3];
  T replace_color[3];
  T tol = (T)tolerance;

  replace_color[0] = (T)replace_data[0];
  replace_color[1] = (T)replace_data[1];
  replace_color[2] = (T)replace_data[2];

  offset = start_y * width + start_x;
  if (color_equal(replace_color, r[offset], g[offset], b[offset]))
    return;

  color_init(target_color, r[offset], g[offset], b[offset]);

  /* very simple 4 neighbors stack based flood fill */

  xyStackArray* stack = xyStackArrayCreate();

  /* a color in the xy_stack is always similar to the target color,
  and it was already replaced */
  xyStackArrayPush(stack, start_x, start_y);
  color_copy(replace_color, r[offset], g[offset], b[offset]);

  while (xyStackArrayHasData(stack))
  {
    xyStackArrayPop(stack, x, y);

    /* right */
    if (x < width - 1)
      fill_color(stack, replace_color, target_color, r, g, b, width, x + 1, y, tol);

    /* left */
    if (x > 0)
      fill_color(stack, replace_color, target_color, r, g, b, width, x - 1, y, tol);

    /* top */
    if (y < height - 1)
      fill_color(stack, replace_color, target_color, r, g, b, width, x, y + 1, tol);

    /* bottom */
    if (y > 0)
      fill_color(stack, replace_color, target_color, r, g, b, width, x, y - 1, tol);
  }

  xyStackArrayDestroy(stack);
}

void imProcessRenderFloodFill(imImage* image, int start_x, int start_y, float* replace_color, float tolerance)
{
  switch (image->data_type)
  {
  case IM_BYTE:
    DoRenderFloodFillRGB((imbyte**)image->data, image->width, image->height, start_x, start_y, replace_color, tolerance);
    break;
  case IM_SHORT:
    DoRenderFloodFillRGB((short**)image->data, image->width, image->height, start_x, start_y, replace_color, tolerance);
    break;
  case IM_USHORT:
    DoRenderFloodFillRGB((imushort**)image->data, image->width, image->height, start_x, start_y, replace_color, tolerance);
    break;
  case IM_INT:
    DoRenderFloodFillRGB((int**)image->data, image->width, image->height, start_x, start_y, replace_color, tolerance);
    break;
  case IM_FLOAT:
    DoRenderFloodFillRGB((float**)image->data, image->width, image->height, start_x, start_y, replace_color, tolerance);
    break;
  case IM_DOUBLE:
    DoRenderFloodFillRGB((double**)image->data, image->width, image->height, start_x, start_y, replace_color, tolerance);
    break;
  }
}
