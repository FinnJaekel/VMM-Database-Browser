#include "mainwindow.h"
#include "dbwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_dbwindow = new DBWindow(this);
    m_dbwindow->setWindowTitle("VMM3 Test Database Browser");
    m_dbwindow->show();
    m_dbwindow->m_dbhandler->readSettingFile();
}

MainWindow::~MainWindow()
{
}

