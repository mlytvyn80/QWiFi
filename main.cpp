// -------------------------------------------------------------------------
/// @file main.cpp
/// @author Mykhailo Lytvyn (mykhailo.lytvyn@avl.com)
/// @date 11.01.2022
/// @brief
// -------------------------------------------------------------------------

#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>

#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <iostream>

#include "WlanInterfaceInfo.h"

void scan();

int main(int argc, char** argv)
{
  std::string error;
  QList<WlanInterfaceInfo> list = availableWlanInterfaces(error);

  foreach(WlanInterfaceInfo item, list)
  {
    std::cout << item.index << "\t" << item.description.toStdString()
              << "\t" << toString(item.state).toStdString() << std::endl;
  }

  return 0;
}
