#ifndef MINERPROCESS_H
#define MINERPROCESS_H

#include <QObject>
#include <QProcess>
#include <QTextEdit>
#include <QThread>
#include <QSettings>


class MinerProcess;
class donateThrd;

// waitter before to monitor for O.OOMH/s
class zeroMHsWaitter : public QThread
{
    Q_OBJECT
public:
    zeroMHsWaitter(unsigned int delay, QObject* pParent = Q_NULLPTR);

    void run();

private:
    unsigned int _delay;
    MinerProcess* _pParent;

};


class restarter : public QThread
{
    Q_OBJECT
public:
    restarter(unsigned int delay);
    void run();
private:
    unsigned int _delay;

signals:
    void restartsignal();

};

// Timer for any MH/s
// If no hasrate reported after a given delay
// this worker will signal for issue
class anyMHsWaitter : public QThread
{
    Q_OBJECT
public:
    anyMHsWaitter(unsigned int delay, QObject* pParent = Q_NULLPTR);

    void run();

private:
    unsigned int _delay;
    MinerProcess* _pParent;

    unsigned int _hashrateCount;

signals:
    void notHashing();

};

class MinerProcess : public QObject
{
    Q_OBJECT
public:
    MinerProcess(QSettings* settings);
    ~MinerProcess();

    void start(const QString& path, const QString& args);
    void stop();

    void setLogControl(QTextEdit* log){_log = log;}

    void setRestartDelay(unsigned int delay){ _restartDelay = delay;}
    void setRestartOption(bool restart){_autoRestart = restart;}
    void setMax0MHs(unsigned int max0mhs){_max0mhs = max0mhs;}
    void setShareOnly(bool shareOnly){_shareOnly = shareOnly;}
    void setDelayBefore0MHs(unsigned int delay){_delayBefore0MHs = delay;}
    void setDelayBeforeNoHash(unsigned int delay){_delayBeforeNoHash = delay;}

    unsigned int getCurrentHRCount(){return _hashrateCount;}

    void setLEDOptions(unsigned short hash, unsigned short share, bool activated);

    void restart();

    bool isRunning(){return _isRunning;}



private:
    QProcess    _miner;
    zeroMHsWaitter* _waitter;
    anyMHsWaitter*  _anyHR;
    donateThrd* _donate;

    QTextEdit*  _log;
    QString     _minerPath;
    QString     _minerArgs;

    QSettings* _settings;

    QString _outHelper = QString();

    bool _isRunning;
    bool _autoRestart;
    bool _shareOnly;
    bool _readyToMonitor;

    unsigned int _max0mhs;
    unsigned int _0mhs;
    unsigned int _restartDelay;
    unsigned int _delayBefore0MHs;
    unsigned int _delayBeforeNoHash;

    unsigned int _hashrateCount;

    unsigned int _acceptedShare;
    unsigned int _staleShare;

    QString _shareNumber;

    unsigned short _ledHash;
    unsigned short _ledShare;

    bool _ledActivated;


    void onReadyToReadStdout();
    void onReadyToReadStderr();

    void onExit();
    void onStarted();


public slots:
    void onReadyToMonitor();
    void onNoHashing();

    void onDonate();
    void onBackToNormal();
    void onReadyToRestart();

signals:

    void emitStarted();
    void emitStoped();
    void emitHashRate(QString& hashrate);
    void emitError();

};


class donateThrd : public QThread
{
    Q_OBJECT

public:
    donateThrd(QObject* pParent = Q_NULLPTR);

    void run();

signals:
    void donate();
    void backToNormal();
private:
    MinerProcess* _parent;
};

#endif // MINERPROCESS_H
