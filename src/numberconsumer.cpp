#include "numberconsumer.h"

NumberConsumer::NumberConsumer(NumberQueue *num_q, QListWidget *list_w, QMutex *mtx)
    : QThread(nullptr)
    , m_num_queue{num_q}
    , main_mutex{mtx}
    , list_widget{list_w}
{}

void NumberConsumer::run()
{
    m_thread_worker_consume_numbers();
}

void NumberConsumer::m_thread_worker_consume_numbers()
{
    do {
        QThread::msleep(20);
        {
            const QMutexLocker lock(&m_num_mtx);
            while (!m_is_active.load() && !m_die.load())
                m_is_active_cond.wait(&m_num_mtx);
        }
        if (m_die.load()) {
            break;
        }
        if (!m_is_active.load()) {
            continue;
        }
        int num = m_num_queue->get_number();
        {
            QMutexLocker lock(main_mutex);
            list_widget->addItem(QString::number(num));
        }
    } while (!m_die.load());
}
