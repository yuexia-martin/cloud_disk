#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>


QByteArray getFileMd5(QString filePath);

#endif // TOOLS_H
