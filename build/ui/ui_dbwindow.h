/********************************************************************************
** Form generated from reading UI file 'dbwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBWINDOW_H
#define UI_DBWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_dbwindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QTextEdit *adressfield;
    QTextEdit *portfield;
    QLabel *portlabel;
    QLabel *adresslabel;
    QPushButton *pushButton_connect;
    QTextEdit *dbnamefield;
    QLabel *dbnamelabel;
    QPushButton *pushButton_refresh;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_2;
    QLabel *measurementIDlabel_2;
    QComboBox *comboBox_MeasurementType;
    QComboBox *comboBox_MeasurementID;
    QLabel *measurementIDlabel;
    QCustomPlot *plot;
    QWidget *gridLayoutWidget_5;
    QGridLayout *ChannelsVMM1_grid;
    QWidget *gridLayoutWidget_4;
    QGridLayout *ChannelsVMM0_grid;
    QPushButton *pushButton_details;
    QPushButton *pushButton_configdownload;
    QPushButton *pushButton_savePlot;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *hybrid_classlabel;
    QGroupBox *groupBox_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *CustomCriteriaGrid;
    QLabel *thr_diff_statuslabel1;
    QGridLayout *gridLayout_83;
    QLabel *label_109;
    QLineEdit *noise_o_l;
    QLineEdit *noise_g_l;
    QLabel *pedestalstatuslabel2;
    QLabel *workingchannelsintlabel;
    QGridLayout *gridLayout_102;
    QLineEdit *threshold_diff_g_l;
    QLineEdit *threshold_diff_o_l;
    QLineEdit *threshold_diff_o_u;
    QLineEdit *threshold_diff_g_u;
    QLabel *label_141;
    QLabel *adcstatuslabel1;
    QLabel *vmm2label;
    QGridLayout *gridLayout_86;
    QLineEdit *internal_o_l;
    QLineEdit *internal_g_l;
    QLabel *label_114;
    QLabel *intchannels2label;
    QGridLayout *gridLayout_99;
    QLabel *label_137;
    QGridLayout *gridLayout_100;
    QLabel *label_138;
    QLabel *label_139;
    QLabel *tdcstatuslabel1;
    QGridLayout *gridLayout_94;
    QLabel *label_128;
    QLabel *label_127;
    QGridLayout *gridLayout_96;
    QLabel *label_125;
    QLabel *label_126;
    QGridLayout *gridLayout_95;
    QLabel *label_123;
    QLabel *label_124;
    QLabel *adcstatuslabel2;
    QLabel *noisestatus1label;
    QGridLayout *gridLayout_80;
    QLineEdit *monitoringADC_g_u;
    QLabel *label_107;
    QLineEdit *monitoringADC_o_l;
    QLineEdit *monitoringADC_o_u;
    QLineEdit *monitoringADC_g_l;
    QLineEdit *monitoringADC_g_l_2;
    QLineEdit *monitoringADC_g_u_2;
    QLineEdit *monitoringADC_o_l_2;
    QLineEdit *monitoringADC_o_u_2;
    QLabel *label_108;
    QLabel *label_7;
    QLabel *thresholdstatuslabel1;
    QGridLayout *gridLayout_88;
    QLineEdit *threshold_g_l;
    QLineEdit *threshold_o_l;
    QLabel *label_117;
    QLabel *extchannels1label;
    QGridLayout *gridLayout_82;
    QLabel *adcvertexstatus1label;
    QLabel *adcvertexstatus3label;
    QLabel *label_134;
    QGridLayout *gridLayout_97;
    QLabel *label_135;
    QLabel *label_136;
    QGridLayout *gridLayout_16;
    QLabel *adccal_bads2;
    QLabel *adccal_bads4;
    QGridLayout *gridLayout_98;
    QLabel *adccurvestatus2label;
    QLabel *adccurvestatus4label;
    QGridLayout *gridLayout_89;
    QLabel *label_118;
    QGridLayout *gridLayout_90;
    QLabel *label_119;
    QLabel *label_120;
    QLabel *label_130;
    QLabel *intchannels1label;
    QLabel *extchannels2label;
    QLabel *noisestatus2label;
    QGridLayout *gridLayout_101;
    QLineEdit *pedestal_o_l;
    QLabel *label_140;
    QLineEdit *pedestal_o_u;
    QLineEdit *pedestal_g_u;
    QLineEdit *pedestal_g_l;
    QGridLayout *gridLayout_87;
    QLineEdit *adcrange_o_l;
    QLabel *label_115;
    QLineEdit *adcrange_g_l;
    QLineEdit *adcrange_g_l_ext;
    QLineEdit *adcrange_o_l_ext;
    QLabel *label_116;
    QGridLayout *gridLayout_91;
    QLabel *adcmonitoringlabel;
    QLabel *label_121;
    QLabel *label_113;
    QGridLayout *gridLayout_92;
    QLabel *adcvertexstatus2label;
    QLabel *adcvertexstatus4label;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_131;
    QGridLayout *gridLayout_12;
    QLabel *label_132;
    QLabel *label_133;
    QGridLayout *gridLayout_11;
    QLabel *adccal_bads1;
    QLabel *adccal_bads3;
    QGridLayout *gridLayout_93;
    QLineEdit *tdc_g_l;
    QLineEdit *tdc_o_l;
    QLineEdit *tdc_o_u;
    QLineEdit *tdc_g_u;
    QLabel *label_122;
    QLabel *tdcstatuslabel2;
    QLabel *pedestallabel;
    QLabel *vmm1label;
    QLabel *thresholdlabel;
    QLabel *thresholdstatuslabel2;
    QGridLayout *gridLayout_81;
    QLabel *adccurvestatus1label;
    QLabel *adccurvestatus3label;
    QGridLayout *gridLayout_84;
    QLineEdit *adcvertex_o_i;
    QLineEdit *adcvertex_g_i;
    QLabel *label_110;
    QLabel *label_111;
    QLineEdit *adcvertex_o_e;
    QLineEdit *adcvertex_g_e;
    QLabel *pedestalstatuslabel1;
    QLabel *workingchannelsextlabel;
    QGridLayout *gridLayout_85;
    QLineEdit *external_o_l;
    QLineEdit *external_g_l;
    QLabel *label_112;
    QLabel *thr_diff_statuslabel2;
    QGroupBox *groupBox_6;
    QTableView *tableView;
    QCheckBox *checkBox_filterLatest;
    QPushButton *pushButton_addfilter;
    QPushButton *pushButton_export;
    QGroupBox *groupBox_7;
    QLineEdit *lineEdit_query;
    QPushButton *pushButton_getquery;
    QLabel *label_2;
    QWidget *tab_2;
    QGroupBox *groupBox_4;
    QCustomPlot *plotNorm;
    QComboBox *comboBox_normcurve;
    QPushButton *pushButton_normcurve;
    QLabel *label_8;
    QLineEdit *lineEdit_bins;
    QPushButton *pushButton_savepdf;
    QCustomPlot *plot_VMM_class;
    QCustomPlot *plot_hybrid_class;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_locationFilter;
    QLabel *label_4;
    QListWidget *listWidget_availableHybrids;
    QLabel *label_5;
    QLabel *label_13;
    QCheckBox *checkBox_filterApply;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_5;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_removeAllFilters;
    QPushButton *pushButton_storeFilters;
    QPushButton *pushButton_loadFilters;
    QPushButton *pushButton_addfilter_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *dbwindow)
    {
        if (dbwindow->objectName().isEmpty())
            dbwindow->setObjectName(QStringLiteral("dbwindow"));
        dbwindow->resize(1743, 1037);
        centralwidget = new QWidget(dbwindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1721, 1001));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 631, 121));
        adressfield = new QTextEdit(groupBox);
        adressfield->setObjectName(QStringLiteral("adressfield"));
        adressfield->setGeometry(QRect(80, 30, 121, 31));
        portfield = new QTextEdit(groupBox);
        portfield->setObjectName(QStringLiteral("portfield"));
        portfield->setGeometry(QRect(270, 30, 121, 31));
        portlabel = new QLabel(groupBox);
        portlabel->setObjectName(QStringLiteral("portlabel"));
        portlabel->setGeometry(QRect(220, 33, 81, 21));
        QFont font;
        font.setPointSize(12);
        portlabel->setFont(font);
        adresslabel = new QLabel(groupBox);
        adresslabel->setObjectName(QStringLiteral("adresslabel"));
        adresslabel->setGeometry(QRect(10, 33, 81, 21));
        adresslabel->setFont(font);
        pushButton_connect = new QPushButton(groupBox);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(10, 80, 121, 22));
        dbnamefield = new QTextEdit(groupBox);
        dbnamefield->setObjectName(QStringLiteral("dbnamefield"));
        dbnamefield->setGeometry(QRect(500, 33, 121, 31));
        dbnamelabel = new QLabel(groupBox);
        dbnamelabel->setObjectName(QStringLiteral("dbnamelabel"));
        dbnamelabel->setGeometry(QRect(410, 33, 81, 21));
        dbnamelabel->setFont(font);
        pushButton_refresh = new QPushButton(groupBox);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));
        pushButton_refresh->setEnabled(false);
        pushButton_refresh->setGeometry(QRect(150, 80, 121, 22));
        pushButton_refresh->setCheckable(false);
        pushButton_refresh->setFlat(false);
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(290, 80, 111, 22));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 440, 971, 511));
        measurementIDlabel_2 = new QLabel(groupBox_2);
        measurementIDlabel_2->setObjectName(QStringLiteral("measurementIDlabel_2"));
        measurementIDlabel_2->setGeometry(QRect(190, 20, 131, 21));
        QFont font1;
        font1.setPointSize(10);
        measurementIDlabel_2->setFont(font1);
        measurementIDlabel_2->setAlignment(Qt::AlignCenter);
        comboBox_MeasurementType = new QComboBox(groupBox_2);
        comboBox_MeasurementType->setObjectName(QStringLiteral("comboBox_MeasurementType"));
        comboBox_MeasurementType->setGeometry(QRect(190, 50, 131, 22));
        comboBox_MeasurementID = new QComboBox(groupBox_2);
        comboBox_MeasurementID->setObjectName(QStringLiteral("comboBox_MeasurementID"));
        comboBox_MeasurementID->setGeometry(QRect(10, 50, 131, 22));
        measurementIDlabel = new QLabel(groupBox_2);
        measurementIDlabel->setObjectName(QStringLiteral("measurementIDlabel"));
        measurementIDlabel->setGeometry(QRect(20, 20, 111, 21));
        measurementIDlabel->setFont(font1);
        measurementIDlabel->setAlignment(Qt::AlignCenter);
        plot = new QCustomPlot(groupBox_2);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setGeometry(QRect(390, 30, 571, 361));
        gridLayoutWidget_5 = new QWidget(groupBox_2);
        gridLayoutWidget_5->setObjectName(QStringLiteral("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(10, 250, 331, 111));
        ChannelsVMM1_grid = new QGridLayout(gridLayoutWidget_5);
        ChannelsVMM1_grid->setObjectName(QStringLiteral("ChannelsVMM1_grid"));
        ChannelsVMM1_grid->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_4 = new QWidget(groupBox_2);
        gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(10, 120, 331, 111));
        ChannelsVMM0_grid = new QGridLayout(gridLayoutWidget_4);
        ChannelsVMM0_grid->setObjectName(QStringLiteral("ChannelsVMM0_grid"));
        ChannelsVMM0_grid->setContentsMargins(0, 0, 0, 0);
        pushButton_details = new QPushButton(groupBox_2);
        pushButton_details->setObjectName(QStringLiteral("pushButton_details"));
        pushButton_details->setEnabled(false);
        pushButton_details->setGeometry(QRect(30, 80, 91, 22));
        pushButton_configdownload = new QPushButton(groupBox_2);
        pushButton_configdownload->setObjectName(QStringLiteral("pushButton_configdownload"));
        pushButton_configdownload->setEnabled(false);
        pushButton_configdownload->setGeometry(QRect(190, 80, 131, 22));
        pushButton_savePlot = new QPushButton(groupBox_2);
        pushButton_savePlot->setObjectName(QStringLiteral("pushButton_savePlot"));
        pushButton_savePlot->setGeometry(QRect(640, 400, 101, 22));
        gridLayoutWidget = new QWidget(groupBox_2);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 380, 331, 36));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        hybrid_classlabel = new QLabel(gridLayoutWidget);
        hybrid_classlabel->setObjectName(QStringLiteral("hybrid_classlabel"));

        gridLayout->addWidget(hybrid_classlabel, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(990, 440, 721, 501));
        scrollArea = new QScrollArea(groupBox_3);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 20, 721, 481));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 705, 551));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        CustomCriteriaGrid = new QGridLayout();
        CustomCriteriaGrid->setObjectName(QStringLiteral("CustomCriteriaGrid"));
        CustomCriteriaGrid->setSizeConstraint(QLayout::SetMaximumSize);
        CustomCriteriaGrid->setHorizontalSpacing(6);
        CustomCriteriaGrid->setContentsMargins(0, -1, 0, -1);
        thr_diff_statuslabel1 = new QLabel(scrollAreaWidgetContents_2);
        thr_diff_statuslabel1->setObjectName(QStringLiteral("thr_diff_statuslabel1"));

        CustomCriteriaGrid->addWidget(thr_diff_statuslabel1, 5, 2, 1, 1);

        gridLayout_83 = new QGridLayout();
        gridLayout_83->setObjectName(QStringLiteral("gridLayout_83"));
        label_109 = new QLabel(scrollAreaWidgetContents_2);
        label_109->setObjectName(QStringLiteral("label_109"));

        gridLayout_83->addWidget(label_109, 0, 2, 1, 1);

        noise_o_l = new QLineEdit(scrollAreaWidgetContents_2);
        noise_o_l->setObjectName(QStringLiteral("noise_o_l"));

        gridLayout_83->addWidget(noise_o_l, 0, 1, 1, 1);

        noise_g_l = new QLineEdit(scrollAreaWidgetContents_2);
        noise_g_l->setObjectName(QStringLiteral("noise_g_l"));

        gridLayout_83->addWidget(noise_g_l, 0, 0, 1, 1);

        gridLayout_83->setColumnStretch(0, 4);
        gridLayout_83->setColumnStretch(1, 4);
        gridLayout_83->setColumnStretch(2, 2);

        CustomCriteriaGrid->addLayout(gridLayout_83, 3, 1, 1, 1);

        pedestalstatuslabel2 = new QLabel(scrollAreaWidgetContents_2);
        pedestalstatuslabel2->setObjectName(QStringLiteral("pedestalstatuslabel2"));

        CustomCriteriaGrid->addWidget(pedestalstatuslabel2, 2, 3, 1, 1);

        workingchannelsintlabel = new QLabel(scrollAreaWidgetContents_2);
        workingchannelsintlabel->setObjectName(QStringLiteral("workingchannelsintlabel"));
        workingchannelsintlabel->setWordWrap(true);

        CustomCriteriaGrid->addWidget(workingchannelsintlabel, 11, 0, 1, 1);

        gridLayout_102 = new QGridLayout();
        gridLayout_102->setObjectName(QStringLiteral("gridLayout_102"));
        threshold_diff_g_l = new QLineEdit(scrollAreaWidgetContents_2);
        threshold_diff_g_l->setObjectName(QStringLiteral("threshold_diff_g_l"));

        gridLayout_102->addWidget(threshold_diff_g_l, 0, 0, 1, 1);

        threshold_diff_o_l = new QLineEdit(scrollAreaWidgetContents_2);
        threshold_diff_o_l->setObjectName(QStringLiteral("threshold_diff_o_l"));

        gridLayout_102->addWidget(threshold_diff_o_l, 0, 2, 1, 1);

        threshold_diff_o_u = new QLineEdit(scrollAreaWidgetContents_2);
        threshold_diff_o_u->setObjectName(QStringLiteral("threshold_diff_o_u"));

        gridLayout_102->addWidget(threshold_diff_o_u, 0, 3, 1, 1);

        threshold_diff_g_u = new QLineEdit(scrollAreaWidgetContents_2);
        threshold_diff_g_u->setObjectName(QStringLiteral("threshold_diff_g_u"));

        gridLayout_102->addWidget(threshold_diff_g_u, 0, 1, 1, 1);

        label_141 = new QLabel(scrollAreaWidgetContents_2);
        label_141->setObjectName(QStringLiteral("label_141"));

        gridLayout_102->addWidget(label_141, 0, 4, 1, 1);

        gridLayout_102->setColumnStretch(0, 18);
        gridLayout_102->setColumnStretch(1, 18);
        gridLayout_102->setColumnStretch(2, 18);
        gridLayout_102->setColumnStretch(3, 18);
        gridLayout_102->setColumnStretch(4, 19);

        CustomCriteriaGrid->addLayout(gridLayout_102, 5, 1, 1, 1);

        adcstatuslabel1 = new QLabel(scrollAreaWidgetContents_2);
        adcstatuslabel1->setObjectName(QStringLiteral("adcstatuslabel1"));
        adcstatuslabel1->setWordWrap(true);

        CustomCriteriaGrid->addWidget(adcstatuslabel1, 1, 2, 1, 1);

        vmm2label = new QLabel(scrollAreaWidgetContents_2);
        vmm2label->setObjectName(QStringLiteral("vmm2label"));

        CustomCriteriaGrid->addWidget(vmm2label, 0, 3, 1, 1);

        gridLayout_86 = new QGridLayout();
        gridLayout_86->setObjectName(QStringLiteral("gridLayout_86"));
        internal_o_l = new QLineEdit(scrollAreaWidgetContents_2);
        internal_o_l->setObjectName(QStringLiteral("internal_o_l"));

        gridLayout_86->addWidget(internal_o_l, 0, 1, 1, 1);

        internal_g_l = new QLineEdit(scrollAreaWidgetContents_2);
        internal_g_l->setObjectName(QStringLiteral("internal_g_l"));

        gridLayout_86->addWidget(internal_g_l, 0, 0, 1, 1);

        label_114 = new QLabel(scrollAreaWidgetContents_2);
        label_114->setObjectName(QStringLiteral("label_114"));

        gridLayout_86->addWidget(label_114, 0, 2, 1, 1);

        gridLayout_86->setColumnStretch(0, 4);
        gridLayout_86->setColumnStretch(1, 4);
        gridLayout_86->setColumnStretch(2, 2);

        CustomCriteriaGrid->addLayout(gridLayout_86, 11, 1, 1, 1);

        intchannels2label = new QLabel(scrollAreaWidgetContents_2);
        intchannels2label->setObjectName(QStringLiteral("intchannels2label"));

        CustomCriteriaGrid->addWidget(intchannels2label, 11, 3, 1, 1);

        gridLayout_99 = new QGridLayout();
        gridLayout_99->setObjectName(QStringLiteral("gridLayout_99"));
        gridLayout_99->setVerticalSpacing(1);
        label_137 = new QLabel(scrollAreaWidgetContents_2);
        label_137->setObjectName(QStringLiteral("label_137"));
        QFont font2;
        font2.setFamily(QStringLiteral("Sans Serif"));
        font2.setPointSize(8);
        label_137->setFont(font2);
        label_137->setWordWrap(true);

        gridLayout_99->addWidget(label_137, 0, 0, 1, 1);

        gridLayout_100 = new QGridLayout();
        gridLayout_100->setObjectName(QStringLiteral("gridLayout_100"));
        label_138 = new QLabel(scrollAreaWidgetContents_2);
        label_138->setObjectName(QStringLiteral("label_138"));

        gridLayout_100->addWidget(label_138, 2, 0, 1, 1);

        label_139 = new QLabel(scrollAreaWidgetContents_2);
        label_139->setObjectName(QStringLiteral("label_139"));

        gridLayout_100->addWidget(label_139, 1, 0, 1, 1);


        gridLayout_99->addLayout(gridLayout_100, 0, 1, 1, 1);

        gridLayout_99->setColumnStretch(0, 4);
        gridLayout_99->setColumnStretch(1, 1);

        CustomCriteriaGrid->addLayout(gridLayout_99, 8, 0, 1, 1);

        tdcstatuslabel1 = new QLabel(scrollAreaWidgetContents_2);
        tdcstatuslabel1->setObjectName(QStringLiteral("tdcstatuslabel1"));

        CustomCriteriaGrid->addWidget(tdcstatuslabel1, 9, 2, 1, 1);

        gridLayout_94 = new QGridLayout();
        gridLayout_94->setObjectName(QStringLiteral("gridLayout_94"));
        gridLayout_94->setSizeConstraint(QLayout::SetMaximumSize);
        label_128 = new QLabel(scrollAreaWidgetContents_2);
        label_128->setObjectName(QStringLiteral("label_128"));
        label_128->setStyleSheet(QStringLiteral("background-color: yellow"));

        gridLayout_94->addWidget(label_128, 0, 1, 1, 1);

        label_127 = new QLabel(scrollAreaWidgetContents_2);
        label_127->setObjectName(QStringLiteral("label_127"));
        label_127->setStyleSheet(QStringLiteral("background-color: lightgreen"));

        gridLayout_94->addWidget(label_127, 0, 0, 1, 1);

        gridLayout_96 = new QGridLayout();
        gridLayout_96->setObjectName(QStringLiteral("gridLayout_96"));
        label_125 = new QLabel(scrollAreaWidgetContents_2);
        label_125->setObjectName(QStringLiteral("label_125"));

        gridLayout_96->addWidget(label_125, 0, 0, 1, 1);

        label_126 = new QLabel(scrollAreaWidgetContents_2);
        label_126->setObjectName(QStringLiteral("label_126"));

        gridLayout_96->addWidget(label_126, 0, 1, 1, 1);

        gridLayout_96->setColumnStretch(0, 1);
        gridLayout_96->setColumnStretch(1, 1);

        gridLayout_94->addLayout(gridLayout_96, 1, 1, 1, 1);

        gridLayout_95 = new QGridLayout();
        gridLayout_95->setObjectName(QStringLiteral("gridLayout_95"));
        label_123 = new QLabel(scrollAreaWidgetContents_2);
        label_123->setObjectName(QStringLiteral("label_123"));

        gridLayout_95->addWidget(label_123, 0, 0, 1, 1);

        label_124 = new QLabel(scrollAreaWidgetContents_2);
        label_124->setObjectName(QStringLiteral("label_124"));

        gridLayout_95->addWidget(label_124, 0, 1, 1, 1);

        gridLayout_95->setColumnStretch(0, 1);
        gridLayout_95->setColumnStretch(1, 1);

        gridLayout_94->addLayout(gridLayout_95, 1, 0, 1, 1);

        gridLayout_94->setColumnStretch(0, 1);
        gridLayout_94->setColumnStretch(1, 1);

        CustomCriteriaGrid->addLayout(gridLayout_94, 0, 1, 1, 1);

        adcstatuslabel2 = new QLabel(scrollAreaWidgetContents_2);
        adcstatuslabel2->setObjectName(QStringLiteral("adcstatuslabel2"));
        adcstatuslabel2->setWordWrap(true);

        CustomCriteriaGrid->addWidget(adcstatuslabel2, 1, 3, 1, 1);

        noisestatus1label = new QLabel(scrollAreaWidgetContents_2);
        noisestatus1label->setObjectName(QStringLiteral("noisestatus1label"));

        CustomCriteriaGrid->addWidget(noisestatus1label, 3, 2, 1, 1);

        gridLayout_80 = new QGridLayout();
        gridLayout_80->setObjectName(QStringLiteral("gridLayout_80"));
        gridLayout_80->setSizeConstraint(QLayout::SetMaximumSize);
        monitoringADC_g_u = new QLineEdit(scrollAreaWidgetContents_2);
        monitoringADC_g_u->setObjectName(QStringLiteral("monitoringADC_g_u"));
        monitoringADC_g_u->setCursorPosition(3);

        gridLayout_80->addWidget(monitoringADC_g_u, 0, 1, 1, 1);

        label_107 = new QLabel(scrollAreaWidgetContents_2);
        label_107->setObjectName(QStringLiteral("label_107"));
        QFont font3;
        font3.setFamily(QStringLiteral("Sans Serif"));
        font3.setPointSize(7);
        label_107->setFont(font3);

        gridLayout_80->addWidget(label_107, 0, 4, 1, 1);

        monitoringADC_o_l = new QLineEdit(scrollAreaWidgetContents_2);
        monitoringADC_o_l->setObjectName(QStringLiteral("monitoringADC_o_l"));
        monitoringADC_o_l->setCursorPosition(3);

        gridLayout_80->addWidget(monitoringADC_o_l, 0, 2, 1, 1);

        monitoringADC_o_u = new QLineEdit(scrollAreaWidgetContents_2);
        monitoringADC_o_u->setObjectName(QStringLiteral("monitoringADC_o_u"));
        monitoringADC_o_u->setCursorPosition(1);

        gridLayout_80->addWidget(monitoringADC_o_u, 0, 3, 1, 1);

        monitoringADC_g_l = new QLineEdit(scrollAreaWidgetContents_2);
        monitoringADC_g_l->setObjectName(QStringLiteral("monitoringADC_g_l"));
        monitoringADC_g_l->setLayoutDirection(Qt::LeftToRight);
        monitoringADC_g_l->setCursorPosition(3);
        monitoringADC_g_l->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_80->addWidget(monitoringADC_g_l, 0, 0, 1, 1);

        monitoringADC_g_l_2 = new QLineEdit(scrollAreaWidgetContents_2);
        monitoringADC_g_l_2->setObjectName(QStringLiteral("monitoringADC_g_l_2"));

        gridLayout_80->addWidget(monitoringADC_g_l_2, 1, 0, 1, 1);

        monitoringADC_g_u_2 = new QLineEdit(scrollAreaWidgetContents_2);
        monitoringADC_g_u_2->setObjectName(QStringLiteral("monitoringADC_g_u_2"));

        gridLayout_80->addWidget(monitoringADC_g_u_2, 1, 1, 1, 1);

        monitoringADC_o_l_2 = new QLineEdit(scrollAreaWidgetContents_2);
        monitoringADC_o_l_2->setObjectName(QStringLiteral("monitoringADC_o_l_2"));

        gridLayout_80->addWidget(monitoringADC_o_l_2, 1, 2, 1, 1);

        monitoringADC_o_u_2 = new QLineEdit(scrollAreaWidgetContents_2);
        monitoringADC_o_u_2->setObjectName(QStringLiteral("monitoringADC_o_u_2"));

        gridLayout_80->addWidget(monitoringADC_o_u_2, 1, 3, 1, 1);

        label_108 = new QLabel(scrollAreaWidgetContents_2);
        label_108->setObjectName(QStringLiteral("label_108"));

        gridLayout_80->addWidget(label_108, 1, 4, 1, 1);

        gridLayout_80->setColumnStretch(0, 18);
        gridLayout_80->setColumnStretch(1, 18);
        gridLayout_80->setColumnStretch(2, 18);
        gridLayout_80->setColumnStretch(3, 18);
        gridLayout_80->setColumnStretch(4, 10);

        CustomCriteriaGrid->addLayout(gridLayout_80, 1, 1, 1, 1);

        label_7 = new QLabel(scrollAreaWidgetContents_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        CustomCriteriaGrid->addWidget(label_7, 5, 0, 1, 1);

        thresholdstatuslabel1 = new QLabel(scrollAreaWidgetContents_2);
        thresholdstatuslabel1->setObjectName(QStringLiteral("thresholdstatuslabel1"));

        CustomCriteriaGrid->addWidget(thresholdstatuslabel1, 4, 2, 1, 1);

        gridLayout_88 = new QGridLayout();
        gridLayout_88->setObjectName(QStringLiteral("gridLayout_88"));
        threshold_g_l = new QLineEdit(scrollAreaWidgetContents_2);
        threshold_g_l->setObjectName(QStringLiteral("threshold_g_l"));

        gridLayout_88->addWidget(threshold_g_l, 0, 0, 1, 1);

        threshold_o_l = new QLineEdit(scrollAreaWidgetContents_2);
        threshold_o_l->setObjectName(QStringLiteral("threshold_o_l"));

        gridLayout_88->addWidget(threshold_o_l, 0, 1, 1, 1);

        label_117 = new QLabel(scrollAreaWidgetContents_2);
        label_117->setObjectName(QStringLiteral("label_117"));

        gridLayout_88->addWidget(label_117, 0, 2, 1, 1);

        gridLayout_88->setColumnStretch(0, 4);
        gridLayout_88->setColumnStretch(1, 4);
        gridLayout_88->setColumnStretch(2, 2);

        CustomCriteriaGrid->addLayout(gridLayout_88, 4, 1, 1, 1);

        extchannels1label = new QLabel(scrollAreaWidgetContents_2);
        extchannels1label->setObjectName(QStringLiteral("extchannels1label"));

        CustomCriteriaGrid->addWidget(extchannels1label, 10, 2, 1, 1);

        gridLayout_82 = new QGridLayout();
        gridLayout_82->setObjectName(QStringLiteral("gridLayout_82"));
        adcvertexstatus1label = new QLabel(scrollAreaWidgetContents_2);
        adcvertexstatus1label->setObjectName(QStringLiteral("adcvertexstatus1label"));

        gridLayout_82->addWidget(adcvertexstatus1label, 0, 0, 1, 1);

        adcvertexstatus3label = new QLabel(scrollAreaWidgetContents_2);
        adcvertexstatus3label->setObjectName(QStringLiteral("adcvertexstatus3label"));

        gridLayout_82->addWidget(adcvertexstatus3label, 1, 0, 1, 1);


        CustomCriteriaGrid->addLayout(gridLayout_82, 8, 2, 1, 1);

        label_134 = new QLabel(scrollAreaWidgetContents_2);
        label_134->setObjectName(QStringLiteral("label_134"));
        label_134->setFont(font2);

        CustomCriteriaGrid->addWidget(label_134, 9, 0, 1, 1);

        gridLayout_97 = new QGridLayout();
        gridLayout_97->setObjectName(QStringLiteral("gridLayout_97"));
        label_135 = new QLabel(scrollAreaWidgetContents_2);
        label_135->setObjectName(QStringLiteral("label_135"));
        label_135->setWordWrap(true);

        gridLayout_97->addWidget(label_135, 0, 0, 1, 1);

        label_136 = new QLabel(scrollAreaWidgetContents_2);
        label_136->setObjectName(QStringLiteral("label_136"));
        label_136->setWordWrap(true);

        gridLayout_97->addWidget(label_136, 1, 0, 1, 1);


        CustomCriteriaGrid->addLayout(gridLayout_97, 6, 1, 1, 1);

        gridLayout_16 = new QGridLayout();
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        adccal_bads2 = new QLabel(scrollAreaWidgetContents_2);
        adccal_bads2->setObjectName(QStringLiteral("adccal_bads2"));
        adccal_bads2->setScaledContents(false);
        adccal_bads2->setWordWrap(true);

        gridLayout_16->addWidget(adccal_bads2, 0, 0, 1, 1);

        adccal_bads4 = new QLabel(scrollAreaWidgetContents_2);
        adccal_bads4->setObjectName(QStringLiteral("adccal_bads4"));
        adccal_bads4->setScaledContents(false);
        adccal_bads4->setWordWrap(true);

        gridLayout_16->addWidget(adccal_bads4, 1, 0, 1, 1);


        CustomCriteriaGrid->addLayout(gridLayout_16, 7, 3, 1, 1);

        gridLayout_98 = new QGridLayout();
        gridLayout_98->setObjectName(QStringLiteral("gridLayout_98"));
        adccurvestatus2label = new QLabel(scrollAreaWidgetContents_2);
        adccurvestatus2label->setObjectName(QStringLiteral("adccurvestatus2label"));

        gridLayout_98->addWidget(adccurvestatus2label, 0, 0, 1, 1);

        adccurvestatus4label = new QLabel(scrollAreaWidgetContents_2);
        adccurvestatus4label->setObjectName(QStringLiteral("adccurvestatus4label"));

        gridLayout_98->addWidget(adccurvestatus4label, 1, 0, 1, 1);


        CustomCriteriaGrid->addLayout(gridLayout_98, 6, 3, 1, 1);

        gridLayout_89 = new QGridLayout();
        gridLayout_89->setObjectName(QStringLiteral("gridLayout_89"));
        label_118 = new QLabel(scrollAreaWidgetContents_2);
        label_118->setObjectName(QStringLiteral("label_118"));
        label_118->setFont(font2);
        label_118->setWordWrap(true);

        gridLayout_89->addWidget(label_118, 0, 0, 1, 1);

        gridLayout_90 = new QGridLayout();
        gridLayout_90->setObjectName(QStringLiteral("gridLayout_90"));
        label_119 = new QLabel(scrollAreaWidgetContents_2);
        label_119->setObjectName(QStringLiteral("label_119"));

        gridLayout_90->addWidget(label_119, 2, 0, 1, 1);

        label_120 = new QLabel(scrollAreaWidgetContents_2);
        label_120->setObjectName(QStringLiteral("label_120"));

        gridLayout_90->addWidget(label_120, 1, 0, 1, 1);


        gridLayout_89->addLayout(gridLayout_90, 0, 1, 1, 1);

        gridLayout_89->setColumnStretch(0, 4);
        gridLayout_89->setColumnStretch(1, 1);

        CustomCriteriaGrid->addLayout(gridLayout_89, 6, 0, 1, 1);

        label_130 = new QLabel(scrollAreaWidgetContents_2);
        label_130->setObjectName(QStringLiteral("label_130"));

        CustomCriteriaGrid->addWidget(label_130, 0, 0, 1, 1);

        intchannels1label = new QLabel(scrollAreaWidgetContents_2);
        intchannels1label->setObjectName(QStringLiteral("intchannels1label"));

        CustomCriteriaGrid->addWidget(intchannels1label, 11, 2, 1, 1);

        extchannels2label = new QLabel(scrollAreaWidgetContents_2);
        extchannels2label->setObjectName(QStringLiteral("extchannels2label"));

        CustomCriteriaGrid->addWidget(extchannels2label, 10, 3, 1, 1);

        noisestatus2label = new QLabel(scrollAreaWidgetContents_2);
        noisestatus2label->setObjectName(QStringLiteral("noisestatus2label"));

        CustomCriteriaGrid->addWidget(noisestatus2label, 3, 3, 1, 1);

        gridLayout_101 = new QGridLayout();
        gridLayout_101->setObjectName(QStringLiteral("gridLayout_101"));
        gridLayout_101->setSizeConstraint(QLayout::SetMaximumSize);
        pedestal_o_l = new QLineEdit(scrollAreaWidgetContents_2);
        pedestal_o_l->setObjectName(QStringLiteral("pedestal_o_l"));

        gridLayout_101->addWidget(pedestal_o_l, 0, 2, 1, 1);

        label_140 = new QLabel(scrollAreaWidgetContents_2);
        label_140->setObjectName(QStringLiteral("label_140"));

        gridLayout_101->addWidget(label_140, 0, 4, 1, 1);

        pedestal_o_u = new QLineEdit(scrollAreaWidgetContents_2);
        pedestal_o_u->setObjectName(QStringLiteral("pedestal_o_u"));

        gridLayout_101->addWidget(pedestal_o_u, 0, 3, 1, 1);

        pedestal_g_u = new QLineEdit(scrollAreaWidgetContents_2);
        pedestal_g_u->setObjectName(QStringLiteral("pedestal_g_u"));

        gridLayout_101->addWidget(pedestal_g_u, 0, 1, 1, 1);

        pedestal_g_l = new QLineEdit(scrollAreaWidgetContents_2);
        pedestal_g_l->setObjectName(QStringLiteral("pedestal_g_l"));

        gridLayout_101->addWidget(pedestal_g_l, 0, 0, 1, 1);

        gridLayout_101->setColumnStretch(0, 18);
        gridLayout_101->setColumnStretch(1, 18);
        gridLayout_101->setColumnStretch(2, 18);
        gridLayout_101->setColumnStretch(3, 18);
        gridLayout_101->setColumnStretch(4, 10);

        CustomCriteriaGrid->addLayout(gridLayout_101, 2, 1, 1, 1);

        gridLayout_87 = new QGridLayout();
        gridLayout_87->setObjectName(QStringLiteral("gridLayout_87"));
        adcrange_o_l = new QLineEdit(scrollAreaWidgetContents_2);
        adcrange_o_l->setObjectName(QStringLiteral("adcrange_o_l"));

        gridLayout_87->addWidget(adcrange_o_l, 0, 1, 1, 1);

        label_115 = new QLabel(scrollAreaWidgetContents_2);
        label_115->setObjectName(QStringLiteral("label_115"));

        gridLayout_87->addWidget(label_115, 0, 2, 1, 1);

        adcrange_g_l = new QLineEdit(scrollAreaWidgetContents_2);
        adcrange_g_l->setObjectName(QStringLiteral("adcrange_g_l"));

        gridLayout_87->addWidget(adcrange_g_l, 0, 0, 1, 1);

        adcrange_g_l_ext = new QLineEdit(scrollAreaWidgetContents_2);
        adcrange_g_l_ext->setObjectName(QStringLiteral("adcrange_g_l_ext"));

        gridLayout_87->addWidget(adcrange_g_l_ext, 1, 0, 1, 1);

        adcrange_o_l_ext = new QLineEdit(scrollAreaWidgetContents_2);
        adcrange_o_l_ext->setObjectName(QStringLiteral("adcrange_o_l_ext"));

        gridLayout_87->addWidget(adcrange_o_l_ext, 1, 1, 1, 1);

        label_116 = new QLabel(scrollAreaWidgetContents_2);
        label_116->setObjectName(QStringLiteral("label_116"));

        gridLayout_87->addWidget(label_116, 1, 2, 1, 1);

        gridLayout_87->setColumnStretch(0, 4);
        gridLayout_87->setColumnStretch(1, 4);
        gridLayout_87->setColumnStretch(2, 2);

        CustomCriteriaGrid->addLayout(gridLayout_87, 7, 1, 1, 1);

        gridLayout_91 = new QGridLayout();
        gridLayout_91->setObjectName(QStringLiteral("gridLayout_91"));
        adcmonitoringlabel = new QLabel(scrollAreaWidgetContents_2);
        adcmonitoringlabel->setObjectName(QStringLiteral("adcmonitoringlabel"));

        gridLayout_91->addWidget(adcmonitoringlabel, 0, 0, 1, 1);

        label_121 = new QLabel(scrollAreaWidgetContents_2);
        label_121->setObjectName(QStringLiteral("label_121"));

        gridLayout_91->addWidget(label_121, 1, 0, 1, 1);


        CustomCriteriaGrid->addLayout(gridLayout_91, 1, 0, 1, 1);

        label_113 = new QLabel(scrollAreaWidgetContents_2);
        label_113->setObjectName(QStringLiteral("label_113"));

        CustomCriteriaGrid->addWidget(label_113, 3, 0, 1, 1);

        gridLayout_92 = new QGridLayout();
        gridLayout_92->setObjectName(QStringLiteral("gridLayout_92"));
        adcvertexstatus2label = new QLabel(scrollAreaWidgetContents_2);
        adcvertexstatus2label->setObjectName(QStringLiteral("adcvertexstatus2label"));

        gridLayout_92->addWidget(adcvertexstatus2label, 0, 0, 1, 1);

        adcvertexstatus4label = new QLabel(scrollAreaWidgetContents_2);
        adcvertexstatus4label->setObjectName(QStringLiteral("adcvertexstatus4label"));

        gridLayout_92->addWidget(adcvertexstatus4label, 1, 0, 1, 1);


        CustomCriteriaGrid->addLayout(gridLayout_92, 8, 3, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_131 = new QLabel(scrollAreaWidgetContents_2);
        label_131->setObjectName(QStringLiteral("label_131"));
        label_131->setFont(font2);
        label_131->setWordWrap(true);

        horizontalLayout_6->addWidget(label_131);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        label_132 = new QLabel(scrollAreaWidgetContents_2);
        label_132->setObjectName(QStringLiteral("label_132"));

        gridLayout_12->addWidget(label_132, 1, 0, 1, 1);

        label_133 = new QLabel(scrollAreaWidgetContents_2);
        label_133->setObjectName(QStringLiteral("label_133"));

        gridLayout_12->addWidget(label_133, 0, 0, 1, 1);


        horizontalLayout_6->addLayout(gridLayout_12);

        horizontalLayout_6->setStretch(0, 4);
        horizontalLayout_6->setStretch(1, 1);

        horizontalLayout_5->addLayout(horizontalLayout_6);


        CustomCriteriaGrid->addLayout(horizontalLayout_5, 7, 0, 1, 1);

        gridLayout_11 = new QGridLayout();
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        adccal_bads1 = new QLabel(scrollAreaWidgetContents_2);
        adccal_bads1->setObjectName(QStringLiteral("adccal_bads1"));
        adccal_bads1->setScaledContents(false);
        adccal_bads1->setWordWrap(true);

        gridLayout_11->addWidget(adccal_bads1, 0, 0, 1, 1);

        adccal_bads3 = new QLabel(scrollAreaWidgetContents_2);
        adccal_bads3->setObjectName(QStringLiteral("adccal_bads3"));
        adccal_bads3->setScaledContents(false);
        adccal_bads3->setWordWrap(true);

        gridLayout_11->addWidget(adccal_bads3, 1, 0, 1, 1);


        CustomCriteriaGrid->addLayout(gridLayout_11, 7, 2, 1, 1);

        gridLayout_93 = new QGridLayout();
        gridLayout_93->setObjectName(QStringLiteral("gridLayout_93"));
        tdc_g_l = new QLineEdit(scrollAreaWidgetContents_2);
        tdc_g_l->setObjectName(QStringLiteral("tdc_g_l"));

        gridLayout_93->addWidget(tdc_g_l, 0, 0, 1, 1);

        tdc_o_l = new QLineEdit(scrollAreaWidgetContents_2);
        tdc_o_l->setObjectName(QStringLiteral("tdc_o_l"));

        gridLayout_93->addWidget(tdc_o_l, 0, 2, 1, 1);

        tdc_o_u = new QLineEdit(scrollAreaWidgetContents_2);
        tdc_o_u->setObjectName(QStringLiteral("tdc_o_u"));

        gridLayout_93->addWidget(tdc_o_u, 0, 3, 1, 1);

        tdc_g_u = new QLineEdit(scrollAreaWidgetContents_2);
        tdc_g_u->setObjectName(QStringLiteral("tdc_g_u"));

        gridLayout_93->addWidget(tdc_g_u, 0, 1, 1, 1);

        label_122 = new QLabel(scrollAreaWidgetContents_2);
        label_122->setObjectName(QStringLiteral("label_122"));

        gridLayout_93->addWidget(label_122, 0, 4, 1, 1);

        gridLayout_93->setColumnStretch(0, 18);
        gridLayout_93->setColumnStretch(1, 18);
        gridLayout_93->setColumnStretch(2, 18);
        gridLayout_93->setColumnStretch(3, 18);
        gridLayout_93->setColumnStretch(4, 19);

        CustomCriteriaGrid->addLayout(gridLayout_93, 9, 1, 1, 1);

        tdcstatuslabel2 = new QLabel(scrollAreaWidgetContents_2);
        tdcstatuslabel2->setObjectName(QStringLiteral("tdcstatuslabel2"));

        CustomCriteriaGrid->addWidget(tdcstatuslabel2, 9, 3, 1, 1);

        pedestallabel = new QLabel(scrollAreaWidgetContents_2);
        pedestallabel->setObjectName(QStringLiteral("pedestallabel"));

        CustomCriteriaGrid->addWidget(pedestallabel, 2, 0, 1, 1);

        vmm1label = new QLabel(scrollAreaWidgetContents_2);
        vmm1label->setObjectName(QStringLiteral("vmm1label"));

        CustomCriteriaGrid->addWidget(vmm1label, 0, 2, 1, 1);

        thresholdlabel = new QLabel(scrollAreaWidgetContents_2);
        thresholdlabel->setObjectName(QStringLiteral("thresholdlabel"));

        CustomCriteriaGrid->addWidget(thresholdlabel, 4, 0, 1, 1);

        thresholdstatuslabel2 = new QLabel(scrollAreaWidgetContents_2);
        thresholdstatuslabel2->setObjectName(QStringLiteral("thresholdstatuslabel2"));

        CustomCriteriaGrid->addWidget(thresholdstatuslabel2, 4, 3, 1, 1);

        gridLayout_81 = new QGridLayout();
        gridLayout_81->setObjectName(QStringLiteral("gridLayout_81"));
        adccurvestatus1label = new QLabel(scrollAreaWidgetContents_2);
        adccurvestatus1label->setObjectName(QStringLiteral("adccurvestatus1label"));

        gridLayout_81->addWidget(adccurvestatus1label, 0, 0, 1, 1);

        adccurvestatus3label = new QLabel(scrollAreaWidgetContents_2);
        adccurvestatus3label->setObjectName(QStringLiteral("adccurvestatus3label"));

        gridLayout_81->addWidget(adccurvestatus3label, 1, 0, 1, 1);


        CustomCriteriaGrid->addLayout(gridLayout_81, 6, 2, 1, 1);

        gridLayout_84 = new QGridLayout();
        gridLayout_84->setObjectName(QStringLiteral("gridLayout_84"));
        adcvertex_o_i = new QLineEdit(scrollAreaWidgetContents_2);
        adcvertex_o_i->setObjectName(QStringLiteral("adcvertex_o_i"));

        gridLayout_84->addWidget(adcvertex_o_i, 0, 1, 1, 1);

        adcvertex_g_i = new QLineEdit(scrollAreaWidgetContents_2);
        adcvertex_g_i->setObjectName(QStringLiteral("adcvertex_g_i"));

        gridLayout_84->addWidget(adcvertex_g_i, 0, 0, 1, 1);

        label_110 = new QLabel(scrollAreaWidgetContents_2);
        label_110->setObjectName(QStringLiteral("label_110"));

        gridLayout_84->addWidget(label_110, 0, 2, 1, 1);

        label_111 = new QLabel(scrollAreaWidgetContents_2);
        label_111->setObjectName(QStringLiteral("label_111"));

        gridLayout_84->addWidget(label_111, 1, 2, 1, 1);

        adcvertex_o_e = new QLineEdit(scrollAreaWidgetContents_2);
        adcvertex_o_e->setObjectName(QStringLiteral("adcvertex_o_e"));

        gridLayout_84->addWidget(adcvertex_o_e, 1, 1, 1, 1);

        adcvertex_g_e = new QLineEdit(scrollAreaWidgetContents_2);
        adcvertex_g_e->setObjectName(QStringLiteral("adcvertex_g_e"));

        gridLayout_84->addWidget(adcvertex_g_e, 1, 0, 1, 1);

        gridLayout_84->setColumnStretch(0, 4);
        gridLayout_84->setColumnStretch(1, 4);
        gridLayout_84->setColumnStretch(2, 2);

        CustomCriteriaGrid->addLayout(gridLayout_84, 8, 1, 1, 1);

        pedestalstatuslabel1 = new QLabel(scrollAreaWidgetContents_2);
        pedestalstatuslabel1->setObjectName(QStringLiteral("pedestalstatuslabel1"));

        CustomCriteriaGrid->addWidget(pedestalstatuslabel1, 2, 2, 1, 1);

        workingchannelsextlabel = new QLabel(scrollAreaWidgetContents_2);
        workingchannelsextlabel->setObjectName(QStringLiteral("workingchannelsextlabel"));
        workingchannelsextlabel->setWordWrap(true);

        CustomCriteriaGrid->addWidget(workingchannelsextlabel, 10, 0, 1, 1);

        gridLayout_85 = new QGridLayout();
        gridLayout_85->setObjectName(QStringLiteral("gridLayout_85"));
        external_o_l = new QLineEdit(scrollAreaWidgetContents_2);
        external_o_l->setObjectName(QStringLiteral("external_o_l"));

        gridLayout_85->addWidget(external_o_l, 0, 1, 1, 1);

        external_g_l = new QLineEdit(scrollAreaWidgetContents_2);
        external_g_l->setObjectName(QStringLiteral("external_g_l"));

        gridLayout_85->addWidget(external_g_l, 0, 0, 1, 1);

        label_112 = new QLabel(scrollAreaWidgetContents_2);
        label_112->setObjectName(QStringLiteral("label_112"));

        gridLayout_85->addWidget(label_112, 0, 2, 1, 1);

        gridLayout_85->setColumnStretch(0, 4);
        gridLayout_85->setColumnStretch(1, 4);
        gridLayout_85->setColumnStretch(2, 2);

        CustomCriteriaGrid->addLayout(gridLayout_85, 10, 1, 1, 1);

        thr_diff_statuslabel2 = new QLabel(scrollAreaWidgetContents_2);
        thr_diff_statuslabel2->setObjectName(QStringLiteral("thr_diff_statuslabel2"));

        CustomCriteriaGrid->addWidget(thr_diff_statuslabel2, 5, 3, 1, 1);

        CustomCriteriaGrid->setColumnStretch(0, 5);
        CustomCriteriaGrid->setColumnStretch(1, 1);
        CustomCriteriaGrid->setColumnStretch(2, 5);
        CustomCriteriaGrid->setColumnStretch(3, 5);

        verticalLayout->addLayout(CustomCriteriaGrid);

        scrollArea->setWidget(scrollAreaWidgetContents_2);
        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 130, 1531, 301));
        tableView = new QTableView(groupBox_6);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(0, 20, 1531, 231));
        checkBox_filterLatest = new QCheckBox(groupBox_6);
        checkBox_filterLatest->setObjectName(QStringLiteral("checkBox_filterLatest"));
        checkBox_filterLatest->setGeometry(QRect(10, 270, 221, 20));
        checkBox_filterLatest->setChecked(true);
        pushButton_addfilter = new QPushButton(groupBox_6);
        pushButton_addfilter->setObjectName(QStringLiteral("pushButton_addfilter"));
        pushButton_addfilter->setGeometry(QRect(230, 270, 131, 22));
        pushButton_export = new QPushButton(groupBox_6);
        pushButton_export->setObjectName(QStringLiteral("pushButton_export"));
        pushButton_export->setGeometry(QRect(370, 270, 121, 22));
        groupBox_7 = new QGroupBox(tab);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(710, 10, 831, 121));
        lineEdit_query = new QLineEdit(groupBox_7);
        lineEdit_query->setObjectName(QStringLiteral("lineEdit_query"));
        lineEdit_query->setGeometry(QRect(20, 50, 791, 22));
        pushButton_getquery = new QPushButton(groupBox_7);
        pushButton_getquery->setObjectName(QStringLiteral("pushButton_getquery"));
        pushButton_getquery->setGeometry(QRect(20, 90, 131, 22));
        label_2 = new QLabel(groupBox_7);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 30, 311, 16));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 10, 751, 831));
        plotNorm = new QCustomPlot(groupBox_4);
        plotNorm->setObjectName(QStringLiteral("plotNorm"));
        plotNorm->setGeometry(QRect(20, 120, 711, 331));
        comboBox_normcurve = new QComboBox(groupBox_4);
        comboBox_normcurve->setObjectName(QStringLiteral("comboBox_normcurve"));
        comboBox_normcurve->setGeometry(QRect(20, 40, 211, 22));
        pushButton_normcurve = new QPushButton(groupBox_4);
        pushButton_normcurve->setObjectName(QStringLiteral("pushButton_normcurve"));
        pushButton_normcurve->setGeometry(QRect(20, 80, 211, 22));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(250, 40, 81, 21));
        lineEdit_bins = new QLineEdit(groupBox_4);
        lineEdit_bins->setObjectName(QStringLiteral("lineEdit_bins"));
        lineEdit_bins->setGeometry(QRect(360, 40, 111, 22));
        pushButton_savepdf = new QPushButton(groupBox_4);
        pushButton_savepdf->setObjectName(QStringLiteral("pushButton_savepdf"));
        pushButton_savepdf->setGeometry(QRect(20, 470, 141, 22));
        plot_VMM_class = new QCustomPlot(groupBox_4);
        plot_VMM_class->setObjectName(QStringLiteral("plot_VMM_class"));
        plot_VMM_class->setGeometry(QRect(20, 540, 341, 261));
        plot_hybrid_class = new QCustomPlot(groupBox_4);
        plot_hybrid_class->setObjectName(QStringLiteral("plot_hybrid_class"));
        plot_hybrid_class->setGeometry(QRect(390, 540, 341, 261));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 520, 161, 16));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(390, 520, 201, 16));
        lineEdit_locationFilter = new QLineEdit(groupBox_4);
        lineEdit_locationFilter->setObjectName(QStringLiteral("lineEdit_locationFilter"));
        lineEdit_locationFilter->setGeometry(QRect(360, 70, 111, 22));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(250, 60, 101, 41));
        label_4->setWordWrap(true);
        listWidget_availableHybrids = new QListWidget(groupBox_4);
        listWidget_availableHybrids->setObjectName(QStringLiteral("listWidget_availableHybrids"));
        listWidget_availableHybrids->setGeometry(QRect(500, 50, 231, 61));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(500, 30, 221, 16));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(250, 100, 101, 16));
        checkBox_filterApply = new QCheckBox(groupBox_4);
        checkBox_filterApply->setObjectName(QStringLiteral("checkBox_filterApply"));
        checkBox_filterApply->setGeometry(QRect(340, 100, 31, 20));
        checkBox_filterApply->setLayoutDirection(Qt::RightToLeft);
        pushButton_2 = new QPushButton(groupBox_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 800, 171, 22));
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(780, 10, 761, 831));
        listWidget = new QListWidget(groupBox_5);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(20, 60, 711, 681));
        pushButton = new QPushButton(groupBox_5);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(160, 30, 171, 22));
        pushButton_removeAllFilters = new QPushButton(groupBox_5);
        pushButton_removeAllFilters->setObjectName(QStringLiteral("pushButton_removeAllFilters"));
        pushButton_removeAllFilters->setGeometry(QRect(340, 30, 151, 22));
        pushButton_storeFilters = new QPushButton(groupBox_5);
        pushButton_storeFilters->setObjectName(QStringLiteral("pushButton_storeFilters"));
        pushButton_storeFilters->setGeometry(QRect(500, 30, 111, 22));
        pushButton_loadFilters = new QPushButton(groupBox_5);
        pushButton_loadFilters->setObjectName(QStringLiteral("pushButton_loadFilters"));
        pushButton_loadFilters->setGeometry(QRect(620, 30, 111, 22));
        pushButton_addfilter_2 = new QPushButton(groupBox_5);
        pushButton_addfilter_2->setObjectName(QStringLiteral("pushButton_addfilter_2"));
        pushButton_addfilter_2->setGeometry(QRect(20, 30, 131, 22));
        tabWidget->addTab(tab_2, QString());
        dbwindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(dbwindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        dbwindow->setStatusBar(statusbar);

        retranslateUi(dbwindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(dbwindow);
    } // setupUi

    void retranslateUi(QMainWindow *dbwindow)
    {
        dbwindow->setWindowTitle(QApplication::translate("dbwindow", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("dbwindow", "Database connection", Q_NULLPTR));
        adressfield->setHtml(QApplication::translate("dbwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:9pt;\">localhost</span></p></body></html>", Q_NULLPTR));
        portfield->setHtml(QApplication::translate("dbwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:9pt;\">5432</span></p></body></html>", Q_NULLPTR));
        portlabel->setText(QApplication::translate("dbwindow", "Port:", Q_NULLPTR));
        adresslabel->setText(QApplication::translate("dbwindow", "Adress:", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("dbwindow", "Connect", Q_NULLPTR));
        dbnamefield->setHtml(QApplication::translate("dbwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:9pt;\">testdb</span></p></body></html>", Q_NULLPTR));
        dbnamelabel->setText(QApplication::translate("dbwindow", "Database:", Q_NULLPTR));
        pushButton_refresh->setText(QApplication::translate("dbwindow", "Refresh", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("dbwindow", "Reload Defaults", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("dbwindow", "Hybrid Details", Q_NULLPTR));
        measurementIDlabel_2->setText(QApplication::translate("dbwindow", "Measurement Type", Q_NULLPTR));
        measurementIDlabel->setText(QApplication::translate("dbwindow", "Measurement ID", Q_NULLPTR));
        pushButton_details->setText(QApplication::translate("dbwindow", "Show Details", Q_NULLPTR));
        pushButton_configdownload->setText(QApplication::translate("dbwindow", "Download Config", Q_NULLPTR));
        pushButton_savePlot->setText(QApplication::translate("dbwindow", "Save PDF", Q_NULLPTR));
        label->setText(QApplication::translate("dbwindow", "Hybrid Class", Q_NULLPTR));
        hybrid_classlabel->setText(QString());
        groupBox_3->setTitle(QApplication::translate("dbwindow", "Custom Criteria ", Q_NULLPTR));
        thr_diff_statuslabel1->setText(QString());
        label_109->setText(QApplication::translate("dbwindow", "mV", Q_NULLPTR));
        noise_o_l->setText(QApplication::translate("dbwindow", "3", Q_NULLPTR));
        noise_g_l->setText(QApplication::translate("dbwindow", "2", Q_NULLPTR));
        pedestalstatuslabel2->setText(QString());
        workingchannelsintlabel->setText(QApplication::translate("dbwindow", "Working Channels internal", Q_NULLPTR));
        threshold_diff_g_l->setText(QApplication::translate("dbwindow", "-14.534", Q_NULLPTR));
        threshold_diff_o_l->setText(QApplication::translate("dbwindow", "-21.416", Q_NULLPTR));
        threshold_diff_o_u->setText(QApplication::translate("dbwindow", "12.992", Q_NULLPTR));
        threshold_diff_g_u->setText(QApplication::translate("dbwindow", "6.11", Q_NULLPTR));
        label_141->setText(QApplication::translate("dbwindow", "mV", Q_NULLPTR));
        adcstatuslabel1->setText(QString());
        vmm2label->setText(QApplication::translate("dbwindow", "VMM 2", Q_NULLPTR));
        internal_o_l->setText(QApplication::translate("dbwindow", "61", Q_NULLPTR));
        internal_g_l->setText(QApplication::translate("dbwindow", "64", Q_NULLPTR));
        label_114->setText(QApplication::translate("dbwindow", "Chs", Q_NULLPTR));
        intchannels2label->setText(QString());
        label_137->setText(QApplication::translate("dbwindow", "ADC Calibration Vertex pos", Q_NULLPTR));
        label_138->setText(QApplication::translate("dbwindow", "Extern", Q_NULLPTR));
        label_139->setText(QApplication::translate("dbwindow", "Intern", Q_NULLPTR));
        tdcstatuslabel1->setText(QString());
        label_128->setText(QApplication::translate("dbwindow", "OK", Q_NULLPTR));
        label_127->setText(QApplication::translate("dbwindow", "Good", Q_NULLPTR));
        label_125->setText(QApplication::translate("dbwindow", "min", Q_NULLPTR));
        label_126->setText(QApplication::translate("dbwindow", "max", Q_NULLPTR));
        label_123->setText(QApplication::translate("dbwindow", "min", Q_NULLPTR));
        label_124->setText(QApplication::translate("dbwindow", "max", Q_NULLPTR));
        adcstatuslabel2->setText(QString());
        noisestatus1label->setText(QString());
        monitoringADC_g_u->setText(QApplication::translate("dbwindow", "0.9", Q_NULLPTR));
        label_107->setText(QString());
        monitoringADC_o_l->setText(QApplication::translate("dbwindow", "0.4", Q_NULLPTR));
        monitoringADC_o_u->setText(QApplication::translate("dbwindow", "1", Q_NULLPTR));
        monitoringADC_g_l->setText(QApplication::translate("dbwindow", "0.5", Q_NULLPTR));
        monitoringADC_g_l_2->setText(QApplication::translate("dbwindow", "0", Q_NULLPTR));
        monitoringADC_g_u_2->setText(QApplication::translate("dbwindow", "100", Q_NULLPTR));
        monitoringADC_o_l_2->setText(QApplication::translate("dbwindow", "0", Q_NULLPTR));
        monitoringADC_o_u_2->setText(QApplication::translate("dbwindow", "200", Q_NULLPTR));
        label_108->setText(QApplication::translate("dbwindow", "mv", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_7->setToolTip(QApplication::translate("dbwindow", "Allowed deviations from the expected threshold for each channel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("dbwindow", "Threshold  Deviation", Q_NULLPTR));
        thresholdstatuslabel1->setText(QString());
        threshold_g_l->setText(QApplication::translate("dbwindow", "15", Q_NULLPTR));
        threshold_o_l->setText(QApplication::translate("dbwindow", "20", Q_NULLPTR));
        label_117->setText(QApplication::translate("dbwindow", "mV", Q_NULLPTR));
        extchannels1label->setText(QString());
        adcvertexstatus1label->setText(QString());
        adcvertexstatus3label->setText(QString());
        label_134->setText(QApplication::translate("dbwindow", "Average TDC range", Q_NULLPTR));
        label_135->setText(QApplication::translate("dbwindow", "Criteria set in code", Q_NULLPTR));
        label_136->setText(QApplication::translate("dbwindow", "Criteria set in code", Q_NULLPTR));
        adccal_bads2->setText(QString());
        adccal_bads4->setText(QString());
        adccurvestatus2label->setText(QString());
        adccurvestatus4label->setText(QString());
        label_118->setText(QApplication::translate("dbwindow", "ADC Calibration Curvature", Q_NULLPTR));
        label_119->setText(QApplication::translate("dbwindow", "Extern", Q_NULLPTR));
        label_120->setText(QApplication::translate("dbwindow", "Intern", Q_NULLPTR));
        label_130->setText(QApplication::translate("dbwindow", "Status of...", Q_NULLPTR));
        intchannels1label->setText(QString());
        extchannels2label->setText(QString());
        noisestatus2label->setText(QString());
        pedestal_o_l->setText(QApplication::translate("dbwindow", "140", Q_NULLPTR));
        label_140->setText(QApplication::translate("dbwindow", "mV", Q_NULLPTR));
        pedestal_o_u->setText(QApplication::translate("dbwindow", "200", Q_NULLPTR));
        pedestal_g_u->setText(QApplication::translate("dbwindow", "190", Q_NULLPTR));
        pedestal_g_l->setText(QApplication::translate("dbwindow", "150", Q_NULLPTR));
        adcrange_o_l->setText(QApplication::translate("dbwindow", "40", Q_NULLPTR));
        label_115->setText(QApplication::translate("dbwindow", "mV", Q_NULLPTR));
        adcrange_g_l->setText(QApplication::translate("dbwindow", "30", Q_NULLPTR));
        adcrange_g_l_ext->setText(QApplication::translate("dbwindow", "30", Q_NULLPTR));
        adcrange_o_l_ext->setText(QApplication::translate("dbwindow", "40", Q_NULLPTR));
        label_116->setText(QApplication::translate("dbwindow", "mV", Q_NULLPTR));
        adcmonitoringlabel->setText(QApplication::translate("dbwindow", "Monitoring ADC Slope", Q_NULLPTR));
        label_121->setText(QApplication::translate("dbwindow", "Monitoring ADC Intercept", Q_NULLPTR));
        label_113->setText(QApplication::translate("dbwindow", "Baseline Noise", Q_NULLPTR));
        adcvertexstatus2label->setText(QString());
        adcvertexstatus4label->setText(QString());
        label_131->setText(QApplication::translate("dbwindow", "ADC Calibration Channel deviation", Q_NULLPTR));
        label_132->setText(QApplication::translate("dbwindow", "Extern", Q_NULLPTR));
        label_133->setText(QApplication::translate("dbwindow", "Intern", Q_NULLPTR));
        adccal_bads1->setText(QString());
        adccal_bads3->setText(QString());
        tdc_g_l->setText(QApplication::translate("dbwindow", "60", Q_NULLPTR));
        tdc_o_l->setText(QApplication::translate("dbwindow", "50", Q_NULLPTR));
        tdc_o_u->setText(QApplication::translate("dbwindow", "110", Q_NULLPTR));
        tdc_g_u->setText(QApplication::translate("dbwindow", "100", Q_NULLPTR));
        label_122->setText(QApplication::translate("dbwindow", "mV", Q_NULLPTR));
        tdcstatuslabel2->setText(QString());
        pedestallabel->setText(QApplication::translate("dbwindow", "Pedestal", Q_NULLPTR));
        vmm1label->setText(QApplication::translate("dbwindow", "VMM 1", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        thresholdlabel->setToolTip(QApplication::translate("dbwindow", "Maximum allowed variation between channel thresholds.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        thresholdlabel->setText(QApplication::translate("dbwindow", "Threshold Variation", Q_NULLPTR));
        thresholdstatuslabel2->setText(QString());
        adccurvestatus1label->setText(QString());
        adccurvestatus3label->setText(QString());
        adcvertex_o_i->setText(QApplication::translate("dbwindow", "34.45", Q_NULLPTR));
        adcvertex_g_i->setText(QApplication::translate("dbwindow", "28.23", Q_NULLPTR));
        label_110->setText(QApplication::translate("dbwindow", "Ch", Q_NULLPTR));
        label_111->setText(QApplication::translate("dbwindow", "Ch", Q_NULLPTR));
        adcvertex_o_e->setText(QApplication::translate("dbwindow", "35.99", Q_NULLPTR));
        adcvertex_g_e->setText(QApplication::translate("dbwindow", "27.28", Q_NULLPTR));
        pedestalstatuslabel1->setText(QString());
        workingchannelsextlabel->setText(QApplication::translate("dbwindow", "Working Channels external", Q_NULLPTR));
        external_o_l->setText(QApplication::translate("dbwindow", "61", Q_NULLPTR));
        external_g_l->setText(QApplication::translate("dbwindow", "64", Q_NULLPTR));
        label_112->setText(QApplication::translate("dbwindow", "Chs", Q_NULLPTR));
        thr_diff_statuslabel2->setText(QString());
        groupBox_6->setTitle(QApplication::translate("dbwindow", "Query Results", Q_NULLPTR));
        checkBox_filterLatest->setText(QApplication::translate("dbwindow", "Show only latest Measurements", Q_NULLPTR));
        pushButton_addfilter->setText(QApplication::translate("dbwindow", "Add Filter", Q_NULLPTR));
        pushButton_export->setText(QApplication::translate("dbwindow", "Export Table", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("dbwindow", "User Query", Q_NULLPTR));
        pushButton_getquery->setText(QApplication::translate("dbwindow", "Query Database", Q_NULLPTR));
        label_2->setText(QApplication::translate("dbwindow", "Enter your SQL-Query below", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("dbwindow", "Database and Hybrid overview", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("dbwindow", "Hybrid Statistics", Q_NULLPTR));
        pushButton_normcurve->setText(QApplication::translate("dbwindow", "getCurve", Q_NULLPTR));
        label_8->setText(QApplication::translate("dbwindow", "Bin Number", Q_NULLPTR));
        lineEdit_bins->setText(QApplication::translate("dbwindow", "50", Q_NULLPTR));
        pushButton_savepdf->setText(QApplication::translate("dbwindow", "Save as PDF", Q_NULLPTR));
        label_9->setText(QApplication::translate("dbwindow", "VMM Class Distribution", Q_NULLPTR));
        label_10->setText(QApplication::translate("dbwindow", "Hybrid Class Distribution", Q_NULLPTR));
        lineEdit_locationFilter->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_4->setToolTip(QApplication::translate("dbwindow", "<html><head/><body><p>Enter location(s) separated by a comma. Entering a location here will list all hybrids at the specified location in the field to the right. If no locations are specified, all Hybrids in the database will be shown.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("dbwindow", "Only list Hybrids from", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_5->setToolTip(QApplication::translate("dbwindow", "<html><head/><body><p>Selecting a Hybrid will show its ranking in the global Hybrid/VMM statistics</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("dbwindow", "Select Hybrid to compare", Q_NULLPTR));
        label_13->setText(QApplication::translate("dbwindow", "Apply Filters", Q_NULLPTR));
        checkBox_filterApply->setText(QString());
        pushButton_2->setText(QApplication::translate("dbwindow", "Save Distributions", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("dbwindow", "Filtering", Q_NULLPTR));
        pushButton->setText(QApplication::translate("dbwindow", "Remove selected Filter", Q_NULLPTR));
        pushButton_removeAllFilters->setText(QApplication::translate("dbwindow", "Remove all Filters", Q_NULLPTR));
        pushButton_storeFilters->setText(QApplication::translate("dbwindow", "Store Filters", Q_NULLPTR));
        pushButton_loadFilters->setText(QApplication::translate("dbwindow", "Load Filters", Q_NULLPTR));
        pushButton_addfilter_2->setText(QApplication::translate("dbwindow", "Add Filter", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("dbwindow", "Hybrid Statistics and Filtering", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dbwindow: public Ui_dbwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBWINDOW_H
