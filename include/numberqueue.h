#ifndef NUMBERQUEUE_H
#define NUMBERQUEUE_H

#include <QList>
#include <QListWidget>
#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
#include <QWaitCondition>
#include <QWidget>
#include <vector>

class NumberQueue : public QThread {
    Q_OBJECT

      public:
    static constexpr int max_array_elems{20};

      private:
    QMutex m_num_mtx{};
    QWaitCondition m_buffer_not_empty;
    std::vector<int> m_buffer{};
    std::atomic<bool> m_die{false};

    QMutex *main_mutex;
    QListWidget *list_widget;

    void m_thread_worker_update_list();

    void run() override;

      public:
    NumberQueue(QListWidget *list_w, QMutex *mtx);

    ~NumberQueue();

    int get_number();

    void push(int);

    void kill();
};

#endif // NUMBERPRODUCER_H
