#include <iostream>
#include <QApplication>
#include "main_window.hpp"

int main(int argc, char** argv)
{
	std::cout << "First release" << std::endl;
	//std::cout << "version " << g_version << std::endl;
	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
}

