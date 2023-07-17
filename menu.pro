QT       += core gui network multimedia

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

SOURCES += \
    chatsimple.cpp \
    detainfo.cpp \
    getLifeInfo.cpp \
    http.cpp \
    iamgeprocess.cpp \
    imagetest.cpp \
    lifemanager.cpp \
    lifewidget.cpp \
    lyrics.cpp \
    main.cpp \
    mainwindow.cpp \
    musicplayer.cpp \
    my_lineedit.cpp \
    mynetmanager.cpp \
    mywifi.cpp \
    objectdetect.cpp \
    set_wifi.cpp \
    speech.cpp \
    systeminfo.cpp \
    syszuxpinyin.cpp \
    v4l2api.cpp \
    wechat.cpp \
    worker.cpp

HEADERS += \
    chatsimple.h \
    detainfo.h \
    http.h \
    iamgeprocess.h \
    imagetest.h \
    lifemanager.h \
    lifewidget.h \
    lyrics.h \
    mainwindow.h \
    musicplayer.h \
    my_lineedit.h \
    mynetmanager.h \
    mywifi.h \
    objectdetect.h \
    set_wifi.h \
    speech.h \
    systeminfo.h \
    syszuxpinyin.h \
    v4l2api.h \
    wechat.h \
    worker.h

FORMS += \
    chatsimple.ui \
    detainfo.ui \
    imagetest.ui \
    lifemanager.ui \
    lifewidget.ui \
    mainwindow.ui \
    musicplayer.ui \
    mywifi.ui \
    objectdetect.ui \
    set_wifi.ui \
    speech.ui \
    systeminfo.ui \
    syszuxpinyin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc \
    qtr.qrc

DISTFILES +=
