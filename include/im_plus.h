/** \file
 * \brief Name space for C++ high level API
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_PLUS_H
#define __IM_PLUS_H


#include "im.h"
#include "im_lib.h"
#include "im_raw.h"
#include "im_image.h"
#include "im_palette.h"
#include "im_kernel.h"
#include "im_capture.h"
#include "im_process.h"
#include "im_counter.h"
#include "im_convert.h"


namespace cd
{
  class Canvas;
  class CanvasImageRGB;
}

/** \brief Name space for C++ high level API
 *
 * \par
 * Defines wrapper classes for all C structures.
 *
 * See \ref im_plus.h
 */
namespace im
{
  const char* Version()
  {
    return imVersion();
  }
  const char* VersionDate()
  {
    return imVersionDate();
  }
  int VersionNumber()
  {
    return imVersionNumber();
  }

  long ColorEncode(unsigned char red, unsigned char green, unsigned char blue)
  {
    return (((long)red) << 16) | (((long)green) << 8) | ((long)blue);
  }
  unsigned char ColorRed(long color)
  {
    return (unsigned char)(color >> 16);
  }
  unsigned char ColorGreen(long color)
  {
    return (unsigned char)(color >> 8);
  }
  unsigned char ColorBlue(long color)
  {
    return (unsigned char)color;
  }


  class Palette
  {
    friend class Image;

  protected:
    long* pal_data;
    int pal_count;

  public:
    Palette(int count = 256)
    {
      pal_count = count;
      pal_data = imPaletteNew(pal_count);
    }
    Palette(long* palette, int count = 256)
    {
      pal_count = count;
      pal_data = palette;
    }
    Palette(const Palette& src_palette)
    {
      pal_count = src_palette.pal_count;
      pal_data = imPaletteNew(pal_count);
      for (int i = 0; i < pal_count; i++)
        pal_data[i] = src_palette.pal_data[i];
    }
    ~Palette()
    {
      if (pal_data)
        imPaletteRelease(pal_data);
    }

    long& operator [] (int index)
    {
      static long err = -1;
      if (!pal_data || index < 0 || index >= pal_count)
        return err;
      return pal_data[index];
    }


    int FindNearest(long color) const
    {
      return imPaletteFindNearest(pal_data, pal_count, color);
    }
    int FindColor(long color, unsigned char tol)
    {
      return imPaletteFindColor(pal_data, pal_count, color, tol);
    }

    /* pre-defined palettes */
    static Palette Gray()
    {
      return Palette(imPaletteGray());
    }
    static Palette Red()
    {
      return Palette(imPaletteRed());
    }
    static Palette Green()
    {
      return Palette(imPaletteGreen());
    }
    static Palette Blue()
    {
      return Palette(imPaletteBlue());
    }
    static Palette Yellow()
    {
      return Palette(imPaletteYellow());
    }
    static Palette Magenta()
    {
      return Palette(imPaletteMagenta());
    }
    static Palette Cian()
    {
      return Palette(imPaletteCian());
    }
    static Palette Rainbow()
    {
      return Palette(imPaletteRainbow());
    }
    static Palette Hues()
    {
      return Palette(imPaletteHues());
    }
    static Palette BlueIce()
    {
      return Palette(imPaletteBlueIce());
    }
    static Palette HotIron()
    {
      return Palette(imPaletteHotIron());
    }
    static Palette BlackBody()
    {
      return Palette(imPaletteBlackBody());
    }
    static Palette HighContrast()
    {
      return Palette(imPaletteHighContrast());
    }
    static Palette Linear()
    {
      return Palette(imPaletteLinear());
    }

    static Palette Uniform()
    {
      return Palette(imPaletteUniform());
    }
    static int UniformIndex(long color)
    {
      return imPaletteUniformIndex(color);
    }
    static int UniformIndexHalftoned(long color, int x, int y)
    {
      return imPaletteUniformIndexHalftoned(color, x, y);
    }
  };


  class ImageChannelLine
  {
    imImage* image;
    int lin;
    void* channel_buffer;

  public:
    ImageChannelLine(imImage* ref_image, int ref_lin, void* ref_channel_buffer)
      : image(ref_image), lin(ref_lin), channel_buffer(ref_channel_buffer)
    {
    }

    double operator [] (int col)
    {
      if (image == 0 || col < 0 || col >= image->width)
        return 0;
      else
      {
        int index = lin * image->width + col;

        switch (image->data_type)
        {
        case IM_BYTE:
          {
            unsigned char *bdata = (unsigned char*)channel_buffer;
            return (double)bdata[index];
          }
        case IM_SHORT:
          {
            short *sdata = (short*)channel_buffer;
            return (double)sdata[index];
          }
        case IM_USHORT:
          {
            unsigned short *udata = (unsigned short*)channel_buffer;
            return (double)udata[index];
          }
        case IM_INT:
          {
            int *idata = (int*)channel_buffer;
            return (double)idata[index];
          }
        case IM_FLOAT:
          {
            float *fdata = (float*)channel_buffer;
            return (double)fdata[index];
          }
        case IM_DOUBLE:
          {
            double *fdata = (double*)channel_buffer;
            return fdata[index];
          }
        }

        return 0;
      }
    }
  };


  class ImageChannel
  {
    imImage* image;
    int plane;

  public:
    ImageChannel(imImage* ref_image, int ref_plane)
      : image(ref_image), plane(ref_plane)
    {
    }

    ImageChannelLine operator [] (int lin)
    {
      if (image == 0 || lin < 0 || lin >= image->height)
        return ImageChannelLine(0, 0, 0);
      else
        return ImageChannelLine(image, lin, image->data[plane]);
    }
  };


  class Image
  {
    friend class File;
    friend class Process;
    friend class Analyze;
    friend class Calc;
    friend class VideoCapture;

    friend class cd::Canvas;
    friend class cd::CanvasImageRGB;

  protected:
    imImage* im_image;

    Image() { im_image = 0; };

    void IncRef()
    {
      int image_ref = GetAttribInteger("_IMAGE_REF");
      image_ref++;
      SetAttribInteger("_IMAGE_REF", IM_INT, image_ref);
    }
    bool DecRef()
    {
      int image_ref = GetAttribInteger("_IMAGE_REF");
      if (image_ref > 0)
      {
        image_ref--;
        SetAttribInteger("_IMAGE_REF", IM_INT, image_ref);
      }
      return image_ref == 0;
    }

  public:
    Image(int width, int height, int color_space, int data_type)
    {
      im_image = imImageCreate(width, height, color_space, data_type);
      IncRef();
    }
    Image(const Image& src_image, int width, int height, int color_space, int data_type)
    {
      im_image = imImageCreateBased(src_image.im_image, width, height, color_space, data_type);
      IncRef();
    }
    Image(const char* file_name, int index, int &error, bool as_bitmap)
    {
      if (as_bitmap)
        im_image = imFileImageLoad(file_name, index, &error);
      else
        im_image = imFileImageLoadBitmap(file_name, index, &error);
      IncRef();
    }
    Image(const Image& ref_image)
    {
      im_image = ref_image.im_image;
      IncRef();
    }
    Image(imImage* ref_image)
    {
      im_image = ref_image;
      IncRef();
    }
    ~Image()
    {
      if (im_image)
      {
        if (DecRef())
          imImageDestroy(im_image);
      }
    }


    bool Failed() const
    {
      return im_image == 0;
    }

    /* image[plane][line][column] */
    ImageChannel operator [] (int plane)
    {
      int depth = im_image->has_alpha? im_image->depth + 1 : im_image->depth;
      if (plane < 0 || plane >= depth)
        return ImageChannel(0, 0);
      else
        return ImageChannel(im_image, plane);
    }

    /* image info */
    int Width() const 
    { 
      return im_image->width; 
    }
    int Height() const 
    { 
      return im_image->height; 
    }
    int ColorSpace() const 
    { 
      return im_image->color_space; 
    }
    int DataType() const 
    { 
      return im_image->data_type; 
    }
    bool HasAlpha() const 
    { 
      return im_image->has_alpha != 0; 
    }
    int Depth() const 
    { 
      return im_image->depth; 
    }
    bool IsBitmap() const
    {
      return imImageIsBitmap(im_image) == 1;
    }


    /* image io */
    int Save(const char* file_name, const char* format)
    {
      return imFileImageSave(file_name, format, im_image);
    }

    void SetValue(int plane, int lin, int col, double value)
    {
      int depth = im_image->has_alpha ? im_image->depth + 1 : im_image->depth;
      if (plane < 0 || plane >= depth)
        return;
      if (lin < 0 || lin >= im_image->height)
        return;
      if (col < 0 || col >= im_image->width)
        return;

      int index = lin * im_image->width + col;
      void* channel_buffer = im_image->data[plane];

      switch (im_image->data_type)
      {
      case IM_BYTE:
      {
        unsigned char *bdata = (unsigned char*)channel_buffer;
        bdata[index] = (unsigned char)value;
      }
      case IM_SHORT:
      {
        short *sdata = (short*)channel_buffer;
        sdata[index] = (short)value;
      }
      case IM_USHORT:
      {
        unsigned short *udata = (unsigned short*)channel_buffer;
        udata[index] = (unsigned short)value;
      }
      case IM_INT:
      {
        int *idata = (int*)channel_buffer;
        idata[index] = (int)value;
      }
      case IM_FLOAT:
      {
        float *fdata = (float*)channel_buffer;
        fdata[index] = (float)value;
      }
      case IM_DOUBLE:
      {
        double *fdata = (double*)channel_buffer;
        fdata[index] = value;
      }
      }
    }
    double GetValue(int plane, int lin, int col)
    {
      int depth = im_image->has_alpha ? im_image->depth + 1 : im_image->depth;
      if (plane < 0 || plane >= depth)
        return 0;
      if (lin < 0 || lin >= im_image->height)
        return 0;
      if (col < 0 || col >= im_image->width)
        return 0;

      int index = lin * im_image->width + col;
      void* channel_buffer = im_image->data[plane];

      switch (im_image->data_type)
      {
        case IM_BYTE:
        {
          unsigned char *bdata = (unsigned char*)channel_buffer;
          return (double)bdata[index];
        }
        case IM_SHORT:
        {
          short *sdata = (short*)channel_buffer;
          return (double)sdata[index];
        }
        case IM_USHORT:
        {
          unsigned short *udata = (unsigned short*)channel_buffer;
          return (double)udata[index];
        }
        case IM_INT:
        {
          int *idata = (int*)channel_buffer;
          return (double)idata[index];
        }
        case IM_FLOAT:
        {
          float *fdata = (float*)channel_buffer;
          return (double)fdata[index];
        }
        case IM_DOUBLE:
        {
          double *fdata = (double*)channel_buffer;
          return fdata[index];
        }
      }

      return 0;
    }

    /* copy utilities */
    Image Duplicate()
    {
      return Image(imImageDuplicate(im_image));
    }
    void Copy(Image& dst_image) const
    {
      imImageCopy(im_image, dst_image.im_image);
    }
    void CopyAttributes(Image& dst_image) const
    {
      imImageCopyAttributes(im_image, dst_image.im_image);
    }
    void MergeAttributes(Image& dst_image) const
    {
      imImageMergeAttributes(im_image, dst_image.im_image);
    }
    void CopyData(Image& dst_image) const
    {
      imImageCopyData(im_image, dst_image.im_image);
    }
    void CopyPlane(Image& dst_image, int src_plane, int dst_plane) const
    {
      imImageCopyPlane(im_image, src_plane, dst_image.im_image, dst_plane);
    }


    /* initialization utilities */
    void Clear()
    {
      imImageClear(im_image);
    }
    void Reshape(int width, int height)
    {
      imImageReshape(im_image, width, height);
    }


    /* palette */
    void SetPalette(const Palette& palette)
    {
      Palette new_palette(palette); /* duplicate */
      imImageSetPalette(im_image, new_palette.pal_data, new_palette.pal_count);
      new_palette.pal_data = 0;  /* mark as released */
    }
    Palette GetPalette()
    {
      Palette ref_palette(im_image->palette, im_image->palette_count);  /* reference */
      Palette new_palette(ref_palette);  /* duplicate */
      ref_palette.pal_data = 0;  /* mark as released */
      return new_palette;
    }


    /* alpha */
    void AddAlpha()
    {
      imImageAddAlpha(im_image);
    }
    void SetAlpha(float alpha)
    {
      imImageSetAlpha(im_image, alpha);
    }
    void RemoveAlpha()
    {
      imImageRemoveAlpha(im_image);
    }


    /* color utilities */
    void MakeBinary()
    {
      imImageMakeBinary(im_image);
    }
    void MakeGray()
    {
      imImageMakeGray(im_image);
    }
    void SetBinary()
    {
      imImageSetBinary(im_image);
    }
    void SetGray()
    {
      imImageSetGray(im_image);
    }
    void SetMap()
    {
      imImageSetMap(im_image);
    }


    /* attributes or metadata */
    void SetAttribute(const char* attrib, int data_type, int count, const void* data)
    {
      imImageSetAttribute(im_image, attrib, data_type, count, data);
    }
    void SetAttribInteger(const char* attrib, int data_type, int value)
    {
      imImageSetAttribInteger(im_image, attrib, data_type, value);
    }
    void SetAttribReal(const char* attrib, int data_type, double value)
    {
      imImageSetAttribReal(im_image, attrib, data_type, value);
    }
    void SetAttribString(const char* attrib, const char* value)
    {
      imImageSetAttribString(im_image, attrib, value);
    }

    const void* GetAttribute(const char* attrib, int *data_type = 0, int *count = 0) const
    {
      return imImageGetAttribute(im_image, attrib, data_type, count);
    }
    int GetAttribInteger(const char* attrib, int index = 0) const
    {
      return imImageGetAttribInteger(im_image, attrib, index);
    }
    double GetAttribReal(const char* attrib, int index = 0) const
    {
      return imImageGetAttribReal(im_image, attrib, index);
    }
    const char* GetAttribString(const char* attrib) const
    {
      return imImageGetAttribString(im_image, attrib);
    }

    void GetAttributeList(char** attrib, int &attrib_count) const
    {
      imImageGetAttributeList(im_image, attrib, &attrib_count);
    }


    /* compare */
    bool operator==(const Image& image2) const
    {
      return Match(image2);
    }
    bool Match(const Image& image2) const
    {
      return imImageMatch(im_image, image2.im_image) == 1;
    }
    bool MatchColor(const Image& image2) const
    {
      return imImageMatchColor(im_image, image2.im_image) == 1;
    }
    bool MatchColorSpace(const Image& image2) const
    {
      return imImageMatchColorSpace(im_image, image2.im_image) == 1;
    }
    bool MatchDataType(const Image& image2) const
    {
      return imImageMatchDataType(im_image, image2.im_image) == 1;
    }
    bool MatchSize(const Image& image2) const
    {
      return imImageMatchSize(im_image, image2.im_image) == 1;
    }


    /* conversion */
    int ConvertDataType(Image& dst_image, int cpx2real, float gamma, bool absolute, int cast_mode) const
    {
      return imConvertDataType(im_image, dst_image.im_image, cpx2real, gamma, absolute, cast_mode);
    }
    int ConvertColorSpace(Image& dst_image) const
    {
      return imConvertColorSpace(im_image, dst_image.im_image);
    }
    int ConvertToBitmap(Image& dst_image, int cpx2real, float gamma, bool absolute, int cast_mode)
    {
      return imConvertToBitmap(im_image, dst_image.im_image, cpx2real, gamma, absolute, cast_mode);
    }

  };


  /********************************************************************/


  class CounterCallback
  {
    void* cc_user_data;

    static int c_callback(int counter, void* user_data, const char* text, int progress)
    {
      CounterCallback* cc = (CounterCallback*)user_data;
      return cc->Callback(counter, cc->cc_user_data, text, progress);
    }

  public:
    CounterCallback(void* user_data)
    {
      cc_user_data = user_data;
      imCounterSetCallback(this, c_callback);
    }
    virtual ~CounterCallback()
    {
    }

    virtual int Callback(int counter, void* user_data, const char* text, int progress) = 0;
  };


  /********************************************************************/


  class File
  {
    friend class Image;

    /* forbidden */
    File(const File&) { }

  protected:
    imFile* im_file;

    File() { im_file = 0; }

  public:
    File(const char* file_name, int &error)
    {
      im_file = imFileOpen(file_name, &error);
    }
    File(const char* file_name, const char* format, int &error)
    {
      im_file = imFileNew(file_name, format, &error);
    }
    File(imFile* ref_file)
    {
      im_file = ref_file;
    }
    ~File()
    {
      if (im_file) 
        imFileClose(im_file);
    }

    bool Failed() const
    {
      return im_file == 0;
    }


    /* attributes or metadata */
    void SetAttribute(const char* attrib, int data_type, int count, const void* data)
    {
      imFileSetAttribute(im_file, attrib, data_type, count, data);
    }
    void SetAttribInteger(const char* attrib, int data_type, int value)
    {
      imFileSetAttribInteger(im_file, attrib, data_type, value);
    }
    void SetAttribReal(const char* attrib, int data_type, double value)
    {
      imFileSetAttribReal(im_file, attrib, data_type, value);
    }
    void SetAttribString(const char* attrib, const char* value)
    {
      imFileSetAttribString(im_file, attrib, value);
    }
    const void* GetAttribute(const char* attrib, int &data_type, int &count) const
    {
      return imFileGetAttribute(im_file, attrib, &data_type, &count);
    }
    int GetAttribInteger(const char* attrib, int index) const
    {
      return imFileGetAttribInteger(im_file, attrib, index);
    }
    double GetAttribReal(const char* attrib, int index) const
    {
      return imFileGetAttribReal(im_file, attrib, index);
    }
    const char* GetAttribString(const char* attrib)
    {
      return imFileGetAttribString(im_file, attrib);
    }


    /* file info */
    void GetInfo(char* format, char* compression, int &image_count)
    {
      imFileGetInfo(im_file, format, compression, &image_count);
    }
    void SetInfo(const char* compression)
    {
      imFileSetInfo(im_file, compression);
    }


    /* image io */
    Image LoadImage(int index, int &error)
    {
      return Image(imFileLoadImage(im_file, index, &error));
    }
    int SaveImage(const Image& im_image)
    {
      return imFileSaveImage(im_file, im_image.im_image);
    }
    void LoadFrame(int index, Image& im_image, int &error, bool as_bitmap)
    {
      if (as_bitmap)
        imFileLoadBitmapFrame(im_file, index, im_image.im_image, &error);
      else
        imFileLoadImageFrame(im_file, index, im_image.im_image, &error);
    }
  };


  /********************************************************************/


  class FileRaw : public File
  {
    /* forbidden */
    FileRaw() {}
    FileRaw(const FileRaw&) {}

  public:

    FileRaw(const char* file_name, int &error, bool new_file) : File()
    {
      if (new_file) 
        im_file = imFileNewRaw(file_name, &error);
      else 
        im_file = imFileOpenRaw(file_name, &error);
    }
  };


  /********************************************************************/


  class FormatList
  {
    /* forbidden */
    FormatList(const FormatList&) {}

  public:
    FormatList()
    {
      imFormatRegisterInternal();
    }
    ~FormatList()
    {
      imFormatRemoveAll();
    }

    static void GetList(char** format_list, int &format_count)
    {
      imFormatList(format_list, &format_count);
    }

    static int FormatInfo(const char* format, char* desc, char* ext, int &can_sequence)
    {
      return imFormatInfo(format, desc, ext, &can_sequence);
    }
    static int FormatInfoExtra(const char* format, char* extra)
    {
      return imFormatInfoExtra(format, extra);
    }
    static int FormatGetCompressions(const char* format, char** comp, int &comp_count, int color_mode, int data_type)
    {
      return imFormatCompressions(format, comp, &comp_count, color_mode, data_type);
    }
    static int FormatCanWriteImage(const char* format, const char* compression, int color_mode, int data_type)
    {
      return imFormatCanWriteImage(format, compression, color_mode, data_type);
    }
  };


  /********************************************************************/


  class VideoCaptureDeviceList
  {
    /* forbidden */
    VideoCaptureDeviceList(const VideoCaptureDeviceList&) {}

  public:
    VideoCaptureDeviceList()
    {
      imVideoCaptureReloadDevices();
    }
    ~VideoCaptureDeviceList()
    {
      imVideoCaptureReleaseDevices();
    }

    static int Count() 
    {
      return imVideoCaptureDeviceCount();
    }

    static const char* DeviceDescription(int device) 
    {
      return imVideoCaptureDeviceDesc(device);
    }
    static const char* DeviceExtendedDescription(int device) 
    {
      return imVideoCaptureDeviceExDesc(device);
    }
    static const char* DevicePath(int device) 
    {
      return imVideoCaptureDevicePath(device);
    }
    static const char* DeviceVendorInfo(int device) 
    {
      return imVideoCaptureDeviceVendorInfo(device);
    }
  };


  /********************************************************************/


  class VideoCapture
  {
    /* forbidden */
    VideoCapture(const VideoCapture&) {}

  protected:
    imVideoCapture* im_vc;

  public:
    VideoCapture()
    {
      im_vc = imVideoCaptureCreate();
    }
    VideoCapture(imVideoCapture* ref_vc)
    {
      im_vc = ref_vc;
    }
    ~VideoCapture()
    {
      if (im_vc) 
        imVideoCaptureDestroy(im_vc);
    }

    bool Failed() const
    {
      return im_vc == 0;
    }


    /* capture connection */
    int Connect(int device)
    {
      return imVideoCaptureConnect(im_vc, device);
    }
    void Disconnect()
    {
      imVideoCaptureDisconnect(im_vc);
    }
    bool SetInOut(int input, int output, int cross)
    {
      return imVideoCaptureSetInOut(im_vc, input, output, cross) != 0;
    }
    bool GetLive() const
    {
      return imVideoCaptureLive(im_vc, -1) == 1;
    }
    bool SetLive(int live)
    {
      return imVideoCaptureLive(im_vc, live) != 0;
    }


    /* configuration dialogs */
    int DialogCount() const
    {
      return imVideoCaptureDialogCount(im_vc);
    }
    bool ShowDialog(int dialog, void* parent)
    {
      return imVideoCaptureShowDialog(im_vc, dialog, parent) != 0;
    }
    const char* DialogDescription(int dialog) const
    {
      return imVideoCaptureDialogDesc(im_vc, dialog);
    }


    /* video format */
    int FormatCount() const
    {
      return imVideoCaptureFormatCount(im_vc);
    }
    bool GetFormatInfo(int format, int &width, int &height, char* desc) const
    {
      return imVideoCaptureGetFormat(im_vc, format, &width, &height, desc) != 0;
    }
    int GetFormat() const
    {
      return imVideoCaptureSetFormat(im_vc, -1);
    }
    bool SetFormat(int format)
    {
      return imVideoCaptureSetFormat(im_vc, format) != 0;
    }


    /* image info */
    void GetImageSize(int &width, int &height) const
    {
      imVideoCaptureGetImageSize(im_vc, &width, &height);
    }
    bool SetImageSize(int width, int height)
    {
      return imVideoCaptureSetImageSize(im_vc, width, height) != 0;
    }


    /* image capture */
    Image CaptureImage(bool as_gray)
    {
      int width, height;
      GetImageSize(width, height);
      return Image(imImageCreate(width, height, as_gray ? IM_GRAY : IM_RGB, IM_BYTE));
    }
    bool CaptureFrame(Image& dst_image, int timeout = -1)
    {
      if (dst_image.im_image->color_space != IM_GRAY && 
          dst_image.im_image->color_space != IM_RGB &&
          dst_image.im_image->data_type != IM_BYTE)
        return false;

      return imVideoCaptureFrame(im_vc, (unsigned char*)dst_image.im_image->data[0], dst_image.im_image->color_space, timeout) != 0;
    }
    bool CaptureOneFrame(Image& dst_image)
    {
      if (dst_image.im_image->color_space != IM_GRAY &&
          dst_image.im_image->color_space != IM_RGB &&
          dst_image.im_image->data_type != IM_BYTE)
        return false;

      return imVideoCaptureOneFrame(im_vc, (unsigned char*)dst_image.im_image->data[0], dst_image.im_image->color_space) != 0;
    }


    /* attributes */
    bool ResetAttribute(const char* attrib, int fauto)
    {
      return imVideoCaptureResetAttribute(im_vc, attrib, fauto) != 0;
    }
    bool GetAttribute(const char* attrib, float &percent) const
    {
      return imVideoCaptureGetAttribute(im_vc, attrib, &percent) != 0;
    }
    bool SetAttribute(const char* attrib, float percent)
    {
      return imVideoCaptureSetAttribute(im_vc, attrib, percent) != 0;
    }
    const char** GetAttributeList(int &num_attrib) const
    {
      return imVideoCaptureGetAttributeList(im_vc, &num_attrib);
    }
  };


  /********************************************************************/


  class Kernel
  {
  public:
    /* pre-defined kernels */
    static Image Sobel()
    {
      return Image(imKernelSobel());
    }
    static Image Prewitt()
    {
      return Image(imKernelPrewitt());
    }
    static Image Kirsh()
    {
      return Image(imKernelKirsh());
    }
    static Image Laplacian4()
    {
      return Image(imKernelLaplacian4());
    }
    static Image Laplacian8()
    {
      return Image(imKernelLaplacian8());
    }
    static Image Laplacian5x5()
    {
      return Image(imKernelLaplacian5x5());
    }
    static Image Laplacian7x7()
    {
      return Image(imKernelLaplacian7x7());
    }
    static Image Gradian3x3()
    {
      return Image(imKernelGradian3x3());
    }
    static Image Gradian7x7()
    {
      return Image(imKernelGradian7x7());
    }
    static Image Sculpt()
    {
      return Image(imKernelSculpt());
    }
    static Image Mean3x3()
    {
      return Image(imKernelMean3x3());
    }
    static Image Mean5x5()
    {
      return Image(imKernelMean5x5());
    }
    static Image CircularMean5x5()
    {
      return Image(imKernelCircularMean5x5());
    }
    static Image Mean7x7()
    {
      return Image(imKernelMean7x7());
    }
    static Image CircularMean7x7()
    {
      return Image(imKernelCircularMean7x7());
    }
    static Image Gaussian3x3()
    {
      return Image(imKernelGaussian3x3());
    }
    static Image Gaussian5x5()
    {
      return Image(imKernelGaussian5x5());
    }
    static Image Barlett5x5()
    {
      return Image(imKernelBarlett5x5());
    }
    static Image TopHat5x5()
    {
      return Image(imKernelTopHat5x5());
    }
    static Image TopHat7x7()
    {
      return Image(imKernelTopHat7x7());
    }
    static Image Enhance()
    {
      return Image(imKernelEnhance());
    }
  };


  class Process
  {
  public:

    static int GaussianStdDev2KernelSize(float stddev)
    {
      return imGaussianStdDev2KernelSize(stddev);
    }
    static float GaussianKernelSize2StdDev(int kernel_size)
    {
      return imGaussianKernelSize2StdDev(kernel_size);
    }
    static void CalcRotateSize(int width, int height, int &new_width, int &new_height, double cos0, double sin0)
    {
      imProcessCalcRotateSize(width, height, &new_width, &new_height, cos0, sin0);
    }
    static int OpenMPSetMinCount(int min_count)
    {
      return imProcessOpenMPSetMinCount(min_count);
    }
    static int OpenMPSetNumThreads(int count)
    {
      return imProcessOpenMPSetNumThreads(count);
    }

    static int HoughLines(const Image& src_image, Image& dst_image)
    {
      return imProcessHoughLines(src_image.im_image, dst_image.im_image);
    }
    static int HoughLinesDraw(const Image& src_image, const Image& hough, const Image& hough_points, Image& dst_image)
    {
      return imProcessHoughLinesDraw(src_image.im_image, hough.im_image, hough_points.im_image, dst_image.im_image);
    }
    static void CrossCorrelation(const Image& src_image1, const Image& src_image2, Image& dst_image)
    {
      imProcessCrossCorrelation(src_image1.im_image, src_image2.im_image, dst_image.im_image);
    }
    static void AutoCorrelation(const Image& src_image, Image& dst_image)
    {
      imProcessAutoCorrelation(src_image.im_image, dst_image.im_image);
    }
    static void DistanceTransform(const Image& src_image, Image& dst_image)
    {
      imProcessDistanceTransform(src_image.im_image, dst_image.im_image);
    }
    static void RegionalMaximum(const Image& src_image, Image& dst_image)
    {
      imProcessRegionalMaximum(src_image.im_image, dst_image.im_image);
    }
    static void FFT(const Image& src_image, Image& dst_image)
    {
      imProcessFFT(src_image.im_image, dst_image.im_image);
    }
    static void IFFT(const Image& src_image, Image& dst_image)
    {
      imProcessIFFT(src_image.im_image, dst_image.im_image);
    }
    static int UnaryPointOp(const Image& src_image, Image& dst_image, imUnaryPointOpFunc func, float* params, void* userdata, const char* op_name)
    {
      return imProcessUnaryPointOp(src_image.im_image, dst_image.im_image, func, params, userdata, op_name);
    }
    static int UnaryPointColorOp(const Image& src_image, Image& dst_image, imUnaryPointColorOpFunc func, float* params, void* userdata, const char* op_name)
    {
      return imProcessUnaryPointColorOp(src_image.im_image, dst_image.im_image, func, params, userdata, op_name);
    }
    static int MultiPointOp(const Image *src_image_list, int src_image_count, Image& dst_image, imMultiPointOpFunc func, float* params, void* userdata, const char* op_name)
    {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].im_image;
      int ret = imProcessMultiPointOp((const imImage**)c_src_image_list, src_image_count, dst_image.im_image, func, params, userdata, op_name);
      delete[] c_src_image_list;
      return ret;
    }
    static int MultiPointColorOp(const Image *src_image_list, int src_image_count, Image& dst_image, imMultiPointColorOpFunc func, float* params, void* userdata, const char* op_name)
    {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].im_image;
      int ret = imProcessMultiPointColorOp((const imImage**)c_src_image_list, src_image_count, dst_image.im_image, func, params, userdata, op_name);
      delete[] c_src_image_list;
      return ret;
    }
    static void UnArithmeticOp(const Image& src_image, Image& dst_image, int op)
    {
      imProcessUnArithmeticOp(src_image.im_image, dst_image.im_image, op);
    }
    static void ArithmeticOp(const Image& src_image1, const Image& src_image2, Image& dst_image, int op)
    {
      imProcessArithmeticOp(src_image1.im_image, src_image2.im_image, dst_image.im_image, op);
    }
    static void ArithmeticConstOp(const Image& src_image, float src_const, Image& dst_image, int op)
    {
      imProcessArithmeticConstOp(src_image.im_image, src_const, dst_image.im_image, op);
    }
    static void BlendConst(const Image& src_image1, const Image& src_image2, Image& dst_image, float alpha)
    {
      imProcessBlendConst(src_image1.im_image, src_image2.im_image, dst_image.im_image, alpha);
    }
    static void Blend(const Image& src_image1, const Image& src_image2, const Image& alpha_image, Image& dst_image)
    {
      imProcessBlend(src_image1.im_image, src_image2.im_image, alpha_image.im_image, dst_image.im_image);
    }
    static void Compose(const Image& src_image1, const Image& src_image2, Image& dst_image)
    {
      imProcessCompose(src_image1.im_image, src_image2.im_image, dst_image.im_image);
    }
    static void SplitComplex(const Image& src_image, Image& dst_image1, Image& dst_image2, int polar)
    {
      imProcessSplitComplex(src_image.im_image, dst_image1.im_image, dst_image2.im_image, polar);
    }
    static void MergeComplex(const Image& src_image1, const Image& src_image2, Image& dst_image, int polar)
    {
      imProcessMergeComplex(src_image1.im_image, src_image2.im_image, dst_image.im_image, polar);
    }
    static void MultipleMean(const Image *src_image_list, int src_image_count, Image& dst_image)
    {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].im_image;
      imProcessMultipleMean((const imImage**)c_src_image_list, src_image_count, dst_image.im_image);
      delete[] c_src_image_list;
    }
    static void MultipleStdDev(const Image *src_image_list, int src_image_count, const Image& mean_image, Image& dst_image)
    {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].im_image;
      imProcessMultipleStdDev((const imImage**)c_src_image_list, src_image_count, mean_image.im_image, dst_image.im_image);
      delete[] c_src_image_list;
    }
    static int MultipleMedian(const Image *src_image_list, int src_image_count, Image& dst_image)
    {
      imImage** c_src_image_list = new imImage*[src_image_count];
      for (int i = 0; i < src_image_count; i++) c_src_image_list[i] = src_image_list[i].im_image;
      return imProcessMultipleMedian((const imImage**)c_src_image_list, src_image_count, dst_image.im_image);
      delete[] c_src_image_list;
    }
    static int AutoCovariance(const Image& src_image, const Image& mean_image, Image& dst_image)
    {
      return imProcessAutoCovariance(src_image.im_image, mean_image.im_image, dst_image.im_image);
    }
    static void MultiplyConj(const Image& src_image1, const Image& src_image2, Image& dst_image)
    {
      imProcessMultiplyConj(src_image1.im_image, src_image2.im_image, dst_image.im_image);
    }
    static void QuantizeRGBUniform(const Image& src_image, Image& dst_image, int do_dither)
    {
      imProcessQuantizeRGBUniform(src_image.im_image, dst_image.im_image, do_dither);
    }
    static void QuantizeGrayUniform(const Image& src_image, Image& dst_image, int grays)
    {
      imProcessQuantizeGrayUniform(src_image.im_image, dst_image.im_image, grays);
    }
    static void ExpandHistogram(const Image& src_image, Image& dst_image, float percent)
    {
      imProcessExpandHistogram(src_image.im_image, dst_image.im_image, percent);
    }
    static void EqualizeHistogram(const Image& src_image, Image& dst_image)
    {
      imProcessEqualizeHistogram(src_image.im_image, dst_image.im_image);
    }
    static void SplitYChroma(const Image& src_image, Image& y_image, Image& chroma_image)
    {
      imProcessSplitYChroma(src_image.im_image, y_image.im_image, chroma_image.im_image);
    }
    static void SplitHSI(const Image& src_image, Image& h_image, Image& s_image, Image& i_image)
    {
      imProcessSplitHSI(src_image.im_image, h_image.im_image, s_image.im_image, i_image.im_image);
    }
    static void MergeHSI(const Image& h_image, const Image& s_image, const Image& i_image, Image& dst_image)
    {
      imProcessMergeHSI(h_image.im_image, s_image.im_image, i_image.im_image, dst_image.im_image);
    }
    static void SplitComponents(const Image& src_image, Image *dst_image_list)
    {
      imImage* c_dst_image_list[4];
      c_dst_image_list[0] = dst_image_list[0].im_image;
      c_dst_image_list[1] = dst_image_list[1].im_image;
      c_dst_image_list[2] = dst_image_list[2].im_image;
      if (src_image.Depth() == 4 || src_image.HasAlpha())
        c_dst_image_list[3] = dst_image_list[3].im_image;
      imProcessSplitComponents(src_image.im_image, c_dst_image_list);
    }
    static void MergeComponents(const Image *src_image_list, Image& dst_image)
    {
      imImage* c_src_image_list[4];
      c_src_image_list[0] = src_image_list[0].im_image;
      c_src_image_list[1] = src_image_list[1].im_image;
      c_src_image_list[2] = src_image_list[2].im_image;
      if (dst_image.Depth() == 4 || dst_image.HasAlpha())
        c_src_image_list[3] = src_image_list[3].im_image;
      imProcessMergeComponents((const imImage**)c_src_image_list, dst_image.im_image);
    }
    static void NormalizeComponents(const Image& src_image, Image& dst_image)
    {
      imProcessNormalizeComponents(src_image.im_image, dst_image.im_image);
    }
    static void ReplaceColor(const Image& src_image, Image& dst_image, float* src_color, float* dst_color)
    {
      imProcessReplaceColor(src_image.im_image, dst_image.im_image, src_color, dst_color);
    }
    static void SetAlphaColor(const Image& src_image, Image& dst_image, float* src_color, float dst_alpha)
    {
      imProcessSetAlphaColor(src_image.im_image, dst_image.im_image, src_color, dst_alpha);
    }
    static void BitwiseOp(const Image& src_image1, const Image& src_image2, Image& dst_image, int op)
    {
      imProcessBitwiseOp(src_image1.im_image, src_image2.im_image, dst_image.im_image, op);
    }
    static void BitwiseNot(const Image& src_image, Image& dst_image)
    {
      imProcessBitwiseNot(src_image.im_image, dst_image.im_image);
    }
    static void BitMask(const Image& src_image, Image& dst_image, unsigned char mask, int op)
    {
      imProcessBitMask(src_image.im_image, dst_image.im_image, mask, op);
    }
    static void BitPlane(const Image& src_image, Image& dst_image, int plane, int do_reset)
    {
      imProcessBitPlane(src_image.im_image, dst_image.im_image, plane, do_reset);
    }
    static int RenderAddSpeckleNoise(const Image& src_image, Image& dst_image, float percent)
    {
      return imProcessRenderAddSpeckleNoise(src_image.im_image, dst_image.im_image, percent);
    }
    static int RenderAddGaussianNoise(const Image& src_image, Image& dst_image, float mean, float stddev)
    {
      return imProcessRenderAddGaussianNoise(src_image.im_image, dst_image.im_image, mean, stddev);
    }
    static int RenderAddUniformNoise(const Image& src_image, Image& dst_image, float mean, float stddev)
    {
      return imProcessRenderAddUniformNoise(src_image.im_image, dst_image.im_image, mean, stddev);
    }
    static void ToneGamut(const Image& src_image, Image& dst_image, int op, float* params)
    {
      imProcessToneGamut(src_image.im_image, dst_image.im_image, op, params);
    }
    static void UnNormalize(const Image& src_image, Image& dst_image)
    {
      imProcessUnNormalize(src_image.im_image, dst_image.im_image);
    }
    static void DirectConv(const Image& src_image, Image& dst_image)
    {
      imProcessDirectConv(src_image.im_image, dst_image.im_image);
    }
    static void Negative(const Image& src_image, Image& dst_image)
    {
      imProcessNegative(src_image.im_image, dst_image.im_image);
    }
    static float CalcAutoGamma(const Image& image)
    {
      return imProcessCalcAutoGamma(image.im_image);
    }
    static void ShiftHSI(const Image& src_image, Image& dst_image, float h_shift, float s_shift, float i_shift)
    {
      imProcessShiftHSI(src_image.im_image, dst_image.im_image, h_shift, s_shift, i_shift);
    }
    static void Threshold(const Image& src_image, Image& dst_image, float level, int value)
    {
      imProcessThreshold(src_image.im_image, dst_image.im_image, level, value);
    }
    static void ThresholdByDiff(const Image& src_image1, const Image& src_image2, Image& dst_image)
    {
      imProcessThresholdByDiff(src_image1.im_image, src_image2.im_image, dst_image.im_image);
    }
    static void HysteresisThreshold(const Image& src_image, Image& dst_image, int low_thres, int high_thres)
    {
      imProcessHysteresisThreshold(src_image.im_image, dst_image.im_image, low_thres, high_thres);
    }
    static void HysteresisThresEstimate(const Image& image, int &low_level, int &high_level)
    {
      imProcessHysteresisThresEstimate(image.im_image, &low_level, &high_level);
    }
    static int UniformErrThreshold(const Image& src_image, Image& dst_image)
    {
      return imProcessUniformErrThreshold(src_image.im_image, dst_image.im_image);
    }
    static void DifusionErrThreshold(const Image& src_image, Image& dst_image, int level)
    {
      imProcessDifusionErrThreshold(src_image.im_image, dst_image.im_image, level);
    }
    static int PercentThreshold(const Image& src_image, Image& dst_image, float percent)
    {
      return imProcessPercentThreshold(src_image.im_image, dst_image.im_image, percent);
    }
    static int OtsuThreshold(const Image& src_image, Image& dst_image)
    {
      return imProcessOtsuThreshold(src_image.im_image, dst_image.im_image);
    }
    static float MinMaxThreshold(const Image& src_image, Image& dst_image)
    {
      return imProcessMinMaxThreshold(src_image.im_image, dst_image.im_image);
    }
    static void LocalMaxThresEstimate(const Image& image, int &level)
    {
      imProcessLocalMaxThresEstimate(image.im_image, &level);
    }
    static void SliceThreshold(const Image& src_image, Image& dst_image, float start_level, float end_level)
    {
      imProcessSliceThreshold(src_image.im_image, dst_image.im_image, start_level, end_level);
    }
    static void Pixelate(const Image& src_image, Image& dst_image, int box_size)
    {
      imProcessPixelate(src_image.im_image, dst_image.im_image, box_size);
    }
    static void Posterize(const Image& src_image, Image& dst_image, int level)
    {
      imProcessPosterize(src_image.im_image, dst_image.im_image, level);
    }
    static void NormDiffRatio(const Image& image1, const Image& image2, Image& dst_image)
    {
      imProcessNormDiffRatio(image1.im_image, image2.im_image, dst_image.im_image);
    }
    static void AbnormalHyperionCorrection(const Image& src_image, Image& dst_image, int threshold_consecutive, int threshold_percent, Image& image_abnormal)
    {
      imProcessAbnormalHyperionCorrection(src_image.im_image, dst_image.im_image, threshold_consecutive, threshold_percent, image_abnormal.im_image);
    }
    static int ConvertDataType(const Image& src_image, Image& dst_image, int cpx2real, float gamma, int absolute, int cast_mode)
    {
      return imProcessConvertDataType(src_image.im_image, dst_image.im_image, cpx2real, gamma, absolute, cast_mode);
    }
    static int ConvertColorSpace(const Image& src_image, Image& dst_image)
    {
      return imProcessConvertColorSpace(src_image.im_image, dst_image.im_image);
    }
    static int ConvertToBitmap(const Image& src_image, Image& dst_image, int cpx2real, float gamma, int absolute, int cast_mode)
    {
      return imProcessConvertToBitmap(src_image.im_image, dst_image.im_image, cpx2real, gamma, absolute, cast_mode);
    }
    static int Reduce(const Image& src_image, Image& dst_image, int order)
    {
      return imProcessReduce(src_image.im_image, dst_image.im_image, order);
    }
    static int Resize(const Image& src_image, Image& dst_image, int order)
    {
      return imProcessResize(src_image.im_image, dst_image.im_image, order);
    }
    static void ReduceBy4(const Image& src_image, Image& dst_image)
    {
      imProcessReduceBy4(src_image.im_image, dst_image.im_image);
    }
    static void Crop(const Image& src_image, Image& dst_image, int xmin, int ymin)
    {
      imProcessCrop(src_image.im_image, dst_image.im_image, xmin, ymin);
    }
    static void Insert(const Image& src_image, const Image& region_image, Image& dst_image, int xmin, int ymin)
    {
      imProcessInsert(src_image.im_image, region_image.im_image, dst_image.im_image, xmin, ymin);
    }
    static void AddMargins(const Image& src_image, Image& dst_image, int xmin, int ymin)
    {
      imProcessAddMargins(src_image.im_image, dst_image.im_image, xmin, ymin);
    }
    static int Rotate(const Image& src_image, Image& dst_image, double cos0, double sin0, int order)
    {
      return imProcessRotate(src_image.im_image, dst_image.im_image, cos0, sin0, order);
    }
    static int RotateRef(const Image& src_image, Image& dst_image, double cos0, double sin0, int x, int y, int to_origin, int order)
    {
      return imProcessRotateRef(src_image.im_image, dst_image.im_image, cos0, sin0, x, y, to_origin, order);
    }
    static void Rotate90(const Image& src_image, Image& dst_image, int dir_clockwise)
    {
      imProcessRotate90(src_image.im_image, dst_image.im_image, dir_clockwise);
    }
    static void Rotate180(const Image& src_image, Image& dst_image)
    {
      imProcessRotate180(src_image.im_image, dst_image.im_image);
    }
    static void Mirror(const Image& src_image, Image& dst_image)
    {
      imProcessMirror(src_image.im_image, dst_image.im_image);
    }
    static void Flip(const Image& src_image, Image& dst_image)
    {
      imProcessFlip(src_image.im_image, dst_image.im_image);
    }
    static int Radial(const Image& src_image, Image& dst_image, float k1, int order)
    {
      return imProcessRadial(src_image.im_image, dst_image.im_image, k1, order);
    }
    static int Swirl(const Image& src_image, Image& dst_image, float k1, int order)
    {
      return imProcessSwirl(src_image.im_image, dst_image.im_image, k1, order);
    }
    static void InterlaceSplit(const Image& src_image, Image& dst_image1, Image& dst_image2)
    {
      imProcessInterlaceSplit(src_image.im_image, dst_image1.im_image, dst_image2.im_image);
    }
    static int GrayMorphConvolve(const Image& src_image, Image& dst_image, const Image& kernel, int ismax)
    {
      return imProcessGrayMorphConvolve(src_image.im_image, dst_image.im_image, kernel.im_image, ismax);
    }
    static int GrayMorphErode(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessGrayMorphErode(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int GrayMorphDilate(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessGrayMorphDilate(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int GrayMorphOpen(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessGrayMorphOpen(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int GrayMorphClose(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessGrayMorphClose(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int GrayMorphTopHat(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessGrayMorphTopHat(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int GrayMorphWell(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessGrayMorphWell(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int GrayMorphGradient(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessGrayMorphGradient(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int BinMorphConvolve(const Image& src_image, Image& dst_image, const Image& kernel, int hit_white, int iter)
    {
      return imProcessBinMorphConvolve(src_image.im_image, dst_image.im_image, kernel.im_image, hit_white, iter);
    }
    static int BinMorphErode(const Image& src_image, Image& dst_image, int kernel_size, int iter)
    {
      return imProcessBinMorphErode(src_image.im_image, dst_image.im_image, kernel_size, iter);
    }
    static int BinMorphDilate(const Image& src_image, Image& dst_image, int kernel_size, int iter)
    {
      return imProcessBinMorphDilate(src_image.im_image, dst_image.im_image, kernel_size, iter);
    }
    static int BinMorphOpen(const Image& src_image, Image& dst_image, int kernel_size, int iter)
    {
      return imProcessBinMorphOpen(src_image.im_image, dst_image.im_image, kernel_size, iter);
    }
    static int BinMorphClose(const Image& src_image, Image& dst_image, int kernel_size, int iter)
    {
      return imProcessBinMorphClose(src_image.im_image, dst_image.im_image, kernel_size, iter);
    }
    static int BinMorphOutline(const Image& src_image, Image& dst_image, int kernel_size, int iter)
    {
      return imProcessBinMorphOutline(src_image.im_image, dst_image.im_image, kernel_size, iter);
    }
    static void BinMorphThin(const Image& src_image, Image& dst_image)
    {
      imProcessBinMorphThin(src_image.im_image, dst_image.im_image);
    }
    static int MedianConvolve(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessMedianConvolve(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int RangeConvolve(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessRangeConvolve(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int RankClosestConvolve(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessRankClosestConvolve(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int RankMaxConvolve(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessRankMaxConvolve(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int RankMinConvolve(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessRankMinConvolve(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int RangeContrastThreshold(const Image& src_image, Image& dst_image, int kernel_size, int min_range)
    {
      return imProcessRangeContrastThreshold(src_image.im_image, dst_image.im_image, kernel_size, min_range);
    }
    static int LocalMaxThreshold(const Image& src_image, Image& dst_image, int kernel_size, int min_level)
    {
      return imProcessLocalMaxThreshold(src_image.im_image, dst_image.im_image, kernel_size, min_level);
    }
    static int Convolve(const Image& src_image, Image& dst_image, const Image& kernel)
    {
      return imProcessConvolve(src_image.im_image, dst_image.im_image, kernel.im_image);
    }
    static int ConvolveSep(const Image& src_image, Image& dst_image, const Image& kernel)
    {
      return imProcessConvolveSep(src_image.im_image, dst_image.im_image, kernel.im_image);
    }
    static int ConvolveDual(const Image& src_image, Image& dst_image, const Image& kernel1, const Image& kernel2)
    {
      return imProcessConvolveDual(src_image.im_image, dst_image.im_image, kernel1.im_image, kernel2.im_image);
    }
    static int ConvolveRep(const Image& src_image, Image& dst_image, const Image& kernel, int count)
    {
      return imProcessConvolveRep(src_image.im_image, dst_image.im_image, kernel.im_image, count);
    }
    static int CompassConvolve(const Image& src_image, Image& dst_image, Image& kernel)
    {
      return imProcessCompassConvolve(src_image.im_image, dst_image.im_image, kernel.im_image);
    }
    static int DiffOfGaussianConvolve(const Image& src_image, Image& dst_image, float stddev1, float stddev2)
    {
      return imProcessDiffOfGaussianConvolve(src_image.im_image, dst_image.im_image, stddev1, stddev2);
    }
    static int LapOfGaussianConvolve(const Image& src_image, Image& dst_image, float stddev)
    {
      return imProcessLapOfGaussianConvolve(src_image.im_image, dst_image.im_image, stddev);
    }
    static int MeanConvolve(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessMeanConvolve(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int GaussianConvolve(const Image& src_image, Image& dst_image, float stddev)
    {
      return imProcessGaussianConvolve(src_image.im_image, dst_image.im_image, stddev);
    }
    static int BarlettConvolve(const Image& src_image, Image& dst_image, int kernel_size)
    {
      return imProcessBarlettConvolve(src_image.im_image, dst_image.im_image, kernel_size);
    }
    static int SobelConvolve(const Image& src_image, Image& dst_image)
    {
      return imProcessSobelConvolve(src_image.im_image, dst_image.im_image);
    }
    static int PrewittConvolve(const Image& src_image, Image& dst_image)
    {
      return imProcessPrewittConvolve(src_image.im_image, dst_image.im_image);
    }
    static int SplineEdgeConvolve(const Image& src_image, Image& dst_image)
    {
      return imProcessSplineEdgeConvolve(src_image.im_image, dst_image.im_image);
    }
    static void ZeroCrossing(const Image& src_image, Image& dst_image)
    {
      imProcessZeroCrossing(src_image.im_image, dst_image.im_image);
    }
    static void Canny(const Image& src_image, Image& dst_image, float stddev)
    {
      imProcessCanny(src_image.im_image, dst_image.im_image, stddev);
    }
    static int Unsharp(const Image& src_image, Image& dst_image, float stddev, float amount, float threshold)
    {
      return imProcessUnsharp(src_image.im_image, dst_image.im_image, stddev, amount, threshold);
    }
    static int Sharp(const Image& src_image, Image& dst_image, float amount, float threshold)
    {
      return imProcessSharp(src_image.im_image, dst_image.im_image, amount, threshold);
    }
    static int SharpKernel(const Image& src_image, const Image& kernel, Image& dst_image, float amount, float threshold)
    {
      return imProcessSharpKernel(src_image.im_image, kernel.im_image, dst_image.im_image, amount, threshold);
    }
    static void PerimeterLine(const Image& src_image, Image& dst_image)
    {
      imProcessPerimeterLine(src_image.im_image, dst_image.im_image);
    }
    static void RemoveByArea(const Image& src_image, Image& dst_image, int connect, int start_size, int end_size, int inside)
    {
      imProcessRemoveByArea(src_image.im_image, dst_image.im_image, connect, start_size, end_size, inside);
    }
    static void FillHoles(const Image& src_image, Image& dst_image, int connect)
    {
      imProcessFillHoles(src_image.im_image, dst_image.im_image, connect);
    }
    static void RotateKernel(Image& kernel)
    {
      imProcessRotateKernel(kernel.im_image);
    }
    static void FFTraw(Image& image, int inverse, int center, int normalize)
    {
      imProcessFFTraw(image.im_image, inverse, center, normalize);
    }
    static void SwapQuadrants(Image& image, int center2origin)
    {
      imProcessSwapQuadrants(image.im_image, center2origin);
    }

    static int RenderOp(Image& image, imRenderFunc render_func, const char* render_name, float* params, int plus)
    {
      return imProcessRenderOp(image.im_image, render_func, render_name, params, plus);
    }
    static int RenderCondOp(Image& image, imRenderCondFunc render_cond_func, const char* render_name, float* params)
    {
      return imProcessRenderCondOp(image.im_image, render_cond_func, render_name, params);
    }
    static int RenderRandomNoise(Image& image)
    {
      return imProcessRenderRandomNoise(image.im_image);
    }
    static int RenderConstant(Image& image, float* value)
    {
      return imProcessRenderConstant(image.im_image, value);
    }
    static int RenderWheel(Image& image, int internal_radius, int external_radius)
    {
      return imProcessRenderWheel(image.im_image, internal_radius, external_radius);
    }
    static int RenderCone(Image& image, int radius)
    {
      return imProcessRenderCone(image.im_image, radius);
    }
    static int RenderTent(Image& image, int tent_width, int tent_height)
    {
      return imProcessRenderTent(image.im_image, tent_width, tent_height);
    }
    static int RenderRamp(Image& image, int start, int end, int vert_dir)
    {
      return imProcessRenderRamp(image.im_image, start, end, vert_dir);
    }
    static int RenderBox(Image& image, int box_width, int box_height)
    {
      return imProcessRenderBox(image.im_image, box_width, box_height);
    }
    static int RenderSinc(Image& image, float x_period, float y_period)
    {
      return imProcessRenderSinc(image.im_image, x_period, y_period);
    }
    static int RenderGaussian(Image& image, float stddev)
    {
      return imProcessRenderGaussian(image.im_image, stddev);
    }
    static int RenderLapOfGaussian(Image& image, float stddev)
    {
      return imProcessRenderLapOfGaussian(image.im_image, stddev);
    }
    static int RenderCosine(Image& image, float x_period, float y_period)
    {
      return imProcessRenderCosine(image.im_image, x_period, y_period);
    }
    static int RenderGrid(Image& image, int x_space, int y_space)
    {
      return imProcessRenderGrid(image.im_image, x_space, y_space);
    }
    static int RenderChessboard(Image& image, int x_space, int y_space)
    {
      return imProcessRenderChessboard(image.im_image, x_space, y_space);
    }
    static int RenderFloodFill(Image& image, int start_x, int start_y, float* replace_color, float tolerance)
    {
      imProcessRenderFloodFill(image.im_image, start_x, start_y, replace_color, tolerance);
    }
  };

  class Histogram
  {
    friend class Calc;

    /* forbidden */
    Histogram() { }

    unsigned long* histo;
    int count;
  public:

    Histogram(int image_data_type)
    {
      count = imHistogramCount(image_data_type);
      histo = new unsigned long[count];
    }
    ~Histogram()
    {
      delete[] histo;
    }

    Histogram(const Histogram& histogram)
    {
      count = histogram.count;
      histo = new unsigned long[count];
      for (int i = 0; i < count; i++) histo[i] = histogram.histo[i];
    }

    unsigned long operator [](int index) { return histo[index]; }
  };


  class Calc
  {
  public:

    static float RMSError(const Image& image1, const Image& image2)
    {
      return imCalcRMSError(image1.im_image, image2.im_image);
    }
    static float SNR(const Image& src_image, const Image& noise_image)
    {
      return imCalcSNR(src_image.im_image, noise_image.im_image);
    }
    static unsigned long CountColors(const Image& image)
    {
      return imCalcCountColors(image.im_image);
    }
    static void GrayHistogram(const Image& image, Histogram& histogram, int cumulative)
    {
      imCalcGrayHistogram(image.im_image, histogram.histo, cumulative);
    }
    static void Histogram(const Image& image, Histogram& histogram, int plane, int cumulative)
    {
      imCalcHistogram(image.im_image, histogram.histo, plane, cumulative);
    }
    static void ImageStatistics(const Image& image, imStats& stats)
    {
      imCalcImageStatistics(image.im_image, &stats);
    }
    static void HistogramStatistics(const Image& image, imStats& stats)
    {
      imCalcHistogramStatistics(image.im_image, &stats);
    }
    static void HistoImageStatistics(const Image& image, int* median, int* mode)
    {
      imCalcHistoImageStatistics(image.im_image, median, mode);
    }
    static void PercentMinMax(const Image& image, float percent, int ignore_zero, int &min, int &max)
    {
      imCalcPercentMinMax(image.im_image, percent, ignore_zero, &min, &max);
    }
  };

  class Analyze
    {
    public:

    static int FindRegions(const Image& src_image, Image& dst_image, int connect, int touch_border)
    {
      return imAnalyzeFindRegions(src_image.im_image, dst_image.im_image, connect, touch_border);
    }

    static void MeasureArea(const Image& image, int* area, int region_count)
    {
      imAnalyzeMeasureArea(image.im_image, area, region_count);
    }
    static void MeasurePerimArea(const Image& image, float* perimarea)
    {
      imAnalyzeMeasurePerimArea(image.im_image, perimarea);
    }
    static void MeasureCentroid(const Image& image, const int* area, int region_count, float* cx, float* cy)
    {
      imAnalyzeMeasureCentroid(image.im_image, area, region_count, cx, cy);
    }
    static void MeasurePrincipalAxis(const Image& image, const int* area, const float* cx, const float* cy, const int region_count, float* major_slope, float* major_length, float* minor_slope, float* minor_length)
    {
      imAnalyzeMeasurePrincipalAxis(image.im_image, area, cx, cy, region_count, major_slope, major_length, minor_slope, minor_length);
    }
    static void MeasureHoles(const Image& image, int connect, int* holes_count, int* area, float* perim)
    {
      imAnalyzeMeasureHoles(image.im_image, connect, holes_count, area, perim);
    }
    static void MeasurePerimeter(const Image& image, float* perim, int region_count)
    {
      imAnalyzeMeasurePerimeter(image.im_image, perim, region_count);
    }

  };

}

#endif
