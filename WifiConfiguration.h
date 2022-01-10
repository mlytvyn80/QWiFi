/*------------------------------------------------------------------------------
 * WiFiConfiguration
 *------------------------------------------------------------------------------
 * File:     WiFiConfiguration.h
 * Authors:  Mykhailo Lytvyn <mikhailo.lytvyn@gmail.com>
 * Purpose:
 *
 *------------------------------------------------------------------------------
 * Versions / History / Changes
 *      23.09.2021: Initial release
 *
 *----------------------------------------------------------------------------*/
#ifndef WIFICONFIGURATION_H
#define WIFICONFIGURATION_H

#include <QObject>

/**
 * @brief Used to define a network configuration.
 *
   QWifiConfiguration object represents a single network configuration.
   Use it to configure properties of your network. For example, passphrase,
   security protocol to use, and so on. WifiManager::connect() function
   uses this information to find a network that matches the provided
   configuration, before establishing a connection.
 */
class WifiConfiguration : public QObject
{
    Q_OBJECT
public:
    WifiConfiguration(QObject *parent=nullptr);
    virtual ~WifiConfiguration();

    bool	isSsidHidden() const;
    QString	passphrase() const;
    QString	protocol() const;
    void	setPassphrase(const QString &passphrase);
    void	setProtocol(const QString &protocol);
    void	setSsid(const QString &ssid);
    void	setSsidHidden(bool hidden);
    QString	ssid() const;
private:
    QString m_passphrase;
    QString m_protocol;
    QString m_ssid;
    bool m_ssid_hidden;
};

#endif // WIFICONFIGURATION_H
