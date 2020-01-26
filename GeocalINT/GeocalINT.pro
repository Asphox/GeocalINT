QT       += core gui serialport location qml positioning quickwidgets quickcontrols2

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# CTO : COMPILE TIME OPTIONS
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += CTO_ENABLE_FILTER_SERIAL_PORT_NAME
DEFINES += CTO_ENABLE_SERIAL_RAW_DISPLAY

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += *.cpp \
    GNSS/NMEA/nmeaframe.cpp \
    GNSS/UBX/ACK/ubxframeack.cpp \
    GNSS/UBX/CFG/ubxframecfg_tp5.cpp \
    GNSS/UBX/NAV/ubxframenav.cpp \
    GNSS/UBX/NAV/ubxframenav_odo.cpp \
    GNSS/UBX/NAV/ubxframenav_timegps.cpp \
    GNSS/UBX/ubxframe.cpp \
    GNSS/gnss.cpp \
    GNSS/gnssparser.cpp \
    GNSS/satmanager.cpp \
    Utils/bytearraymanipulator.cpp \
    Utils/stringhtml.cpp

HEADERS += *.h \
    GNSS/NMEA/nmeaframe.h \
    GNSS/UBX/ACK/ubxframeack.h \
    GNSS/UBX/AID/ubxframeaid_eph.h \
    GNSS/UBX/AID/ubxframeaid_eph_defines.h \
    GNSS/UBX/CFG/ubxframecfg_tp5.h \
    GNSS/UBX/Ephemeris.h \
    GNSS/UBX/NAV/ubxframenav_odo.h \
    GNSS/UBX/NAV/ubxframenav_timegps.h \
    GNSS/UBX/RXM/ubxframerxm_sfrbx.h \
    GNSS/UBX/ubx.h \
    GNSS/UBX/ubxframe.h \
    GNSS/gnss.h \
    GNSS/gnssparser.h \
    GNSS/satmanager.h \
    Utils/bytearraymanipulator.h \
    Utils/mathphy.h \
    Utils/stringhtml.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    Resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
