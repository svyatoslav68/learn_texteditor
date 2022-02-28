/*******************************************************************************
******** Заголовочный файл главного окна приложения ****************************
********             main_window.hpp                ****************************
*******************************************************************************/
#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QTextCharFormat>
/*class QMainWindow*/
class QAction;
class QActionGroup;
class QMenu;
class QToolBar;
class QWidget;
class TNewTextEdit;
class QPushButton;
class QComboBox;
class QTextDocument;
class QPrinter;
class QTextCharFormat;

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
	void createToolBar();
	bool exportToPdf(QString &fileName, QTextDocument *document);
	void print(QPrinter *printer);
	QWidget *centralWidget;
	QPushButton *pushButtonOk, *pushButtonSave, *pushButtonOpen;
	QComboBox *comboBoxFonts;
	QComboBox *comboBoxFontsSize;
	QAction *actOpen, *actSave, *actSaveFormatted, *actReadOnly, *actPrint, *actExit;
	QAction *actJustifyLeft, *actJustifyCenter, *actJustifyRight, *actJustifyFill;
	//QAction *font
	QAction *actViewLight, *actViewDark;
	QAction *actCopyFormat, *actSetFormat;
	QAction *actEnglish, *actRussian;
	QAction *actHelp, *actAboutQt, *actAbout;
	TNewTextEdit *textEditMain;
	QActionGroup *grpLanguages, *grpStyles, *grpJustify;
	QToolBar *toolBarFonts, *toolBarJustify;
	QMenu *menuFile, *menuTools, *menuView, *menuHelp, *menuFormatting;
	QTextCharFormat currentCharFormat;
private slots:
	void onSelectLanguages(LANGUAGE_INTERFACE);
	void onSelectStyle(STYLE);
	void onSelectJustify();
	void onCopyFormat();
	void onChangeFont();
	void onOpenFile();
	void onSaveFile(bool format = false);
	void onPrintFile();
	void onReadOnly();
	void onAbout();
	void onAboutQt();
	void onShowHelp();
};

#endif // MAIN_WINDOW_HPP

