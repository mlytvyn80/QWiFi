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
    Q_PROPERTY(bool scanning MEMBER m_scanning READ isScanning WRITE setScanning NOTIFY scanningChanged)
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

    /// Data roles supported by the data model returned from WifiManager::networks()
    enum Roles
    {
      SSID = Qt::UserRole + 1,           //!< informal (human) name of a Wifi network (QString)
      BSSID = Qt::UserRole + 2,          //!< basic service set identification of a network, used to uniquely identify BSS (QString)
      SignalStrength = Qt::UserRole + 3, //!< strength of a Wifi signal represented as percentage (0-100) (int)
      WPASupported = Qt::UserRole + 4,   //!< holds whether network access point supports WPA security protocol (bool)
      WPA2Supported = Qt::UserRole + 5,  //!< holds whether network access point supports WPA2 security protocol (bool)
      WEPSupported = Qt::UserRole + 6,   //!< holds whether network access point supports WEP security protocol (bool)
      WPSSupported = Qt::UserRole + 7,   //!< holds whether network access point supports WPS security protocol (bool)
    };

    WifiManager();
    virtual ~WifiManager();

    static WifiManager& instance();

    WifiManager(WifiManager const&) = delete;
    void operator=(WifiManager const&)  = delete;


    /// Returns BackendState last set by WiFiManager.
    BackendState backendState() const;

    /// Returns a network name of the last selected network.
    QString currentSSID() const;

    /// Returns a QString containing the last error message set by QWifiManager.
    QString lastError() const;

    /// Returns true if WiFiManager performs network scanning in background.
    bool isScanning() const;

    /// Enables/disables discovering of wireless networks in background.
    void setScanning(bool scanning);

    /// Returns discoverd nertworks as ListModel can be used in View widgets.
    QAbstractListModel *networks() const;

signals:
    void backendStateChanged(WifiManager::BackendState state);
    void currentSSIDChanged(QString SSID);
    void lastErrorChanged(QString lastError);
    void scanningChanged();

public slots:
    /// Connect a device to a network using the config network configuration.
    /// This method returns true if the network with the provided configuration
    /// could be successfully added by the backend or false on failure.
    /// @note Use lastError() to obtain the error message on failure.
    bool connect(WifiConfiguration *config);

    /// Disconnect from currently connected network connection.
    void disconnect();

    /// Start the Wifi backend. This function returns immediately,
    /// the BackendState change events are delivered asynchronously.
    void start();

    /// Stop the Wifi backend. Closes the open network connection if any.
    /// This function returns immediately, and the BackendState change events
    /// are delivered asynchronously.
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
