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
        {
            const QMutexLocker lock(&m_num_mtx);
            counter++;
        }
        m_num_queue->push(counter);
        {
            const QMutexLocker lock(main_mutex);
            list_widget->addItem(QString::number(counter));
        }
    } while (!m_die.load());
}

void NumberProducer::enable_generation()
{
    m_is_active.store(true);
    m_is_active_cond.wakeOne();
}

void NumberProducer::disable_generation()
{
    m_is_active.store(false);
    m_is_active_cond.wakeOne();
}

void NumberProducer::kill()
{
    m_die.store(true);
    m_is_active_cond.wakeOne();
}
