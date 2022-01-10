/*------------------------------------------------------------------------------
 * WifiConnectionHandler
 *------------------------------------------------------------------------------
 * File:     WifiConnectionHandler.cpp
 * Authors:  Mykhailo Lytvyn <mikhailo.lytvyn@gmail.com>
 * Purpose:
 *
 *------------------------------------------------------------------------------
 * Versions / History / Changes
 *      23.09.2021: Initial release
 *
 *----------------------------------------------------------------------------*/
#include "WifiConnectionHandler.h"
#include "WifiConfiguration.h"

WifiConnectionHandler::WifiConnectionHandler(QObject *parent) : QObject(parent)
{
    m_config.setSsid("bus-station-wifi");
    m_config.setPassphrase("mypassword");
    m_config.setProtocol("WPA2");

    m_manager = &WifiManager::instance();
    connect(m_manager, &WifiManager::backendStateChanged,
            this, &WifiConnectionHandler::handleBackendStateChanged);

    if (m_manager->backendState() == WifiManager::Running)
    {
        m_manager->connect(&m_config);
    }
    else
    {
        m_manager->start();
    }
}

WifiConnectionHandler::~WifiConnectionHandler()
{

}

void WifiConnectionHandler::handleBackendStateChanged(WifiManager::BackendState state)
{
    if (state == WifiManager::Running)
        m_manager->connect(&m_config);
}
