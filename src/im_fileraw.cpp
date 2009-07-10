/** \file
 * \brief RAW File Format Open/New Functions
 *
 * See Copyright Notice in im_lib.h
 * $Id: im_fileraw.cpp,v 1.2 2008-12-03 15:45:34 scuri Exp $
 */

#include "im.h"
#include "im_image.h"
#include "im_util.h"
#include "im_counter.h"
#include "im_raw.h"
#include "im_format.h"
#include "im_format_raw.h"

#include <stdlib.h>
#include <assert.h>


imFile* imFileOpenRaw(const char* file_name, int *error)
{
  assert(file_name);

  imFileFormatBase* iformat = imFormatInitRAW();
  *error = iformat->Open(file_name);
  if (*error)
  {
    delete iformat;
    return NULL;
  }

  imFileClear(iformat);

  iformat->attrib_table = new imAttribTable(599);

  iformat->counter = imCounterBegin(file_name);

  return iformat;
}

imFile* imFileNewRaw(const char* file_name, int *error)
{
  assert(file_name);

  imFileFormatBase* iformat = imFormatInitRAW();
  *error = iformat->New(file_name);
  if (*error) 
  {
    delete iformat;
    return NULL;
  }
   
  imFileClear(iformat);

  iformat->is_new = 1;
  iformat->image_count = 0;
  iformat->compression[0] = 0;

  iformat->attrib_table = new imAttribTable(101);

  iformat->counter = imCounterBegin(file_name);

  return iformat;
}