#include "threadsdemowindow.h"
#include "./ui_threadsdemowindow.h"

ThreadsDemoWindow::ThreadsDemoWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ThreadsDemoWindow)
{
    ui->setupUi(this);

    ui->thread_1_resume->setEnabled(true);
    ui->thread_1_stop->setEnabled(false);

    ui->thread_3_resume->setEnabled(true);
    ui->thread_3_stop->setEnabled(false);

    m_number_queue = (new NumberQueue(ui->thread_2_number_list, &main_mtx));
    m_num_producer = (new NumberProducer(m_number_queue, ui->thread_1_number_list, &main_mtx));
    m_number_consumer = (new NumberConsumer(m_number_queue, ui->thread_3_number_list, &main_mtx));

    m_number_queue->start();
    m_num_producer->start();
    m_number_consumer->start();
}

ThreadsDemoWindow::~ThreadsDemoWindow()
{
    m_number_queue->kill();

    on_thread_1_stop_clicked();
    m_num_producer->kill();
    m_num_producer->wait();

    on_thread_3_stop_clicked();
    m_number_consumer->kill();
    m_number_consumer->wait();

    m_number_queue->wait();

    delete m_number_consumer;
    delete m_num_producer;
    delete m_number_queue;

    delete ui;
}

void ThreadsDemoWindow::on_thread_1_resume_clicked()
{
    const QMutexLocker lock(&main_mtx);
    m_num_producer->enable_generation();
    ui->thread_1_resume->setEnabled(false);
    ui->thread_1_stop->setEnabled(true);
}

void ThreadsDemoWindow::on_thread_1_stop_clicked()
{
    const QMutexLocker lock(&main_mtx);
    m_num_producer->disable_generation();
    ui->thread_1_resume->setEnabled(true);
    ui->thread_1_stop->setEnabled(false);
}

void ThreadsDemoWindow::on_thread_3_resume_clicked()
{
    const QMutexLocker lock(&main_mtx);
    m_number_consumer->enable_consumption();
    ui->thread_3_resume->setEnabled(false);
    ui->thread_3_stop->setEnabled(true);
}

void ThreadsDemoWindow::on_thread_3_stop_clicked()
{
    QMutexLocker lock(&main_mtx);
    m_number_consumer->disable_consumption();
    ui->thread_3_resume->setEnabled(true);
    ui->thread_3_stop->setEnabled(false);
}
