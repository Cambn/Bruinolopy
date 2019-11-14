#include "gif.h"
#include <QApplication>
#include <QImage>

AnimatedLabel::AnimatedLabel(const QString &image, const int imageCount, QWidget *parent)
    :     QLabel(parent), currentPixmap(0)
{
    QImage img;
    img.load(image);
    int subImageHeight = img.height() / imageCount;

    for (int i = 0; i < imageCount; i++)
    {
        QImage subImage = img.copy(0, i * subImageHeight, img.width(), subImageHeight);
        pixmaps.push_back(QPixmap::fromImage(subImage));
    }

    connect(&timer, SIGNAL(timeout()), SLOT(changeImage()));
    timer.start(100);
    changeImage();
}

void AnimatedLabel::changeImage()
{
    if (currentPixmap >= pixmaps.length())
        currentPixmap = 0;

    setPixmap(pixmaps.at(currentPixmap));

    currentPixmap++;
}

