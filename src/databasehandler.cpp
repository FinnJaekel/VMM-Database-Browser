#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QInputDialog>
#include <QFont>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <set>
//#include <qcustomplot.h>
#include "databasehandler.h"
#include <filterdialog.h>
#include <PolynomialRegression.h>

using namespace std;
DBHandler::DBHandler(MainWindow *top, QObject *parent)
{
    m_mainWindow = top;
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db = QSqlDatabase::addDatabase("QPSQL");
    downloadDB();
}
DBHandler::~DBHandler(){
    delete this;
}

bool DBHandler::initiateDatabase(){
    getConnectionInformation();
    //getUserInformation();
    bool working = db.open();
    cout << working << endl;
    db.close();
    return working;
}

bool DBHandler::downloadDB(){
    cout << "Trying to download DB"<<endl;
    connect(&m_WebCtrl,SIGNAL(finished(QNetworkReply*)),this,SLOT(dbdownloaded(QNetworkReply*)));
    QNetworkRequest request(QUrl("https://finnjaekel.github.io/VMM-test-result-database/testdb.db"));
    m_WebCtrl.get(request);
    cout << "Request send"<<endl;
}

void DBHandler::getConnectionInformation(){
    QString hostname = m_mainWindow->m_dbwindow->ui->adressfield->toPlainText();
    QString port = m_mainWindow->m_dbwindow->ui->portfield->toPlainText();
    QString dbname = m_mainWindow->m_dbwindow->ui->dbnamefield->toPlainText();
    db.setHostName(hostname);
    db.setPort(port.toInt());
    db.setDatabaseName(dbname);
    db.setDatabaseName(QCoreApplication::applicationDirPath()+"/testdb.db");
}

QString DBHandler::getCurrentHybridID()
{
    QTableView* table = m_mainWindow->m_dbwindow->ui->tableView;
    QModelIndex h_point = table->selectionModel()->currentIndex();
    QString Hybrid_id= table->model()->data(table->model()->index(h_point.row(),0)).toString();
    return Hybrid_id;
}

void DBHandler::getUserInformation(){
    QString user = QInputDialog::getText(0,tr("QInputDialog::getText()"),tr("User Name"));
    QString password = QInputDialog::getText(0,tr("QInputDialog::getText()"),tr("Password"));
    db.setUserName(user);
    db.setPassword(password);
    //db.setUserName("fjaekel");
    //db.setPassword("1234");
}

void DBHandler::listAvailableHybrids(){
    db.open();
    QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel();
    QTableView* table = m_mainWindow->m_dbwindow->ui->tableView;
    QItemSelectionModel *selectmodel = table->selectionModel();
    QString tablequery = "SELECT * FROM hybrid_overview ";
    if(m_mainWindow->m_dbwindow->ui->checkBox_filterLatest->isChecked()==true){
        QString latestMeasFilter = getLatestMeasurementFilter();
        if(latestMeasFilter.size()>0){
            tablequery +="WHERE ";
            tablequery += latestMeasFilter;
        }
    }
    QString otherFilters = getAdditionalFilters();
    if(otherFilters.size()>1){
        if(m_mainWindow->m_dbwindow->ui->checkBox_filterLatest->isChecked()==false){
            tablequery += "WHERE ";
        }
        else{
            if(m_mainWindow->m_dbwindow->ui->listWidget->count()>0){
                tablequery += " AND ";
            }
        }
        tablequery += otherFilters;
    }
    else{
        tablequery += ";";
    }
    cout << tablequery.toStdString()<<endl;
    model->setQuery(tablequery,db);
    table->setModel(model);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter | (Qt::Alignment)Qt::TextWordWrap);
    //table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    QFont font = table->font();
    font.setPointSize(9);
    table->setFont(font);
    table->setWordWrap(true);
    table->resizeRowsToContents();
    table->show();

    connect(table->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(showDetails()));
    db.close();
    ListNormCurves();
    putAvailableHybrids(m_mainWindow->m_dbwindow->ui->lineEdit_locationFilter->text());
}

QString DBHandler::getAdditionalFilters(){
    int count = m_mainWindow->m_dbwindow->ui->listWidget->count();
    QString allfilter = "";
    for(int i=0;i<count;i++)
    {
        QListWidgetItem* item = m_mainWindow->m_dbwindow->ui->listWidget->item(i);
        QString addfilter = item->text();
        cout << addfilter.toStdString()<<endl;
        allfilter += addfilter +" AND ";
    }
    QString andstrip = allfilter.left(allfilter.size()-4);
    andstrip += ";";
    return andstrip;
}

QString DBHandler::getLatestMeasurementFilter()
{
    return "measurement_id IN (SELECT max FROM(SELECT hybrid_id,MAX(measurement_id) as max FROM hybrid_overview GROUP BY hybrid_id) as foo)";
}

void DBHandler::getAndStoreConfigs(QString dir)
{
    db.open();
    QSqlQuery query;
    QString measurement_id = m_mainWindow->m_dbwindow->ui->comboBox_MeasurementID->currentText();
    QString qstr = "SELECT * FROM configs WHERE measurement_id =?;";
    query.prepare(qstr);
    query.bindValue(0,measurement_id);
    query.exec();
    if(query.size()<1){
        cout << "No Config files for this measurement found"<<endl;
    }
    while(query.next()){
       // cout << query.value(0).toString().toStdString()<< "\t" << query.value(1).toString().toStdString()<< "\t"
            // << query.value(2).toString().toStdString()<< "\t" << query.value(3).toString().toStdString()<< "\t" << endl;
        QString filename = query.value(2).toString();
        QByteArray content = query.value(3).toByteArray();
        QString filepath = dir+"/"+measurement_id+"config";
        QDir dir;
        if(!dir.exists(filepath)){
            dir.mkpath(filepath);
        }
        QFile file(filepath+"/"+filename);
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            file.write(content);
            cout <<"written content" <<endl;
        }
    }
    return;
}

void DBHandler::showDetails(){
    QTableView* table = m_mainWindow->m_dbwindow->ui->tableView;
    QModelIndex h_point = table->selectionModel()->currentIndex();
    QString Hybrid_id= table->model()->data(table->model()->index(h_point.row(),0)).toString();
    m_mainWindow->m_dbwindow->ui->comboBox_MeasurementID->clear();
    listAvailableMeasurements(Hybrid_id);
    evaluateMeasurement(Hybrid_id);
}

void DBHandler::evaluateMeasurement(QString Hybrid_id){
    QLabel* alllabels[22] = {m_mainWindow->m_dbwindow->ui->pedestalstatuslabel1,m_mainWindow->m_dbwindow->ui->pedestalstatuslabel2,m_mainWindow->m_dbwindow->ui->thresholdstatuslabel1,m_mainWindow->m_dbwindow->ui->thresholdstatuslabel2,
                          m_mainWindow->m_dbwindow->ui->extchannels1label,m_mainWindow->m_dbwindow->ui->extchannels2label,m_mainWindow->m_dbwindow->ui->intchannels1label,m_mainWindow->m_dbwindow->ui->intchannels2label,
                           m_mainWindow->m_dbwindow->ui->adccurvestatus1label,m_mainWindow->m_dbwindow->ui->adccurvestatus2label, m_mainWindow->m_dbwindow->ui->adccurvestatus3label, m_mainWindow->m_dbwindow->ui->adccurvestatus4label,
                            m_mainWindow->m_dbwindow->ui->tdcstatuslabel1,m_mainWindow->m_dbwindow->ui->tdcstatuslabel2,m_mainWindow->m_dbwindow->ui->noisestatus1label, m_mainWindow->m_dbwindow->ui->noisestatus2label,
                             m_mainWindow->m_dbwindow->ui->adccal_bads1,m_mainWindow->m_dbwindow->ui->adccal_bads2, m_mainWindow->m_dbwindow->ui->adcvertexstatus1label, m_mainWindow->m_dbwindow->ui->adcvertexstatus2label,
                              m_mainWindow->m_dbwindow->ui->adcvertexstatus3label, m_mainWindow->m_dbwindow->ui->adcvertexstatus4label};
    for(int i=0; i<22;i++){
        alllabels[i]->clear();
        alllabels[i]->setStyleSheet("background-color:");
    }
    QGridLayout* grids [2] = {m_mainWindow->m_dbwindow->ui->ChannelsVMM0_grid,m_mainWindow->m_dbwindow->ui->ChannelsVMM1_grid};
    for(int i=0;i<2;i++){
        QLayoutItem *child;
        while((child=grids[i]->takeAt(0))!=nullptr){
            delete child->widget();
            delete child;
        }
        for(int j=0;j<64;j++){
            h_ChannelResults[i][j].clear();
        }
        h_VMMResults[i].clear();
    }
    cout << "Crash1" <<endl;
    int size = m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType->count();
    QString meas_id = m_mainWindow->m_dbwindow->ui->comboBox_MeasurementID->currentText();
    if(meas_id.isEmpty()==false){
        for(int i=0; i<size;i++){
            QString type = m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType->itemText(i);
            QVector<double> x;
            QVector<QVector<double>> yvec;
            QVector<QString> labels;
            int datlen = getDataLength(type,meas_id,Hybrid_id);
            yvec=loadData(type,meas_id,Hybrid_id,x,datlen);
            int vecsize = yvec.count();
            QVector<double> y[vecsize];
            for(int i=0; i<vecsize;i++){
                QVector<double> vals = yvec[i];
                y[i]=vals;
            }
            if(i==2){
                cout << type.toStdString() <<endl;
            }
            evaluateData(type,x,y,Hybrid_id);
        }
    }
    evaluateResults();

}

void DBHandler::doQuery(){
    QString querytext = m_mainWindow->m_dbwindow->ui->lineEdit_query->text();
    bool filtered = querytext.contains("WHERE",Qt::CaseInsensitive);
    if(m_mainWindow->m_dbwindow->ui->checkBox_filterLatest->isChecked()==true){
        querytext.remove(";");
        QString latestMeasFilter = getLatestMeasurementFilter();
        if(latestMeasFilter.size()>0){
            if(filtered == true){
                querytext+=" AND ";
            }
            else{
                querytext+=" WHERE ";
            }
            querytext += latestMeasFilter;
            cout << querytext.toStdString()<<endl;
        }
        querytext+=";";
    }

    db.open();
    QTableView* table = m_mainWindow->m_dbwindow->ui->tableView;
    QSqlQueryModel *model = new QSqlQueryModel();
    QItemSelectionModel *selectmodel = table->selectionModel();
    model->setQuery(querytext,db);
    table->setModel(model);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter | (Qt::Alignment)Qt::TextWordWrap);
    //table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    QFont font = table->font();
    font.setPointSize(9);
    table->setFont(font);
    table->setWordWrap(true);
    table->resizeRowsToContents();
    table->show();
    db.close();
}

void DBHandler::readSettingFile()
{
    QString path = QCoreApplication::applicationDirPath()+"/../testsettings.txt";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    else{
        while(!file.atEnd()){
            QString line = QString(file.readLine());
            line.remove('\n');
            QStringList splitted = line.split(QRegExp("\\s+"));
            if(splitted[0]=="MonitoringADCSlope"){
                if(splitted.count()<5){
                    cout << "incomplete configuration"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->monitoringADC_g_l->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->monitoringADC_g_u->setText(splitted[2]);
                    m_mainWindow->m_dbwindow->ui->monitoringADC_o_l->setText(splitted[3]);
                    m_mainWindow->m_dbwindow->ui->monitoringADC_o_u->setText(splitted[4]);
                }
            }

            if(splitted[0]=="MonitoringADCIntercept"){
                if(splitted.count()<5){
                    cout << "incomplete configuration"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->monitoringADC_g_l_2->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->monitoringADC_g_u_2->setText(splitted[2]);
                    m_mainWindow->m_dbwindow->ui->monitoringADC_o_l_2->setText(splitted[3]);
                    m_mainWindow->m_dbwindow->ui->monitoringADC_o_u_2->setText(splitted[4]);
                }
            }
            if(splitted[0]=="Pedestal"){
                if(splitted.count()<5){
                    cout << "incomplete configuration"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->pedestal_g_l->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->pedestal_g_u->setText(splitted[2]);
                    m_mainWindow->m_dbwindow->ui->pedestal_o_l->setText(splitted[3]);
                    m_mainWindow->m_dbwindow->ui->pedestal_o_u->setText(splitted[4]);
                }
            }
            if(splitted[0]=="AverageTDCRange"){
                if(splitted.count()<5){
                    cout << "incomplete configuration"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->tdc_g_l->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->tdc_g_u->setText(splitted[2]);
                    m_mainWindow->m_dbwindow->ui->tdc_o_l->setText(splitted[3]);
                    m_mainWindow->m_dbwindow->ui->tdc_o_u->setText(splitted[4]);
                }
            }
            if(splitted[0]=="BaselineNoise"){
                if(splitted.count()<3){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->noise_g_l->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->noise_o_l->setText(splitted[2]);
                }
            }
            if(splitted[0]=="Threshold"){
                if(splitted.count()<3){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->threshold_g_l->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->threshold_o_l->setText(splitted[2]);
                }
            }
            if(splitted[0]=="ADCCalibrationChannelDeviation"){
                if(splitted.count()<3){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->adcrange_g_l->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->adcrange_o_l->setText(splitted[2]);
                }
            }
            if(splitted[0]=="WorkingChannelsExternal"){
                if(splitted.count()<3){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->external_g_l->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->external_o_l->setText(splitted[2]);
                }
            }
            if(splitted[0]=="WorkingChannelsInternal"){
                if(splitted.count()<3){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->internal_g_l->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->internal_o_l->setText(splitted[2]);
                }
            }
            if(splitted[0]=="ADCCalibrationVertexPosExtern"){
                if(splitted.count()<3){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->adcvertex_g_e->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->adcvertex_o_e->setText(splitted[2]);
                }
            }
            if(splitted[0]=="ADCCalibrationVertexPosIntern"){
                if(splitted.count()<3){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->adcvertex_g_i->setText(splitted[1]);
                    m_mainWindow->m_dbwindow->ui->adcvertex_o_i->setText(splitted[2]);
                }
            }
            if(splitted[0]=="DatabaseIP"){
                if(splitted.count()<2){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->adressfield->setText(splitted[1]);
                }
            }
            if(splitted[0]=="DatabaseName"){
                if(splitted.count()<2){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->dbnamefield->setText(splitted[1]);
                }
            }
            if(splitted[0]=="DatabasePort"){
                if(splitted.count()<2){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    m_mainWindow->m_dbwindow->ui->portfield->setText(splitted[1]);
                }
            }
            if(splitted[0]=="DatabaseUser"){
                if(splitted.count()<2){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    this->db.setUserName(splitted[1]);
                }
            }
            if(splitted[0]=="DatabasePassword"){
                if(splitted.count()<2){
                    cout << "incomplete configuration,"<<endl;
                }
                else{
                    this->db.setPassword(splitted[1]);
                }
            }
        }
    }
}

void DBHandler::dbdownloaded(QNetworkReply * pReply)
{
    cout << "dbdownloaded, trying to store DB"<<endl;
    QByteArray downloaded = pReply->readAll();
    QString path = QCoreApplication::applicationDirPath()+"/testdb.db";
    QFile dbfile(path);
    dbfile.open(QIODevice::WriteOnly);
    dbfile.write(downloaded);
    dbfile.close();
}


void DBHandler::getCurveSettings(QString caller, double &ideal, double &range)
{
    QString sIdeal = "ADCCalibrationCurvature";
    QString sRange = "ADCCalibrationCurvature";
    if(QString::compare(caller,"Internal",Qt::CaseInsensitive)==0){
        sIdeal += "InternIdeal";
        sRange += "InternStddev";
    }
    if(QString::compare(caller,"External",Qt::CaseInsensitive)==0){
        sIdeal += "ExternIdeal";
        sRange += "ExternStddev";
    }

    QString path = QCoreApplication::applicationDirPath()+"/../testsettings.txt";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    else{
        while(!file.atEnd()){
            QString line = QString(file.readLine());
            line.remove('\n');
            QStringList splitted = line.split(QRegExp("\\s+"));
            if(splitted.count()<2){
                cout << "incomplete configuration"<<endl;
            }
            else{
                if(splitted[0]==sIdeal){
                    ideal = QVariant(splitted[1]).toDouble();
                    cout << ideal<<endl;
                }
                if(splitted[0]==sRange){
                    range = QVariant(splitted[1]).toDouble();
                    cout << range<<endl;
                }
            }
        }
    }
}

void DBHandler::exportQueryToTxt(){
    QString filename = QFileDialog::getSaveFileName(m_mainWindow,tr("Export table to txt Format"),"",tr("txt Files(*.txt);;All Files(*)"));
    QFile* fp = new QFile(filename);
    QTableView* table = m_mainWindow->m_dbwindow->ui->tableView;
    int rows = table->model()->rowCount();
    int cols = table->model()->columnCount();
    fp->open(QIODevice::WriteOnly);
    for(int i=0; i<rows; i++){
        QByteArray line = "";
        QVector<QVector<double>> alldata;
        for(int j=0; j<cols;j++){
            QString data = table->model()->data(table->model()->index(i,j)).toString();
            /*if(data.length()>128){
                QVector<double> x = convertStrToVec(data);
                alldata.push_back(x);
            }
            else{
                line += data;
                line += "\t";
            }*/
            line += data;
            line += "\t";
        }
        /*if(alldata.count()>0){
            line += "\n";
        }
        QVector<int> sizes;
        int maxsize = 0;
        for(int h=0; h< alldata.count();h++){
            int datsize = alldata[h].count();
            if(datsize>maxsize){
                maxsize = datsize;
            }
            sizes.push_back(datsize);
        }
        for(int k=0; k<maxsize;k++){
            for(int l = 0; l<alldata.size();l++){
                if(l<=sizes[l]){
                    line += QString::number(alldata[l][k]) + "\t";
                }
            }
            line += "\n";
        }*/

        line+="\n";
        fp->write(line);
    }
    fp->close();
}

void DBHandler::listAvailableMeasurements(QString Hybrid_ID){
    db.open();
    QSqlQuery query;
    QString querystring = "SELECT DISTINCT measurement_id FROM hybrid_data WHERE hybrid_id = ? ORDER BY measurement_id ASC";
    query.prepare(querystring);
    query.bindValue(0,Hybrid_ID);
    query.exec();
    if(query.last()){
        do{
            m_mainWindow->m_dbwindow->ui->comboBox_MeasurementID->addItem(query.value(0).toString());
        }while(query.previous());
    }
    db.close();
}

int DBHandler::listAvailableMeasurementTypes(QString Measurement_ID, QString Hybrid_ID, QString currentString){
    db.open();
    QComboBox* box = m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType;
    QSqlQuery query;
    QString querystring = "SELECT measurement_type FROM hybrid_data WHERE hybrid_id = ? AND measurement_id = ?";
    query.prepare(querystring);
    query.bindValue(0,Hybrid_ID);
    query.bindValue(1,Measurement_ID);
    query.exec();
    if(query.last()){
        do{
            if(query.value(0).toString().compare("MonitoringADC",Qt::CaseInsensitive)==0){
                m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType->insertItem(0,query.value(0).toString());
            }
            else{
                m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType->insertItem(1,query.value(0).toString());
            }
        }while(query.previous());
    }

    int foundindex = 0;
    for(int i=0;i<box->count();i++){
        QString test = box->itemText(i);
        cout << "Current test "<< currentString.toStdString()<< " compared to " << test.toStdString();
        if(test.compare(currentString,Qt::CaseInsensitive)==0){
            foundindex=i;
        }
    }
    m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType->setCurrentIndex(foundindex);
//    m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType->setCurrentIndex(0);
    db.close();
    return foundindex;
}

void DBHandler::plotData(QString measurementType, QString Measurement_ID, QString Hybrid_ID){
    int datlen=getDataLength(measurementType,Measurement_ID,Hybrid_ID);
    db.open();
    QSqlQuery query;
    QString querytype = "SELECT labels FROM " + measurementType.toLower() + " WHERE hybrid_id = ? AND measurement_id = ?";
    query.prepare(querytype);
    query.bindValue(0,Hybrid_ID);
    query.bindValue(1,Measurement_ID);
    query.exec();
    QString labelstr;
    while(query.next()){
        labelstr = query.value(0).toString();
    }
    QStringList strlist = labelstr.split(",");
    QVector<QString> lvec;
    for(int i=0;i<strlist.size();i++){
        QString l = strlist[i].remove('{').remove('}');
        lvec.append(l);
    }
    db.close();
    QVector<double> x;
    QVector<QVector<double>> yvec;
    if(Measurement_ID.isEmpty()==false){
        yvec=loadData(measurementType,Measurement_ID,Hybrid_ID,x,datlen);
    }
    int vecsize = yvec.count();
    QVector<double> y[vecsize];
    for(int i=0; i<vecsize;i++){
        QVector<double> vals = yvec[i];
        y[i]=vals;
    }
    evaluateData(measurementType,x,y,Hybrid_ID);
    if(measurementType.size()>0){
        if(lvec.size()>1){
            QString xlabel = lvec[1].remove("\"");
            QString ylabel = lvec[2].remove("\"");
            QString graphlabel = lvec[3].remove("\"");
            m_mainWindow->m_dbwindow->PlotData(x,y,xlabel,ylabel,measurementType,graphlabel,datlen);
        }
        else{
            m_mainWindow->m_dbwindow->PlotData(x,y,"","","","",datlen);
        }
        if(QString::compare(measurementType,"ADCCalibrationInternal",Qt::CaseInsensitive)==0){
            QVector<double>pars;
            QVector<double> fits [2] = {evaluateADCCalibrationFit(x,y[0],"internal",0,pars),evaluateADCCalibrationFit(x,y[1],"internal",1,pars)};
            m_mainWindow->m_dbwindow->AddFitToPlot(x,fits,"Fit",2,m_mainWindow->m_dbwindow->ui->plot);
        }
        if(QString::compare(measurementType,"ADCCalibrationExternal",Qt::CaseInsensitive)==0){
            QVector<double>pars;
            QVector<double> fits [2] = {evaluateADCCalibrationFit(x,y[0],"external",0,pars),evaluateADCCalibrationFit(x,y[1],"external",1,pars)};
            m_mainWindow->m_dbwindow->AddFitToPlot(x,fits,"Fit",2,m_mainWindow->m_dbwindow->ui->plot);
        }
        if(QString::compare(measurementType,"monitoringadc",Qt::CaseInsensitive)==0){
            QVector<double> fits[2];
            double slope[2];
            double intercept[2];
            QVector<double> xclean;
            QVector<double> yclean[2];
            for(int i=10;i<x.count();i++){
                xclean.push_back(x[i]);
                yclean[0].push_back(y[0][i]);
                yclean[1].push_back(y[1][i]);
            }
            //FitLinear(xclean,yclean[0],slope[0],intercept[0]);
            //FitLinear(xclean,yclean[1],slope[1],intercept[1]);
            FitLinear(x,y[0],slope[0],intercept[0]);
            FitLinear(x,y[1],slope[1],intercept[1]);
            for(int i=0;i<x.count();i++){
                for(int j=0;j<2;j++){
                    double val = slope[j]*x[i]+intercept[j];
                    fits[j].push_back(val);
                }
            }
            m_mainWindow->m_dbwindow->AddFitToPlot(x,fits,"Fit",2,m_mainWindow->m_dbwindow->ui->plot);

        }
    }

}

QVector<QVector<double>> DBHandler::loadData(QString measurementType, QString Measurement_ID, QString Hybrid_ID, QVector<double> &x, int datlen){
    db.open();
    QSqlQuery query;
    QString querytype = "SELECT labels FROM " + measurementType.toLower() + " WHERE hybrid_id = ? AND measurement_id = ?";
    query.prepare(querytype);
    query.bindValue(0,Hybrid_ID);
    query.bindValue(1,Measurement_ID);
    query.exec();
    QString labelstr;
    while(query.next()){
        labelstr = query.value(0).toString();
    }
    QStringList strlist = labelstr.split(",");
    QVector<QString> lvec;
    for(int i=0;i<strlist.size();i++){
        QString l = strlist[i].remove('{').remove('}');
        lvec.append(l);
    }
    QString queryx = "SELECT x_ FROM " + measurementType.toLower() + " WHERE hybrid_id = ? AND measurement_id = ?";
    query.prepare(queryx);
    query.bindValue(0,Hybrid_ID);
    query.bindValue(1,Measurement_ID);
    query.exec();
    while(query.next()){
        QString xstr = query.value(0).toString();
        x = convertStrToVec(xstr);
        //std::cout << query.value(0).toString().toStdString()<< endl;;
    }
    QVector<QVector<double>> yreturn;
    for(int i=0;i< datlen;i++){
        QString queryy1 = "SELECT ";
        queryy1 += "y" + QString::number(i+1) +"_";
        queryy1 += " FROM " + measurementType.toLower() + " WHERE hybrid_id = ? AND measurement_id = ?";
        query.prepare(queryy1);
        query.bindValue(0,Hybrid_ID);
        query.bindValue(1,Measurement_ID);
        query.exec();
        while(query.next()){
            QString ystr = query.value(0).toString();
            QVector<double> yi = convertStrToVec(ystr);
            yreturn.push_back(yi);
            //std::cout << query.value(0).toString().toStdString()<< endl;;
        }

    }
    db.close();
    return yreturn;
}

double DBHandler::getThresholdSetting(int vmm)
{
    db.open();
    QSqlQuery query;
    QString measurement_id = m_mainWindow->m_dbwindow->ui->comboBox_MeasurementID->currentText();
    QString qstr = "SELECT * FROM configs WHERE measurement_id =?;";
    QString end = "vmm";
    end+=QString::number(vmm);
    end+=".txt";
    query.prepare(qstr);
    query.bindValue(0,measurement_id);
    query.exec();
    double ThrDAC = 0;
    if(query.last()){
        if(query.size()<1){
            cout << "No Config files for this measurement found"<<endl;
            ThrDAC=300;
            return ThrDAC;
        }
        do{
            QString filename = query.value(2).toString();
            if(filename.contains(end)==true){
                QString content = query.value(3).toString();
                if(content.contains("sdt")){
                    int ind = content.indexOf("sdt");
                    QString mid = content.mid(ind+3+1,4);
                    ThrDAC = mid.toDouble();
                }
            }
        }while(query.previous());
    }
    db.close();
    return ThrDAC;
}

void DBHandler::evaluateData(QString type, QVector<double> x, QVector<double> y[], QString hybrid_id, int datalen){
    if(QString::compare(type,"pedestal",Qt::CaseInsensitive)==0){
        double qGood[2] = {m_mainWindow->m_dbwindow->ui->pedestal_g_l->text().toDouble(),m_mainWindow->m_dbwindow->ui->pedestal_g_u->text().toDouble()};
        double qOk[2] = {m_mainWindow->m_dbwindow->ui->pedestal_o_l->text().toDouble(),m_mainWindow->m_dbwindow->ui->pedestal_o_u->text().toDouble()};
        std::set<int> outliers[2];
        outliers[0] = findOutliers(y[0],100);
        outliers[1] = findOutliers(y[1],100);
        QVector<double> nooutliers[2];
        for(int i = 0; i<2;i++){
            //pedestals[i]=QVector<double>::fromStdVector(m_calibmod->m_mean[0][m_FEC_test][m_HDMI_test][0][i]);
            int n=0;
            for(int j = 0;j<64; j++){
                double ped = y[i][j];
                if(ped>=qGood[0] && ped<=qGood[1]){
                    MarkChannel("Pedestal",i,j,"good");
                }
                else if(ped>=qOk[0] && ped<=qOk[1]){
                    MarkChannel("Pedestal",i,j,"ok");
                }
                else if(ped<qOk[0] || ped>qOk[1]){
                    MarkChannel("Pedestal",i,j,"bad");
                }
                else{
                    MarkChannel("Pedestal",i,j,"unknown");
                }
            }
        }
        for(int i=0;i<2;i++){
            for(int j=0;j<64;j++){
                if(outliers[i].find(j)==outliers[i].end()){
                        nooutliers[i].push_back(y[i][j]);
                }
            }
        }
        double avg[2] = {getAverage(nooutliers[0]),getAverage(nooutliers[1])};
        double stdds[2] = {getStdDev(nooutliers[0]),getStdDev(nooutliers[1])};


        QLabel* labelvec[2] = {m_mainWindow->m_dbwindow->ui->pedestalstatuslabel1,m_mainWindow->m_dbwindow->ui->pedestalstatuslabel2};
        QString exports[2] = {"",""};
        //Evaluate found Data
        for(int i = 0; i<2;i++){
                labelvec[i]->setWordWrap(true);
                QString labeltext = QString(QString::number(avg[i],'f',1)); //+ " ± " +QString(QString::number(stdds[i],'f',1))+" mV";
                labelvec[i]->setText(labeltext);
                if(avg[i]>qGood[0] && avg[i]<qGood[1]){
                    labelvec[i]->setStyleSheet("background-color: lightgreen");
                    h_VMMResults[i].insert("Pedestal",0);
               }
                else if(avg[i]>qOk[0] && avg[i]<qOk[1] && (avg[i]<qGood[0] || avg[i]>qGood[1])){
                    labelvec[i]->setStyleSheet("background-color: yellow");
                    h_VMMResults[i].insert("Pedestal",1);
                }
                else{
                    labelvec[i]->setStyleSheet("background-color: red");
                    h_VMMResults[i].insert("Pedestal",2);
                }
        }
        return;
    }
    else if(QString::compare(type,"thresholdscan",Qt::CaseInsensitive)==0){
        double avg[2] = {getAverage(y[0]),getAverage(y[1])};
        double stdds[2] = {getStdDev(y[0]),getStdDev(y[1])};
        QLabel* labelvec[2] = {m_mainWindow->m_dbwindow->ui->thresholdstatuslabel1,m_mainWindow->m_dbwindow->ui->thresholdstatuslabel2};
        double slopes[2] = {h_monitoringADCcal[0][0],h_monitoringADCcal[1][0]};
        double intercepts[2] = {h_monitoringADCcal[0][1],h_monitoringADCcal[1][1]};
        double DACsetting[2] = {getThresholdSetting(0),getThresholdSetting(1)};
        double setthreshold[2] = {DACsetting[0]*slopes[0]+intercepts[0],DACsetting[1]*slopes[1]+intercepts[1]};
        //double setthreshold[2] ={260};
        cout << "Expected Thresholds  " << setthreshold[0] << "\t" << setthreshold[1] <<endl;
        double qGood = m_mainWindow->m_dbwindow->ui->threshold_g_l->text().toDouble();
        double qOk = m_mainWindow->m_dbwindow->ui->threshold_o_l->text().toDouble();
        for(int i = 0; i<2;i++){
            double min = *std::min_element(y[i].begin(),y[i].end());
            double max = *std::max_element(y[i].begin(),y[i].end());
            double diff = max-min;
            labelvec[i]->setWordWrap(true);
            QString labeltext = QString::number(diff)+"mV";
            labelvec[i]->setText(labeltext);
            if(diff<=qGood){
                labelvec[i]->setStyleSheet("background-color: lightgreen");
            }
            else if(diff>qGood && diff<=qOk){
                labelvec[i]->setStyleSheet("background-color: yellow");
            }
            else{
                labelvec[i]->setStyleSheet("background-color: red");
            }
        }
        for(int i=0;i<2;i++){
            for(int j=0;j<64;j++){
                if(fabs(y[i][j]-setthreshold[i])<qGood){
                    MarkChannel("Threshold",i,j,"good");
                }
                else if(fabs(y[i][j]-setthreshold[i])<qOk){
                    MarkChannel("Threshold",i,j,"ok");
                }
                else{
                    MarkChannel("Threshold",i,j,"bad");
                }
            }
        }

        return;
    }
    else if(QString::compare(type,"externalpulses",Qt::CaseInsensitive)==0){
        QString test = "External";
        int working[2] = {0,0};
        for(int j=0; j<2; j++){
            for(int i=0; i<64;i++){
                if(y[j][i]<=200){
                    MarkChannel(test,j,i,"bad");
                }
                else if(y[j][i]>9000 && y[j][i]<9200){
                    MarkChannel(test,j,i,"good");
                    working[j]++;
                }
                else if(y[j][i]<9000 && y[j][i]>200){
                    MarkChannel(test,j,i,"ok");
                    working[j]++;
                }
                else{
                    MarkChannel(test,j,i,"ok");
                    working[j]++;
                }
            }
        }
        QLabel* labelvec[2] = {m_mainWindow->m_dbwindow->ui->extchannels1label,m_mainWindow->m_dbwindow->ui->extchannels2label};
        QString exports[2] = {"",""};
        double qGood = m_mainWindow->m_dbwindow->ui->external_g_l->text().toDouble();
        double qOk = m_mainWindow->m_dbwindow->ui->external_o_l->text().toDouble();
        //Classify to good, ok, or bad depending on number of working channels
        for(int i = 0; i<2;i++){
            labelvec[i]->setWordWrap(true);
            QString labeltext = QString::number(working[i]);
            labelvec[i]->setText(labeltext);
            if(working[i]>=qGood){
                labelvec[i]->setStyleSheet("background-color: lightgreen");
            }
            else if(working[i]<qGood && working[i]>=qOk){
                labelvec[i]->setStyleSheet("background-color: yellow");
            }
            else{
                labelvec[i]->setStyleSheet("background-color: red");
            }

        }


    }
    else if(QString::compare(type,"internalpulses",Qt::CaseInsensitive)==0){
        h_nwchannels[0]=64;
        h_nwchannels[1]=64;
        double avg[2] = {getMedian(y[0]),getMedian(y[1])};
        for(int i=0;i<2;i++){
            if(avg[i]<1000){
                double* max = std::max_element(y[i].begin(),y[i].end());
                if(*max<1000){
                    avg[i]=1000;
                }
                else{
                    avg[i]=*max;
                }
            }
        }
        int working[2] = {0,0};
        QString test = "Internal";
        for(int j=0; j<2; j++){
            for(int i=0; i<64;i++){
                if(y[j][i]<=100){
                    MarkChannel(test,j,i,"bad");
                    h_nwchannels[j]--;
                }
                else if(fabs(y[j][i]-avg[j])<1000){
                    MarkChannel(test,j,i,"good");
                    working[j]++;
                }
                else{
                    MarkChannel(test,j,i,"unknown");

                }
            }
        }
        QLabel* labelvec[2] = {m_mainWindow->m_dbwindow->ui->intchannels1label,m_mainWindow->m_dbwindow->ui->intchannels2label};
        QString exports[2] = {"",""};
        double qGood = m_mainWindow->m_dbwindow->ui->internal_g_l->text().toDouble();
        double qOk = m_mainWindow->m_dbwindow->ui->internal_o_l->text().toDouble();
        //Classify to good, ok, or bad depending on number of working channels
        for(int i = 0; i<2;i++){
            labelvec[i]->setWordWrap(true);
            QString labeltext = QString::number(working[i]);
            labelvec[i]->setText(labeltext);
            if(working[i]>=qGood){
                labelvec[i]->setStyleSheet("background-color: lightgreen");
            }
            else if(working[i]<qGood && working[i]>=qOk){
                labelvec[i]->setStyleSheet("background-color: yellow");
            }
            else{
                labelvec[i]->setStyleSheet("background-color: red");
            }
        }

    }
    else if(QString::compare(type,"adccalibrationinternal",Qt::CaseInsensitive)==0){
        double adcdiff[2] = {evaluateADCCalibration(y[0],"Internal"),evaluateADCCalibration(y[1],"Internal")};
        QVector<double> popt;
        evaluateADCCalibrationFit(x,y[1],"Internal",1,popt);
        evaluateADCCalibrationFit(x,y[0],"Internal",0,popt);
        double qGood2 = m_mainWindow->m_dbwindow->ui->adcrange_g_l->text().toDouble()*5/7.;
        double qOk2 = m_mainWindow->m_dbwindow->ui->adcrange_o_l->text().toDouble()*5/7.;
        QLabel* labels[2] = {m_mainWindow->m_dbwindow->ui->adccurvestatus1label, m_mainWindow->m_dbwindow->ui->adccurvestatus2label};
        for(int i=0;i<2;i++){
            if(adcdiff[i]<0.000000000000001){
                adcdiff[i] = 4095;
            }
            QString labeltext = QString::number(adcdiff[i])+"mV";
            if(adcdiff[i]<=qGood2){
                //labels[i]->setStyleSheet("background-color: lightgreen");
                h_VMMResults[i].insert("ADCCurveInt",0);
            }
            else if(adcdiff[i]>qGood2 && adcdiff[i]<=qOk2){
                //labels[i]->setStyleSheet("background-color: yellow");
                h_VMMResults[i].insert("ADCCurveInt",1);
            }
            else{
                //labels[i]->setStyleSheet("background-color: red");
                h_VMMResults[i].insert("ADCCurveInt",2);
            }
            //labels[i]->setText(labeltext);
            for(int j=0;j<64;j++){
                if(y[i][j]==0){
                    //MarkChannel("ADCCalibrationinternal",i,j,"bad");
                }
                else{
                    //MarkChannel("ADCCalibrationinternal",i,j,"good");
                }
            }
        }
    }
    else if(QString::compare(type,"tdccalibrationinternal",Qt::CaseInsensitive)==0){
        double qGood3[2] = {m_mainWindow->m_dbwindow->ui->tdc_g_l->text().toDouble(),m_mainWindow->m_dbwindow->ui->tdc_g_u->text().toDouble()};
        double qOk3[2] = {m_mainWindow->m_dbwindow->ui->tdc_o_l->text().toDouble(),m_mainWindow->m_dbwindow->ui->tdc_o_u->text().toDouble()};
        double avgavgtdc[2] = {getAverage(y[0]),getAverage(y[1])};
        QLabel* labels2[2] = {m_mainWindow->m_dbwindow->ui->tdcstatuslabel1, m_mainWindow->m_dbwindow->ui->tdcstatuslabel2};
        for(int i=0;i<2;i++){
            QString labeltext = QString::number(avgavgtdc[i])+"mV";
            for(int j=0; j<64;j++){
                if(y[i][j]>qGood3[0]&&y[i][j]<qGood3[1]){
                    MarkChannel("TDCCalibrationInternal",i,j,"good");
                }
                else if(y[i][j]>qOk3[0]&&y[i][j]<qOk3[1]){
                    MarkChannel("TDCCalibrationInternal",i,j,"ok");
                }
                else{
                    MarkChannel("TDCCalibrationInternal",i,j,"bad");
                }
            }

            if(avgavgtdc[i]>=qGood3[0]&&avgavgtdc[i]<=qGood3[1]){
                labels2[i]->setStyleSheet("background-color: lightgreen");
                h_VMMResults[i].insert("avgTDC",0);
            }
            else if(avgavgtdc[i]>=qOk3[0]&&avgavgtdc[i]<=qOk3[1]){
                labels2[i]->setStyleSheet("background-color: yellow");
                h_VMMResults[i].insert("avgTDC",1);
            }
            else{
                labels2[i]->setStyleSheet("background-color: red");
                h_VMMResults[i].insert("avgTDC",2);
            }
            labels2[i]->setText(QString::number(avgavgtdc[i]));
        }

    }
    else if(QString::compare(type,"adccalibrationexternal",Qt::CaseInsensitive)==0){
        double adcdiff[2] = {evaluateADCCalibration(y[0],"External"),evaluateADCCalibration(y[1],"External")};
        QVector<double> popt;
        evaluateADCCalibrationFit(x,y[1],"External",1,popt);
        evaluateADCCalibrationFit(x,y[0],"External",0,popt);
        double qGood2 = m_mainWindow->m_dbwindow->ui->adcrange_g_l->text().toDouble();
        double qOk2 = m_mainWindow->m_dbwindow->ui->adcrange_o_l->text().toDouble();
        QLabel* labels[2] = {m_mainWindow->m_dbwindow->ui->adccurvestatus3label, m_mainWindow->m_dbwindow->ui->adccurvestatus4label};
        for(int i=0;i<2;i++){
            if(adcdiff[i]<0.000000000000001){
                adcdiff[i] = 4095;
            }
            QString labeltext = QString::number(adcdiff[i])+"mV";
            if(adcdiff[i]<=qGood2){
                //labels[i]->setStyleSheet("background-color: lightgreen");
                h_VMMResults[i].insert("ADCCurveExt",0);
            }
            else if(adcdiff[i]>qGood2 && adcdiff[i]<=qOk2){
                //labels[i]->setStyleSheet("background-color: yellow");
                h_VMMResults[i].insert("ADCCurveExt",1);
            }
            else{
                //labels[i]->setStyleSheet("background-color: red");
                h_VMMResults[i].insert("ADCCurveExt",2);
            }
            //labels[i]->setText(labeltext);
            for(int j=0;j<64;j++){
                if(y[i][j]==0){
                    MarkChannel("ADCCalibrationexternal",i,j,"bad");
                }
                else{
                    MarkChannel("ADCCalibrationexternal",i,j,"good");
                }
            }
        }
    }
    else if(QString::compare(type,"baselinenoise",Qt::CaseInsensitive)==0){
        double qGoodD = m_mainWindow->m_dbwindow->ui->noise_g_l->text().toDouble();
        double qOkD = m_mainWindow->m_dbwindow->ui->noise_o_l->text().toDouble();
        for(int i=0; i<2;i++){
            for(int j=0; j<64;j++){
                if(y[i][j]<=qGoodD){
                    MarkChannel("Baseline Noise",i,j,"good");
                }
                else if(y[i][j]>qGoodD && y[i][j]<=qOkD){
                    MarkChannel("Baseline Noise",i,j,"ok");
                }
                else{
                    MarkChannel("Baseline Noise",i,j,"bad");
                }
            }
        }
        double avgnoise[2] = {getAverage(y[0]),getAverage(y[1])};
        double noisestd[2] = {getStdDev(y[0]),getStdDev(y[1])};
        QLabel* labelvec2[2] = {m_mainWindow->m_dbwindow->ui->noisestatus1label,m_mainWindow->m_dbwindow->ui->noisestatus2label};
        QString exports2[2] = {"",""};
        for(int i = 0; i<2;i++){
            labelvec2[i]->setWordWrap(true);
            QString labeltext = QString(QString::number(avgnoise[i],'f',3)); //+ " ± " +QString(QString::number(stdds[i],'f',1))+" mV";
            labelvec2[i]->setText(labeltext);
            if(avgnoise[i]<=qGoodD){
                labelvec2[i]->setStyleSheet("background-color: lightgreen");
                h_VMMResults[i].insert("Baseline Noise",0);
           }
            else if(avgnoise[i]>qGoodD&& avgnoise[i]<=qOkD){
                labelvec2[i]->setStyleSheet("background-color: yellow");
                h_VMMResults[i].insert("Baseline Noise",1);
            }
            else{
                labelvec2[i]->setStyleSheet("background-color: red");
                h_VMMResults[i].insert("Baseline Noise",2);
            }
            exports2[i] += labeltext;
        }
    }
    else if(QString::compare(type,"monitoringadc",Qt::CaseInsensitive)==0){
        double slopeapprox[2];
        double intercept[2];

        for(int i=0;i<2;i++){
            FitLinear(x,y[i],slopeapprox[i],intercept[i]);
        }

        /*
           Define in following loop (in if clause) Criteria if ADC is okay or not.
           For now just check the slope.
                                                                                     */
        h_monitoringADCcal[0][0]=slopeapprox[0];
        h_monitoringADCcal[1][0]=slopeapprox[1];
        h_monitoringADCcal[0][1]=intercept[0];
        h_monitoringADCcal[1][1]=intercept[1];

        QLabel* labelvec[2] = {m_mainWindow->m_dbwindow->ui->adcstatuslabel1,m_mainWindow->m_dbwindow->ui->adcstatuslabel2};
        double qGoodSlopes[2] = {m_mainWindow->m_dbwindow->ui->monitoringADC_g_l->text().toDouble(),m_mainWindow->m_dbwindow->ui->monitoringADC_g_u->text().toDouble()};
        double qOkSlopes[2] = {m_mainWindow->m_dbwindow->ui->monitoringADC_o_l->text().toDouble(),m_mainWindow->m_dbwindow->ui->monitoringADC_o_u->text().toDouble()};
        double qGoodIntercept[2] = {m_mainWindow->m_dbwindow->ui->monitoringADC_g_l_2->text().toDouble(),m_mainWindow->m_dbwindow->ui->monitoringADC_g_u_2->text().toDouble()};
        double qOkIntercept[2] = {m_mainWindow->m_dbwindow->ui->monitoringADC_o_l_2->text().toDouble(),m_mainWindow->m_dbwindow->ui->monitoringADC_o_u_2->text().toDouble()};
        for(int i=0;i<2;i++){
            if(slopeapprox[i]>=qGoodSlopes[0] && slopeapprox[i]<= qGoodSlopes[1] && intercept[i]>=qGoodIntercept[0] &&intercept[i]<=qGoodIntercept[1]){
                labelvec[i]->setText("Monitoring ADC functional");
                labelvec[i]->setStyleSheet("background-color: lightgreen");
                //h_monitoringADC[i]=true;
                h_VMMResults[i].insert("MonitoringADC",0);
            }
            else if(((slopeapprox[i]<qGoodSlopes[0] || slopeapprox[i]>qGoodSlopes[1] || intercept[i]<qGoodIntercept[0] || intercept[i]>qGoodIntercept[1])) &&
                     slopeapprox[i]>=qOkSlopes[0] && slopeapprox[i]<= qOkSlopes[1] && intercept[i]>=qOkIntercept[0] && intercept[i]<=qOkIntercept[1]){
                labelvec[i]->setText("Monitoring ADC OK");
                labelvec[i]->setStyleSheet("background-color: yellow");
                //h_monitoringADC[i]=true;
                h_VMMResults[i].insert("MonitoringADC",1);
            }
            else{
                labelvec[i]->setText("Monitoring ADC bad");
                labelvec[i]->setStyleSheet("background-color: red");
                //h_monitoringADC[i]=false;
                h_VMMResults[i].insert("MonitoringADC",2);
            }
        }
    }
    else if(QString::compare(type,"ThresholdTrimabilityVMM0",Qt::CaseInsensitive)==0){
    double thresholdrange [2] = {m_mainWindow->m_dbwindow->ui->thresholdstatuslabel1->text().remove("mV").toDouble(),m_mainWindow->m_dbwindow->ui->thresholdstatuslabel2->text().remove("mV").toDouble()};
        for(int i=0;i<64;i++){
            bool bad = false;
            double minval = *std::min_element(y[i].begin(),y[i].end());
            double maxval = *std::max_element(y[i].begin(),y[i].end());
            double range = maxval-minval;
            for(int h=1;h<y[i].size();h++){
                if(y[i][h]>y[i][h-1]){
                    bad = true;
                }
            }
            double required = thresholdrange[0];
            if(range<required){
                bad = true;
            }
            if(bad==true){
                MarkChannel("Threshold Trimability",0,i,"bad");
            }
            else{
                MarkChannel("Threshold Trimability",0,i,"good");
            }
        }
    }
    else if(QString::compare(type,"ThresholdTrimabilityVMM1",Qt::CaseInsensitive)==0){
    double thresholdrange [2] = {m_mainWindow->m_dbwindow->ui->thresholdstatuslabel1->text().remove("mV").toDouble(),m_mainWindow->m_dbwindow->ui->thresholdstatuslabel2->text().remove("mV").toDouble()};
        for(int i=0;i<64;i++){
            bool bad = false;
            double minval = *std::min_element(y[i].begin(),y[i].end());
            double maxval = *std::max_element(y[i].begin(),y[i].end());
            double range = maxval-minval;
            for(int h=1;h<y[i].size();h++){
                if(y[i][h]>y[i][h-1]){
                    bad = true;
                }
            }
            double required = thresholdrange[1];
            if(range<required){
                bad = true;
            }
            if(bad==true){
                MarkChannel("Threshold Trimability",1,i,"bad");
            }
            else{
                MarkChannel("Threshold Trimability",1,i,"good");
            }
        }
    }
    else if(QString::compare(type,"currentovertime",Qt::CaseInsensitive)==0){
        getMedian(y[0]);
        getMedian(y[1]);
    }
    else if (QString::compare(type,"neighbouring",Qt::CaseInsensitive)==0){
        int norm = 384;
        for(int i=0;i<2;i++){
            for(int j=0;j<64;j++){
                if(j!=0 && j!=63){
                    double ch = y[i][j];
                    double rneigh = y[i][j+1];
                    double lneigh = y[i][j-1];
                    if(ch < norm){
                        if(lneigh<norm){
                            if(rneigh<norm){
                                MarkChannel("Neighbor",i,j,"bad");
                            }
                        }
                    }
                    else{
                        MarkChannel("Neighbor",i,j,"good");
                    }
                }
                else if(j==0){
                    if(i==0){
                        double ch = y[i][j];
                        double rneigh = y[i][j+1];
                        if(rneigh<norm){
                            if(ch<=norm*1/3.){
                                MarkChannel("Neighbor",i,j,"bad");
                            }
                        }
                        else{
                            MarkChannel("Neighbor",i,j,"good");
                        }
                    }
                    if(i==1){
                        double ch = y[i][j];
                        double rneigh = y[i][j+1];
                        double lneigh = y[0][63];
                        if(ch<norm){
                            if(lneigh<norm){
                                if(rneigh<norm){
                                    MarkChannel("Neighbor",i,j,"bad");
                                }
                            }
                        }
                        else{
                            MarkChannel("Neighbor",i,j,"good");
                        }
                    }
                }
                else if(j==63){
                    if(i==1){
                        double ch = y[i][j];
                        double lneigh = y[i][j-1];
                        if(lneigh<norm){
                            if(ch<=norm*1/3.){
                                MarkChannel("Neighbor",i,j,"bad");
                            }
                        }
                        else{
                            MarkChannel("Neighbor",i,j,"good");
                        }
                    }
                    if(i==0){
                        double ch = y[i][j];
                        double rneigh = y[1][0];
                        double lneigh = y[i][j-1];
                        if(ch<norm){
                            if(lneigh<norm){
                                if(rneigh<norm){
                                    MarkChannel("Neighbor",i,j,"bad");
                                }
                            }
                        }
                        else{
                            MarkChannel("Neighbor",i,j,"good");
                        }
                    }
                }
            }
        }

    }
}

double DBHandler::evaluateADCCalibration(QVector<double> dataset, QString caller)
{
    int size=dataset.size();
    double high = 1000;
    if(QString::compare(caller,"internal",Qt::CaseInsensitive)==0){
        high = 375;
    }
    else if(QString::compare(caller,"external",Qt::CaseInsensitive)==0){
        high = 550;
    }
    double avgmid = 0;
    double avgside = 0;
    int mid = size/2 -1;
    int n_s=0;
    int n_m = 0;
    int i=0;
    while(n_s<=10&& i<31){
        if(dataset[i]!=0 && dataset[i]<high){
            n_s++;
            avgside += dataset[i];
        }
        if(dataset[size-i-1]!=0 && dataset[size-i-1]<high){
            n_s++;
            avgside += dataset[size-i-1];
        }
        i++;
    }
    i=1;
    if(dataset[mid]!=0 && dataset[mid]<high){
        avgmid += dataset[mid];
        n_m++;
    }
    while(n_m<=10 && i<31){
        if(dataset[mid+i]!=0 && dataset[mid+i]<high){
            n_m++;
            avgmid+= dataset[mid+i];
            }
        if(dataset[mid-i]!=0 && dataset[mid-i]<high){
            n_m++;
            avgmid += dataset[mid-i];
            }
        i++;
        }
    if(n_m==0){n_m=1;}
    if(n_s==0){n_s=1;}
    avgmid/=n_m;
    avgside/=n_s;
    double diff = avgmid-avgside;
    return diff;
}

QVector<double> DBHandler::evaluateADCCalibrationFit(QVector<double> datax, QVector<double> datay, QString caller, int chip, QVector<double> &params)
{
    //remove Datapoints with y=0 to not mess up to fit
    QString chanmarkstring = "ADCCalibration"+caller;
    QVector<double> xclean;
    QVector<double> yclean;
    double curveideal;
    double curvestd;
    double centerideal;
    double centerstd;
    double maxheightideal;
    double maxheightstd;
    double posrangeup;
    double posrangelow;
    QString resultinsert1;
    QString resultinsert2;
    QLabel* labels[6];
    bool failedMeasurement =false;
    double good_dev = m_mainWindow->m_dbwindow->ui->adcrange_g_l->text().toDouble();
    double ok_dev = m_mainWindow->m_dbwindow->ui->adcrange_o_l->text().toDouble();
    if(QString::compare(caller,"Internal",Qt::CaseInsensitive)==0){
        getCurveSettings("Internal",curveideal,curvestd);
/*
        curveideal = -0.0604396074478;
        curvestd = 0.00896593791387;*/
        centerideal = 31.3400625589;
        centerstd = 1.55508392126;

        cout << "Settings"<< curveideal <<"," << curvestd <<","<< centerideal<<","<<centerstd<<endl;
        maxheightideal = 313.702862948;
        maxheightstd = 16.2023985974;
        resultinsert1 = "adcintcurvature";
        resultinsert2 = "adcintvertex";
        labels[0]=m_mainWindow->m_dbwindow->ui->adccurvestatus1label;
        labels[1]=m_mainWindow->m_dbwindow->ui->adccurvestatus2label;
        labels[2]=m_mainWindow->m_dbwindow->ui->adcvertexstatus1label;
        labels[3]=m_mainWindow->m_dbwindow->ui->adcvertexstatus2label;
        labels[4]=m_mainWindow->m_dbwindow->ui->adccal_bads1;
        labels[5]=m_mainWindow->m_dbwindow->ui->adccal_bads2;
        posrangelow = m_mainWindow->m_dbwindow->ui->adcvertex_g_i->text().toDouble();;
        posrangeup = m_mainWindow->m_dbwindow->ui->adcvertex_o_i->text().toDouble();
    }
    else if(QString::compare(caller,"External",Qt::CaseInsensitive)==0){
        getCurveSettings("External",curveideal,curvestd);
/*
        curveideal = -0.070142162122;
        curvestd = 0.00628598041229;*/
        centerideal = 31.6371319652;
        centerstd = 2.17699310923;

        cout << "Settings"<<curveideal <<"," << curvestd <<","<< centerideal<<","<<centerstd<<endl;
        maxheightideal = 426.371640739;
        maxheightstd = 18.5010979906;
        resultinsert1 = "adcextcurvature";
        resultinsert2 = "adcextvertex";
        labels[0]=m_mainWindow->m_dbwindow->ui->adccurvestatus3label;
        labels[1]=m_mainWindow->m_dbwindow->ui->adccurvestatus4label;
        labels[2]=m_mainWindow->m_dbwindow->ui->adcvertexstatus3label;
        labels[3]=m_mainWindow->m_dbwindow->ui->adcvertexstatus4label;
        labels[4]=m_mainWindow->m_dbwindow->ui->adccal_bads1;
        labels[5]=m_mainWindow->m_dbwindow->ui->adccal_bads2;
        posrangelow = m_mainWindow->m_dbwindow->ui->adcvertex_g_e->text().toDouble();
        posrangeup = m_mainWindow->m_dbwindow->ui->adcvertex_o_e->text().toDouble();
    }

    for(int i=0;i<datax.size();i++){
        if(datay[i]!=0 && datay[i]<800){
            xclean.push_back(datax[i]);
            yclean.push_back(datay[i]);
        }
    }
    if(xclean.size()==0){
        for(int i=0;i<datax.size();i++){
            xclean.push_back(datax[i]);
            yclean.push_back(datay[i]);
        }
        failedMeasurement=true;
    }
    const int order = 2;
    std::vector<double> results;
    PolynomialRegression<double> *fitter = new PolynomialRegression<double>();
    fitter->fitIt(xclean.toStdVector(),yclean.toStdVector(),order,results);
    for(int i=0;i<results.size();i++){
        //cout << results[i]<<endl;
        params.push_back(results[i]);
    }
    QVector<double> yexpected;
    int size = datax.size();
    QVector<double> ploty [2];
    double peakpos = results[1]/(-2*results[2]);
    double curvature = results[2];
    double peakheight = results[0]-pow(results[1],2)/(4*results[2]);
    if(failedMeasurement){
        peakpos =0;
        curvature = 0;
        peakheight = 0;
    }
    cout << curvature <<"," << peakpos <<"," << peakheight <<endl;
    bool markedcurve = false;
    bool markedpos = false;
    if(fabs(curvature)>=fabs(curveideal)){
        if(fabs(curvature-curveideal)>=5*curvestd){
            h_VMMResults[chip].insert(resultinsert1,2);
            labels[chip]->setStyleSheet("background-color: red");
            markedcurve =true;
        }
    }
    else{
        if(fabs(curvature-curveideal)>=5*curvestd){
            h_VMMResults[chip].insert(resultinsert1,2);
            labels[chip]->setStyleSheet("background-color: red");
            markedcurve =true;
        }
    }
    if(!(peakpos>=posrangelow&&peakpos<=posrangeup)){
        h_VMMResults[chip].insert(resultinsert2,2);
        labels[chip+2]->setStyleSheet("background-color: red");
        markedpos =true;
    }
    if(fabs(peakheight-maxheightideal)>3*maxheightstd){
        h_VMMResults[chip].insert(resultinsert2,2);
        labels[chip+2]->setStyleSheet("background-color: red");
        markedpos =true;
    }
    if(markedcurve == false && markedpos==false ){
        yexpected.clear();
        for(int i=0;i<datax.size();i++){
            double x = datax[i];
            double yexp = results[2]*pow(x,2)+results[1]*x+results[0];
            yexpected.push_back(yexp);
        }
    }
    else if(markedcurve == true || markedpos==true){
        yexpected.clear();
        for(int i=0;i<datax.size();i++){
            double x = datax[i];
            double yexp = curveideal*pow((x-centerideal),2)+maxheightideal;
            yexpected.push_back(yexp);
        }
    }
    if(markedcurve == false){
        labels[chip]->setStyleSheet("background-color: lightgreen");
    }
    if(markedpos == false){
        labels[chip+2]->setStyleSheet("background-color: lightgreen");
    }
    labels[chip]->setText(QString::number(curvature,'g',4)+"mV/Ch²");
    labels[chip+2]->setText("(Ch"+QString::number(peakpos,'g',3)+","+QString::number(peakheight,'g',4)+"mV)");
    double diffs = yexpected[size/2-1]-((yexpected[0]+yexpected[size-1])/2);
    cout <<diffs<<endl;
    ploty[0]=datay;
    ploty[1]=yexpected;
    QString badchans = "";
    int n_bad =0;
    for(int i=0;i<64;i++){
        if(datay[i]==0){
            MarkChannel(chanmarkstring,chip,i,"bad");
            badchans += QString::number(i)+", ";
            n_bad++;
        }
        else if(fabs(datay[i]-yexpected[i])<good_dev){
            MarkChannel(chanmarkstring,chip,i,"good");
        }
        else if(fabs(datay[i]-yexpected[i])<ok_dev){
            MarkChannel(chanmarkstring,chip,i,"ok");
        }
        else{
            MarkChannel(chanmarkstring,chip,i,"bad");
            badchans += QString::number(i)+", ";
            n_bad++;
        }
    }
    badchans.chop(2);
    labels[chip+4]->setText(badchans);
    labels[chip+4]->setToolTip(badchans);
    if(n_bad>0){
        labels[chip+4]->setStyleSheet("background-color: red");
    }
    else{
        labels[chip+4]->setStyleSheet("background-color: lightgreen");
    }
    //m_mainWindow->m_dbwindow->PlotData(datax,ploty,"Channel","ADC","ADC Fit","",2);
    //return diffs;
    return ploty[1];
}

void DBHandler::evaluateResults(){
    QVector<QLabel*> labels1;
    QGridLayout* grids [2] = {m_mainWindow->m_dbwindow->ui->ChannelsVMM0_grid,m_mainWindow->m_dbwindow->ui->ChannelsVMM1_grid};
    QLabel* vmmlabels[2] = {m_mainWindow->m_dbwindow->ui->vmm1label,m_mainWindow->m_dbwindow->ui->vmm2label};
    QString vmmstati[2] ={"",""};
    QString hybridclass = "";
    for(int j=0;j<2;j++){
        int n_perfect =0;
        int n_ok =0;
        for(int i=0; i<64;i++){
            QLabel* label = new QLabel();
            QHash<QString,int> channelinfo = h_ChannelResults[j][i];
            QList<QString> keys = channelinfo.keys();
            double total =0;
            int ntests =0;
            QString tTip = "<font color=\"#000000\">Channel " +QString::number(i);
            bool fixable = false;
            if(channelinfo.value("External")==2){
                //if External test says channel is broken check if also internally broken!
                if(channelinfo.value("Internal")==2){
                    //Also internally broken
                    if(channelinfo.value("Pedestal")==2){
                        //baseline too high
                    }
                    else{
                        //unknown reason
                    }
                }
                else{
                    //Channel not connected to detector (fixable)
                    fixable==true;
                }
            }
            QStringList badtests;
            QStringList oktests;
            for(int h =0; h< keys.size();h++){
                total += channelinfo.value(keys[h]);
                if(channelinfo.value(keys[h])!=0){
                    tTip += ", " + QString(keys[h]);
                }
                if(channelinfo.value(keys[h])==1){
                    oktests << keys[h];
                }
                if(channelinfo.value(keys[h])==2){
                    badtests << keys[h];
                }
                ntests++;
            }

            QList<int> values = channelinfo.values();
            int ngood = values.count(0);
            int nok = values.count(1);
            int nbad = values.count(2);
            int unknown = values.count(3);
            QString color = "";
            if(nbad>=1){
                bool crit = false;
                foreach(const QString &str,badtests){
                    if(m_criticaltests.contains(str)){
                        crit=true;
                    }
                }
                if(crit==true){
                    color = "background-color: #ff0000";
                }
                else{
                    color = "background-color: rgb(255,255,0)";
                    n_ok++;
                }
                label->setStyleSheet(color);
            }

            else if(nok>=1 && nbad==0){
                int ntotal = nok;
                double avg = ntotal/ntests;
                color = "background-color: #ff";
                int colval=255*(1-avg);
                QString add = QString::number(colval,16);
                if(add.size()%2!=0){
                    add = "0"+add;
                }
                color += add;
                color += "00";
                label->setStyleSheet(color);
                n_ok++;
            }
            else if(nbad==0 && nok==0){
                color = "background-color: #00ff00";
                label->setStyleSheet(color);
                n_perfect++;
            }
            else{
                color = "background-color: #0000ff";
            }
            label->setStyleSheet(color);

            label->setText(QString::number(total));
            label->setToolTip(tTip);
            label->setAlignment(Qt::AlignCenter);
            labels1.push_back(label);
            grids[j]->addWidget(label,i/16,i%16);
        }
        QHash<QString,int> vmmresults = h_VMMResults[j];
        QList<QString> keys2 = vmmresults.keys();
        int ntestsmade=0;
        int total2 =0;
        for(int h =0; h< keys2.size();h++){
            total2 += vmmresults.value(keys2[h]);
            ntestsmade++;
        }
        double avgresult = total2/ntestsmade;
        if(keys2.contains("MonitoringADC")==true){
            if(h_VMMResults[j].value("MonitoringADC")==2){
            vmmstati[j] = "Bad";
            vmmlabels[j]->setStyleSheet("background-color: red");
            vmmlabels[j]->setText("VMM"+QString::number(j)+": E");
            }
            else if(h_VMMResults[j].value("MonitoringADC")<2){
                if (n_perfect+n_ok>=m_mainWindow->m_dbwindow->ui->external_g_l->text().toDouble()){
                    vmmstati[j] = "A";
                    vmmlabels[j]->setStyleSheet("background-color: lightgreen");
                    vmmlabels[j]->setText("VMM"+QString::number(j)+": A");
                }
                else if(n_perfect+n_ok >=m_mainWindow->m_dbwindow->ui->external_g_l->text().toDouble()-1){
                    vmmstati[j] = "B";
                    vmmlabels[j]->setStyleSheet("background-color: rgb(255,133,255)");
                    vmmlabels[j]->setText("VMM"+QString::number(j)+": B");
                }
                else if(n_perfect+n_ok>=m_mainWindow->m_dbwindow->ui->external_o_l->text().toDouble()){
                    vmmstati[j] = "C";
                    vmmlabels[j]->setStyleSheet("background-color: yellow");
                    vmmlabels[j]->setText("VMM"+QString::number(j)+": C");
                }
                else if(n_perfect+n_ok>1){
                    vmmstati[j] = "D";
                    vmmlabels[j]->setStyleSheet("background-color: orange");
                    vmmlabels[j]->setText("VMM"+QString::number(j)+": D");
                }
                else{
                    vmmstati[j] = "E";
                    vmmlabels[j]->setStyleSheet("background-color: red");
                    vmmlabels[j]->setText("VMM"+QString::number(j)+": E");
                }
            }
        }
        else{
            if (n_perfect+n_ok>=m_mainWindow->m_dbwindow->ui->external_g_l->text().toDouble()){
                vmmstati[j] = "A";
                vmmlabels[j]->setStyleSheet("background-color: lightgreen");
                vmmlabels[j]->setText("VMM"+QString::number(j)+": A");
            }
            else if(n_perfect+n_ok >=m_mainWindow->m_dbwindow->ui->external_g_l->text().toDouble()-1){
                vmmstati[j] = "B";
                vmmlabels[j]->setStyleSheet("background-color: rgb(255,133,255)");
                vmmlabels[j]->setText("VMM"+QString::number(j)+": B");
            }
            else if(n_perfect+n_ok>=m_mainWindow->m_dbwindow->ui->external_o_l->text().toDouble()){
                vmmstati[j] = "C";
                vmmlabels[j]->setStyleSheet("background-color: yellow");
                vmmlabels[j]->setText("VMM"+QString::number(j)+": C");
            }
            else if(n_perfect+n_ok>1){
                vmmstati[j] = "D";
                vmmlabels[j]->setStyleSheet("background-color: orange");
                vmmlabels[j]->setText("VMM"+QString::number(j)+": D");
            }
            else{
                vmmstati[j] = "E";
                vmmlabels[j]->setStyleSheet("background-color: red");
                vmmlabels[j]->setText("VMM"+QString::number(j)+": E");
            }
        }
    }
    if(vmmstati[0]=="A"){
        if(vmmstati[1]=="A"){
            hybridclass="a";
        }
        else if(vmmstati[1] == "B"||vmmstati[1] == "C"){
            hybridclass = "b";
        }
        else if(vmmstati[1] == "D" || vmmstati[1] == "E"){
            hybridclass = "c";
        }
    }
    else if(vmmstati[0]=="B"){
        if(vmmstati[1]=="A"){
            hybridclass="b";
        }
        else if(vmmstati[1] == "B"){
            hybridclass = "b";
        }
        else if(vmmstati[1] == "C"){
            int ntot = h_nwchannels[0] + h_nwchannels[1];
            if(ntot >=125){
                hybridclass = "b";
            }
            else{
                hybridclass = "c";
            }
        }
        else if(vmmstati[1] == "D" || vmmstati[1] == "E"){
            hybridclass = "c";
        }
    }
    else if(vmmstati[0]=="C"){
        if(vmmstati[1]=="A"){
            hybridclass="b";
        }
        else if(vmmstati[1] == "B" || vmmstati[1]=="C"){
            int ntot = h_nwchannels[0] + h_nwchannels[1];
            if(ntot >=125){
                hybridclass = "b";
            }
            else{
                hybridclass = "c";
            }
        }
        else if(vmmstati[1] == "D" || vmmstati[1] == "E"){
            hybridclass = "c";
        }
    }
    else if(vmmstati[0]=="D"){
        hybridclass = "c";
    }
    else if(vmmstati[0]=="E"){
        if(vmmstati[1]=="A"|| vmmstati[1] == "B" || vmmstati[1] == "C"|| vmmstati[1] == "D"){
            hybridclass = "c";
        }
        if(vmmstati[1]=="E"){
            hybridclass = "d";
        }
        else{
            hybridclass = "c";
        }
    }
    else{
        hybridclass = "unknown";
    }

    m_mainWindow->m_dbwindow->ui->hybrid_classlabel->setText(hybridclass);
    if(hybridclass=="a"){
        m_mainWindow->m_dbwindow->ui->hybrid_classlabel->setStyleSheet("background-color: lightgreen");
    }
    else if(hybridclass=="b"){
        m_mainWindow->m_dbwindow->ui->hybrid_classlabel->setStyleSheet("background-color: yellow");
    }
    else if(hybridclass=="c"){
        m_mainWindow->m_dbwindow->ui->hybrid_classlabel->setStyleSheet("background-color: red");
    }
    else if(hybridclass=="d"){
        m_mainWindow->m_dbwindow->ui->hybrid_classlabel->setStyleSheet("background-color: black");
        m_mainWindow->m_dbwindow->ui->hybrid_classlabel->setStyleSheet("color: white");
    }
}

double DBHandler::getDataLength(QString measurementType, QString Measurement_ID, QString Hybrid_ID)
{
    db.open();
    QSqlQuery query;
    QString querytype = "SELECT labels FROM " + measurementType.toLower() + " WHERE hybrid_id = ? AND measurement_id = ?";
    query.prepare(querytype);
    query.bindValue(0,Hybrid_ID);
    query.bindValue(1,Measurement_ID);
    query.exec();
    QString labelstr;
    while(query.next()){
        labelstr = query.value(0).toString();
    }
    QStringList strlist = labelstr.split(",");
    QVector<QString> lvec;
    for(int i=0;i<strlist.size();i++){
        QString l = strlist[i].remove('{').remove('}');
        lvec.append(l);
    }
    db.close();
    int datlen =0;
    if(lvec.size()>0){
        QString type = lvec[0];
        if(type=="channels"){
            datlen=64;
        }
        else{
            datlen = 2;
        }
    }
    else{
        datlen=2;
    }
    return datlen;
}

std::set<int> DBHandler::findOutliers(QVector<double> input, double thr)
{
    std::set<int> indices;
    indices.clear();
    std::vector<double> copy;
    for(int i=0;i<input.size();i++){
        double inp = input[i];
        copy.push_back(inp);
    }
    std::sort(copy.begin(),copy.end());
    double median=0;
    int copsize = copy.size();
    if(copsize%2==0){
        median = (copy[copy.size()/2]+copy[copy.size()/2-1])/2;
    }
    else{
        median = copy[copy.size()/2];
    }
    int chno = 0;
    for(int i=0; i< input.size();i++){
        double val = input[i];
        if(fabs(val-median)>thr){
            indices.insert(chno);
        }
        chno++;
    }
    return indices;
}

void DBHandler::FitLinear(QVector<double> x, QVector<double> y, double &slope, double &intercept)
{
    double xavg = getAverage(x);
    double yavg = getAverage(y);
    double xysum=0;
    double xxsum=0;
    for(int i=0;i<x.size();i++){
        xysum += (x[i]-xavg)*(y[i]-yavg);
        xxsum += pow((x[i]-xavg),2);
    }
    slope = xysum/xxsum;
    intercept = yavg - slope*xavg;
}

void DBHandler::ListNormCurves()
{
    db.open();
    m_mainWindow->m_dbwindow->ui->comboBox_normcurve->clear();
    QSqlQuery query;
    QVariant v = db.driver()->handle();
    cout << v.typeName()<<endl;
    QString text;
    if(qstrcmp(v.typeName(),"PGconn*")==0){
        text ="SELECT column_name,data_type FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'hybrid_overview';";
    }
    else if(qstrcmp(v.typeName(),"sqlite3*")==0){
        text = "SELECT name,type FROM PRAGMA_TABLE_INFO('hybrid_overview');";
    }
    query.prepare(text);
    query.exec();
    QString col;
    QString type;
    if(qstrcmp(v.typeName(),"PGconn*")==0){
        while(query.next()){
            col = query.value(0).toString();
            type = query.value(1).toString();
            if(type == "integer" || type == "real"){
                if(m_mainWindow->m_dbwindow->ui->comboBox_normcurve->findText(type)==-1){
                    m_mainWindow->m_dbwindow->ui->comboBox_normcurve->addItem(col);
                }
            }
        }
    }
    else if (qstrcmp(v.typeName(),"sqlite3*")==0){
        if(query.last()){
            do{
                col = query.value(0).toString();
                type = query.value(1).toString();
                if(type == "int" || type == "real"){
                    if(m_mainWindow->m_dbwindow->ui->comboBox_normcurve->findText(type)==-1){
                        m_mainWindow->m_dbwindow->ui->comboBox_normcurve->addItem(col);
                    }
                }
            }while(query.previous());
        }
    }

    db.close();
}

QVector<double> DBHandler::getHistoLimits(QVector<double> y)
{
    QVector<double> lims;
    //double max = m_mainWindow->m_dbwindow->ui->lineEdit_upper->text().toDouble();
    //double min = m_mainWindow->m_dbwindow->ui->lineEdit_lower->text().toDouble();
    int bins = m_mainWindow->m_dbwindow->ui->lineEdit_bins->text().toInt();
    double max = *std::max_element(y.begin(),y.end());
    double min = *std::min_element(y.begin(),y.end());
    if(min>0){
        min *=0.9;
    }
    else{
        min*=1.1;
    }
    if(max >0){
        max *=1.1;
    }
    else{
        max *=0.9;
    }
    max *= 1.1;
    min *=0.9;
    //if(max==0){
    //    max=2;
    //}
    lims.push_back(min);
    lims.push_back(max);
    double diff = max-min;
    lims.push_back(bins);
    return lims;
}

void DBHandler::getNormCurve(QString whichProp)
{
    db.open();
    QSqlQuery query;
    QString querstr;
    if(whichProp.isEmpty()==false){
        querstr = "SELECT hybrid_id, vmm, " + whichProp + " FROM latest_measurements";
    }
    else{
        querstr = "SELECT hybrid_id, vmm FROM latest_measurements";
    }

    if(m_mainWindow->m_dbwindow->ui->checkBox_filterApply->isChecked()==true){
        QString otherFilters = getAdditionalFilters();
        if(otherFilters.size()>1){
            querstr += " WHERE ";
            querstr += otherFilters;
        }
        else{
            querstr += ";";
        }
    }
    else{
        querstr += ";";
    }
    cout << querstr.toStdString()<<endl;
    query.exec(querstr);
    QVector<double> y;
    while(query.next()){
        if(!query.value(2).isNull()){
            y.push_back(query.value(2).toDouble());
        }
    }
    QVector<double> lims = getHistoLimits(y);
    m_mainWindow->m_dbwindow->PlotHistogram(y,lims[0],lims[1],lims[2],whichProp,"n",whichProp,whichProp);
    db.close();
    //getVMMClassDistro();
    //getHybridClassDistro();

}

void DBHandler::putAvailableHybrids(QString locations)
{
    m_mainWindow->m_dbwindow->ui->listWidget_availableHybrids->clear();
    QStringList locs = locations.split(",");
    db.open();
    QSqlQuery query;
    QString querstr;
    if(locations.size()>0){
        querstr = "SELECT DISTINCT hybrid_id FROM latest_measurements WHERE location IN('";
        for(int i=0;i<locs.count();i++){
            querstr += locs[i];
            if(i!=locs.count()-1){
                querstr += "','";
            }
        }
        querstr +="') ";
    }
    else if(locations.isEmpty() == true){
        querstr = "SELECT DISTINCT hybrid_id FROM latest_measurements";
    }
    if(m_mainWindow->m_dbwindow->ui->checkBox_filterApply->isChecked()==true){
        QString otherFilters = getAdditionalFilters();
        if(otherFilters.size()>1){
            if(locations.size()>0){
                querstr += " AND ";
            }
            else{
                querstr += " WHERE ";
            }
            querstr += otherFilters;
        }
        else{
            querstr += ";";
        }
    }
    else{
        querstr += ";";
    }
    query.exec(querstr);
    while(query.next()){
        QString hid = query.value(0).toString();
        m_mainWindow->m_dbwindow->ui->listWidget_availableHybrids->addItem(hid);
    }

}

void DBHandler::showHybridInHisto(QString hybrid_id)
{
    QString whichCurve = m_mainWindow->m_dbwindow->ui->comboBox_normcurve->currentText();
    QCustomPlot *plot = m_mainWindow->m_dbwindow->ui->plotNorm;
    QCustomPlot *plotvmm = m_mainWindow->m_dbwindow->ui->plot_VMM_class;
    QCustomPlot *plothybrid = m_mainWindow->m_dbwindow->ui->plot_hybrid_class;
    int nitemp1= plot->itemCount();
    int nitemp2= plotvmm->itemCount();
    int nitemp3= plothybrid->itemCount();
    for(int i=0; i<nitemp1;i++){
        plot->removeItem(0);
    }
    for(int i=0; i<nitemp2;i++){
        plotvmm->removeItem(0);
    }
    for(int i=0; i<nitemp3;i++){
        plothybrid->removeItem(0);
    }
    db.open();
    QSqlQuery query ;
    QString querstr = "SELECT vmm, vmm_class, hybrid_class, "+whichCurve +" FROM latest_measurements WHERE hybrid_id = ?;";
    query.prepare(querstr);
    query.bindValue(0,hybrid_id);
    query.exec();
    QVector<int> vmm;
    QVector<QString> vmmclass;
    QString hybridclass;
    QVector<double> values;
    while(query.next()){
        int vmm = query.value(0).toInt();
        QString vmmclass = query.value(1).toString();
        hybridclass = query.value(2).toString();
        double value = query.value(3).toDouble();
        QString labeltext = hybrid_id+"."+QString::number(vmm);
        QCPItemText *textLabel = new QCPItemText(plot);
        textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
        textLabel->position->setTypeX(QCPItemPosition::ptPlotCoords);
        textLabel->position->setTypeY(QCPItemPosition::ptViewportRatio);
        textLabel->position->setCoords(value, 0);
        textLabel->setText(labeltext);
        textLabel->setPen(QPen(Qt::black));
        textLabel->setClipToAxisRect(false);

        QCPItemLine *arrow = new QCPItemLine(plot);
        arrow->start->setParentAnchor(textLabel->bottom);
        arrow->end->setCoords(value, 1);
        arrow->setHead(QCPLineEnding::esSpikeArrow);
        plot->replot();

        QCPItemText *textLabel1 = new QCPItemText(plotvmm);
        textLabel1->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
        textLabel1->position->setTypeX(QCPItemPosition::ptPlotCoords);
        textLabel1->position->setTypeY(QCPItemPosition::ptViewportRatio);
        int classint =0;
        if(vmmclass == "A"){
            classint = 1;
        }
        if(vmmclass == "B"){
            classint = 2;
        }
        if(vmmclass == "C"){
            classint = 3;
        }
        if(vmmclass == "D"){
            classint = 4;
        }
        if(vmmclass == "E"){
            classint = 5;
        }
        textLabel1->position->setCoords(classint, 0);
        textLabel1->setText(labeltext);
        textLabel1->setPen(QPen(Qt::black));
        textLabel1->setClipToAxisRect(false);

        QCPItemLine *arrow1 = new QCPItemLine(plotvmm);
        arrow1->start->setParentAnchor(textLabel1->bottom);
        arrow1->end->setCoords(classint, 1); // point to (4, 1.6) in x-y-plot coordinates
        arrow1->setHead(QCPLineEnding::esSpikeArrow);
        plotvmm->replot();
    }
    QCPItemText *textLabel2 = new QCPItemText(plothybrid);
    textLabel2->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel2->position->setTypeX(QCPItemPosition::ptPlotCoords);
    textLabel2->position->setTypeY(QCPItemPosition::ptViewportRatio);
    int classint1 =0;
    if(hybridclass == "a"){
        classint1 = 1;
    }
    if(hybridclass== "b"){
        classint1 = 2;
    }
    if(hybridclass== "c"){
        classint1 = 3;
    }
    if(hybridclass== "d"){
        classint1 = 4;
    }
    textLabel2->position->setCoords(classint1, 0);
    textLabel2->setText(hybrid_id);
    textLabel2->setPen(QPen(Qt::black));
    textLabel2->setClipToAxisRect(false);

    QCPItemLine *arrow2 = new QCPItemLine(plothybrid);
    arrow2->start->setParentAnchor(textLabel2->bottom);
    arrow2->end->setCoords(classint1, 1); // point to (4, 1.6) in x-y-plot coordinates
    arrow2->setHead(QCPLineEnding::esSpikeArrow);
    plothybrid->replot();

}

void DBHandler::getVMMClassDistro(){
    db.open();
    QSqlQuery query;
    QString querstr = "SELECT hybrid_id, vmm, vmm_class FROM latest_measurements";
    if(m_mainWindow->m_dbwindow->ui->checkBox_filterApply->isChecked()==true){
        QString otherFilters = getAdditionalFilters();
        if(otherFilters.size()>1){
            querstr += " WHERE ";
            querstr += otherFilters;
        }
        else{
            querstr += ";";
        }
    }
    else{
        querstr += ";";
    }
    query.exec(querstr);
    QVector<QString> vals;
    while(query.next()){
        vals.push_back(query.value(2).toString());
    }
    QCustomPlot* plot = m_mainWindow->m_dbwindow->ui->plot_VMM_class;
    plot->clearItems();
    plot->clearPlottables();
    plot->clearGraphs();
    plot->plotLayout()->removeAt(1);
    plot->legend = new QCPLegend();
    plot->axisRect()->insetLayout()->addElement(plot->legend, Qt::AlignRight|Qt::AlignTop);
    plot->axisRect()->insetLayout()->setMargins(QMargins(12, 12, 12, 12));
    plot->legend->setLayer("legend");
    plot->yAxis->setLabel("Amount");
    plot->xAxis->setLabel("VMM Class");
    plot->legend->setVisible(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);
    QCPLayoutGrid* subLayout = new QCPLayoutGrid();
    plot->plotLayout()->addElement(1, 0, subLayout);
    subLayout->setMargins(QMargins(5, 5, 5, 5));
    subLayout->addElement(0,0,plot->legend);
    plot->legend->setFillOrder(QCPLegend::foColumnsFirst);
    plot->plotLayout()->setRowStretchFactor(1, 0.001);
    QCPBars* histo = new QCPBars(plot->xAxis, plot->yAxis);
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5;
    labels << "A"<< "B" << "C" << "D" << "E";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    plot->xAxis->setTicker(textTicker);
    plot->xAxis->setSubTicks(false);
    plot->xAxis->setTickLength(0, 4);
    plot->xAxis->setRange(0, 6);
//    plot->xAxis->setBasePen(QPen(Qt::white));
//    plot->xAxis->setTickPen(QPen(Qt::white));
    plot->xAxis->grid()->setVisible(true);
    plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    QVector<double> counts;
    counts << vals.count("A") << vals.count("B") << vals.count("C") << vals.count("D") << vals.count("E");
    histo->setData(ticks,counts);
    histo->setName("VMM Class");
    histo->setPen(QPen(QColor(88, 208, 116).lighter(170)));
    histo->setBrush(QColor(88, 208, 116));
    plot->rescaleAxes();
    plot->yAxis->scaleRange(1.1);
    plot->replot();

}

void DBHandler::getHybridClassDistro(){
    db.open();
    QSqlQuery query;
    QString querstr = "SELECT hybrid_id, vmm, hybrid_class FROM latest_measurements";
    if(m_mainWindow->m_dbwindow->ui->checkBox_filterApply->isChecked()==true){
        QString otherFilters = getAdditionalFilters();
        if(otherFilters.size()>1){
            querstr += " WHERE ";
            querstr += otherFilters;
        }
        else{
            querstr += ";";
        }
    }
    else{
        querstr += ";";
    }
    query.exec(querstr);
    QVector<QString> vals;
    while(query.next()){
        vals.push_back(query.value(2).toString());
    }
    QCustomPlot* plot = m_mainWindow->m_dbwindow->ui->plot_hybrid_class;
    plot->clearItems();
    plot->clearPlottables();
    plot->clearGraphs();
    plot->plotLayout()->removeAt(1);
    plot->legend = new QCPLegend();
    plot->axisRect()->insetLayout()->addElement(plot->legend, Qt::AlignRight|Qt::AlignTop);
    plot->axisRect()->insetLayout()->setMargins(QMargins(12, 12, 12, 12));
    plot->legend->setLayer("legend");
    plot->yAxis->setLabel("Amount");
    plot->xAxis->setLabel("Hybrid Class");
    plot->legend->setVisible(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);
    QCPLayoutGrid* subLayout = new QCPLayoutGrid();
    plot->plotLayout()->addElement(1, 0, subLayout);
    subLayout->setMargins(QMargins(5, 5, 5, 5));
    subLayout->addElement(0,0,plot->legend);
    plot->legend->setFillOrder(QCPLegend::foColumnsFirst);
    plot->plotLayout()->setRowStretchFactor(1, 0.001);
    QCPBars* histo = new QCPBars(plot->xAxis, plot->yAxis);
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4;
    labels << "a"<< "b" << "c" << "d" ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    plot->xAxis->setTicker(textTicker);
    plot->xAxis->setSubTicks(false);
    plot->xAxis->setTickLength(0, 4);
    plot->xAxis->setRange(0, 5);
//    plot->xAxis->setBasePen(QPen(Qt::white));
//    plot->xAxis->setTickPen(QPen(Qt::white));
    plot->xAxis->grid()->setVisible(true);
    plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    QVector<double> counts;
    counts << vals.count("a")/2 << vals.count("b")/2 << vals.count("c")/2 << vals.count("d")/2;
    histo->setData(ticks,counts);
    histo->setName("Hybrid Class");
    histo->setPen(QPen(QColor(88, 208, 116).lighter(170)));
    histo->setBrush(QColor(88, 208, 116));
    plot->rescaleAxes();
    plot->yAxis->scaleRange(1.1);
    plot->replot();

}


void DBHandler::addfilter()
{
    db.open();
    QSqlQuery query;
    QVariant v = db.driver()->handle();
    QString text;
    if(qstrcmp(v.typeName(),"PGconn*")==0){
        text ="SELECT column_name,data_type FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'hybrid_overview';";
    }
    else if(qstrcmp(v.typeName(),"sqlite3*")==0){
        text = "SELECT name,type FROM PRAGMA_TABLE_INFO('hybrid_overview');";
    }
    query.prepare(text);
    query.exec();
    QStringList cols;
    QStringList types;
    if(qstrcmp(v.typeName(),"PGconn*")==0){
        while(query.next()){
            cols << query.value(0).toString();
            types << query.value(1).toString();
        }

    }
    else if (qstrcmp(v.typeName(),"sqlite3*")==0){
        if(query.last()){
            do{
                cols << query.value(0).toString();
                types << query.value(1).toString();
            }while(query.previous());
        }
    }
    db.close();
    FilterDialog dwindow(m_mainWindow);
    dwindow.SetColumnsToFilter(cols,types);
    dwindow.exec();
    QString filter = dwindow.getFilter();
    cout << filter.toStdString()<<endl;
    if(filter.isEmpty()==false){
        m_mainWindow->m_dbwindow->ui->listWidget->addItem(filter);
    }
}

void DBHandler::MarkChannel(QString whichtest, int vmm, int chno, QString status)
{
    if(QString::compare(status,"good",Qt::CaseInsensitive)==0){
        MarkChannel(whichtest,vmm,chno,0);
        return;
    }
    else if(QString::compare(status,"ok",Qt::CaseInsensitive)==0){
        MarkChannel(whichtest,vmm,chno,1);
        return;
    }
    else if(QString::compare(status,"bad",Qt::CaseInsensitive)==0){
        MarkChannel(whichtest,vmm,chno,2);
        return;
    }
    else{
        MarkChannel(whichtest,vmm,chno,3);
        return;
    }
}

void DBHandler::MarkChannel(QString whichtest, int vmm, int chno, int status)
{
    h_ChannelResults[vmm][chno].insert(whichtest,status);
}

double DBHandler::getAverage(QVector<double> data){
    double avg = 0;
    int size = data.size();
    if(size==0){
        return 0;
    }
    for(int i =0; i<size;i++){
        avg +=data[i];
    }
    avg /=size;
    return avg;
}

double DBHandler::getMedian(QVector<double> data)
{
    std::vector<double> copy = data.toStdVector();
    std::sort(copy.begin(),copy.end());
    double median;
    if(copy.size()%2==0){
        median = (copy[copy.size()/2]+copy[copy.size()/2-1])/2;
    }
    else{
        median = copy[copy.size()/2];
    }
    cout << median<<endl;
    return median;
}

double DBHandler::getStdDev(QVector<double> data){
    double avg = getAverage(data);
    int size = data.size();
    double stdd=0;
    if(size==0){
        return 0;
    }
    for(int i=0; i< size; i++){
        stdd += pow((avg-data[i]),2);
    }
    stdd /=size;
    stdd = sqrt(stdd);
    if(stdd<1e-16){
        stdd = 0;
    }
    return stdd;
}


QVector<double> DBHandler::convertStrToVec(QString original){
    QStringList veclist = original.split(",");
    QVector<double> vec;
    for(int i=0; i< veclist.size();i++){
        double x = veclist[i].remove('{').remove('}').toDouble();
        //cout << veclist[i].toStdString() << "\t" << x << endl;
        vec.append(x);
    }
    return vec;
}

