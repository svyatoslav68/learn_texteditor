#ifndef CONTROLLER_THREAD_HPP
#define CONTROLLER_THREAD_HPP
#include <QObject>
#include <QSharedPointer>
#include "thread_finder.hpp"
class Controller : public QObject
{
   Q_OBJECT
public:
 explicit Controller(QObject *parent = nullptr);
   ~Controller();
   void startFind(QString dir, QString file);
private:
   QSharedPointer<ThreadFinder>findThread;
private:
   QString currentPath;
signals:
   void changFindPath(QString);     // Сообщаем о новом каталоге поиска и об
                                    // окончании работы
   void genPathOfFile(QString, QString); // Найденный файл для вывода готов
   void newFind();                  // Очистка поля вывода результата
public slots:
   void deleteThread();             // Удаляем поток при завершение работы
   void printCurrentPath(QString);  // Выводим текущий каталог поиска
   void genStringPathFile(QString); // Выводим найденный файл
   void finishThread();             // Информируем о завершении потока
};

#endif // CONTROLLER_THREAD_HPP
