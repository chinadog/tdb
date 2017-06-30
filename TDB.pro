#-------------------------------------------------
#
# Проект TDB создан 2017-01-29 01:31:29
#
#-------------------------------------------------

QT       -= gui
QT       += sql

PROJECT = TDB

CONFIG += create_prl
CONFIG += no_install_prl
CONFIG += create_pc
CONFIG += link_pkgconfig
CONFIG += c++11

TARGET = $$PROJECT
TEMPLATE = lib
VERSION  = 0.0.1

DEFINES += TDB_LIBRARY

SOURCES += \
    $$PWD/src/tdb.cpp \
    src/structs.cpp \
    src/sqlworker.cpp \
    src/resultasync.cpp

HEADERS += \
    $$PWD/src/tdb.h \
    $$PWD/src/tdb_global.h \
    $$PWD/src/TDB \
    src/structs.h \
    src/sqlworker.h \
    src/resultasync.h


DESTDIR = $$PWD/build/lib
MOC_DIR = $$PWD/build/moc
OBJECTS_DIR = $$PWD/build/obj

isEmpty(PREFIX) {
    PREFIX=$$PWD
}

PKG_CONFIG_LIBDIR  = $$PREFIX/share/pkgconfig
PKG_CONFIG_LIBDIR += $$system(pkg-config --variable pc_path pkg-config)

PKGCONFIG += TLogger

unix {
    target.path = $$PREFIX/lib

    # includes
    includes.path = $$PREFIX/include/$$PROJECT
    includes.files += $$PWD/src/tdb.h
    includes.files += $$PWD/src/tdb_global.h
    includes.files += $$PWD/src/TDB
    includes.files += $$PWD/src/structs.h
    includes.files += $$PWD/src/sqlworker.h
    includes.files += $$PWD/src/resultasync.h

    INSTALLS += target includes

    # pc-file params
    QMAKE_PKGCONFIG_NAME          = $$PROJECT
    QMAKE_PKGCONFIG_FILE          = $$PROJECT
    QMAKE_PKGCONFIG_DESCRIPTION   = The $$PROJECT library
    QMAKE_PKGCONFIG_LIBDIR        = $$target.path
    QMAKE_PKGCONFIG_INCDIR        = $$PREFIX/include
    QMAKE_PKGCONFIG_REQUIRES      =
    QMAKE_PKGCONFIG_DESTDIR       = ../share/pkgconfig #путь берётся относительно установки библиотеки
}
