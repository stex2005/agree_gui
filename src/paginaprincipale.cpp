#include "../include/agree_gui/paginaprincipale.h"
#include "ui_paginaprincipale.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/main_window.hpp"
#include "../include/agree_gui/sc_assistivo.h"
#include "../include/agree_gui/matrixwidget.h"
#include "../include/agree_gui/qnode.hpp"
#include <QMessageBox>
#include <QFloat16>
#include <QMovie>
#include <QVBoxLayout>
#include "../include/agree_gui/matplotlibcpp.h"
#include <vector>
#include <fstream>
#include<QFile>
#include <QTextStream>
#include <cmath>
#include "../include/agree_gui/fsm_gui_define.h"
//#include <QMultimedia>
//#include <QSound>
//#include <QMediaPlayer>
//#include <QVideoWidget>
#include <string>





//matplotlibcpp.use("Qt5Agg")

//GRAFICO?
#include <math.h>
#include <stdio.h>


QString dati::codice_id;
QString dati::ind;
QString dati::NomeP, dati::CognomeP, dati::data1;
QString dati::uservecchio;
QString dati::count_act;
QString dati::lato, dati::lato_prec; // 1 destro, 0 sinistro
QString dati::modulo_spalla, dati::modulo_gomito, dati::modulo_polso;
QString dati::modulo_spalla_prec, dati::modulo_gomito_prec, dati::modulo_polso_prec;
QString dati::modulo_eeg, dati::modulo_emg;
QString dati::mano;
QString dati::oi;
QString dati::modulo_prec;
QString dati::modulo_eeg_prec, dati::modulo_emg_prec;
QString dati::oi_prec;
QString dati::mano_prec;
QString dati::data_vecchia;
QString dati::modulo_extra;
QString dati::modulo_prec1;
int     dati::l_eeg_p, dati::l_emg_p;
int     dati::l_m_p;
int     dati::l_oi_p;
QString dati::ex1_prec, dati::ex2_prec, dati::ex3_prec, dati::ex4_prec, dati::ex5_prec, dati::ex6_prec, dati::ex7_prec;
int     dati::lex1, dati::lex2, dati::lex3, dati::lex4, dati::lex5, dati::lex6, dati::lex7;
QString dati::rip1_prec, dati::rip2_prec, dati::rip3_prec, dati::rip4_prec, dati::rip5_prec, dati::rip6_prec, dati::rip7_prec;
QString dati::ogg1_prec, dati::ogg2_prec, dati::ogg3_prec, dati::ogg4_prec, dati::ogg5_prec, dati::ogg6_prec, dati::ogg7_prec;
QString dati::mood;
QString dati::mood_prec;
QString dati::ex1, dati::ex2, dati::ex3, dati::ex4, dati::ex5, dati::ex6, dati::ex7;
QString dati::num_ex1, dati::num_ex2, dati::num_ex3, dati::num_ex4, dati::num_ex5, dati::num_ex6, dati::num_ex7;

QString dati::rip1, dati::rip2, dati::rip3, dati::rip4, dati::rip5, dati::rip6, dati::rip7;
QString dati::next_img;

int16_t dati::command_pp = 0, dati::command_old_pp = 1, dati::rep_index, dati::current_rep_index=0;
int8_t dati::command_exercise_pp = 0, dati::command_task_pp= 0;
int8_t dati::command_exercise_old_pp, dati::command_task_old_pp;
int8_t dati::flag_ex=0, dati::flag_ex_recap=0;
QString dati::mode_output;
double dati::emg_vector[5];
int dati::output_val;

namespace plt = matplotlibcpp;

//SignalHelper *helper;
void paginaprincipale::emg_callback(const agree_gui::agree_emg_status emg_msg){

  for(int i=0; i<5; i++){
    dati::emg_vector[i] = emg_msg.check_emg[i];

  }
}
void paginaprincipale::esmacat_callback(const agree_esmacat_pkg::agree_esmacat_status msg){
  ROM_rad[0]= msg.joint_position_rad[0]; //J1

  ROM_rad[1]= msg.joint_position_rad[1]; //J2
  ROM_rad[2]= msg.joint_position_rad[2]; //J3
  ROM_rad[3]= msg.joint_position_rad[3]; //J4
  ROM_rad[4]= msg.joint_position_rad[4]; //J5
  ui->lcdNumber_j1->display(ROM_rad[0]);
  ui->lcdNumber_j2->display(ROM_rad[1]);
  ui->lcdNumber_j3->display(ROM_rad[2]);
  ui->lcdNumber_j4->display(ROM_rad[3]);
  ui->lcdNumber_j5->display(ROM_rad[4]);
  ui->dial_j1->setValue(ROM_rad[0]);
  ui->dial_j2->setValue(ROM_rad[1]);
  ui->dial_j3->setValue(ROM_rad[2]);
  ui->dial_j4->setValue(ROM_rad[3]);
  ui->dial_j5->setValue(ROM_rad[4]);



}

void paginaprincipale::callback2(const agree_gui::agree_gui_command msg_command_pp) {
  ros::NodeHandle n;
  //  dati::command_old_pp = 1;
  dati::command_pp = msg_command_pp.mode;
  dati::command_exercise_pp = msg_command_pp.exercise;
  dati::command_task_pp = msg_command_pp.task;
  if((dati::command_old_pp) != (dati::command_pp) || (dati::command_exercise_old_pp)!= (dati::command_exercise_pp) || (dati::command_task_old_pp)!= (dati::command_task_pp)) {
    qDebug()<< dati::command_old_pp;
    qDebug()<< dati::command_pp;
    dati::command_old_pp=dati::command_pp;
    dati::command_task_old_pp = dati::command_task_pp;
    dati::command_exercise_old_pp = dati::command_exercise_pp;
    ROS_INFO("I heard: %d PAGINA PRINCIPALE", dati::command_pp);

    if(dati::command_old_pp ==SC1_EDIT_PATIENT_MODULE_CONTROL) {
      ui->tabWidget->setCurrentWidget(ui->tab);
      ui->pushButton_allarme->setVisible(false);
      this->showMaximized();
      ui->stackedWidget_rom->showMaximized();

      QSqlQuery prova;
      prova.prepare("select Nome, Cognome from Users where Username = '"+dati::username+"' and Password = '"+dati::password+"'");
      prova.exec();
      if (prova.exec()) {
        qDebug()<< "sono nella query prova";
        while(prova.next()) {
          ui->label_status->setText("Terapista: " + prova.value(0).toString() + " " +  prova.value(1).toString());
        } }
      else {  qDebug()<<"ho problemi qui";
        qDebug()<< prova.lastError();
      qDebug() << QSqlDatabase::drivers();}
      this->show();
    }
    if (dati::command_old_pp ==SC1_SESSION_DEFINING) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_controllo);

      ui->pushButton_allarme->setVisible(false);
      exe1=0;
      exe2=0;
      exe3=0;
      exe4=0;
      exe5=0;
      exe6=0;
      exe7=0;
      rep1=0;
      rep2=0;
      rep3=0;
      rep4=0;
      rep5=0;
      rep6=0;
      rep7=0;
      ros_ogg1=0;
      ros_ogg2=0;
      ros_ogg3=0;
      ros_ogg4=0;
      ros_ogg5=0;
      ros_ogg6=0;
      ros_ogg7=0;
      ex_seq = {exe1, exe2, exe3, exe4, exe5, exe6, exe7};
      ex_rep = {rep1, rep2, rep3, rep4, rep5, rep6, rep7};
      ex_obj = {ros_ogg1, ros_ogg2, ros_ogg3, ros_ogg4, ros_ogg5, ros_ogg6, ros_ogg7};

    }
    if(dati::command_old_pp == SC1_WEARING) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_vestizione);
      ui->pushButton_allarme->setVisible(false);


    }
    if(dati::command_old_pp == SC1_ROM) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_exo_param);

      ui->pushButton_allarme->setVisible(false);
    }
    if(dati::command_old_pp == SC1_HAND_POSITION){
      ui->tabWidget_2->setCurrentWidget(ui->tab_calibrazione);
      ui->pushButton_allarme->setVisible(true);
      point1p={0,0};
      point2p={0,0};
      point3p={0,0};
      n.setParam("/point1/mat_coordinates", point1p);
      n.setParam("/point2/mat_coordinates", point2p);
      n.setParam("/point3/mat_coordinates", point3p);



    }
    if(dati::command_old_pp == SC1_WORKSPACE_ON) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
      dati::status1 = SC1_WORKSPACE_ON;
      msg_status_pp.data = dati::status1;
      ROS_INFO ("%d", msg_status_pp.data);
      status_publisher.publish(msg_status_pp);
      ui->pushButton_allarme->setVisible(true);
       ui->pushButton_salvatapp->setEnabled(false);
    }
    if(dati::command_old_pp == SC1_SELECT_FINISH) {
      if(dati::selcount_mat ==1) {
        ui->pushButton_salvatapp->setEnabled(true);
        dati::selcount_mat=0;
      qDebug()<<dati::selcount_mat;}
      else if(dati::selcount_mat==0) {
        ui->pushButton_salvatapp->setEnabled(false);
        qDebug()<<dati::selcount_mat;
      }

    }

    if(dati::command_old_pp == SC1_START_SESSION) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
      ui->stackedWidget_2->setCurrentWidget(ui->page_recap);
      ui->label_recap->setText(QString("Modalità di controllo: %1").arg(dati::mood));

      //ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
      ui->pushButton_allarme->setVisible(true);

    }
    if((dati::command_old_pp ==SC1_READY_TO_START_EXERCISE)||(dati::command_old_pp==SC1_OUT_100)){
      ui->progressBar_th->setMinimum(0);
      ui->progressBar_th->setMaximum(dati::rep_index);
      ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
      ui->stackedWidget_2->setCurrentWidget(ui->page_sessione);
      if(dati::command_task_old_pp==1) {
        dati::current_rep_index++;
        ui->progressBar_th->setValue(dati::current_rep_index);

      }

    }
    if(dati::command_old_pp == SC1_EVALUATION){
      timer_rehab->stop();
      ui->tabWidget_2->setCurrentWidget(ui->tab_valutazione);
      n.getParam("/evaluation/Output", dati::output_val);
      int mode_consigliata;

      //SAVE THE PDF EVALUATION PATH

      if(dati::output_val == -1) {
        QPixmap output_neg("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/output/output-1.png");
        ui->label_output->setPixmap(output_neg);
        n.getParam("/exercise/mode", mode_consigliata);
        mode_consigliata = mode_consigliata-1;
        QString mode_consigliata_db = QString::number(mode_consigliata);
        QSqlQuery salvaout;
        salvaout.prepare("update Parametri_Paziente set output='"+mode_consigliata_db+"' where Codice_ID='"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
        salvaout.exec();
        if (!salvaout.exec()) {
          qDebug()<<salvaout.lastError();
        }

      }
      if(dati::output_val== 0)
      {
        QPixmap output0("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/output/output0.png");
        ui->label_output->setPixmap(output0);
        n.getParam("/exercise/mode", mode_consigliata);
        mode_consigliata = mode_consigliata;
        QString mode_consigliata_db = QString::number(mode_consigliata);
        QSqlQuery salvaout;
        salvaout.prepare("update Parametri_Paziente set output='"+mode_consigliata_db+"' where Codice_ID='"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
        salvaout.exec();
        if (!salvaout.exec()) {
          qDebug()<<salvaout.lastError();
        }
      }
      if(dati::output_val==1) {
        QPixmap output1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/output/output1.png");
        ui->label_output->setPixmap(output1);
        n.getParam("/exercise/mode", mode_consigliata);
        mode_consigliata = mode_consigliata+1;
        QString mode_consigliata_db = QString::number(mode_consigliata);
        QSqlQuery salvaout;
        salvaout.prepare("update Parametri_Paziente set output='"+mode_consigliata_db+"' where Codice_ID='"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
        salvaout.exec();
        if (!salvaout.exec()) {
          qDebug()<<salvaout.lastError();
        }
      }

      //SAVING EVALUATION PDF PATH ON THE DATABASE

      //std::string PatientCode = "gigio01";
      std::string dir_val = "/home/nearlab/AGREE_ws/src/agree_evaluation_pkg/src/evaluation_node/";
      std::string PatientCode = dati::ind.toUtf8().constData();
      std::string format = ".pdf";
      std::string filepath = dir_val+ PatientCode + format;
      //      std::string filepath;
      //      n.getParam("/evaluation/Path_pdf", filepath);

      QString filepath_db = QString::fromUtf8(filepath.c_str());
      cout << filepath <<endl;
      QSqlQuery save_path;
      save_path.prepare("update  Parametri_Paziente set path_val = '"+filepath_db+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
      save_path.exec();
      if(!save_path.exec())
        qDebug()<< save_path.lastError();


      // QFileInfo fi( QDir("/home/nearlab/AGREE_ws/src/agree_evaluation_pkg/src/evaluation_node/"), "%s", PatientCode );
      //  QString path = fi.absoluteFilePath();
      // QDir dir_val("/home/nearlab/AGREE_ws/src/agree_evaluation_pkg/src/evaluation_node/");


      //sprintf(bufferollo,"/home/nearlab/AGREE_ws/src/agree_evaluation_pkg/src/evaluation_node/%s",PatientCode.c_str());


    }
    if(dati::command_old_pp== SC1_EMERGENCY_RESET) {

      ui->tabWidget_2->setCurrentWidget(ui->tab_alarm);

    }
    if(dati::command_old_pp == SC1_ELECTRODES_POSITION) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_emg);
      ui->stackedWidget_3->setCurrentWidget(ui->page_posizionaEMG);

    }
    if(dati::command_old_pp == SC1_ELECTRODES_CHECK) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_emg);
      ui->stackedWidget_3->setCurrentWidget(ui->page_check);

    }
    if(dati::command_old_pp == SC1_ELECTRODES_ENERGY_MEASURE) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_emg);
      ui->stackedWidget_3->setCurrentWidget(ui->page_restEMG);

    }

    if(dati::command_old_pp== 1070) {

     system("aplay /home/alice/Desktop/POLIMI/Poli.wav");

    }


  }

}

paginaprincipale::paginaprincipale(QWidget *parent) :


  QDialog(parent),

  ui(new Ui::paginaprincipale)


{




  ui->setupUi(this);
  ui->progressBar_th->setVisible(false);

  //ui->pushButton_salvatapp->setEnabled(false);



  ui->tabWidget->setCurrentWidget(ui->tab);
  ui->stackedWidget->setCurrentWidget(ui->page_3);


  ui->verticalLayout->addWidget(matrix);

  // ho aggiunto questi
  ros::NodeHandle n;
  status_publisher = n.advertise<std_msgs::Int16>("/gui/status", 1000);


  command_subscriber = n.subscribe("/gui/command", 1000, &paginaprincipale::callback2, this); //creo il topic a cui faccio il subscribe
  emg_subscriber = n.subscribe("/agree/emg_status", 1000, &paginaprincipale::emg_callback, this);
  esmacat_subscriber = n.subscribe("/agree/esmacat_status", 1000, &paginaprincipale::esmacat_callback, this);


  //connetto combobox con combo box
  connect(ui->comboBox_ex1, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
  connect(ui->comboBox_ex2, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
  connect(ui->comboBox_ex3, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
  connect(ui->comboBox_ex4, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
  connect(ui->comboBox_ex5, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
  connect(ui->comboBox_ex6, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
  connect(ui->comboBox_ex7, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo()));
  //RECAP
  connect(ui->comboBox_es1, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo_recap()));
  connect(ui->comboBox_es2, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo_recap()));
  connect(ui->comboBox_es3, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo_recap()));
  connect(ui->comboBox_es4, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo_recap()));
  connect(ui->comboBox_es5, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo_recap()));
  connect(ui->comboBox_es6, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo_recap()));
  connect(ui->comboBox_es7, SIGNAL (currentTextChanged(QString)), this, SLOT(enable_combo_recap()));

  //connect(ui->lineEdit_ex1, SIGNAL(TextChanged(QString)),this, SLOT(update_tempo_terapia(QString)));
  connect(ui->lineEdit_ex1, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
  connect(ui->lineEdit_ex2, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
  connect(ui->lineEdit_ex3, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
  connect(ui->lineEdit_ex4, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
  connect(ui->lineEdit_ex5, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
  connect(ui->lineEdit_ex6, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));
  connect(ui->lineEdit_ex7, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_terapia()));

  //RECAP
  connect(ui->lineEdit_rep1, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_recap()));
  connect(ui->lineEdit_rep2, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_recap()));
  connect(ui->lineEdit_rep3, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_recap()));
  connect(ui->lineEdit_rep4, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_recap()));
  connect(ui->lineEdit_rep5, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_recap()));
  connect(ui->lineEdit_rep6, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_recap()));
  connect(ui->lineEdit_rep7, SIGNAL(textChanged(const QString)),this, SLOT(update_tempo_recap()));



  connect(ui->checkBox_ex1, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
  connect(ui->checkBox_ex2, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
  connect(ui->checkBox_ex3, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
  connect(ui->checkBox_ex4, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
  connect(ui->checkBox_ex5, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
  connect(ui->checkBox_ex6, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
  connect(ui->checkBox_7, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex()));
  //RECAP
  connect(ui->checkBox_es1, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex_recap()));
  connect(ui->checkBox_es2, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex_recap()));
  connect(ui->checkBox_es3, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex_recap()));
  connect(ui->checkBox_es4, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex_recap()));
  connect(ui->checkBox_es5, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex_recap()));
  connect(ui->checkBox_es6, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex_recap()));
  connect(ui->checkBox_es7, SIGNAL(stateChanged(int)), this, SLOT(enable_combo_ex_recap()));

  //controllo unicità checkbox dei lato e dei moduli
  connect(ui->checkBox_destro, SIGNAL(stateChanged(int)), this, SLOT(enable_checkbox_moduli_dx()));

  connect(ui->checkBox_sinistro, SIGNAL(stateChanged(int)), this, SLOT(enable_checkbox_moduli_sx()));
  connect(ui->checkBox_spalla, SIGNAL(stateChanged(int)), this, SLOT(enable_checkbox_moduli_spalla()));
  connect(ui->checkBox_gomito, SIGNAL(stateChanged(int)), this, SLOT(enable_checkbox_moduli_gomito()));
  connect(ui->checkBox_polso, SIGNAL(stateChanged(int)), this, SLOT(enable_checkbox_moduli_polso()));
  //timer = new QTimer(this);
  //timer_init = new QTimer(this);
  timer_rehab = new QTimer(this);
  timer_val = new QTimer(this);
  timer_feedback = new QTimer(this);
  timer_comp = new QTimer (this);
  ROS_INFO("TIMER");


  connect(timer_rehab, SIGNAL(timeout()),this,SLOT(next_img()));


  // msec

  connect(ui->horizontalSlider_comp, SIGNAL(valueChanged(int)), ui->progressBar_comp, SLOT(setValue(int)));
  connect(ui->progressBar_comp, SIGNAL(valueChanged(int)), ui->lcdNumber, SLOT(display(int)));
  connect(ui->progressBar_comp, SIGNAL(valueChanged(int)), this, SLOT(set_comp_param()));

  connect(ui->horizontalSlider_comp_ses, SIGNAL(valueChanged(int)), ui->progressBar_comp_ses, SLOT(setValue(int)));
  connect(ui->progressBar_comp_ses, SIGNAL(valueChanged(int)), ui->lcdNumber_comp_ses, SLOT(display(int)));
  connect(ui->progressBar_comp_ses, SIGNAL(valueChanged(int)), this, SLOT(set_comp_param_ses()));

  connect(ui->horizontalSlider_comp_avam, SIGNAL(valueChanged(int)), ui->progressBar_comp_avam, SLOT(setValue(int)));
  connect(ui->progressBar_comp_avam, SIGNAL(valueChanged(int)), ui->lcdNumber_comp_avam, SLOT(display(int)));
  connect(ui->progressBar_comp_avam, SIGNAL(valueChanged(int)), this, SLOT(set_comp_param()));

  connect(ui->horizontalSlider_comp_avam_ses, SIGNAL(valueChanged(int)), ui->progressBar_comp_avam_ses, SLOT(setValue(int)));
  connect(ui->progressBar_comp_avam_ses, SIGNAL(valueChanged(int)), ui->lcdNumber_comp_avam_ses, SLOT(display(int)));
  connect(ui->progressBar_comp_avam_ses, SIGNAL(valueChanged(int)), this, SLOT(set_comp_param_ses()));
  //  ui->lcdNumber_j1->display(ROM_rad[0]);
  //  ui->lcdNumber_j2->display(ROM_rad[1]);
  //  ui->lcdNumber_j3->display(ROM_rad[2]);
  //  ui->lcdNumber_j4->display(ROM_rad[3]);
  //  ui->lcdNumber_j5->display(ROM_rad[4]);
//connect(ui->lcdNumber_j1, SIGNAL(display(int)),ui->dial_j1, SLOT(setValue(int)));

  ui->progressBar_comp->setValue(ui->horizontalSlider_comp->value());
  ui->progressBar_comp_ses->setValue(ui->horizontalSlider_comp_ses->value());




  //SETTO IMMAGINI
  QPixmap pic1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/passivo.png");
  ui->label_pass->setPixmap(pic1);

  QPixmap pic2("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/trigger.png");
  ui->label_trigger->setPixmap(pic2);

  QPixmap pic3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/asan.png");
  ui->label_asasne->setPixmap(pic3);

  QPixmap pic4("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/antig.png");
  ui->label_antig->setPixmap(pic4);

  QPixmap pic5("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/chall.png");
  ui->label_chall->setPixmap(pic5);

  QPixmap pic_trasp("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/mode_trasparente.png");
  ui->label_trasp->setPixmap(pic_trasp);

  QPixmap pic6("/home/alice/catkin_ws/src/agree_gui/resources/images/img/arm/bracciodx.png");
  //ui->label_4_dx_3->setPixmap(pic6);



  QPixmap pic12("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/iniz.png");
  ui->label_wait->setPixmap(pic12);


  QPixmap pic13("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/emergenza.png");
  ui->label_allarme_2->setPixmap(pic13);



  QPixmap pic14("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/cal_mat.png");
  ui->label_cal_pad->setPixmap(pic14);

  QPixmap pic15("/home/alice/catkin_ws/src/agree_gui/resources/images/img/arm/bracciodx.png");
  ui->label_dimensionebraccio->setPixmap(pic15);

  QPixmap deltoids ("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/IMG_GUI/IMG_EMG/deltoids.png");
  ui->label_deltoids->setPixmap(deltoids);

  QPixmap biceps ("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/IMG_GUI/IMG_EMG/biceps.png");
  ui->label_biceps->setPixmap(biceps);

  QPixmap triceps ("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/IMG_GUI/IMG_EMG/triceps.png");
  ui->label_triceps->setPixmap(triceps);


  // setto icone
  ui->pushButton_cerca_3->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Zoom.png"));
  ui->pushButton_elencoPazienti->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Database.png"));
  ui->pushButton_eliminapaziente->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Delete.png"));
  ui->pushButton_utente->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Person.png"));
  ui->pushButton_home->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Home.png"));
  ui->pushButton_nuovopaziente->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Add.png"));
  ui->pushButton_modifica->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Modify.png"));
  ui->pushButton_vestizioneAgree->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Movie.png"));
  ui->pushButton_salva->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
  ui->pushButton_salva_2->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
  ui->pushButton_salva_recap->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
  ui->pushButton_salvamoduli->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
  ui->pushButton_salvaconf->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
  //ui->pushButton_controllo->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
  ui->pushButton_salvaex->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
  ui->pushButton_salvatapp->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));
  ui->pushButton_salta->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Forward.png"));
  ui->pushButton_indietro_2->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Back.png"));
  ui->pushButton_prosegui->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Fast-forward.png"));
  ui->pushButton_go->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Forward"));
  ui->pushButton_logout->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Turn off"));
  ui->pushButton_go->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Fast-forward"));
  ui->pushButton_avanti_v->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Forward"));
  ui->pushButton_allarme->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Stop sign"));
  ui->pushButton_add->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Add"));
  ui->pushButton_add_2->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Add"));
  ui->pushButton_remove->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Remove"));
  ui->pushButton_remove_2->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Remove"));
  ui->pushButton_indietro->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Go back.png"));
  ui->pushButton_esplorarom->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Application.png"));
  ui->pushButton_next->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Clock.png"));
  ui->pushButton_ok->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/OK.png"));
  ui->pushButton_riprendi->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Redo.png"));
  ui->pushButton_termina->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Abort.png"));
  ui->pushButton_conferma_recap->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/OK.png"));
  ui->pushButton_modifica_recap->setIcon(QIcon("/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Modifiy.png"));
  ui->pushButton_salva_exo_param->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Save.png"));

  //ui->pushButton_indietro_EMG->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Back.png"));
  ui->pushButton_salta_EMG->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Fast-forward.png"));
  // ui->pushButton_avanti_EMG->setIcon(QIcon("/home/alice/catkin_ws/src/agree_gui/resources/images/img/icone/Forward.png"));

  ui->label_tut->setText("Seguire le istruzioni per il Montaggio dei moduli selezionati. \nPer Saltare il Tutorial fare click su 'Salta Tutorial' ");
  ui->label_istr_vest->setText("Indossare l'esoscheletro sul Paziente.\n\nVerificare la vestibilità sul Paziente.\n\nUna volta effettuata la procedura premere Avanti per Continuare.");
  //creo la data
  QDate data;
  data= QDate::currentDate();
  dati::data1= data.toString(Qt::ISODate);
  ui->label_date->setText(data.toString());


  QSqlDatabase mydb2 = QSqlDatabase::database();


  ui->pushButton_show_pdf->setEnabled(false);


}


paginaprincipale::~paginaprincipale()
{
  delete ui;
}

/**********************************************************************************/

/**********************       HOME PAGE FUNCTION             *********************/

/**********************************************************************************/

/**********************       INSERT NEW PATIENT             *********************/
void paginaprincipale::on_pushButton_nuovopaziente_clicked()
{    ROS_INFO("NUOVOPAZIENTE");
     qDebug()<< "nuovopaziente";
        ui->stackedWidget->setCurrentWidget(ui->page_4);
           flag=1; //nuovo paziente
              ui->lineEdit_nome->clear();
                 ui-> lineEdit_cognome -> clear();
                    ui-> lineEdit_datanascita ->clear();
                       ui-> lineEdit_patologia -> clear();
                          ui->lineEdit_storiaclinica ->clear();
                             ui->lineEdit_braccio->clear();
                                ui ->lineEdit_avambraccio->clear();
                                   QSqlQuery query;
                                      query.prepare("select count (*) from Count");
                                         query.exec();
                                            while(query.next())
                                            {
                                              query.first();
                                              dati::count= query.value(0).toString();
                                              qDebug()<< dati::count;
                                            }
}

/**********************       SAVE PATIENT (BOTH FOR NEW AND EDITING)  *********************/
void paginaprincipale::on_pushButton_salva_clicked()
{

  QString Data, Sesso, Patologia, Lato, storiaclinica,sigla, altezza, peso;
  dati::NomeP = ui->lineEdit_nome-> text();
  dati::CognomeP = ui-> lineEdit_cognome -> text();
  Data = ui-> lineEdit_datanascita -> text();
  Sesso = ui-> comboBox_sesso -> currentText();
  Patologia = ui-> lineEdit_patologia -> text();
  Lato = ui-> comboBox_latodominante-> currentText();
  storiaclinica = ui->lineEdit_storiaclinica ->text();

  altezza = ui-> lineEdit_h-> text();
  peso = ui->lineEdit_peso->text();
  dati::sigla = "p";

  if(flag==1)
    // controllo unicità paziente
  { QSqlQuery qry11;
    qry11.prepare("select * from Pazienti where NomePaziente = '"+dati::NomeP+"'and  Cognome = '"+dati::CognomeP+"' ");
    qry11.exec();
    if (qry11.exec()){
      int cont=0;
      while(qry11.next())
      {
        cont++;
      }
      // se paziente unico lo salvo
      if (cont==0) {
        if (!(dati::NomeP=="") || !(dati::CognomeP == "")){

          dati::codice_id= dati::NomeP + dati::CognomeP + dati::sigla+dati::count;
          QSqlQuery qry;
          qry.prepare("insert into Pazienti (Codice_ID, UsernameDOC, NomePaziente, Cognome, DatadiNascita, Patologia, Sesso, Lato_paretico, Altezza, Peso, StoriaClinica) values ('"+dati::codice_id+"', '"+dati::username+"', '"+dati::NomeP+"', '"+dati::CognomeP+"','"+Data+"', '"+Patologia+"', '"+Sesso+"', '"+Lato+"', '"+altezza+"', '"+peso+"', '"+storiaclinica+"')" );
          if(qry.exec()) {
            // se lo salvo lo comunico e copio username in tabella count
            //QMessageBox ::information(this,tr("Salvataggio"),tr(" Paziente Salvato Correttamente"));
            ui->stackedWidget->setCurrentWidget(ui->page_3);
            QSqlQuery qryc;
            qryc.prepare("insert into Count (username,cont) values('"+dati::codice_id+"', '"+dati::count+"')");
            qryc.exec();
          }
          else qDebug()<<qry.lastError();
        }
        else {
          QMessageBox::warning(this,tr("Attenzione"), tr("Inserire Nome e Cognome del paziente!"));
        }
      }
      // se esiste già non  eseguo la  query
      else if (cont==1)
      {
        QMessageBox ::critical(this,tr("Errore"),tr("Attenzione: Paziente già presente nel database"));
      }
    }
    else qDebug()<<qry11.lastError();
  }
  if (flag==2) {
    qDebug()<<dati::count_act;
    dati::codice_id= dati::NomeP+ dati::CognomeP+ dati::sigla+ dati::count_act;
    qDebug()<<dati::codice_id;

    QSqlQuery qry6;
    qry6.prepare("update Pazienti set Codice_ID= '"+dati::codice_id+"', NomePaziente ='"+dati::NomeP+"', Cognome= '"+dati::CognomeP+"', DatadiNascita= '"+Data+"',  Patologia = '"+Patologia+"', Sesso='"+Sesso+"', Lato_paretico = '"+Lato+"', Altezza='"+altezza+"', Peso= '"+peso+"', StoriaClinica = '"+storiaclinica+"'  where Codice_ID = '"+dati::ind+"'");
    if (qry6.exec())
    {
    //  QMessageBox ::information(this,tr("Modifica"),tr(" Dati del Paziente Modificati Correttamente"));
      QMessageBox::information(this, tr("Information"), tr("Premere Elenco Pazienti per aggiornare il database dei Pazienti"));
      ui->stackedWidget->setCurrentWidget(ui->page_3);

      QSqlQuery qry12;
      qry12.prepare("update Count set username= '"+dati::codice_id+"'  where cont = '"+dati::count_act+"'");
      qry12.exec();
    }
    else {
      QMessageBox ::critical(this,tr("Errore"),tr("bo3"));

    }
  }
}

/**********************      UPLOAD PATIENT TABLE                       *********************/
void paginaprincipale::on_pushButton_elencoPazienti_clicked()
{
  QSqlQueryModel *model = new QSqlQueryModel();
  QSqlQuery * qry1 = new QSqlQuery(mydb2);
  qry1 -> prepare("select rowid, Codice_ID, NomePaziente, Cognome, DatadiNascita, Patologia, Sesso, Lato_paretico, LunghezzaBraccio, LunghezzaAvambraccio, StoriaClinica from Pazienti where UsernameDOC = '"+dati::username+"' order by Cognome  asc");
  qry1 -> exec();
  if(qry1->exec()) {
    model -> setQuery(*qry1);
    ui->tableView_database->setModel(model);
    ui->tableView_database->resizeColumnsToContents();


  }
  else qDebug()<<qry1->lastError();
}

/**********************       DOUBLE MOUSE CLICK ACVIVATED                 *********************/
void paginaprincipale::on_tableView_database_activated(const QModelIndex &index)
{
  dati::ind= ui-> tableView_database->model()->data(index).toString();
  flag= 3; //paziente selezionato
}

/**********************       DELETE PATIENT                      *********************/
void paginaprincipale::on_pushButton_eliminapaziente_clicked()
{   if(flag==3)
  {
    QSqlQuery qry7;
    qry7.prepare("select NomePaziente, Cognome from Pazienti  where Codice_ID= '"+dati::ind+"'");
    qry7.exec();
    while(qry7.next())
    {
      dati::NomeP = qry7.value(0).toString();
      dati::CognomeP = qry7.value(1).toString();

      QMessageBox risposta;
      risposta.setText(tr("Si è scelto eliminare i dati relativi al paziente : %1 %2") .arg(dati::NomeP).arg(dati::CognomeP));
      QAbstractButton* pButtonYes = risposta.addButton(tr("Conferma"), QMessageBox::YesRole);
      QAbstractButton* pButtonNo =  risposta.addButton(tr("No"), QMessageBox::NoRole);
      risposta.exec();
      if(risposta.clickedButton()==pButtonYes)
      {
        QSqlQuery qry4;
        qry4.prepare("delete from Pazienti where Codice_ID ='"+dati::ind+"'");
        qry4.exec();

        QSqlQuery qry5;
        qry5.prepare("delete from Parametri_Paziente where Codice_ID ='"+dati::ind+"'");
        qry5.exec();
      //  QMessageBox ::information(this,tr("Eliminazione"),tr("Paziente Eliminato"));
        QMessageBox::information(this, tr("Information"), tr("Premere Elenco Pazienti per aggiornare il database dei Pazienti"));

      }
      else if(risposta.clickedButton()==pButtonNo)
      {
        ui->stackedWidget->setCurrentWidget(ui->page_3);
      }
    }

  }
  else
  {
    QMessageBox ::warning(this,tr("Attenzione"),tr("Selezionare con doppio click il paziente che si vuole eliminare"));
  }
}

/**********************       EDIT PATIENT                       *********************/
void paginaprincipale::on_pushButton_modifica_clicked()
{ if (flag==3)
  {
    ui->stackedWidget->setCurrentWidget(ui->page_4);

    QSqlQuery qry5;
    qry5.prepare("select * from Pazienti where Codice_ID = '"+dati::ind+"'");
    if (qry5.exec())
    {
      while(qry5.next())
      { flag=2; //modifica paziente
        ui->lineEdit_nome ->setText(qry5.value(2).toString());
        ui->lineEdit_cognome->setText(qry5.value(3).toString());
        ui->lineEdit_datanascita ->setText(qry5.value(4).toString());
        ui->comboBox_sesso->setCurrentText(qry5.value(6).toString());
        ui->lineEdit_patologia ->setText(qry5.value(5).toString());
        ui->comboBox_latodominante->setCurrentText(qry5.value(7).toString());
        ui->lineEdit_h->setText(qry5.value(8).toString());
        ui->lineEdit_peso->setText(qry5.value(9).toString());
        ui->lineEdit_storiaclinica ->setText(qry5.value(12).toString());
        ui->lineEdit_braccio->setText(qry5.value(10).toString());
        ui->lineEdit_avambraccio->setText(qry5.value(11).toString());
        QSqlQuery prova1;
        prova1.prepare("select cont from Count where username = '"+dati::ind+"'");
        prova1.exec();
        while(prova1.next())
        { dati::count_act= prova1.value(0).toString();
          qDebug()<< dati::count_act;
        }
      }
    }

    else {
      QMessageBox ::critical(this,tr("Errore"),tr("boh2"));
    }
  }
  else {
    QMessageBox ::warning(this,tr("Attenzione"),tr("Selezionare con doppio click il paziente che si vuole Modificare"));

  }
}

/**********************       EDIT THERAPIST DATA                       *********************/
void paginaprincipale::on_pushButton_utente_clicked()
{
  ui->stackedWidget->setCurrentWidget(ui->page_5);
  QSqlQuery qry3;
  qry3.prepare("select * from Users where Username = '"+dati::username+"'");
  if (qry3.exec())
  {
    while(qry3.next())
    {
      ui->lineEdit_nome_2 ->setText(qry3.value(0).toString());
      ui->lineEdit_cognome_2->setText(qry3.value(1).toString());
      ui->lineEdit_data ->setText(qry3.value(2).toString());
      ui->lineEdit_password_2 ->setText(qry3.value(4).toString());
      ui->lineEdit_conferma ->setText(qry3.value(4).toString());
      dati::uservecchio=dati::username;
      QString profilo = qry3.value(5).toString();
      if(profilo == "1") ui->radioButton_terapista->setChecked(true);
      else if(profilo == "2") ui->radioButton_tecnico->setChecked(true);
      else if(profilo == "3") ui->radioButton_utente->setChecked(true);
    } }
  else
  {
    QMessageBox ::critical(this,tr("Errore"),tr("boh3"));
  }
  QSqlQuery prova1;
  prova1.prepare("select cont from Count where username = '"+dati::username+"'");
  prova1.exec();
  while(prova1.next())
  {
    dati::count_act= prova1.value(0).toString();
    qDebug()<< dati::count_act;
  }
}

/**********************       SAVE EDITED THERAPIST DATA                       *********************/
void paginaprincipale::on_pushButton_salva_2_clicked()
{
  QSqlQuery qry6;
  QString Profilo;
  dati::Nome = ui->lineEdit_nome_2-> text();
  dati::Cognome = ui->lineEdit_cognome_2->text();
  dati::Data = ui->lineEdit_data->text();
  if(ui->radioButton_terapista->isChecked())
  {
    Profilo =QString::number(1); // creo una variabile in qui assegno un valore in base al radio button selezionato. a questo punto riassocio la variabile all'elemento della struct che si riferisce alla colonna della tabella in cui sto scrivendo,mi serve per poter leggere da database i diversi profili e quindi aprire diverse finestre a seconda del profilo selezionato
    dati::profilo = Profilo.toInt();
    dati::sigla= "t";
  }
  else if(ui->radioButton_tecnico ->isChecked())
  {
    Profilo =QString::number(2);
    dati::profilo = Profilo.toInt();
    dati::sigla= "tc";
  }
  else if(ui->radioButton_utente ->isChecked())
  {
    Profilo=QString::number(3);
    dati::profilo = Profilo.toInt();
    dati::sigla = "u";
  }
  dati::username = dati::Nome+ dati::Cognome + dati::sigla + dati::count_act;
  qDebug()<< dati::username;

  qry6.prepare("update Users set Username= '"+dati::username+"', Nome ='"+dati::Nome+"', Cognome= '"+dati::Cognome+"', Data_di_Nascita= '"+dati::Data+"',  Password= '"+dati::password+"' where Username = '"+dati::uservecchio+"'");
  if (qry6.exec())
  {
  //  QMessageBox ::information(this,tr("Modifica"),tr("Dati Utente Modificati Correttamente"));
    ui->stackedWidget->setCurrentWidget(ui->page_3);

    qDebug() << dati::username;
    QSqlQuery qry12;
    qry12.prepare("update Count set username= '"+dati::username+"'  where cont = '"+dati::count_act+"'");
    qry12.exec();
    if(qry12.exec())
    {
      QSqlQuery prova2;
      prova2.prepare("update Pazienti set UsernameDoc = '"+dati::username+"' where UsernameDoc = '"+dati::uservecchio+"'" );
      prova2.exec();
    }
  }
  else
  {
    QMessageBox ::critical(this,tr("Errore"),tr("bo3"));
  }

  ui->label_status->setText(QString("Terapista: %1 %2").arg(dati::Nome) .arg(dati::Cognome));
}

/**********************       START REHAB CONFIGURATION                       *********************/
void paginaprincipale::on_pushButton_vestizioneAgree_clicked()
{   //  if (dati::command == 3){
  if (flag==3)
  {
    qDebug()<< dati::ind;
    QSqlQuery qry7;
    qry7.prepare("select NomePaziente, Cognome from Pazienti  where codice_ID= '"+dati::ind+"'");
    qry7.exec();
    while(qry7.next())
    {
      dati::NomeP = qry7.value(0).toString();
      dati::CognomeP = qry7.value(1).toString();
      ui->label_status2->setText(qry7.value(0).toString()+ " "+ qry7.value(1).toString());
      QMessageBox risposta;
      risposta.setText(tr("Si è scelto di iniziare la sessione di terapia del paziente : %1 %2") .arg(dati::NomeP).arg(dati::CognomeP));
      QAbstractButton* pButtonYes = risposta.addButton(tr("Conferma"), QMessageBox::YesRole);
      QAbstractButton* pButtonNo =  risposta.addButton(tr("No"), QMessageBox::NoRole);
      risposta.exec();
      if(risposta.clickedButton()==pButtonYes)

      {

        QSqlQuery selezione; // selezioni l'ultima riga salvata con questo codice id
        selezione.prepare ("select *  from Parametri_Paziente where Codice_ID = '"+dati::ind+"' order by Data_acquisizione desc limit 1");
        if (selezione.exec())
        {
          while(selezione.next())
          {
            QString FESm2, FESM2, AASm2, AASM2, RIESm2, RIESM2, Gm2, GM2, Pm2, PM2, Lunghezza_b, Lunghezza_a, comp_exo, comp_exo_forearm;
            dati::data_vecchia = selezione.value(2).toString();
            FESm2 = selezione.value(3).toString();
            FESM2 = selezione.value(4).toString();
            AASm2 = selezione.value(5).toString();
            AASM2 = selezione.value(6).toString();
            RIESm2 = selezione.value(7).toString();
            RIESM2 = selezione.value(8).toString();
            Gm2 = selezione.value(9).toString();
            GM2 = selezione.value(10).toString();
            Pm2 = selezione.value(11).toString();
            PM2 = selezione.value(12).toString();
            dati::lato_prec= selezione.value(13).toString();
            dati::modulo_spalla_prec = selezione.value(14).toString();
            dati::modulo_gomito_prec = selezione.value(15).toString();
            dati::modulo_polso_prec = selezione.value(16).toString();
            dati::modulo_eeg_prec = selezione.value(17).toString();
            dati::modulo_emg_prec = selezione.value(18).toString();
            dati::mano_prec = selezione.value(19).toString();
            dati::oi_prec = selezione.value(20).toString();
            dati::mood_prec = selezione.value(21).toString();
            dati::l_eeg_p = dati::modulo_eeg_prec.length();
            dati::l_emg_p = dati::modulo_emg_prec.length();
            dati::l_m_p = dati::mano_prec.length();
            dati::l_oi_p = dati::oi_prec.length();
            dati::ex1_prec= selezione.value(22).toString();
            dati::rip1_prec = selezione.value(23).toString();
            dati::ogg1_prec = selezione.value(24).toString();
            dati::ex2_prec = selezione.value(25).toString();
            dati::rip2_prec = selezione.value(26).toString();
            dati::ogg2_prec = selezione.value(27).toString();
            dati::ex3_prec = selezione.value(28).toString();
            dati::rip3_prec = selezione.value(29).toString();
            dati::ogg3_prec = selezione.value(30).toString();
            dati::ex4_prec = selezione.value(31).toString();
            dati::rip4_prec = selezione.value(32).toString();
            dati::ogg4_prec = selezione.value(33).toString();
            dati::ex5_prec = selezione.value(34).toString();
            dati::rip5_prec = selezione.value(35).toString();
            dati::ogg5_prec = selezione.value(36).toString();
            dati::ex6_prec = selezione.value(37).toString();
            dati::rip6_prec = selezione.value(38).toString();
            dati::ogg6_prec = selezione.value(39).toString();
            dati::ex7_prec= selezione.value(40).toString();
            dati::rip7_prec = selezione.value(41).toString();
            dati::ogg7_prec = selezione.value(42).toString();
            dati::lex1 = dati::ex1_prec.length();
            dati::lex2 = dati::ex2_prec.length();
            dati::lex3 = dati::ex3_prec.length();
            dati::lex4 = dati::ex4_prec.length();
            dati::lex5 = dati::ex5_prec.length();
            dati::lex6 = dati::ex6_prec.length();
            dati::lex7 = dati::ex7_prec.length();
            comp_exo_forearm = selezione.value(43).toString();
            comp_exo = selezione.value(44).toString();
            Lunghezza_a = selezione.value(48).toString();
            Lunghezza_b = selezione.value(49).toString();
            dati::mode_output = selezione.value(52).toString();

            if(dati::mode_output =="1") {
              dati::mode_output = "Passiva";
            }
            else if(dati::mode_output =="2") {
              dati::mode_output  = "Trigger";
            }
            else if(dati::mode_output =="3") {
              dati::mode_output  = "Assisted as needed";
            }
            else if(dati::mode_output =="4") {
              dati::mode_output  = "Anti-gravitaria";
            }
            else if(dati::mode_output =="5") {
              dati::mode_output  = "Trasparente";
            }
            else if(dati::mode_output =="6") {
              dati::mode_output  = "Challenging";
            }




            ui->lineEdit_flessospallamin->setText(FESm2);
            ui->lineEdit_flessospallamax->setText(FESM2);
            ui->lineEdit_adduzionespallamin->setText(AASm2);
            ui->lineEdit_adduzionespallamax->setText(AASM2);
            ui->lineEdit_rotazionespallamin->setText(RIESm2);
            ui->lineEdit_rotazionespallamax->setText(RIESM2);
            ui->lineEdit_gomitomin->setText(Gm2);
            ui->lineEdit_gomitomax->setText(GM2);
            ui ->lineEdit_polsomin->setText(Pm2);
            ui->lineEdit_polsomax->setText(PM2);
            ui->label_59-> setText("La sessione precedente si è utilizzato questo parametro di compensazione.\n Verificalo e aggiornalo.\n\n Quindi premi Salva.\n\nPotrai modificare questo parametro in qualsiasi momento.");
            ui->lcdNumber->display(comp_exo.toInt());
            ui->progressBar_comp->setValue(comp_exo.toInt());
            ui->horizontalSlider_comp->setValue(comp_exo.toInt());
            ui->lcdNumber_comp_ses->display(comp_exo.toInt());
            ui->progressBar_comp_ses->setValue(comp_exo.toInt());
            ui->horizontalSlider_comp_ses->setValue(comp_exo.toInt());
            ui->lcdNumber_comp_avam->display(comp_exo_forearm.toInt());
            ui->progressBar_comp_avam->setValue(comp_exo_forearm.toInt());
            ui->horizontalSlider_comp_avam->setValue(comp_exo_forearm.toInt());
            ui->lcdNumber_comp_avam_ses->display(comp_exo_forearm.toInt());
            ui->progressBar_comp_avam_ses->setValue(comp_exo_forearm.toInt());
            ui->horizontalSlider_comp_avam_ses->setValue(comp_exo_forearm.toInt());


            ui->label_istr_agg_param_exo-> setText("Durante la precedente sessione sono state inserite\n\nle lunghezze che vedi qui riportate.\n\nVerificale sull'esoscheltro e aggiornale.\n\nQuindi premi Salva");
            ui->lineEdit_braccio->setText(Lunghezza_b);
            ui->lineEdit_avambraccio->setText(Lunghezza_a);

            //            QSqlQuery agg_param_exo;
            //            agg_param_exo.prepare("select from Pazienti(LunghezzaBraccio, LunghezzaAvambraccio) where Codice_ID = '"+dati::ind+"'");
            //            agg_param_exo.exec();
            //            while(agg_param_exo.next()) {
            //              ui->lineEdit_braccio->setText(agg_param_exo.value(0).toString());
            //              ui->lineEdit_avambraccio->setText(agg_param_exo.value(1).toString());
            //              ui->label_istr_agg_param_exo->setText("Quelli che vedi sono i parametri salvati durante la sessione precedente.\nControlla la corrispondenza con le misure sull'esoscheltro, in caso contrario inserisci nuovamente le misure che leggi da AGREE. \nPremi Salva per continuare la configurazione.");
            //            }


            flag = 4; //rilevo la presenza di una configurazione precedente
          }
        }
        if (!(flag==4))
        {
          QString FESm1, FESM1, AASm1, AASM1, RIESm1, RIESM1,Gm1, GM1, Pm1,PM1;

          FESm1= ui->lineEdit_flessospallamin->placeholderText();
          FESM1 = ui->lineEdit_flessospallamax->placeholderText();
          AASm1= ui->lineEdit_adduzionespallamin->placeholderText();
          AASM1 = ui->lineEdit_adduzionespallamax->placeholderText();
          RIESm1= ui->lineEdit_rotazionespallamin->placeholderText();
          RIESM1 = ui->lineEdit_rotazionespallamax->placeholderText();
          Gm1= ui->lineEdit_gomitomin->placeholderText();
          GM1 = ui->lineEdit_gomitomax->placeholderText();
          Pm1 = ui ->lineEdit_polsomin->placeholderText();
          PM1 = ui->lineEdit_polsomax->placeholderText();
          ui->lineEdit_flessospallamin->setText(FESm1);
          ui->lineEdit_flessospallamax->setText(FESM1);
          ui->lineEdit_adduzionespallamin->setText(AASm1);
          ui->lineEdit_adduzionespallamax->setText(AASM1);
          ui->lineEdit_rotazionespallamin->setText(RIESm1);
          ui->lineEdit_rotazionespallamax->setText(RIESM1);
          ui->lineEdit_gomitomin->setText(Gm1);
          ui->lineEdit_gomitomax->setText(GM1);
          ui ->lineEdit_polsomin->setText(Pm1);
          ui->lineEdit_polsomax->setText(PM1);


          QSqlQuery insert;
          insert.prepare("insert into Parametri_Paziente (Codice_ID, UsernameDoc, Data_acquisizione) values ('"+dati::ind+"', '"+dati::username+"', '"+dati::data1+"')");
          if (insert.exec())
          {
            ui->tabWidget->setCurrentWidget(ui->tab_2);
            ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
          }
          //  }
        }
        if (flag==4)
        {

          QSqlQuery insert;
          insert.prepare("insert into Parametri_Paziente (Codice_ID, UsernameDoc, Data_acquisizione) values ('"+dati::ind+"', '"+dati::username+"', '"+dati::data1+"')");

          if (insert.exec())
          {
            if(dati::lato_prec == "0") ui->checkBox_sinistro->setChecked(true);
            else if (dati::lato_prec == "1") ui->checkBox_destro->setChecked(true);

            if(dati::modulo_spalla_prec=="1" && dati::modulo_gomito_prec=="0" && dati::modulo_polso_prec=="0")
            {
              dati::modulo_prec1= "Spalla";

              ui->checkBox_spalla->setChecked(true);
            }
            if (dati::modulo_gomito_prec== "1" && dati::modulo_polso_prec =="0") {
              dati::modulo_prec1 = "Spalla e Gomito";

              ui-> checkBox_gomito ->setChecked(true);
            }
            if (dati::modulo_polso_prec=="1") {
              dati::modulo_prec1 = "Spalla, Gomito e Polso";

              ui->checkBox_polso->setChecked(true);
            }

            if (dati::modulo_emg_prec=="1")
            {
              ui->checkBox_emg_2->setChecked(true);
            }
            else if(dati::modulo_eeg_prec=="1")
            {
              ui->checkBox_eeg_2->setChecked(true);
            }
            else {
              ui->checkBox_eeg_2->setChecked(false);
              ui->checkBox_emg_2->setChecked(false);
            }
            if(dati::mano_prec=="1") //ho cambiato qui
            {
              ui->checkBox_MAP_2->setChecked(true);
              //  prova= 5;
            }
            else {
              ui->checkBox_MAP_2->setChecked(false);
            }




          }
          ui->tabWidget->setCurrentWidget(ui->tab_2);
          ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
        }


        else if(risposta.clickedButton()==pButtonNo){
          ui->tabWidget->setCurrentWidget(ui->tab);
          ui->stackedWidget->setCurrentWidget(ui->page_3);
        }
      }
    }
  }
  else
  {
    QMessageBox ::warning(this,tr("Attenzione"),tr("Selezionare con doppio click il paziente di cui si vuole iniziare la seduta riabilitativa"));

  }
  // }
  QString l_b, l_a, h, p;
  QSqlQuery lunghezza;
  lunghezza.prepare("select Altezza, Peso, LunghezzaBraccio, LunghezzaAvambraccio from Pazienti where Codice_ID = '"+dati::ind+"' ");
  lunghezza.exec();
  while(lunghezza.next()) {
    h= lunghezza.value(0).toString();
    p = lunghezza.value(1).toString();
    l_b = lunghezza.value(2).toString();
    l_a = lunghezza.value(3).toString();

  }

  upperarm = l_b.toDouble();
  lowerarm = l_a.toDouble();
  height = h.toDouble();
  weight = p.toDouble();

  UA_m = double(0.028)*weight;
  LA_m = double(0.016)*weight;
  H_m = double(0.006)*weight;
  //mandali nei ROS param


  ros::NodeHandle n;

  n.setParam("/physiological_param/height", height);
  n.setParam("/physiological_param/weight", weight);
  n.setParam("/physiological_param/mass_upperarm", UA_m);
  n.setParam("/physiological_param/mass_lowerarm", LA_m);
  n.setParam("/physiological_param/mass_hand", H_m);
  std::string codice_id_paziente, patient_name, patient_surname;
  codice_id_paziente = dati::ind.toUtf8().constData();
  patient_name = dati::NomeP.toUtf8().constData();
  patient_surname = dati::CognomeP.toUtf8().constData();
  n.setParam("/evaluation/Code_ID_patient", codice_id_paziente);
  n.setParam("/evaluation/Patient_Name", patient_name);
  n.setParam("/evaluation/Patient_Surname", patient_surname);

  QString ua_m, la_m, h_m;
  ua_m = QString::number(UA_m);
  la_m = QString::number(LA_m);
  h_m = QString::number(H_m);
  QSqlQuery masse;
  masse.prepare("update Pazienti set UA_m = '"+ua_m+"', LA_m = '"+la_m+"', H_m = '"+h_m+"' where Codice_ID = '"+dati::ind+"'");
  if(masse.exec()){
    //  QMessageBox ::information(this,tr("Salvato"),tr("Parametri Salvati"));

  }
  else qDebug()<< "non funzioano le masse";




}

/**********************       SEARCH FOR PATIENT BY SURNAME                       *********************/
void paginaprincipale::on_pushButton_cerca_3_clicked()
{
  QString Ricerca;
  Ricerca= ui->lineEdit_cercapaziente_3->text();

  QSqlQueryModel *model1 = new QSqlQueryModel();
  QSqlQuery * qry10 = new QSqlQuery(mydb2);
  qry10->prepare("Select * from Pazienti where Cognome= '"+Ricerca+"'");
  qry10 -> exec();
  model1 -> setQuery(*qry10);
  ui->tableView_database->setModel(model1);
  qDebug() << (model1->rowCount());
}


/**********************       HOME (CLEAN ALL THE GUI)             *********************/
void paginaprincipale::on_pushButton_home_clicked()
{
  ui->tabWidget->setCurrentWidget(ui->tab);
  ui->stackedWidget->setCurrentWidget(ui->page_3);
  ui->checkBox_sinistro->setChecked(false);
  ui->checkBox_destro->setChecked(false);
  ui->checkBox_eeg_2->setChecked(false);
  ui->checkBox_emg_2->setChecked(false);
  ui->checkBox_MAP_2->setChecked(false);
  ui->checkBox_spalla->setChecked(false);
  ui->checkBox_gomito->setChecked(false);
  ui->checkBox_polso->setChecked(false);

  ui->checkBox_ex1->setChecked(false);
  ui->checkBox_ex2->setChecked(false);
  ui->checkBox_ex3->setChecked(false);
  ui->checkBox_ex4->setChecked(false);
  ui->checkBox_ex5->setChecked(false);
  ui->checkBox_ex6->setChecked(false);
  ui->checkBox_7->setChecked(false);
  ui->comboBox_ex1->setCurrentIndex(0);
  ui->comboBox_ex2->setCurrentIndex(0);
  ui->comboBox_ex3->setCurrentIndex(0);
  ui->comboBox_ex4->setCurrentIndex(0);
  ui->comboBox_ex5->setCurrentIndex(0);
  ui->comboBox_ex6->setCurrentIndex(0);
  ui->comboBox_ex7->setCurrentIndex(0);

  dati::status1 = SC1_EVALUATION;

  std_msgs::Int16 msg_status;
  msg_status.data = dati::status1;
  ROS_INFO ("%d", msg_status.data);
  status_publisher.publish(msg_status);
  //AZZERO ROS PARAM
  comp_param = 0;
  comp_forearm=0;
  active_modules = {false, false,false,false,false,false,false,false,false,false};
  mode=0;
  exe1=0;
  exe2=0;
  exe3=0;
  exe4=0;
  exe5=0;
  exe6=0;
  exe7=0;
  rep1=0;
  rep2=0;
  rep3=0;
  rep4=0;
  rep5=0;
  rep6=0;
  rep7=0;
  ros_ogg1=0;
  ros_ogg2=0;
  ros_ogg3=0;
  ros_ogg4=0;
  ros_ogg5=0;
  ros_ogg6=0;
  ros_ogg7=0;
  ex_seq = {exe1, exe2, exe3, exe4, exe5, exe6, exe7};
  ex_rep = {rep1, rep2, rep3, rep4, rep5, rep6, rep7};
  ex_obj = {ros_ogg1, ros_ogg2, ros_ogg3, ros_ogg4, ros_ogg5, ros_ogg6, ros_ogg7};
  point1xp=0;
  point1yp=0;
  point2xp=0;
  point2yp=0;
  point3xp=0;
  point3yp=0;
  curr_ex=0;
  point0p= {0,0};
  point1p= {0,0};
  point2p= {0,0};
  point3p= {0,0};
  ros::NodeHandle n;
  n.setParam ("/physiological_param/arm_compensation", comp_param);
  n.setParam ("/physiological_param/forearm_compensation", comp_forearm);
  n.setParam("/active_modules", active_modules);
  n.setParam("/exercise/sequence", ex_seq);
  n.setParam("/exercise/repetition", ex_rep);
  n.setParam ("/exercise/objects", ex_obj);
  n.setParam ("/exercise/mode", mode);
  n.setParam("/exercise/current_exercise", curr_ex);
 n.setParam("matlab/point1/x", point1xp);
 n.setParam("matlab/point1/y", point1yp);
 n.setParam("matlab/point2/x", point2xp);
 n.setParam("matlab/point2/y", point2yp);
  n.setParam("matlab/point3/x", point3xp);
  n.setParam("matlab/point3/y", point3yp);
  n.setParam("/point0/mat_coordinates", point0p);
  n.setParam("/point1/mat_coordinates", point1p);
  n.setParam("/point2/mat_coordinates", point2p);
  n.setParam("/point3/mat_coordinates", point3p);

}


/**********************************************************************************/

/**********************       SAVE MODULE             *********************/

/**********************************************************************************/

/**********************       ENABLE ACTIVE MODULE CHECKBOXES      **************/
//this functions allow to select only one module for each group (side and exoskeleton modules)
void paginaprincipale::enable_checkbox_moduli_sx() {
  if(ui->checkBox_sinistro->isChecked()) {
    ui->checkBox_destro->setChecked(false);
  }}
void paginaprincipale::enable_checkbox_moduli_dx() {
  if (ui->checkBox_destro->isChecked()) {
    ui->checkBox_sinistro->setChecked(false);
  }
}
void paginaprincipale::enable_checkbox_moduli_spalla() {
  if (ui->checkBox_spalla->isChecked()) {
    ui->checkBox_gomito->setChecked(false);
    ui->checkBox_polso->setChecked(false);
  }
}
void paginaprincipale::enable_checkbox_moduli_gomito() {
  if (ui->checkBox_gomito->isChecked()) {
    ui->checkBox_spalla->setChecked(false);
    ui->checkBox_polso->setChecked(false);
  }
}
void paginaprincipale::enable_checkbox_moduli_polso() {
  if (ui->checkBox_polso->isChecked()) {
    ui->checkBox_gomito->setChecked(false);
    ui->checkBox_spalla->setChecked(false);
  }
}

/**********************************************************************************/

/**********************       ASSEMBLY TUTORIAL             *********************/

/**********************************************************************************/

/**********************       ASSEMBLY IMAGES TUTORIAL                       *********************/
QList<QPixmap>GetImages2(QString tutID) {
  QList<QPixmap> mylist2;
  auto folder2("/home/alice/Desktop/tutorial/" +tutID);
  QDir directory2(folder2);
  QStringList img = directory2.entryList(QStringList() << "*.jpg" << "*.JPG" <<"*.png" << "*.PNG", QDir::Files );
  qDebug()<<directory2;
  qDebug() <<"i found" << img.size();
  foreach (QString filename, img) {
    QPixmap pix2(folder2 + QString("/") + filename);
    mylist2.append(pix2);
    qDebug()<< mylist2;
  }
  return mylist2;
}

/**********************      BACK OF ASSEMBLY IMAGES  *********************/
void paginaprincipale::on_pushButton_indietro_2_clicked()
{ qDebug()<< curTut;
  qDebug()<< curImg;
  if(curImg != 0) {
    curImg --;
    qDebug()<<curImg;


    key2 = sel_tut.at(curTut);
    qDebug() << key2;
    if(TutInfoMap.find(key2) != TutInfoMap.end()) {
      TutInfo &one2 = TutInfoMap[key2];

      if(curImg <  one2.img.size()){
        ui->label_img_tut -> setPixmap(one2.img.at(curImg));

        qDebug() <<curTut;} }

  }

  else if(curImg ==0 && curTut != 0)
  {curTut --;

    key2 = sel_tut.at(curTut);
    qDebug() << key2;
    if(TutInfoMap.find(key2) != TutInfoMap.end()) {
      TutInfo &one2 = TutInfoMap[key2];

      if(curImg < one2.img.size()){
        ui->label_img_tut -> setPixmap(one2.img.at(curImg));

        qDebug() <<curTut;} }

  }
  else {
    qDebug()<< "stop";
  }



}

/**********************       SKIP ASSEMBLY TUTORIAL  *********************/
void paginaprincipale::on_pushButton_prosegui_clicked()
{


  dati::status1 = SC1_EDIT_PATIENT_MODULE_CONTROL;

  std_msgs::Int16 msg;
  msg.data = dati::status1;
  ROS_INFO ("%d", msg.data);
  status_publisher.publish(msg);

}


/**********************       GO FORWARD ASSEMBLY TUTORIAL                      *********************/
void paginaprincipale::on_pushButton_salta_clicked()
{    qDebug() << sel_tut;

     if(curTut<sel_tut.size()) {
       key2 = sel_tut.at(curTut);
       qDebug() << key2;
       if(TutInfoMap.find(key2) != TutInfoMap.end()) {
         TutInfo &one2 = TutInfoMap[key2];
         if(curImg < one2.img.size()){
           ui->label_img_tut -> setPixmap(one2.img.at(curImg));
           ui->label_tut->setText(one2.istr.at(curImg));
           curImg ++;
         }
         if(curImg == one2.img.size()) {
           curImg =0;
           curTut ++;
         }
       }
     }
     else if(curTut== sel_tut.size()) {

       ui->label_img_tut->clear();
       ui->label_tut->setText("");

     }

}

/**********************************************************************************/

/**********************       CONTROL MODE PAGE             *********************/

/**********************************************************************************/

/**********************        TRIGGER CONTROL MODE  *********************/
void paginaprincipale::on_pushButton_4_clicked()
{
  dati::mood = "Trigger";
  ui->comboBox_mode->setCurrentText("Mobilizzazione passiva con trigger");
  ui->pushButton_es_libero->setVisible(false);
  QSqlQuery modalita;
  modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
  modalita.exec();
  if (modalita.exec())
  {
    mode = 2;
   // QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Mobilizzazione Passiva con Trigger"));
    ui->tabWidget_2->setCurrentWidget(ui->tab_ex);
    ui->stackedWidget_es->setCurrentWidget(ui->page_es);
    ros::NodeHandle n;
    n.setParam ("/exercise/mode", mode);
    ui->comboBox_ex1->removeItem(7);
    ui->comboBox_ex1->removeItem(8);
    ui->comboBox_ex1->removeItem(9);
    ui->comboBox_ex1->removeItem(10);

    ui->comboBox_ex2->removeItem(7);
    ui->comboBox_ex2->removeItem(8);
    ui->comboBox_ex2->removeItem(9);
    ui->comboBox_ex2->removeItem(10);

    ui->comboBox_ex3->removeItem(7);
    ui->comboBox_ex3->removeItem(8);
    ui->comboBox_ex3->removeItem(9);
    ui->comboBox_ex3->removeItem(10);

    ui->comboBox_ex4->removeItem(7);
    ui->comboBox_ex4->removeItem(8);
    ui->comboBox_ex4->removeItem(9);
    ui->comboBox_ex4->removeItem(10);

    ui->comboBox_ex5->removeItem(7);
    ui->comboBox_ex5->removeItem(8);
    ui->comboBox_ex5->removeItem(9);
    ui->comboBox_ex5->removeItem(10);

    ui->comboBox_ex6->removeItem(7);
    ui->comboBox_ex6->removeItem(8);
    ui->comboBox_ex6->removeItem(9);
    ui->comboBox_ex6->removeItem(10);

    ui->comboBox_ex7->removeItem(7);
    ui->comboBox_ex7->removeItem(8);
    ui->comboBox_ex7->removeItem(9);
    ui->comboBox_ex7->removeItem(10);
  }
  else {
    QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
  }
  if (dati::flag_ex ==0 ){
    ui->checkBox_ex1->setChecked(true);
    dati::flag_ex++;
  }
}

/**********************        PASSIVE CONTROL MODE  *********************/
void paginaprincipale::on_pushButton_pass_clicked()
{
  dati::mood = "Mobilizzazione Passiva";
  ui->comboBox_mode->setCurrentText("Mobilizzazione passiva");
  ui->pushButton_es_libero->setVisible(false);
  QSqlQuery modalita;
  modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
  modalita.exec();
  if (modalita.exec())
  {
    mode = 1;
    //QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Mobilizzazione Passiva"));
    ui->tabWidget_2->setCurrentWidget(ui->tab_ex);
    ui->stackedWidget_es->setCurrentWidget(ui->page_es);
    ros::NodeHandle n;
    n.setParam ("/exercise/mode", mode);

    ui->comboBox_ex1->removeItem(7);
    ui->comboBox_ex1->removeItem(8);
    ui->comboBox_ex1->removeItem(9);
    ui->comboBox_ex1->removeItem(10);

    ui->comboBox_ex2->removeItem(7);
    ui->comboBox_ex2->removeItem(8);
    ui->comboBox_ex2->removeItem(9);
    ui->comboBox_ex2->removeItem(10);

    ui->comboBox_ex3->removeItem(7);
    ui->comboBox_ex3->removeItem(8);
    ui->comboBox_ex3->removeItem(9);
    ui->comboBox_ex3->removeItem(10);

    ui->comboBox_ex4->removeItem(7);
    ui->comboBox_ex4->removeItem(8);
    ui->comboBox_ex4->removeItem(9);
    ui->comboBox_ex4->removeItem(10);

    ui->comboBox_ex5->removeItem(7);
    ui->comboBox_ex5->removeItem(8);
    ui->comboBox_ex5->removeItem(9);
    ui->comboBox_ex5->removeItem(10);

    ui->comboBox_ex6->removeItem(7);
    ui->comboBox_ex6->removeItem(8);
    ui->comboBox_ex6->removeItem(9);
    ui->comboBox_ex6->removeItem(10);

    ui->comboBox_ex7->removeItem(7);
    ui->comboBox_ex7->removeItem(8);
    ui->comboBox_ex7->removeItem(9);
    ui->comboBox_ex7->removeItem(10);
  }
  else {
    QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
  }
  ui->label_mood->setText(QString("Modalità di controllo selezionata : %1").arg(dati::mood));
  if (dati::flag_ex ==0 ){
    ui->checkBox_ex1->setChecked(true);
    dati::flag_ex++;
  }
}

/**********************        ASSISTIVE AS NEEDED CONTROL MODE  *********************/
void paginaprincipale::on_pushButton_asan_clicked()
{
  dati::mood = "Assisted as needed";
  ui->comboBox_mode->setCurrentText("Mobilizzazione con assistenza se necessario");
  ui->comboBox_mode->setCurrentText("Mobilizzazione con assistenza se necessario");
  ui->pushButton_es_libero->setVisible(false);
  QSqlQuery modalita;
  modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
  modalita.exec();
  if (modalita.exec())
  {
    // mode = 3;
    mode=4;
  //  QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Assisted As Needed"));
    ui->tabWidget_2->setCurrentWidget(ui->tab_ex);
    ui->stackedWidget_es->setCurrentWidget(ui->page_es);
    ros::NodeHandle n;
    n.setParam ("/exercise/mode", mode);

    ui->comboBox_ex1->removeItem(7);
    ui->comboBox_ex1->removeItem(8);
    ui->comboBox_ex1->removeItem(9);
    ui->comboBox_ex1->removeItem(10);

    ui->comboBox_ex2->removeItem(7);
    ui->comboBox_ex2->removeItem(8);
    ui->comboBox_ex2->removeItem(9);
    ui->comboBox_ex2->removeItem(10);

    ui->comboBox_ex3->removeItem(7);
    ui->comboBox_ex3->removeItem(8);
    ui->comboBox_ex3->removeItem(9);
    ui->comboBox_ex3->removeItem(10);

    ui->comboBox_ex4->removeItem(7);
    ui->comboBox_ex4->removeItem(8);
    ui->comboBox_ex4->removeItem(9);
    ui->comboBox_ex4->removeItem(10);

    ui->comboBox_ex5->removeItem(7);
    ui->comboBox_ex5->removeItem(8);
    ui->comboBox_ex5->removeItem(9);
    ui->comboBox_ex5->removeItem(10);

    ui->comboBox_ex6->removeItem(7);
    ui->comboBox_ex6->removeItem(8);
    ui->comboBox_ex6->removeItem(9);
    ui->comboBox_ex6->removeItem(10);

    ui->comboBox_ex7->removeItem(7);
    ui->comboBox_ex7->removeItem(8);
    ui->comboBox_ex7->removeItem(9);
    ui->comboBox_ex7->removeItem(10);
  }
  else {
    QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
  }
  ui->label_mood->setText(QString("Modalità di controllo selezionata : %1").arg(dati::mood));
  if (dati::flag_ex ==0 ){
    ui->checkBox_ex1->setChecked(true);
    dati::flag_ex++;
  }
}

/**********************       ANTI-G CONTROL MODE  *********************/
void paginaprincipale::on_pushButton_antig_clicked()
{
  dati::mood = "Anti-g";
  ui->comboBox_mode->setCurrentText("Mobilizzazione antigravitaria");
  ui->pushButton_es_libero->setVisible(true);
  QSqlQuery modalita;
  modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
  modalita.exec();
  if (modalita.exec())
  {
    mode = 4;
   // QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Anti Gravitario"));
    ui->tabWidget_2->setCurrentWidget(ui->tab_ex);
    ui->stackedWidget_es->setCurrentWidget(ui->page_es);
    ros::NodeHandle n;
    n.setParam ("/exercise/mode", mode);
  }
  else {
    QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
  }
  ui->label_mood->setText(QString("Modalità di controllo selezionata : %1").arg(dati::mood));
  if (dati::flag_ex ==0 ){
    ui->checkBox_ex1->setChecked(true);
    dati::flag_ex++;
  }
}

/**********************       CHALLENGING CONTROL MODE  *********************/
void paginaprincipale::on_pushButton_challening_clicked()
{
  dati::mood = "Challenging";
  ui->comboBox_mode->setCurrentText("Mobilizzazione con resistenza");
  ui->pushButton_es_libero->setVisible(false);
  QSqlQuery modalita;
  modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
  modalita.exec();
  if (modalita.exec())
  {
    mode = 5;
  // QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Challenging"));
    ui->tabWidget_2->setCurrentWidget(ui->tab_ex);
    ui->stackedWidget_es->setCurrentWidget(ui->page_es);
    ros::NodeHandle n;
    n.setParam ("/exercise/mode", mode);

    ui->comboBox_ex1->removeItem(7);
    ui->comboBox_ex1->removeItem(8);
    ui->comboBox_ex1->removeItem(9);
    ui->comboBox_ex1->removeItem(10);

    ui->comboBox_ex2->removeItem(7);
    ui->comboBox_ex2->removeItem(8);
    ui->comboBox_ex2->removeItem(9);
    ui->comboBox_ex2->removeItem(10);

    ui->comboBox_ex3->removeItem(7);
    ui->comboBox_ex3->removeItem(8);
    ui->comboBox_ex3->removeItem(9);
    ui->comboBox_ex3->removeItem(10);

    ui->comboBox_ex4->removeItem(7);
    ui->comboBox_ex4->removeItem(8);
    ui->comboBox_ex4->removeItem(9);
    ui->comboBox_ex4->removeItem(10);

    ui->comboBox_ex5->removeItem(7);
    ui->comboBox_ex5->removeItem(8);
    ui->comboBox_ex5->removeItem(9);
    ui->comboBox_ex5->removeItem(10);

    ui->comboBox_ex6->removeItem(7);
    ui->comboBox_ex6->removeItem(8);
    ui->comboBox_ex6->removeItem(9);
    ui->comboBox_ex6->removeItem(10);

    ui->comboBox_ex7->removeItem(7);
    ui->comboBox_ex7->removeItem(8);
    ui->comboBox_ex7->removeItem(9);
    ui->comboBox_ex7->removeItem(10);
  }
  else {
    QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
  }
  ui->label_mood->setText(QString("Modalità di controllo selezionata : %1").arg(dati::mood));
  if (dati::flag_ex ==0 ){
    ui->checkBox_ex1->setChecked(true);
    dati::flag_ex++;
  }
}
/**********************        TRASPARENT CONTROL MODE  *********************/
void paginaprincipale::on_pushButton_trasp_clicked()
{
  dati::mood = "trasparente";
  ui->comboBox_mode->setCurrentText("Mobilizzazione con trasparenza");
  ui->pushButton_es_libero->setVisible(true);
  QSqlQuery modalita;
  modalita.prepare("update Parametri_Paziente set Modalita_utilizzo = '"+dati::mood+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
  modalita.exec();
  if (modalita.exec())
  {
    mode = 6;
    ui->tabWidget_2->setCurrentWidget(ui->tab_ex);
    ui->stackedWidget_es->setCurrentWidget(ui->page_es);
    ros::NodeHandle n;
    n.setParam ("/exercise/mode", mode);
 //   QMessageBox ::information(this,tr("Salvato"),tr("Configurazione della modalità salvata: Challenging"));

  }
  else {
    QMessageBox ::critical(this,tr("Errore"),tr("modalità"));
  }
  ui->label_mood->setText(QString("Modalità di controllo selezionata : %1").arg(dati::mood));
  if (dati::flag_ex ==0 ){
    ui->checkBox_ex1->setChecked(true);
    dati::flag_ex++;
  }
}

/**********************************************************************************/

/**********************       EXERCISE CONFIGURATION PAGE             *********************/

/**********************************************************************************/

/**********************       ENABLE INTERACTIVE OBJECTS COMBOBOX                      *********************/
void paginaprincipale::enable_combo() {
  ui->comboBox_oi_es1->setEnabled(false);
  ui->comboBox_oi_es2->setEnabled(false);
  ui->comboBox_oi_es3->setEnabled(false);
  ui->comboBox_oi_es4->setEnabled(false);
  ui->comboBox_oi_es5->setEnabled(false);
  ui->comboBox_oi_es6->setEnabled(false);
  ui->comboBox_oi_es7->setEnabled(false);


  es2 = "Raggiungimento anteriore di target su un piano con oggetti";
  es4 = "Raggiungimento anteriore di target su un piano nello spazio con oggetti";
  es7 = "Mano alla bocca con oggetto";

  qDebug()<< "sono nella funzione enable_combo";
  if(ui->comboBox_ex1->currentText()==es2 || ui->comboBox_ex1->currentText()== es4 || ui->comboBox_ex1->currentText()== es7) {
    ui->comboBox_oi_es1->setEnabled(true);

  }
  if(ui->comboBox_ex2->currentText()==es2 || ui->comboBox_ex2->currentText()== es4 || ui->comboBox_ex2->currentText()== es7) {
    ui->comboBox_oi_es2->setEnabled(true);

  }
  if(ui->comboBox_ex3->currentText()==es2 || ui->comboBox_ex3->currentText()== es4 || ui->comboBox_ex3->currentText()== es7) {
    ui->comboBox_oi_es3->setEnabled(true);

  }
  if(ui->comboBox_ex4->currentText()==es2 || ui->comboBox_ex4->currentText()== es4 || ui->comboBox_ex4->currentText()== es7) {
    ui->comboBox_oi_es4->setEnabled(true);

  }
  if(ui->comboBox_ex5->currentText()==es2 || ui->comboBox_ex5->currentText()== es4 || ui->comboBox_ex5->currentText()== es7) {
    ui->comboBox_oi_es5->setEnabled(true);

  }
  if(ui->comboBox_ex6->currentText()==es2 || ui->comboBox_ex6->currentText()== es4 || ui->comboBox_ex6->currentText()== es7) {
    ui->comboBox_oi_es6->setEnabled(true);

  }
  if(ui->comboBox_ex7->currentText()==es2 || ui->comboBox_ex7->currentText()== es4 || ui->comboBox_ex7->currentText()== es7) {
    ui->comboBox_oi_es7->setEnabled(true);

  }

}

/**********************       UPDATE THERAPY TIME IN REHAB CONFIGURATION                       *********************/
void paginaprincipale::update_tempo_terapia(){
  QString t;
  qDebug()<< "sono nella funzione update_tempo_terapia";
  es1 = "Raggiungimento anteriore di target su un piano senza oggetti";
  es2 = "Raggiungimento anteriore di target su un piano con oggetti";
  es3 = "Raggiungimento anteriore di target su un piano nello spazio senza oggetti";
  es4 = "Raggiungimento anteriore di target su un piano nello spazio con oggetti ";
  es5 = "Elevazione laterale su un piano frontale";
  es6 = "Mano alla bocca senza oggetto";
  es7 = "Mano alla bocca con oggetto";
  es8 = "Exergames - Basket";
  es9 = "Exergames - Macedonia";
  es10 = "Exergames - Spesa";
  es11 = "Exergames - Caffè";


  if (ui->comboBox_ex1->currentText()== es1 || ui->comboBox_ex1->currentText()==es3 || ui->comboBox_ex1->currentText() == es5 || ui->comboBox_ex1->currentText()== es6){
    t_es1 = 1;
    ripe1 = ui->lineEdit_ex1->text().toInt();
    //ripe1 = dati::rip1.toInt();
    t_es1 = t_es1*ripe1;
    qDebug() << "es 1";
    qDebug() << t_es1;

  }
  else if ( ui->comboBox_ex1->currentText() == es2 || ui->comboBox_ex1->currentText()== es7 || ui->comboBox_ex1->currentText()== es8 || ui->comboBox_ex1->currentText()== es9 || ui->comboBox_ex1->currentText()== es10 || ui->comboBox_ex1->currentText()== es11  ) {
    t_es1 = 2;
    ripe1 = ui->lineEdit_ex1->text().toInt();
    t_es1 = t_es1* ripe1;
    qDebug() << "es 1";
    qDebug() << t_es1;
  }
  if (ui->comboBox_ex2->currentText()== es1 || ui->comboBox_ex2->currentText()==es3 || ui->comboBox_ex2->currentText() == es5 || ui->comboBox_ex2->currentText()== es6){
    t_es2 = 1;
    ripe2 = ui->lineEdit_ex2->text().toInt();
    t_es2 = t_es2*ripe2;
    qDebug() << "es2";
    qDebug() << t_es2;

  }
  else if ( ui->comboBox_ex2->currentText() == es2 || ui->comboBox_ex2->currentText()== es7 || ui->comboBox_ex2->currentText()== es8 || ui->comboBox_ex2->currentText()== es9 || ui->comboBox_ex2->currentText()== es10 || ui->comboBox_ex2->currentText()== es11) {
    t_es2 = 2;
    ripe2 = ui->lineEdit_ex2->text().toInt();
    t_es2 = t_es2* ripe2;
    qDebug() << "es2";
    qDebug() << t_es2;
  }
  if (ui->comboBox_ex3->currentText()== es1 || ui->comboBox_ex3->currentText()==es3 || ui->comboBox_ex3->currentText() == es5 || ui->comboBox_ex3->currentText()== es6){
    t_es3 = 1;
    ripe3 = ui->lineEdit_ex3->text().toInt();
    t_es3 = t_es3*ripe3;
    qDebug() << "es3";
    qDebug() << t_es3;

  }
  else if ( ui->comboBox_ex3->currentText() == es2 || ui->comboBox_ex3->currentText()== es7 || ui->comboBox_ex3->currentText()== es8 || ui->comboBox_ex3->currentText()== es9 || ui->comboBox_ex3->currentText()== es10 || ui->comboBox_ex3->currentText()== es11) {
    t_es3 = 2;
    ripe3 = ui->lineEdit_ex3->text().toInt();
    t_es3 = t_es3* ripe3;
    qDebug() << "es3";
    qDebug() << t_es3;
  }
  if (ui->comboBox_ex4->currentText()== es1 || ui->comboBox_ex4->currentText()==es3 || ui->comboBox_ex4->currentText() == es5 || ui->comboBox_ex4->currentText()== es6){
    t_es4 = 1;
    ripe4 = ui->lineEdit_ex4->text().toInt();
    t_es4 = t_es4*ripe4;

  }
  else if ( ui->comboBox_ex4->currentText() == es2 || ui->comboBox_ex4->currentText()== es7 || ui->comboBox_ex4->currentText()== es8 || ui->comboBox_ex4->currentText()== es9 || ui->comboBox_ex4->currentText()== es10 || ui->comboBox_ex4->currentText()== es11) {
    t_es4 = 2;
    ripe4 = ui->lineEdit_ex4->text().toInt();
    t_es4 = t_es4* ripe4;
  }
  if (ui->comboBox_ex5->currentText()== es1 || ui->comboBox_ex5->currentText()==es3 || ui->comboBox_ex5->currentText() == es5 || ui->comboBox_ex5->currentText()== es6){
    t_es5 = 1;
    ripe5 = ui->lineEdit_ex5->text().toInt();
    t_es5 = t_es5*ripe5;

  }
  else if ( ui->comboBox_ex5->currentText() == es2 || ui->comboBox_ex5->currentText()== es7 || ui->comboBox_ex5->currentText()== es8 || ui->comboBox_ex5->currentText()== es9 || ui->comboBox_ex5->currentText()== es10 || ui->comboBox_ex5->currentText()== es11) {
    t_es5 = 2;
    ripe5 = ui->lineEdit_ex5->text().toInt();
    t_es5 = t_es5* ripe5;
  }

  if (ui->comboBox_ex6->currentText()== es1 || ui->comboBox_ex6->currentText()==es3 || ui->comboBox_ex6->currentText() == es5 || ui->comboBox_ex6->currentText()== es6){
    t_es6 = 1;
    ripe6 = ui->lineEdit_ex6->text().toInt();
    t_es6 = t_es6*ripe6;

  }
  else if ( ui->comboBox_ex6->currentText() == es2 || ui->comboBox_ex6->currentText()== es7 || ui->comboBox_ex6->currentText()== es8 || ui->comboBox_ex6->currentText()== es9 || ui->comboBox_ex6->currentText()== es10 || ui->comboBox_ex6->currentText()== es11) {
    t_es6 = 2;
    ripe6 = ui->lineEdit_ex6->text().toInt();
    t_es6 = t_es6* ripe6;
  }

  if (ui->comboBox_ex7->currentText()== es1 || ui->comboBox_ex7->currentText()==es3 || ui->comboBox_ex7->currentText() == es5 || ui->comboBox_ex7->currentText()== es6){
    t_es7 = 1;
    ripe7 = ui->lineEdit_ex7->text().toInt();
    t_es7 = t_es7*ripe7;

  }
  else if ( ui->comboBox_ex7->currentText() == es2 || ui->comboBox_ex7->currentText()== es7 || ui->comboBox_ex7->currentText()== es8 || ui->comboBox_ex7->currentText()== es9 || ui->comboBox_ex7->currentText()== es10 || ui->comboBox_ex7->currentText()== es11) {
    t_es7 = 2;
    ripe7 = ui->lineEdit_ex7->text().toInt();
    t_es7 = t_es7* ripe7;
  }
  if(ui->checkBox_ex1->isChecked()) {
    temp_tot = t_es1;
    ui->label_t_es1->setText(QString::number(t_es1));
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex2->isChecked()) {
    temp_tot += t_es2;
    ui->label_t_es2->setText(QString::number(t_es2));
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex3->isChecked()) {
    temp_tot += t_es3;
    ui->label_t_es3->setText(QString::number(t_es3));
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex4->isChecked()) {
    temp_tot += t_es4;
    ui->label_t_es4->setText(QString::number(t_es4));
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex5->isChecked()) {
    temp_tot += t_es5;
    ui->label_t_es5->setText(QString::number(t_es5));
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_ex6->isChecked()) {
    temp_tot += t_es6;
    ui->label_t_es6->setText(QString::number(t_es6));
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_7->isChecked()) {
    temp_tot += t_es7;
    ui->label_t_es7->setText(QString::number(t_es7));
    temp_string = QString::number(temp_tot);
  }


  qDebug()<< temp_tot;
  qDebug()<< temp_string;

  QString test = QString("Tempo Stimato per la Terapia : %1 minuti").arg(temp_string);

  ui->label_tempo->setText(test);
  ui->lcdNumber_tempotot->display(temp_tot);

}

/**********************       ENABLE EXERCISES COMBOBOX IN THE REHAB CONFIGURATION                *********************/
void paginaprincipale::enable_combo_ex() {
  ui->comboBox_ex1->setEnabled(false);
  ui->comboBox_ex2->setEnabled(false);
  ui->comboBox_ex3->setEnabled(false);
  ui->comboBox_ex4->setEnabled(false);
  ui->comboBox_ex5->setEnabled(false);
  ui->comboBox_ex6->setEnabled(false);
  ui->comboBox_ex7->setEnabled(false);

  if(ui->checkBox_ex1->isChecked() ) {
    ui->comboBox_ex1->setEnabled(true);
  }
  if(ui->checkBox_ex2->isChecked() ) {
    ui->comboBox_ex2->setEnabled(true);
  }
  if(ui->checkBox_ex3->isChecked()) {
    ui->comboBox_ex3->setEnabled(true);
  }
  if(ui->checkBox_ex4->isChecked() ) {
    ui->comboBox_ex4->setEnabled(true);
  }
  if(ui->checkBox_ex5->isChecked() ) {
    ui->comboBox_ex5->setEnabled(true);
  }
  if(ui->checkBox_ex6->isChecked()) {
    ui->comboBox_ex6->setEnabled(true);
  }
  if(ui->checkBox_7->isChecked()) {
    ui->comboBox_ex7->setEnabled(true);
  }

}

/**********************        ADD EXERCISE IN REHAB CONFIGURATION *********************/
void paginaprincipale::on_pushButton_add_clicked()

{ if(dati::flag_ex == 0) {
    dati::flag_ex++;}
  if(dati::flag_ex == 1) {
    ui->checkBox_ex2->setChecked(true);

    dati::flag_ex++;
    qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==2) {
    ui->checkBox_ex3->setChecked(true);
    dati::flag_ex++;
    qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==3) {
    ui->checkBox_ex4->setChecked(true);
    dati::flag_ex++;
    qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==4) {
    ui->checkBox_ex5->setChecked(true);
    dati::flag_ex++;
    qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==5) {
    ui->checkBox_ex6->setChecked(true);
    dati::flag_ex++;
    qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex==6) {
    ui->checkBox_7->setChecked(true);
    // dati::flag_ex++;
    qDebug()<<dati::flag_ex;
  }

}
/**********************        REMOVE EXERCISE IN REHAB CONFIGURATION *********************/
void paginaprincipale::on_pushButton_remove_clicked()
{ if(dati::flag_ex == 6){
    ui->checkBox_7->setChecked(false);
    dati::flag_ex--;
    qDebug()<<dati::flag_ex;

  }
  else if (dati::flag_ex ==5) {
    ui->checkBox_ex6->setChecked(false);
    dati::flag_ex--;
    qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex ==4) {
    ui->checkBox_ex5->setChecked(false);
    dati::flag_ex--;
    qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex ==3) {
    ui->checkBox_ex4->setChecked(false);
    dati::flag_ex--;
    qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex ==2) {
    ui->checkBox_ex3->setChecked(false);
    dati::flag_ex--;
    qDebug()<<dati::flag_ex;
  }
  else if (dati::flag_ex ==1) {
    ui->checkBox_ex2->setChecked(false);
    dati::flag_ex--;
    qDebug()<<dati::flag_ex;
  }

}

/**********************       SAVE EXERCISES                       *********************/
void paginaprincipale::on_pushButton_salvaex_clicked()
{
  ros::NodeHandle n;

  ui->tabWidget_2->setCurrentWidget(ui->tab_init);
  QString bicchiere, borraccia, tazza;
  bicchiere = "Bicchiere";
  borraccia = "Borraccia";
  tazza = "Tazza";

  if(ui->checkBox_ex1->isChecked())
  {  check_ex1=1;

    dati::ex1 = ui->comboBox_ex1->currentText();
    ui->label_es1_recap->setText(dati::ex1);



    dati::rip1= ui->lineEdit_ex1->text();
    ui->label_es1_rip_recap->setText(dati::rip1);

    ui->checkBox_es1->setChecked(true);
    ui->comboBox_es1->setCurrentText(dati::ex1);
    ui->lineEdit_rep1->setText(dati::rip1);

    rep1 = dati::rip1.toInt();
    if(ui->comboBox_oi_es1->isEnabled()) {
      //AGGIORNA ROSPARAM MODULI OGGETTI QUI
      if(ui->comboBox_oi_es1->currentText()== bicchiere ) { ui->comboBox_ogg1->setCurrentText("bicchiere"); oggetto_es1= "1"; ros_ogg1=1; ui->label_oi1_recap->setText(bicchiere);}
      else if (ui->comboBox_oi_es1->currentText()==borraccia) {ui->comboBox_ogg1->setCurrentText("borraccia"); oggetto_es1= "2"; ros_ogg1=2; ui->label_oi1_recap->setText(borraccia);}
      else if(ui->comboBox_oi_es1 ->currentText()==tazza) {ui->comboBox_ogg1->setCurrentText("tazza"); oggetto_es1= "3"; ros_ogg1=3; ui->label_oi1_recap->setText(tazza);} }
    else if (!(ui->comboBox_oi_es1->isEnabled())) {
      oggetto_es1="0";
      ros_ogg1 = 0;
    }
    qDebug()<< oggetto_es1;
    QSqlQuery selezione1;
    selezione1.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex1+"'");
    selezione1.exec();
    if (selezione1.exec()) {
      while(selezione1.next())
      {
        dati::num_ex1 = selezione1.value(0).toString();
        exe1 = dati::num_ex1.toInt();
        if(exe1==3) {
          active_module_RF=1;
          active_modules = {active_module_spalla, active_module_gomito, active_module_polso, active_module_MAT, active_module_RF, active_module_EEG_EMG, active_module_MAP, active_module_JOYSTICK, active_module_VOCAL, active_module_IK_ONLINE};
          n.setParam("/active_modules", active_modules);

        }

      }
      if(dati::rip1.toInt()< 30) {

      }
      else if(dati::rip1.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni del primo esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));


      }
    }

    if(!(dati::num_ex1.toInt()==2 || dati::num_ex1.toInt()==4 || dati::num_ex1.toInt()==7) ) {

      ui->comboBox_oi_es1->setEnabled(false);
    }

  }
  if(ui->checkBox_ex2->isChecked())
  {
    dati::ex2 = ui->comboBox_ex2->currentText();
    ui->label_es2_recap->setText(dati::ex2);


    dati::rip2= ui->lineEdit_ex2->text();
    ui->label_es2_ripe_recap->setText(dati::rip2);

    ui->checkBox_es2->setChecked(true);
    ui->comboBox_es2->setCurrentText(dati::ex2);
    ui->lineEdit_rep2->setText(dati::rip2);

    rep2 = dati::rip2.toInt();
    if(ui->comboBox_oi_es2->isEnabled()) {
      if(ui->comboBox_oi_es2->currentText()== bicchiere ) { ui->comboBox_ogg2->setCurrentText("bicchiere"); oggetto_es2= "1"; ros_ogg2=1; ui->label_oi2_recap->setText(bicchiere);}
      else if (ui->comboBox_oi_es2->currentText()==borraccia) { ui->comboBox_ogg2->setCurrentText("borraccia");oggetto_es2 = "2"; ros_ogg2= 2; ui->label_oi2_recap->setText(borraccia);}
      else if(ui->comboBox_oi_es2 ->currentText()==tazza) {ui->comboBox_ogg2->setCurrentText("tazza"); oggetto_es2= "3"; ros_ogg2= 3; ui->label_oi2_recap->setText(tazza);} }
    else if (!(ui->comboBox_oi_es2->isEnabled())) {
      oggetto_es2 = "0";
      ros_ogg2 = 0;
    }
    QSqlQuery selezione2;
    selezione2.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex2+"'");
    selezione2.exec();
    if (selezione2.exec()) {
      while(selezione2.next())
      {
        dati::num_ex2 = selezione2.value(0).toString();
        exe2 = dati::num_ex2.toInt();
        if(exe2==3) {
          active_module_RF=1;
          active_modules = {active_module_spalla, active_module_gomito, active_module_polso, active_module_MAT, active_module_RF, active_module_EEG_EMG, active_module_MAP, active_module_JOYSTICK, active_module_VOCAL, active_module_IK_ONLINE};
          n.setParam("/active_modules", active_modules);

        }


      }
      if(dati::rip2.toInt()<30) {

      }
      else if (dati::rip2.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }

  }
  if(ui->checkBox_ex3->isChecked())
  {
    dati::ex3 = ui->comboBox_ex3->currentText();
    ui->label_es3_recap->setText(dati::ex3);


    dati::rip3= ui->lineEdit_ex3->text();
    ui->label_es3_ripe_recap->setText(dati::rip3);

    ui->checkBox_es3->setChecked(true);
    ui->comboBox_es3->setCurrentText(dati::ex3);
    ui->lineEdit_rep3->setText(dati::rip3);

    rep3 = dati::rip3.toInt();
    if(ui->comboBox_oi_es3->isEnabled()) {
      if(ui->comboBox_oi_es3->currentText()== bicchiere ) { ui->comboBox_ogg3->setCurrentText("bicchiere"); oggetto_es3= "1"; ros_ogg3=1; ui->label_oi3_recap->setText(bicchiere);}
      else if (ui->comboBox_oi_es3->currentText()==borraccia) {  ui->comboBox_ogg3->setCurrentText("borraccia"); oggetto_es3= "2"; ros_ogg3=2; ui->label_oi3_recap->setText(borraccia);}
      else if(ui->comboBox_oi_es3 ->currentText()==tazza) { ui->comboBox_ogg3->setCurrentText("tazza"); oggetto_es3= "3"; ros_ogg3=3; ui->label_oi3_recap->setText(tazza);} }
    else if(!(ui->comboBox_oi_es3->isEnabled())) {
      oggetto_es3 = "0";
      ros_ogg3 = 0;
    }
    QSqlQuery selezione3;
    selezione3.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex3+"'");
    selezione3.exec();
    if (selezione3.exec()) {
      while(selezione3.next())
      {
        dati::num_ex3 = selezione3.value(0).toString();
        exe3 = dati::num_ex3.toInt();
        if(exe3==3) {
          active_module_RF=1;
          active_modules = {active_module_spalla, active_module_gomito, active_module_polso, active_module_MAT, active_module_RF, active_module_EEG_EMG, active_module_MAP, active_module_JOYSTICK, active_module_VOCAL, active_module_IK_ONLINE};
          n.setParam("/active_modules", active_modules);

        }


      }
      if(dati::rip3.toInt()<30) {

      }
      else if (dati::rip3.toInt()>30) {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }

  }
  if(ui->checkBox_ex4->isChecked())
  {
    dati::ex4 = ui->comboBox_ex4->currentText();
    ui->label_es4_recap->setText(dati::ex4);


    dati::rip4= ui->lineEdit_ex4->text();
    ui->label_es4_ripe_recap->setText(dati::rip4);

    ui->checkBox_es4->setChecked(true);
    ui->comboBox_es4->setCurrentText(dati::ex4);
    ui->lineEdit_rep4->setText(dati::rip4);

    rep4 = dati::rip4.toInt();
    if(ui->comboBox_oi_es4->isEnabled()) {
      if(ui->comboBox_oi_es4->currentText()== bicchiere ) {ui->comboBox_ogg4->setCurrentText("bicchiere"); oggetto_es4= "1"; ros_ogg4=1; ui->label_oi4_recap->setText(bicchiere);}
      else if (ui->comboBox_oi_es4->currentText()==borraccia) {ui->comboBox_ogg4->setCurrentText("borraccia"); oggetto_es4= "2"; ros_ogg4=2; ui->label_oi4_recap->setText(borraccia);}
      else if(ui->comboBox_oi_es4 ->currentText()==tazza) {ui->comboBox_ogg4->setCurrentText("tazza"); oggetto_es4= "3"; ros_ogg4=3; ui->label_oi4_recap->setText(tazza);} }
    else if (!(ui->comboBox_oi_es4->isEnabled())) {
      oggetto_es4 = "0";
      ros_ogg4 = 0;
    }
    QSqlQuery selezione4;
    selezione4.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex4+"'");
    selezione4.exec();
    if (selezione4.exec()) {
      while(selezione4.next())
      {
        dati::num_ex4 = selezione4.value(0).toString();
        exe4 = dati::num_ex4.toInt();
        if(exe4==3) {
          active_module_RF=1;
          active_modules = {active_module_spalla, active_module_gomito, active_module_polso, active_module_MAT, active_module_RF, active_module_EEG_EMG, active_module_MAP, active_module_JOYSTICK, active_module_VOCAL, active_module_IK_ONLINE};
          n.setParam("/active_modules", active_modules);

        }


      }
      if (dati::rip4.toInt()<30) {

      }
      else if (dati::rip4.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }

  }
  if(ui->checkBox_ex5->isChecked())
  {
    dati::ex5 = ui->comboBox_ex5->currentText();
    ui->label_es5_recap->setText(dati::ex5);


    dati::rip5= ui->lineEdit_ex5->text();
    ui->label_5_ripe_recap->setText(dati::rip5);

    ui->checkBox_es5->setChecked(true);
    ui->comboBox_es5->setCurrentText(dati::ex5);
    ui->lineEdit_rep5->setText(dati::rip5);

    rep5 = dati::rip5.toInt();
    if(ui->comboBox_oi_es5->isEnabled()) {
      if(ui->comboBox_oi_es5->currentText()== bicchiere ) {ui->comboBox_ogg5->setCurrentText("bicchiere"); oggetto_es5= "1"; ros_ogg5=1; ui->label_oi5_recap->setText(bicchiere);}
      else if (ui->comboBox_oi_es5->currentText()==borraccia) {ui->comboBox_ogg5->setCurrentText("borraccia"); oggetto_es5= "2"; ros_ogg5=2; ui->label_oi5_recap->setText(borraccia);}
      else if(ui->comboBox_oi_es5->currentText()==tazza) {ui->comboBox_ogg5->setCurrentText("tazza"); oggetto_es5= "3"; ros_ogg5=3;ui->label_oi5_recap->setText(tazza);} }
    else if (!(ui->comboBox_oi_es5->isEnabled())) {
      oggetto_es5 = "0";
      ros_ogg5 = 0;

    }
    QSqlQuery selezione5;
    selezione5.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex5+"'");
    selezione5.exec();
    if (selezione5.exec()) {
      while(selezione5.next())
      {
        dati::num_ex5 = selezione5.value(0).toString();
        exe5 = dati::num_ex5.toInt();
        if(exe5==3) {
          active_module_RF=1;
          active_modules = {active_module_spalla, active_module_gomito, active_module_polso, active_module_MAT, active_module_RF, active_module_EEG_EMG, active_module_MAP, active_module_JOYSTICK, active_module_VOCAL, active_module_IK_ONLINE};
          n.setParam("/active_modules", active_modules);

        }


      }
      if(dati::rip5.toInt()<30) {

      }
      else if(dati::rip5.toInt()>30) {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }

    }

  }
  if(ui->checkBox_ex6->isChecked())
  {
    dati::ex6 = ui->comboBox_ex6->currentText();
    ui->label_es6_recap->setText(dati::ex6);

    dati::rip6= ui->lineEdit_ex6->text();
    ui->label_es6_ripe_recap->setText(dati::rip6);

    ui->checkBox_es6->setChecked(true);
    ui->comboBox_es6->setCurrentText(dati::ex6);
    ui->lineEdit_rep6->setText(dati::rip6);

    rep6 = dati::rip6.toInt();
    if(ui->comboBox_oi_es6->isEnabled()) {
      if(ui->comboBox_oi_es6->currentText()== bicchiere ) {ui->comboBox_ogg6->setCurrentText("bicchiere"); oggetto_es6= "1"; ros_ogg6=1; ui->label_oi6_recap->setText(bicchiere);}
      else if (ui->comboBox_oi_es6->currentText()==borraccia) {ui->comboBox_ogg6->setCurrentText("borraccia"); oggetto_es6= "2"; ros_ogg6=2;ui->label_oi6_recap->setText(borraccia);}
      else if(ui->comboBox_oi_es6 ->currentText()==tazza) {ui->comboBox_ogg6->setCurrentText("tazza"); oggetto_es6= "3"; ros_ogg6=3;ui->label_oi6_recap->setText(tazza);} }
    else if(!(ui->comboBox_oi_es6->isEnabled()))  {
      oggetto_es6 = "0";
      ros_ogg6 = 0;
    }
    QSqlQuery selezione6;
    selezione6.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex6+"'");
    selezione6.exec();
    if (selezione6.exec()) {
      while(selezione6.next())
      {
        dati::num_ex6 = selezione6.value(0).toString();
        exe6 = dati::num_ex6.toInt();
        if(exe6==3) {
          active_module_RF=1;
          active_modules = {active_module_spalla, active_module_gomito, active_module_polso, active_module_MAT, active_module_RF, active_module_EEG_EMG, active_module_MAP, active_module_JOYSTICK, active_module_VOCAL, active_module_IK_ONLINE};
          n.setParam("/active_modules", active_modules);

        }


      }
      if(dati::rip6.toInt()<30) {

      }
      else if(dati::rip6.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }


  }
  if(ui->checkBox_7->isChecked())
  {
    dati::ex7 = ui->comboBox_ex7->currentText();
    ui->label_es7_recap->setText(dati::ex7);


    dati::rip7= ui->lineEdit_ex7->text();
    ui->label_7_ripe_recap->setText(dati::rip7);

    ui->checkBox_es7->setChecked(true);
    ui->comboBox_es7->setCurrentText(dati::ex7);
    ui->lineEdit_rep7->setText(dati::rip7);

    rep7 = dati::rip7.toInt();
    if(ui->comboBox_oi_es7->isEnabled()) {
      if(ui->comboBox_oi_es7->currentText()== bicchiere ) {ui->comboBox_ogg7->setCurrentText("bicchiere"); oggetto_es7= "1"; ros_ogg7=1; ui->label_oi7_recap->setText(bicchiere);}
      else if (ui->comboBox_oi_es7->currentText()==borraccia) {ui->comboBox_ogg7->setCurrentText("borraccia"); oggetto_es7= "2"; ros_ogg7=2; ui->label_oi7_recap->setText(borraccia);}
      else if(ui->comboBox_oi_es7 ->currentText()==tazza) {ui->comboBox_ogg7->setCurrentText("tazza"); oggetto_es7= "3"; ros_ogg7=3; ui->label_oi7_recap->setText(tazza);} }
    else if(!(ui->comboBox_oi_es7 ->isEnabled())) {
      oggetto_es7 = "0";
      ros_ogg7 = 0;
    }
    QSqlQuery selezione7;
    selezione7.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex7+"'");
    selezione7.exec();
    if (selezione7.exec()) {
      while(selezione7.next())
      {
        dati::num_ex7 = selezione7.value(0).toString();
        exe7 = dati::num_ex7.toInt();
        if(exe7==3) {
          active_module_RF=1;
          active_modules = {active_module_spalla, active_module_gomito, active_module_polso, active_module_MAT, active_module_RF, active_module_EEG_EMG, active_module_MAP, active_module_JOYSTICK, active_module_VOCAL, active_module_IK_ONLINE};
          n.setParam("/active_modules", active_modules);

        }


      }
      if(dati::rip7.toInt()<30) {

      }
      else if(dati::rip7.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }

  }
  qDebug()<< dati::ind;
  QSqlQuery selezione;
  selezione.prepare("update Parametri_Paziente set ex1 = '"+dati::num_ex1+"', rip1 = '"+dati::rip1+"', ogg_es1 = '"+oggetto_es1+"', ex2 = '"+dati::num_ex2+"', rip2 = '"+dati::rip2+"',ogg_es2 = '"+oggetto_es2+"', ex3 = '"+dati::num_ex3+"', rip3 = '"+dati::rip3+"', ogg_es3 = '"+oggetto_es3+"',ex4 = '"+dati::num_ex4+"', rip4 = '"+dati::rip4+"', ogg_es4 = '"+oggetto_es4+"',ex5 = '"+dati::num_ex5+"', rip5 = '"+dati::rip5+"',ogg_es5 = '"+oggetto_es5+"',ex6 = '"+dati::num_ex6+"', rip6 = '"+dati::rip6+"', ogg_es6 = '"+oggetto_es6+"',ex7 = '"+dati::num_ex7+"', rip7 = '"+dati::rip7+"', ogg_es7 = '"+oggetto_es7+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
  selezione.exec();
  if (selezione.exec())
  {
    //QMessageBox ::information(this,tr("Salvato"),tr("Set di esercizi salvati"));
    dati::rep_index= rep1+rep2+rep3+rep4+rep5+rep6+rep7;


    /******************       AGGIORNO TOPIC STATUS : FINISHED EXERCISE SEQUENCE                 ***********************/
    //std_msgs::Int8 msg_status;
    dati::status1 = SC1_SESSION_DEFINING;
    msg_status_pp.data = dati::status1;
    ROS_INFO ("%d", msg_status_pp.data);
    status_publisher.publish(msg_status_pp);

    /******************         AGGIORNO ROS PARAMETERS : EXERCISE SEQUENCE                      ***********************/
    ex_seq = {exe1, exe2, exe3, exe4, exe5, exe6, exe7};
    ex_rep = {rep1, rep2, rep3, rep4, rep5, rep6, rep7};
    ex_obj = {ros_ogg1, ros_ogg2, ros_ogg3, ros_ogg4, ros_ogg5, ros_ogg6, ros_ogg7};
    ros::NodeHandle n;
    n.setParam("/exercise/sequence", ex_seq);
    n.setParam("/exercise/repetition", ex_rep);
    n.setParam ("/exercise/objects", ex_obj);

  }
  else {
    QMessageBox ::critical(this,tr("Errore"),tr("errore"));
    qDebug()<< selezione.lastError();
  }

  //            QSqlQuery esercizi;
  //             esercizi.prepare("select ex1,rip1,ex2,rip2,ex3,rip3,ex4,rip4,ex5,rip5,ex6,rip6,ex7,rip7 from Parametri_Paziente where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' order by Data_acquisizione desc limit 1");
  //              if(esercizi.exec()){
  //                while(esercizi.next())
  //                { ExInfo cur;
  //                  QString EX1 = esercizi.value(0).toString();
  //                  int RIP1 = esercizi.value(1).toInt();

  //                  if ( ! EX1.isEmpty() ){
  //                    // FILL IT
  //                    cur.EX = EX1; // fill it
  //                    cur.REP = RIP1;
  //                    cur.images = GetImages(EX1);
  //                    ExInfoMap[EX1] = cur; //  add it
  //                    qDebug()<<cur.images.size();
  //                    sel_ex.append(EX1);
  //                    qDebug()<< "sel:" << sel_ex;
  //                    qDebug()<< " size:" << sel_ex.size();
  //                  }
  //                  else {
  //                    QString es = "01";
  //                    QString es2 = "02";
  //                    QString es3 = "03";
  //                    QString es4 = "04";
  //                    if(ExInfoMap.find(es) !=ExInfoMap.end() || (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
  //                      // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);

  //                    }
  //                    //else ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  //                  }

  //                  QString EX2 = esercizi.value(2).toString();
  //                  int RIP2 = esercizi.value(3).toInt();
  //                  if(!EX2.isEmpty()) {
  //                    // FILL IT
  //                    cur.EX = EX2; // fill it
  //                    cur.REP = RIP2;
  //                    cur.images = GetImages(EX2);  // use ID to get images  /////////////////////////////////////////////// IMAGES
  //                    ExInfoMap[EX2] = cur; //  add it
  //                    sel_ex.append(EX2);
  //                    qDebug()<< "sel:" << sel_ex;
  //                    qDebug()<< " size:" << sel_ex.size();

  //                  }
  //                  else {

  //                    QString es = "01";
  //                    QString es2 = "02";
  //                    QString es3 = "03";
  //                    QString es4 = "04";
  //                    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
  //                      // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
  //                      std::cout<< "Key found";


  //                    }
  //                    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  //                      std::cout<< "key not found";}
  //                  }

  //                  QString EX3 = esercizi.value(4).toString();
  //                  int RIP3 = esercizi.value(5).toInt();
  //                  if(!EX3.isEmpty()) {
  //                    // FILL IT
  //                    cur.EX = EX3; // fill it
  //                    cur.REP = RIP3;
  //                    cur.images = GetImages(EX3);
  //                    ExInfoMap[EX3] = cur; //  add it
  //                    sel_ex.append(EX3);
  //                    qDebug()<< "sel:" << sel_ex;
  //                    qDebug()<< " size:" << sel_ex.size();

  //                  }
  //                  else {

  //                    QString es = "01";
  //                    QString es2 = "02";
  //                    QString es3 = "03";
  //                    QString es4 = "04";
  //                    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
  //                      // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
  //                      std::cout<< "Key found";


  //                    }
  //                    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  //                      std::cout<< "key not found";}
  //                  }
  //                  QString EX4 = esercizi.value(6).toString();
  //                  int RIP4 = esercizi.value(7).toInt();
  //                  if(!EX4.isEmpty()) {
  //                    // FILL IT
  //                    cur.EX = EX4; // fill it
  //                    cur.REP = RIP4;
  //                    cur.images = GetImages(EX4);
  //                    ExInfoMap[EX4] = cur; //  add it
  //                    sel_ex.append(EX4);
  //                    qDebug()<< "sel:" << sel_ex;
  //                    qDebug()<< " size:" << sel_ex.size();




  //                  }
  //                  else {

  //                    QString es = "01";
  //                    QString es2 = "02";
  //                    QString es3 = "03";
  //                    QString es4 = "04";
  //                    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
  //                      //ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
  //                      std::cout<< "Key found";


  //                    }
  //                    else  {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  //                      std::cout<< "key not found";}
  //                  }
  //                  QString EX5 = esercizi.value(8).toString();
  //                  int RIP5 = esercizi.value(9).toInt();
  //                  if(!EX5.isEmpty()){
  //                    // FILL IT
  //                    cur.EX = EX5; // fill it
  //                    cur.REP = RIP5;
  //                    cur.images = GetImages(EX5);
  //                    ExInfoMap[EX5] = cur; //  add it
  //                    sel_ex.append(EX5);
  //                    qDebug()<< "sel:" << sel_ex;
  //                    qDebug()<< " size:" << sel_ex.size();




  //                  }
  //                  else {

  //                    QString es = "01";
  //                    QString es2 = "02";
  //                    QString es3 = "03";
  //                    QString es4 = "04";
  //                    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
  //                      // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
  //                      std::cout<< "Key found";


  //                    }
  //                    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  //                      std::cout<< "key not found";}
  //                  }
  //                  QString EX6 = esercizi.value(10).toString();
  //                  int RIP6 = esercizi.value(11).toInt();
  //                  if(!EX6.isEmpty()) {
  //                    // FILL IT
  //                    cur.EX = EX6; // fill it
  //                    cur.REP = RIP6;
  //                    cur.images = GetImages(EX6);
  //                    ExInfoMap[EX6] = cur; //  add it
  //                    sel_ex.append(EX6);
  //                    qDebug()<< "sel:" << sel_ex;
  //                    qDebug()<< " size:" << sel_ex.size();




  //                  }
  //                  else {

  //                    QString es = "01";
  //                    QString es2 = "02";
  //                    QString es3 = "03";
  //                    QString es4 = "04";
  //                    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
  //                      //ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
  //                      std::cout<< "Key found";


  //                    }
  //                    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  //                      std::cout<< "key not found";}
  //                  }
  //                  QString EX7 = esercizi.value(12).toString();
  //                  int RIP7 = esercizi.value(13).toInt();
  //                  if(!EX7.isEmpty()) {
  //                    // FILL IT
  //                    cur.EX = EX7; // fill it
  //                    cur.REP = RIP7;
  //                    cur.images = GetImages(EX7);
  //                    ExInfoMap[EX7] = cur; //  add it
  //                    sel_ex.append(EX7);
  //                    qDebug()<< "sel:" << sel_ex;
  //                    qDebug()<< " size:" << sel_ex.size();


  //                  }
  //                  else {

  //                    QString es = "01";
  //                    QString es2 = "02";
  //                    QString es3 = "03";
  //                    QString es4 = "04";
  //                    if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
  //                      //ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
  //                      std::cout<< "Key found";


  //                    }
  //                    else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  //                      std::cout<< "key not found";}
  //                  }
  //                }

  //              }

}


/**********************************************************************************/

/**********************       EMG PAGE             *********************/

/**********************************************************************************/

/**********************  CONTINUE AFTER CHECKING EMG ELECTRODES POSITION       *********************/
void paginaprincipale::on_pushButton_clicked()
{
  dati::status1 = SC1_ELECTRODES_CHECK;

  std_msgs::Int16 msg;
  msg.data = dati::status1;
  ROS_INFO ("%d", msg.data);
  status_publisher.publish(msg);
}

/**********************  SHOW RQT PLOT TO CHECK POSITIONING OF THE ELECTRODES        *********************/
void paginaprincipale::on_pushButton_test_matplotlib_clicked()
{

  system("rqt_plot rqt_plot /emg_eeg_module/status/ref_emg /emg_eeg_module/status/check_emg[0] /emg_eeg_module/status/check_emg[1] /emg_eeg_module/status/check_emg[2] /emg_eeg_module/status/check_emg[3] /emg_eeg_module/status/check_emg[4]");



}

/**********************  CONTINUE AFTER EMG WEARING        *********************/
void paginaprincipale::on_pushButton_salta_EMG_clicked()
{
  dati::status1 = SC1_ELECTRODES_POSITION;

  std_msgs::Int16 msg;
  msg.data = dati::status1;
  ROS_INFO ("%d", msg.data);
  status_publisher.publish(msg);
}


/**********************  ACQUIRING EMG REST ENERGY        *********************/
void paginaprincipale::on_pushButton_5_clicked()
{
  dati::status1 = SC1_ELECTRODES_ENERGY_MEASURE;

  std_msgs::Int16 msg;
  msg.data = dati::status1;
  ROS_INFO ("%d", msg.data);
  status_publisher.publish(msg);
}


/**********************************************************************************/

/**********************       WEARING TUTORIAL PAGE             *********************/

/**********************************************************************************/

/**********************       WEARING IMAGES TUTORIAL                      *********************/
QList<QPixmap>GetImages3(QString vestID) {
  QList<QPixmap> mylist3;
  auto folder3 ("/home/alice/Desktop/vestizione/" +vestID);
  QDir directory3(folder3);
  QStringList img_v = directory3.entryList(QStringList() <<"*.jpg" << "*.JPG" <<"*.png" << "*.PNG", QDir::Files );
  qDebug() <<directory3;
  qDebug() << "i found" << img_v.size();
  foreach(QString filename, img_v) {
    QPixmap pix3(folder3 + QString("/") + filename);
    mylist3.append(pix3);
    qDebug()<< mylist3;
  }
  return mylist3;
}

/**********************       SKIP WEARING TUTORIAL  *********************/
void paginaprincipale::on_pushButton_go_clicked()
{  dati::status1 = SC1_WEARING;

   std_msgs::Int16 msg;
    msg.data = dati::status1;
     ROS_INFO ("%d", msg.data);
      status_publisher.publish(msg);
       ui->tabWidget_2->setCurrentWidget(ui->tab_exo_param);
        ui->stackedWidget_4->setCurrentWidget(ui->page_param_agree);

         //  if(dati::command == 4)
         //    ui->tabWidget_2->setCurrentWidget(ui->tab_parametri);
}

/**********************       GO FORWARD WEARING TUTORIAL IMAGES  *********************/
void paginaprincipale::on_pushButton_avanti_v_clicked()
{
  qDebug() << sel_vest;

  if(curVest<sel_vest.size()) {
    key3 = sel_vest.at(curVest);
    qDebug() << key2;
    if(VestInfoMap.find(key3) != VestInfoMap.end()) {
      VestInfo &one3 = VestInfoMap[key3];
      if(curimgs < one3.img_v.size()){
        ui->label_img_vest -> setPixmap(one3.img_v.at(curimgs));
        ui->label_istr_vest->setText(one3.istr_vest.at(curimgs));
        curimgs ++;
      }
      if(curimgs == one3.img_v.size()) {
        curimgs =0;
        curVest++;
      }
    }
  }
  else if(curTut== sel_tut.size()) {
    // timer_init->start(5000);
    if(dati::command_pp == SC1_WEARING) {
      ui->tabWidget_2->setCurrentWidget(ui->tab_parametri);
    }
    ui->label_img_vest->clear();
    ui->label_istr_vest->setText("");

  }
}


/**********************************************************************************/

/**********************       EXO PARAM CONFIGURATION PAGE (length and compensation)      ****************/

/**********************************************************************************/

/**********************        SAVE LENGTH EXO PARAM  *********************/
void paginaprincipale::on_pushButton_salva_exo_param_clicked()
{ QString Lunghezza_braccio, Lunghezza_avambraccio;
  Lunghezza_braccio = ui->lineEdit_braccio -> text();
  //  float Lunghezza_braccio_f = Lunghezza_braccio.toFloat();
  Lunghezza_avambraccio = ui->lineEdit_avambraccio-> text();

  UA_l = Lunghezza_braccio.toDouble();
  LA_l = Lunghezza_avambraccio.toDouble();
  UA_l =UA_l/100;
  LA_l=LA_l/100;
  height = height/100;
  H_l = double(0.108)*height;
  CdM_UA = double(0.436)*UA_l;
  CdM_LA = double(0.43)*LA_l;
  CdM_H = double(0.506)*H_l;
  ros::NodeHandle n;
  n.setParam("/physiological_param/upperarm_length", UA_l);
  n.setParam("/physiological_param/lowerarm_length", LA_l);
  n.setParam("/physiological_param/hand_length",H_l);
  n.setParam("/matlab/len_fore", LA_l);
  n.setParam("/matlab/len_upp", UA_l);


  n.setParam ("/physiological_param/cdm_upperarm", CdM_UA);
  n.setParam("/physiological_param/cdm_lowerarm", CdM_LA);
  n.setParam("/physiological_param/cdm_hand", CdM_H);

  QString l_h, com_ua, com_la, com_h;
  l_h= QString::number(H_l);
  com_ua = QString::number(CdM_UA);
  com_la = QString::number(CdM_LA);
  com_h = QString::number(CdM_H);
  QSqlQuery exo_param;
  exo_param.prepare("update Parametri_Paziente set l_UA= '"+Lunghezza_braccio+"', l_LA = '"+Lunghezza_avambraccio+"', com_UA = '"+com_ua+"', com_LA = '"+com_la+"', com_H = '"+com_h+"', l_H = '"+l_h+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
  if(exo_param.exec()){
  //  QMessageBox ::information(this,tr("Salvataggio"),tr(" Dati Salvati Correttamente"));

  }
  //timer_comp->start(20);
  ui->stackedWidget_4->setCurrentWidget(ui->page_comp);


}

/**********************        SAVE COMPENSATION PARAM   *********************/
void paginaprincipale::on_pushButton_salva_comp_clicked()
{ ros::NodeHandle n;
  int comp,comp_avam;
  comp = ui->progressBar_comp->value();
  comp_avam = ui->progressBar_comp_avam->value();
  //comp= comp/int(125);

  n.setParam("/physiological_param/speed", speed);

  ui->lcdNumber_comp_ses->display(comp);
  ui->progressBar_comp_ses->setValue(comp);
  ui->horizontalSlider_comp_ses->setValue(comp);
  ui->lcdNumber_comp_avam_ses->display(comp_avam);
  ui->progressBar_comp_avam_ses->setValue(comp_avam);
  ui->horizontalSlider_comp_avam_ses->setValue(comp_avam);

  QString comp_s, comp_avam_s;
  comp_s = QString::number(comp);
  comp_avam_s = QString::number(comp_avam);
  QSqlQuery comp_exo;
  comp_exo.prepare("update Parametri_Paziente set compensazione ='"+comp_s+"', compensazione_avamb= '"+comp_avam_s+"', speed = '"+speeds+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
  if(comp_exo.exec()){
  //  QMessageBox ::information(this,tr("Salvataggio"),tr(" Dati Salvati Correttamente"));
    ui->tabWidget_2->setCurrentWidget(ui->tab_parametri);

  }
  else qDebug()<<"non funziona la comp_exo";

}


/**********************  UPDATE COMPENSATION ROS PARAMETER        *********************/
//DOBBIAMO MODIFICARE MSG DELLO STATUS PER MANDARE ANCHE QUESTI
void paginaprincipale::set_comp_param(){

  comp_param = ui->progressBar_comp->value();
  comp_param =comp_param/int(100);
  comp_forearm = ui->progressBar_comp_avam->value();
  qDebug()<<comp_forearm;
  comp_forearm =comp_forearm/int(100);
  ros::NodeHandle n;
  n.setParam ("/physiological_param/arm_compensation", comp_param);
  n.setParam ("/physiological_param/forearm_compensation", comp_forearm);


}

/**********************************************************************************/

/**********************       ROM PAGE      ****************/

/**********************************************************************************/

/**********************        EXPLORE ROM IN THE ROM CONFIGURATION PAGE  *********************/
void paginaprincipale::on_pushButton_esplorarom_clicked()
{
  dati::status1=SC1_MODIFY_ROM;
  msg_status_pp.data = dati::status1;
  status_publisher.publish(msg_status_pp);
}

/**********************       SAVE ROM                       *********************/
void paginaprincipale::on_pushButton_salvaconf_clicked()
{
  QString FESm1, FESM1, AASm1, AASM1, RIESm1, RIESM1,Gm1, GM1, Pm1,PM1;
  double FESm1_f, FESM1_f, AASm1_f, AASM1_f, RIESm1_f, RIESM1_f,Gm1_f, GM1_f, Pm1_f,PM1_f;
  double FESm1_def, FESM1_def, AASm1_def, AASM1_def, RIESm1_def, RIESM1_def,Gm1_def, GM1_def, Pm1_def,PM1_def;
  FESm1_def = -90;
  FESM1_def = 20;
  AASm1_def = -50;
  AASM1_def = 30;
  RIESm1_def = -20;
  RIESM1_def = 90;
  Gm1_def = 0;
  GM1_def = 110;
  Pm1_def = -90;
  PM1_def = 90;
  FESm1= ui->lineEdit_flessospallamin->text();
  FESm1_f = FESm1.toDouble();
  FESM1 = ui->lineEdit_flessospallamax->text();
  FESM1_f = FESM1.toDouble();
  AASm1= ui->lineEdit_adduzionespallamin->text();
  AASm1_f = AASm1.toDouble();
  AASM1 = ui->lineEdit_adduzionespallamax->text();
  AASM1_f = AASM1.toDouble();
  RIESm1= ui->lineEdit_rotazionespallamin->text();
  RIESm1_f = RIESm1.toDouble();
  RIESM1 = ui->lineEdit_rotazionespallamax->text();
  RIESM1_f = RIESM1.toDouble();
  Gm1= ui->lineEdit_gomitomin->text();
  Gm1_f =Gm1.toDouble();
  GM1 = ui->lineEdit_gomitomax->text();
  GM1_f = GM1.toDouble();
  Pm1 = ui ->lineEdit_polsomin->text();
  Pm1_f = Pm1.toDouble();
  PM1= ui->lineEdit_polsomax->text();
  PM1_f = PM1.toDouble();
  if(FESm1_f<FESm1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della flesso estensione minima della spalla è fuori dal valore minimo consentito"));

  }
  else if (FESM1_f > FESM1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della flesso estensione massima della spalla è fuori dal valore massimo consentito"));

  }
  else if(AASm1_f < AASm1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della abdo-adduzione minima della spalla è fuori dal valore minimo consentito"));

  }
  else if (AASM1_f > AASM1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della abdo-adduzione massima della spalla è fuori dal valore massimo consentito"));

  }
  else if(RIESm1_f < RIESm1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della rotazione interna/esterna minima della spalla è fuori dal valore minimo consentito"));

  }
  else if (RIESM1_f > RIESM1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della rotazione interna/esterna massima della spalla è fuori dal valore massimo consentito"));

  }
  else if(Gm1_f < Gm1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della felsso-estensione minima del gomito è fuori dal valore minimo consentito"));

  }
  else if (GM1_f > GM1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della flesso-estensione massima del gomito è fuori dal valore massimo consentito"));

  }
  else if(Pm1_f < Pm1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della prono-supinazione minima del polso è fuori dal valore minimo consentito"));

  }
  else if (PM1_f > PM1_def) {
    QMessageBox ::critical(this,tr("Attenzione"),tr("il range of motion della prono-supinazione massima del polso è fuori dal valore massimo consentito"));

  }
  else {
    QSqlQuery qry9;
    qry9.prepare("update Parametri_Paziente set ROM1_min = '"+FESm1+"', ROM1_max= '"+FESM1+"', ROM2_min= '"+AASm1+"', ROM2_max= '"+AASM1+"', ROM3_min= '"+RIESm1+"', ROM3_max= '"+RIESM1+"', ROM4_min= '"+Gm1+"', ROM4_max= '"+GM1+"', ROM5_min = '"+Pm1+"', ROM5_max= '"+PM1+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    qry9.exec();
    if (qry9.exec())
    {
     // QMessageBox ::information(this,tr("Salvato"),tr("Parametri Salvati"));
      // ui->tabWidget_2->setCurrentWidget(ui->tab_controllo);
      // aggiungo questo:

      //pubblico che ho salvato i rom su gui/status

      dati::status1 = SC1_ROM_FINISHED;

      std_msgs::Int16 msg_status;
      msg_status.data = dati::status1;
      ROS_INFO ("%d", msg_status.data);
      status_publisher.publish(msg_status);

      /***************         SETTO ROS PARAMETERS CON I ROM   ******************/
      J_MAX = {FESM1_f, AASM1_f, RIESM1_f, GM1_f, PM1_f};
      J_MIN = {FESm1_f, AASm1_f, RIESm1_f, Gm1_f, Pm1_f};


      ros::NodeHandle n;

      n.setParam("/physiological_param/ROM_Max", J_MAX);
      n.setParam("/physiological_param/ROM_Min", J_MIN);
      n.setParam("/matlab/rom_max/J1", FESM1_f);
      n.setParam("/matlab/rom_max/J2", AASM1_f);
      n.setParam("/matlab/rom_max/J3", RIESM1_f);
      n.setParam("/matlab/rom_max/J4", GM1_f);
      n.setParam("/matlab/rom_max/J5", PM1_f);

      n.setParam("/matlab/rom_min/J1", FESm1_f);
      n.setParam("/matlab/rom_min/J2", AASm1_f);
      n.setParam("/matlab/rom_min/J3", RIESm1_f);
      n.setParam("/matlab/rom_min/J4", Gm1_f);
      n.setParam("/matlab/rom_min/J5", Pm1_f);


    }
    else {
      QMessageBox ::critical(this,tr("Errore"),tr("bo3"));
    }

  }
}

/**********************************************************************************/

/**********************       PAD CALIBRATION     ****************/

/**********************************************************************************/

/**********************        PAD CALIBRATION  *********************/
void paginaprincipale::on_pushButton_2_clicked()
{
  dati::status1 = SC1_HAND_POSITION;

  std_msgs::Int16 msg;
  msg.data = dati::status1;
  ROS_INFO ("%d", msg.data);
  status_publisher.publish(msg);
}

/**********************************************************************************/

/**********************       SAVING TARGET POINTS PAD     ****************/

/**********************************************************************************/

/**********************       SAVE 3 POINTS                        *********************/
void paginaprincipale::on_pushButton_salvatapp_clicked()
{

  QVector<QPoint> mylocalList =matrix->getPosition();


  dati::status1 = SC1_FINISHED;

  std_msgs::Int16 msg;
  msg.data = dati::status1;
  ROS_INFO ("%d", msg.data);
  status_publisher.publish(msg);
  dati::selcount_mat=0;


}

/**********************************************************************************/

/**********************       RECAP SESSION PAGE     ****************/

/**********************************************************************************/

/**********************       ENABLE INTERACTIVE OBJECTS COMBOBOX                      *********************/

void paginaprincipale::enable_combo_recap(){
  ui->comboBox_ogg1->setEnabled(false);
  ui->comboBox_ogg2->setEnabled(false);
  ui->comboBox_ogg3->setEnabled(false);
  ui->comboBox_ogg4->setEnabled(false);
  ui->comboBox_ogg5->setEnabled(false);
  ui->comboBox_ogg6->setEnabled(false);
  ui->comboBox_ogg7->setEnabled(false);


  es2 = "Raggiungimento anteriore di target su un piano con oggetto";
  es4 = "Raggiungimento anteriore di target su un piano nello spazio con oggetto";
  es7 = "Mano alla bocca con oggetto";

  qDebug()<< "sono nella funzione enable_combo";
  if(ui->comboBox_es1->currentText()==es2 || ui->comboBox_es1->currentText()== es4 || ui->comboBox_es1->currentText()== es7) {
    ui->comboBox_ogg1->setEnabled(true);

  }
  if(ui->comboBox_es2->currentText()==es2 || ui->comboBox_es2->currentText()== es4 || ui->comboBox_es2->currentText()== es7) {
    ui->comboBox_ogg2->setEnabled(true);

  }
  if(ui->comboBox_es3->currentText()==es2 || ui->comboBox_es3->currentText()== es4 || ui->comboBox_es3->currentText()== es7) {
    ui->comboBox_ogg3->setEnabled(true);

  }
  if(ui->comboBox_es4->currentText()==es2 || ui->comboBox_es4->currentText()== es4 || ui->comboBox_es4->currentText()== es7) {
    ui->comboBox_ogg4->setEnabled(true);

  }
  if(ui->comboBox_es5->currentText()==es2 || ui->comboBox_es5->currentText()== es4 || ui->comboBox_es5->currentText()== es7) {
    ui->comboBox_ogg5->setEnabled(true);

  }
  if(ui->comboBox_es6->currentText()==es2 || ui->comboBox_es6->currentText()== es4 || ui->comboBox_es6->currentText()== es7) {
    ui->comboBox_ogg6->setEnabled(true);

  }
  if(ui->comboBox_es7->currentText()==es2 || ui->comboBox_es7->currentText()== es4 || ui->comboBox_es7->currentText()== es7) {
    ui->comboBox_ogg7->setEnabled(true);
  }
}

/**********************       UPDATE THERAPY TIME IN THE RECAP                      *********************/
void paginaprincipale::update_tempo_recap(){

  qDebug()<< "sono nella funzione update_tempo_terapia";
  es1 = "Raggiungimento anteriore di target su un piano senza oggetti";
  es2 = "Raggiungimento anteriore di target su un piano con oggetti";
  es3 = "Raggiungimento anteriore di target su un piano nello spazio senza oggetti";
  es4 = "Raggiungimento anteriore di target su un piano nello spazio con oggetti ";
  es5 = "Elevazione laterale su un piano frontale";
  es6 = "Mano alla bocca senza oggetto";
  es7 = "Mano alla bocca con oggetto";
  es8 = "Exergames - Basket";
  es9 = "Exergames - Macedonia";
  es10 = "Exergames - Spesa";
  es11 = "Exergames - Caffè";



  if (ui->comboBox_es1->currentText()== es1 || ui->comboBox_es1->currentText()==es3 || ui->comboBox_es1->currentText() == es5 || ui->comboBox_es1->currentText()== es6){
    t_es1 = 1;
    ripe1 = ui->lineEdit_rep1->text().toInt();
    //ripe1 = dati::rip1.toInt();
    t_es1 = t_es1*ripe1;
    qDebug() << "es 1";
    qDebug() << t_es1;

  }
  else if (ui->comboBox_es1->currentText() == es2 || ui->comboBox_es1->currentText()== es7|| ui->comboBox_es1->currentText()==es4 || ui->comboBox_es1->currentText()== es8 || ui->comboBox_es1->currentText()== es9 || ui->comboBox_es1->currentText()== es10 || ui->comboBox_es1->currentText()== es11) {
    t_es1 = 2;
    ripe1 = ui->lineEdit_rep1->text().toInt();
    t_es1 = t_es1* ripe1;
    qDebug() << "es 1";
    qDebug() << t_es1;
  }
  if (ui->comboBox_es2->currentText()== es1 || ui->comboBox_es2->currentText()==es3 || ui->comboBox_es2->currentText() == es5 || ui->comboBox_es2->currentText()== es6){
    t_es2 = 1;
    ripe2 = ui->lineEdit_rep2->text().toInt();
    t_es2 = t_es2*ripe2;
    qDebug() << "es2";
    qDebug() << t_es2;

  }
  else if ( ui->comboBox_es2->currentText() == es2 || ui->comboBox_es2->currentText()== es7|| ui->comboBox_es2->currentText()==es4) {
    t_es2 = 2;
    ripe2 = ui->lineEdit_rep2->text().toInt();
    t_es2 = t_es2* ripe2;
    qDebug() << "es2";
    qDebug() << t_es2;
  }
  if (ui->comboBox_es3->currentText()== es1 || ui->comboBox_es3->currentText()==es3 || ui->comboBox_es3->currentText() == es5 || ui->comboBox_es3->currentText()== es6){
    t_es3 = 1;
    ripe3 = ui->lineEdit_rep3->text().toInt();
    t_es3 = t_es3*ripe3;
    qDebug() << "es3";
    qDebug() << t_es3;

  }
  else if ( ui->comboBox_es3->currentText() == es2 || ui->comboBox_es3->currentText()== es7 || ui->comboBox_es3->currentText()==es4 || ui->comboBox_es3->currentText()== es8 || ui->comboBox_es3->currentText()== es9 || ui->comboBox_es3->currentText()== es10 || ui->comboBox_es3->currentText()== es11) {
    t_es3 = 2;
    ripe3 = ui->lineEdit_rep3->text().toInt();
    t_es3 = t_es3* ripe3;
    qDebug() << "es3";
    qDebug() << t_es3;
  }
  if (ui->comboBox_es4->currentText()== es1 || ui->comboBox_es4->currentText()==es3 || ui->comboBox_es4->currentText() == es5 || ui->comboBox_es4->currentText()== es6){
    t_es4 = 1;
    ripe4 = ui->lineEdit_rep4->text().toInt();
    t_es4 = t_es4*ripe4;

  }
  else if ( ui->comboBox_es4->currentText() == es2 || ui->comboBox_es4->currentText()== es7 || ui->comboBox_es4->currentText()==es4 || ui->comboBox_es4->currentText()== es8 || ui->comboBox_es4->currentText()== es9 || ui->comboBox_es4->currentText()== es10 || ui->comboBox_es4->currentText()== es11) {
    t_es4 = 2;
    ripe4 = ui->lineEdit_rep4->text().toInt();
    t_es4 = t_es4* ripe4;
  }
  if (ui->comboBox_es5->currentText()== es1 || ui->comboBox_es5->currentText()==es3 || ui->comboBox_es5->currentText() == es5 || ui->comboBox_es5->currentText()== es6){
    t_es5 = 1;
    ripe5 = ui->lineEdit_rep5->text().toInt();
    t_es5 = t_es5*ripe5;

  }
  else if ( ui->comboBox_es5->currentText() == es2 || ui->comboBox_es5->currentText()== es7 || ui->comboBox_es5->currentText()==es4 || ui->comboBox_es5->currentText()== es8 || ui->comboBox_es5->currentText()== es9 || ui->comboBox_es5->currentText()== es10 || ui->comboBox_es5->currentText()== es11) {
    t_es5 = 2;
    ripe5 = ui->lineEdit_rep5->text().toInt();
    t_es5 = t_es5* ripe5;
  }

  if (ui->comboBox_es6->currentText()== es1 || ui->comboBox_es6->currentText()==es3 || ui->comboBox_es6->currentText() == es5 || ui->comboBox_es6->currentText()== es6){
    t_es6 = 1;
    ripe6 = ui->lineEdit_rep6->text().toInt();
    t_es6 = t_es6*ripe6;

  }
  else if ( ui->comboBox_es6->currentText() == es2 || ui->comboBox_es6->currentText()== es7 || ui->comboBox_es6->currentText()==es4 || ui->comboBox_es6->currentText()== es8 || ui->comboBox_es6->currentText()== es9 || ui->comboBox_es6->currentText()== es10 || ui->comboBox_es6->currentText()== es11) {
    t_es6 = 2;
    ripe6 = ui->lineEdit_rep6->text().toInt();
    t_es6 = t_es6* ripe6;
  }

  if (ui->comboBox_es7->currentText()== es1 || ui->comboBox_es7->currentText()==es3 || ui->comboBox_es7->currentText() == es5 || ui->comboBox_es7->currentText()== es6){
    t_es7 = 1;
    ripe7 = ui->lineEdit_rep7->text().toInt();
    t_es7 = t_es7*ripe7;

  }
  else if ( ui->comboBox_es7->currentText() == es2 || ui->comboBox_es7->currentText()== es7 || ui->comboBox_es7->currentText()==es4 || ui->comboBox_es7->currentText()== es8 || ui->comboBox_es7->currentText()== es9 || ui->comboBox_es7->currentText()== es10 || ui->comboBox_es7->currentText()== es11) {
    t_es7 = 2;
    ripe7 = ui->lineEdit_rep7->text().toInt();
    t_es7 = t_es7* ripe7;
  }
  if(ui->checkBox_es1->isChecked()) {
    temp_tot = t_es1;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_es2->isChecked()) {
    temp_tot += t_es2;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_es3->isChecked()) {
    temp_tot += t_es3;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_es4->isChecked()) {
    temp_tot += t_es4;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_es5->isChecked()) {
    temp_tot += t_es5;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_es6->isChecked()) {
    temp_tot += t_es6;
    temp_string = QString::number(temp_tot);
  }
  if(ui->checkBox_es7->isChecked()) {
    temp_tot += t_es7;
    temp_string = QString::number(temp_tot);
  }


  qDebug()<< temp_tot;
  qDebug()<< temp_string;

  QString test = QString("Tempo Stimato per la Terapia : %1 minuti").arg(temp_string);

  ui->label_tempo_recap->setText(test);

}


/**********************       ENABLE EXERCISES COMBOXES IN THE RECAP                       *********************/
void paginaprincipale::enable_combo_ex_recap() {
  ui->comboBox_es1->setEnabled(false);
  ui->comboBox_es2->setEnabled(false);
  ui->comboBox_es3->setEnabled(false);
  ui->comboBox_es4->setEnabled(false);
  ui->comboBox_es5->setEnabled(false);
  ui->comboBox_es6->setEnabled(false);
  ui->comboBox_es7->setEnabled(false);

  if(ui->checkBox_es1->isChecked() ) {
    ui->comboBox_es1->setEnabled(true);
  }
  if(ui->checkBox_es2->isChecked() ) {
    ui->comboBox_es2->setEnabled(true);
  }
  if(ui->checkBox_es3->isChecked()) {
    ui->comboBox_es3->setEnabled(true);
  }
  if(ui->checkBox_es4->isChecked() ) {
    ui->comboBox_es4->setEnabled(true);
  }
  if(ui->checkBox_es5->isChecked() ) {
    ui->comboBox_es5->setEnabled(true);
  }
  if(ui->checkBox_es6->isChecked()) {
    ui->comboBox_es6->setEnabled(true);
  }
  if(ui->checkBox_es7->isChecked()) {
    ui->comboBox_es7->setEnabled(true);
  }
}

/**********************        CONFIRM RECAP  *********************/
void paginaprincipale::on_pushButton_conferma_recap_clicked()
{
  ui->stackedWidget_2->setCurrentWidget(ui->page_sessione);
}


/**********************        EDIT EXERCISES RECAP  *********************/
void paginaprincipale::on_pushButton_modifica_recap_clicked()
{
  ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  ui->stackedWidget_2->setCurrentWidget(ui->modifica_recap);
}

/**********************        ADD EXERCISES IN RECAP PAGE  *********************/
void paginaprincipale::on_pushButton_add_2_clicked()
{
  if(dati::flag_ex_recap == 0) {
    dati::flag_ex_recap++;}
  if(dati::flag_ex_recap == 1) {
    ui->checkBox_es2->setChecked(true);

    dati::flag_ex_recap++;
    qDebug()<<dati::flag_ex_recap;
  }
  else if (dati::flag_ex_recap==2) {
    ui->checkBox_es3->setChecked(true);
    dati::flag_ex_recap++;
    qDebug()<<dati::flag_ex_recap;
  }
  else if (dati::flag_ex_recap==3) {
    ui->checkBox_es4->setChecked(true);
    dati::flag_ex_recap++;
    qDebug()<<dati::flag_ex_recap;
  }
  else if (dati::flag_ex_recap==4) {
    ui->checkBox_es5->setChecked(true);
    dati::flag_ex_recap++;
    qDebug()<<dati::flag_ex_recap;
  }
  else if (dati::flag_ex_recap==5) {
    ui->checkBox_es6->setChecked(true);
    dati::flag_ex_recap++;
    qDebug()<<dati::flag_ex_recap;
  }
  else if (dati::flag_ex_recap==6) {
    ui->checkBox_es7->setChecked(true);
    // dati::flag_ex++;
    qDebug()<<dati::flag_ex_recap;
  }
}

/**********************        REMOVE EXERCISES IN RECAP PAGE  *********************/
void paginaprincipale::on_pushButton_remove_2_clicked()
{
  if(dati::flag_ex_recap == 6){
    ui->checkBox_es7->setChecked(false);
    dati::flag_ex_recap--;
    qDebug()<<dati::flag_ex_recap;

  }
  else if (dati::flag_ex_recap ==5) {
    ui->checkBox_es6->setChecked(false);
    dati::flag_ex_recap--;
    qDebug()<<dati::flag_ex_recap;
  }
  else if (dati::flag_ex_recap ==4) {
    ui->checkBox_es5->setChecked(false);
    dati::flag_ex_recap--;
    qDebug()<<dati::flag_ex_recap;
  }
  else if (dati::flag_ex_recap ==3) {
    ui->checkBox_es4->setChecked(false);
    dati::flag_ex_recap--;
    qDebug()<<dati::flag_ex_recap;
  }
  else if (dati::flag_ex_recap ==2) {
    ui->checkBox_es3->setChecked(false);
    dati::flag_ex_recap--;
    qDebug()<<dati::flag_ex_recap;
  }
  else if (dati::flag_ex_recap ==1) {
    ui->checkBox_es2->setChecked(false);
    dati::flag_ex_recap--;
    qDebug()<<dati::flag_ex_recap;
  }
}

/**********************        SAVE EXERCISES AND MODALITY RECAP  *********************/
void paginaprincipale::on_pushButton_salva_recap_clicked()
{
  QString bicchiere, borraccia, tazza;
  bicchiere = "Bicchiere";
  borraccia = "Borraccia";
  tazza = "Tazza";

  if(ui->checkBox_es1->isChecked())
  {  check_ex1=1;

    dati::ex1 = ui->comboBox_es1->currentText();





    dati::rip1= ui->lineEdit_rep1->text();




    rep1 = dati::rip1.toInt();
    if(ui->comboBox_ogg1->isEnabled()) {
      if(ui->comboBox_ogg1->currentText()== bicchiere ) {  oggetto_es1= "1"; ros_ogg1=1; ui->label_oi1_recap->setText(bicchiere);}
      else if (ui->comboBox_ogg1->currentText()==borraccia) { oggetto_es1= "2"; ros_ogg1=2; ui->label_oi1_recap->setText(borraccia);}
      else if(ui->comboBox_ogg1 ->currentText()==tazza) {ui->comboBox_ogg1->setCurrentText("tazza"); oggetto_es1= "3"; ros_ogg1=3; ui->label_oi1_recap->setText(tazza);} }
    else if (!(ui->comboBox_ogg1->isEnabled())) {
      oggetto_es1="0";
      ros_ogg1 = 0;
    }
    qDebug()<< oggetto_es1;
    QSqlQuery selezione1;
    selezione1.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex1+"'");
    selezione1.exec();
    if (selezione1.exec()) {
      while(selezione1.next())
      {
        dati::num_ex1 = selezione1.value(0).toString();
        exe1 = dati::num_ex1.toInt();

      }
      if(dati::rip1.toInt()< 30) {

      }
      else if(dati::rip1.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni del primo esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));


      }
    }

    if(!(dati::num_ex1.toInt()==2 || dati::num_ex1.toInt()==4 || dati::num_ex1.toInt()==7) ) {

      ui->comboBox_oi_es1->setEnabled(false);
    }

  }
  if(ui->checkBox_ex2->isChecked())
  {
    dati::ex2 = ui->comboBox_ex2->currentText();



    dati::rip2= ui->lineEdit_ex2->text();




    rep2 = dati::rip2.toInt();
    if(ui->comboBox_ogg2->isEnabled()) {
      if(ui->comboBox_ogg2->currentText()== bicchiere ) {  oggetto_es2= "1"; ros_ogg2=1; ui->label_oi2_recap->setText(bicchiere);}
      else if (ui->comboBox_ogg2->currentText()==borraccia) { oggetto_es2 = "2"; ros_ogg2= 2; ui->label_oi2_recap->setText(borraccia);}
      else if(ui->comboBox_ogg2 ->currentText()==tazza) {oggetto_es2= "3"; ros_ogg2= 3; ui->label_oi2_recap->setText(tazza);} }
    else if (!(ui->comboBox_ogg2->isEnabled())) {
      oggetto_es2 = "0";
      ros_ogg2 = 0;
    }
    QSqlQuery selezione2;
    selezione2.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex2+"'");
    selezione2.exec();
    if (selezione2.exec()) {
      while(selezione2.next())
      {
        dati::num_ex2 = selezione2.value(0).toString();
        exe2 = dati::num_ex2.toInt();


      }
      if(dati::rip2.toInt()<30) {

      }
      else if (dati::rip2.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }

  }
  if(ui->checkBox_es3->isChecked())
  {
    dati::ex3 = ui->comboBox_es3->currentText();



    dati::rip3= ui->lineEdit_rep3->text();




    rep3 = dati::rip3.toInt();
    if(ui->comboBox_ogg3->isEnabled()) {
      if(ui->comboBox_ogg3->currentText()== bicchiere ) { oggetto_es3= "1"; ros_ogg3=1; ui->label_oi3_recap->setText(bicchiere);}
      else if (ui->comboBox_ogg3->currentText()==borraccia) { oggetto_es3= "2"; ros_ogg3=2; ui->label_oi3_recap->setText(borraccia);}
      else if(ui->comboBox_ogg3 ->currentText()==tazza) {  oggetto_es3= "3"; ros_ogg3=3; ui->label_oi3_recap->setText(tazza);} }
    else if(!(ui->comboBox_ogg3->isEnabled())) {
      oggetto_es3 = "0";
      ros_ogg3 = 0;
    }
    QSqlQuery selezione3;
    selezione3.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex3+"'");
    selezione3.exec();
    if (selezione3.exec()) {
      while(selezione3.next())
      {
        dati::num_ex3 = selezione3.value(0).toString();
        exe3 = dati::num_ex3.toInt();


      }
      if(dati::rip3.toInt()<30) {

      }
      else if (dati::rip3.toInt()>30) {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }

  }
  if(ui->checkBox_es4->isChecked())
  {
    dati::ex4 = ui->comboBox_es4->currentText();



    dati::rip4= ui->lineEdit_rep4->text();


    rep4 = dati::rip4.toInt();
    if(ui->comboBox_ogg4->isEnabled()) {
      if(ui->comboBox_ogg4->currentText()== bicchiere ) {oggetto_es4= "1"; ros_ogg4=1; ui->label_oi4_recap->setText(bicchiere);}
      else if (ui->comboBox_ogg4->currentText()==borraccia) { oggetto_es4= "2"; ros_ogg4=2; ui->label_oi4_recap->setText(borraccia);}
      else if(ui->comboBox_ogg4 ->currentText()==tazza) { oggetto_es4= "3"; ros_ogg4=3; ui->label_oi4_recap->setText(tazza);} }
    else if (!(ui->comboBox_ogg4->isEnabled())) {
      oggetto_es4 = "0";
      ros_ogg4 = 0;
    }
    QSqlQuery selezione4;
    selezione4.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex4+"'");
    selezione4.exec();
    if (selezione4.exec()) {
      while(selezione4.next())
      {
        dati::num_ex4 = selezione4.value(0).toString();
        exe4 = dati::num_ex4.toInt();


      }
      if (dati::rip4.toInt()<30) {

      }
      else if (dati::rip4.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }

  }
  if(ui->checkBox_es5->isChecked())
  {
    dati::ex5 = ui->comboBox_es5->currentText();



    dati::rip5= ui->lineEdit_rep5->text();




    rep5 = dati::rip5.toInt();
    if(ui->comboBox_ogg5->isEnabled()) {
      if(ui->comboBox_ogg5->currentText()== bicchiere ) { oggetto_es5= "1"; ros_ogg5=1; ui->label_oi5_recap->setText(bicchiere);}
      else if (ui->comboBox_ogg5->currentText()==borraccia) { oggetto_es5= "2"; ros_ogg5=2; ui->label_oi5_recap->setText(borraccia);}
      else if(ui->comboBox_ogg5->currentText()==tazza) { oggetto_es5= "3"; ros_ogg5=3;ui->label_oi5_recap->setText(tazza);} }
    else if (!(ui->comboBox_ogg5->isEnabled())) {
      oggetto_es5 = "0";
      ros_ogg5 = 0;

    }
    QSqlQuery selezione5;
    selezione5.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex5+"'");
    selezione5.exec();
    if (selezione5.exec()) {
      while(selezione5.next())
      {
        dati::num_ex5 = selezione5.value(0).toString();
        exe5 = dati::num_ex5.toInt();


      }
      if(dati::rip5.toInt()<30) {

      }
      else if(dati::rip5.toInt()>30) {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }

    }

  }
  if(ui->checkBox_es6->isChecked())
  {
    dati::ex6 = ui->comboBox_es6->currentText();


    dati::rip6= ui->lineEdit_rep6->text();




    rep6 = dati::rip6.toInt();
    if(ui->comboBox_ogg6->isEnabled()) {
      if(ui->comboBox_ogg6->currentText()== bicchiere ) { oggetto_es6= "1"; ros_ogg6=1; ui->label_oi6_recap->setText(bicchiere);}
      else if (ui->comboBox_ogg6->currentText()==borraccia) { oggetto_es6= "2"; ros_ogg6=2;ui->label_oi6_recap->setText(borraccia);}
      else if(ui->comboBox_ogg6 ->currentText()==tazza) { oggetto_es6= "3"; ros_ogg6=3;ui->label_oi6_recap->setText(tazza);} }
    else if(!(ui->comboBox_ogg6->isEnabled()))  {
      oggetto_es6 = "0";
      ros_ogg6 = 0;
    }
    QSqlQuery selezione6;
    selezione6.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex6+"'");
    selezione6.exec();
    if (selezione6.exec()) {
      while(selezione6.next())
      {
        dati::num_ex6 = selezione6.value(0).toString();
        exe6 = dati::num_ex6.toInt();


      }
      if(dati::rip6.toInt()<30) {

      }
      else if(dati::rip6.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }


  }
  if(ui->checkBox_es7->isChecked())
  {
    dati::ex7 = ui->comboBox_es7->currentText();



    dati::rip7= ui->lineEdit_ex7->text();




    rep7 = dati::rip7.toInt();
    if(ui->comboBox_ogg7->isEnabled()) {
      if(ui->comboBox_ogg7->currentText()== bicchiere ) { oggetto_es7= "1"; ros_ogg7=1; ui->label_oi7_recap->setText(bicchiere);}
      else if (ui->comboBox_ogg7->currentText()==borraccia) { oggetto_es7= "2"; ros_ogg7=2; ui->label_oi7_recap->setText(borraccia);}
      else if(ui->comboBox_ogg7 ->currentText()==tazza) { oggetto_es7= "3"; ros_ogg7=3; ui->label_oi7_recap->setText(tazza);} }
    else if(!(ui->comboBox_ogg7 ->isEnabled())) {
      oggetto_es7 = "0";
      ros_ogg7 = 0;
    }
    QSqlQuery selezione7;
    selezione7.prepare("select Num_ex from Esercizi where Ex = '"+dati::ex7+"'");
    selezione7.exec();
    if (selezione7.exec()) {
      while(selezione7.next())
      {
        dati::num_ex7 = selezione7.value(0).toString();
        exe7 = dati::num_ex7.toInt();


      }
      if(dati::rip7.toInt()<30) {

      }
      else if(dati::rip7.toInt()>30)
      {
        QMessageBox::warning(this, tr("Attenzione"), tr("Numero di ripetizioni dell'esercizio selezionato ha superato il limite massimo di 30, si prega di modificare."));
      }
    }

  }
  qDebug()<< dati::ind;
  QSqlQuery selezione;
  selezione.prepare("update Parametri_Paziente set ex1 = '"+dati::num_ex1+"', rip1 = '"+dati::rip1+"', ogg_es1 = '"+oggetto_es1+"', ex2 = '"+dati::num_ex2+"', rip2 = '"+dati::rip2+"',ogg_es2 = '"+oggetto_es2+"', ex3 = '"+dati::num_ex3+"', rip3 = '"+dati::rip3+"', ogg_es3 = '"+oggetto_es3+"',ex4 = '"+dati::num_ex4+"', rip4 = '"+dati::rip4+"', ogg_es4 = '"+oggetto_es4+"',ex5 = '"+dati::num_ex5+"', rip5 = '"+dati::rip5+"',ogg_es5 = '"+oggetto_es5+"',ex6 = '"+dati::num_ex6+"', rip6 = '"+dati::rip6+"', ogg_es6 = '"+oggetto_es6+"',ex7 = '"+dati::num_ex7+"', rip7 = '"+dati::rip7+"', ogg_es7 = '"+oggetto_es7+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' ");
  selezione.exec();
  if (selezione.exec())
  {
  //  QMessageBox ::information(this,tr("Salvato"),tr("Set di esercizi salvati"));




    /******************         AGGIORNO ROS PARAMETERS : EXERCISE SEQUENCE                      ***********************/
    ex_seq = {exe1, exe2, exe3, exe4, exe5, exe6, exe7};
    ex_rep = {rep1, rep2, rep3, rep4, rep5, rep6, rep7};
    ex_obj = {ros_ogg1, ros_ogg2, ros_ogg3, ros_ogg4, ros_ogg5, ros_ogg6, ros_ogg7};
    ros::NodeHandle n;
    n.setParam("/exercise/sequence", ex_seq);
    n.setParam("/exercise/repetition", ex_rep);
    n.setParam ("/exercise/objects", ex_obj);

  }
  else {
    QMessageBox ::critical(this,tr("Errore"),tr("errore"));
    qDebug()<< selezione.lastError();
  }

  QSqlQuery esercizi;
  esercizi.prepare("select ex1,rip1,ex2,rip2,ex3,rip3,ex4,rip4,ex5,rip5,ex6,rip6,ex7,rip7 from Parametri_Paziente where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' order by Data_acquisizione desc limit 1");
  if(esercizi.exec()){
    while(esercizi.next())
    { ExInfo cur;
      QString EX1 = esercizi.value(0).toString();
      int RIP1 = esercizi.value(1).toInt();

      if ( ! EX1.isEmpty() ){
        // FILL IT
        cur.EX = EX1; // fill it
        cur.REP = RIP1;
        cur.images = GetImages(EX1);
        ExInfoMap[EX1] = cur; //  add it
        qDebug()<<cur.images.size();
        sel_ex.append(EX1);
        qDebug()<< "sel:" << sel_ex;
        qDebug()<< " size:" << sel_ex.size();
      }
      else {
        QString es = "01";
        QString es2 = "02";
        QString es3 = "03";
        QString es4 = "04";
        if(ExInfoMap.find(es) !=ExInfoMap.end() || (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
          // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);

        }
        //else ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
      }

      QString EX2 = esercizi.value(2).toString();
      int RIP2 = esercizi.value(3).toInt();
      if(!EX2.isEmpty()) {
        // FILL IT
        cur.EX = EX2; // fill it
        cur.REP = RIP2;
        cur.images = GetImages(EX2);  // use ID to get images  /////////////////////////////////////////////// IMAGES
        ExInfoMap[EX2] = cur; //  add it
        sel_ex.append(EX2);
        qDebug()<< "sel:" << sel_ex;
        qDebug()<< " size:" << sel_ex.size();

      }
      else {

        QString es = "01";
        QString es2 = "02";
        QString es3 = "03";
        QString es4 = "04";
        if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
          // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
          std::cout<< "Key found";


        }
        else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
          std::cout<< "key not found";}
      }

      QString EX3 = esercizi.value(4).toString();
      int RIP3 = esercizi.value(5).toInt();
      if(!EX3.isEmpty()) {
        // FILL IT
        cur.EX = EX3; // fill it
        cur.REP = RIP3;
        cur.images = GetImages(EX3);
        ExInfoMap[EX3] = cur; //  add it
        sel_ex.append(EX3);
        qDebug()<< "sel:" << sel_ex;
        qDebug()<< " size:" << sel_ex.size();

      }
      else {

        QString es = "01";
        QString es2 = "02";
        QString es3 = "03";
        QString es4 = "04";
        if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
          // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
          std::cout<< "Key found";


        }
        else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
          std::cout<< "key not found";}
      }
      QString EX4 = esercizi.value(6).toString();
      int RIP4 = esercizi.value(7).toInt();
      if(!EX4.isEmpty()) {
        // FILL IT
        cur.EX = EX4; // fill it
        cur.REP = RIP4;
        cur.images = GetImages(EX4);
        ExInfoMap[EX4] = cur; //  add it
        sel_ex.append(EX4);
        qDebug()<< "sel:" << sel_ex;
        qDebug()<< " size:" << sel_ex.size();




      }
      else {

        QString es = "01";
        QString es2 = "02";
        QString es3 = "03";
        QString es4 = "04";
        if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
          //ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
          std::cout<< "Key found";


        }
        else  {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
          std::cout<< "key not found";}
      }
      QString EX5 = esercizi.value(8).toString();
      int RIP5 = esercizi.value(9).toInt();
      if(!EX5.isEmpty()){
        // FILL IT
        cur.EX = EX5; // fill it
        cur.REP = RIP5;
        cur.images = GetImages(EX5);
        ExInfoMap[EX5] = cur; //  add it
        sel_ex.append(EX5);
        qDebug()<< "sel:" << sel_ex;
        qDebug()<< " size:" << sel_ex.size();




      }
      else {

        QString es = "01";
        QString es2 = "02";
        QString es3 = "03";
        QString es4 = "04";
        if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
          // ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
          std::cout<< "Key found";


        }
        else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
          std::cout<< "key not found";}
      }
      QString EX6 = esercizi.value(10).toString();
      int RIP6 = esercizi.value(11).toInt();
      if(!EX6.isEmpty()) {
        // FILL IT
        cur.EX = EX6; // fill it
        cur.REP = RIP6;
        cur.images = GetImages(EX6);
        ExInfoMap[EX6] = cur; //  add it
        sel_ex.append(EX6);
        qDebug()<< "sel:" << sel_ex;
        qDebug()<< " size:" << sel_ex.size();




      }
      else {

        QString es = "01";
        QString es2 = "02";
        QString es3 = "03";
        QString es4 = "04";
        if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
          //ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
          std::cout<< "Key found";


        }
        else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
          std::cout<< "key not found";}
      }
      QString EX7 = esercizi.value(12).toString();
      int RIP7 = esercizi.value(13).toInt();
      if(!EX7.isEmpty()) {
        // FILL IT
        cur.EX = EX7; // fill it
        cur.REP = RIP7;
        cur.images = GetImages(EX7);
        ExInfoMap[EX7] = cur; //  add it
        sel_ex.append(EX7);
        qDebug()<< "sel:" << sel_ex;
        qDebug()<< " size:" << sel_ex.size();


      }
      else {

        QString es = "01";
        QString es2 = "02";
        QString es3 = "03";
        QString es4 = "04";
        if(ExInfoMap.find(es) !=ExInfoMap.end()|| (ExInfoMap.find(es2)) != ExInfoMap.end() || ExInfoMap.find(es3 ) != ExInfoMap.end() || ExInfoMap.find(es4)!= ExInfoMap.end()) {
          //ui->tabWidget_2->setCurrentWidget(ui->tab_tappetino);
          std::cout<< "Key found";


        }
        else {//ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
          std::cout<< "key not found";}
      }
    }

  }



  /**********************       INSERISCO VALUTAZIONI FITTIZIE                      *********************/
  //  QSqlQuery ins_val;
  //  ins_val.prepare("insert into Valutazioni (Codice_ID, Data_acquisizione) values('"+dati::ind+"', '"+dati::data1+"') ");

  //  if (ins_val.exec()) {
  //    qDebug()<< "fatto";
  //  }
  //  else qDebug()<< ins_val.lastError();





  ui->tabWidget_2->setCurrentWidget(ui->tab_sessione);
  ui->stackedWidget_2->setCurrentWidget(ui->page_sessione);

  // qDebug()<< rand1;
}


/**********************************************************************************/

/**********************       THERAPY SESSIONE PAGE     ****************/

/**********************************************************************************/

/**********************       START THERAPY                        *********************/
void paginaprincipale::on_pushButton_next_clicked()
{ //qDebug()<<sel_ex;
  ui->progressBar_th->setVisible(true);
  ui->progressBar_th->setMinimum(0);
  ui->progressBar_th->setMaximum(dati::rep_index);



  ui->pushButton_next->setVisible(false);
  timer_rehab->start(20);
  dati::status1 = SC1_START_SESSION;

  std_msgs::Int16 msg;
  msg.data = dati::status1;
  ROS_INFO ("%d", msg.data);
  status_publisher.publish(msg);

}

/**********************          SHOW EXERCISES IMAGES                    *********************/
void paginaprincipale::next_img() {
  qDebug()<< dati::command_exercise_pp;

  //GET PARAM DEI PUNTI DEL TAPPETINO PER FARE CONTROLLO SU COLONNE
  ros::NodeHandle n;
  n.getParam("/point1/mat_coordinates", point1ses);
  n.getParam("/point2/mat_coordinates", point2ses);
  n.getParam("/point3/mat_coordinates", point3ses);


  ui->pushButton_salvascore->setVisible(false);
  QString istr99, istr199, istr_def, istr1_1, istr3_1, istr5_1, istr1_3, istr2_3, istr3_3, istr4_3, istr5_3, istr6_3, istr7_3, istr8_3, istr9_3, istr_def6, istr2_6, istr_def7, istr2_7, istr_terap, istr0_3;
  istr99 = "Resta in Attesa di una nuova istruzione";
  istr199 = "Caricamento Exergame in corso, attendere";
  istr_def = "Posizione di Riposo";
  istr_def6 = "Posizione di Riposo";
  //  istr_def7 = "Posizione di Riposo";

  //ISTRUZIONI ESERCIZIO 1
  istr1_1 = "Porta il braccio sul punto Rosso";
  istr3_1 = "Porta il braccio sul punto Rosso";
  istr5_1 = "Porta il braccio sul punto Rosso";



  //ISTRUZIONI ESERCIZIO 6
  istr_terap = "Terapista, posiziona l'oggetto in posizione di riposo ";
  istr2_6 = "porta l'oggetto alla bocca";



  //ISTRUZIONI ESERCIZIO 7

  istr2_7= "Eleva il braccio lateralmente";

  //EXER 1 IMAGES

  QPixmap case99("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/wait.jpg"); // ATTESA

  //  QPixmap case1_1, case3_1, case5_1, def, case1_3, case2_3, case3_3, case4_3, case5_3, case6_3, case7_3, case8_3, case9_3, case1_5, case2_5, case1_6, case2_6, def_5, def_6;
  //check for the side of the exoskeleton
  if(dati::lato=="0") {

    //EXERCISE 1
    QPixmap feedback_happy("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/smile.jpeg");


    QPixmap case1_1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_2.png");
    QPixmap case1_1_c("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_3.png");
    QPixmap case1_1_d("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_4.png");

    QPixmap case3_1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_3.png");
    QPixmap case3_1_s("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_2.png");
    QPixmap case3_1_d("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_4.png");

    QPixmap case5_1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_4.png");
    QPixmap case5_1_c("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_3.png");
    QPixmap case5_1_s("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_2.png");

    QPixmap def("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_sx/es1_1.png");

    //EXERCISE 3

    QPixmap case1_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_2.png"); //vai in centro prendi oggetto


    QPixmap case2_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_3.png"); // sx
    QPixmap case2_3_d("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_6.png");
    QPixmap case2_3_c("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_2.png");

    QPixmap case3_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_4.png"); // rest
    QPixmap case3_3_d("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_7.png");
    QPixmap case3_3_c("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_1.png");

    QPixmap case4_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_5.png"); // sx
    QPixmap case4_3_d("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_8.png");
    QPixmap case4_3_c("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_2.png");

    QPixmap case5_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_6.png"); // dx
    QPixmap case5_3_s("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_3.png");
    QPixmap case5_3_c("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_2.png");

    QPixmap case6_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_7.png"); // rest
    QPixmap case6_3_s("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_4.png"); // rest
    QPixmap case6_3_c("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_1.png"); // rest

    QPixmap case7_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_8.png"); // dx
    QPixmap case7_3_s("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_5.png");
    QPixmap case7_3_c("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_2.png");

    QPixmap case8_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_2.png.jpg"); // centro

    QPixmap case9_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_sx/es3_1.png"); // rest


    //EXER 6 IMAGES

    QPixmap def_6("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es6_sx/es6_1.png");

    QPixmap case2_6("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es6_sx/es6_2.png");

    //EXER 5 IMAGES
    QPixmap def_5("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es5_sx/es5_1.png");

    QPixmap case2_5("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es5_sx/es5_2.png");


    switch (dati::command_exercise_pp) {

    //ESERCIZIO REACHING NEL PIANO SENZA OGGETTI

    case 1 :
      qDebug()<< dati::command_task_pp;
      switch (dati::command_task_pp) {

      case 100: // SCHERMATA ESERCIZIO
        // mostro foto dell'esercizio 1
        ui->label_img-> setText("Iniziamo esercizio di \nraggiungimento dei punti. \nPremere OK per iniziare.");

        break;

      case 99:
        ui->label_img->setPixmap(case99);

        qDebug()<< "case99";
        break;
      case 0:
        ui->label_img->setText("Attendi che AGREE\nposizioni la mano in \nposizione di riposo");
        break;
      case 1:
        //prova esempio controllo colonne
   if(point1ses.at(1)<11){
        ui->label_img->setPixmap(case1_1);}
else if(point1ses.at(1)>=12 && point1ses.at(1)<20) {
     ui->label_img->setPixmap(case1_1_c);
   }
   else if(point1ses.at(1)>=20 && point1ses.at(1)<30) {
     ui->label_img->setPixmap(case1_1_d);
   }
        qDebug()<< "case1";
        break;

      case 3:

        if(point2ses.at(1)<11){
             ui->label_img->setPixmap(case3_1_s);}
     else if(point2ses.at(1)>=12 && point2ses.at(1)<20) {
          ui->label_img->setPixmap(case3_1);
        }
        else if(point2ses.at(1)>=20 && point2ses.at(1)<30) {
          ui->label_img->setPixmap(case3_1_d);
        }

        qDebug()<< "case3";
        break;

      case 5:

        if(point3ses.at(1)<11){
             ui->label_img->setPixmap(case5_1_s);}
     else if(point3ses.at(1)>=12 && point3ses.at(1)<20) {
          ui->label_img->setPixmap(case5_1_c);
        }
        else if(point3ses.at(1)>=20 && point3ses.at(1)<30) {
       ui->label_img->setPixmap(case5_1);
        }

        qDebug()<< "case5";
        break;

      case 102: //FEEDBACK
        ui->label_img->setPixmap(feedback_happy);

        break;

      default:
        ui->label_img->setPixmap(def);

        qDebug()<< "casedef";
        break;



      }   // end switch task
      break; //break exer 1


      // ESERCIZIO REACHING NEL PIANO CON OGGETTI
    case 3:
      qDebug()<< dati::command_task_pp;
      switch(dati::command_task_pp) {

      case 100: // SCHERMATA ESERCIZIO
        // mostro foto dell'esercizio 1
        ui->label_img-> setText("Iniziamo esercizio di \n\nraggiungimento punti con oggetto. \n\nPremere OK per iniziare.");
        ui->pushButton_ok->setEnabled(true);
        break;

      case 0:
        ui->label_img->setText("Attendi che AGREE\n\nposizioni la mano in Rest");
        ui->pushButton_ok->setEnabled(false);
        break;

      case 101: // POSIZIONAMENTO OGGETTO
        ui->label_img->setText("Terapista, posiziona l'oggetto \n\nsul punto del pad illuminato.\n\nQuindi premi OK");
        ui->pushButton_ok->setEnabled(true);
        break;
      case 99:
        ui->label_img->setPixmap(case99);

        ui->pushButton_ok->setEnabled(false);
        qDebug()<< "case99";
        break;



      case 1:
        ui->label_img->setPixmap(case1_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "case1_3";
        break;


      case 2: //sx
        ui->pushButton_ok->setEnabled(false);
        if(point1ses.at(1)<11){

          ui->label_img->setPixmap(case2_3);
        }
        else if(point1ses.at(1)>=11 && point1ses.at(1)<20) {
          ui->label_img->setPixmap(case2_3_c);
        }
        else if(point1ses.at(1)>=20) {
          ui->label_img->setPixmap(case2_3_d);
        }



        qDebug()<< "case2_3";
        break;


      case 3 : //rest
        ui->pushButton_ok->setEnabled(false);
        if(point1ses.at(1)<11){
        ui->label_img->setPixmap(case3_3);
        }
        else if (point1ses.at(1)>=11 && point1ses.at(1)<20) {
       ui->label_img->setPixmap(case3_3_c);

        }
        else if(point1ses.at(1)>=20) {
          ui->label_img->setPixmap(case3_3_d);

        }



        break;

      case 4: //sx
        if(point1ses.at(1)<11) {
          ui->label_img->setPixmap(case4_3);
        }
        else if(point1ses.at(1)>=11 && point1ses.at(1)<20) {
          ui->label_img->setPixmap(case4_3_c);
        }
        else if(point1ses.at(1)>=20) {
          ui->label_img->setPixmap(case4_3_d);
        }

        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "case4_3";
        break;

      case 5: //dx
        ui->pushButton_ok->setEnabled(false);
        if(point2ses.at(1)>=20){
        ui->label_img->setPixmap(case5_3);
        }
        else if (point2ses.at(1)>=11 && point2ses.at(1)<20) {
          ui->label_img->setPixmap(case5_3_c);
        }
        else if(point2ses.at(1)<11) {
          ui->label_img->setPixmap(case5_3_s);
        }


        qDebug()<< "case5_3";
        break;

      case 6: //rest
        ui->pushButton_ok->setEnabled(false);
        if(point2.at(1)>=20) {

          ui->label_img->setPixmap(case6_3);
        }
        else if(point2.at(1)<11) {
          ui->label_img->setPixmap(case6_3_s);
        }
        else if(point2.at(1)>=11 && point2.at(1)<20) {
          ui->label_img->setPixmap(case6_3_c);
        }


        qDebug()<< "case6_3";
        break;

      case 7: //dx
                ui->pushButton_ok->setEnabled(false);


        if(point2.at(1)>=20) {

           ui->label_img->setPixmap(case7_3);
        }
        else if(point2.at(1)<11) {
           ui->label_img->setPixmap(case7_3_s);
        }
        else if(point2.at(1)>=11 && point2.at(1)<20) {
          ui->label_img->setPixmap(case7_3_c);
        }

        qDebug()<< "case8_3";
        break;

      case 8: //centro
        ui->pushButton_ok->setEnabled(false);

        ui->label_img->setPixmap(case8_3);


        qDebug()<< "case9_3";
        break;

      case 9: //rest
        ui->label_img->setPixmap(case9_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "case9_3";
        break;

      case 102: // FEEDBACK
        ui->label_img->setPixmap(feedback_happy);

        ui->pushButton_ok->setEnabled(false);
        break;

      default:
        ui->label_img->setPixmap(case2_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "casedef";
        break;
      }
      break;

      // ESERICZIO MANO ALLA BOCCA CON OGGETTO
    case 6:
      qDebug()<< dati::command_task_pp;
      switch(dati::command_task_pp) {

      case 100: // SCHERMATA ESERCIZIO
        // mostro foto dell'esercizio 1
        ui->label_img-> setText("Iniziamo esercizio\n\nMano alla bocca con oggetto.\n\nPremere OK per iniziare.");
        ui->pushButton_ok->setEnabled(true);
        break;
      case 101: //POSIZIONAMENO OGGETTO
        ui->label_img-> setText("Terapista aggancia l'oggetto \n\n alla mano del paziente.\n\nQuindi premi OK");
        ui->pushButton_ok->setEnabled(true);

        break;
      case 99:
        ui->label_img->setPixmap(case99);

        qDebug()<< "case99";
        break;

      case 0:
        ui->label_img->setText("Attendi che AGREE\n\nposizioni la mano in Rest");
        ui->pushButton_ok->setEnabled(false);
        break;




      case 1:
        ui->label_img->setPixmap(case2_6);

        qDebug()<< "case2_6";
        ui->pushButton_ok->setEnabled(false);
        break;

      case 2:
        ui->label_img->setPixmap(def_6);

        qDebug()<< "case2_6";
        ui->pushButton_ok->setEnabled(false);
        break;

      case 102: //FEEDBACK
        ui->label_img->setPixmap(feedback_happy);

        ui->pushButton_ok->setEnabled(false);
        break;

      default:
        ui->label_img->setPixmap(def_6);

        qDebug()<< "casedef";
        ui->pushButton_ok->setEnabled(false);
        break;




      }
      break;


      // ESERICZIO MANO ALLA BOCCA SENZA OGGETTO
    case 5:
      qDebug()<< dati::command_task_pp;
      switch(dati::command_task_pp) {

      case 100: // SCHERMATA ESERCIZIO
        // mostro foto dell'esercizio 1
        ui->label_img-> setText("Iniziamo esercizio \n\nMano alla bocca con oggetto.\n\nPremere OK per iniziare.");
        ui->pushButton_ok->setEnabled(true);
        break;
        //    case 101: //POSIZIONAMENO OGGETTO
        //      ui->label_img-> setText("Terapista aggancia l'oggetto \n\nalla mano del paziente.\n\nQuindi premi OK");
        //      ui->pushButton_ok->setEnabled(true);

        //     break;
      case 99:
        ui->label_img->setPixmap(case99);

        qDebug()<< "case99";
        break;

      case 0:
        ui->label_img->setText("Attendi che AGREE\n\nposizioni la mano in Rest");
        ui->pushButton_ok->setEnabled(false);
        break;




      case 1:
        ui->label_img->setPixmap(case2_5);

        // qDebug()<< "case2_6";
        ui->pushButton_ok->setEnabled(false);
        break;

      case 2:
        ui->label_img->setPixmap(def_5);

        //  qDebug()<< "case2_6";
        ui->pushButton_ok->setEnabled(false);
        break;

      case 102: //FEEDBACK
        ui->label_img->setPixmap(feedback_happy);

        ui->pushButton_ok->setEnabled(false);
        break;

      default:
        ui->label_img->setPixmap(def_5);

        //    qDebug()<< "casedef";
        ui->pushButton_ok->setEnabled(false);
        break;

      }
      break;

      //EXERGAMES FRUIT

    case 9:
      switch(dati::command_task_pp) {
      case 199:
        ui->label_img->setText(istr199);
        ui->pushButton_salvascore->setVisible(true);
        break;

      case 100:
        ui->label_img-> setText("Iniziamo exergames \n\nMacedonia.\n\nPremere OK per iniziare.\n\nTerminata la sessioni chiudi il gioco e\n\npremi Salva Punteggio.");
        ui->pushButton_es_libero->setVisible(true);
        break;
      }
      break;


      //    // ELEVAZIONE LATERALE CON OGGETTO
      //  case 7 :
      //    qDebug()<< dati::command_task_pp;
      //    switch(dati::command_task_pp) {
      //    case 99:
      //      ui->label_img->setPixmap(case99);

      //      qDebug()<< "case99";
      //      ui->pushButton_ok->setEnabled(false);
      //      break;

      //    case 1:
      //      ui->label_img->setPixmap(case2_7);
      //
      //      ui->pushButton_ok->setEnabled(false);
      //      qDebug()<< "case2_7";
      //      break;

      //    case 102: //FEEDBACK PAZIENTE
      //      ui->label_img->setPixmap(feedback_happy);

      //      ui->pushButton_ok->setEnabled(false);
      //      break;

      //    default:
      //      ui->label_img->setPixmap(def_7);

      //      ui->pushButton_ok->setEnabled(false);
      //      qDebug()<< "casedef";
      //      break;

      //    }
      //   break;

    } // end switch exer

    qDebug()<< "sono nella funzione next_img";




  }
  else if(dati::lato=="1") {


    QPixmap feedback_happy("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/smile.jpeg");
    //EXERCISE 1
    QPixmap case1_1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_dx/es1_2_dx.png");

    QPixmap case3_1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_dx/es1_3_dx.png");

    QPixmap case5_1("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_dx/es1_4_dx.png");

    QPixmap def("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es1_dx/es1_1_dx.png");

    //EXERCISE 3

    QPixmap case1_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_dx/es3_2_dx.png"); //vai in centro prendi oggetto


    QPixmap case2_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_dx/es3_3_dx.png"); // dx


    QPixmap case3_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_dx/es3_4_dx.png"); // rest


    QPixmap case4_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_dx/es3_5_dx.png"); // dx

    QPixmap case5_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_dx/es3_6_dx.png"); // sx

    QPixmap case6_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_dx/es3_7_dx.png"); // rest

    QPixmap case7_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_dx/es3_8_dx.png"); // sx

    QPixmap case8_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_dx/es3_2.png.jpg"); // centro

    QPixmap case9_3("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es3_dx/es3_1.png"); // rest

    //EXER 6 IMAGES

    QPixmap def_6("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es6_dx/es6_1_dx.png");

    QPixmap case2_6("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es6_dx/es6_2_dx.png");

    //EXER 5 IMAGES
    QPixmap def_5("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es5_dx/es5_1_dx.png");

    QPixmap case2_5("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ESERCIZI_AGREE/es5_dx/es5_2_dx.png");
    switch (dati::command_exercise_pp) {

    //ESERCIZIO REACHING NEL PIANO SENZA OGGETTI

    case 1 :
      qDebug()<< dati::command_task_pp;
      switch (dati::command_task_pp) {

      case 100: // SCHERMATA ESERCIZIO
        // mostro foto dell'esercizio 1
        ui->label_img-> setText("Iniziamo esercizio di \nraggiungimento dei punti. \nPremere OK per iniziare.");

        break;

      case 99:
        ui->label_img->setPixmap(case99);

        qDebug()<< "case99";
        break;
      case 0:
        ui->label_img->setText("Attendi che AGREE\nposizioni la mano in \nposizione di riposo");
        break;
      case 1:
        ui->label_img->setPixmap(case1_1);

        qDebug()<< "case1";
        break;

      case 3:
        ui->label_img->setPixmap(case3_1);

        qDebug()<< "case3";
        break;

      case 5:
        ui->label_img->setPixmap(case5_1);

        qDebug()<< "case5";
        break;

      case 102: //FEEDBACK
        ui->label_img->setPixmap(feedback_happy);

        break;

      default:
        ui->label_img->setPixmap(def);

        qDebug()<< "casedef";
        break;



      }   // end switch task
      break; //break exer 1


      // ESERCIZIO REACHING NEL PIANO CON OGGETTI
    case 3:
      qDebug()<< dati::command_task_pp;
      switch(dati::command_task_pp) {

      case 100: // SCHERMATA ESERCIZIO
        // mostro foto dell'esercizio 1
        ui->label_img-> setText("Iniziamo esercizio di \n\nraggiungimento punti con oggetto. \n\nPremere OK per iniziare.");
        ui->pushButton_ok->setEnabled(true);
        break;

      case 0:
        ui->label_img->setText("Attendi che AGREE\n\nposizioni la mano in Rest");
        ui->pushButton_ok->setEnabled(false);
        break;

      case 101: // POSIZIONAMENTO OGGETTO
        ui->label_img->setText("Terapista, posiziona l'oggetto \n\nsul punto del pad illuminato.\n\nQuindi premi OK");
        ui->pushButton_ok->setEnabled(true);
        break;
      case 99:
        ui->label_img->setPixmap(case99);

        ui->pushButton_ok->setEnabled(false);
        qDebug()<< "case99";
        break;



      case 1:
        ui->label_img->setPixmap(case1_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "case1_3";
        break;


      case 2:
        ui->label_img->setPixmap(case2_3);
        ui->pushButton_ok->setEnabled(false);


        qDebug()<< "case2_3";
        break;


      case 3 :
        ui->label_img->setPixmap(case3_3);
        ui->pushButton_ok->setEnabled(false);

        break;

      case 4:
        ui->label_img->setPixmap(case4_3);
        ui->pushButton_ok->setEnabled(false);


        qDebug()<< "case4_3";
        break;

      case 5:
        ui->label_img->setPixmap(case5_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "case5_3";
        break;

      case 6:
        ui->label_img->setPixmap(case6_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "case6_3";
        break;

      case 7:
        ui->label_img->setPixmap(case7_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "case8_3";
        break;

      case 8:
        ui->label_img->setPixmap(case8_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "case9_3";
        break;

      case 9:
        ui->label_img->setPixmap(case9_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "case9_3";
        break;

      case 102: // FEEDBACK
        ui->label_img->setPixmap(feedback_happy);

        ui->pushButton_ok->setEnabled(false);
        break;

      default:
        ui->label_img->setPixmap(case2_3);
        ui->pushButton_ok->setEnabled(false);

        qDebug()<< "casedef";
        break;
      }
      break;

      // ESERICZIO MANO ALLA BOCCA CON OGGETTO
    case 6:
      qDebug()<< dati::command_task_pp;
      switch(dati::command_task_pp) {

      case 100: // SCHERMATA ESERCIZIO
        // mostro foto dell'esercizio 1
        ui->label_img-> setText("Iniziamo esercizio\n\nMano alla bocca con oggetto.\n\nPremere OK per iniziare.");
        ui->pushButton_ok->setEnabled(true);
        break;
      case 101: //POSIZIONAMENO OGGETTO
        ui->label_img-> setText("Terapista aggancia l'oggetto \n\n alla mano del paziente.\n\nQuindi premi OK");
        ui->pushButton_ok->setEnabled(true);

        break;
      case 99:
        ui->label_img->setPixmap(case99);

        qDebug()<< "case99";
        break;

      case 0:
        ui->label_img->setText("Attendi che AGREE\n\nposizioni la mano in Rest");
        ui->pushButton_ok->setEnabled(false);
        break;




      case 1:
        ui->label_img->setPixmap(case2_6);

        qDebug()<< "case2_6";
        ui->pushButton_ok->setEnabled(false);
        break;

      case 2:
        ui->label_img->setPixmap(def_6);

        qDebug()<< "case2_6";
        ui->pushButton_ok->setEnabled(false);
        break;

      case 102: //FEEDBACK
        ui->label_img->setPixmap(feedback_happy);

        ui->pushButton_ok->setEnabled(false);
        break;

      default:
        ui->label_img->setPixmap(def_6);

        qDebug()<< "casedef";
        ui->pushButton_ok->setEnabled(false);
        break;




      }
      break;


      // ESERICZIO MANO ALLA BOCCA SENZA OGGETTO
    case 5:
      qDebug()<< dati::command_task_pp;
      switch(dati::command_task_pp) {

      case 100: // SCHERMATA ESERCIZIO
        // mostro foto dell'esercizio 1
        ui->label_img-> setText("Iniziamo esercizio \n\nMano alla bocca con oggetto.\n\nPremere OK per iniziare.");
        ui->pushButton_ok->setEnabled(true);
        break;
        //    case 101: //POSIZIONAMENO OGGETTO
        //      ui->label_img-> setText("Terapista aggancia l'oggetto \n\nalla mano del paziente.\n\nQuindi premi OK");
        //      ui->pushButton_ok->setEnabled(true);

        //     break;
      case 99:
        ui->label_img->setPixmap(case99);

        qDebug()<< "case99";
        break;

      case 0:
        ui->label_img->setText("Attendi che AGREE\n\nposizioni la mano in Rest");
        ui->pushButton_ok->setEnabled(false);
        break;




      case 1:
        ui->label_img->setPixmap(case2_5);

        // qDebug()<< "case2_6";
        ui->pushButton_ok->setEnabled(false);
        break;

      case 2:
        ui->label_img->setPixmap(def_5);

        //  qDebug()<< "case2_6";
        ui->pushButton_ok->setEnabled(false);
        break;

      case 102: //FEEDBACK
        ui->label_img->setPixmap(feedback_happy);

        ui->pushButton_ok->setEnabled(false);
        break;

      default:
        ui->label_img->setPixmap(def_5);

        //    qDebug()<< "casedef";
        ui->pushButton_ok->setEnabled(false);
        break;

      }
      break;

      //EXERGAMES FRUIT

    case 9:
      switch(dati::command_task_pp) {
      case 199:
        ui->label_img->setText(istr199);
        ui->pushButton_salvascore->setVisible(true);
        break;

      case 100:
        ui->label_img-> setText("Iniziamo exergames \n\nMacedonia.\n\nPremere OK per iniziare.\n\nTerminata la sessioni chiudi il gioco e\n\npremi Salva Punteggio.");
        ui->pushButton_es_libero->setVisible(true);
        break;
      }
      break;


      //    // ELEVAZIONE LATERALE CON OGGETTO
      //  case 7 :
      //    qDebug()<< dati::command_task_pp;
      //    switch(dati::command_task_pp) {
      //    case 99:
      //      ui->label_img->setPixmap(case99);

      //      qDebug()<< "case99";
      //      ui->pushButton_ok->setEnabled(false);
      //      break;

      //    case 1:
      //      ui->label_img->setPixmap(case2_7);

      //      ui->pushButton_ok->setEnabled(false);
      //      qDebug()<< "case2_7";
      //      break;

      //    case 102: //FEEDBACK PAZIENTE
      //      ui->label_img->setPixmap(feedback_happy);

      //      ui->pushButton_ok->setEnabled(false);
      //      break;

      //    default:
      //      ui->label_img->setPixmap(def_7);

      //      ui->pushButton_ok->setEnabled(false);
      //      qDebug()<< "casedef";
      //      break;

      //    }
      //   break;

    } // end switch exer

    qDebug()<< "sono nella funzione next_img";
  }


  //  QPixmap def_7("/home/alice/Desktop/ex_img1/07/es7_1.JPG");
  //  //QPixmap def_7("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ex_img1/07/es7_1.JPG");
  //  QPixmap case2_7("/home/alice/Desktop/ex_img1/07/es7_2.JPG");
  //  //QPixmap case2_7("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ex_img1/07/es7_2.JPG");


  QPixmap feedback_happy("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/smile.jpeg");




  /**********************          SCORRO LE IMMAGINI DEGLI ESERCIZI FUNZIONE NUOVA             *********************/


}

/**********************        OK BUTTON THERAPY PAGE  *********************/
void paginaprincipale::on_pushButton_ok_clicked()
{
  if(dati::command_old_pp == SC1_READY_TO_START_EXERCISE) {
    dati::status1=SC1_EXERCISE_STARTED;
    msg_status_pp.data = dati::status1;
    status_publisher.publish(msg_status_pp);
  }
  if(dati::command_old_pp ==SC1_OUT_100) {
    dati::status1=SC1_OUT_100;
    msg_status_pp.data = dati::status1;
    status_publisher.publish(msg_status_pp);
  }

}

/**********************  UPDATE COMPENSATION ROS PARAMETER        *********************/
void paginaprincipale::set_comp_param_ses(){

  comp_param = ui->progressBar_comp_ses->value();
  comp_param = comp_param/100;
  comp_forearm = ui->progressBar_comp_avam_ses->value();
  comp_forearm = comp_forearm/100;
  ros::NodeHandle n;
  n.setParam ("/physiological_param/arm_compensation", comp_param);
  n.setParam ("/physiological_param/forearm_compensation", comp_forearm);
  QString comp_s1, comp_avam_s1;
  comp_s1 = QString::number(comp_param);
  comp_avam_s1 = QString::number(comp_forearm);
  QSqlQuery comp_exo_ses;
  comp_exo_ses.prepare("update Parametri_Paziente set compensazione ='"+comp_s1+"', compensazione_avam = '"+comp_avam_s1+"' where Codice_ID = '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
  if(comp_exo_ses.exec()){
    //QMessageBox ::information(this,tr("Salvataggio"),tr(" Dati Salvati Correttamente"));

  }
  else qDebug()<<"non funziona la comp_exo_ses";


}

/**********************  PAUSE EXERCISE EXECUTION IN THERAPY PAGE        *********************/
void paginaprincipale::on_pushButton_3_clicked()
{
  dati::status1 = 1015;

  std_msgs::Int16 msg;
  msg.data = dati::status1;
  ROS_INFO ("%d", msg.data);
  status_publisher.publish(msg);
  QMessageBox ::information(this,tr("PAUSA"),tr("L'esercizio è stato messo in pausa. Se vuoi riprendere la terapia premi il tasto RIPRENDI. L'esercizio ricomincerà dalla prima ripetizione."));


  QMessageBox riprendi;
  riprendi.setText(tr("L'esercizio è stato messo in pausa. Se vuoi riprendere la terapia premi il tasto RIPRENDI. L'esercizio ricomincerà dalla prima ripetizione."));
  QAbstractButton* pButtonYes = riprendi.addButton(tr("RIPRENDI"), QMessageBox::YesRole);
  //QAbstractButton* pButtonNo =  risposta.addButton(tr("No"), QMessageBox::NoRole);
  riprendi.exec();
  if(riprendi.clickedButton()==pButtonYes) {
    dati::status1 = SC1_START_SESSION;

    std_msgs::Int16 msg;
    msg.data = dati::status1;
    ROS_INFO ("%d", msg.data);
    status_publisher.publish(msg);
  }
}


/**********************************************************************************/

/**********************       EVALUATION PAGE     ****************/

/**********************************************************************************/

/**********************  SHOW EVALUATION PDF       *********************/
void paginaprincipale::on_pushButton_pdf_clicked()
{
  //system("xdg-open test_pdf.pdf");
  // system ("xdg-open /home/alice/Desktop/evaluationpdf.pdf");
}

/**********************          CAPIRE SE TOGLIERE                    *********************/
void paginaprincipale::on_pushButton_salvamoduli_clicked()
{ int8_t check = 0;
  ui->tabWidget_2->setCurrentWidget(ui->tab_tutorial);
  dati::modulo_spalla= "0";
  dati::modulo_gomito = "0";
  dati::modulo_polso="0";
  dati::modulo_eeg = "0";
  dati::modulo_emg= "0";
  dati::mano = "0";
  dati::oi = "0";

  if(ui->checkBox_sinistro->isChecked())
  {dati::lato="0" ;
    QPixmap pic7("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/sx/rom_j2_sx.png");
    ui->label_13->setPixmap(pic7);

    QPixmap pic8("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/sx/rom_j5_sx.png");
    ui->label_14->setPixmap(pic8);

    QPixmap pic9("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/sx/rom_j3_sx.png");
    ui->label_15->setPixmap(pic9);

    QPixmap pic10("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/sx/rom_j4_sx.png");
    ui->label_17->setPixmap(pic10);

    QPixmap pic11("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/sx/rom_j1_sx.png");
    ui->label_67->setPixmap(pic11);

  }
  if(ui->checkBox_destro->isChecked())
  { dati::lato = "1";
    QPixmap pic7("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/dx/rom_j2_dx.png");
    ui->label_13->setPixmap(pic7);

    QPixmap pic8("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/dx/rom_j5_dx.png");
    ui->label_14->setPixmap(pic8);

    QPixmap pic9("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/dx/rom_j3_dx.png");
    ui->label_15->setPixmap(pic9);

    QPixmap pic10("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/dx/rom_j4_dx.png");
    ui->label_17->setPixmap(pic10);

    QPixmap pic11("/home/alice/catkin_ws/src/agree_gui/IMG_AGREE/ROM/dx/rom_j1_dx.png");
    ui->label_67->setPixmap(pic11);




  }


  if (ui->checkBox_gomito->isChecked())
  {
    dati::modulo_gomito = "1";
    dati::modulo_spalla = "1";
    dati::oi = "1";
    active_module_spalla = 1;
    active_module_gomito = 1;
    active_module_RF = 0;
    active_module_MAT = 1;

  }

  if (ui->checkBox_polso->isChecked())  {

    dati::modulo_spalla = "1";
    dati::modulo_polso= "1";
    dati::modulo_gomito = "1";
    dati::oi = "1";
    active_module_spalla = 1;
    active_module_gomito = 1;
    active_module_RF = 0;
    active_module_MAT = 1;
    active_module_polso = 1;


  }

  if(ui->checkBox_eeg_2->isChecked())
  {
    dati::modulo_eeg= "1";
    active_module_EEG_EMG=1;


  }
  if(ui->checkBox_emg_2->isChecked())
  {
    dati::modulo_emg= "1";
    active_module_EEG_EMG = 1;


  }
  if(ui->checkBox_MAP_2->isChecked()) //|| (prova == 5))
  {

    if(dati::modulo_polso == "1")
    {
      dati::mano = "1";
      active_module_MAP = 1;

    }


    else if (dati::modulo_polso == "0" ) {

      QMessageBox::StandardButton risposta= QMessageBox::question(this,tr("Attenzione"), tr("Il modulo extra: Mano non può essere attivato se la configurazione dei moduli moduli meccanici non comprende anche il Modulo : Polso. Si desidera modificare la configurazione dei Moduli Meccanici? "));
      if (risposta==QMessageBox::Yes)
      {
        //  flag=6;
        // ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
        ui->tabWidget_2->setCurrentWidget(ui->tab_moduli);
        check = 1;
        qDebug() << "modulo polso stronzissimo";
      }
      else if (risposta==QMessageBox::No) {
        ui->checkBox_MAP_2->setChecked(false);
      }
    }

  }

  if(!(check==1)) {
    QSqlQuery moduli;
    moduli.prepare("update Parametri_Paziente set Lato = '"+dati::lato+"', Modulo_Spalla= '"+dati::modulo_spalla+"', Modulo_gomito = '"+dati::modulo_gomito+"', Modulo_polso = '"+dati::modulo_polso+"',EEG='"+dati::modulo_eeg+"', Oggetti_int='"+dati::oi+"', Mano='"+dati::mano+"', EMG='"+dati::modulo_emg+"' where Codice_ID= '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"'");
    moduli.exec();
    if (moduli.exec())
    { //QMessageBox ::information(this,tr("Salvato"),tr("Configurazione dei Moduli Meccanici ed Extra salvata"));
      ui->tabWidget_2->setCurrentWidget(ui->tab_tutorial);
      active_modules = {active_module_spalla, active_module_gomito, active_module_polso, active_module_MAT, active_module_RF, active_module_EEG_EMG, active_module_MAP, active_module_JOYSTICK, active_module_VOCAL, active_module_IK_ONLINE};
    }
    else {
      QMessageBox ::critical(this,tr("Errore"),tr("moduli"));
      qDebug()<< moduli.lastError();
    }
  }
  QString r1, r2,r3,r4,r5,r6,r7;
  r1 = ui->lineEdit_ex1->placeholderText();
  r2 = ui->lineEdit_ex2->placeholderText();
  r3 = ui->lineEdit_ex3->placeholderText();
  r4 = ui->lineEdit_ex4->placeholderText();
  r5 = ui->lineEdit_ex5->placeholderText();
  r6 = ui->lineEdit_ex6->placeholderText();
  r7= ui->lineEdit_ex7->placeholderText();


  enable_combo();
  enable_combo_recap();
  update_tempo_terapia();
  update_tempo_recap();
  enable_combo_ex();
  enable_combo_ex_recap();
  if (flag == 4) {
    ui->label_recap_controllo->setText(QString("Modalità di controllo utilizzata nella scorsa sessione : %1\n").arg(dati::mood_prec));
    //  ui->label_suggerimento_output->setText(QString("Modalità di controllo suggerita dalla valutazione della precedente sessione : %1").arg(dati::mode_output));



    qDebug()<< "qui";
    if(!(dati::lex1==0))
    {
      ui->checkBox_ex1->setChecked(true);
      dati::flag_ex=0;
      QSqlQuery selezione1;
      selezione1.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex1_prec+"'");
      selezione1.exec();
      if (selezione1.exec()) {

        while(selezione1.next())
        { ui->comboBox_ex1->setCurrentText(selezione1.value(0).toString());
          QString ex1;
          ex1 = selezione1.value(0).toString();
          qDebug()<< ex1;

        }



        r1 = dati::rip1_prec;
        ui->lineEdit_ex1->setText(r1);
        qDebug()<< r1;
        if(dati::ogg1_prec =="1") {
          ui->comboBox_oi_es1->setCurrentText("Bicchiere");
        }
        else if(dati::ogg1_prec == "2") {
          ui->comboBox_oi_es1->setCurrentText("Borraccia");
        }
        else if(dati::ogg1_prec == "3") {
          ui->comboBox_oi_es1->setCurrentText("Tazza");
        }


      }

    }
    else {
      ui->checkBox_ex1->setChecked(false);
    }
    if(!(dati::lex2==0))
    {
      ui->checkBox_ex2->setChecked(true);
      dati::flag_ex = 1;
      QSqlQuery selezione2;
      selezione2.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex2_prec+"'");
      selezione2.exec();
      if (selezione2.exec()) {

        while(selezione2.next())
        { ui->comboBox_ex2->setCurrentText(selezione2.value(0).toString());
          QString ex2;
          ex2 = selezione2.value(0).toString();
          qDebug()<< ex2;
        }


        r2 = dati::rip2_prec;
        ui->lineEdit_ex2->setText(r2);
        qDebug()<<r2;
        if(dati::ogg2_prec =="1") {
          ui->comboBox_oi_es2->setCurrentText("Bicchiere");
        }
        else if(dati::ogg2_prec == "2") {
          ui->comboBox_oi_es2->setCurrentText("Borraccia");
        }
        else if(dati::ogg2_prec == "3") {
          ui->comboBox_oi_es2->setCurrentText("Tazza");
        }

      }
    }
    else {
      ui->checkBox_ex2->setChecked(false);
    }

    if(!(dati::lex3==0))
    {
      ui->checkBox_ex3->setChecked(true);
      dati::flag_ex=2;
      QSqlQuery selezione3;
      selezione3.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex3_prec+"'");
      selezione3.exec();
      if (selezione3.exec()) {

        while(selezione3.next())
        { ui->comboBox_ex3->setCurrentText(selezione3.value(0).toString());
          QString ex3;
          ex3 = selezione3.value(0).toString();
          qDebug()<< ex3;
        }


        r3 = dati::rip3_prec;
        qDebug()<<r3;
        if(dati::ogg3_prec =="1") {
          ui->comboBox_oi_es3->setCurrentText("Bicchiere");
        }
        else if(dati::ogg3_prec == "2") {
          ui->comboBox_oi_es3->setCurrentText("Borraccia");
        }
        else if(dati::ogg3_prec == "3") {
          ui->comboBox_oi_es3->setCurrentText("Tazza");
        }


        ui->lineEdit_ex3->setText(r3);

      }
    }
    else {
      ui->checkBox_ex3->setChecked(false);
    }
    if(!(dati::lex4==0))
    {
      ui->checkBox_ex4->setChecked(true);
      dati::flag_ex=3;
      QSqlQuery selezione4;
      selezione4.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex4_prec+"'");
      selezione4.exec();
      if (selezione4.exec()){

        while(selezione4.next())
        { ui->comboBox_ex4->setCurrentText(selezione4.value(0).toString());
          QString ex4;
          ex4 = selezione4.value(0).toString();
          qDebug()<< ex4;
        }


        r4 = dati::rip4_prec;
        ui->lineEdit_ex4->setText(r4);
        qDebug()<< r4;
        if(dati::ogg4_prec =="1") {
          ui->comboBox_oi_es4->setCurrentText("Bicchiere");
        }
        else if(dati::ogg4_prec == "2") {
          ui->comboBox_oi_es4->setCurrentText("Borraccia");
        }
        else if(dati::ogg4_prec == "3") {
          ui->comboBox_oi_es4->setCurrentText("Tazza");
        }


      }
    }
    else {
      ui->checkBox_ex4->setChecked(false);
    }
    if(!(dati::lex5==0))
    {
      ui->checkBox_ex5->setChecked(true);
      dati::flag_ex=4;
      QSqlQuery selezione5;
      selezione5.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex5_prec+"'");
      selezione5.exec();
      if (selezione5.exec()) {

        while(selezione5.next())
        { ui->comboBox_ex5->setCurrentText(selezione5.value(0).toString());
          QString ex5;
          ex5 = selezione5.value(0).toString();
          qDebug()<< ex5;
        }


        r5 = dati::rip5_prec;
        ui->lineEdit_ex5->setText(r5);
        qDebug()<< r5;
        if(dati::ogg5_prec =="1") {
          ui->comboBox_oi_es5->setCurrentText("Bicchiere");
        }
        else if(dati::ogg5_prec == "2") {
          ui->comboBox_oi_es5->setCurrentText("Borraccia");
        }
        else if(dati::ogg5_prec == "3") {
          ui->comboBox_oi_es5->setCurrentText("Tazza");
        }


      }
    }
    else {
      ui->checkBox_ex5->setChecked(false);
    }
    if(!(dati::lex6==0))
    {
      ui->checkBox_ex6->setChecked(true);
      dati::flag_ex=5;
      QSqlQuery selezione6;
      selezione6.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex6_prec+"'");
      selezione6.exec();
      if (selezione6.exec()){

        while(selezione6.next())
        { ui->comboBox_ex6->setCurrentText(selezione6.value(0).toString());
          QString ex6;
          ex6 = selezione6.value(0).toString();
          qDebug()<< ex6;

        }

        r6 = dati::rip6_prec;
        ui->lineEdit_ex6->setText(r6);
        qDebug()<< r6;
        if(dati::ogg6_prec =="1") {
          ui->comboBox_oi_es6->setCurrentText("Bicchiere");
        }
        else if(dati::ogg6_prec == "2") {
          ui->comboBox_oi_es6->setCurrentText("Borraccia");
        }
        else if(dati::ogg6_prec == "3") {
          ui->comboBox_oi_es6->setCurrentText("Tazza");
        }


      }
    }
    else {
      ui->checkBox_ex6->setChecked(false);
    }
    if(!(dati::lex7==0))
    {
      ui->checkBox_7->setChecked(true);
      dati::flag_ex=6;
      QSqlQuery selezione7;
      selezione7.prepare("select Ex from Esercizi where Num_ex ='"+dati::ex7_prec+"'");
      selezione7.exec();
      if (selezione7.exec()) {

        while(selezione7.next())
        { ui->comboBox_ex7->setCurrentText(selezione7.value(0).toString());
          QString ex7;
          ex7 = selezione7.value(0).toString();
          qDebug()<< ex7;

        }



        r7 = dati::rip7_prec;
        ui->lineEdit_ex7->setText(r7);
        qDebug()<< r7;
        if(dati::ogg7_prec =="1") {
          ui->comboBox_oi_es7->setCurrentText("Bicchiere");
        }
        else if(dati::ogg7_prec == "2") {
          ui->comboBox_oi_es7->setCurrentText("Borraccia");
        }
        else if(dati::ogg7_prec == "3") {
          ui->comboBox_oi_es7->setCurrentText("Tazza");
        }



      }
    }
    else {
      ui->checkBox_7->setChecked(false);
    }
    qDebug()<<r1;
    qDebug()<< r2;
    qDebug()<< r3;
    qDebug()<< r4;
    qDebug()<< r5;
    qDebug()<< r6;
    qDebug()<< r7;
    ui->lineEdit_ex1->setText(r1);
    ui->lineEdit_ex2->setText(r2);
    ui->lineEdit_ex3->setText(r3);
    ui->lineEdit_ex4->setText(r4);
    ui->lineEdit_ex5->setText(r5);
    ui->lineEdit_ex6->setText(r6);
    ui->lineEdit_ex7->setText(r7);

  }
  else {
    // ui->tabWidget_2->setCurrentWidget(ui->tab_ex);
    qDebug()<< "fino qui ok";
    r1 = ui->lineEdit_ex1->placeholderText();
    r2 = ui->lineEdit_ex2->placeholderText();
    r3 = ui->lineEdit_ex3->placeholderText();
    r4 = ui->lineEdit_ex4->placeholderText();
    r5 = ui->lineEdit_ex5->placeholderText();
    r6 = ui->lineEdit_ex6->placeholderText();
    r7= ui->lineEdit_ex7->placeholderText();
    ui->lineEdit_ex1->setText(r1);
    ui->lineEdit_ex2->setText(r2);
    ui->lineEdit_ex3->setText(r3);
    ui->lineEdit_ex4->setText(r4);
    ui->lineEdit_ex5->setText(r5);
    ui->lineEdit_ex6->setText(r6);
    ui->lineEdit_ex7->setText(r7);
  }


  //recupero dati salvati
  QSqlQuery conf_moduli;
  conf_moduli.prepare("select Modulo_Spalla, Modulo_gomito, Modulo_polso, EEG, EMG, Mano from Parametri_Paziente where  Codice_ID= '"+dati::ind+"' and Data_acquisizione = '"+dati::data1+"' order by Data_acquisizione desc limit 1");
  if(conf_moduli.exec()){
  //  qDebug()<< "ho eseguito la query";

    while(conf_moduli.next()) {
      TutInfo curr;
      VestInfo curr1;
      QString spalla, gomito, polso, EEG, EMG, Mano;

      spalla = conf_moduli.value(0).toString();
      gomito = conf_moduli.value(1).toString();
      polso = conf_moduli.value(2).toString();
      EEG = conf_moduli.value(3).toString();
      EMG = conf_moduli.value(4).toString();
      Mano = conf_moduli.value(5).toString();
      //QString string1 = "Impostare la lunghezza del braccio del paziente regolando la distanza tra asse 1 e asse 4. ";
      //QString string2 = "Svitare le viti cherchiate in figura, bloccando la testa della vite e svitando il bullone.Successivamente posizionare il giunto 4 (in corrispondenza dell'asse 4) sfilando o infilando la barra di collegamento all'interno della morsa. Ruotare la morsa attorno all'asse della vite soltanto se necessario.";
      //QString string3 = ""
      QStringList istr1 = {"Impostare la lunghezza del braccio del paziente regolando la distanza tra asse 1 e asse 4. ", "Svitare le viti cherchiate in figura, bloccando la testa della vite e svitando il bullone.\nSuccessivamente posizionare il giunto 4 (in corrispondenza dell'asse 4) sfilando o infilando la barra di collegamento all'interno della morsa.\nRuotare la morsa attorno all'asse della vite soltanto se necessario.", "Impostare la lunghezza dell'avambraccio del paziente regolando la distanza tra l'asse 4 e l'attacco del giunto 5. ","Per farlo, svitare le 4 viti ad incasso esagonale mostrate in figura,\nquindi far slittare la barra di aggancio al giunto 5, fino a raggiungere la posizione desiderata.\nIn fine avvitare le 4 viti. "};
      QStringList istr2 = {"Posizionare gli elettrodi sul Deltoide posteriore", "Posizionare gli elettrodi sul deltoide anteriore", "Posizionare gli elettrodi sul deltoide mediale", "Posizionare gli elettrodi sul bicipite", "Accendere il dispositivo utilizzando il tasto on/off.\nPosizionarlo nell'apposito alloggiamento in dotazione in corrispondenza della spalla dell'utente"};
      QStringList istr3 = {"Agganciare il Modulo di Assistenza alla Presa al giunto 5 (Polso) dell'esoscheletro"};
      QStringList istr_vest1 = {"Individuare e definire una posizione confortevole ddel paziente in modo tale che la shiena sia appoggiata allo schienale.", "il giunto 1 (spalla) deve essere almeno allo stesso livello della spalla nel piano orizzontale lungo x, come mostrato in figura.\nVerificare inoltre che l'altezza del giunto 1(spalla) sia tale da evitare il contatto tra la spalla del paziente e il giunto stesso, sia in stasi che in movimento.\nVerificare infine che il sistema di aggancio del polso all'esoscheletro non sia in alcun modo d'ostacolo al movimento di presa della mano,\ne che non provochi sensazione di trazione nella mano del paziente."};
      if (spalla =="1" && gomito == "1" && polso == "1") {
        QString tut1 = "mecc1";
        curr.tut = tut1;
        curr.img = GetImages2(tut1);
        curr.istr = istr1;
        TutInfoMap[tut1] = curr;
        qDebug()<<curr.img.size();
        sel_tut.append(tut1);

        QString vest1 = "vest";
        curr1.vest = vest1;
        curr1.img_v = GetImages3(vest1);
        curr1.istr_vest = istr_vest1;
        VestInfoMap[vest1] = curr1;
        sel_vest.append(vest1);
        qDebug()<<"sel : " <<sel_vest;
        qDebug()<<"size:" << sel_vest.size();


      }
      else if (spalla =="1" && gomito == "1" && polso == "0") {
        QString tut2 = "mecc";
        curr.tut = tut2;
        curr.img = GetImages2(tut2);
        TutInfoMap[tut2] = curr;
        qDebug()<<curr.img.size();
        sel_tut.append(tut2);
        qDebug()<<"sel : " <<sel_tut;
        qDebug()<<"size:" << sel_tut.size();

      }
      if(EEG == "1") {
        QString tut3 = "eeg";
        curr.tut = tut3;
        curr.img = GetImages2(tut3);
        TutInfoMap[tut3] = curr;
        qDebug()<<curr.img.size();
        sel_tut.append(tut3);
        qDebug()<<"sel : " <<sel_tut;
        qDebug()<<"size:" << sel_tut.size();

      }
      if (EMG == "1") {
        QString tut4 = "emg";
        curr.tut = tut4;
        curr.img = GetImages2(tut4);
        curr.istr = istr2;
        TutInfoMap[tut4] = curr;
        qDebug()<<curr.img.size();
        sel_tut.append(tut4);
        qDebug()<<"sel : " <<sel_tut;
        qDebug()<<"size:" << sel_tut.size();
      }
      if(Mano == "1") {
        QString tut5 = "map";
        curr.tut = tut5;
        curr.img = GetImages2(tut5);
        curr.istr = istr3;
        TutInfoMap[tut5] = curr;
        qDebug()<<curr.img.size();
        sel_tut.append(tut5);
        qDebug()<<"sel : " <<sel_tut;
        qDebug()<<"size:" << sel_tut.size();
      }


    }





  }
  /***************         SETTO ROS PARAMETERS CON I MODULI   ******************/
  ros::NodeHandle n;
  n.setParam("/active_modules", active_modules );



}

/**********************       SALVO IN UNA LISTA IMMAGINI PER ESERCIZI                       *********************/
//SALVO TUTTE LE IMMAGINI DEGLI ESERCIZI IN UNA LISTA
QList<QPixmap>GetImages(QString exID) {
  QList<QPixmap> mylist;
  //auto folder("/home/alice/catkin_ws/src/agree_gui/resources/ex_img/" + exID);
  auto folder ("/home/alice/Desktop/ex_img1/" + exID);
  QDir directory(folder);
  QStringList images = directory.entryList(QStringList() << "*.jpg" <<"*.JPG" ,QDir::Files);
  qDebug() << directory;
  qDebug() << "i found" << images.size();
  foreach(QString filename, images) {
    QPixmap pix(folder+ QString("/") + filename);
    mylist.append(pix);
    qDebug()<<mylist;

  }
  return mylist;


}

/**********************************************************************************/

/**********************       EMERGENCE PROCEDURE PAGE     ****************/

/**********************************************************************************/


/**********************       EMERGENCE PROCEDURE  *********************/
void paginaprincipale::on_pushButton_allarme_clicked()
{   //timer->stop();
  timer_rehab->stop();
  //    ui->tabWidget->setCurrentWidget(ui->tab);
  //    ui->stackedWidget->setCurrentWidget(ui->page_3);
  dati::status1 = SC1_EMERGENCY;

  std_msgs::Int16 msg;
  msg.data = dati::status1;
  ROS_INFO ("%d", msg.data);
  status_publisher.publish(msg);
}


/**********************        RESUME THERAPY (emergence procedure page)   *********************/
void paginaprincipale::on_pushButton_riprendi_clicked()
{
  dati::status1=SC1_EMERGENCY_RESET;
  msg_status_pp.data = dati::status1;
  status_publisher.publish(msg_status_pp);
  ui->tabWidget_2->setCurrentWidget(ui->tab_init);


}

/**********************        END THERAPY  (emergence procedure page)  *********************/
void paginaprincipale::on_pushButton_termina_clicked()
{
  dati::status1=1032;
  msg_status_pp.data = dati::status1;
  status_publisher.publish(msg_status_pp);
}

/**********************************************************************************/

/**********************       LOGOUT     ****************/

/**********************************************************************************/


/**********************        LOG OUT  *********************/
void paginaprincipale::on_pushButton_logout_clicked()
{


  QMessageBox logout;
  logout.setText(tr("Si è scelto di effetturare il Log out?"));
  QAbstractButton* pButtonYes = logout.addButton(tr("Conferma"), QMessageBox::YesRole);
  QAbstractButton* pButtonNo =  logout.addButton(tr("No"), QMessageBox::NoRole);
  logout.exec();
  if(logout.clickedButton()==pButtonYes) {

    emit ShowMain();
    accept();
    dati::status1 = SC1_EVALUATION;

    std_msgs::Int16 msg_status;
    msg_status.data = dati::status1;
    ROS_INFO ("%d", msg_status.data);
    status_publisher.publish(msg_status);






  }
  else if (logout.clickedButton()==pButtonNo) {

  }
}


/**********************************************************************************/

/**********************       BACK     ****************/

/**********************************************************************************/


/**********************        BACK FUNCTION  *********************/
void paginaprincipale::on_pushButton_indietro_clicked()
{
  dati::status1=SC1_GOBACK;
  msg_status_pp.data = dati::status1;
  status_publisher.publish(msg_status_pp);

}







void paginaprincipale::on_pushButton_es_libero_clicked()
{
  //manda info exergames


}

void paginaprincipale::on_pushButton_salvascore_clicked()
{
  dati::status1 = SC1_SAVE_SCORE;
  msg_status_pp.data = dati::status1;
  status_publisher.publish(msg_status_pp);
}

void paginaprincipale::on_pushButton_valutazione_clicked()
{  if(flag==3)  {  //PAZIENTE SELEZIONATO
  QSqlQueryModel *model2 = new QSqlQueryModel();
    QSqlQuery elenco_val;
    elenco_val.prepare("select rowid, Data_acquisizione from Parametri_Paziente where Codice_ID = '"+dati::ind+"' ");
    elenco_val.exec();
      model2 -> setQuery(elenco_val);
      ui->tableView_valutazioni->setModel(model2);
      ui->tableView_valutazioni->resizeColumnsToContents();
      ui->pushButton_show_pdf->setEnabled(true);
  }
  else
  {
    QMessageBox ::warning(this,tr("Attenzione"),tr("Selezionare con doppio click il paziente di cui si vogliono visualizzare le valutazioni"));
  }

}

void paginaprincipale::on_pushButton_show_pdf_clicked()
{ if(flag==7) {

  QSqlQuery sel_eval;
    sel_eval.prepare("select path_val from Parametri_Paziente where Data_acquisizione ='"+data_eval+"'");
    sel_eval.exec();
      if(sel_eval.exec()) {

      while(sel_eval.next()) {

        filename_eval = sel_eval.value(0).toString();
        std::string s = filename_eval.toStdString();
        qDebug()<<filename_eval;
        system(("xdg-open " +  s).c_str());

      }
      }
      else {
        qDebug()<<sel_eval.lastError();}
}
  else
  {
    QMessageBox ::warning(this,tr("Attenzione"),tr("Selezionare con doppio click il paziente di cui si vogliono visualizzare le valutazioni"));
  }
//    system("xdg-open test_pdf.pdf");
//    system("xdg-open mozilla.pdf");
}

void paginaprincipale::on_tableView_valutazioni_activated(const QModelIndex &index)
{
  data_eval= ui-> tableView_valutazioni->model()->data(index).toString();
  flag= 7; //data selezionata
  qDebug()<<data_eval;

}

void paginaprincipale::on_radioButton_lenta_clicked()
{
    //setto velocità lenta
  speed = 0.05;
  speeds = "lento";
}

void paginaprincipale::on_radioButton_media_clicked()
{
    speed = 0.1;
    speeds = "medio";
}

void paginaprincipale::on_radioButton_veloce_clicked()
{
    speed = 0.20;
    speeds = "veloce";
}
