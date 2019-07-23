#include "wallpaper.h"
#include "ui_wallpaper.h"
#include "tool.h"

Wallpaper::Wallpaper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wallpaper)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); //无边框
}

Wallpaper::~Wallpaper()
{
    delete ui;
}
void Wallpaper::hide(){
    QWidget::hide();
    tool::UnderE::refresh();
}


void Wallpaper::run(QString path){
    //播放视频
//    auto playlist = new QMediaPlaylist;
//    playlist->addMedia(QUrl::fromLocalFile(
//                           QString::fromLocal8Bit("F:/视频和电影/电影/大鱼海棠.mkv")
//                       ));
//    playlist->setCurrentIndex(0);

//    auto player = new QMediaPlayer;
//    //player->setPlaylist(playlist);
//    player->setMedia(QUrl::fromLocalFile(
//        QString::fromLocal8Bit("F:/视频和电影/电影/大鱼海棠.mkv")
//    ));
//    player->play();

//    //auto videoWidget = new QVideoWidget;
//    //videoWidget->show();
//    //player->setVideoOutput(videoWidget);
//    player->setVideoOutput(this);


    //播放图片
    //设置Label
    ui->show->setScaledContents(true); //控件自适应
    ui->show->move(0,0); //label 移动到左上角
    ui->show->setFixedSize(this->size()); //适应窗口大小

    QImage image;
    image.load(path);
    qDebug()<<path;
    ui->show->clear();
    ui->show->setPixmap(QPixmap::fromImage(image));
}
