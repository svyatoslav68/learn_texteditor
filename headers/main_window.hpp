/*******************************************************************************
******** Заголовочный файл главного окна приложения ****************************
********             main_window.hpp                ****************************
*******************************************************************************/
#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
/*class QMainWindow*/
class QAction;
class QActionGroup;
class QMenu;
class QWidget;
class TNewTextEdit;
class QPushButton;

class MainWindow: public QMainWindow {
Q_OBJECT
public:
	enum LANGUAGE_INTERFACE {ENGLISH, RUSSIAN};
	enum STYLE {LIGHT, DARK};
	MainWindow();
	~MainWindow();
private:
	void createActions();
	void createMenu();
	QWidget *centralWidget;
	QPushButton *pushButtonOk, *pushButtonSave, *pushButtonOpen;
	QAction *actOpen, *actSave, *actReadOnly, *actExit;
	QAction *actViewLight, *actViewDark;
	QAction *actEnglish, *actRussian;
	QAction *actHelp, *actAboutQt, *actAbout;
	TNewTextEdit *textEditMain;
	QActionGroup *grpLanguages, *grpStyles;
	QMenu *menuFile, *menuLanguages, *menuView, *menuHelp;
private slots:
	void onSelectLanguages(LANGUAGE_INTERFACE);
	void onSelectStyle(STYLE);
	void onOpenFile();
	void onSaveFile();
	void onReadOnly();
	void onAbout();
	void onAboutQt();
	void onShowHelp();
};

#endif // MAIN_WINDOW_HPP

