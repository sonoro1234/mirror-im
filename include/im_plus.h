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

namespace cd
{
  class Canvas;
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

  enum DataType
  {
    BYTE = IM_BYTE,
    SHORT = IM_SHORT,
    USHORT = IM_USHORT,
    INT = IM_INT,
    FLOAT = IM_FLOAT,
    DOUBLE = IM_DOUBLE,
    CFLOAT = IM_CFLOAT,
    CDOUBLE = IM_CDOUBLE
  };
  enum ColorSpace
  {
    RGB = IM_RGB,
    MAP = IM_MAP,
    GRAY = IM_GRAY,
    BINARY = IM_BINARY,
    CMYK = IM_CMYK,
    YCBCR = IM_YCBCR,
    LAB = IM_LAB,
    LUV = IM_LUV,
    XYZ = IM_XYZ
  };
  enum ColorModeConfig
  {
    ALPHA = IM_ALPHA,
    PACKED = IM_PACKED,
    TOPDOWN = IM_TOPDOWN
  };
  enum ErrorCodes
  {
    ERR_NONE = IM_ERR_NONE,
    ERR_OPEN = IM_ERR_OPEN,
    ERR_ACCESS = IM_ERR_ACCESS,
    ERR_FORMAT = IM_ERR_FORMAT,
    ERR_DATA = IM_ERR_DATA,
    ERR_COMPRESS = IM_ERR_COMPRESS,
    ERR_MEM = IM_ERR_MEM,
    ERR_COUNTER = IM_ERR_COUNTER
  };


  class Image
  {
    friend class File;
    friend class Process;
    friend class VideoCapture;
    friend class cd::Canvas;

  protected:
    imImage* im_image;

    Image() { im_image = 0; };

  public:
    Image(int width, int height, int color_space, int data_type)
    {
      im_image = imImageCreate(width, height, color_space, data_type);
    }
//    Image(const Image& src_image, int width = -1, int height = -1, int color_space = -1, int data_type = -1)
//    {
//      im_image = imImageCreateBased(src_image.im_image, width, height, color_space, data_type);
//    }
    Image(const char* file_name, int index, int &error, bool as_bitmap)
    {
      if (as_bitmap)
        im_image = imFileImageLoad(file_name, index, &error);
      else
        im_image = imFileImageLoadBitmap(file_name, index, &error);
    }
    Image(const Image& ref_image)
    {
      im_image = ref_image.im_image;
    }
    Image(imImage* ref_image)
    {
      im_image = ref_image;
    }
    ~Image()
    {
      if (im_image)
        imImageDestroy(im_image);
    }


    bool Failed() const
    {
      return im_image == 0;
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


    /* utilities */
    void Clear()
    {
      imImageClear(im_image);
    }
    void Reshape(int width, int height)
    {
      imImageReshape(im_image, width, height);
    }
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
    int GetAttribInteger(const char* attrib, int index) const
    {
      return imImageGetAttribInteger(im_image, attrib, index);
    }
    double GetAttribReal(const char* attrib, int index) const
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
      imCounterSetCallback(this, c_callback);  //imCounterCallback
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
}

#endif
