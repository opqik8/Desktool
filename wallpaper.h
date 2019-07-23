#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QWidget>
//#include <QMediaPlayer>
//#include <QMediaPlaylist>
//#include <QVideoWidget>


namespace Ui {
class Wallpaper;
}

class Wallpaper : public QWidget
{
    Q_OBJECT

public:
    explicit Wallpaper(QWidget *parent = 0);
    ~Wallpaper();

    void run(QString path);

    QRect screen;


public slots:
    void hide();

private:
    Ui::Wallpaper *ui;
};

#endif // WALLPAPER_H
