#include "filterdialog.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>

using namespace std;
FilterDialog::FilterDialog(QWidget *parent, const char *name)
{
    m_lEdit1 = new QLineEdit(this);
    m_cols = new QComboBox(this);
    m_FilterType = new QComboBox(this);
    m_Filterlabel = new QLabel(tr("Select column for filtering"),this);
    m_variablelabel = new QLabel(tr(""),this);
    addButton = new QPushButton(tr("Add"),this);
    cancelButton = new QPushButton(tr("Close"),this);
    m_errorlabel = new QLabel(tr(""),this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *testLayout = new QVBoxLayout();
    QHBoxLayout *buttons = new QHBoxLayout(this);
    testLayout->addWidget(m_Filterlabel);
    testLayout->addWidget(m_cols);
    testLayout->addWidget(m_FilterType);
    testLayout->addWidget(m_variablelabel);
    testLayout->addWidget(m_lEdit1);
    testLayout->addWidget(m_errorlabel);
    buttons->addWidget(addButton);
    buttons->addWidget(cancelButton);
    mainLayout->addLayout(testLayout);
    mainLayout->addLayout(buttons);
    m_FilterType->addItem("Range");
    m_FilterType->addItem("<=");
    m_FilterType->addItem(">=");
    m_FilterType->addItem("=");
    m_FilterType->addItem("!=");
    connect(addButton,SIGNAL(clicked()),this,SLOT(createFilterStatement()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(m_cols,SIGNAL(currentIndexChanged(int)),this,SLOT(updateDialogLabel()));
    connect(m_FilterType,SIGNAL(currentIndexChanged(int)),this,SLOT(updateDialogLabel()));
}
void FilterDialog::SetColumnsToFilter(QStringList cols, QStringList types){
    for(int i=0;i<cols.size();i++){
        cout << cols[i].toStdString()<<endl;
        cout << types[i].toStdString()<<endl;
        if(types[i] == "text" || types[i] == "real" || types[i] == "integer" || types[i] == "date"){
            cout << "adding " << cols[i].toStdString() <<endl;
            m_colList << cols[i];
            m_typesList << types[i];
            m_cols->addItem(cols[i]);
        }
    }
}

QString FilterDialog::getFilter()
{
    return m_filter;
}

void FilterDialog::updateDialogLabel()
{
    int index = m_cols->currentIndex();
    QString type = m_typesList[index];
    int opindex = m_FilterType->currentIndex();
    QString operation = m_FilterType->itemText(opindex);
    m_variablelabel->setText(type);
    if(type == "text"){
        m_variablelabel->setWordWrap(true);
        if(operation =="Range"){
            m_variablelabel->setText(tr("Enter multiple strings, separate by ',' (e.g. str1,str2,str3)"));
        }
        if(operation ==">=" || operation =="<="){
            m_variablelabel->setText(tr("Enter single string. Operation will not necessarily give out useful results"));
        }
        if(operation == "=" || operation == "!="){
            m_variablelabel->setText(tr("Enter single string"));
        }
    }
    if(type == "real" || type == "integer"){
        m_variablelabel->setWordWrap(true);
        if(operation =="Range"){
            m_variablelabel->setText(tr("Enter value range, separate by ',' (lower,upper) "));
        }
        if(operation ==">=" || operation =="<="){
            m_variablelabel->setText(tr("Enter single number"));
        }
        if(operation == "=" || operation == "!="){
            m_variablelabel->setText(tr("Enter single number"));
        }
    }
    if(type == "date"){
        m_variablelabel->setWordWrap(true);
        if(operation =="Range"){
            m_variablelabel->setText(tr("Enter date range, separate by ',' (e.g. date1, date2) , format yyyy-mm-dd"));
        }
        if(operation ==">=" || operation =="<="){
            m_variablelabel->setText(tr("Enter single date, format yyyy-mm-dd"));
        }
        if(operation == "=" || operation == "!="){
            m_variablelabel->setText(tr("Enter single date, format yyyy-mm-dd"));
        }
    }
}

void FilterDialog::createFilterStatement()
{
    m_errorlabel->clear();
    m_errorlabel->setStyleSheet("background-color: ");
    int index = m_cols->currentIndex();
    QString type = m_typesList[index];
    QString value = m_colList[index];
    QString text = m_lEdit1->text();
    QString statement = "";
    int opindex = m_FilterType->currentIndex();
    QString operation = m_FilterType->itemText(opindex);
    if(text.isEmpty()==true){
        m_errorlabel->setText("No Input given");
        m_errorlabel->setStyleSheet("background-color: red");
        cout <<"No filter input given"<<endl;
    }
    else{
        if(type == "text"){
            QStringList strings = text.split(",");
            statement += value;
            if(operation == "Range" || operation == "="){
                statement += " IN (";
                statement += "'"+strings[0]+"'";
                for(int i=1;i<strings.size();i++){
                    statement += ",'"+strings[i]+"'";
                }
                statement += ")";
                this->close();
            }
            else{
                if(strings.size()>1){
                    m_errorlabel->setText(tr("Only single values allowed, please remove one value or change Filtertype to Range"));
                    m_errorlabel->setStyleSheet("background-color: red");
                }
                else{
                    statement += " " + operation + "'"+ strings[0] + "'";
                    this->close();
                }
            }
        }
        if(type == "real" || type == "integer"){
            QStringList strings = text.split(",");
            if(operation == "Range"){
                if(strings.size()!=2){
                    m_errorlabel->setText(tr("Please enter the range (lower,upper) separated by a comma"));
                    m_errorlabel->setStyleSheet("background-color: red");
                }
                else{
                    statement += value + " between " + strings[0] + " and " + strings[1];
                    this->close();
                }
            }
            else{
                if(strings.size()>1){
                    m_errorlabel->setText(tr("Only single values allowed, please remove one value or change Filtertype to Range"));
                    m_errorlabel->setStyleSheet("background-color: red");
                }
                else{
                    statement += value + " " + operation + strings[0];
                    this->close();
                }
            }
        }
        if(type == "date"){
            QStringList strings = text.split(",");
            if(operation == "Range"){
                if(strings.size()!=2){
                    m_errorlabel->setText(tr("Please enter the date range separated by a comma"));
                    m_errorlabel->setStyleSheet("background-color: red");
                }
                else{
                    statement += value + " between " + "'" + strings[0] + "'" + " and " + "'" + strings[1] + "'" ;
                    this->close();
                }
            }
            else{
                if(strings.size()>1){
                    m_errorlabel->setText(tr("Only single values allowed, please remove one value or change Filtertype to Range"));
                    m_errorlabel->setStyleSheet("background-color: red");
                }
                else{
                    statement += value + " " + operation + "'" + strings[0] + "'" ;
                    this->close();
                }
            }
        }
        m_filter = statement;
    }
}
