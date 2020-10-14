#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class FilterDialog : public QDialog
{
    Q_OBJECT
public:
    FilterDialog(QWidget *parent = 0, const char *name= 0);
    void SetColumnsToFilter(QStringList cols, QStringList types);
    QString getFilter();
signals:
    void FilterReady();
private:
    QComboBox *m_cols;
    QComboBox *m_FilterType;
    QLineEdit *m_lEdit1;
    QLabel *m_Filterlabel;
    QLabel *m_variablelabel;
    QLabel *m_errorlabel;
    QPushButton *addButton;
    QPushButton *cancelButton;
    QStringList m_colList;
    QStringList m_typesList;
    QString m_filter ="";
private slots:
    void updateDialogLabel();
    void createFilterStatement();
};

#endif // FILTERDIALOG_H
