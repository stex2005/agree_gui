#include "../include/agree_gui/sc_assistivo.h"
#include "ui_sc_assistivo.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/main_window.hpp"
#include "../include/agree_gui/paginaprincipale.h"
#include <QMessageBox>
QString dati::patologia;
int joy;
int contatore= 0;
int rett=0;

int dati::controllo_voc, dati::controllo_joy, dati::controllo_gomito;


sc_assistivo::sc_assistivo(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::sc_assistivo)
{
  ui->setupUi(this);
ros::NodeHandle n;
chatter_publisher = n.advertise<std_msgs::String>("/chatter", 1000);
  //creo il timer per cambiare il colore dei rettangoli del joystick
 timer = new QTimer(this);
 timer1 = new QTimer(this);
 timer2 = new QTimer(this);
 timer3 = new QTimer(this);
 timer4 = new QTimer(this);



  connect(timer,SIGNAL(timeout()), this, SLOT (myfunction()));
  connect(timer1,SIGNAL(timeout()), this, SLOT (myfunction1()));
  connect(timer2,SIGNAL(timeout()), this, SLOT (myfunction2()));
  connect(timer3,SIGNAL(timeout()), this, SLOT (myfunction3()));
   connect(timer4,SIGNAL(timeout()), this, SLOT (myfunction4()));

 // timer->start(5000);
 //QSqlDatabase::database();

  QSqlQuery  qry3;
   qry3.prepare("select Nome, Cognome from Users where username = '"+dati::username+"' " );
   qry3.exec();
   while(qry3.next()){
      ui->label_utente->setText(qry3.value(0).toString() + " " +  qry3.value(1).toString());

 }
   qDebug() << dati::nuovo_utente;
if(dati::nuovo_utente==1) ui->stackedWidget->setCurrentWidget(ui->page_config);
else if(dati::nuovo_utente==0) ui->stackedWidget->setCurrentWidget(ui->page_prima);
}

sc_assistivo::~sc_assistivo()
{
  delete ui;
}

void sc_assistivo::myfunction() //up
{
  col1 = Qt::green; //up
  ui->label_istr->setText("Spingere il joystick verso l'alto ");



update();


     qDebug()<< "timer...";

     }
void sc_assistivo::myfunction1() //down

{ timer->stop();
  ui->label_istr->setText("Spingere il joystick verso il basso ");

  col1 = Qt::cyan;
  col2 = Qt::green;

update();

     qDebug()<< "timer1...";


     }
void sc_assistivo::myfunction2() //left
{ timer1->stop();
  ui->label_istr->setText("Spingere il joystick verso destra ");

  col1= Qt::cyan;
  col2= Qt::cyan;
  col3 = Qt::green;




update();

     qDebug()<< "timer2...";

     }
void sc_assistivo::myfunction3() //right
{ ui->label_istr->setText("Spingere il joystick verso sinistra ");
 timer2->stop();
 col1= Qt::cyan;
 col2= Qt::cyan;
 col3 = Qt::cyan;
 col4 = Qt::green;


update();

     qDebug()<< "timer3...";

     }
void sc_assistivo::myfunction4() {
  timer3->stop();

  col4 = Qt::cyan;
 ui->label_istr->setText("Se sei soddisfatto della configurazione premi Salva, \n in caso contrario premi Configura");
  qDebug()<< "timer4...";
  update();
}



// // update();



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
     {     QMessageBox::information(this, tr("Salvato"), tr("Modifiche salvate correttamente"));
       ss_rom << "ho effettuato la configurazione dei ROM" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
       msg.data = ss_rom.str();
     chatter_publisher.publish(msg);
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
{       QMessageBox controllovoc;
        controllovoc.setText(tr("Si è scelto di utilizzare il controllo vocale per la sessione corrente.Confermare?"));
        QAbstractButton* pButtonYes = controllovoc.addButton(tr("Conferma"), QMessageBox::YesRole);
        QAbstractButton* pButtonNo =  controllovoc.addButton(tr("No"), QMessageBox::NoRole);
        controllovoc.exec();
        if(controllovoc.clickedButton()==pButtonYes)
//  QMessageBox messageBox(QMessageBox::Question, tr("Controllo Vocale"), tr("Si è scelto di utilizzare il controllo vocale. Confermare?"), QMessageBox::Yes | QMessageBox::No, this);
//      messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
//      messageBox.setButtonText(QMessageBox::No, tr("No"));
//      if (messageBox.exec() ==QMessageBox::Yes)
      {
       //messaggio ros per il controllo vocale

        dati::controllo_voc=1;
        ss_voc << "ho effettuato la configurazione dei ROM" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
        msg.data = ss_voc.str();
      chatter_publisher.publish(msg);

      }
 else if(controllovoc.clickedButton()==pButtonNo)      {
       dati::controllo_voc = 0;
      }
}


void sc_assistivo::paintEvent(QPaintEvent *event) {
  QPainter prova1(this);
  QPainter prova2(this);
  QPainter prova3(this);
  QPainter prova4(this);
  QPainter prova5(this);
  QBrush colore(Qt::gray);

 if(joy==1){

  QBrush colore(Qt::gray);

 //creo i rettangoli
  prova1.drawRect(QRect (500,120,200,100)); //up
  prova2.drawRect(QRect(500,500,200,100));  //down
  prova3.drawRect(QRect(500,300,200,100)); // center
  prova4.drawRect(QRect(150,300,200,100));  //left
  prova5.drawRect(QRect(850,300,200,100));  //right
  //setto i rettangoli del colore di defautl

  prova3.fillRect(QRect(500,300,200,100), colore);
  prova1.fillRect(QRect (500,120,200,100), col1); // up
  prova2.fillRect(QRect(150,300,200,100), col4); //left
  prova4.fillRect(QRect(850,300,200,100), col3); //right
  prova5.fillRect(QRect(500,500,200,100), col2); // down

}
 if(joy==2){
   prova1.eraseRect(QRect (500,120,200,100));
   prova2.eraseRect(QRect(500,500,200,100));  //down
   prova3.eraseRect(QRect(500,300,200,100)); // center
   prova4.eraseRect(QRect(150,300,200,100));  //left
   prova5.eraseRect(QRect(850,300,200,100));

 }

 }



void sc_assistivo::on_pushButton_joy_clicked()
{
     joy = 1;
     timer->start(5000);
     timer1->start(10000);
     timer2->start(15000);
     timer3->start(20000);
     timer4->start(25000);


     ui->stackedWidget->setCurrentWidget(ui->page_joy);


}

void sc_assistivo::on_pushButton_salva_2_clicked()
{
    //mandero i parametri con ros e salverò i dati nel db
     ui->label_istr->setText("Seguire le istruzioni che compariranno a Schermo");
     ui->stackedWidget->setCurrentWidget(ui->page_2);
     joy=2;
     ss_joy_conf << "ho effettuato la configurazione dei ROM" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
     msg.data = ss_joy_conf.str();
   chatter_publisher.publish(msg);

}

void sc_assistivo::on_pushButton_configura_clicked()
{ ui->label_istr->setText("Seguire le istruzioni che compariranno a Schermo");
  timer->start(5000);
  timer1->start(10000);
  timer2->start(16000);
  timer3->start(21000);
  timer4->start(26000);
  joy =1;
}

void sc_assistivo::on_pushButton_joystick_clicked()
{  QMessageBox controllojoy;
   controllojoy.setText(tr("Si è scelto di utilizzare il controllo vocale per la sessione corrente.Confermare?"));
   QAbstractButton* pButtonYes = controllojoy.addButton(tr("Conferma"), QMessageBox::YesRole);
   QAbstractButton* pButtonNo =  controllojoy.addButton(tr("No"), QMessageBox::NoRole);
   controllojoy.exec();
   if(controllojoy.clickedButton()==pButtonYes)
//  QMessageBox messageBox(QMessageBox::Question, tr("Controllo con Joystick"), tr("Si è scelto di utilizzare il controllo vocale. Confermare?"), QMessageBox::Yes | QMessageBox::No, this);
//    messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
//    messageBox.setButtonText(QMessageBox::No, tr("No"));
//    if (messageBox.exec() ==QMessageBox::Yes)
    {
     //messaggio ros per il controllo vocale

      dati::controllo_joy=1;
      ss_joy << "ho selezionato il controllo con il Joystick" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
      msg.data = ss_joy.str();
    chatter_publisher.publish(msg);


    }
    else if(controllojoy.clickedButton()==pButtonNo)
    {
     dati::controllo_joy = 0;
    }

}

void sc_assistivo::on_pushButton_gomito_clicked()

{ QMessageBox controllogom;
  controllogom.setText(tr("Si è scelto di controllare la rotazione del gomito.Confermare?"));
  QAbstractButton* pButtonYes = controllogom.addButton(tr("Conferma"), QMessageBox::YesRole);
  QAbstractButton* pButtonNo =  controllogom.addButton(tr("No"), QMessageBox::NoRole);
  controllogom.exec();
  if(controllogom.clickedButton()==pButtonYes)
//  QMessageBox messageBox(QMessageBox::Question, tr("Controllo Rotazione del Gomito"), tr("Si è scelto di controllare la rotazione del gomito. Confermare?"), QMessageBox::Yes | QMessageBox::No, this);
//   messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
//   messageBox.setButtonText(QMessageBox::No, tr("No"));
//   if (messageBox.exec() ==QMessageBox::Yes)
   {
    //messaggio ros per il controllo vocale

     dati::controllo_gomito=1;
     ss_elb_rot << "ho selezionato la rotazione del gomito" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
     msg.data = ss_elb_rot.str();
   chatter_publisher.publish(msg);


   }
   else if(controllogom.clickedButton()==pButtonNo)
   {
    dati::controllo_gomito = 0;
   }

}

void sc_assistivo::on_pushButton_indietro_single_joint_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}



void sc_assistivo::on_pushButton_salva_single_joint_clicked()
{
    bool flex_spalla = 0, adbu_add_spall=0, rot_spalla = 0, gomito=0, polso =0;
    QString single_joint;

    if(ui->radioButton_flex_est_spalla->isChecked())
    {
      flex_spalla=1;
      single_joint = " Flessione/Estensione della Spalla";

    }
    else if(ui->radioButton_abdu_add_spalla->isChecked()) {

      adbu_add_spall=1;
      single_joint= "Adduzione/Abduzione della Spalla";
    }
    else if (ui->radioButton_rot_spalla->isChecked()) {

      rot_spalla=1;
      single_joint = "Rotazione Interna ed Esterna della Spalla";
    }
    else if (ui->radioButton_flex_est_gomito->isChecked()) {

      gomito=1;
      single_joint = "Flessione/Estensione del Gomito";
    }
    else if (ui->radioButton_polso->isChecked()) {

      polso=1;
      single_joint= "Pronazione/Supinazione del Polso";
    }

    QMessageBox messageBox(QMessageBox::Question, tr("Salvataggio Singolo Giunto"), tr("Vuoi attivare solo il giunto per la : %1?").arg(single_joint), QMessageBox::Yes | QMessageBox::No, this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Conferma"));
        messageBox.setButtonText(QMessageBox::No, tr("No"));
           if (messageBox.exec()==QMessageBox::Yes) {

             ui->stackedWidget->setCurrentWidget(ui->page_2);
             ss_single_joy << "ho selezionato il controllo del singolo giunto" ; // al posto di questa devo leggere qnode.variabile da dove l'ho modificata
             msg.data = ss_single_joy.str();
           chatter_publisher.publish(msg);
           }
         else  if(messageBox.exec()==QMessageBox::No) {
             ui->stackedWidget->setCurrentWidget(ui->page_joint);

           }


}

void sc_assistivo::on_pushButton_singoloj_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_joint);
}

void sc_assistivo::on_pushButton_modifica_2_clicked()
{
  dati::nuovo_utente = 0;
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

       ui->lineEdit_patologia->setText(patologia);
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
