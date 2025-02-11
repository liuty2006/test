QT += core
QT -= gui

CONFIG += c++11

TARGET = tinyxml_test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += \
    ../libs/tinyxml/ \

SOURCES += main.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += $$PWD/../libs/tinyxml/tinyxml.lib

win32:{
    contains(DEFINES, WIN64):{
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../Bin/Release/X64
            LIBS += $$PWD/../Bin/Release/X64/tinyxml.lib
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../Bin/Debug/X64
            LIBS += $$PWD/../Bin/Debug/X64/tinyxml.lib
        }
    }
    else:{
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../Bin/Release/X86
            LIBS += $$PWD/../Bin/Release/X86/tinyxml.lib
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../Bin/Debug/X86
            LIBS += $$PWD/../Bin/Debug/X86/tinyxml.lib
        }
    }
}

