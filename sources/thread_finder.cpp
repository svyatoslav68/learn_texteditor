#include <QDir>
#include "thread_finder.hpp"

ThreadFinder::ThreadFinder(QString dir, QString file, QObject *parent):
	QThread(parent),m_dir(dir), m_file(file), m_toWork(true)
{

}

void ThreadFinder::run()
{
   QStringList dirs = {m_dir};
   for (int i = 0; dirs.count() && m_toWork; ){
	QDir search(dirs.at(i));
	emit writeFoundPath(dirs.at(i));
	search.setFilter(QDir::Hidden | QDir::Dirs | QDir::NoSymLinks);
	QStringList foundDirs = search.entryList();
	int amount = foundDirs.count();
	for (int j = 0; j < amount && m_toWork; j++)
	{
	   QString newPath = dirs.at(i) + foundDirs[j] + "/";
	   if (newPath.indexOf("/.") == -1) dirs << newPath; // Добавляем
														 // новый каталог
														 // для поиска 
	// Не забываем, что есть ссылки на каталоги текущий и возврата уровня: . и ..
	}
	search.setFilter(QDir::Hidden | QDir::Files | QDir::NoSymLinks);
	QStringList foundFiles = search.entryList();
	amount = foundFiles.count();
	for (int j = 0; j < amount && m_toWork; j++){//пока не просмотрены все 
										  		// файлы или пока флаг
										  		// toWork не установлен в
										  		// false
		   QString filename = foundFiles.at(j);
		   if (filename.indexOf(m_file) != -1)
		   {
			   emit findFile(filename);
		   }
		}
		dirs.removeAt(0);
   }
   emit stopedThread();
}
