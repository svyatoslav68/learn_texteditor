#ifndef DIALOG_INSERT_CHAR_HPP
#define DIALOG_INSERT_CHAR_HPP

#include <QDialog>
#include <QDateTime>
#include <vector>
class QTableView;
class QPushButton;

class DialogInsertChar:public QDialog 
{
Q_OBJECT
public:
	DialogInsertChar(QWidget *parent = nullptr);
	QChar getResult() const;
private:
	std::vector<QChar> specialChars;
	QPushButton *pushButtonOk, *pushButtonCancel;
	QTableView *tableChars;
};

#endif //DIALOG_INSERT_CHAR_HPP
