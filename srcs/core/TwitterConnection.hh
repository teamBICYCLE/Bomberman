#ifndef     __TWITTERCONNECTION_HH__
# define    __TWITTERCONNECTION_HH__
# include <string>
# include <kqoauth/QtKOAuth>
# include <QObject>
# include <QSettings>
# include <iostream>
# include <QApplication>
# include <QString>
# include <fstream>

# define TWITTER_DATA_FILE "Ressources/.twitter_data"
# define NO_CONNECTION 2
# define ALLOW_CONNECTION 1
# define DISALLOW_CONNECTION 0

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
    void saveChoice(bool c) const;
    uint getChoice(void) const;

private:
    const QString cKey_;
    const QString cSecretKey_;
    QCoreApplication app_;
    KQOAuthRequest *oauthRequest_;
    KQOAuthManager *oauthManager_;
    QSettings config_;
    bool allowSendTweet_;
    static TwitterConnection *instance_;

private slots:
    void tmpToken(void) const;
    void success(void);
    void accessToken(QString, QString);
    void onAuthorizedRequestDone(void);
    void ready(void);
};

#endif // __TWITTERCONNECTION_HH__
