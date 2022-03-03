#ifndef THREADFINDER_HPP
#define THREADFINDER_HPP

#include <QObject>
#include <QThread>

class ThreadFinder: public QThread
{
   Q_OBJECT
public:
   explicit ThreadFinder(QString dir, QString file, QObject *parent = nullptr);
   void findStop() {m_toWork = false;} // Команда прекращения работы потока
protected:
   void run();
private:
   QString m_dir;
   QString m_file;
   bool m_toWork;                      // Завершение потока извне
signals:
   void stopedThread();              // Сигнал завершения поиска
   void writeFoundPath(QString);     // Вывод текущего каталога поиска
   void findFile(QString);           // Сообщение о найденном файле

};

#endif // THREADFINDER_HPP

