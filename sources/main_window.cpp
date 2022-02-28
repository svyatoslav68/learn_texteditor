/**************************************************************
***** Файл реализации главного окна приложения ****************
*****       main_window.cpp                    ****************
**************************************************************/
#include <QWidget>
#include <QMainWindow>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QMessageBox>
#include <QTextEdit>
#include <QPushButton>
#include <QIcon>
#include <QComboBox>
//#include <QOverload>
#include <QFile>
#include <QTextStream>
#include <QTextCursor>
#include <QLayout>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QStringList>
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
	connect(textEditMain, &TNewTextEdit::signalSaveFile, this, [this](){this->onSaveFile(false);});
	mainLayout->addWidget(textEditMain);
	mainLayout->addLayout(bottomLayout);
	centralWidget = new QWidget(this);
	centralWidget->setLayout(mainLayout);
	setMinimumSize(600, 400);
	setCentralWidget(centralWidget);
	createActions();
	createMenu();
	createToolBar();
	//currentCharFormat = new QTextCharFormat();
}

MainWindow::~MainWindow()
{
	//delete currentCharFormat;
}

void MainWindow::createActions()
{
	actOpen = new QAction(tr("&Open"), this);
	actOpen->setObjectName("actOpen");
	connect(actOpen, &QAction::triggered, this, &MainWindow::onOpenFile);
	actSave = new QAction(tr("&Save"), this);
	actSave->setObjectName("actSave");
	connect(actSave, &QAction::triggered, this, &MainWindow::onSaveFile);
	actSaveFormatted = new QAction(tr("&Save formatted"), this);
	actSaveFormatted->setObjectName("actSaveFormatted");
	connect(actSaveFormatted, &QAction::triggered, this, [this](){this->onSaveFile(true);});
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
	grpJustify = new QActionGroup(this);
	actJustifyLeft = new QAction(QIcon(":/icons/format-justify-left.png"), tr("Left"), this);
	actJustifyLeft->setCheckable("true");
	connect(actJustifyLeft, &QAction::triggered, this, &MainWindow::onSelectJustify);
	actJustifyCenter = new QAction(QIcon(":/icons/format-justify-center.png"), tr("Center"), this);
	actJustifyCenter->setCheckable("true");
	connect(actJustifyCenter, &QAction::triggered, this, &MainWindow::onSelectJustify);
	actJustifyRight = new QAction(QIcon(":/icons/format-justify-right.png"), tr("Right"), this);
	actJustifyRight->setCheckable("true");
	connect(actJustifyRight, &QAction::triggered, this, &MainWindow::onSelectJustify);
	actJustifyFill = new QAction(QIcon(":/icons/format-justify-fill.png"), tr("Fill"), this);
	actJustifyFill->setCheckable("true");
	connect(actJustifyFill, &QAction::triggered, this, &MainWindow::onSelectJustify);
	grpJustify->addAction(actJustifyLeft);
	grpJustify->addAction(actJustifyCenter);
	grpJustify->addAction(actJustifyRight);
	grpJustify->addAction(actJustifyFill);
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
	actCopyFormat = new QAction(tr("Copy format"));
	actCopyFormat->setObjectName("actCopyFormat");
	connect(actCopyFormat, &QAction::triggered, this, &MainWindow::onCopyFormat);
	actSetFormat = new QAction(tr("Set format"));
	actSetFormat->setObjectName("actSetFormat");
	connect(actSetFormat, &QAction::triggered, this, [this](){this->textEditMain->setCurrentCharFormat(currentCharFormat);});
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
	menuFile->addAction(actSaveFormatted);
	menuFile->addAction(actReadOnly);
	menuFile->addAction(actPrint);
	menuFile->addSeparator();
	menuFile->addAction(actExit);
	menuFormatting = menuBar()->addMenu(tr("&Formatting"));
	menuFormatting->addAction(actCopyFormat);
	menuFormatting->addAction(actSetFormat);
	menuTools = menuBar()->addMenu(tr("&Tools"));
	menuTools->addAction(actEnglish);
	menuTools->addAction(actRussian);
	menuTools->addSeparator();
	menuTools->addAction(actViewDark);
	menuTools->addAction(actViewLight);
	menuView = menuBar()->addMenu(tr("&View"));
	menuView->addAction(actCopyFormat);
	menuView->addAction(actSetFormat);
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

void MainWindow::onSaveFile(bool format)
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
		if (format) {
			out << textEditMain->toHtml();
		}
		else {
			out << textEditMain->toPlainText();
		}
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
    DialogHelp dialogHelp;// = new Ui::Dialog(this);
    dialogHelp.exec();
}

bool exportToPdf(QString &fileName, QTextDocument *document)
{
	return true;
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

void MainWindow::createToolBar()
{
	toolBarFonts = addToolBar(tr("Fonts toolbar"));
	QFontDatabase database;
	comboBoxFontsSize = new QComboBox(this);
	QStringList listSizes;
	listSizes << "10" << "12" << "14" << "16";
	comboBoxFontsSize->addItems(listSizes);
	connect(comboBoxFontsSize, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){this->onChangeFont();});
	comboBoxFonts = new QComboBox(this);
	comboBoxFonts->addItems(database.families());
	connect(comboBoxFonts, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){this->onChangeFont();});
	//comboBoxFonts
	toolBarFonts->addWidget(comboBoxFontsSize);
	toolBarFonts->addWidget(comboBoxFonts);
	toolBarJustify = addToolBar(tr("Justify toolbar"));
	toolBarJustify->addAction(actJustifyLeft);
	toolBarJustify->addAction(actJustifyCenter);
	toolBarJustify->addAction(actJustifyRight);
	toolBarJustify->addAction(actJustifyFill);
}

void MainWindow::onSelectJustify()
{
	QTextCursor selectedText = textEditMain->textCursor();
	if (actJustifyLeft->isChecked()) {
		//qDebug() << "actJustifyLeft";
		textEditMain->setAlignment(Qt::AlignLeft);
	}
	else {
		if (actJustifyRight->isChecked()) {
			//qDebug() << "actJustifyRight";
			textEditMain->setAlignment(Qt::AlignRight);
		}
		else {
			if (actJustifyCenter->isChecked()) {
				//qDebug() << "actJustifyCenter";
				textEditMain->setAlignment(Qt::AlignHCenter);
			}
			else {
				if (actJustifyFill->isChecked()) {
					//qDebug() << "actJustifyFill";
					textEditMain->setAlignment(Qt::AlignJustify);
				}
			}
		}
	}
}

void MainWindow::onChangeFont()
{
	//QTextCharFormat fmt;
	currentCharFormat.setFontPointSize(comboBoxFontsSize->currentText().toInt());
	currentCharFormat.setFontFamily(comboBoxFonts->currentText());
	textEditMain->textCursor().setCharFormat(currentCharFormat);
	textEditMain->setCurrentCharFormat(currentCharFormat);
}

void MainWindow::onCopyFormat()
{
	currentCharFormat = (textEditMain->textCursor().charFormat());
}

