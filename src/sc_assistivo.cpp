#include "../include/agree_gui/sc_assistivo.h"
#include "ui_sc_assistivo.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/main_window.hpp"
#include "../include/agree_gui/paginaprincipale.h"
#include <QMessageBox>

QString dati::patologia;

sc_assistivo::sc_assistivo(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::sc_assistivo)
{
  ui->setupUi(this);

  QSqlDatabase mydb3 = QSqlDatabase::database();
  QSqlQuery * qry3 = new QSqlQuery(mydb3);

   qry3 -> prepare("select Nome, Cognome from Users where username = '"+dati::username+"' " );
   qry3 -> exec();
   while(qry3->next()){

      ui->label_utente->setText(qry3->value(0).toString() + " " +  qry3->value(1).toString());
 }
   if (!mydb3.open())
      ui->label_provaconn-> setText("Database non connesso");

      else

      ui->label_provaconn ->setText("Database connesso...");
//   QSqlQuery prova;
//   prova.prepare("insert into Utenti_ass (username, Nome, Cognome, DataNascita) values ('"+dati::username+"', '"+dati::Nome+"', '"+dati::Cognome+"', '"+dati::Data+"')");
//   prova.exec();
//   if (!prova.exec())
//   {
//        qDebug()<< prova.lastError().text();

//   }

//     else {
//     QMessageBox::information(this, tr("done"), tr("done"));

//   }


}


sc_assistivo::~sc_assistivo()
{
  delete ui;
}

void sc_assistivo::on_pushButton_salva_clicked()
{

   // QString   sesso, latodom, lb, la,ROM1_min, ROM1_max, ROM2_min, ROM2_max, ROM3_min, ROM3_max, ROM4_min, ROM4_max, ROM5_min, ROM5_max;
//    dati::patologia = ui->lineEdit_patologia->text();
//    sesso = ui->comboBox_sesso->currentText();
//    latodom = ui->comboBox_latodom->currentText();
//    lb = ui->lineEdit_lb->text();
//    la= ui->lineEdit_la->text();
//    ROM1_min = ui->lineEdit_rom1_min->text();
//    ROM1_max = ui->lineEdit_rom1_max->text();
//    ROM2_min = ui->lineEdit_rom2_min->text();
//    ROM2_max = ui->lineEdit_rom2_max->text();
//    ROM3_min = ui->lineEdit_rom3_min->text();
//    ROM3_max = ui->lineEdit_rom3_max->text();
//    ROM4_min = ui->lineEdit_rom4_min->text();
//    ROM4_max = ui->lineEdit_rom4_max->text();
//    ROM5_min = ui->lineEdit_rom5_min->text();
//    ROM5_max = ui->lineEdit_rom5_max->text();
//    int band = 1;
//    if (band ==1) {

//    QSqlQuery demo; ;
//   prova.prepare("insert into Utenti_ass (Patologia) values ('"+patologia+"') where usernameass = '"+dati::username+"'");
//   demo.prepare ("update Utenti_ass set Patologia = '"+dati::patologia+"' where usernameass = '"+dati::username+"'");
//  demo.exec();
//    if (demo.exec())
//    {

//        QMessageBox::information(this, tr("done"), tr("done"));
//    }

//      else {
//        qDebug()<< demo.lastError().text();
//        qDebug()<< dati::patologia;

//      }



     QSqlQuery prova;
     prova.prepare("insert into Utenti_ass (Patologia) values ('"+dati::patologia+"')");
     prova.exec();

       QMessageBox::information(this, tr("done"), tr("done"));

     }















