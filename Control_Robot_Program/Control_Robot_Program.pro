QT += quick xml

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        appcore.cpp \
        filesandfolders.cpp \
        kinematics.cpp \
        main.cpp \
        robotcontrol.cpp \
        rt_ethercat.cpp \
    programcodexml.cpp

RESOURCES += qml.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =


LIBS += -lalchemy -lcopperplate /usr/xenomai/lib/xenomai/bootstrap-pic.o -Wl,--wrap=main -Wl,--dynamic-list=/usr/xenomai/lib/dynlist.ld -L/usr/xenomai/lib -lcobalt -lpthread -lrt  -L/usr/local/lib -lethercat
INCLUDEPATH += /usr/xenomai/include/cobalt /usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -D__COBALT__ -D__COBALT_WRAP__ /usr/xenomai/include/alchemy

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    appcore.h \
    filesandfolders.h \
    kinematics.h \
    robotcontrol.h \
    rt_ethercat.h \
    programcodexml.h
