#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialPort = new QSerialPort(this);

    serialPort->setPortName("COM10");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);

    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    if (serialPort->isOpen())
    {
        qDebug() << "Порт уже открыт";
    }
    else
        serialPort->open(QSerialPort::ReadWrite);

}

void MainWindow::on_disconnectButton_clicked()
{
    if (serialPort->isOpen())
    {
        serialPort->close();

    }
    else
        qDebug() << "Порт еще не открыт";

}

void MainWindow::on_sendMessageButton_clicked()
{
    QString input = ui->lineEdit->text();
    serialPort->write(input.toUtf8());
}

void MainWindow::readData()
{
    serialPort->read(this->symbol, 1);
    qDebug() << symbol;
    ui->textEdit->setText(QString(symbol));

    QTimer::singleShot(5000, this, [this]() {
        // Ваш код, который выполнится через 5 секунд
        serialPort->write(this->symbol);
    });

}


