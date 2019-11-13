#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QIcon>
#include <QStringList>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPixmap>
class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);

   // void setIcon(const QIcon& icon);
    //void setSize(const QSize& size);
   // static QVector<QIcon::Mode> iconModes();

    //static QVector<QIcon::State> iconStates();
    static QStringList iconLengthNames();
    static QStringList iconWidthNames();
    //static QVector<>
private:
    QLabel *createHeaderLabel(const QString& text);
    //void updatePixmapLabels();
   // QLabel *createLandMark();
    QLabel *createPixmapLabel();

    enum{BoardLength = 4, BoardWidth = 4};
   // QIcon icon;
   // QSize size;
    QLabel *LengthLabels[BoardWidth];
    QLabel *WidthLabels[BoardLength];
    QLabel *pixmapLabels[BoardWidth][BoardLength];

};

#endif // GAMEBOARD_H
