#include "mainoperate.h"
#include "ui_mainoperate.h"
#include "lowermenu.h"
#include "mainoperate.h"
MainOperate* MainInst = nullptr;


MainOperate::MainOperate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainOperate)
{
    MainInst = this;
    //UI
    ui->setupUi(this);
    this->setFixedSize(this->ui->bg->size());
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->setStyleSheet("color:white");
    this->ui->bg->setStyleSheet("#bg{background:rgba(0,0,0,0.3)}");

    tool::Effect::blur((HWND)this->winId(),tool::BLUR2);
    ui->radio_trans->setChecked(true);
    connect(ui->radio_blur1,SIGNAL(clicked()),this,SLOT(radio()));
    connect(ui->radio_blur2,SIGNAL(clicked()),this,SLOT(radio()));
    connect(ui->radio_trans,SIGNAL(clicked()),this,SLOT(radio()));


    //初始化托盘
    menu=new LowerMenu(this);
    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon("resource/img/logo.png"));
    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(onTray(QSystemTrayIcon::ActivationReason)));
    tray->show();

    //检测显示屏数
    QDesktopWidget * deskTop = QApplication::desktop();
    this->n_window = deskTop->screenCount();
    //初始化壁纸
    if (!tool::UnderE::init()){
        QMessageBox::warning(this,"初始化错误","壁纸初始化失败！");
        this->end_process();
    }
    this->s_window=new Wallpaper*[this->n_window];
    for(int i=0;i<n_window;i++){
        this->s_window[i] = new Wallpaper();
        auto t = this->s_window[i];
        //设置位置和大小
        t->setGeometry(deskTop->screenGeometry(i));
        //下潜
        qDebug()<<"Window put "<<tool::UnderE::put(t->winId());
    }
    //设置默认图片
    s_window[0]->run("resource/bg-img/bg.jpg");
    if (this->n_window>=2)s_window[1]->run("resource/bg-img/bg2.png");

    //hotkey
    HotKey::getInstance()->init();

}

MainOperate::~MainOperate(){
    delete ui;
}

void MainOperate::radio(){
    if (ui->radio_blur1->isChecked()){
        tool::Effect::blur((HWND)this->winId(),tool::BLUR1);

    }
    if (ui->radio_blur2->isChecked()){
        tool::Effect::blur((HWND)this->winId(),tool::BLUR2);

    }
    if (ui->radio_trans->isChecked()){
        tool::Effect::blur((HWND)this->winId(),tool::TRANS);

    }


}

void MainOperate::end_process(){
    //清理资源
    this->hide();
    for(int i=0;i<n_window;i++){
        auto t = this->s_window[i];
        if (t!=nullptr)
            t->hide();
    }
    this->tray->hide();
    this->menu->hide();
    this->close();
}

void MainOperate::onTray(QSystemTrayIcon::ActivationReason reason){
    switch(reason){
    case QSystemTrayIcon::Context: //右击托盘图标
        menu->show();
        menu->activateWindow();
        break;
    case QSystemTrayIcon::DoubleClick: //双击托盘图标
        this->show();
        break;
    case QSystemTrayIcon::Trigger:
        //左键单击
    case QSystemTrayIcon::MiddleClick:
        //中建
    default:
        break;
    }
}

void MainOperate::on_start_wall_clicked()
{
    for(int i=0;i<n_window;i++){
        (this->s_window[i])->show();
    }
}

//拖拽移动
void MainOperate::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        mMoving = true;
        mLastMousePosition = event->globalPos();
    }
}
void MainOperate::mouseMoveEvent(QMouseEvent* event)
{
    if(mMoving && event->buttons().testFlag(Qt::LeftButton))
    {
        this->move(this->pos() + (event->globalPos() - mLastMousePosition));
        mLastMousePosition = event->globalPos();
    }
}
void MainOperate::mouseReleaseEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton)
        mMoving = false;
}
