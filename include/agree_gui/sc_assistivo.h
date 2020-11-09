 #ifndef SC_ASSISTIVO_H
#define SC_ASSISTIVO_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QMainWindow>
#include <QDate>
#include <QPainter>
#include <QTimer>
#include "paginaprincipale.h"
#include <ros/ros.h>
#include <ros/network.h>
#include<std_msgs/Int8.h>
#include<std_msgs/Int16.h>

#include "agree_gui/agree_gui_command.h"


//namespace agree_gui {


namespace Ui {
class sc_assistivo;
}

class sc_assistivo : public QDialog

{

  Q_OBJECT
  QColor col1{Qt::cyan};
  QColor col2{Qt::cyan};
  QColor col3{Qt::cyan};
  QColor col4{Qt::cyan};

  std_msgs::String msg;
  std::stringstream ss_voc; //CONTROLLO VOCALE
  std::stringstream ss_joy; //CONTROLLO JOYSTICK
  std::stringstream ss_elb_rot; // ROTAZIONE GOMITO
  std::stringstream ss_single_joy; // CONTROLLO SINGOLO GIUNTO
  std::stringstream ss_rest; //POSIZIONE DI REST
  std::stringstream ss_joy_conf; //CONFIGURAZIONE JOYSTICK
  std::stringstream ss_rom; // CONFIGURAZIONE ROM

  std::vector<float> J_MAX_SC3;         // ROM MAX
  std::vector<float> J_MIN_SC3;
      std::vector<float> ARM_LENGTH_SC3;    // LUNGHEZZA BRACCIO

  //AGGIUNGI GLI ALTRI MESSAGGI DA INVIARE






public:
  explicit sc_assistivo(QWidget *parent = nullptr);
  ~sc_assistivo();

signals:
  //  void login_open();
      void ShowMain_sc3();

  //definisco uno slot pubblico che uso per connettere il timer a una funzione
public slots:
  void myfunction();
  void myfunction1();
  void myfunction2();
  void myfunction3();
  void myfunction4();

    void cal_joy();


private slots:
  void on_pushButton_salva_clicked();

  void on_pushButton_vocale_clicked();


  void on_pushButton_joy_clicked();





  void on_pushButton_joystick_clicked();

  void on_pushButton_gomito_clicked();

  void on_pushButton_singoloj_clicked();



  void callback3(const agree_gui::agree_gui_command msg);

  void on_pushButton_salva_rom_sc3_clicked();

  void on_pushButton_skip_sc3_clicked();

  void on_pushButton_spegni_clicked();

  void on_pushButton_configura_joy_sc3_clicked();

  void on_pushButton_salta_joy_clicked();



  void on_pushButton_rifo_joy_clicked();

  void on_pushButton_end_conf_joy_clicked();

  void on_pushButton_clicked();

private:
  Ui::sc_assistivo *ui;
    QSqlDatabase  mydb3;
//  QTimer *timer;
//  QTimer *timer1;
//  QTimer *timer2;
//  QTimer *timer3;
//  QTimer *timer4;
  QTimer *timer_joy;
  ros::Publisher status_publisher;
  ros::Subscriber command_subscriber; //creo il topic command  a cui fare il subscribe
protected:
 // virtual void paintEvent(QPaintEvent *event) override;
};


#endif // SC_ASSISTIVO_H
