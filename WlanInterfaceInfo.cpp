// -------------------------------------------------------------------------
/// @file wlaninterfaceinfo.cpp
/// @author Mykhailo Lytvyn (mikhailo.lytvyn@gmail.com)
/// @date 11.01.2022
/// @brief
// -------------------------------------------------------------------------
#include "WlanInterfaceInfo.h"


#include <objbase.h>
#include <wtypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stringapiset.h>

#include "utils.h"


QString wideCharToString(WCHAR* array, int length)
{
  char ch[length];
  char def_char = ' ';
  WideCharToMultiByte(CP_ACP, 0, array, -1, ch, 256, &def_char, NULL);
  return std::string(ch).c_str();
}

void freeWlanMemory(PWLAN_INTERFACE_INFO_LIST p)
{
  if(p)
  {
    WlanFreeMemory(p);
    p = NULL;
  }
}

WlanInterfaceInfo::WlanInterfaceInfo(int idx, PWLAN_INTERFACE_INFO info) :
  index(idx)
{
  if(info)
  {
    state = static_cast<WlanInterfaceState>(info->isState);
    description = ::wideCharToString(info->strInterfaceDescription, 256);
  }
}

QList<WlanInterfaceInfo> availableWlanInterfaces(std::string &error)
{
  QList<WlanInterfaceInfo> result;

  HANDLE client = NULL;
  DWORD max_client = 2;
  DWORD current_version = 0;

  DWORD ret_code = WlanOpenHandle(max_client, NULL, &current_version, &client);
  if(ret_code != ERROR_SUCCESS)
  {
    error = "WlanOpenHandle failed with error: " + lastErrorAsString(ret_code);
    return result;
  }

  PWLAN_INTERFACE_INFO_LIST if_list = NULL;
  ret_code = WlanEnumInterfaces(client, NULL, &if_list);
  if(ret_code != ERROR_SUCCESS)
  {
    error = "WlanEnumInterfaces failed with error: " + lastErrorAsString(ret_code);
    freeWlanMemory(if_list);
    return result;
  }

  for(int i = 0; i < static_cast<int>(if_list->dwNumberOfItems); i++)
  {
    PWLAN_INTERFACE_INFO interface_info = (WLAN_INTERFACE_INFO *) &if_list->InterfaceInfo[i];
    result.append(WlanInterfaceInfo(i, interface_info));
  }

  freeWlanMemory(if_list);

  return result;
}

bool hasWlanInterface()
{
  std::string last_error;
  return !availableWlanInterfaces(last_error).isEmpty();
}

QString toString(WlanInterfaceState state)
{
  QString result;

  switch(state)
  {
    case NotReady: result = "Not ready"; break;
    case Connected: result = "Connected"; break;
    case AdHocNetworkFormed: result = "Ad hoc network formed"; break;
    case Disconnecting: result = "Disconnecting"; break;
    case Disconnected: result = "Disconnected"; break;
    case Associating: result = "Associating"; break;
    case Discovering: result = "Discovering"; break;
    case Authenticating: result = "Authenticating"; break;
  }

  return result;
}

void scan(std::string &error, WlanInterfaceInfo &interface_info)
{
  HANDLE hClient = NULL;
  DWORD dwMaxClient = 2;
  DWORD dwCurVersion = 0;

  DWORD dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
  if(dwResult != ERROR_SUCCESS)
  {
    error = "WlanOpenHandle failed with error: " + lastErrorAsString(dwResult);
    return;
  }

  dwResult = WlanScan(hClient, &interface_info.guid, NULL, NULL, NULL);
  if(dwResult != ERROR_SUCCESS)
  {
    error = lastErrorAsString(dwResult);
    return;
  }

}

