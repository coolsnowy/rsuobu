#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QtNetwork>
#include <QFileDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void send();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QFile *file;
    QUdpSocket *sender;
    QTimer *timer;
    QString fileName;
    QString ip;

};

#endif // MAINWINDOW_H
