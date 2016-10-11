/* IM 3 sample that shows an image.

  Needs "im.lib", "iup.lib", "cd.lib" and "iupcd.lib".

  Usage: im_view <file_name>

    Example: im_view test.tif

    
  Click on image to open another file.
*/

#include <im_plus.h>
#include <cd_plus.h>
#include <iup_plus.h>

#include <im_format_jp2.h>
#include <im_format_avi.h>
#include <im_format_wmv.h>

#include <stdio.h>
#include <string.h>


static int disable_repaint = 0; /* used to optimize repaint, while opening a new file */

static void PrintError(int error)
{
  switch (error)
  {
  case IM_ERR_OPEN:
    Iup::Message("IM", "Error Opening File.");
    break;
  case IM_ERR_MEM:
    Iup::Message("IM", "Insufficient memory.");
    break;
  case IM_ERR_ACCESS:
    Iup::Message("IM", "Error Accessing File.");
    break;
  case IM_ERR_DATA:
    Iup::Message("IM", "Image type not Supported.");
    break;
  case IM_ERR_FORMAT:
    Iup::Message("IM", "Invalid Format.");
    break;
  case IM_ERR_COMPRESS:
    Iup::Message("IM", "Invalid or unsupported compression.");
    break;
  default:
    Iup::Message("IM", "Unknown Error.");
  }
}

static int cbCanvasRepaint(Ihandle* iup_canvas)
{
  cd::Canvas* cd_canvas = (cd::Canvas*)IupGetAttribute(iup_canvas, "cd::Canvas");
  im::Image* image = (im::Image*)IupGetAttribute(iup_canvas, "im::Image");

  if (!cd_canvas || disable_repaint)
    return IUP_DEFAULT;

  cd_canvas->Activate();
  cd_canvas->Clear();

  if (!image)
    return IUP_DEFAULT;

  cd_canvas->PutImage(*image, 0, 0, image->Width(), image->Height());
  
  cd_canvas->Flush();
  
  return IUP_DEFAULT;
}

static void ShowImage(char* file_name, Ihandle* iup_dialog)
{
  int error = 0;
  im::Image* image = (im::Image*)IupGetAttribute(iup_dialog, "im::Image");
  if (image) delete image;
  IupSetAttribute(iup_dialog, "im::Image", NULL);

  image = new im::Image(file_name, 0, error, true);
  if (error) PrintError(error);
  if (!image) return;

  IupSetAttribute(iup_dialog, "im::Image", (char*)image);
  IupStoreAttribute(iup_dialog, "TITLE", file_name);

  cbCanvasRepaint(iup_dialog); /* we can do this because canvas inherit attributes from the dialog */
}

static int cbCanvasButton(Ihandle* iup_canvas, int but, int pressed)
{
  char file_name[200] = "*.*";

  if (but != IUP_BUTTON1 || !pressed)
    return IUP_DEFAULT;
  
  disable_repaint = 1;
  if (Iup::GetFile(file_name) != 0)
  {
    disable_repaint = 0;
    return IUP_DEFAULT;
  }

  disable_repaint = 0;
  ShowImage(file_name, IupGetDialog(iup_canvas));
  
  return IUP_DEFAULT;
}

static int cbCanvasMap(Ihandle* iup_canvas)
{
  cd::Canvas* cd_canvas = new cd::CanvasIup(iup_canvas);
  IupSetAttribute(IupGetDialog(iup_canvas), "cd::Canvas", (char*)cd_canvas);
  return IUP_DEFAULT;
}

static int cbDialogClose(Ihandle* iup_dialog)
{
  cd::Canvas* cd_canvas = (cd::Canvas*)IupGetAttribute(iup_dialog, "cd::Canvas");
  im::Image* image = (im::Image*)IupGetAttribute(iup_dialog, "im::Image");

  if (cd_canvas) delete cd_canvas;
  if (image) delete image;

  IupSetAttribute(iup_dialog, "cd::Canvas", NULL);
  IupSetAttribute(iup_dialog, "im::Image", NULL);

  return IUP_CLOSE;
}

static Ihandle* CreateDialog(void)
{
  Ihandle *iup_dialog, *iup_canvas;

  iup_canvas = IupCanvas(NULL);
  IupSetCallback(iup_canvas, "BUTTON_CB", (Icallback)cbCanvasButton);
  IupSetCallback(iup_canvas, "ACTION", (Icallback)cbCanvasRepaint);
  IupSetCallback(iup_canvas, "MAP_CB", (Icallback)cbCanvasMap);
  
  iup_dialog = IupDialog(iup_canvas);
  IupSetCallback(iup_dialog, "CLOSE_CB", (Icallback)cbDialogClose);
  IupSetAttribute(iup_dialog, "SIZE", "HALFxHALF");  /* initial size */

  return iup_dialog;
}

int main(int argc, char* argv[])
{
  Iup::Dialog dlg;

  //  imFormatRegisterJP2();
  //  imFormatRegisterAVI();
  //  imFormatRegisterWMV();   

  Iup::Open(argc, argv);

  dlg = CreateDialog();

  dlg.Show();
  
  /* Try to get a file name from the command line. */
  if (argc > 1)
    ShowImage(argv[1], dlg);
  else   
  {
    char file_name[1024] = "*.*";
    if (IupGetFile(file_name) == 0)
      ShowImage(file_name, dlg);
  }
                                   
  Iup::MainLoop();
  IupDestroy(dlg);
  Iup::Close();

  return 0;
}
