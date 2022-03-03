#ifndef DIALOGHELP_H
#define DIALOGHELP_H

#include <QDialog>

class QPushButton;
class QLabel;
class DialogHelp : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHelp(QWidget *parent = nullptr);
    ~DialogHelp();

private:
	QLabel *labelText;
	QPushButton *pushButtonOk;
};

#endif // DIALOGHELP_H
