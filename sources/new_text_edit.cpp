#include <QTextEdit>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include "new_text_edit.hpp"

TNewTextEdit::TNewTextEdit(QWidget *parent):QTextEdit(parent)
{

}

TNewTextEdit::~TNewTextEdit()
{

}

void TNewTextEdit::contextMenuEvent (QContextMenuEvent * )
{

}

void TNewTextEdit::keyPressEvent ( QKeyEvent * event )
{
	switch (event->key()) 
	{
		case Qt::Key_S:
			if (event->modifiers() & Qt::ControlModifier)// && Qt::ControlModifier)
			{
				emit signalSaveFile();
			}
			event->accept();
			break;
		case Qt::Key_O:
			if (event->modifiers() & Qt::ControlModifier)// && Qt::ControlModifier)
			{
				emit signalOpenFile();
			}
			event->accept();
			break;
		default:
			QTextEdit::keyPressEvent(event);
	}
}


