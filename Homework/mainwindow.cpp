#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Введите число от 0 до 100");

    ui->label->setText("00:00");

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString temp = ui->lineEdit->text();
    ui->lineEdit->clear();

    bool isDigit;
    int intTemp = temp.toInt(&isDigit, 10);
    if (isDigit && intTemp >= 0 && intTemp <= 100)
    {
        seconds = intTemp;
        timer->start(1000);
        //QTimer::
        //QTimer::singleShot(intTemp, ui->label, &QWidget::hide);
    }

}

void MainWindow::slotTimerAlarm()
{
    /* Ежесекундно обновляем данные по текущему времени
     * Перезапускать таймер не требуется
     * */
    int minutes = 0;
    int tempSeconds = 0;

    minutes = seconds / 60;
    tempSeconds = seconds % 60;
    std::string stringTime = "0" + std::to_string(minutes) + ":" + std::to_string(tempSeconds);
    const char *cstr = stringTime.c_str();
    ui->label->setText(cstr);

    seconds -= 1;

    if (seconds == 0)
    {
        timer->stop();

    }
}
