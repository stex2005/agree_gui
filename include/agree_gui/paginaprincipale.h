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
#include <map>
#include <string>
#include <iterator>

#include "matrixwidget.h"


QList<QPixmap > GetImages(QString exID);  // in here we load all images from folder

struct ExInfo{
  QString EX;
  int REP;
  QList<QPixmap> images;
};






namespace Ui {
class paginaprincipale;
}
class QMediaPlayer;
class QVideoWidget;
class paginaprincipale : public QDialog
{
  Q_OBJECT
   std::map<QString,ExInfo>ExInfoMap;

public:
  explicit paginaprincipale(QWidget *parent = nullptr);
  ~paginaprincipale();

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

private:
  Ui::paginaprincipale *ui;
  QSqlDatabase mydb2;



};

#endif // PAGINAPRINCIPALE_H
