#include <iostream>
#include <QPushButton>
#include <QLineEdit>
#include <QTreeView>
#include <QTextEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QLayout>
#include <QIcon>
//#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QDir>
#include "dialog_file.hpp"
#include "thread_finder.hpp"
#include "controller_thread.hpp"

DialogFile::DialogFile(QWidget *parent):QDialog(parent)
{
	setWindowTitle(tr("Select file"));
	setMinimumSize(500,200);
	pushButtonOk = new QPushButton(tr("Ok"), this);
	pushButtonOk->setObjectName("pushButtonOk");
	connect(pushButtonOk, &QPushButton::clicked, this, &QDialog::accept);
	pushButtonCancel = new QPushButton(tr("Cancel"), this);
	pushButtonCancel->setObjectName("pushButtonCancel");
	connect(pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
	filesModel = new QFileSystemModel(this);
	filesModel->setRootPath(QDir::currentPath());
	treeFileSystem = new QTreeView(this);
	treeFileSystem->setModel(filesModel);
	lineEditAddress = new QLineEdit(this);
	lineEditAddress->setObjectName("lineEditAddress");
	lineEditFindFile = new QLineEdit(this);
	lineEditFindFile->setObjectName("lineEditFindFile");
	foundFiles = new QListWidget(this);
	connect(foundFiles, &QListWidget::currentItemChanged, this, &DialogFile::onPathChanged);//[this](QListWidgetItem *current, QListWidgetItem *previous){std::cout << current->text().toStdString() << std::endl;});
	pushButtonSetCurrentDir = new QPushButton(tr("Set current"), this);
	connect(pushButtonSetCurrentDir, &QPushButton::clicked, this, &DialogFile::onSetCurrentDir);
	pushButtonFindFile = new QPushButton(QIcon(":/icons/system-search-symbolic.symbolic.png"), tr("Find"), this);
	pushButtonFindFile->setObjectName("pushButtonFindFile");
	connect(pushButtonFindFile, &QPushButton::clicked, this, &DialogFile::onFindFile);
	labelStatus = new QLabel(this);
	QVBoxLayout *statusBarLayout = new QVBoxLayout;
	statusBarLayout->addWidget(labelStatus);
	QVBoxLayout *setDirLayout = new QVBoxLayout;
	QVBoxLayout *findLayout = new QVBoxLayout;
	QHBoxLayout *pathLayout = new QHBoxLayout;
	setDirLayout->addStretch();
	setDirLayout->addWidget(lineEditAddress);
	setDirLayout->addWidget(pushButtonSetCurrentDir);
	findLayout->addStretch();
	findLayout->addWidget(lineEditFindFile);
	findLayout->addWidget(pushButtonFindFile);
	pathLayout->addLayout(setDirLayout);
	pathLayout->addLayout(findLayout);
	pathLayout->addWidget(foundFiles, 2);
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(pushButtonOk);
	bottomLayout->addWidget(pushButtonCancel);
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(pathLayout);
	mainLayout->addWidget(treeFileSystem);
	mainLayout->addLayout(bottomLayout);
	mainLayout->addLayout(statusBarLayout);
	setLayout(mainLayout);
	controllerThread = new Controller(this);
	connect(controllerThread, SIGNAL(changFindPath(QString)), 
							this, SLOT(changStatusLabel(QString)));
	connect(controllerThread, SIGNAL(genPathOfFile(QString, QString)), 
							this, SLOT(printFindFile(QString, QString)));
	connect(controllerThread, SIGNAL(newFind()), foundFiles, SLOT(clear()));
}

DialogFile::~DialogFile()
{
	delete pushButtonSetCurrentDir;
	delete lineEditAddress;
	delete treeFileSystem;
	delete pushButtonCancel;
	delete pushButtonOk;
}

QString DialogFile::getFileName() const
{
	return filesModel->filePath(treeFileSystem->currentIndex());//+filesModel->fileName(treeFileSystem->currentIndex());
}

void DialogFile::onSetCurrentDir()
{
	auto index = filesModel->setRootPath(lineEditAddress->text());
//	treeFileSystem->reset();
	treeFileSystem->setRootIndex(index);
}

void DialogFile::onFindFile()
{
	foundFiles->clear();
	QString linesearch = lineEditFindFile->text();
	if (linesearch.length() == 0) return;
	controllerThread->startFind("/home/", linesearch);
}

void DialogFile::changStatusLabel(QString line)
{
   labelStatus->setText(line);
}

void DialogFile::printFindFile(QString path, QString str)
{
	lineEditAddress->setText(path);
	auto index = filesModel->setRootPath(path);
	treeFileSystem->setRootIndex(index);
	foundFiles->addItem(path);
}

void DialogFile::onPathChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
	lineEditAddress->setText(current->text());
	onSetCurrentDir();
}
