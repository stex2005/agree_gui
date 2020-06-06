#include "../include/agree_gui/sc_assistivo.h"
#include "ui_sc_assistivo.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/main_window.hpp"
#include "../include/agree_gui/paginaprincipale.h"
#include <QMessageBox>
QString dati::patologia;

int dati::controllo_voc;


sc_assistivo::sc_assistivo(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::sc_assistivo)
{
  ui->setupUi(this);

 //QSqlDatabase::database();

  QSqlQuery  qry3;
   qry3.prepare("select Nome, Cognome from Users where username = '"+dati::username+"' " );
   qry3.exec();
   while(qry3.next()){
      ui->label_utente->setText(qry3.value(0).toString() + " " +  qry3.value(1).toString());

 }
   qDebug() << dati::nuovo_utente;
if(dati::nuovo_utente==1) ui->stackedWidget->setCurrentWidget(ui->page_config);
else if(dati::nuovo_utente==0) ui->stackedWidget->setCurrentWidget(ui->page_2);
}

sc_assistivo::~sc_assistivo()
{
  delete ui;
}
void sc_assistivo::on_pushButton_salva_clicked()
{

  QString   sesso, latodom, lb, la,ROM1_min, ROM1_max, ROM2_min, ROM2_max, ROM3_min, ROM3_max, ROM4_min, ROM4_max, ROM5_min, ROM5_max;
  QString user;
  user = dati::username;
    dati::patologia = ui->lineEdit_patologia->text();
    sesso = ui->comboBox_sesso->currentText();
    latodom = ui->comboBox_latodom->currentText();
    lb = ui->lineEdit_lb->text();
    la= ui->lineEdit_la->text();
    ROM1_min = ui->lineEdit_rom1_min->text();
    ROM1_max = ui->lineEdit_rom1_max->text();
    ROM2_min = ui->lineEdit_rom2_min->text();
    ROM2_max = ui->lineEdit_rom2_max->text();
    ROM3_min = ui->lineEdit_rom3_min->text();
    ROM3_max = ui->lineEdit_rom3_max->text();
    ROM4_min = ui->lineEdit_rom4_min->text();
    ROM4_max = ui->lineEdit_rom4_max->text();
    ROM5_min = ui->lineEdit_rom5_min->text();
    ROM5_max = ui->lineEdit_rom5_max->text();
     QSqlQuery prova;
     prova.prepare("update Utenti_ass set Sesso = '"+sesso+"', Patologia = '"+dati::patologia+"', Lato_dominante= '"+latodom+"', Lunghezza_braccio = '"+lb+"', Lunghezza_avambraccio = '"+la+"', uROM1_min= '"+ROM1_min+"', uROM1_max = '"+ROM1_max+"', uROM2_min= '"+ROM2_min+"', uROM2_max = '"+ROM2_max+"', uROM3_min= '"+ROM3_min+"', uROM3_max = '"+ROM3_max+"', uROM4_min= '"+ROM4_min+"', uROM4_max = '"+ROM4_max+"', uROM5_min= '"+ROM5_min+"', uROM5_max = '"+ROM5_max+"' where usernameass = '"+user+"'");
     prova.exec();
     if(prova.exec())
     {     QMessageBox::information(this, tr("done"), tr("done"));
       ui->stackedWidget->setCurrentWidget(ui->page_2);
     }
     else { qDebug()<<prova.lastError().text();

     }}

void sc_assistivo::on_pushButton_home_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void sc_assistivo::on_pushButton_vocale_clicked()
{
  QMessageBox messageBox(QMessageBox::Question, tr("Controllo Vocale"), tr("Si è scelto di utilizzare il controllo vocale. Confermare?"), QMessageBox::Yes | QMessageBox::No, this);
      messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
      messageBox.setButtonText(QMessageBox::No, tr("No"));
      if (messageBox.exec() ==QMessageBox::Yes)
      {
       //messaggio ros per il controllo vocale

        dati::controllo_voc=1;

      }
      else if(messageBox.exec() == QMessageBox::No)
      {
       dati::controllo_voc = 0;
      }
}

void sc_assistivo::on_pushButton_modifica_clicked()
{

}
