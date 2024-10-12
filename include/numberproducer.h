#ifndef NUMBERPRODUCER_H
#define NUMBERPRODUCER_H

#include <QList>
#include <QListWidget>
#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
#include <QWaitCondition>
#include <QWidget>
#include "numberqueue.h"

class NumberProducer : public QThread
{
    Q_OBJECT

    QMutex m_num_mtx{};
    int counter{0};
    std::atomic<bool> m_is_active{false};
    std::atomic<bool> m_die{false};
    NumberQueue *m_num_queue;
    QWaitCondition m_is_active_cond;

    QMutex *main_mutex;
    QListWidget *list_widget;

    void m_thread_worker_generate_numbers();

    void run() override;

public:
    NumberProducer(NumberQueue *, QListWidget *list_w, QMutex *mtx);

    ~NumberProducer();

    void enable_generation();
    void disable_generation();
    void kill();
};

#endif // NUMBERPRODUCER_H
