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


namespace Ui {
class sc_assistivo;
}

class sc_assistivo : public QDialog

{

  Q_OBJECT

public:
  explicit sc_assistivo(QWidget *parent = nullptr);
  ~sc_assistivo();


private slots:
  void on_pushButton_salva_clicked();



private:
  Ui::sc_assistivo *ui;
 //   QSqlDatabase  mydb3;

};

#endif // SC_ASSISTIVO_H
