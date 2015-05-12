/** \file
 * \brief Name space for C++ high level API
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_PLUS_H
#define __IM_PLUS_H

#include "im.h"
#include "im_raw.h"
#include "im_image.h"
#include "im_capture.h"


/** \brief Name space for C++ high level API
 *
 * \par
 * Defines wrapper classes for all C structures.
 *
 * See \ref im_plus.h
 */
namespace im 
{
  class Image
  {
    friend class File;
    friend class Processing;
    friend class VideoCapture;

  protected:
    imImage* image;

    Image() {};

  public:
    Image(int width, int height, int color_space, int data_type)
    {
      image = imImageCreate(width, height, color_space, data_type);
    }

    Image(const Image& src_image, int width = -1, int height = -1, int color_space = -1, int data_type = -1)
    {
      image = imImageCreateBased(src_image.image, width, height, color_space, data_type);
    }

    Image(const char* file_name, int index, int &error, bool as_bitmap)
    {
      if (as_bitmap)
        image = imFileImageLoad(file_name, index, &error);
      else
        image = imFileImageLoadBitmap(file_name, index, &error);
    }

    Image(imImage* ref_image)
    {
      image = ref_image;
    }

    int Save(const char* file_name, const char* format)
    {
      return imFileImageSave(file_name, format, image);
    }

    Image& operator = (const Image& src_image)
    {
      if (image) imImageDestroy(image);
      image = imImageDuplicate(src_image.image);
      return *this;
    }

    virtual ~Image()
    {
      if (image) imImageDestroy(image);
    }

    bool Failed() const
    {
      return image == 0;
    }

    int Width() const { return image->width; }
    int Height() const { return image->height; }
    int ColorSpace() const { return image->color_space; }
    int DataType() const { return image->data_type; }
    bool HasAlpha() const { return image->has_alpha != 0; }
    int Depth() const { return image->depth; }

    void Copy(Image& dst_image) const
    {
      imImageCopy(image, dst_image.image);
    }
    void CopyAttributes(Image& dst_image) const
    {
      imImageCopyAttributes(image, dst_image.image);
    }
    void MergeAttributes(Image& dst_image) const
    {
      imImageMergeAttributes(image, dst_image.image);
    }
    void CopyData(Image& dst_image) const
    {
      imImageCopyData(image, dst_image.image);
    }
    void CopyPlane(Image& dst_image, int src_plane, int dst_plane) const
    {
      imImageCopyPlane(image, src_plane, dst_image.image, dst_plane);
    }

    bool IsBitmap() const
    {
      return imImageIsBitmap(image) == 1;
    }

    void Clear()
    {
      imImageClear(image);
    }

    void Reshape(int width, int height)
    {
      imImageReshape(image, width, height);
    }

    void AddAlpha()
    {
      imImageAddAlpha(image);
    }
    void SetAlpha(float alpha)
    {
      imImageSetAlpha(image, alpha);
    }
    void RemoveAlpha()
    {
      imImageRemoveAlpha(image);
    }

    void MakeBinary()
    {
      imImageMakeBinary(image);
    }
    void MakeGray()
    {
      imImageMakeGray(image);
    }
    void SetBinary()
    {
      imImageSetBinary(image);
    }
    void SetGray()
    {
      imImageSetGray(image);
    }
    void SetMap()
    {
      imImageSetMap(image);
    }

    void SetPalette(long* palette, int palette_count)
    {
      imImageSetPalette(image, palette, palette_count);
    }

    void SetAttribute(const char* attrib, int data_type, int count, const void* data)
    {
      imImageSetAttribute(image, attrib, data_type, count, data);
    }
    void SetAttribInteger(const char* attrib, int data_type, int value)
    {
      imImageSetAttribInteger(image, attrib, data_type, value);
    }
    void SetAttribReal(const char* attrib, int data_type, double value)
    {
      imImageSetAttribReal(image, attrib, data_type, value);
    }
    void SetAttribString(const char* attrib, const char* value)
    {
      imImageSetAttribString(image, attrib, value);
    }

    const void* GetAttribute(const char* attrib, int *data_type = 0, int *count = 0) const
    {
      return imImageGetAttribute(image, attrib, data_type, count);
    }
    int GetAttribInteger(const char* attrib, int index) const
    {
      return imImageGetAttribInteger(image, attrib, index);
    }
    double GetAttribReal(const char* attrib, int index) const
    {
      return imImageGetAttribReal(image, attrib, index);
    }
    const char* GetAttribString(const char* attrib) const
    {
      return imImageGetAttribString(image, attrib);
    }

    void GetAttributeList(char** attrib, int &attrib_count) const
    {
      imImageGetAttributeList(image, attrib, &attrib_count);
    }

    bool operator==(const Image& image2) const
    {
      return Match(image2);
    }
    bool Match(const Image& image2) const
    {
      return imImageMatch(image, image2.image) == 1;
    }
    bool MatchColor(const Image& image2) const
    {
      return imImageMatchColor(image, image2.image) == 1;
    }
    bool MatchColorSpace(const Image& image2) const
    {
      return imImageMatchColorSpace(image, image2.image) == 1;
    }
    bool MatchDataType(const Image& image2) const
    {
      return imImageMatchDataType(image, image2.image) == 1;
    }
    bool MatchSize(const Image& image2) const
    {
      return imImageMatchSize(image, image2.image) == 1;
    }
  };

  /********************************************************************/

  class File
  {
  protected:
    imFile* ifile;

    File() {};

  public:

    File(const char* file_name, int &error)
    {
      ifile = imFileOpen(file_name, &error);
    }

    File(const char* file_name, const char* format, int &error)
    {
      ifile = imFileNew(file_name, format, &error);
    }

    File(imFile* ref_ifile)
    {
      ifile = ref_ifile;
    }

    virtual ~File()
    {
      if (ifile) imFileClose(ifile);
    }

    bool Failed() const
    {
      return ifile == 0;
    }

    void SetAttribute(const char* attrib, int data_type, int count, const void* data)
    {
      imFileSetAttribute(ifile, attrib, data_type, count, data);
    }

    void SetAttribInteger(const char* attrib, int data_type, int value)
    {
      imFileSetAttribInteger(ifile, attrib, data_type, value);
    }

    void SetAttribReal(const char* attrib, int data_type, double value)
    {
      imFileSetAttribReal(ifile, attrib, data_type, value);
    }

    void SetAttribString(const char* attrib, const char* value)
    {
      imFileSetAttribString(ifile, attrib, value);
    }

    const void* GetAttribute(const char* attrib, int &data_type, int &count) const
    {
      return imFileGetAttribute(ifile, attrib, &data_type, &count);
    }

    int GetAttribInteger(const char* attrib, int index) const
    {
      return imFileGetAttribInteger(ifile, attrib, index);
    }

    double GetAttribReal(const char* attrib, int index) const
    {
      return imFileGetAttribReal(ifile, attrib, index);
    }

    const char* GetAttribString(const char* attrib)
    {
      return imFileGetAttribString(ifile, attrib);
    }

    void GetInfo(char* format, char* compression, int &image_count)
    {
      imFileGetInfo(ifile, format, compression, &image_count);
    }

    int ReadImageInfo(int index, int &width, int &height, int &color_mode, int &data_type)
    {
      return imFileReadImageInfo(ifile, index, &width, &height, &color_mode, &data_type);
    }

    void GetPalette(long* palette, int &palette_count)
    {
      imFileGetPalette(ifile, palette, &palette_count);
    }

    int ReadImageData(void* data, int convert2bitmap, int color_mode_flags)
    {
      return imFileReadImageData(ifile, data, convert2bitmap, color_mode_flags);
    }

    void SetInfo(const char* compression)
    {
      imFileSetInfo(ifile, compression);
    }

    void SetPalette(long* palette, int palette_count)
    {
      imFileSetPalette(ifile, palette, palette_count);
    }

    int WriteImageInfo(int width, int height, int color_mode, int data_type)
    {
      return imFileWriteImageInfo(ifile, width, height, color_mode, data_type);
    }

    int WriteImageData(void* data)
    {
      return imFileWriteImageData(ifile, data);
    }

    Image* LoadImage(int index, int &error)
    {
      imImage* image = imFileLoadImage(ifile, index, &error);
      return new Image(image);
    }
    int SaveImage(const Image& image)
    {
      return imFileSaveImage(ifile, image.image);
    }

    void LoadFrame(int index, Image& image, int &error, bool as_bitmap)
    {
      if (as_bitmap)
        imFileLoadBitmapFrame(ifile, index, image.image, &error);
      else
        imFileLoadImageFrame(ifile, index, image.image, &error);
    }
  };

  /********************************************************************/

  class FileRaw : public File
  {
    FileRaw() {};

  public:

    FileRaw(const char* file_name, int &error, bool new_file) : File()
    {
      if (new_file) 
        ifile = imFileNewRaw(file_name, &error);
      else 
        ifile = imFileOpenRaw(file_name, &error);
    }
  };

  /********************************************************************/

  class VideoCaptureDeviceList
  {
  public:
    VideoCaptureDeviceList()
    {
      imVideoCaptureReloadDevices();
    }

    ~VideoCaptureDeviceList()
    {
      imVideoCaptureReleaseDevices();
    }

    int Count() const
    {
      return imVideoCaptureDeviceCount();
    }

    const char* DeviceDescription(int device) const
    {
      return imVideoCaptureDeviceDesc(device);
    }

    const char* DeviceExtendedDescription(int device) const
    {
      return imVideoCaptureDeviceExDesc(device);
    }

    const char* DevicePath(int device) const
    {
      return imVideoCaptureDevicePath(device);
    }

    const char* DeviceVendorInfo(int device) const
    {
      return imVideoCaptureDeviceVendorInfo(device);
    }
  };

  /********************************************************************/

  class VideoCapture
  {
  protected:
    imVideoCapture* vc;

  public:
    VideoCapture()
    {
      vc = imVideoCaptureCreate();
    }

    VideoCapture(imVideoCapture* ref_vc)
    {
      vc = ref_vc;
    }

    ~VideoCapture()
    {
      if (vc) imVideoCaptureDestroy(vc);
    }

    bool Failed() const
    {
      return vc == 0;
    }

    int Connect(int device)
    {
      return imVideoCaptureConnect(vc, device);
    }

    void Disconnect()
    {
      imVideoCaptureDisconnect(vc);
    }

    int DialogCount() const
    {
      return imVideoCaptureDialogCount(vc);
    }

    bool ShowDialog(int dialog, void* parent)
    {
      return imVideoCaptureShowDialog(vc, dialog, parent) != 0;
    }

    const char* DialogDescription(int dialog) const
    {
      return imVideoCaptureDialogDesc(vc, dialog);
    }

    bool SetInOut(int input, int output, int cross)
    {
      return imVideoCaptureSetInOut(vc, input, output, cross) != 0;
    }

    int FormatCount() const
    {
      return imVideoCaptureFormatCount(vc);
    }

    bool GetFormatInfo(int format, int &width, int &height, char* desc) const
    {
      return imVideoCaptureGetFormat(vc, format, &width, &height, desc) != 0;
    }

    int GetFormat() const
    {
      return imVideoCaptureSetFormat(vc, -1);
    }

    bool SetFormat(int format)
    {
      return imVideoCaptureSetFormat(vc, format) != 0;
    }

    void GetImageSize(int &width, int &height) const
    {
      imVideoCaptureGetImageSize(vc, &width, &height);
    }

    bool SetImageSize(int width, int height)
    {
      return imVideoCaptureSetImageSize(vc, width, height) != 0;
    }

    bool CaptureFrame(unsigned char* data, int color_mode, int timeout = -1)
    {
      return imVideoCaptureFrame(vc, data, color_mode, timeout) != 0;
    }

    bool CaptureOneFrame(unsigned char* data, int color_mode)
    {
      return imVideoCaptureOneFrame(vc, data, color_mode) != 0;
    }

    bool CaptureFrame(Image& dst_image, int timeout = -1)
    {
      if (dst_image.image->color_space != IM_GRAY && 
          dst_image.image->color_space != IM_RGB &&
          dst_image.image->data_type != IM_BYTE)
        return false;

      return CaptureFrame((unsigned char*)dst_image.image->data[0], dst_image.image->color_space, timeout);
    }

    bool CaptureOneFrame(Image& dst_image)
    {
      if (dst_image.image->color_space != IM_GRAY &&
          dst_image.image->color_space != IM_RGB &&
          dst_image.image->data_type != IM_BYTE)
        return false;

      return CaptureOneFrame((unsigned char*)dst_image.image->data[0], dst_image.image->color_space);
    }

    bool GetLive() const
    {
      return imVideoCaptureLive(vc, -1) == 1;
    }

    bool SetLive(int live)
    {
      return imVideoCaptureLive(vc, live) != 0;
    }

    bool ResetAttribute(const char* attrib, int fauto)
    {
      return imVideoCaptureResetAttribute(vc, attrib, fauto) != 0;
    }

    bool GetAttribute(const char* attrib, float &percent) const
    {
      return imVideoCaptureGetAttribute(vc, attrib, &percent) != 0;
    }

    bool SetAttribute(const char* attrib, float percent)
    {
      return imVideoCaptureSetAttribute(vc, attrib, percent) != 0;
    }

    const char** GetAttributeList(int &num_attrib) const
    {
      return imVideoCaptureGetAttributeList(vc, &num_attrib);
    }
  };
}

#endif
