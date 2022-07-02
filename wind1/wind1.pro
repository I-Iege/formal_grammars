#-------------------------------------------------
#
# Project created by QtCreator 2013-12-06T17:02:28
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wind1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    new_grammar.cpp \
    grammar.cpp \
    sign.cpp \
    s_rule.cpp \
    early_alg.cpp \
    greibach.cpp \
    sign_list.cpp \
    grammar_alg.cpp \
    gr_to_pd.cpp \
    pd_to_gr.cpp

HEADERS  += mainwindow.h \
    new_grammar.h \
    grammar.h \
    sign.h \
    s_rule.h \
    early_alg.h \
    greibach.h \
    sign_list.h \
    move.h \
    result.h \
    grammar_alg.h \
    pd_to_gr.h \
    gr_to_pd.h \
    push_down.h

FORMS    += mainwindow.ui \
    new_grammar.ui

OTHER_FILES += \
    t2.txt
