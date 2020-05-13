#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QFileInfo>

#include "paginaprincipale.h"






//dichiaro delle variabili 'globali' così da poterle usare in tutte le finestre
struct dati {
    static QString username,password,codice_id,ind,Nome, Cognome, Data, NomeP, CognomeP,data1,count,sigla,uservecchio, count_act, modulo_spalla, modulo_gomito, modulo_polso,modulo_spalla_prec, modulo_gomito_prec, modulo_polso_prec, modulo_eeg, modulo_emg, mano, oi, modulo_prec, modulo_eeg_prec, modulo_emg_prec,oi_prec, mano_prec, data_vecchia, modulo_extra, mood, mood_prec,ex1,ex2,ex3,ex4,ex5,ex6,ex7,rip1,rip2,rip3,rip4,rip5,rip6,rip7, rip1_prec, rip2_prec,rip3_prec,rip4_prec,rip5_prec,rip6_prec,rip7_prec, ex1_prec,ex2_prec,ex3_prec,ex4_prec,ex5_prec,ex6_prec,ex7_prec, modulo_prec1;
    static int profilo, password_i, l_eeg_p, l_emg_p, l_m_p, l_oi_p, lex1, lex2,lex3,lex4,lex5,lex6,lex7;
};

namespace Ui {
class login;
}

class login : public QMainWindow
{
  Q_OBJECT

public:
  explicit login(QWidget *parent = nullptr);
  ~login();

private slots:
  void on_pushButton_accedi_clicked();

  void on_pushButton_newrec_clicked();

  void on_pushButton_salva_clicked();

 // void on_pushButton_modifica_clicked();

private:
  Ui::login *ui;
   paginaprincipale *Paginaprincipale; //dichiaro il nome delle finestre a cui accedo dalla mainwindow

   login *Login;



};

#endif // LOGIN_H
