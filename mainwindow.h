#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>

#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QMainWindow>
#include "emission.h"
#include <QtCharts>
#include "dialog_stats.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);


    ~MainWindow();

private slots:


    void on_pb_Ajouter_clicked();



    void on_pushButton_clicked();





    void on_pb_modifier_clicked();

    void on_pb_Ajouter_3_clicked();

    void on_pb_Ajouter_2_clicked();

    void on_pb_Ajouter_4_clicked();

    void on_pb_Ajouter_6_clicked();

    void on_pb_Ajouter_5_clicked();

    void on_pb_stats_clicked();

    void on_qrcode_clicked();

    void on_insertimg_clicked();

   // void on_tabWidget_currentChanged(int index);

   // void on_stats_clicked();


private:

    Ui::MainWindow *ui;
    Emission E;
    Dialog_stats *s;


};

#endif // MAINWINDOW_H
