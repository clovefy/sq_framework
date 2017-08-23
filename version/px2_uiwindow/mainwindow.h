#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data_agent.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent,data_agent* input);
    ~MainWindow();

    void paintEvent(QPaintEvent *);

    data_agent* mdataagent;

public:
    void paintDod();
    void paintSeg();
    void paintLoc();
    void paintPld();
    void paintRecord();
    void paintLdw();

    void paintStatus();

private slots:

    void on_record_status_clicked();

    void on_actionOpenfile_triggered();

private:
    Ui::MainWindow *ui;

    //loc res
    QImage mlocbg_png;
    QImage mloccar_png;
    bool mrecordflag;

};

#endif // MAINWINDOW_H
