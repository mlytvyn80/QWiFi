/*------------------------------------------------------------------------------
 * %{Cpp:License:ClassName}
 *------------------------------------------------------------------------------
 * File:     %{Cpp:License:FileName}
 * Authors:  Mykhailo Lytvyn <mikhailo.lytvyn@gmail.com>
 * Purpose:
 *
 *------------------------------------------------------------------------------
 * Versions / History / Changes
 *      23.09.2021: Initial release
 *
 *----------------------------------------------------------------------------*/
#include "WifiManager.h"

#include <QAbstractListModel>

WifiManager::WifiManager()
{
}

WifiManager::~WifiManager()
{
}

WifiManager &WifiManager::instance()
{
    static WifiManager instance;
    return instance;
}

WifiManager::BackendState WifiManager::backendState() const
{
    return m_backend_state;
}

QString WifiManager::currentSSID() const
{
    return m_current_ssid;
}

QString WifiManager::lastError() const
{
    return m_last_error;
}

bool WifiManager::isScanning() const
{
    return m_scanning;
}

void WifiManager::setScanning(bool scanning)
{
    if(scanning != m_scanning)
    {
        m_scanning = scanning;
        emit scanningChanged();
    }
}

QAbstractListModel *WifiManager::networks() const
{
    return m_networks;
}

bool WifiManager::connect(WifiConfiguration *config)
{
    Q_UNUSED(config);
    return false;
}

void WifiManager::disconnect()
{

}

void WifiManager::start()
{

}

void WifiManager::stop()
{

}


