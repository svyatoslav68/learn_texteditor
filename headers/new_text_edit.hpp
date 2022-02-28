#ifndef NEW_TEXT_EDIT_HPP
#define NEW_TEXT_EDIT_HPP
#include <QTextEdit>

class TNewTextEdit:public QTextEdit
{
	Q_OBJECT
public:
	TNewTextEdit(QWidget *parent = nullptr);
	~TNewTextEdit();
protected:
	void contextMenuEvent (QContextMenuEvent * ); 
	void keyPressEvent ( QKeyEvent * event );
signals:
	void signalOpenFile();
	void signalSaveFile();
};

#endif //NEW_TEXT_EDIT_HPP
