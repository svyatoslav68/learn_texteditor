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
class QMdiSubWindow;
class QMdiArea;
class TNewTextEdit;
class QPushButton;
class QTextDocument;
class QPrinter;

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
	bool exportToPdf(QString &fileName, QTextDocument *document);
	void print(QPrinter *printer);
	QWidget *centralWidget;
	QMdiArea *mdiArea;
	QPushButton *pushButtonOk, *pushButtonSave, *pushButtonOpen;
	QAction *actOpen, *actSave, *actReadOnly, *actPrint, *actExit;
	QAction *actNewSubWindow;
	QAction *actViewLight, *actViewDark;
	QAction *actEnglish, *actRussian;
	QAction *actHelp, *actAboutQt, *actAbout;
	TNewTextEdit *textEditMain;
	QActionGroup *grpLanguages, *grpStyles;
	QMenu *menuFile, *menuLanguages, *menuView, *menuHelp;
private slots:
	void onSelectLanguages(LANGUAGE_INTERFACE);
	void onSelectStyle(STYLE);
	void onNewSubWindow();
	void onOpenFile();
	void onSaveFile();
	void onPrintFile();
	void onReadOnly();
	void onAbout();
	void onAboutQt();
	void onShowHelp();
};

#endif // MAIN_WINDOW_HPP

