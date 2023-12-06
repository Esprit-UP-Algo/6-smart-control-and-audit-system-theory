QT       += core gui sql
QT       += printsupport
QT       += sql

QT += charts

QT       += widgets
QT       += core gui sql network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += C:\curl\include
LIBS += -LC:\curl\lib -lcurl

SOURCES += \
    auditeur/arduino.cpp \
    auditeur/auditeur.cpp \
    auditeur/mainwindow.cpp \
    auditeur/sms.cpp \
    certificat/arduinocertif.cpp \
    certificat/certificat.cpp \
    certificat/mainwindowcertif.cpp \
    connexion.cpp \
    contract/contrat.cpp \
    contract/login.cpp \
    contract/mainwindowcontrat.cpp \
    formation/formation.cpp \
    formation/gesfor.cpp \
    formation/smtp.cpp \
    main.cpp \
    mission/mainwindowmission.cpp \
    mission/mission.cpp \
    widget.cpp

HEADERS += \
    auditeur/arduino.h \
    auditeur/auditeur.h \
    auditeur/mainwindow.h \
    auditeur/sms.h \
    certificat/arduinocertif.h \
    certificat/certificat.h \
    certificat/mainwindowcertif.h \
    connexion.h \
    contract/contrat.h \
    contract/login.h \
    contract/mainwindowcontrat.h \
    formation/formation.h \
    formation/gesfor.h \
    formation/smtp.h \
    mission/mainwindowmission.h \
    mission/mission.h \
    widget.h

FORMS += \
    auditeur/mainwindow.ui \
    certificat/mainwindowcertif.ui \
    contract/login.ui \
    contract/mainwindowcontrat.ui \
    formation/gesfor.ui \
    mission/mainwindowmission.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    formation/formationn.pro

DISTFILES += \
    formation/libeay32.dll \
    formation/ssleay32.dll \
    integration.pro.user

RESOURCES += \
    ress.qrc
