QT       += core gui
QT       += xml
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filewriter.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    networkaccess.cpp \
    reader.cpp \
    selector.cpp \
    word.cpp

HEADERS += \
    filewriter.h \
    mainwindow.h \
    model.h \
    networkaccess.h \
    reader.h \
    selector.h \
    word.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
