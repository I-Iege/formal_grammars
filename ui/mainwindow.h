#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QScrollArea>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QScrollBar>
#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QTableWidget>
#include <QMessageBox>

#include "grammar.h"
#include "greibach.h"
#include "early_alg.h"
#include "pd_to_gr.h"
#include "gr_to_pd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void init_view();
    void on_pushButton_clicked();

    void on_actionExit_triggered();
    void on_actionNew_grammar_triggered();
    void on_actionLoad_triggered();
    void on_actionSave_grammar_triggered();

    void open_file_selected( const QString & file );
    void save_file_selected( const QString & file );


    void on_early_text_textChanged();
    void on_early_button_clicked();

    void set_greibach_label_style();
    void refresh_greibach_labels();

    void refresh_early_labels();
    void refresh_early_matrix();

    void refresh_pd_labels();

    void grammar_created(grammar *);

    void on__tab_currentChanged(int index);

//algorithm iterator button eventhandlers
    void on_greibach_next_button_clicked();
    void on_greibach_back_button_clicked();

    void on_early_back_button_clicked();
    void on_early_next_button_clicked();

    void on_push_down_back_button_clicked();
    void on_push_down_next_button_clicked();

    void on_back_pd_grammar_button_clicked();
    void on_next_pd_grammar_button_clicked();

    void on_generate_pushdown_clicked();

    void on_generate_grammar_clicked();

private:
    int index;
    Ui::MainWindow *ui;
    grammar *g;
    grammar *selected_grammar;

    greibach *gn;
    gr_to_pd *pd_from_grammar;
    early_alg *early;
    pd_to_gr *gr_from_push_down;

    std::vector<std::vector<QTextEdit*> > e;
    QScrollArea *early_scroll;
    QFileDialog* qfd;
    QMessageBox *b;
};

