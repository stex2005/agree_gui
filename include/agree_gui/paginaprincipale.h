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
#include<std_msgs/Int16.h>
#include <sstream>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <QTimer>
#include <vector>






#include "matrixwidget.h"
#include "qnode.hpp"
#include "agree_gui/agree_gui_command.h"
#include "agree_gui/agree_emg_status.h"

#include "agree_esmacat_pkg/agree_esmacat_command.h"
#include "agree_esmacat_pkg/agree_esmacat_status.h"

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

/********************         ASSEMBLY IMAGES            *******************/

QList<QPixmap > GetImages2(QString tutID); //UPLOAD OF TUTORIAL IMAGES

struct TutInfo {
  QString tut;
  QList<QPixmap> img;
  QStringList istr;
};

/********************         WEARING IMAGES            *******************/

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

  ***********************       MAPPING THE IMAGES         ****************

  *****************************************************************************/

  /**********************        EXERCISES MAP         *********************/

   std::map<QString,ExInfo>ExInfoMap;
   int curImage = 0;
   int rep = 0;
   QVector<QString> sel_ex;
   int curEx=0;
   QString key;
      std::vector<int> vect;

    /**********************         ASSEMPLY MAP         *********************/

   std::map<QString, TutInfo> TutInfoMap;
   int curImg = 0;
   QVector<QString> sel_tut;
   int curTut = 0;
   QString key2;

    /**********************        WEARING MAP          *********************/

   std::map<QString, VestInfo> VestInfoMap; //WEARING
   int curimgs = 0;
   QVector<QString> sel_vest;
   int curVest = 0;
   QString key3;

   /********************       MATRIX MAT DECLARATION         *******************/

    MatrixWidget * matrix = new MatrixWidget (this);
     std::vector<int> point0p;
     std::vector<int> point1p;
     std::vector<int> point2p;
     std::vector<int> point3p;
     std::vector<int> point1ses;
     std::vector<int> point2ses;
     std::vector<int> point3ses;
    int  point1xp,point1yp,point2xp,point2yp,point3xp,point3yp;
    int curr_ex;






    /*****************************************************************************

    ***************         ROS MESSAGES DECLARATION          ******************

    *****************************************************************************/

    std_msgs::String msg;
    std::stringstream ss; //ROM
    std::stringstream ss1; //MODALITA
    std::stringstream ss2; // MODULI
    std::stringstream ss3; //ESERCIZI
    std::stringstream ss4; //TAPPETINO
    std::stringstream ss5; //CHECK TAPPETINO

    std_msgs::Int16 msg_status_pp;

    // STRING LIST TO ASSOCIATE ANOTHER THERAPIST
    QStringList associa_user;

    bool check_ex1;

    int flag, prova;

    /*****************************************************************************

    ***************         ROS PARAMETERS DECLARATION   ******************

    *****************************************************************************/

    /***************               ACTIVE MODULES               ******************/

    bool active_module_spalla = 0;
    bool active_module_gomito = 0;
    bool active_module_polso = 0;
    bool active_module_MAT = 0;
    bool active_module_RF = 0;
    bool active_module_EEG_EMG = 0;
    bool active_module_MAP = 0;
    bool active_module_JOYSTICK=0;
    bool active_module_VOCAL=0;
    bool active_module_IK_ONLINE=0;



    std::vector<bool> active_modules; //ACTIVE MODULES
    std::vector<double> J_MAX;         // ROM MAX
    std::vector<double> J_MIN;         // ROM MIN
    double upperarm, lowerarm, height, weight, UA_m, LA_m, H_m, CdM_UA, CdM_LA, CdM_H, UA_l, LA_l, H_l, comp_param, comp_forearm, speed;
    // UA --> upper arm
    // LA --> lower arm
    // H --> hand
    // *_m variables refer to the mass of UA (upperarm), LA (lowerarm), H (hand)
    // CdM_* variables refer to the center of mass of UA, LA, H
    //comp_param refers to the compensation parameter of the weight of the arm needed to the exoskeleton

    std::vector<double> ARM_LENGTH;   // LUNGHEZZA BRACCIO
    double ROM_rad[5];
    uint8_t mode;
    int exe1=0, exe2=0, exe3=0, exe4=0, exe5=0, exe6=0, exe7=0;
    std::vector<int> ex_seq; //exercises sequence
    int rep1=0, rep2=0, rep3=0, rep4=0, rep5=0, rep6=0, rep7=0;
    std::vector<int> ex_rep; //exercise repetition
    std::vector<int> ex_obj; //exercise objects


    /***************            MAT  POINTS           ******************/

     std::vector<int> point1; //target point 1

     std::vector<int> point2; //target point 2
      std::vector<int> point3; // target point 3

    /*****************************************************************************

    ***************            VARIABLES TO COMPUTE THE ESTIMATION OF TIME THERAPY       ******************

    *****************************************************************************/

    QString es1, es2,es3,es4,es5,es6,es7,es8,es9,es10,es11;
    int t_es1, t_es2, t_es3, t_es4, t_es5, t_es6, t_es7; //time for each exercise
    int ripe1, ripe2, ripe3, ripe4, ripe5, ripe6, ripe7; //  repetition for each exercise
    int temp_tot;
    QString temp_string;
    /*****************************************************************************

    *********            VARIABLES DECLARION FOR INTERACTIVE OBJECTS           *********

    *****************************************************************************/

    QString oggetto_es1, oggetto_es2, oggetto_es3, oggetto_es4, oggetto_es5, oggetto_es6, oggetto_es7;
    int ros_ogg1=0, ros_ogg2=0, ros_ogg3=0, ros_ogg4=0, ros_ogg5=0, ros_ogg6=0, ros_ogg7=0;

    /*****************************************************************************

    *********            EVALUATION VARIABLE DECLARATION                  *********

    *****************************************************************************/

    // METTI OUTPUT QUI
    QString filename_eval;
    QString data_eval;

    QString speeds;



public:
  explicit paginaprincipale(QWidget *parent = nullptr);
  ~paginaprincipale();
    //  agree_gui::QNode qnode;
   //   SignalHelper1 *helper1;
signals:
  //  void login_open();
      void ShowMain();



private slots:

/**********************         NEW PATIENT         *********************/

  void on_pushButton_nuovopaziente_clicked();

/**********************         SAVE NEW PATIENT         *********************/

  void on_pushButton_salva_clicked();

/**********************        PATIENTS LIST         *********************/

  void on_pushButton_elencoPazienti_clicked();

/*****               FUNCTION TO ACTIVATE THE CLICK MOUSE ON THE DATABASE TABLE      *********/

  void on_tableView_database_activated(const QModelIndex &index);

/**********************         DELETE PATIENT           *********************/

  void on_pushButton_eliminapaziente_clicked();

/**********************         EDIT PATIENT            *********************/

  void on_pushButton_modifica_clicked();

/**********************        EDIT USER              *********************/

  void on_pushButton_utente_clicked();

/**********************         SAVE USER EDIT        *********************/

  void on_pushButton_salva_2_clicked();

/**********************         START REHAB CONFIGURATION         *********************/

  void on_pushButton_vestizioneAgree_clicked();

/**********************         HOME                         *********************/

  void on_pushButton_home_clicked();

/**********************         ENABLE OBJECTS COMBOBOXES      *********************/

  void enable_combo(); //REHAB CONFIGURATION
  void enable_combo_recap();  //REHAB RECAP

/**********************         COMPUTE TIME THERAPY       *********************/

  void update_tempo_terapia(); //REHAB CONFIGURATION
  void update_tempo_recap();   //REHAB RECAP



/**********************         ENABLE EXERCISES COMBOBOXES    *********************/

  void enable_combo_ex(); //REHAB CONFIGURATION
  void enable_combo_ex_recap(); //REHAB RECAP

  /**********************         ENABLE MODULES CHECKBOXES   *********************/

    void enable_checkbox_moduli_sx(); //LEFT SIDE
    void enable_checkbox_moduli_dx(); //RIGHT SIDE
    void enable_checkbox_moduli_spalla(); //SHOULDER
    void enable_checkbox_moduli_gomito(); //ELBOW
    void enable_checkbox_moduli_polso(); //WRIST

/**********************               EXERCISES FUNCTION               *********************/

  void next_img();



 // void prova_signal();

/**********************       AVANTI TUTORIAL MONTAGGIO       *********************/

  void on_pushButton_salta_clicked();

/**********************       SAVE ROM                       *********************/

  void on_pushButton_salvaconf_clicked();

/**********************       SEARCH FOR PATIENT BY SURNAME                 *********************/

  void on_pushButton_cerca_3_clicked();

/**********************       SAVE EXECISES                 *********************/

  void on_pushButton_salvaex_clicked();

/**********************       SALVA CONTROLLO                *********************/

 // void on_pushButton_controllo_clicked();

/**********************       SAVE MODULES                  *********************/

  void on_pushButton_salvamoduli_clicked();

/**********************       SAVE MAT TARGET POINTS                *********************/

  void on_pushButton_salvatapp_clicked();

/**********************      START THERAPY                *********************/

  void on_pushButton_next_clicked();

/**********************       BACK ASSEMLY TUTORIAL    *********************/

  void on_pushButton_indietro_2_clicked();

/**********************       SKIP ASSEMBLI TUTORIAL      *********************/

  void on_pushButton_prosegui_clicked();

/**********************       SKIP WEARING TUTORIAL      *********************/

  void on_pushButton_go_clicked();

/**********************       ROS CALLBACK DECLARATION     *********************/

// void callback1(const std_msgs::StringConstPtr& str);

 void esmacat_command_callback(const agree_esmacat_pkg::agree_esmacat_command msg);

 void emg_callback(const agree_gui::agree_emg_status msg);

 void esmacat_callback(const agree_esmacat_pkg::agree_esmacat_status msg);


/**********************   SET COMPENSATION ROSPARAM DURING REHAB CONFIGURATION     *************/

 void set_comp_param();
 /**********************   SET COMPENSATION AD ROSPARAM DURING REHAB SESSION     *************/

  void set_comp_param_ses();
/**********************       INTERROMPI TERAPIA             *********************/

 void on_pushButton_allarme_clicked();

/**********************       GO FORWARD WEARING TUTORIAL      *********************/

 void on_pushButton_avanti_v_clicked();

/**********************       LOG-OUT                           *********************/

 void on_pushButton_logout_clicked();

 void on_pushButton_2_clicked();

 void on_pushButton_add_clicked();

 void on_pushButton_remove_clicked();

 void on_pushButton_ok_clicked();


 void on_pushButton_indietro_clicked();

 void on_pushButton_esplorarom_clicked();

 void on_pushButton_riprendi_clicked();

 void on_pushButton_termina_clicked();

 void on_pushButton_conferma_recap_clicked();





 void on_pushButton_4_clicked();

 void on_pushButton_pass_clicked();

 void on_pushButton_asan_clicked();

 void on_pushButton_antig_clicked();

 void on_pushButton_challening_clicked();

 void on_pushButton_trasp_clicked();

 void on_pushButton_modifica_recap_clicked();

 void on_pushButton_add_2_clicked();

 void on_pushButton_remove_2_clicked();

 void on_pushButton_salva_recap_clicked();

 void on_pushButton_3_clicked();

 void on_pushButton_salva_exo_param_clicked();

 void on_pushButton_salva_comp_clicked();

 void on_pushButton_clicked();

 //void plot();

 void on_pushButton_test_matplotlib_clicked();

 void on_pushButton_salta_EMG_clicked();

 void on_pushButton_5_clicked();

 void on_pushButton_pdf_clicked();

 void on_pushButton_es_libero_clicked();

 void on_pushButton_salvascore_clicked();

 void on_pushButton_valutazione_clicked();

 void on_pushButton_show_pdf_clicked();

 void on_tableView_valutazioni_activated(const QModelIndex &index);

 void on_radioButton_lenta_clicked();

 void on_radioButton_media_clicked();

 void on_radioButton_veloce_clicked();

private:
  Ui::paginaprincipale *ui;

/**********************       DICHIARO DATABASE                   *********************/
  QSqlDatabase mydb2;
 // agree_gui::QNode qnode;
  //ho aggiunto questo

/**********************       DICHIARO TOPIC                      *********************/
 ros::Publisher status_publisher;
 ros::Subscriber command_subscriber;

 //EMG
 ros::Subscriber emg_subscriber; //creo il topic command  a cui fare il subscribe

 ros::Subscriber esmacat_subscriber;

  SignalHelper *helper;
 // SignalHelper1 *helper1;

/**********************       DICHIARO TIMER                       *********************/
  QTimer *timer; // TIMER PER AGGIORNARE FUNZIONE CALLBACK (PROVVISORIO?)
  QTimer *timer_init; // TIMER PER INIZILIZZAZIONE
  QTimer *timer_rehab; // TIMER PER IMMAGINI REHAB
  QTimer *timer_val;   // TIMER PER MOSTRARE VALUTAZIONE
  QTimer *timer_feedback; // TIMER PER FEEDBACK AL PAZIENTE
  QTimer *timer_comp; //TIMER PER INVIARE LA COMPENSAZIONE NEI ROSPARAM


};


#endif // PAGINAPRINCIPALE_H
