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
#include <sstream>
#include <string>
#include <QThread>
#include <QStringListModel>



#include "matrixwidget.h"
#include "qnode.hpp"
//#include "main_window.hpp"



QList<QPixmap > GetImages(QString exID);  // in here we load all images from folder

struct ExInfo{
  QString EX;
  int REP;
  QList<QPixmap> images;
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
   std::map<QString,ExInfo>ExInfoMap;
    MatrixWidget * matrix = new MatrixWidget (this);
    int curImage = 0;
    int rep = 0;
    QVector<QString > sel_ex;
    int curEx=0;
    QString key;
    // aggiungo questo
    std_msgs::String msg;
    std::stringstream ss; //ROM
    std::stringstream ss1; //MODALITA
    std::stringstream ss2; // MODULI
    std::stringstream ss3; //ESERCIZI
    std::stringstream ss4; //TAPPETINO


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

private:
  Ui::paginaprincipale *ui;
  QSqlDatabase mydb2;
 // agree_gui::QNode qnode;
  //ho aggiunto questo
  ros::Publisher chatter_publisher;








};


#endif // PAGINAPRINCIPALE_H
