#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QPoint>
#include <QMouseEvent>
#include <QApplication>
#include <QClipboard>
#include <QString>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *);    // 实现窗体移动的事件（鼠标点击事件）
    void mouseMoveEvent(QMouseEvent *);     // 实现窗体移动的事件（鼠标移动事件）

public slots:
    void click_bt_top();    // 槽：窗体最前点击函数
    void click_bt_close();  // 槽：窗体关闭点击函数
    void paste();           // 槽：复制点击函数（点击实现傻瓜式图片粘贴板内容2文字粘贴板内容）

private:
    Ui::MainWindow *ui;
    bool m_is_top = false;  // 变量：用于实现窗体最前/取消窗体最前
    QPoint m_pre_pos;       // 变量：用于实现窗体拖拽移动
};
#endif // MAINWINDOW_H
