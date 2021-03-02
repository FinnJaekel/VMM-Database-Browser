#include "dbwindow.h"
#include "ui_dbwindow.h"
#include <iostream>

using namespace std;
DBWindow::DBWindow(MainWindow *top, QWidget *parent):
    QMainWindow(parent),
    m_mainWindow{top},
    ui(new Ui::dbwindow),
    m_dbhandler(new DBHandler(m_mainWindow,this))
{
    ui->setupUi(this);
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    //m_dbhandler = new DBHandler(m_mainWindow,this);

}

DBWindow::~DBWindow(){
    delete this;
}

void DBWindow::on_pushButton_connect_clicked()
{
    SetClearing(true);
    bool open = m_dbhandler->initiateDatabase();
    if(open){
        m_dbhandler->listAvailableHybrids();
        m_mainWindow->m_dbwindow->ui->pushButton_details->setEnabled(true);
        m_mainWindow->m_dbwindow->ui->pushButton_configdownload->setEnabled(true);
    }
    m_mainWindow->m_dbwindow->ui->pushButton_refresh->setEnabled(true);
    SetClearing(false);
    m_dbhandler->getHybridClassDistro();
    m_dbhandler->getVMMClassDistro();

}

void DBWindow::on_pushButton_refresh_clicked()
{
    SetClearing(true);
    m_dbhandler->listAvailableHybrids();
    SetClearing(false);
}


void DBWindow::on_comboBox_MeasurementID_currentIndexChanged(const QString &arg1)
{
    QString currentSelection = m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType->currentText();
    if(!currentSelection.isEmpty()){
        currentTypeSelection = currentSelection;
    }
    m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType->clear();
    QString h_id = m_dbhandler->getCurrentHybridID();
    int index = m_dbhandler->listAvailableMeasurementTypes(arg1,h_id,currentTypeSelection);
    m_mainWindow->m_dbwindow->ui->comboBox_MeasurementType->setCurrentIndex(index);
    //emit on_pushButton_details_clicked();
}

void DBWindow::on_comboBox_MeasurementType_currentIndexChanged(const QString &arg1)
{
    QString hybrid_id = m_dbhandler->getCurrentHybridID();
    QString measurement_id = m_mainWindow->m_dbwindow->ui->comboBox_MeasurementID->currentText();
    if(measurement_id.isEmpty()==false){
        m_dbhandler->plotData(arg1,measurement_id,hybrid_id);
    }
}

void DBWindow::PlotData(QVector<double> x, QVector<double> y[], QString xlabel, QString ylabel, QString name, QString graphlabel, int datalen, QCustomPlot* plot){
    if(!plot){
        plot = m_mainWindow->m_dbwindow->ui->plot;
    }
    plot->clearItems();
    plot->clearPlottables();
    plot->clearGraphs();
    plot->plotLayout()->removeAt(1);
    plot->legend = new QCPLegend();
    plot->axisRect()->insetLayout()->addElement(plot->legend, Qt::AlignRight|Qt::AlignTop);
    plot->axisRect()->insetLayout()->setMargins(QMargins(12, 12, 12, 12));
    plot->legend->setLayer("legend");
    plot->yAxis->setLabel(ylabel);
    plot->xAxis->setLabel(xlabel);
    plot->legend->setVisible(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);
    QCPLayoutGrid* subLayout = new QCPLayoutGrid();
    plot->plotLayout()->addElement(1, 0, subLayout);
    subLayout->setMargins(QMargins(5, 5, 5, 5));
    subLayout->addElement(0,0,plot->legend);
    plot->legend->setFillOrder(QCPLegend::foColumnsFirst);
    plot->plotLayout()->setRowStretchFactor(1, 0.001);
    plot->xAxis->rescale();
    plot->yAxis->rescale();
    plot->replot();
    QColor colors[datalen];
    if(datalen==2){
        colors[0] = Qt::blue;
        colors[1] = Qt::red;
    }
    else{
        for(int i =0;i<datalen;i++){
            double h = 0.618033988749895* 360./datalen * i;
            colors[i] = QColor::fromHsv(int(h),245,245,255);
        }
    }

    for(int i = 0; i<datalen; i++){
        QString graphname = graphlabel;
        graphname.append(QString::fromStdString(std::to_string(i)));
        plot->addGraph();
        plot->graph(i)->setName(graphname);
        plot->graph(i)->setLineStyle(QCPGraph::lsLine);
        plot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        plot->graph(i)->setPen(QPen(QBrush(colors[i]),1));
        plot->graph(i)->setData(x,y[i]);
        plot->yAxis->rescale();
        plot->xAxis->rescale();
    }
    plot->yAxis->scaleRange(1.1);
    plot->replot(QCustomPlot::RefreshPriority(QCustomPlot::rpImmediateRefresh));
}

void DBWindow::PlotHistogram(QVector<double> y, double xlow, double xhigh,int nbins, QString xlabel, QString ylabel, QString name, QString graphlabel){
    QVector<double> bins;
    QVector<double> ydatas;
    QVector<double> limits;
    limits.resize(3);
    limits[0] = xlow;
    limits[1] = xhigh;
    limits[2] = double(nbins);
    ydatas.resize(nbins);
    double binwidth = (xhigh-xlow)/nbins;
    for(int i=0; i<nbins; i++){
        double bincenter = xlow+(i+0.5)*binwidth;
        bins.push_back(bincenter);
    }
    QVector<double> values =y;
    for(int i=0; i<values.size();i++){
        double val = values[i];
        int bin = int ((val-xlow)/binwidth);
        if(bin>=nbins){
         bin = nbins-1;
        }
        if(bin<0){
            bin=0;
        }
        ydatas[bin]++;
    }
    QCustomPlot* plot = m_mainWindow->m_dbwindow->ui->plotNorm;
    plot->clearItems();
    plot->clearPlottables();
    plot->clearGraphs();
    plot->plotLayout()->removeAt(1);
    plot->legend = new QCPLegend();
    plot->axisRect()->insetLayout()->addElement(plot->legend, Qt::AlignRight|Qt::AlignTop);
    plot->axisRect()->insetLayout()->setMargins(QMargins(12, 12, 12, 12));
    plot->legend->setLayer("legend");
    plot->yAxis->setLabel(ylabel);
    plot->xAxis->setLabel(xlabel);
    plot->legend->setVisible(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes);
    QCPLayoutGrid* subLayout = new QCPLayoutGrid();
    plot->plotLayout()->addElement(1, 0, subLayout);
    subLayout->setMargins(QMargins(5, 5, 5, 5));
    subLayout->addElement(0,0,plot->legend);
    plot->legend->setFillOrder(QCPLegend::foColumnsFirst);
    plot->plotLayout()->setRowStretchFactor(1, 0.001);
    QCPBars* histo = new QCPBars(plot->xAxis, plot->yAxis);
    histo->setData(bins,ydatas);
    histo->setWidth(binwidth);
    histo->setName(name);
    histo->setPen(QPen(QColor(88, 208, 116).lighter(170)));
    histo->setBrush(QColor(88, 208, 116));
    plot->rescaleAxes();
    plot->yAxis->scaleRange(1.1);
    plot->replot();
    plot->savePdf("histogram_of_something.pdf");
}

void DBWindow::AddFitToPlot(QVector<double> x, QVector<double> y[], QString graphlabel, int datalen, QCustomPlot *plot)
{
    if(!plot){
        plot = m_mainWindow->m_dbwindow->ui->plot;
    }
    QColor colors[datalen];
    if(datalen==2){
        colors[0] = Qt::blue;
        colors[1] = Qt::red;
    }
    for(int i = 0; i<datalen; i++){
        QString graphname = graphlabel;
        graphname.append(QString::fromStdString(std::to_string(i)));
        plot->addGraph();
        plot->graph(i+2)->setName(graphname);
        plot->graph(i+2)->setLineStyle(QCPGraph::lsLine);
        //plot->graph(i+2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        plot->graph(i+2)->setPen(QPen(QBrush(colors[i]),1,Qt::DashLine));
        plot->graph(i+2)->setData(x,y[i]);
        plot->yAxis->rescale();
        plot->xAxis->rescale();
    }
    plot->yAxis->scaleRange(1.1);
    plot->replot(QCustomPlot::RefreshPriority(QCustomPlot::rpImmediateRefresh));
}


void DBWindow::on_pushButton_details_clicked()
{
    QTableView* table = m_mainWindow->m_dbwindow->ui->tableView;
    if(table->selectionModel()->hasSelection()==true){
        QModelIndex h_point = table->selectionModel()->currentIndex();
        QString Hybrid_id= table->model()->data(table->model()->index(h_point.row(),0)).toString();
        m_dbhandler->evaluateMeasurement(Hybrid_id);
    }
    else{
        return;
    }

}

void DBWindow::on_pushButton_getquery_clicked()
{
    m_dbhandler->doQuery();
}

void DBWindow::on_pushButton_export_clicked()
{
    m_dbhandler->exportQueryToTxt();
}

void DBWindow::on_pushButton_configdownload_clicked()
{
    QString stdpath = QCoreApplication::applicationDirPath();
    QString dirpath = QFileDialog::getExistingDirectory(this,tr("Select Directory for config files"),stdpath,QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    cout << "Storing config files in " << dirpath.toStdString()<<endl;
    m_dbhandler->getAndStoreConfigs(dirpath);
}

void DBWindow::on_pushButton_addfilter_clicked()
{
    m_dbhandler->addfilter();
}

void DBWindow::on_pushButton_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

void DBWindow::on_pushButton_removeAllFilters_clicked()
{
    int count = m_mainWindow->m_dbwindow->ui->listWidget->count();
    for(int i=0;i<count;i++)
    {
        QListWidgetItem* item = ui->listWidget->item(0);
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

void DBWindow::on_pushButton_storeFilters_clicked()
{
    int count = m_mainWindow->m_dbwindow->ui->listWidget->count();
    QByteArray content;
    for(int i=0;i<count;i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        content.append(item->text());
    }
    QString fileName = QFileDialog::getSaveFileName(this,tr("Store Filters (in txt)"), "",tr("txt Files(*.txt);;All Files (*)"));
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        file.write(content);
        file.close();
    }
}

void DBWindow::on_pushButton_loadFilters_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("txt Files(*.txt);;All Files(*)"));
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        while(!file.atEnd()){
            QByteArray line = file.readLine();
            m_mainWindow->m_dbwindow->ui->listWidget->addItem(line);
        }
        file.close();
    }
}

void DBWindow::on_pushButton_normcurve_clicked()
{
    QString whichprop = m_mainWindow->m_dbwindow->ui->comboBox_normcurve->currentText();
    if(!whichprop.isEmpty()){
        m_dbhandler->getNormCurve(whichprop);
    }
    m_dbhandler->getHybridClassDistro();
    m_dbhandler->getVMMClassDistro();

}

void DBWindow::on_pushButton_addfilter_2_clicked()
{
    m_dbhandler->addfilter();
}

void DBWindow::on_comboBox_normcurve_currentIndexChanged(const QString &arg1)
{
    if(getClearing()==false){
        m_dbhandler->getNormCurve(arg1);
        if(m_mainWindow->m_dbwindow->ui->listWidget_availableHybrids->selectedItems().size()!=0){
            m_dbhandler->showHybridInHisto(m_mainWindow->m_dbwindow->ui->listWidget_availableHybrids->currentItem()->text());
        }
    }
}

void DBWindow::on_pushButton_savepdf_clicked()
{
    QCustomPlot *plot = m_mainWindow->m_dbwindow->ui->plotNorm;
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Plot as PDF"), "",tr("PDF File (*.pdf);;All Files (*)"));
    fileName.remove(".pdf");
    fileName.remove(".png");
    if(fileName.isEmpty()){
        return;
    }
    else{
        plot->savePdf(fileName+".pdf");
        return;
    }
}

void DBWindow::on_lineEdit_locationFilter_returnPressed()
{
    SetClearing(true);
    QString locs = ui->lineEdit_locationFilter->text();
    m_dbhandler->putAvailableHybrids(locs);
    SetClearing(false);
}

void DBWindow::on_listWidget_availableHybrids_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(getClearing() == false){
        QString hybrid_id = current->text();
        m_dbhandler->showHybridInHisto(hybrid_id);
    }
}

void DBWindow::on_checkBox_filterApply_stateChanged(int arg1)
{
    SetClearing(true);
    this->ui->listWidget_availableHybrids->clear();
    m_dbhandler->putAvailableHybrids(m_mainWindow->m_dbwindow->ui->lineEdit_locationFilter->text());
    SetClearing(false);
}

void DBWindow::on_pushButton_savePlot_clicked()
{
    QCustomPlot *plot = m_mainWindow->m_dbwindow->ui->plot;
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Plot as PDF"), "",tr("PDF File (*.pdf);;All Files (*)"));
    fileName.remove(".pdf");
    fileName.remove(".png");
    if(fileName.isEmpty()){
        return;
    }
    else{
        plot->savePdf(fileName+".pdf");
        return;
    }
}

void DBWindow::on_pushButton_2_clicked()
{
    QCustomPlot *plotVMM = m_mainWindow->m_dbwindow->ui->plot_VMM_class;
    QCustomPlot *plotHybrid = m_mainWindow->m_dbwindow->ui->plot_hybrid_class;
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Plots as PDFs (filename_vmm/filename_hybrid.pdf)"), "",tr("PDF File (*.pdf);;All Files (*)"));
    fileName.remove(".pdf");
    fileName.remove(".png");
    if(fileName.isEmpty()){
        return;
    }
    else{
        plotVMM->savePdf(fileName+"_vmm.pdf");
        plotHybrid->savePdf(fileName+"_hybrid.pdf");
        return;
    }
}

void DBWindow::on_pushButton_3_clicked()
{
    m_dbhandler->readSettingFile();
}
