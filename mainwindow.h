#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QThread>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QDateTimeAxis>
#include <QTimer>

#include "minerprocess.h"
#include "highlighter.h"
#include "nanopoolapi.h"
#include "nvapi.h"
#include "nvidiaapi.h"
#include "amdapi_adl.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class autoStart : public QThread
{
    Q_OBJECT
public:
    autoStart(QObject* pParent = Q_NULLPTR);

    void run();

signals:

    void readyToStartMiner();
};



class nvMonitorThrd : public QThread
{
    Q_OBJECT
public:
    nvMonitorThrd(QObject* = Q_NULLPTR);

    void run();

signals:

    void gpuInfoSignal(unsigned int gpucount
                       , unsigned int maxgputemp
                       , unsigned int mingputemp
                       , unsigned int maxfanspeed
                       , unsigned int minfanspeed
                       , unsigned int maxmemclock
                       , unsigned int minmemclock
                       , unsigned int maxgpuclock
                       , unsigned int mingpuclock
                       , unsigned int maxpowerdraw
                       , unsigned int minpowerdraw
                       , unsigned int totalpowerdraw);

};

class amdMonitorThrd : public QThread
{
    Q_OBJECT
public:
    amdMonitorThrd(QObject* = Q_NULLPTR);

    void run();

signals:

    void gpuInfoSignal(unsigned int gpucount
                       , unsigned int maxgputemp
                       , unsigned int mingputemp
                       , unsigned int maxfanspeed
                       , unsigned int minfanspeed
                       , unsigned int maxmemclock
                       , unsigned int minmemclock
                       , unsigned int maxgpuclock
                       , unsigned int mingpuclock
                       , unsigned int maxpowerdraw
                       , unsigned int minpowerdraw
                       , unsigned int totalpowerdraw);
private:
    amdapi_adl* _amd;

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setVisible(bool visible) Q_DECL_OVERRIDE;
    void startMiner();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void setIcon();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    void createActions();
    void createTrayIcon();
    void setupEditor();
    void setupToolTips();
    void loadParameters();
    void saveParameters();


    nvidiaAPI* _nvapi;
    void applyOC();




private slots:

    void on_pushButton_clicked();
    void on_spinBoxMax0MHs_valueChanged(int arg1);
    void on_spinBoxDelay_valueChanged(int arg1);
    void on_checkBoxOnlyShare_clicked(bool checked);
    void on_pushButtonHelp_clicked();
    void on_spinBoxDelay0MHs_valueChanged(int arg1);
    void onReadyToStartMiner();

    void onNvMonitorInfo(unsigned int gpucount
                         , unsigned int maxgputemp
                         , unsigned int mingputemp
                         , unsigned int maxfanspeed
                         , unsigned int minfanspeed
                         , unsigned int maxmemclock
                         , unsigned int minmemclock
                         , unsigned int maxgpuclock
                         , unsigned int mingpuclock
                         , unsigned int maxpowerdraw
                         , unsigned int minpowerdraw
                         , unsigned int totalpowerdraw
                         );

    void onAMDMonitorInfo(unsigned int gpucount
                          , unsigned int maxgputemp
                          , unsigned int mingputemp
                          , unsigned int maxfanspeed
                          , unsigned int minfanspeed
                          , unsigned int maxmemclock
                          , unsigned int minmemclock
                          , unsigned int maxgpuclock
                          , unsigned int mingpuclock
                          , unsigned int maxpowerdraw
                          , unsigned int minpowerdraw
                          , unsigned int totalpowerdraw
                          );

    void on_pushButtonOC_clicked();


    void onHelp();
    void on_groupBoxWatchdog_clicked(bool checked);

    void on_spinBoxDelayNoHash_valueChanged(int arg1);

    void on_pushButtonPool_clicked(bool checked);

    void on_pushButtonShowHideLog_clicked(bool checked);

    void on_pushButtonDisplayPoolStats_clicked();

    void onBalance(double balance);
    void onPoolUserInfo(double userBalance
                        , double currentCalcultatedHashRate
                        , double averageHashRate1H
                        , double averageHashRate3H
                        , double averageHashRate6H
                        , double averageHashRate12H
                        , double averageHashRate24H
                        );

    void on_pushButtonEthminerBrowser_clicked();

    void onHrChartTimer();

private:

    void onMinerStarted();
    void onMinerStoped();
    void onHashrate(QString& hashrate);
    void onError();

    const QColor getTempColor(unsigned int temp);

    Ui::MainWindow *ui;
    MinerProcess* _process;
    QSettings*  _settings;
    QIcon*       _icon;

    bool _isMinerRunning;
    bool _isStartStoping;

    unsigned int _errorCount;

    QSystemTrayIcon* _trayIcon;
    QMenu* _trayIconMenu;

    QAction* _minimizeAction;
    QAction* _maximizeAction;
    QAction* _restoreAction;
    QAction* _quitAction;
    QAction* _helpAction;

    Highlighter* _highlighter;

    QChart* _chart;
    QLineSeries* _series;
    QDateTimeAxis *_axisX;

    QTimer _hrChartTimer;

    double _currentHashRate = 0.0;
    double _maxChartHashRate = 0.0;
    int _plotsCntr = 0;

    //QThreads
    autoStart* _starter;

    nvMonitorThrd* _nvMonitorThrd;

    amdMonitorThrd* _amdMonitorThrd;

    nanopoolAPI* _nano;
};

#endif // MAINWINDOW_H
