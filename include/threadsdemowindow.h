#ifndef THREADSDEMOWINDOW_H
#define THREADSDEMOWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QString>
#include "numberconsumer.h"
#include "numberproducer.h"
#include "numberqueue.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ThreadsDemoWindow;
}
QT_END_NAMESPACE

class ThreadsDemoWindow : public QMainWindow
{
    Q_OBJECT

public:
    ThreadsDemoWindow(QWidget *parent = nullptr);
    ~ThreadsDemoWindow();

private slots:
    void on_thread_1_resume_clicked();

    void on_thread_1_stop_clicked();

    void on_thread_3_resume_clicked();

    void on_thread_3_stop_clicked();

private:
    Ui::ThreadsDemoWindow *ui;
    NumberQueue *m_number_queue{};
    NumberProducer *m_num_producer{};
    NumberConsumer *m_number_consumer{};
    QMutex main_mtx{};
};
#endif // THREADSDEMOWINDOW_H
