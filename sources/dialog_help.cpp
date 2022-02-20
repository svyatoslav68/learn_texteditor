#include <QFile>
#include <QDialog>
#include <QTextStream>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include "dialog_help.hpp"

DialogHelp::DialogHelp(QWidget *parent) :
    QDialog(parent)
{
	setWindowTitle("Help information");
	pushButtonOk = new QPushButton(tr("Ok"), this);
	pushButtonOk->setObjectName("pushButtonOk");
	connect(pushButtonOk, &QPushButton::clicked, this, &QDialog::accept);
	labelText = new QLabel(this);
	labelText->setObjectName("labelText");
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(pushButtonOk);
	mainLayout->addWidget(labelText);
	mainLayout->addLayout(bottomLayout);
    QFile file(":/help/help.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString s = stream.readAll();
        file.close();
        // Здесь можно и текст с разметкой загрузить, используя setTextFormat(Qt::RichText)
        labelText->setText(s);
    }
	setLayout(mainLayout);
}

DialogHelp::~DialogHelp()
{
}
