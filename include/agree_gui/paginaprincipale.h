#ifndef PAGINAPRINCIPALE_H
#define PAGINAPRINCIPALE_H

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






QList<QPixmap > GetImages(QString exID);  // carico tutte le immagini del folder

struct ExInfo{
  QString EX;
  int REP;
  QList<QPixmap> images;
};

QList<QPixmap > GetImages2(QString tutID); //carico le immagini dal folder tutorial

struct TutInfo {
  QString tut;
  QList<QPixmap> img;
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
//se sottoscrivo a un topic non ho bisogno delle classi lo vedo come topic


//namespace agree_gui {


namespace Ui {
class paginaprincipale;
//using namespace  agree_gui;
}
//}

class QMediaPlayer;
class QVideoWidget;
class paginaprincipale : public QDialog

{
  Q_OBJECT
   std::map<QString,ExInfo>ExInfoMap; // mappo gli esercizi
   std::map<QString, TutInfo> TutInfoMap; // mappo le immagini del tutorial
    MatrixWidget * matrix = new MatrixWidget (this);
    int curImage = 0;
    int rep = 0;
    QVector<QString> sel_ex;
    int curEx=0;
    QString key;

    // sistemo mappatura immagini tutorial
    int curImg = 0;
    QVector<QString> sel_tut;
    int curTut = 0;
    QString key2;

    // aggiungo questo
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
    QString es1, es2,es3,es4,es5,es6,es7;
    int t_es1, t_es2, t_es3, t_es4, t_es5, t_es6, t_es7;
    int ripe1, ripe2, ripe3, ripe4, ripe5, ripe6, ripe7;
    int temp_tot;
    QString temp_string;
    QString oggetto_es1, oggetto_es2, oggetto_es3, oggetto_es4, oggetto_es5, oggetto_es6, oggetto_es7;
    int ros_ogg1, ros_ogg2, ros_ogg3, ros_ogg4, ros_ogg5, ros_ogg6, ros_ogg7;

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

private slots:
  void on_pushButton_nuovopaziente_clicked();

  void on_pushButton_salva_clicked();

  void on_pushButton_elencoPazienti_clicked();


  void on_tableView_database_activated(const QModelIndex &index);

  void on_pushButton_eliminapaziente_clicked();

  void on_pushButton_modifica_clicked();


  void on_pushButton_utente_clicked();

  void on_pushButton_salva_2_clicked();

  void on_pushButton_vestizioneAgree_clicked();

  void on_pushButton_home_clicked();

  void enable_combo();
  void update_tempo_terapia();
  void enable_combo_ex();

  void next_img();
  void prova_signal();



  void on_pushButton_salta_clicked();

  void on_pushButton_salvaconf_clicked();


  void on_pushButton_cerca_3_clicked();


//  void on_pushButton_save_clicked();

/*  void on_pushButton_spalla_clicked();

  void on_pushButton_spallagomito_clicked();

  void on_pushButton_spallagomitopolso_clicked()*/;

  void on_pushButton_continua_clicked();

//  void on_pushButton_trigger_clicked();

//  void on_pushButton_passivo_clicked();

//  void on_pushButton_antig_clicked();

//  void on_pushButton_aan_clicked();

//  void on_pushButton_chall_clicked();

  void on_pushButton_salvaex_clicked();

  void on_pushButton_controllo_clicked();

  void on_pushButton_salvamoduli_clicked();

  void on_pushButton_salvatapp_clicked();

 // void on_pushButton_goon_clicked();

  void on_pushButton_next_clicked();

  void on_pushButton_associa_clicked();



  void on_pushButton_indietro_2_clicked();

  void on_pushButton_prosegui_clicked();

  void on_pushButton_go_clicked();
 void callback1(const std_msgs::StringConstPtr& str);
 void callback2(const std_msgs::Int8 msg);
private:
  Ui::paginaprincipale *ui;
  QSqlDatabase mydb2;
 // agree_gui::QNode qnode;
  //ho aggiunto questo
  ros::Publisher chatter_publisher;
 ros::Subscriber command_subscriber; //creo il topic command  a cui fare il subscribe

  SignalHelper *helper;
  QTimer *timer;

};


#endif // PAGINAPRINCIPALE_H
