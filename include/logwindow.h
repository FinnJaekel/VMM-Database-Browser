#ifndef LOGWINDOW_H
#define LOGWINDOW_H
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>


class LogWindow : public QDialog
{
    Q_OBJECT
public:
    LogWindow(QWidget *parent =0, const char *name = 0);
    void setLogText(QString text);
private:
    QTextEdit* m_LogDisplay;
    QPushButton* m_OkButton;

};

#endif // LOGWINDOW_H
