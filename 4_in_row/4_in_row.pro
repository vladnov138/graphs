QT += quick
QT += concurrent

SOURCES += \
        src/alphabeta/alphabeta.cpp \
        src/boardcell/boardcell.cpp \
        src/gamecontroller/gamecontroller.cpp \
        src/gameenemy/gameenemy.cpp \
        main.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/alphabeta/alphabeta.h \
    src/boardcell/boardcell.h \
    src/gamecontroller/gamecontroller.h \
    src/gameenemy/gameenemy.h
