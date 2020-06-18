/**
 * @file /include/agree_gui/main_window.hpp
 *
 * @brief Qt based gui for agree_gui.
 *
 * @date November 2010
 **/
#ifndef agree_gui_MAIN_WINDOW_H
#define agree_gui_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtWidgets/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include "login.h"
#include "paginaprincipale.h"
//#include "sc_assistivo.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QtSql>
#include <QtDebug>
#include <QFileInfo>

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace agree_gui {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void on_actionAbout_triggered();
	void on_button_connect_clicked(bool check );
	void on_checkbox_use_environment_stateChanged(int state);

    /******************************************
    ** Manual connections
    *******************************************/
    void updateLoggingView(); // no idea why this can't connect automatically

private slots:
    //void on_button_connect_clicked();

private:
	Ui::MainWindowDesign ui;
  QNode qnode;
  paginaprincipale *Paginaprincipale; //quando creo oggetto questo prenda in ingresso anche il puntantore a qnode
  login *Login;
//  sc_assistivo *Sc_assistivo;
};

}  // namespace agree_gui

#endif // agree_gui_MAIN_WINDOW_H
