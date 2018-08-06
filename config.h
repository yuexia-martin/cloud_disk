#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

class Config {

public:
    QByteArray token;
    QString url;

public:
    void clear();

};

#endif // CONFIG_H
