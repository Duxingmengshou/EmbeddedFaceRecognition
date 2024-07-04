QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttonctl.cpp \
    face_check.cpp \
    face_root.cpp \
    ledctl.cpp \
    cameractl.cpp \
    videodevice.cpp \
    udpcom.cpp \
    syn6288ctl.cpp \
    main.cpp

HEADERS += \
    buttonctl.h \
    face_check.h \
    face_root.h \
    cameractl.h \
    videodevice.h \
    udpcom.h \
    syn6288ctl.h \
    ledctl.h

FORMS += \
    face_check.ui \
    face_root.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
