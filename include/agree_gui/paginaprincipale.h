#ifndef PAGINAPRINCIPALE_H
#define PAGINAPRINCIPALE_H
/*****************************************************************************

***********************         INCLUDE         ******************************

*****************************************************************************/
#include <QDialog>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QMainWindow>
#include <QDate>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPixmap>
#include <iostream>
#include <QMap>
#include <string>
#include <iterator>
// ho aggiunto questi
#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include<std_msgs/Int8.h>
#include <sstream>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <QTimer>

#include "matrixwidget.h"
#include "qnode.hpp"
//#include "main_window.hpp"



/*****************************************************************************

***********************       DICHIARO LISTA IMMAGINI         ****************

*****************************************************************************/

/********************         IMMAGINI ESERCIZI            *******************/

QList<QPixmap > GetImages(QString exID);  // carico tutte le immagini del folder

struct ExInfo{
  QString EX;
  int REP;
  QList<QPixmap> images;
};

/********************         IMMAGINI MONTAGGIO            *******************/

QList<QPixmap > GetImages2(QString tutID); //carico le immagini dal folder tutorial

struct TutInfo {
  QString tut;
  QList<QPixmap> img;
  QStringList istr;
};

/********************         IMMAGINI VESTIZIONE            *******************/

QList<QPixmap> GetImages3(QString vestID);
struct VestInfo {
  QString vest;
  QList<QPixmap> img_v;
  QStringList istr_vest;
};

class SignalHelper : public QObject { //classe che richiamo nella callback e mi emette segnale ogni volta che viene chiamata la callback, così posso connettere segnale con funzione che voglio che faccia cose
Q_OBJECT
signals:
void SignalName();
public:
void SendSignal() {
    emit SignalName();
    }
};






namespace Ui {
class paginaprincipale;

}

class QMediaPlayer;
class QVideoWidget;
class paginaprincipale : public QDialog

{
  Q_OBJECT

  /*****************************************************************************

  ***********************       DICHIARO MAPPE IMMAGINI         ****************

  *****************************************************************************/

  /**********************         MAPPA ESERCIZI         *********************/

   std::map<QString,ExInfo>ExInfoMap;
   int curImage = 0;
   int rep = 0;
   QVector<QString> sel_ex;
   int curEx=0;
   QString key;

    /**********************         MAPPA MONTAGGIO         *********************/

   std::map<QString, TutInfo> TutInfoMap;
   int curImg = 0;
   QVector<QString> sel_tut;
   int curTut = 0;
   QString key2;

    /**********************        MAPPA VESTIZIONE          *********************/

   std::map<QString, VestInfo> VestInfoMap; //VESTIZIONE
   int curimgs = 0;
   QVector<QString> sel_vest;
   int curVest = 0;
   QString key3;

   /********************       DICHIARO MATRICE PAD         *******************/

    MatrixWidget * matrix = new MatrixWidget (this);





    /*****************************************************************************

    ***************         DICHIARO MESSAGGI ROS         ******************

    *****************************************************************************/

    std_msgs::String msg;
    std::stringstream ss; //ROM
    std::stringstream ss1; //MODALITA
    std::stringstream ss2; // MODULI
    std::stringstream ss3; //ESERCIZI
    std::stringstream ss4; //TAPPETINO
    std::stringstream ss5; //CHECK TAPPETINO

    // STRING LIST PER ASSOCIARE LO USER
    QStringList associa_user;

    bool check_ex1;
    /*****************************************************************************

    ***************            CALCOLO TEMPO TERAPIA            ******************

    *****************************************************************************/

    QString es1, es2,es3,es4,es5,es6,es7;
    int t_es1, t_es2, t_es3, t_es4, t_es5, t_es6, t_es7;
    int ripe1, ripe2, ripe3, ripe4, ripe5, ripe6, ripe7;
    int temp_tot;
    QString temp_string;
    /*****************************************************************************

    *********            DICHIARO VARIABILI PER OGGETTI TERAPIA          *********

    *****************************************************************************/

    QString oggetto_es1, oggetto_es2, oggetto_es3, oggetto_es4, oggetto_es5, oggetto_es6, oggetto_es7;
    int ros_ogg1, ros_ogg2, ros_ogg3, ros_ogg4, ros_ogg5, ros_ogg6, ros_ogg7;

    /*****************************************************************************

    *********            DICHIARO VARIABILI VALUTAZIONE                  *********

    *****************************************************************************/

    float  rand1, rand2, rand3, rand4, rand5, rand6,rand10;
    float arr7_1, arr7_2,arr7_3,arr7_4,arr7_5;
    float arr9_1, arr9_2,arr9_3,arr9_4,arr9_5;
    QVector<float> val;
    QVector<float> val2;
    QVector<float> val8;
    QStringList vals;
    QStringList vals2;
    QStringList vals8;
    int8_t num;



public:
  explicit paginaprincipale(QWidget *parent = nullptr);
  ~paginaprincipale();
    //  agree_gui::QNode qnode;
   //   SignalHelper1 *helper1;
signals:
  //  void login_open();
      void ShowMain();



private slots:

/**********************         NUOVO PAZIENTE         *********************/

  void on_pushButton_nuovopaziente_clicked();

/**********************         NUOVO PAZIENTE         *********************/

  void on_pushButton_salva_clicked();

/**********************         ELENCO PAZIENTI         *********************/

  void on_pushButton_elencoPazienti_clicked();

/*****               FUNZIONE PER ATTIVARE IL CLICK SUL DATABASE      *********/

  void on_tableView_database_activated(const QModelIndex &index);

/**********************         ELIMINA PAZIENTE           *********************/

  void on_pushButton_eliminapaziente_clicked();

/**********************         MODIFICA PAZIENTE            *********************/

  void on_pushButton_modifica_clicked();

/**********************         MODIFICA UTENTE              *********************/

  void on_pushButton_utente_clicked();

/**********************         SALVA MODIFICA UTENTE        *********************/

  void on_pushButton_salva_2_clicked();

/**********************         SEDUTA RIABILITATIVA         *********************/

  void on_pushButton_vestizioneAgree_clicked();

/**********************         HOME                         *********************/

  void on_pushButton_home_clicked();

/**********************         DISABILITÀ COMBO OGGETTI     *********************/

  void enable_combo();

/**********************         CALCOLA TEMPO TERAPIA        *********************/

  void update_tempo_terapia();

/**********************         DISABILITÀ COMBO ESERCIZI    *********************/

  void enable_combo_ex();

/**********************               ESERCIZI               *********************/

  void next_img();



 // void prova_signal();

/**********************       AVANTI TUTORIAL MONTAGGIO       *********************/

  void on_pushButton_salta_clicked();

/**********************       SALVA ROM                       *********************/

  void on_pushButton_salvaconf_clicked();

/**********************       CERCA PAZIENTE                 *********************/

  void on_pushButton_cerca_3_clicked();

/**********************       SALVA ESERCIZI                 *********************/

  void on_pushButton_salvaex_clicked();

/**********************       SALVA CONTROLLO                *********************/

  void on_pushButton_controllo_clicked();

/**********************       SALVA MODULI                   *********************/

  void on_pushButton_salvamoduli_clicked();

/**********************       SALVA PUNTI PAD                *********************/

  void on_pushButton_salvatapp_clicked();

/**********************       INIZIA TERAPIA                 *********************/

  void on_pushButton_next_clicked();

/**********************       INDIETRO TUTORIAL MONTAGGIO    *********************/

  void on_pushButton_indietro_2_clicked();

/**********************       SALTA  TUTORIAL MONTAGGIO      *********************/

  void on_pushButton_prosegui_clicked();

/**********************       SALTA TUTORIAL VESTIZIONE      *********************/

  void on_pushButton_go_clicked();

/**********************       DICHIARAZIONE CALLBACK ROS     *********************/

 void callback1(const std_msgs::StringConstPtr& str);

 void callback2(const std_msgs::Int8 msg);

 void skip_init();

/**********************    FUNZIONE PER MOSTRARE VALUTAZIONE    ******************/

 void show_val();

/**********************   FUNZIONE PER MOSTRARE FEEDBACK PAZIENTE     *************/

 void show_feed();

/**********************       INTERROMPI TERAPIA             *********************/

 void on_pushButton_clicked();

/**********************       AVANTI  TUTORIAL VESTIZIONE      *********************/

 void on_pushButton_avanti_v_clicked();

/**********************       LOG-OUT                           *********************/

 void on_pushButton_logout_clicked();

private:
  Ui::paginaprincipale *ui;

/**********************       DICHIARO DATABASE                   *********************/
  QSqlDatabase mydb2;
 // agree_gui::QNode qnode;
  //ho aggiunto questo

/**********************       DICHIARO TOPIC                      *********************/
 ros::Publisher chatter_publisher;
 ros::Subscriber command_subscriber; //creo il topic command  a cui fare il subscribe

  SignalHelper *helper;
 // SignalHelper1 *helper1;

/**********************       DICHIARO TIMER                       *********************/
  QTimer *timer; // TIMER PER AGGIORNARE FUNZIONE CALLBACK (PROVVISORIO?)
  QTimer *timer_init; // TIMER PER INIZILIZZAZIONE
  QTimer *timer_rehab; // TIMER PER IMMAGINI REHAB
  QTimer *timer_val;   // TIMER PER MOSTRARE VALUTAZIONE
  QTimer *timer_feedback; // TIMER PER FEEDBACK AL PAZIENTE
};


#endif // PAGINAPRINCIPALE_H
