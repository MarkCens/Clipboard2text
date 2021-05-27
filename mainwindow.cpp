#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    // 隐藏窗体标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    // 设置窗体icon，这个qtc资源图片路径
    this->setWindowIcon(QIcon(":/img/icon.png"));
    // 设置窗体最前
    click_bt_top();
    // 连接信号和槽（设置程序需要的各种事件监听）
    connect(ui->main_convert, &QPushButton::clicked, this, &MainWindow::paste);
    connect(ui->main_top, &QPushButton::clicked, this, &MainWindow::click_bt_top);
    connect(ui->main_close, &QPushButton::clicked, this, &MainWindow::click_bt_close);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::click_bt_top(){
    // 如果不是窗体最前
    if (this->m_is_top == false){
        // 设置为窗体最前
        this->m_is_top = true;
        // 更新按钮的样式
        ui->main_top->setStyleSheet(""
                                    "QPushButton{background-color:#5bbcff;color:#ffffff;font-weight:bold;border-image:url();border:0;}"
                                    "QPushButton:hover{background-color:#4aabfe;}"
                                    "QPushButton:pressed{background-color:#4aabfe;}");
        // 设置窗体Flags，前者是隐藏窗口标题栏，后者是保持窗体最前
        this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
        this->showNormal();
    }else{  // 如果已经是窗体最前
        this->m_is_top = false;
        // 取消设置为窗体最前
        ui->main_top->setStyleSheet(""
                                    "QPushButton{background-color:#4aabfe;color:#ffffff;font-weight:bold;border-image:url();border:0;}"
                                    "QPushButton:hover{background-color:#5bbcff;}"
                                    "QPushButton:pressed{background-color:#5bbcff;}");
        // 设置窗体Flags，意思是保持当前窗口Flags但除了保持窗体最前
        this->setWindowFlags(this->windowFlags() & ~Qt::WindowStaysOnTopHint);
        this->showNormal();
    }
}

void MainWindow::click_bt_close(){
    // 关闭窗口，退出程序
    this->close();
    exit(0);
}

void MainWindow::paste(){
    // 获取系统剪贴板指针
    QClipboard *clipboard = QApplication::clipboard();
    // 获取剪贴板文本信息
    QString content = clipboard->text();
    // 设置剪贴板内容
    clipboard->setText(content);
}

void MainWindow::mouseMoveEvent(QMouseEvent *lpEvent){
    // 鼠标左键实现拖拽
    if (lpEvent->buttons() & Qt::LeftButton){
        // 获取位置
        QPoint pos = lpEvent->globalPos();
        // 移动窗体
        move(pos - m_pre_pos);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *lpEvent){
    // 鼠标左键实现拖拽
    if (lpEvent->button() == Qt::LeftButton){
        // 获取位置
        m_pre_pos = lpEvent->globalPos() - frameGeometry().topLeft();
    }
}
