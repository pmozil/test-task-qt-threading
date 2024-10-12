#include "numberproducer.h"

NumberProducer::NumberProducer(NumberQueue *num_q, QListWidget *list_w, QMutex *mtx)
    : QThread(nullptr)
    , m_num_queue{num_q}
    , main_mutex{mtx}
    , list_widget{list_w}
{}

NumberProducer::~NumberProducer()
{
    m_die.store(true);
}

void NumberProducer::run()
{
    m_thread_worker_generate_numbers();
}

void NumberProducer::m_thread_worker_generate_numbers()
{
    do {
        QThread::msleep(100);
        if (!m_is_active.load()) {
            continue;
        }
        {
            QMutexLocker lock(&m_num_mtx);
            counter++;
        }
        m_num_queue->push(counter);
        {
            QMutexLocker lock(main_mutex);
            list_widget->addItem(QString::number(counter));
        }
    } while (!m_die.load());
}
