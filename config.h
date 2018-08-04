#ifndef CONFIG_H
#define CONFIG_H

#include <QMainWindow>
#include <QDebug>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QMessageBox>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonArray>
#include <QJsonParseError>
#include <QObject>
#include <QFileDialog>
#include <QCryptographicHash>
#include <QFile>



class Config{

public:

    QString host;

    QString ip;

    QString port;

    QString token;

};


#endif // CONFIG_H
