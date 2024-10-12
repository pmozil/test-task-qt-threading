#ifndef NUMBERCONSUMER_H
#define NUMBERCONSUMER_H

#include "numberqueue.h"

#include <QList>
#include <QListWidget>
#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
#include <QWidget>

class NumberConsumer : public QThread {
    Q_OBJECT

    QMutex m_num_mtx{};
    int counter{0};
    std::atomic<bool> m_is_active{false};
    std::atomic<bool> m_die{false};
    NumberQueue *m_num_queue;
    QWaitCondition m_is_active_cond;

    QMutex *main_mutex;
    QListWidget *list_widget;

    void m_thread_worker_consume_numbers();

    void run() override;

      public:
          NumberConsumer(NumberQueue *, QListWidget *list_w, QMutex *mtx);

          ~NumberConsumer() = default;

          void enable_consumption()
          {
              m_is_active.store(true);
              m_is_active_cond.wakeOne();
          }
          void disable_consumption()
          {
              m_is_active.store(false);
              m_is_active_cond.wakeOne();
          }

          void kill()
          {
              m_die.store(true);
              m_is_active_cond.wakeOne();
          }
};

#endif // NUMBERPRODUCER_H
