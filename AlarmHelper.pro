QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alramlisttype.cpp \
    load_config.cpp \
    loggerserver.cpp \
        main.cpp \
    snap7/snap7.cpp \
        snap7helper.cpp\


TRANSLATIONS += \
    AlarmHelper_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/snap7/ -lsnap7

INCLUDEPATH += $$PWD/snap7
DEPENDPATH += $$PWD/snap7

HEADERS += \
    alramlisttype.h \
    load_config.h \
    loggerserver.h \
    snap7/snap7.h \
    snap7helper.h
