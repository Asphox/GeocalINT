#include "stringhtml.h"

QString HTMLFormat(const QString& baseString, QString color)
{
    QString tmp = "<font color=\""+color+"\">"+baseString+"</font>";
    return tmp;
}
