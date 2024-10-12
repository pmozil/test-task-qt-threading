#ifndef NUMBERPRODUCER_H
#define NUMBERPRODUCER_H

#include <QList>
#include <QListWidget>
#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
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

    QMutex *main_mutex;
    QListWidget *list_widget;

    void m_thread_worker_generate_numbers();

    void run() override;

public:
    NumberProducer(NumberQueue *, QListWidget *list_w, QMutex *mtx);

    ~NumberProducer();

    void enable_generation() { m_is_active.store(true); }
    void disable_generation() { m_is_active.store(false); }

    void kill() { m_die.store(true); }
};

#endif // NUMBERPRODUCER_H
