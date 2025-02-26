QT       += core gui
QT += openglwidgets

include(QtGifImage/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += OpenGL/

SOURCES += \
    Model/parser.cc \
    Controller/controller.cc \
    main.cc \
    View/mainwindow.cc \
    Settings/settings.cc \
    OpenGL/wopengl.cc

HEADERS += \
    Model/parser.h \
    Controller/controller.h \
    View/mainwindow.h \
    Settings/settings.h \
    OpenGL/wopengl.h

FORMS += \
    View/mainwindow.ui

win32:LIBS += -lglu32 -lopengl32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Resources/fshader.fsh \
    Resources/vshader.vsh \
    Settings/logs.txt

RESOURCES += \
#    Texture.qrc \
    Resources/shaders.qrc \
