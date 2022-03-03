#include <QLayout>
#include <QTableView>
#include <QPushButton>
#include <QChar>
#include "dialog_insert_char.hpp"

DialogInsertChar::DialogInsertChar(QWidget *parent):QDialog(parent)
{
	setWindowTitle(tr("Select inserting char"));
	tableChars = new QTableView(this);
	pushButtonCancel = new QPushButton(tr("Cancel"), this);
	connect(pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
	pushButtonOk = new QPushButton(tr("Ok"), this);
	connect(pushButtonOk, &QPushButton::clicked, this, &QDialog::accept);
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	QHBoxLayout *bottomLayout = new QHBoxLayout(this);
	bottomLayout->addStretch();
	bottomLayout->addWidget(pushButtonCancel);
	bottomLayout->addWidget(pushButtonOk);
	mainLayout->addWidget(tableChars);
	mainLayout->addLayout(bottomLayout);
}

QChar DialogInsertChar::getResult() const
{
	return QChar();
}
