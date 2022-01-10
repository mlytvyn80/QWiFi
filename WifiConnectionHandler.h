/*------------------------------------------------------------------------------
 * WifiConnectionHandler
 *------------------------------------------------------------------------------
 * File:     WifiConnectionHandler.h
 * Authors:  Mykhailo Lytvyn <mikhailo.lytvyn@gmail.com>
 * Purpose:
 *
 *------------------------------------------------------------------------------
 * Versions / History / Changes
 *      23.09.2021: Initial release
 *
 *----------------------------------------------------------------------------*/
#ifndef WIFICONNECTIONHANDLER_H
#define WIFICONNECTIONHANDLER_H

#include <QObject>

#include "WifiConfiguration.h"
#include "WifiManager.h"

class WifiConnectionHandler : public QObject
{
    Q_OBJECT
public:
    WifiConnectionHandler(QObject *parent=nullptr);
    virtual ~WifiConnectionHandler();

protected slots:
    void handleBackendStateChanged(WifiManager::BackendState state);
private:
    WifiManager *m_manager;
    WifiConfiguration m_config;
};

#endif // WIFICONNECTIONHANDLER_H
