#ifndef GIF_H
#define GIF_H
#include <QString>
#include <QTimer>
#include <QList>
#include <QPixmap>
#include <QLabel>

class AnimatedLabel : public QLabel{
    Q_OBJECT

public:
    AnimatedLabel(const QString & image, const int imageCount,  QWidget* parent = 0);
private slots:
    void changeImage();

private:
    QList<QPixmap> pixmaps;
    int currentPixmap;
    QTimer timer;

};

#endif // GIF_H
