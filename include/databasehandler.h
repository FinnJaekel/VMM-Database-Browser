#ifndef DBHandler_H
#define DBHandler_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QLabel>
#include <set>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>



class QCustomPlot;
class MainWindow;

class DBHandler : public QObject
{
    Q_OBJECT
public:
    DBHandler(MainWindow *top, QObject *parent);
    ~DBHandler();
    bool initiateDatabase();
    void listAvailableHybrids();
    void listAvailableMeasurements(QString Hybrid_ID);
    int listAvailableMeasurementTypes(QString Measurement_ID, QString Hybrid_ID,QString currentString);
    void plotData(QString measurementType, QString Measurement_ID, QString Hybrid_ID);
    QString getCurrentHybridID();
    void evaluateMeasurement(QString Hybrid_id);
    void exportQueryToTxt();
    void getAndStoreConfigs(QString dir);
    void addfilter();
    void getNormCurve(QString whichProp);
    void putAvailableHybrids(QString locations);
    void showHybridInHisto(QString hybrid_id);
    void getVMMClassDistro();
    void getHybridClassDistro();
    bool downloadDB();

private:
    QHash<QString,int> h_ChannelResults[2][64];
    QHash<QString,int> h_VMMResults[2];
    int h_nwchannels[2] = {64,64};
    double h_monitoringADCcal[2][2];
    QNetworkAccessManager m_WebCtrl;
    void getUserInformation();
    void getConnectionInformation();
    MainWindow* m_mainWindow;
    QSqlDatabase db;
    QStringList m_criticaltests = {"Internal","External","Pedestal","ADCCalibrationExternal","ADCCalibrationInternal"};
    QVector<double> convertStrToVec(QString original);
    QString getAdditionalFilters();
    QString getLatestMeasurementFilter();
    QVector<QVector<double> > loadData(QString measurementType, QString Measurement_ID, QString Hybrid_ID, QVector<double> &x, int datlen);
    double getThresholdSetting(int vmm);
    void evaluateData(QString type, QVector<double> x, QVector<double> y[], QString hybrid_id, int datalen=2);
    double evaluateADCCalibration(QVector<double> dataset, QString caller);
    QVector<double> evaluateADCCalibrationFit(QVector<double> datax , QVector<double> datay, QString caller, int chip, QVector<double> &params);
    void MarkChannel(QString whichtest, int vmm, int chno, QString status);
    void MarkChannel(QString whichtest, int vmm, int chno, int status);
    double getStdDev(QVector<double> data);
    double getAverage(QVector<double> data);
    double getMedian(QVector<double> data);
    void evaluateResults();
    double getDataLength(QString measurementType,QString Measurement_ID,QString Hybrid_ID);
    std::set<int> findOutliers(QVector<double> input,double thr);
    void FitLinear(QVector<double> x, QVector<double> y,double& slope,double& intercept);
    void ListNormCurves();
    QVector<double> getHistoLimits(QVector<double> y);


    void getCurveSettings(QString caller, double &ideal, double &range);
public slots:
    void showDetails();
    void doQuery();
    void readSettingFile();
    void dbdownloaded(QNetworkReply*pReply);

};

#endif // DBHandler_H

#ifndef _MAINWINDOW_HPP
#include "mainwindow.h"
#endif
