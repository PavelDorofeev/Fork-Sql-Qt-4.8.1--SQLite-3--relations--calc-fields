TEMPLATE = subdirs

CONFIG += ordered

message($$PWD/core)

win32:SRC_SUBDIRS += core
qp_core.subdir = $$PWD/core
qp_core.target = sub_qp_core

win32:SRC_SUBDIRS += qp_gui
qp_gui.subdir = $$PWD/gui
qp_gui.target = sub_qp_gui
qp_gui.depends += qp_core

win32:SRC_SUBDIRS += qp_ntw
qp_ntw.subdir = $$PWD/ntw
qp_ntw.target = sub_qp_ntw
qp_ntw.depends += qp_core qp_gui

win32:SRC_SUBDIRS += qp_sql
qp_sql.subdir = $$PWD/sql
qp_sql.target = sub_qp_sql
qp_sql.depends += qp_core qp_gui qp_ntw

message ($$SRC_SUBDIRS)

SUBDIRS += $$SRC_SUBDIRS
