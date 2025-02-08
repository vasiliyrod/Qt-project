#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocale>
#include <QTranslator>

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
    void on_btnClick_clicked();
    void changeLanguage();

private:
    Ui::MainWindow *ui;
    int clickCount;
    QTranslator translator;
    void updateUI();
    QString getSelectedLanguage() const;

    static constexpr const char* CLICK_TEXT = QT_TR_N_NOOP("Currently, %1 clicks have been made");
};
#endif // MAINWINDOW_H
