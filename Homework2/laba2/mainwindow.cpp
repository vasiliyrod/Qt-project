#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), clickCount(0)
{
    ui->setupUi(this);

    ui->radioRussian->setChecked(true);
    changeLanguage();

    connect(ui->radioEnglish, &QRadioButton::clicked, this, &MainWindow::changeLanguage);
    connect(ui->radioRussian, &QRadioButton::clicked, this, &MainWindow::changeLanguage);
    connect(ui->radioGerman, &QRadioButton::clicked, this, &MainWindow::changeLanguage);

    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnClick_clicked()
{
    clickCount++;
    updateUI();
}

void MainWindow::changeLanguage()
{
    QString langCode = getSelectedLanguage();

    QString qmPath = "app_" + langCode + ".qm";

    if (translator.load(qmPath)) {
        qDebug() << "Перевод успешно загружен!";
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
        updateUI();
    } else {
        qDebug() << "Ошибка загрузки перевода! Файл не найден.";
    }
}

void MainWindow::updateUI()
{
    ui->btnClick->setText(tr("Currently, %1 clicks have been made").arg(clickCount));
    QLocale locale(getSelectedLanguage());
    ui->lblCountry->setText(locale.nativeCountryName());
    ui->textEdit->setText(locale.toString(12345.67, 'f', 2));
}

QString MainWindow::getSelectedLanguage() const
{
    if (ui->radioRussian->isChecked()) return "ru";
    if (ui->radioGerman->isChecked()) return "de";
    return "en";
}
