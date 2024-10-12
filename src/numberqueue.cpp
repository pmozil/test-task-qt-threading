#include "numberqueue.h"

NumberQueue::NumberQueue(QListWidget *list_w, QMutex *mtx)
    : QThread(nullptr), main_mutex{mtx}, list_widget{list_w} {}

NumberQueue::~NumberQueue()
{
    m_die.store(true);
    m_buffer_not_empty.wakeAll();
}

void NumberQueue::kill()
{
    m_die.store(true);
    m_buffer_not_empty.wakeAll();
}

void NumberQueue::push(int new_num) {
    const QMutexLocker lock(&m_num_mtx);
    m_buffer.push_back(new_num);
    if (m_buffer.size() > max_array_elems) {
        m_buffer.erase(m_buffer.begin(), m_buffer.begin() + 1);
    }

    m_buffer_not_empty.wakeOne();
}

int NumberQueue::get_number() {
    {
        const QMutexLocker locker(&m_num_mtx);
        while (m_buffer.empty() && !m_die.load())
            m_buffer_not_empty.wait(&m_num_mtx);
    }

    if (m_die.load()) {
        return 0;
    }

    const QMutexLocker locker(&m_num_mtx);
    int val = m_buffer[m_buffer.size() - 1];
    m_buffer.pop_back();

    return val;
}

void NumberQueue::run() { m_thread_worker_update_list(); }

void NumberQueue::m_thread_worker_update_list() {
    do {
        QThread::msleep(100);
        {
            const QMutexLocker queue_lock(&m_num_mtx);
            const QMutexLocker lock(main_mutex);
            list_widget->clear();
            for (const int val : m_buffer) {
                list_widget->addItem(QString::number(val));
            }
        }
    } while (!m_die.load());
}
