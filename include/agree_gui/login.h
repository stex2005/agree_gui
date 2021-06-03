#ifndef LOGIN_H
#define LOGIN_H

/*****************************************************************************

***********************         INCLUDE         ******************************

*****************************************************************************/

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QFileInfo>

#include "paginaprincipale.h"
//#include "sc_assistivo.h"
//#include "agree_gui/agree_gui_command.h"
#include "agree_emg_pkg/agree_emg_command.h"
#include "agree_esmacat_pkg/agree_esmacat_command.h"

/*****************************************************************************

***************         GLOBAL VARIABLES DECLARATION         ******************

*****************************************************************************/

struct dati {
    static QString  next_img, username,password,codice_id,ind,Nome, Cognome, Data, NomeP, CognomeP,data1,count,sigla,uservecchio, count_act, lato, lato_prec, modulo_spalla, modulo_gomito, modulo_polso,modulo_spalla_prec, modulo_gomito_prec, modulo_polso_prec, modulo_eeg, modulo_emg, mano, oi, modulo_prec, modulo_eeg_prec, modulo_emg_prec,oi_prec, mano_prec, data_vecchia, modulo_extra, mood, mood_prec,ex1,ex2,ex3,ex4,ex5,ex6,ex7,rip1,rip2,rip3,rip4,rip5,rip6,rip7, rip1_prec, rip2_prec,rip3_prec,rip4_prec,rip5_prec,rip6_prec,rip7_prec, ex1_prec,ex2_prec,ex3_prec,ex4_prec,ex5_prec,ex6_prec,ex7_prec,ogg1_prec, ogg2_prec, ogg3_prec, ogg4_prec, ogg5_prec, ogg6_prec, ogg7_prec, modulo_prec1, num_ex1, num_ex2, num_ex3, num_ex4, num_ex5, num_ex6, num_ex7, patologia, status, user_devel, pass_devel, mode_output;
    static int profilo, password_i, l_eeg_p, l_emg_p, l_m_p, l_oi_p, lex1, lex2,lex3,lex4,lex5,lex6,lex7, nuovo_utente, controllo_voc, controllo_joy, controllo_gomito, output_val;
    static int8_t  command_exercise_pp, command_task_pp, command_exercise_old_pp, command_task_old_pp, flag_ex, flag_ex_recap;
    static int16_t status1, command_pp,command_old_pp,command_login,  command_matrix, command_old_login,  command_old_matrix, command_old_sc3, command_sc3, flag_sc, command_istr_sc3, command_sec_sc3, command_istr_sc3_old, command_sec_sc3_old, rep_index, current_rep_index;
    static double emg_vector[5];
    static bool selcount_mat;
};

namespace Ui {
class login;
}

class login : public QMainWindow
{
  Q_OBJECT
  /*****************************************************************************

  ***************         ROS MESSAGES DECLARATION         ******************

  *****************************************************************************/
  std_msgs::String msg;
  std::stringstream ss_log1; //LOGIN SC 1
  std::stringstream ss_log2; //LOGIN SC 2
  std::stringstream ss_log1_new; // NEW LOGIN SC 1
  std::stringstream ss_log2_new; // NEW LOGIN SC 2
  std_msgs::Int16 msg_status;

  //VERIFICA PATH
  size_t size;
  char *path=NULL;

 char *path_alice =NULL;
char *path_smartbox = NULL;



public:
  explicit login(QWidget *parent = nullptr);
  ~login();
  /*****************************************************************************

  ***************         FUNCTION DECLARATION                   ******************

  *****************************************************************************/
public slots :

/*******      RE-SHOW LOGIN FUNCTION DECLARATION         ***********/
  //this functions allow to re-open the login window from scenario 1 window and scenario 3 window

  void showlogin();

  void showlogin_sc3();


  void callback_log(const agree_esmacat_pkg::agree_esmacat_command msg);



private slots:

  void on_pushButton_accedi_clicked();

  void on_pushButton_newrec_clicked();

  void on_pushButton_salva_clicked();


private:
  Ui::login *ui;
  paginaprincipale *Paginaprincipale; //declaring the name of window that i can open from the login
  //sc_assistivo *Sc_assistivo;
  login *Login;
  ros::Publisher status_publisher;
  ros::Subscriber command_subscriber;
};

#endif // LOGIN_H
