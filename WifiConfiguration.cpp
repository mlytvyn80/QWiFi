/*------------------------------------------------------------------------------
 * WiFiConfiguration
 *------------------------------------------------------------------------------
 * File:     WiFiConfiguration.cpp
 * Authors:  Mykhailo Lytvyn <mikhailo.lytvyn@gmail.com>
 * Purpose:
 *
 *------------------------------------------------------------------------------
 * Versions / History / Changes
 *      23.09.2021: Initial release
 *
 *----------------------------------------------------------------------------*/
#include "WifiConfiguration.h"

WifiConfiguration::WifiConfiguration(QObject *parent) : QObject(parent)
{

}

WifiConfiguration::~WifiConfiguration()
{

}

bool WifiConfiguration::isSsidHidden() const
{
  return m_ssid_hidden;
}

QString WifiConfiguration::passphrase() const
{
  return m_passphrase;
}

QString WifiConfiguration::protocol() const
{
  return m_protocol;
}

void WifiConfiguration::setPassphrase(const QString &passphrase)
{
  m_passphrase = passphrase;
}

void WifiConfiguration::setProtocol(const QString &protocol)
{
  m_protocol = protocol;
}

void WifiConfiguration::setSsid(const QString &ssid)
{
  m_ssid = ssid;
}

void WifiConfiguration::setSsidHidden(bool hidden)
{
  m_ssid_hidden = hidden;
}

QString WifiConfiguration::ssid() const
{
  return m_ssid;
}




