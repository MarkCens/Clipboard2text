#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    // ���ش��������
    this->setWindowFlags(Qt::FramelessWindowHint);
    // ���ô���icon�����qtc��ԴͼƬ·��
    this->setWindowIcon(QIcon(":/img/icon.png"));
    // ���ô�����ǰ
    click_bt_top();
    // �����źźͲۣ����ó�����Ҫ�ĸ����¼�������
    connect(ui->main_convert, &QPushButton::clicked, this, &MainWindow::paste);
    connect(ui->main_top, &QPushButton::clicked, this, &MainWindow::click_bt_top);
    connect(ui->main_close, &QPushButton::clicked, this, &MainWindow::click_bt_close);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::click_bt_top(){
    // ������Ǵ�����ǰ
    if (this->m_is_top == false){
        // ����Ϊ������ǰ
        this->m_is_top = true;
        // ���°�ť����ʽ
        ui->main_top->setStyleSheet(""
                                    "QPushButton{background-color:#5bbcff;color:#ffffff;font-weight:bold;border-image:url();border:0;}"
                                    "QPushButton:hover{background-color:#4aabfe;}"
                                    "QPushButton:pressed{background-color:#4aabfe;}");
        // ���ô���Flags��ǰ�������ش��ڱ������������Ǳ��ִ�����ǰ
        this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
        this->showNormal();
    }else{  // ����Ѿ��Ǵ�����ǰ
        this->m_is_top = false;
        // ȡ������Ϊ������ǰ
        ui->main_top->setStyleSheet(""
                                    "QPushButton{background-color:#4aabfe;color:#ffffff;font-weight:bold;border-image:url();border:0;}"
                                    "QPushButton:hover{background-color:#5bbcff;}"
                                    "QPushButton:pressed{background-color:#5bbcff;}");
        // ���ô���Flags����˼�Ǳ��ֵ�ǰ����Flags�����˱��ִ�����ǰ
        this->setWindowFlags(this->windowFlags() & ~Qt::WindowStaysOnTopHint);
        this->showNormal();
    }
}

void MainWindow::click_bt_close(){
    // �رմ��ڣ��˳�����
    this->close();
    exit(0);
}

void MainWindow::paste(){
    // ��ȡϵͳ������ָ��
    QClipboard *clipboard = QApplication::clipboard();
    // ��ȡ�������ı���Ϣ
    QString content = clipboard->text();
    // ���ü���������
    clipboard->setText(content);
}

void MainWindow::mouseMoveEvent(QMouseEvent *lpEvent){
    // ������ʵ����ק
    if (lpEvent->buttons() & Qt::LeftButton){
        // ��ȡλ��
        QPoint pos = lpEvent->globalPos();
        // �ƶ�����
        move(pos - m_pre_pos);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *lpEvent){
    // ������ʵ����ק
    if (lpEvent->button() == Qt::LeftButton){
        // ��ȡλ��
        m_pre_pos = lpEvent->globalPos() - frameGeometry().topLeft();
    }
}
