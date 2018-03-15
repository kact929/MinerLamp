#include "helpdialog.h"
#include "ui_helpdialog.h"

helpDialog::helpDialog(QSettings* settings, QWidget *parent) :
    QDialog(parent),
    _settings(settings),
    ui(new Ui::helpDialog)
{

    ui->setupUi(this);

    setFixedSize(size());

    ui->plainTextEdit->appendHtml("<html>");
    ui->plainTextEdit->appendHtml("<h2>Simple Qt GUI for running ethminer safely.</h2><br>");
    ui->plainTextEdit->appendHtml("It will restart ethminer for you in case of error...");
    ui->plainTextEdit->appendHtml("<u>https://github.com/orkblutt/MinerLamp</u><br>");
    ui->plainTextEdit->appendHtml("You'll need ethminer you can download from:");
    ui->plainTextEdit->appendHtml("<u>https://github.com/ethereum-mining/ethminer</u><br>");
    ui->plainTextEdit->appendHtml("If you want to donate you can at this address:");
    ui->plainTextEdit->appendHtml("<b>0xa07a8c9975145bb5371e8b3c31acb62ad9d0698e</b><br><br>");
    ui->plainTextEdit->appendHtml("<br>Feel free to send me comment at <b>orkblutt@msn.com</b><br>");
    ui->plainTextEdit->appendHtml(QString("Version: <b>" + QApplication::applicationVersion() + "</b>"));
    ui->plainTextEdit->appendHtml("</html>");

    ui->checkBox->setChecked(_settings->value("donate", true).toBool());
}

helpDialog::~helpDialog()
{
    delete ui;
}

void helpDialog::on_pushButtonFinish_clicked()
{
    close();
}

void helpDialog::on_checkBox_clicked(bool checked)
{
    _settings->setValue("donate", checked);
}
