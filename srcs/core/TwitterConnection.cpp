#include "TwitterConnection.hh"

TwitterConnection *TwitterConnection::instance_ = NULL;

TwitterConnection::TwitterConnection(int ac, char **av)
    : cKey_("L5hDurEYHdr83rSbZnqvA"),
      cSecretKey_("IGkpocv2BJv2ArR5e3uRsojTrOmtwKjfFrts0MupI"),
      app_(ac, av)
{
    oauthRequest_ = new KQOAuthRequest;
    oauthManager_ = new KQOAuthManager(this);
    userHasRefuse_ = false;
    allowSendTweet_ = false;
    //oauthRequest_->setEnableDebugOutput(true);
}

TwitterConnection::~TwitterConnection(void)
{
    delete oauthRequest_;
    delete oauthManager_;
}

TwitterConnection *TwitterConnection::getInstance(int ac, char **av)
{
    if (!instance_)
        instance_ = new TwitterConnection(ac, av);
    return instance_;
}

TwitterConnection *TwitterConnection::getInstance(void)
{
    return instance_;
}

void TwitterConnection::deleteInstance(void)
{
    delete instance_;
    instance_ = NULL;
}

void TwitterConnection::requestAccess(void)
{
//    if (config_.value("oauth_token").toString().isEmpty() ||
//            config_.value("oauth_token_secret").toString().isEmpty())
//    {
        connect(oauthManager_, SIGNAL(temporaryTokenReceived(QString,QString)),
                this, SLOT(tmpToken()));
        connect(oauthManager_, SIGNAL(authorizationReceived(QString,QString)),
                this, SLOT(success()));
        connect(oauthManager_, SIGNAL(accessTokenReceived(QString,QString)),
                this, SLOT(accessToken(QString,QString)));
        connect(oauthManager_, SIGNAL(requestReady(QByteArray)),
                this, SLOT(ready(QByteArray)));

        oauthRequest_->initRequest(KQOAuthRequest::TemporaryCredentials, QUrl("https://api.twitter.com/oauth/request_token"));
        oauthRequest_->setConsumerKey(cKey_);
        oauthRequest_->setConsumerSecretKey(cSecretKey_);
        oauthManager_->setHandleUserAuthorization(true);
        oauthManager_->executeRequest(oauthRequest_);
        app_.exec();
//    }
}

void TwitterConnection::sendTweet(int score)
{
    if (!userHasRefuse_ &&
            !config_.value("oauth_token").toString().isEmpty() &&
            !config_.value("oauth_token_secret").toString().isEmpty())
    {
        TwitterConnection::privateSendTweet(score);
        app_.exec();
    }
}

void TwitterConnection::privateSendTweet(int score)
{
    if(!config_.value("oauth_token").toString().isEmpty() &&
            !config_.value("oauth_token_secret").toString().isEmpty())
    {

        std::cout << config_.value("oauth_token").toString().toStdString() << std::endl;
        QString status("I just beat my personal best score on #Bomberman. (New Score : ");
        status.append(QString::number(score));
        status.append(")");

        KQOAuthParameters tweet;

        connect(oauthManager_, SIGNAL(requestReady(QByteArray)),
                    this, SLOT(ready(QByteArray)));
        connect(oauthManager_, SIGNAL(authorizedRequestDone()),
             this, SLOT(onAuthorizedRequestDone()));

        oauthRequest_->clearRequest();
        oauthRequest_->initRequest(KQOAuthRequest::AuthorizedRequest, QUrl("http://api.twitter.com/1/statuses/update.xml"));
        oauthRequest_->setConsumerKey(cKey_);
        oauthRequest_->setConsumerSecretKey(cSecretKey_);
        oauthRequest_->setToken(config_.value("oauth_token").toString());
        oauthRequest_->setTokenSecret(config_.value("oauth_token_secret").toString());

        tweet.insert("status", status);
        oauthRequest_->setAdditionalParameters(tweet);
        oauthManager_->executeRequest(oauthRequest_);
    }
}

/* SLOTS */

void TwitterConnection::tmpToken()
{
    QUrl url("https://api.twitter.com/oauth/authorize");

    oauthManager_->getUserAuthorization(url);
}

void TwitterConnection::success()
{
    oauthManager_->getUserAccessTokens(QUrl("https://api.twitter.com/oauth/access_token"));

    if (oauthManager_->lastError() != KQOAuthManager::NoError)
    {
        userHasRefuse_ = true;
        config_.setValue("oauth_token", "");
        config_.setValue("oauth_token_secret", "");
        QCoreApplication::exit();
    }
}

void TwitterConnection::accessToken(QString token, QString tokenSecret)
{
    if (!userHasRefuse_)
    {
        config_.setValue("oauth_token", token);
        config_.setValue("oauth_token_secret", tokenSecret);
        QCoreApplication::exit();
        allowSendTweet_ = true;
    }
}

void TwitterConnection::ready(QByteArray response)
{
    if (allowSendTweet_)
        app_.exit();
}

void TwitterConnection::onAuthorizedRequestDone()
{
    QCoreApplication::exit();
}


