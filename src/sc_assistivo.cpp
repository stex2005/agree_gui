#include "../include/agree_gui/sc_assistivo.h"
#include "ui_sc_assistivo.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/main_window.hpp"
#include "../include/agree_gui/paginaprincipale.h"
#include <QMessageBox>
QString dati::patologia;
int joy;

int rect1=0;
int rect2=0;
int rect3=0;


int dati::controllo_voc;


sc_assistivo::sc_assistivo(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::sc_assistivo)
{
  ui->setupUi(this);
  //creo il timer per cambiare il colore dei rettangoli del joystick
  timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()), this, SLOT (myfunction()));
  timer->start(5000);
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

void sc_assistivo::myfunction()
{
  col1 = Qt::green;

 // update();


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

     }


}

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
{ dati::nuovo_utente = 0;
 ui->stackedWidget->setCurrentWidget(ui->page_config);
 if (dati::nuovo_utente==0)
 {
   QSqlQuery sel_mod;

   sel_mod.prepare("select Sesso, Patologia, Lato_dominante, Lunghezza_braccio, Lunghezza_avambraccio, uROM1_min, uROM1_max, uROM2_min, uROM2_max,uROM3_min, uROM3_max,uROM4_min, uROM4_max,uROM5_min, uROM5_max from Utenti_ass where usernameass = '"+dati::username+"' ");
   if (sel_mod.exec()){
   while (sel_mod.next()) {
  //  sel_mod.value(0).toString();
  //  sel_mod.value(2).toString();
     QString patologia = sel_mod.value(1).toString();

     ui->lineEdit_patologia->setText(dati::patologia);
     ui->lineEdit_la->setText(sel_mod.value(4).toString());
     ui->lineEdit_lb->setText(sel_mod.value(3).toString());
     ui->lineEdit_rom1_min->setText(sel_mod.value(5).toString());
     ui->lineEdit_rom1_max->setText(sel_mod.value(6).toString());
     ui->lineEdit_rom2_min->setText(sel_mod.value(7).toString());
     ui->lineEdit_rom2_max->setText(sel_mod.value(8).toString());
     ui->lineEdit_rom3_min->setText(sel_mod.value(9).toString());
     ui->lineEdit_rom3_max->setText(sel_mod.value(10).toString());
     ui->lineEdit_rom4_min->setText(sel_mod.value(11).toString());
     ui->lineEdit_rom4_max->setText(sel_mod.value(12).toString());
     ui->lineEdit_rom5_min->setText(sel_mod.value(13).toString());
     ui->lineEdit_rom5_max->setText(sel_mod.value(14).toString());
   }
   }
   else{qDebug()<<sel_mod.lastError();}




 }

}
void sc_assistivo::paintEvent(QPaintEvent *event) {

 if(joy==1){
  QPainter prova1(this);
  QPainter prova2(this);
  QPainter prova3(this);
  QPainter prova4(this);
  QPainter prova5(this);
  QBrush colore(Qt::gray);
  QBrush colore1(Qt::cyan);
  QBrush colore2(Qt::green);

  prova1.drawRect(QRect (500,120,200,100)); //up
  prova1.fillRect(QRect (500,120,200,100), col1);
  prova2.fillRect(QRect(500,500,200,100), colore1);
  prova4.fillRect(QRect(150,300,200,100), colore1);
    prova5.fillRect(QRect(850,300,200,100), colore1);
  rect1=1;
   update();

  //prova1.drawText("spingere il joystick verso l'alto");
  prova2.drawRect(QRect(500,500,200,100));  //down
  if (rect1==1) {
    rect2=1;
  prova2.fillRect(QRect(500,500,200,100), col1);
  // update();
  }
  prova3.drawRect(QRect(500,300,200,100)); // center
  prova3.fillRect(QRect(500,300,200,100), colore);

  prova4.drawRect(QRect(150,300,200,100));  //left
  if(rect2==1){
    rect3=1;
  prova4.fillRect(QRect(150,300,200,100), col1);
   //update();
  }
  prova5.drawRect(QRect(850,300,200,100));  //right
  if(rect3==1){
  prova5.fillRect(QRect(850,300,200,100), col1);
   //update();
}
}

 }


void sc_assistivo::on_pushButton_joy_clicked()
{
     joy = 1;
     ui->stackedWidget->setCurrentWidget(ui->page_joy);
}
