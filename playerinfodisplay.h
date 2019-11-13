#ifndef PLAYERINFODISPLAY_H
#define PLAYERINFODISPLAY_H
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
//everthing inside a template is a duck typed
class PlayerInfoDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerInfoDisplay(QWidget *parent = nullptr);
    //~PlayerInfoDisplay();
    static QStringList PlayerNames();
private:
    QLabel *createPlayerHeader(const QString& text);
    QLabel *createPlayerPixmap();

    enum{BoardLength = 4};
    QLabel *playertext[BoardLength];
    QLabel *playerPixmap[BoardLength];
};

#endif // PLAYERINFODISPLAY_H
