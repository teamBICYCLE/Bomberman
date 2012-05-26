#ifndef     __TWITTERCONNECTION_HH__
# define    __TWITTERCONNECTION_HH__
# include <string>
# include <kqoauth/QtKOAuth>
# include <QObject>
# include <QSettings>
# include <iostream>
# include <QApplication>
# include <QString>

# define TWITTER_DATA_FILE "Ressources/.twitter_data"

class TwitterConnection : public QObject
{

    Q_OBJECT

public:
    static TwitterConnection *getInstance(int ac, char **av);
    static TwitterConnection *getInstance(void);
    static void deleteInstance(void);

private:
    TwitterConnection(int ac, char **av);
    ~TwitterConnection(void);

public:
    void requestAccess(void);
    void sendTweet(int);

private:
    void privateSendTweet(int);

private:
    const QString cKey_;
    const QString cSecretKey_;
    QCoreApplication app_;
    KQOAuthRequest *oauthRequest_;
    KQOAuthManager *oauthManager_;
    QSettings config_;
    bool userHasRefuse_;
    bool allowSendTweet_;
    static TwitterConnection *instance_;

private slots:
    void tmpToken();
    void success();
    void accessToken(QString, QString);
    void onAuthorizedRequestDone();
    void ready(QByteArray);
};

#endif // __TWITTERCONNECTION_HH__
