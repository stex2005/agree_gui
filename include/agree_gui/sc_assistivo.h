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

  //definisco uno slot pubblico che uso per connettere il timer a una funzione
public slots:
  void myfunction();
  void myfunction1();
  void myfunction2();
  void myfunction3();
  void myfunction4();


private slots:
  void on_pushButton_salva_clicked();



  void on_pushButton_home_clicked();

  void on_pushButton_vocale_clicked();


  void on_pushButton_joy_clicked();

  void on_pushButton_salva_2_clicked();

  void on_pushButton_configura_clicked();

  void on_pushButton_joystick_clicked();

  void on_pushButton_gomito_clicked();

  void on_pushButton_singoloj_clicked();

  void on_pushButton_modifica_2_clicked();

  void callback3(const agree_gui::agree_gui_command msg);

private:
  Ui::sc_assistivo *ui;
 //   QSqlDatabase  mydb3;
  QTimer *timer;
  QTimer *timer1;
  QTimer *timer2;
  QTimer *timer3;
  QTimer *timer4;
  ros::Publisher status_publisher;
  ros::Subscriber command_subscriber; //creo il topic command  a cui fare il subscribe
protected:
  virtual void paintEvent(QPaintEvent *event) override;
};


#endif // SC_ASSISTIVO_H
