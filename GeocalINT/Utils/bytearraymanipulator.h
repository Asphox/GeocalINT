#ifndef BYTEARRAYMANIPULATOR_H
#define BYTEARRAYMANIPULATOR_H

#include <iostream>
#include <QByteArray>

void displayQByteArray(const QByteArray&, std::ios_base&(*base)(std::ios_base&) = std::dec, char separator = ' ');

#endif // BYTEARRAYMANIPULATOR_H
