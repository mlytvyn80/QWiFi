// -------------------------------------------------------------------------
/// @file wlaninterfaceinfo.h
/// @author Mykhailo Lytvyn (mykhailo.lytvyn@avl.com)
/// @date 11.01.2022
/// @brief
// -------------------------------------------------------------------------
#ifndef WLANINTERFACEINFO_H
#define WLANINTERFACEINFO_H

#include <string>
#include <QList>

#include <windows.h>
#include <wlanapi.h>
#include <guiddef.h>


enum WlanInterfaceState
{
  NotReady           = 0, //!< Not ready
  Connected          = 1, //!< Connected
  AdHocNetworkFormed = 2, //!< First node in a ad hoc network
  Disconnecting      = 3, //!< Disconnecting
  Disconnected       = 4, //!< Not connected
  Associating        = 5, //!< Attempting to associate with a network
  Discovering        = 6, //!< Auto configuration is discovering settings for the network
  Authenticating     = 7  //!< In process of authenticating
};

struct WlanInterfaceInfo
{
  WlanInterfaceInfo() {}
  WlanInterfaceInfo(int idx, PWLAN_INTERFACE_INFO info);

  QString description;
  WlanInterfaceState state;
  GUID guid;
  int index;
};

QList<WlanInterfaceInfo> availableWlanInterfaces(std::string &error);
bool hasWlanInterface();
QString toString(WlanInterfaceState state);

void scan(std::string &error, const WlanInterfaceInfo &interface_info);



#endif // WLANINTERFACEINFO_H
