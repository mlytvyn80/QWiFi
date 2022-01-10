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
#ifndef QTWIFI_H
#define QTWIFI_H

#include <QObject>
#include <QString>

class WifiConfiguration;

class QAbstractListModel;

class WifiManager : public QObject
{
    Q_OBJECT

    /**
     * @brief This property holds the current backend state.

       Returns the current backend state.
     * @accessors backendState(), setBackend()
     * @notifier_signal backendStateChanged(BackendState backendState)
     */
    Q_PROPERTY(BackendState backendState MEMBER m_backend_state READ backendState NOTIFY backendStateChanged)
    Q_PROPERTY(QString currentSSID MEMBER m_current_ssid READ currentSSID NOTIFY currentSSIDChanged)
    Q_PROPERTY(QString lastError MEMBER m_last_error READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(bool scanning MEMBER m_scanning READ scanning NOTIFY scanningChanged)
public:

    /// Describes current state of the Wifi backend.
    enum BackendState
    {
        Initializing, //!< Wireless supplicant is starting up
        Running,      //!< Supplicant is initialized and ready to process commands
        Terminating,  //!< Shutting down wireless supplicant
        NotRunning    //!< Wireless supplicant process is not running
    };

    /// Describes current state of the network connection.
    enum NetworkState
    {
        Disconnected,       //!< Not connected to any network
        Authenticating,     //!< Verifying password with the network provider
        HandshakeFailed,    //!< Incorrect password provided
        ObtainingIPAddress, //!< Requesting IP address from DHCP server
        DhcpRequestFailed,  //!< Could not retrieve IP address
        Connected           //!< Ready to process network requests
    };
    enum Roles
    {
      SSID = Qt::UserRole + 1, //!< informal (human) name of a Wifi network (QString)
      BSSID = Qt::UserRole + 2,
      SignalStrength = Qt::UserRole + 3,
      WPASupported = Qt::UserRole + 4,
      WPA2Supported = Qt::UserRole + 5,
      WEPSupported = Qt::UserRole + 6,
      WPSSupported = Qt::UserRole + 7,
    };

    WifiManager();
    virtual ~WifiManager();

    static WifiManager& instance();

    WifiManager(WifiManager const&) = delete;
    void operator=(WifiManager const&)  = delete;


    /**
     * @brief backendState
     * @return
     */
    BackendState backendState() const;
    QString currentSSID() const;
    QString lastError() const;
signals:
    void backendStateChanged(WifiManager::BackendState state);
    void currentSSIDChanged(QString SSID);
    void lastErrorChanged(QString lastError);

public slots:
    bool connect(WifiConfiguration *config);
    void disconnect();
    void start();
    void stop();

private:
    BackendState m_backend_state;
    QString m_current_ssid;
    QString m_last_error;
    NetworkState m_network_state;
    QAbstractListModel* m_networks;
    bool m_scanning;
};

#endif // QTWIFI_H
