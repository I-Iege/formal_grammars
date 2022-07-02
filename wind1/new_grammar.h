#ifndef NEW_GRAMMAR_H
#define NEW_GRAMMAR_H

#include <QDialog>
#include <QTextEdit>
#include <QScrollArea>
#include <QScrollBar>
#include <QWidget>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <QMessageBox>

#include "grammar.h"
#include <vector>
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class new_grammar; }
QT_END_NAMESPACE

class new_grammar : public QDialog
{
    Q_OBJECT
    
public:
    explicit new_grammar(QWidget *parent = 0);
    ~new_grammar();
    
private slots:
    void on_cancel_button_clicked();

    void on_next_button_clicked();

    void on_non_terminal_t_textChanged();

    void on_finish_button_clicked();

    void on_back_button_clicked();

signals:
    void gr_finished(grammar *);
private:
    Ui::new_grammar *ui;
    QScrollArea *scroll;
    QMessageBox *message;
    std::vector<QTextEdit*> t_rules;
    std::vector<QLabel*> labvec;
    //grammar
    sign_list t;
    sign_list n;
    std::map<sign,std::list<sign_list> > p;
    sign s;

};

#endif // NEW_GRAMMAR_H
