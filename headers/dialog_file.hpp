#ifndef DIALOG_FILE_HPP
#define DIALOG_FILE_HPP

#include <QDialog>

class QPushButton;
class QLineEdit;
class QListWidget;
class QListWidgetItem;
class QTreeView;
class QLabel;
class QTextEdit;
class QStandardItemModel;
class QFileSystemModel;
class Controller;

class DialogFile:public QDialog 
{
Q_OBJECT
public:
	DialogFile(QWidget *parent);
	~DialogFile();
	QString getFileName() const;
private:
	QPushButton *pushButtonOk, *pushButtonCancel;
	QPushButton *pushButtonSetCurrentDir, *pushButtonFindFile;
	QLineEdit *lineEditAddress, *lineEditFindFile;
	//QTextEdit *infoText;
	QListWidget *foundFiles;
	QTreeView *treeFileSystem;
	QLabel *labelStatus;
	QFileSystemModel *filesModel;
	Controller *controllerThread;
	//QString currentPath;
private slots:
	void onSetCurrentDir();
	void onFindFile();
	void changStatusLabel(QString);
	void printFindFile(QString, QString);
	void onPathChanged(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif //DIALOG_FILE_HPP
