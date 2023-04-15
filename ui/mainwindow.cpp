#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_grammar.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //   ui->_tab->
    this->setFixedSize(this->size());

    ui->pd_text->setReadOnly(true);
    ui->pd_grammar->setReadOnly(true);
    ui->pd_gr_info->setReadOnly(true);
    ui->greibach_t_edit->setReadOnly(true);

    ui->greibach_t_edit->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    ui->greibach_t_edit->setLineWrapMode(QTextEdit::NoWrap);
    ui->greibach_t_edit->setStyleSheet("QTextEdit {color: black; font: 12px}");
    ui->pd_text->setLineWrapMode(QTextEdit::NoWrap);
    ui->early_info_text->setLineWrapMode(QTextEdit::NoWrap);
    ui->early_info_text->setReadOnly(true);
    ui->pd_info->setLineWrapMode(QTextEdit::NoWrap);
    ui->pd_info->setReadOnly(true);
    ui->pd_grammar->setLineWrapMode(QTextEdit::NoWrap);
    set_greibach_label_style();
    index = 0; // selected tab
    b = 0;     // messagebox for warnings
    g = 0;
    selected_grammar = 0;
    // grammar algs
    early_scroll = 0;
    gn = 0;
    early = 0;
    pd_from_grammar = 0;
    gr_from_push_down = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    if (g != 0)
    {
        delete g;
    }
    if (gn != 0)
    {
        delete gn;
    }
    if (early != 0)
    {
        delete early;
        for (int i = 0; i < (int)e.size(); ++i)
        {
            for (int j = 0; j < (int)e.size(); ++j)
            {
                delete e[i][j];
            }
        }
    }
    if (pd_from_grammar != 0)
    {
        delete pd_from_grammar;
    }
    if (gr_from_push_down != 0)
    {
        delete gr_from_push_down;
    }
    if (g != selected_grammar && selected_grammar != 0)
    {
        delete selected_grammar;
    }
}

void MainWindow::init_view()
{
    selected_grammar = g;
    ui->greibach_t_edit->setText(g->to_string().c_str());
    // delete data from pervious grammars
    if (gn != 0)
    {
        delete gn;
        ui->gn_count->setText("");
        ui->greibach_info_label->setText("");
        gn = 0;
    }
    if (pd_from_grammar != 0)
    {
        delete pd_from_grammar;
        ui->pd_info->setText("");
        ui->pd_text->setText("");
        ui->pd_progress_lab->setText("");
        ui->generate_grammar->setEnabled(false);
        pd_from_grammar = 0;
    }
    if (early != 0)
    {
        delete early;
        for (int i = 0; i < (int)e.size(); ++i)
        {
            for (int j = 0; j < (int)e.size(); ++j)
            {
                delete e[i][j];
            }
        }
        e.clear();
        ui->early_progress_lab->setText("");
        ui->early_info_text->setText("");
        ui->early_text->setText("");
        early = 0;
    }
    if (gr_from_push_down != 0)
    {
        delete gr_from_push_down;
        gr_from_push_down = 0;
        ui->pd_grammar_progress_lab->setText("");
        ui->pd_gr_info->setText("");
        ui->pd_grammar->setText("");
    }
    ui->pushButton->setEnabled(true);
    ui->generate_pushdown->setEnabled(true);
    ui->greibach_back_button->setEnabled(false);
    ui->greibach_next_button->setEnabled(false);
    ui->push_down_back_button->setEnabled(false);
    ui->push_down_next_button->setEnabled(false);
    ui->next_pd_grammar_button->setEnabled(false);
    ui->back_pd_grammar_button->setEnabled(false);
    ui->early_back_button->setEnabled(false);
    ui->early_next_button->setEnabled(false);
    ui->early_button->setEnabled(ui->early_text->toPlainText().length() != 0);
}
void MainWindow::on_pushButton_clicked()
{
    gn = new greibach(*g);
    ui->gn_count->setText(gn->progress().c_str());
    ui->greibach_next_button->setEnabled(true);
    ui->greibach_back_button->setEnabled(true);
    refresh_greibach_labels();
}

void MainWindow::on_actionExit_triggered()
{
    if (g != 0)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QString::fromUtf8("Figyelmeztetés"),
                                      QString::fromUtf8("Az el nem mentett nyelvtan el fog veszni,biztosan kilép?"),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            qApp->quit();
        }
    }
    else
    {
        qApp->quit();
    }
}

void MainWindow::on_actionNew_grammar_triggered()
{
    new_grammar* k = new new_grammar(this);
    connect(k, SIGNAL(gr_finished(grammar*)), this, SLOT(grammar_created(grammar*)));
    k->show();
    k->exec();
}

void MainWindow::on_actionLoad_triggered()
{
    qfd = new QFileDialog(this);
    QObject::connect(qfd, SIGNAL(fileSelected(QString)), this, SLOT(open_file_selected(QString)));
    qfd->show();
}

void MainWindow::on_actionSave_grammar_triggered()
{
    if (selected_grammar != 0)
    {
        qfd = new QFileDialog(this);
        QObject::connect(qfd, SIGNAL(fileSelected(QString)), this, SLOT(save_file_selected(QString)));
        qfd->setAcceptMode(QFileDialog::AcceptSave);
        qfd->show();
    }
    else
    {
        if (b != 0)
        {
            delete b;
        }
        b = new QMessageBox;
        b->setText(QString::fromUtf8("nincs nyelvtan betöltve!"));
        b->show();
    }
}

void MainWindow::open_file_selected(const QString& file)
{
    QString s = file;
    QFile qf(s);
    if (qf.size() == 0)
    {
        if (b != 0)
        {
            delete b;
        }
        b = new QMessageBox;
        b->setText(QString::fromUtf8("Üres fájl!"));
        b->show();
    }
    else
    {
        g = new grammar(s.toStdString().c_str());
        init_view();
    }
}

void MainWindow::save_file_selected(const QString& file)
{
    if (selected_grammar != 0)
    {
        selected_grammar->to_file(file.toStdString());
    }
}
void MainWindow::grammar_created(grammar* gr)
{
    if (g != 0)
    {
        delete g;
    }
    g = gr;

    init_view();
}

void MainWindow::set_greibach_label_style()
{
    ui->left_rec_lab->setStyleSheet("QLabel {color: black; font: 14px}");
    ui->sort_lab->setStyleSheet("QLabel {color: black; font: 14px}");
    ui->substitute_lab->setStyleSheet("QLabel {color: black; font: 14px}");
    ui->n_lab->setStyleSheet("QLabel {color: black; font: 14px}");
    ui->reduction_lab->setStyleSheet("QLabel {color: black; font: 14px}");
    ui->end_lab->setStyleSheet("QLabel {color: black; font: 14px}");
}

void MainWindow::refresh_greibach_labels()
{
    ui->greibach_t_edit->setText(gn->to_string().c_str());
    ui->gn_count->setText(gn->progress().c_str());
    QString info_str = gn->show_info().c_str();
    switch (gn->show_state())
    {
    case greibach::LEFT_REC: // leftrecusrsion
    {
        set_greibach_label_style();
        ui->left_rec_lab->setStyleSheet("QLabel {color: red; font: 14px}");
        QStringList info_list = info_str.split("#");
        info_str = info_list[0] + QString::fromUtf8(" szabály(ok) kicserélése\n");
        info_str += info_list[2] + QString::fromUtf8(" szabály(ok)-ra\n");
        info_str += info_list[1] + QString::fromUtf8(" szabály(ok) bevezetése\n");
    }
    break;
    case greibach::SORT: // sort non-terminals
    {
        set_greibach_label_style();
        ui->sort_lab->setStyleSheet("QLabel {color: red; font: 14px}");
        QStringList info_list = info_str.split("#");
        info_str = QString::fromUtf8("levezetési sorrend: ") + gn->sequence().c_str() + "\n";
        info_str += "mivel " + info_list[1] + QString::fromUtf8(" behelyettesítjük ") + info_list[2]
                    + QString::fromUtf8(" szabályait\n");
        info_str += info_list[0] + QString::fromUtf8(" helyére");
    }
    break;
    case greibach::SUBSTITUTE: // substitute
    {
        set_greibach_label_style();
        ui->substitute_lab->setStyleSheet("QLabel {color: red; font: 14px}");
        info_str += QString::fromUtf8(" szabályainak behelyettesítése");
    }
    break;
    case greibach::REDUCTION: // reduction
    {
        set_greibach_label_style();
        ui->reduction_lab->setStyleSheet("QLabel {color: red; font: 14px}");
        info_str += QString::fromUtf8(" elhagyása");
    }
    break;
    case greibach::END: // end
    {
        set_greibach_label_style();
        ui->end_lab->setStyleSheet("QLabel {color: red; font: 14px}");
        info_str = QString::fromUtf8("kész");
        //   ui->left_rec_lab->setStyleSheet("QLabel {color: red; font: 14px}");
    }
    break;
    case greibach::NON_TERMINAL: // eliminate terminals
    {
        set_greibach_label_style();
        ui->n_lab->setStyleSheet("QLabel {color: red; font: 14px}");
        info_str += QString::fromUtf8(" bevezetése");
    }
    break;
    }
    ui->greibach_info_label->setText(info_str);
}

void MainWindow::refresh_early_labels()
{
    QString info_str = early->show_info().c_str();
    switch (early->show_state())
    {
    case early_alg::STEP1:
    {
        std::vector<QStringList> info_matrix;
        QStringList info_list = info_str.split("\n");
        for (QStringList::Iterator it = info_list.begin(); it != info_list.end(); ++it)
        {
            if ((*it) != "")
                info_matrix.push_back(it->split("#"));
        }
        QString str = "";
        for (int i = 0; i < (int)info_matrix.size(); ++i)
        {
            if (info_matrix[i].size() == 2)
            {
                str += "mivel " + info_matrix[i][0];
                str += QString::fromUtf8(" szabály benne van a nyelvtanban, ezért legyen ");
                str += info_matrix[i][1] + QString::fromUtf8(" eleme e[0][0]-nak \n");
            }
            else
            {
                str += "mivel " + info_matrix[i][0];
                str += QString::fromUtf8(" szabály benne van a nyelvtanban, és");
                str += info_matrix[i][2];
                str += QString::fromUtf8(" nem-terminálisokból levezethető epszilon,ezért legyen ");
                str += info_matrix[i][1] + QString::fromUtf8(" eleme e[0][0]-nak \n");
            }
        }

        ui->early_info_text->setText(str);
    }
    break;
    case early_alg::STEP2:
    {
        std::vector<QStringList> info_matrix;
        QStringList info_list = info_str.split("\n");
        for (QStringList::Iterator it = info_list.begin(); it != info_list.end(); ++it)
        {
            if ((*it) != "")
                info_matrix.push_back(it->split("#"));
        }
        QString str = "";
        for (int i = 0; i < (int)info_matrix.size(); ++i)
        {
            if (info_matrix[i].size() == 5)
            {
                str += "mivel " + info_matrix[i][2];
                str += QString::fromUtf8(" eleme ");
                str += "e[" + info_matrix[i][3] + "][" + info_matrix[i][4] + "]";
                str += QString::fromUtf8(" és ") + info_matrix[i][0];
                str += QString::fromUtf8(" szabály benne van a nyelvtanban, ezért legyen ");
                str += info_matrix[i][1] + " eleme e[" + info_matrix[i][4] + "][" + info_matrix[i][4] + "]-nak \n";
                ui->early_info_text->setText(str);
            }
            else if (info_matrix[i].size() == 6)
            {
                str += "mivel " + info_matrix[i][2];
                str += QString::fromUtf8(" eleme ");
                str += "e[" + info_matrix[i][3] + "][" + info_matrix[i][4] + "]";
                str += QString::fromUtf8(" és ") + info_matrix[i][0];
                str += QString::fromUtf8(" szabály benne van a nyelvtanban");
                str += QString::fromUtf8(" és ") + info_matrix[i][5]
                       + QString::fromUtf8(" nem-terminálisokból levezethető epszilon, ezért legyen ");
                str += info_matrix[i][1] + " eleme e[" + info_matrix[i][4] + "][" + info_matrix[i][4] + "]-nak \n";
                ui->early_info_text->setText(str);
            }
        }
    }
    break;
    case early_alg::STEP4:
    {
        std::vector<QStringList> info_matrix;
        QStringList info_list = info_str.split("\n");
        for (QStringList::Iterator it = info_list.begin(); it != info_list.end(); ++it)
        {
            if ((*it) != "")
                info_matrix.push_back(it->split("#"));
        }
        QString str = "";
        for (int i = 0; i < (int)info_matrix.size(); ++i)
        {
            if (info_matrix[i].size() == 4)
            {
                // j-1
                QString str_tmp = QString::number(info_matrix[i][3].toInt() - 1);

                str += "mivel " + info_matrix[i][0];
                str += QString::fromUtf8(" eleme ");
                str += "e[" + info_matrix[i][2] + "][" + str_tmp + "]";
                str += QString::fromUtf8(" ezért legyen ");
                str += info_matrix[i][1] + " eleme e[" + info_matrix[i][2] + "][" + info_matrix[i][3] + "]-nak \n";
                ui->early_info_text->setText(str);
            }
            else if (info_matrix[i].size() == 5)
            {
                // j-1
                QString str_tmp = QString::number(((info_matrix[i][3].toInt()) - 1));
                str += "mivel " + info_matrix[i][0];
                str += QString::fromUtf8(" eleme ");
                str += "e[" + info_matrix[i][2] + "][" + str_tmp + "]";
                str += QString::fromUtf8(" és ") + info_matrix[i][4]
                       + QString::fromUtf8(" nem-terminálisokból levezethető epszilon, legyen");
                str += info_matrix[i][1] + " eleme e[" + info_matrix[i][2] + "][" + info_matrix[i][3] + "]-nak \n";
                ui->early_info_text->setText(str);
            }
        }
    }
    break;
    case early_alg::STEP5:
    {
        std::vector<QStringList> info_matrix;
        QStringList info_list = info_str.split("\n");
        for (QStringList::Iterator it = info_list.begin(); it != info_list.end(); ++it)
        {
            if ((*it) != "")
                info_matrix.push_back(it->split("#"));
        }
        QString str = "";
        for (int i = 0; i < (int)info_matrix.size(); ++i)
        {
            if (info_matrix[i].size() == 6)
            {
                str += "mivel " + info_matrix[i][0];
                str += QString::fromUtf8(" eleme ");
                str += "e[" + info_matrix[i][3] + "][" + info_matrix[i][5] + "]";
                str += QString::fromUtf8(" és ");
                str += info_matrix[i][2] + QString::fromUtf8(" eleme ");
                str += "e[" + info_matrix[i][5] + "][" + info_matrix[i][4] + "]";
                str += QString::fromUtf8(" ezért legyen ");
                str += info_matrix[i][1] + " eleme e[" + info_matrix[i][3] + "][" + info_matrix[i][4] + "]-nak \n";
                ui->early_info_text->setText(str);
            }
            else if (info_matrix[i].size() == 7)
            {
                str += "mivel " + info_matrix[i][0];
                str += QString::fromUtf8(" eleme ");
                str += "e[" + info_matrix[i][3] + "][" + info_matrix[i][5] + "]";
                str += QString::fromUtf8(" és ");
                str += info_matrix[i][2] + QString::fromUtf8(" eleme ");
                str += "e[" + info_matrix[i][5] + "][" + info_matrix[i][4] + "]";
                str += QString::fromUtf8(" és ") + info_matrix[i][6]
                       + QString::fromUtf8(" nem-terminálisokból levezethető epszilon, legyen");
                str += info_matrix[i][1] + " eleme e[" + info_matrix[i][3] + "][" + info_matrix[i][4] + "]-nak \n";
                ui->early_info_text->setText(str);
            }
        }
    }
    break;
    case early_alg::END:
    {
        if (early->contains)
        {
            ui->early_info_text->setText(QString::fromUtf8("A nyelvtan tartalmazza a szót."));
        }
        else
        {
            ui->early_info_text->setText(QString::fromUtf8("A nyelvtan nem tartalmazza a szót."));
        }
    }
    break;
    }
    //  ui->early_info_text->setText(early->show_info().c_str());
    ui->early_progress_lab->setText(early->progress().c_str());
}

void MainWindow::refresh_early_matrix()
{
    for (int i = 0; i < (int)e.size(); ++i)
    {
        for (int j = 0; j < (int)e.size(); ++j)
        {
            if (i <= j)
            {
                e[i][j]->setText(early->get(i, j).c_str());
            }
        }
    }
}

void MainWindow::refresh_pd_labels()
{
    ui->pd_info->setText(pd_from_grammar->show_info().c_str());
    ui->pd_text->setText(pd_from_grammar->get_moves().c_str());
    ui->pd_progress_lab->setText(pd_from_grammar->progress().c_str());
}
void MainWindow::on_early_text_textChanged()
{
    ui->early_button->setEnabled(g != 0 && (ui->early_text->toPlainText().length() != 0));
}

void MainWindow::on_early_button_clicked()
{
    if (e.size() != 0)
    {
        for (int i = 0; i < (int)e.size(); ++i)
        {
            for (int j = 0; j < (int)e.size(); ++j)
            {
                delete e[i][j];
            }
        }
    }
    QString s = ui->early_text->toPlainText();
    QStringList sl = s.split(" ");
    std::vector<sign> e_word;
    for (int i = 0; i < (int)sl.size(); ++i)
    {
        sign b(sl[i].toStdString());
        e_word.push_back(b);
    }

    early = new early_alg(*g, e_word);

    e.resize(e_word.size() + 1);

    for (int i = 0; i < (int)e_word.size() + 1; ++i)
    {
        e[i].resize(e_word.size() + 1);
    }
    early_scroll = new QScrollArea(ui->centralWidget);
    early_scroll->setGeometry(0, 0, ui->centralWidget->width(), ui->centralWidget->height());
    for (int i = 0; i < (int)e_word.size() + 1; ++i)
    {
        for (int j = 0; j < (int)e_word.size() + 1; ++j)
        {
            if (i <= j)
            {
                e[i][j] = new QTextEdit(ui->tab_2);
                e[i][j]->setGeometry(30 + 100 * j, 200 + i * 120, 100, 120);
                e[i][j]->show();
                e[i][j]->setText(early->get(i, j).c_str());
                e[i][j]->setReadOnly(true);
                e[i][j]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            }
        }
    }

    int t_height = e.size() * 120 + 250;
    int t_width = e.size() * 100 + 70;
    t_height = std::max(t_height, this->height());
    t_width = std::max(t_width, this->width());
    ui->_tab->setGeometry(0, 0, t_width, t_height);
    early_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    early_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    early_scroll->setWidget(ui->_tab);
    early_scroll->show();
    refresh_early_labels();
    ui->early_back_button->setEnabled(true);
    ui->early_next_button->setEnabled(true);
}

void MainWindow::on__tab_currentChanged(int index)
{
    this->index = index;

    if (index == 0)
    {
        if (gn != 0)
        {
            if (g != selected_grammar)
            {
                delete selected_grammar;
            }
            selected_grammar = new grammar(gn->get_grammar());
        }
        if (early_scroll)
        {
            early_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            early_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            early_scroll->verticalScrollBar()->setValue(0);
            early_scroll->horizontalScrollBar()->setValue(0);
        }
    }
    else if (index == 2)
    {
        if (gr_from_push_down != 0)
        {
            if (g != selected_grammar)
            {
                delete selected_grammar;
            }
            selected_grammar = new grammar(gr_from_push_down->get_grammar());
        }
        if (early_scroll)
        {
            early_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            early_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            early_scroll->verticalScrollBar()->setValue(0);
            early_scroll->horizontalScrollBar()->setValue(0);
        }
    }
    else
    {
        if (early_scroll)
        {
            early_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            early_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        }
    }
}

void MainWindow::on_greibach_next_button_clicked()
{
    if (g != 0)
    {
        gn->next();
        if (selected_grammar != 0 && selected_grammar != g)
        {
            delete selected_grammar;
        }
        selected_grammar = new grammar(gn->get_grammar());
        refresh_greibach_labels();
    }
}

void MainWindow::on_greibach_back_button_clicked()
{
    if (g != 0)
    {
        gn->back();
        if (selected_grammar != 0 && selected_grammar != g)
        {
            delete selected_grammar;
        }
        selected_grammar = new grammar(gn->get_grammar());
        refresh_greibach_labels();
    }
}

void MainWindow::on_early_back_button_clicked()
{
    early->back();
    refresh_early_labels();
    refresh_early_matrix();
}

void MainWindow::on_early_next_button_clicked()
{
    early->next();
    refresh_early_labels();
    refresh_early_matrix();
}

void MainWindow::on_push_down_back_button_clicked()
{
    pd_from_grammar->back();
    refresh_pd_labels();
}

void MainWindow::on_push_down_next_button_clicked()
{
    pd_from_grammar->next();
    refresh_pd_labels();
}

void MainWindow::on_back_pd_grammar_button_clicked()
{
    gr_from_push_down->back();
    QString grammar_info = QString::fromUtf8((gr_from_push_down->show_info().c_str()));
    ui->pd_gr_info->setText(grammar_info);
    ui->pd_grammar->setText(gr_from_push_down->get_grammar().to_string().c_str());
    ui->pd_grammar_progress_lab->setText(gr_from_push_down->progress().c_str());
    if (selected_grammar != 0 && selected_grammar != g)
    {
        delete selected_grammar;
    }
    selected_grammar = new grammar(gr_from_push_down->get_grammar());
}

void MainWindow::on_next_pd_grammar_button_clicked()
{
    gr_from_push_down->next();
    QString grammar_info = QString::fromUtf8((gr_from_push_down->show_info().c_str()));
    ui->pd_gr_info->setText(grammar_info);
    ui->pd_grammar->setText(gr_from_push_down->get_grammar().to_string().c_str());
    ui->pd_grammar_progress_lab->setText(gr_from_push_down->progress().c_str());
    if (selected_grammar != 0 && selected_grammar != g)
    {
        delete selected_grammar;
    }
    selected_grammar = new grammar(gr_from_push_down->get_grammar());
}

void MainWindow::on_generate_pushdown_clicked()
{
    pd_from_grammar = new gr_to_pd(*g);

    ui->pd_info->setText(pd_from_grammar->show_info().c_str());
    ui->pd_text->setText(pd_from_grammar->get_moves().c_str());
    ui->pd_progress_lab->setText(pd_from_grammar->progress().c_str());
    ui->push_down_next_button->setEnabled(true);
    ui->push_down_back_button->setEnabled(true);
    ui->generate_grammar->setEnabled(true);
}

void MainWindow::on_generate_grammar_clicked()
{

    gr_from_push_down = new pd_to_gr(pd_from_grammar->get_push_down());
    QString grammar_info = QString::fromUtf8((gr_from_push_down->show_info().c_str()));
    ui->pd_gr_info->setText(grammar_info);
    ui->pd_grammar->setText(gr_from_push_down->get_grammar().to_string().c_str());
    ui->pd_grammar_progress_lab->setText(gr_from_push_down->progress().c_str());

    ui->next_pd_grammar_button->setEnabled(true);
    ui->back_pd_grammar_button->setEnabled(true);
    if (selected_grammar != 0 && selected_grammar != g)
    {
        delete selected_grammar;
    }
    selected_grammar = new grammar(gr_from_push_down->get_grammar());
}
