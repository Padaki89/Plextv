#ifndef OSXUTILS_H
#define OSXUTILS_H

#include <QString>
#include <QWindow>
#include <QRect>
#include <ApplicationServices/ApplicationServices.h>

namespace OSXUtils
{
  QString ComputerName();
  OSStatus SendAppleEventToSystemProcess(AEEventID eventToSendID);

  void SetPresentationOptions(unsigned long flags);
  unsigned long GetPresentationOptions();
  unsigned long GetPresentationOptionsForFullscreen(bool hideMenuAndDock);
  void SetCursorVisible(bool visible);
  bool isWindowFullScreen(QWindow *window);
  void SetWindowFullScreen(QWindow *window, bool fullScreen);
  void SetWindowFullScreenOnSpecificScreen(QWindow *qtWindow, QRect screenRect);
};

#endif /* OSXUTILS_H */
