#-------------------------------------------------
#
# Project created by QtCreator 2020-12-15T20:57:41
#
#-------------------------------------------------

QT       -= core gui

TARGET = tinyxml
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        tinyxml.cpp \
    tinystr.cpp \
    tinyxmlerror.cpp \
    tinyxmlparser.cpp

HEADERS += \
        tinyxml.h \
    tinystr.h


#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}

#win32:{
#    target.path = $$PWD/../bin
#    INSTALLS += target
#}

win32:{
    contains(DEFINES, WIN64):{
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../Bin/Release/X64
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../Bin/Debug/X64
        }
    }
    else:{
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../Bin/Release/X86
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../Bin/Debug/X86
        }
    }
}
