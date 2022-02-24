#include <QPushButton>
#include <QLineEdit>
#include <QTreeView>
#include <QLayout>
//#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QDir>
#include "dialog_file.hpp"

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
	pushButtonSetCurrentDir = new QPushButton(tr("Set current"), this);
	connect(pushButtonSetCurrentDir, &QPushButton::clicked, this, &DialogFile::onSetCurrentDir);
	QHBoxLayout *pathLayout = new QHBoxLayout;
	pathLayout->addWidget(lineEditAddress);
	pathLayout->addStretch();
	pathLayout->addWidget(pushButtonSetCurrentDir);
	QHBoxLayout *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(pushButtonOk);
	bottomLayout->addWidget(pushButtonCancel);
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(pathLayout);
	mainLayout->addWidget(treeFileSystem);
	mainLayout->addLayout(bottomLayout);
	setLayout(mainLayout);
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

