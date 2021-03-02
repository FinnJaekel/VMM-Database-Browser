#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QMainWindow>
#include "ui_dbwindow.h"
#include "databasehandler.h"
#include "qcustomplot.h"

class MainWindow;
class FilterDialog;
namespace  Ui {
class dbwindow;
}

class DBWindow : public QMainWindow
{
    Q_OBJECT
    friend class DBHandler;
    friend class MainWindow;

public:
    explicit DBWindow(MainWindow *top, QWidget *parent=0);
    ~DBWindow();

    void PlotData(QVector<double> x, QVector<double> y[], QString xlabel, QString ylabel, QString name="", QString graphlabel="VMM", int datalen =2,QCustomPlot *plot=nullptr);
    void PlotHistogram(QVector<double> y, double xlow, double xhigh, int nbins, QString xlabel, QString ylabel, QString name, QString graphlabel);
    void AddFitToPlot(QVector<double> x, QVector<double> y[], QString graphlabel = "Fit", int datalen = 2,QCustomPlot *plot = nullptr);
private slots:
    void on_pushButton_connect_clicked();

    void on_comboBox_MeasurementID_currentIndexChanged(const QString &arg1);

    void on_comboBox_MeasurementType_currentIndexChanged(const QString &arg1);

    void on_pushButton_refresh_clicked();

    void on_pushButton_details_clicked();

    void on_pushButton_getquery_clicked();

    void on_pushButton_export_clicked();

    void on_pushButton_configdownload_clicked();

    void on_pushButton_addfilter_clicked();

    void on_pushButton_clicked();

    void on_pushButton_removeAllFilters_clicked();

    void on_pushButton_storeFilters_clicked();

    void on_pushButton_loadFilters_clicked();

    void on_pushButton_normcurve_clicked();

    void on_pushButton_addfilter_2_clicked();

    void on_comboBox_normcurve_currentIndexChanged(const QString &arg1);

    void on_pushButton_savepdf_clicked();

    void on_lineEdit_locationFilter_returnPressed();

    void on_listWidget_availableHybrids_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void SetClearing(bool val){m_clearing = val;}

    bool getClearing(){return m_clearing;}

    void on_checkBox_filterApply_stateChanged(int arg1);

    void on_pushButton_savePlot_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    MainWindow *m_mainWindow;
    Ui::dbwindow *ui;
    DBHandler* m_dbhandler;
    bool m_clearing = false;
    QString currentTypeSelection;
signals:
    void readsettings();

};

#endif // DBWINDOW_H

