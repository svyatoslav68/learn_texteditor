/**************************************************************
***** Файл реализации главного окна приложения ****************
*****       main_window.cpp                    ****************
**************************************************************/
#include <iostream>
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include <QMessageBox>
#include <QTextEdit>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QLayout>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QStringList>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDebug>
#include "version.hpp"
#include "new_text_edit.hpp"
#include "main_window.hpp"
#include "dialog_file.hpp"
#include "dialog_help.hpp"

MainWindow::MainWindow()
{
	setObjectName("MainWindow");
	setWindowTitle("Text editor");
	mdiArea = new QMdiArea(this);
	pushButtonOk = new QPushButton(tr("Ok"), this);
	connect(pushButtonOk, &QPushButton::clicked, this, &QMainWindow::close); 
	pushButtonSave = new QPushButton(tr("Save"), this);
	connect(pushButtonSave, &QPushButton::clicked, this, &MainWindow::onSaveFile);
	pushButtonOpen = new QPushButton(tr("Open"), this);
	connect(pushButtonOpen, &QPushButton::clicked, this, &MainWindow::onOpenFile);
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addWidget(pushButtonOpen);
	bottomLayout->addWidget(pushButtonSave);
	bottomLayout->addStretch();
	bottomLayout->addWidget(pushButtonOk);
	textEditMain = new TNewTextEdit(this);
	textEditMain->setObjectName("textEditMain");
	connect(textEditMain, &TNewTextEdit::signalOpenFile, this, &MainWindow::onOpenFile);
	connect(textEditMain, &TNewTextEdit::signalSaveFile, this, &MainWindow::onSaveFile);
	mainLayout->addWidget(mdiArea);
	mdiArea->addSubWindow(textEditMain);
	mainLayout->addLayout(bottomLayout);
	centralWidget = new QWidget(this);
	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);
	createActions();
	createMenu();
	// Если вызываю метод из конструктора, то окно добавляется
	//onNewSubWindow();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
	actOpen = new QAction(tr("&Open"), this);
	actOpen->setObjectName("actOpen");
	connect(actOpen, &QAction::triggered, this, &MainWindow::onOpenFile);
	actSave = new QAction(tr("&Save"), this);
	actSave->setObjectName("actSave");
	connect(actSave, &QAction::triggered, this, &MainWindow::onSaveFile);
	actReadOnly = new QAction(tr("Read only"), this);
	actReadOnly->setObjectName("actReadOnly");
	connect(actReadOnly, &QAction::triggered, this, &MainWindow::onReadOnly);
	actPrint = new QAction(tr("&Print"), this);
	actPrint->setObjectName("actPrint");
	connect(actPrint, &QAction::triggered, this, &MainWindow::onPrintFile);
	actExit = new QAction(tr("E&xit"), this);
	actExit->setObjectName("actExit");
	actExit->setShortcut(QKeySequence::Quit);
	connect(actExit, &QAction::triggered, this, &QMainWindow::close);
	actNewSubWindow = new QAction(tr("New subwindow"), this);
	actNewSubWindow->setObjectName("actNewSubWindow");
	connect(actNewSubWindow, &QAction::triggered, this, &MainWindow::onNewSubWindow);
	grpLanguages = new QActionGroup(this);
	actEnglish = new QAction(tr("&English"));
	actEnglish->setObjectName("actEnglish");
	actEnglish->setCheckable("true");
	connect(actEnglish, &QAction::triggered, this, [this](){this->onSelectLanguages(ENGLISH);});
	actRussian = new QAction(tr("&Russian"));
	actRussian->setObjectName("actRussian");
	actRussian->setCheckable("true");
	actRussian->setChecked("true");
	connect(actRussian, &QAction::triggered, this, [this](){this->onSelectLanguages(RUSSIAN);});
	grpLanguages->addAction(actEnglish);
	grpLanguages->addAction(actRussian);
	actViewDark = new QAction(tr("Dark style"));
	actViewDark->setCheckable("true");
	connect(actViewDark, &QAction::triggered, this, [this](){this->onSelectStyle(DARK);});
	actViewLight = new QAction(tr("Light style"));
	actViewLight->setCheckable("true");
	actViewLight->setChecked("true");
	connect(actViewLight, &QAction::triggered, this, [this](){this->onSelectStyle(LIGHT);});
	grpStyles = new QActionGroup(this);
	grpStyles->addAction(actViewLight);
	grpStyles->addAction(actViewDark);
	actHelp = new QAction(tr("Help"), this);
	actHelp->setObjectName("actHelp");
	connect(actHelp, &QAction::triggered, this, &MainWindow::onShowHelp);
	actAboutQt = new QAction(tr("О Qt"), this);
	actAboutQt->setObjectName("actAboutQt");
	connect(actAboutQt, SIGNAL(triggered()), this, SLOT(onAboutQt()));
	actAbout = new QAction(tr("About"), this);
	actAbout->setObjectName("actAbout");
	connect(actAbout, &QAction::triggered, this, [this](){this->onAbout();});
}

void MainWindow::createMenu()
{
	menuFile = menuBar()->addMenu(tr("&File"));
	menuFile->addAction(actOpen);
	menuFile->addAction(actSave);
	menuFile->addAction(actReadOnly);
	menuFile->addAction(actPrint);
	menuFile->addSeparator();
	menuFile->addAction(actNewSubWindow);
	menuFile->addSeparator();
	menuFile->addAction(actExit);
	menuLanguages = menuBar()->addMenu(tr("&Languages"));
	menuLanguages->addAction(actEnglish);
	menuLanguages->addAction(actRussian);
	menuView = menuBar()->addMenu(tr("&View"));
	menuView->addAction(actViewDark);
	menuView->addAction(actViewLight);
	menuHelp = menuBar()->addMenu(tr("&Help"));
	menuHelp->addAction(actHelp);
	menuHelp->addSeparator();
	menuHelp->addAction(actAbout);
	menuHelp->addAction(actAboutQt);
}

void MainWindow::onSelectLanguages(LANGUAGE_INTERFACE language)
{
}

void MainWindow::onAbout()
{
	QMessageBox::information(this, tr("About"), 
				QString("%1 %2").arg(tr("Text editor\nversion")).arg(QString(g_version)));
}

void MainWindow::onAboutQt()
{
	QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::onOpenFile()
{
	DialogFile *dialogOpenFile = new DialogFile(this);
	if (dialogOpenFile->exec() == QDialog::Accepted)
	{
		qDebug() << dialogOpenFile->getFileName();
		QString nameFile = dialogOpenFile->getFileName();
		QFile file(nameFile);
		/* Дальше я все сделал, как  в документации по qt */
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;
		textEditMain->clear();
		QTextStream in(&file);
		while (!in.atEnd()){
			// Считываю по строке и записываю эти строки в QTextEdit
			QString line = in.readLine();
			textEditMain->append(line);
		}
	}
	delete dialogOpenFile;
}

void MainWindow::onSaveFile()
{
	DialogFile *dialogOpenFile = new DialogFile(this);
	if (dialogOpenFile->exec() == QDialog::Accepted)
	{
		QString nameFile = dialogOpenFile->getFileName();
		QFile file(nameFile);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::critical(this, tr("Error"), QString("Ошибка открытия файла %1 на запись").arg(file.fileName()));
			return;
		}
		QTextStream out(&file);
		out << textEditMain->toPlainText();
	}
}


void MainWindow::onReadOnly()
{
	onOpenFile();
	textEditMain->setReadOnly(true);
}

void MainWindow::onSelectStyle(STYLE style)
{
	switch (style){
		case LIGHT:
			this->setStyleSheet("QPushButton  {font: 14 px; background-color: grey;} QMainWindow{background-color:white}");
			break;
		case DARK:
			this->setStyleSheet("QPushButton  {font: bold 14 px; background-color: red;} QMainWindow{background-color:grey}");
			break;
		default:
			;
	}
}

void MainWindow::onShowHelp()
{
	qDebug() << "onShowHelp";
    DialogHelp dialogHelp;// = new Ui::Dialog(this);
    dialogHelp.exec();
}

bool exportToPdf(QString &fileName, QTextDocument *document)
{

}

void MainWindow::onPrintFile()
{
	QPrinter printer;
	QPrintDialog dlg(&printer, this);
	dlg.setWindowTitle("Print");
	if (dlg.exec() != QDialog::Accepted)
		return;
	print(&printer);
}

void MainWindow::print(QPrinter *printer)
{
	QString printStr = textEditMain->toPlainText();
    QChar *list = printStr.data();
	QStringList strlst;
	int line = 0, cursor = 0;
	for (bool getst = true;getst;) {
		int index = printStr.indexOf("\n", cursor); 
		QString s = ""; 
		if (index == -1) {
			getst = false;
			s.append(&list[cursor], printStr.length() - cursor);
		}
		else {
			s.append(&list[cursor], index - cursor);
		}
        cursor = index + 1;
        strlst << s;
    }
	QPainter painter;
	painter.begin(printer);
	int w = painter.window().width();
	int h = painter.window().height();
	int amount = strlst.count();
	QFont font = painter.font();
	QFontMetrics fmetrics(font);
	for (int i = 0; i < amount; i++)
	{
       QPointF pf;
       pf.setX(10);
       pf.setY(line);
       painter.drawText(pf, strlst.at(i));
       line += fmetrics.height();
       if (h - line <= fmetrics.height())
       {
           printer->newPage();
           line = 0;
       }

	}
	painter.end();
}

void MainWindow::onNewSubWindow()
{
	//Здесь ничего не добавляется.
	//Странно, но и не работает qDebug()
	std::cout << "onNewSubWindow" << std::endl;
	mdiArea->addSubWindow(new TNewTextEdit(this));
}
