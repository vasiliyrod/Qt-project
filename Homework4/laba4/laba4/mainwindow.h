#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_sendMessageButton_clicked();

    void on_connectButton_clicked();

    void on_disconnectButton_clicked();

    void readData();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    char *symbol;
};
#endif // MAINWINDOW_H
