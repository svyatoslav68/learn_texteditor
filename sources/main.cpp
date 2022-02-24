#include <iostream>
#include <QApplication>
#include <QDebug>
#include "main_window.hpp"

int main(int argc, char** argv)
{
	std::cout << "First release" << std::endl;
	qDebug() << "Proba";
	//std::cout << "version " << g_version << std::endl;
	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
}

