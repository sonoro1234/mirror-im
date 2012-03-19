/** \file
 * \brief Image Statistics Calculations
 *
 * See Copyright Notice in im_lib.h
 */


#include <im.h>
#include <im_util.h>
#include <im_color.h>
#include <im_math_op.h>

#include "im_process_counter.h"
#include "im_process_ana.h"

#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include <stdio.h>


template <class T>
static void DoCalcHisto(T* map, int size, unsigned long* histo, int hcount, int cumulative, int shift)
{
  memset(histo, 0, hcount * sizeof(unsigned long));

#pragma omp parallel for if (IM_OMP_MINCOUNT(size))
  for (int i = 0; i < size; i++)
  {
    int index = map[i] + shift;
    #pragma omp atomic
    histo[index]++;
  }

  if (cumulative)
  {
    /* make cumulative histogram */
    for (int i = 1; i < hcount; i++)
      histo[i] += histo[i-1];
  }
}

void imCalcHistogram(const imbyte* map, int size, unsigned long* histo, int cumulative)
{
  DoCalcHisto(map, size, histo, 256, cumulative, 0);
}

void imCalcUShortHistogram(const imushort* map, int size, unsigned long* histo, int cumulative)
{
  DoCalcHisto(map, size, histo, 65536, cumulative, 0);
}

void imCalcShortHistogram(const short* map, int size, unsigned long* histo, int cumulative)
{
  DoCalcHisto(map, size, histo, 65536, cumulative, 32768);
}

void imCalcGrayHistogram(const imImage* image, unsigned long* histo, int cumulative)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT || image->data_type == IM_SHORT)
    hcount = 65536;

  if (image->color_space == IM_GRAY)
  {
    if (image->data_type == IM_USHORT)
      DoCalcHisto((imushort*)image->data[0], image->count, histo, hcount, 0, 0);
    else if (image->data_type == IM_SHORT)
      DoCalcHisto((short*)image->data[0], image->count, histo, hcount, 0, 32768);
    else
      DoCalcHisto((imbyte*)image->data[0], image->count, histo, hcount, 0, 0);
  }
  else 
  {
    int i;
    memset(histo, 0, hcount * sizeof(unsigned long));

    if (image->color_space == IM_MAP || image->color_space == IM_BINARY)
    {
      imbyte* map = (imbyte*)image->data[0];
      imbyte gray_map[256], r, g, b;

      for (i = 0; i < image->palette_count; i++)
      {
        imColorDecode(&r, &g, &b, image->palette[i]);
        gray_map[i] = imColorRGB2Luma(r, g, b);
      }

#pragma omp parallel for if (IM_OMP_MINCOUNT(image->count))
      for (i = 0; i < image->count; i++)
      {
        int index = gray_map[map[i]];
        #pragma omp atomic
        histo[index]++;
      }
    }
    else   // RGB
    {
      if (image->data_type == IM_USHORT)
      {
        imushort* r = (imushort*)image->data[0];
        imushort* g = (imushort*)image->data[1];
        imushort* b = (imushort*)image->data[2];

#pragma omp parallel for if (IM_OMP_MINCOUNT(image->count))
        for (i = 0; i < image->count; i++)
        {
          imushort index = imColorRGB2Luma(*r++, *g++, *b++);
          #pragma omp atomic
          histo[index]++;
        }
      }
      else if (image->data_type == IM_SHORT)
      {
        short* r = (short*)image->data[0];
        short* g = (short*)image->data[1];
        short* b = (short*)image->data[2];

#pragma omp parallel for if (IM_OMP_MINCOUNT(image->count))
        for (i = 0; i < image->count; i++)
        {
          int index = imColorRGB2Luma(*r++, *g++, *b++) + 32768;
          #pragma omp atomic
          histo[index]++;
        }
      }
      else
      {
        imbyte* r = (imbyte*)image->data[0];
        imbyte* g = (imbyte*)image->data[1];
        imbyte* b = (imbyte*)image->data[2];

#pragma omp parallel for if (IM_OMP_MINCOUNT(image->count))
        for (i = 0; i < image->count; i++)
        {
          imbyte index = imColorRGB2Luma(*r++, *g++, *b++);
          #pragma omp atomic
          histo[index]++;
        }
      }
    }

    if (cumulative)
    {
      /* make cumulative histogram */
      for (i = 1; i < hcount; i++)
        histo[i] += histo[i-1];
    }
  }
}

static unsigned long count_map(const imImage* image)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT || image->data_type == IM_SHORT)
    hcount = 65536;

  unsigned long *histo = new unsigned long[hcount];

  if (image->data_type == IM_USHORT)
    DoCalcHisto((imushort*)image->data[0], image->count, histo, hcount, 0, 0);
  else if (image->data_type == IM_SHORT)
    DoCalcHisto((short*)image->data[0], image->count, histo, hcount, 0, 32768);
  else
    DoCalcHisto((imbyte*)image->data[0], image->count, histo, hcount, 0, 0);

  unsigned long numcolor = 0;

  for (int i = 0; i < hcount; i++)
  {             
    if(histo[i] != 0)
      numcolor++;
  }

  delete [] histo;

  return numcolor;
}

static unsigned long count_comp(const imImage* image)
{
  imbyte *count = (imbyte*)calloc(sizeof(imbyte), 1 << 21); /* (2^24)/8=2^21 ~ 2Mb - using a bit array */
  if (!count)
    return (unsigned long)-1;

  imbyte *comp0 = (imbyte*)image->data[0];
  imbyte *comp1 = (imbyte*)image->data[1];
  imbyte *comp2 = (imbyte*)image->data[2];

  int index;
  unsigned long numcolor = 0;

  for(int i = 0; i < image->count; i++)
  {
    index = comp0[i] << 16 | comp1[i] << 8 | comp2[i];

    if(imDataBitGet(count, index) == 0)
      numcolor++;

    imDataBitSet(count, index, 1);
  }

  free(count);

  return numcolor;
}

unsigned long imCalcCountColors(const imImage* image)
{
  if (imColorModeDepth(image->color_space) > 1)
    return count_comp(image);
  else
    return count_map(image);
}

template <class T>
static void DoStats(T* data, int count, imStats* stats)
{
  memset(stats, 0, sizeof(imStats));

  unsigned long positive = 0;
  unsigned long negative = 0;
  unsigned long zeros = 0;
  double mean = 0;
  double stddev = 0;

  T min, max;
  imMinMax(data, count, min, max);

#pragma omp parallel for if (IM_OMP_MINCOUNT(count)) \
                         reduction (+:positive, negative, zeros, mean, stddev) 
  for (int i = 0; i < count; i++)
  {
    if (data[i] > 0)
      positive++;

    if (data[i] < 0)
      negative++;

    if (data[i] == 0)
      zeros++;

    mean += (double)data[i];
    stddev += ((double)data[i])*((double)data[i]);
  }

  double dcount = (double)count;
  mean /= dcount;
  stddev = sqrt((stddev - dcount*mean*mean)/(dcount-1.0));

  stats->max = (float)max;
  stats->min = (float)min;
  stats->positive = positive;
  stats->negative = negative;
  stats->zeros = zeros;
  stats->mean = (float)mean;
  stats->stddev = (float)stddev;
}

void imCalcImageStatistics(const imImage* image, imStats* stats)
{
  for (int i = 0; i < image->depth; i++)
  {
    switch(image->data_type)
    {
    case IM_BYTE:
      DoStats((imbyte*)image->data[i], image->count, &stats[i]);
      break;                                                                                
    case IM_SHORT:                                                                           
      DoStats((short*)image->data[i], image->count, &stats[i]);
      break;                                                                                
    case IM_USHORT:                                                                           
      DoStats((imushort*)image->data[i], image->count, &stats[i]);
      break;                                                                                
    case IM_INT:                                                                           
      DoStats((int*)image->data[i], image->count, &stats[i]);
      break;                                                                                
    case IM_FLOAT:                                                                           
      DoStats((float*)image->data[i], image->count, &stats[i]);
      break;                                                                                
    }
  }
}

void imCalcHistogramStatistics(const imImage* image, imStats* stats)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT || image->data_type == IM_SHORT)
    hcount = 65536;

  unsigned long *histo = new unsigned long[hcount];

  for (int d = 0; d < image->depth; d++)
  {
    if (image->data_type == IM_USHORT)
      DoCalcHisto((imushort*)image->data[0], image->count, histo, hcount, 0, 0);
    else if (image->data_type == IM_SHORT)
      DoCalcHisto((short*)image->data[0], image->count, histo, hcount, 0, 32768);
    else
      DoCalcHisto((imbyte*)image->data[0], image->count, histo, hcount, 0, 0);

    DoStats((unsigned long*)histo, hcount, &stats[d]);
  }

  delete [] histo;
}

void imCalcHistoImageStatistics(const imImage* image, int* median, int* mode)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT || image->data_type == IM_SHORT)
    hcount = 65536;

  unsigned long *histo = new unsigned long[hcount];

  for (int d = 0; d < image->depth; d++)
  {
    int i;

    if (image->data_type == IM_USHORT)
      DoCalcHisto((imushort*)image->data[0], image->count, histo, hcount, 0, 0);
    else if (image->data_type == IM_SHORT)
      DoCalcHisto((short*)image->data[0], image->count, histo, hcount, 0, 32768);
    else
      DoCalcHisto((imbyte*)image->data[0], image->count, histo, hcount, 0, 0);

    unsigned long half = image->count/2;
    unsigned long count = histo[0];
    for (i = 1; i < hcount; i++)
    {
      if (count > half)
      {
        median[d] = i-1;
        break;
      }

      count += histo[i];
    }

    unsigned long max = histo[0];
    for (i = 1; i < hcount; i++)
    {
      if (max < histo[i])
        max = histo[i];
    }

    int found_mode = 0;
    for (i = 0; i < hcount; i++)
    {
      if (histo[i] == max)
      {
        if (found_mode)
        {
          mode[d] = -1;
          break;
        }

        mode[d] = i;
        found_mode = 1;
      }
    }
  }

  delete [] histo;
}

void imCalcPercentMinMax(const imImage* image, float percent, int ignore_zero, int *min, int *max)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT || image->data_type == IM_SHORT)
    hcount = 65536;

  unsigned long* histo = new unsigned long[hcount];
  imCalcGrayHistogram(image, histo, 0);

  unsigned long acum, cut = (unsigned long)((image->count * percent) / 100.0f);

  acum = 0;
  for ((*min = ignore_zero? 1: 0); *min < hcount; (*min)++)
  {  
    acum += histo[*min];
    if (acum > cut)
      break;
  }

  acum = 0;
  for (*max = hcount-1; *max > 0; (*max)--)
  {  
    acum += histo[*max];
    if (acum > cut)
      break;
  }

  if (*min >= *max)
  {
    *min = 0;
    *max = hcount-1;
  }

  delete [] histo;
}

float imCalcSNR(const imImage* image, const imImage* noise_image)
{
  imStats stats[4];
  imCalcImageStatistics((imImage*)image, stats);

  imStats noise_stats[4];
  imCalcImageStatistics((imImage*)noise_image, noise_stats);

  if (image->color_space == IM_RGB)
  {
    noise_stats[0].stddev += noise_stats[1].stddev;
    noise_stats[0].stddev += noise_stats[2].stddev;
    noise_stats[0].stddev /= 3;
    stats[0].stddev += stats[1].stddev;
    stats[0].stddev += stats[2].stddev;
    stats[0].stddev /= 3;
  }

  if (noise_stats[0].stddev == 0)
    return 0;

  return float(20.*log10(stats[0].stddev / noise_stats[0].stddev));
}

template <class T> 
static double DoRMSOp(T *map1, T *map2, int count)
{
  double rmserror = 0;

#pragma omp parallel for reduction(+:rmserror) if (IM_OMP_MINCOUNT(count))
  for (int i = 0; i < count; i++)
  {
    double diff = double(map1[i] - map2[i]);
    rmserror += diff * diff;
  }

  return rmserror;
}
  
float imCalcRMSError(const imImage* image1, const imImage* image2)
{
  double rmserror = 0;

  int count = image1->count*image1->depth;

  switch(image1->data_type)
  {
  case IM_BYTE:
    rmserror = DoRMSOp((imbyte*)image1->data[0], (imbyte*)image2->data[0], count);
    break;
  case IM_SHORT:
    rmserror = DoRMSOp((short*)image1->data[0], (short*)image2->data[0], count);
    break;
  case IM_USHORT:
    rmserror = DoRMSOp((imushort*)image1->data[0], (imushort*)image2->data[0], count);
    break;
  case IM_INT:
    rmserror = DoRMSOp((int*)image1->data[0], (int*)image2->data[0], count);
    break;
  case IM_FLOAT:
    rmserror = DoRMSOp((float*)image1->data[0], (float*)image2->data[0], count);
    break;
  case IM_CFLOAT:
    rmserror = DoRMSOp((float*)image1->data[0], (float*)image2->data[0], 2*count);
    break;
  }

  rmserror = sqrt(rmserror / double((count * image1->depth)));

  return (float)rmserror;
}

