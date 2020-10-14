#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasehandler.h"

class DBWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class DBWindow;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    DBWindow *m_dbwindow;
    DBHandler* m_dbhandler;

private:
};

#endif // MAINWINDOW_H
#ifndef _DBWINDOW_HPP
#include "dbwindow.h"
#endif
