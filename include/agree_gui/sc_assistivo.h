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

//namespace agree_gui {


namespace Ui {
class sc_assistivo;
}

class sc_assistivo : public QDialog

{

  Q_OBJECT
  QColor col1{Qt::cyan};


public:
  explicit sc_assistivo(QWidget *parent = nullptr);
  ~sc_assistivo();

  //definisco uno slot pubblico che uso per connettere il timer a una funzione
public slots:
  void myfunction();

private slots:
  void on_pushButton_salva_clicked();



  void on_pushButton_home_clicked();

  void on_pushButton_vocale_clicked();

  void on_pushButton_modifica_clicked();

  void on_pushButton_joy_clicked();

private:
  Ui::sc_assistivo *ui;
 //   QSqlDatabase  mydb3;
  QTimer *timer;
protected:
  virtual void paintEvent(QPaintEvent *event) override;
};


#endif // SC_ASSISTIVO_H
