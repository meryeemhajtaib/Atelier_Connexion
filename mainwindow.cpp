#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "emission.h"
#include "dialog_stats.h"
#include "qrcode.h"
#include <QMessageBox>
#include<QIntValidator>
#include<QDate>
#include<QPushButton>
#include<QPdfWriter>
#include<QPainter>
#include<QDesktopServices>
#include <iostream>
#include <fstream>
#include <string>
#include<QtCharts>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_Emission->setModel(E.afficher());
     ui->le_ID_Emission->setValidator(new QIntValidator(100, 9999999, this));
     ui->lineEdit_2->setValidator(new QIntValidator(100, 9999999, this));
     ui->le_Nom->setInputMask("AAAAAAAAAAAAAAAAAAAA");
     ui->lineEdit->setInputMask("AAAAAAAAAAAAAAAAAAAA");
     ui->lenom_mod->setInputMask("AAAAAAAAAAAAAAAAAAAA");
     ui->leanimateur_mod->setInputMask("AAAAAAAAAAAAAAAAAAAA");
     ui->tab_Emission->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_Ajouter_clicked()
{
   int  ID_Emission=ui->le_ID_Emission->text().toInt();
   int Date_emission =ui->lineEdit_2->text().toInt();
    QString Nom=ui->le_Nom->text();
     QString Animateur=ui->lineEdit->text();
    Emission E(ID_Emission, Date_emission, Nom , Animateur );
    bool test=E.ajouter();

    if(test)
         {ui->tab_Emission->setModel(E.afficher());
             QMessageBox::information(nullptr, QObject::tr("Ok"),
                  QObject::tr("Ajout effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);



         }
         else

             QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                  QObject::tr("Ajout non effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


         }



void MainWindow::on_pushButton_clicked()
{
    int ID_Emission =ui->le_ID_Emission_supp->text().toInt();
    bool test=E.supprimer(ID_Emission);
    if(test)
    {ui->tab_Emission->setModel(E.afficher());
       QMessageBox::information(nullptr,QObject::tr("ok"),
                                QObject::tr("suppression effectuee \n"
                                            "click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                               QObject::tr("suppression non effectuee.\n"
                                      "click Cancel to exit."),QMessageBox::Cancel);
}




void MainWindow::on_pb_modifier_clicked()
{


    int ID_Emission=ui->leid_mod->text().toInt();
    int Date_emission=ui->ledate_mod->text().toInt();
    QString Nom=ui->lenom_mod->text();
    QString Animateur=ui->leanimateur_mod->text();


       Emission E(ID_Emission , Date_emission, Nom, Animateur );

       bool test=E.modifier();
       if(test)
       { ui->tab_Emission->setModel(E.afficher());
           QMessageBox::information(nullptr, QObject::tr("ok"),
                                QObject::tr("Modiffication effectué"),QMessageBox::Cancel);

       }
       else
           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                QObject::tr("Modiffication non effectué"),QMessageBox::Cancel);

}



void MainWindow::on_pb_Ajouter_3_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_Emission->setModel(E.tri_id());
}

void MainWindow::on_pb_Ajouter_2_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_Emission->setModel(E.tri_nom());
}

void MainWindow::on_pb_Ajouter_4_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_Emission->setModel(E.tri_animateur());
}

void MainWindow::on_pb_Ajouter_6_clicked()
{
    QPdfWriter pdf("C:/Users/CBE/Desktop/Atelier_Connexion/Liste.pdf");

                     QPainter painter(&pdf);

                     int i = 4000;


                     painter.drawText(3000,1500,"LISTE DES EMISSION");
                     painter.setPen(Qt::blue);
                     painter.setFont(QFont("Arial", 50));
                     painter.drawRect(2700,200,6300,2600);
                     painter.drawRect(0,3000,9600,500);
                     painter.setPen(Qt::black);
                     painter.setFont(QFont("Arial", 9));
                     painter.drawText(300,3300,"ID_EMISSION");
                     painter.drawText(2300,3300,"NOM");
                     painter.drawText(4300,3300,"DATE_EMISSION");
                     painter.drawText(6000,3300,"ANIMATEUR");

                     QSqlQuery query;
                     query.prepare("select * from emission");
                     query.exec();
                     while (query.next())
                     {
                         painter.drawText(300,i,query.value(0).toString());
                         painter.drawText(2300,i,query.value(1).toString());
                         painter.drawText(4300,i,query.value(2).toString());
                         painter.drawText(6300,i,query.value(3).toString());

                         i = i +500;
                     }

                     int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                     if (reponse == QMessageBox::Yes)
                     {
                         QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/CBE/Desktop/Atelier_Connexion/Liste.pdf"));

                         painter.end();
                     }
                     if (reponse == QMessageBox::No)
                     {
                         painter.end();
                     }
}

void MainWindow::on_pb_Ajouter_5_clicked()
{
    Emission E;
        QString text;



            E.clearTable(ui->tab_Emission);
                int id=ui->le_ID_Emission_2->text().toInt();
                E.chercheID(ui->tab_Emission,id);
}

/*void MainWindow::on_pb_stats_clicked()
{
    Dialog_stats stats;
    stats.setModal(true);
    stats.exec();
}*/

void MainWindow::on_qrcode_clicked()
{
    QDesktopServices::openUrl(QUrl("https://app.qr-code-generator.com/manage/?aftercreate=1&count=1"));
        QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png )"));
        if (QString::compare(filename,QString()) !=0)
        {
            QImage image;
            bool valid = image.load(filename);
            if(valid)
            {
                image=image.scaledToWidth(ui->lbl_image_2->width(), Qt::SmoothTransformation);
                        ui->lbl_image_2->setPixmap(QPixmap::fromImage(image));
            }
            else
            {
                //ERROR HANDLING
            }
        }

}

void MainWindow::on_insertimg_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png *.jpeg *.jpg *.bmp *.gif)"));
    QSqlQuery query;
          query.prepare("INSERT INTO IMAGE (IMG) "
                        "VALUES (:LOAD_FILE(filename))");
          query.bindValue(":LOAD_FILE(filename)",  filename);
          //QLabel* x = ui->imagee;
          //x->text();
          //x->(filename);

















      if (QString::compare(filename,QString()) !=0)
      {
          QImage image;
          bool valid = image.load(filename);
          if(valid)
          {
              image=image.scaledToWidth(ui->imagee->width(), Qt::SmoothTransformation);
                      ui->imagee->setPixmap(QPixmap::fromImage(image));
                      query.exec();
          }
          else
          {
              //ERROR HANDLING
          }
      }
}
/*
void MainWindow::on_pb_stats_clicked()
{
    s = new stat_combo();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();
}
*/

void MainWindow::on_pb_stats_clicked()
{
    s = new Dialog_stats();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();
}
