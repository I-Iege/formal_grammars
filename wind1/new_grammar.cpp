#include "new_grammar.h"
#include "ui_new_grammar.h"

new_grammar::new_grammar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_grammar)
{

    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    message=0;
    scroll = new QScrollArea();
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setWidget(this);
    scroll->show();
}

new_grammar::~new_grammar()
{
    for(std::vector<QTextEdit*>::iterator it=t_rules.begin();it!=t_rules.end();++it)
    {
        delete *it;
    }
    for(std::vector<QLabel*>::iterator it=labvec.begin();it!=labvec.end();++it)
    {
        delete *it;
    }
    if(message!=0)
    {
        delete message;
    }
    delete ui;
    scroll->close();
}

void new_grammar::on_cancel_button_clicked()
{

    this->close();
}

void new_grammar::on_next_button_clicked()
{
    if(ui->non_terminal_t->toPlainText().length()!=0 && ui->terminal_t->toPlainText().length()!=0
    && ui->nstart_t->toPlainText().length()!=0 )
    {
        std::set<QString> str_set;
        ui->non_terminal_t->hide();
        ui->terminal_t->hide();
        ui->nstart_t->hide();
        ui->non_terminal_lab->hide();
        ui->terminal_lab->hide();
        ui->s_lab->hide();
        ui->helper_lab->setText(QString::fromUtf8("Kérem adja meg  az adott szabályokat |-jellel elválasztva!"));
        ui->finish_button->show();
        ui->finish_button->setEnabled(true);
        ui->back_button->setEnabled(true);

         QStringList sl;
        //read terminals
        sl=ui->terminal_t->toPlainText().split(" ");
        for(int i=0;i<sl.size();++i)
        {
            if(sl[i]!=QString("") && str_set.count(sl[i])==0)
            {
                sign a(sl[i].toStdString());
                t.push_back(a);
                str_set.insert(sl[i]);
            }
        }
        sl.clear();
        //read non-terminals
        sl=ui->non_terminal_t->toPlainText().split(" ");
        for(int i=0;i<sl.size();++i)
        {
            if(sl[i]!=QString("")  && str_set.count(sl[i])==0)
            {
                sign a(sl[i].toStdString(),false);
                n.push_back(a);
                str_set.insert(sl[i]);
            }
        }
        //read S
        sign a(ui->nstart_t->toPlainText().toStdString(),false);
        s=a;
        if((std::find(n.begin(),n.end(),s)==n.end()))
        {
            n.push_front(s);
            sl.push_front(s.to_string().c_str());
        }
        QTextEdit *qtext;
        QLabel *qlab;

        for(int i=0;i<n.size();++i)
        {
            qlab=new QLabel(this);
            qtext=new QTextEdit(this);
            t_rules.push_back(qtext);
            labvec.push_back(qlab);
            t_rules[i]->setGeometry(50,30+i*30,256,27);
            t_rules[i]->show();
            labvec[i]->setGeometry(20,30+i*30,25,23);
            QString labstr=n[i].to_string().c_str();
            labstr+= "->";
            labvec[i]->setText(labstr);
            labvec[i]->show();

        }

        int button_height=30*n.size()+50;
        this->setFixedHeight(std::max(button_height+43,300));
        button_height=std::max(button_height,240);
        ui->cancel_button->setGeometry(100,button_height,75,23);
        ui->back_button->setGeometry(190,button_height,75,23);
        ui->finish_button->setGeometry(280,button_height,75,23);
        ui->next_button->hide();
    }
    else
    {
        if(message!=0)
        {
           delete message;
        }
        message=new QMessageBox;
        QString warning=QString::fromUtf8("Üres sor: ");
        QString empty_line;
        if(ui->non_terminal_t->toPlainText().length()==0)
        {
            empty_line=QString::fromUtf8("Nem-terminálisok");
        }
        else if(ui->terminal_t->toPlainText().length()==0)
        {
            empty_line=QString::fromUtf8("Terminálisok");
        }
        else
        {
            empty_line=QString::fromUtf8("Kezdőjel");
        }
        warning+=empty_line;
        message->setText(warning);
        message->show();
    }
}

void new_grammar::on_non_terminal_t_textChanged()
{
    ui->next_button->setEnabled(!(ui->non_terminal_t->toPlainText()==QString("")));
}

void new_grammar::on_finish_button_clicked()
{
    //search empty lines
    bool find=false;
    QString empty_line;
    for(int i=0;!find && i<(int)t_rules.size();++i)
    {
       if((find=t_rules[i]->toPlainText().trimmed().isEmpty()))
       {
           empty_line=labvec[i]->text();
       }
    }
    //create grammar
    if(!find)
    {
        bool error=false;
        for(int i=0; i<(int)t_rules.size() && !error;++i)
        {
            QStringList qsl=t_rules[i]->toPlainText().split("|");
            std::list<sign_list> node;
            std::set<sign_list> rule_set;
            for(int j=0;j<qsl.size();++j)
            {
                if(qsl[j]=="")
                {
                    continue;
                }
                QStringList qsl2=qsl[j].split(" ");
                sign_list s_list;
                for(int k=0;k<qsl2.size();++k)
                {
                    if(qsl2[k]=="")
                    {
                        continue;
                    }
                    std::string str=qsl2[k].toStdString();
                    sign* sg= new sign(str,false);
                    sign_list::iterator it=std::find(n.begin(),n.end(),*sg);
                    if(it==n.end())
                    {
                        delete sg;
                        sg=new sign(str,true);
                        it=std::find(t.begin(),t.end(),*sg);
                        if(it==t.end())
                        {
                            error=true;
                            message=new QMessageBox;
                            QString warning=sg->to_string().c_str() + QString::fromUtf8(" nem szerepel a terminálisok, nem-terminálisok listájában!");
                            message->setText(warning);
                            message->show();
                        }
                        else
                        {
                            s_list.push_back(*sg);
                            delete sg;
                        }
                    }
                    else
                    {
                        s_list.push_back(*sg);
                        delete sg;
                    }
                }
                if(rule_set.count(s_list)==0)
                {
                    node.push_back(s_list);
                    rule_set.insert(s_list);
                }
            }
            if(!error)
            {
                p[n[i]]=node;
            }
            else
            {
                p.clear();
            }
        }
        if(!error)
        {
            grammar *g=new grammar(n,t,p,s);
            emit gr_finished(g);
            this->close();
        }
    }
    else
    {
        if(message!=0)
        {
            delete message;
        }
        message=new QMessageBox;
        QString warning=QString::fromUtf8("Üres sor: ");
        warning+=empty_line;
        message->setText(warning);
        message->show();
    }
}

void new_grammar::on_back_button_clicked()
{
    for(std::vector<QTextEdit*>::iterator it=t_rules.begin();it!=t_rules.end();++it)
    {
        delete *it;
    }
    for(std::vector<QLabel*>::iterator it=labvec.begin();it!=labvec.end();++it)
    {
        delete *it;
    }
    t_rules.clear();
    labvec.clear();
    t.clear();
    n.clear();
    this->setFixedHeight(300);
    ui->non_terminal_t->show();
    ui->terminal_t->show();
    ui->nstart_t->show();
    ui->non_terminal_lab->show();
    ui->terminal_lab->show();
    ui->s_lab->show();

    ui->helper_lab->setText(QString::fromUtf8("Kérem adja meg  az adott jeleket szóközzel elválasztva!"));
    ui->next_button->show();
    ui->finish_button->hide();
    ui->finish_button->setEnabled(false);
    ui->back_button->setEnabled(false);
    ui->cancel_button->setGeometry(100,240,75,23);
    ui->back_button->setGeometry(190,240,75,23);

}
