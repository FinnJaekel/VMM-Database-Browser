#include "logwindow.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>

using namespace std;
LogWindow::LogWindow(QWidget *parent, const char *name)
{
    m_LogDisplay = new QTextEdit(this);
    m_OkButton = new QPushButton(tr("Ok"),this);
    connect(m_OkButton,SIGNAL(clicked()),this,SLOT(close()));
    //m_LogDisplay->setFixedSize(800,800);
    m_LogDisplay->resize(800,800);
    this->adjustSize();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *testLayout = new QVBoxLayout();
    testLayout->addWidget(m_LogDisplay);
    testLayout->addWidget(m_OkButton);
    mainLayout->addLayout(testLayout);
}

void LogWindow::setLogText(QString text)
{
    m_LogDisplay->setText(text);
}



