#ifndef MAINOPERATE_H
#define MAINOPERATE_H

#include <QMainWindow>
#include <QDebug>
#include <Windows.h>
#include <tchar.h>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QGraphicsEffect>
#include <QPainter>
#include <QtMath>
#include <QDialog>
#include <QFileInfoList>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSystemTrayIcon>
#include <QDir>
#include <random>
#include <algorithm>

#include "wallpaper.h"
#include "lowermenu.h"
#include "tool.h"
#include "hotkey.h"

namespace Ui {
class MainOperate;
}

extern MainOperate* MainInst; //主窗口实例

class MainOperate : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainOperate(QWidget *parent = 0);
    ~MainOperate();

    //关闭窗口
    void end_process();

    //getter & setter
    Wallpaper** wallpapers(){ return s_window; }
    int countWallpaper(){ return n_window; }

private slots:
    void onTray(QSystemTrayIcon::ActivationReason);
    void radio();


    void on_start_wall_clicked();


protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);


private:
    Ui::MainOperate *ui;

    //拖拽移动
    QPoint mLastMousePosition;
    bool mMoving;

    //壁纸
    Wallpaper** s_window; //窗口数组
    int n_window = 0;    //屏幕数量

    //托盘
    QSystemTrayIcon* tray;
    LowerMenu* menu;

};

#endif // MAINOPERATE_H
