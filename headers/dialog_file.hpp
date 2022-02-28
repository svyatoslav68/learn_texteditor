#ifndef DIALOG_FILE_HPP
#define DIALOG_FILE_HPP

#include <QDialog>

class QPushButton;
class QLineEdit;
class QTreeView;
class QStandardItemModel;
class QFileSystemModel;

class DialogFile:public QDialog 
{
Q_OBJECT
public:
	DialogFile(QWidget *parent);
	~DialogFile();
	QString getFileName() const;
private:
	QPushButton *pushButtonOk, *pushButtonCancel;
	QPushButton *pushButtonSetCurrentDir;
	QLineEdit *lineEditAddress;
	QTreeView *treeFileSystem;
	QFileSystemModel *filesModel;
	//QString currentPath;
private slots:
	void onSetCurrentDir();
};

#endif //DIALOG_FILE_HPP
