#ifndef QLANDINGWINDOW_H
#define QLANDINGWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QLayout>
#include <string>

class MainWindow;

void NoOptionWindow(QWidget*parent, QString statement);


class QLandingWindow: public QWidget {
Q_OBJECT
public:
QLandingWindow(QObject* _game, QWidget* parent = nullptr);
QLandingWindow(QWidget* _mainWidget, QObject* game, QWidget* parent = nullptr);
virtual ~QLandingWindow() = default;
protected:
QGridLayout* layout;
QWidget* mainWidget;
private:
QObject* game;
};


class QLandingOptions : public QLandingWindow {
   Q_OBJECT

public :
    QLandingOptions(QWidget* _mainWidget,
                    const QString& _prompt,
                    QObject* _game,
                    const QString& leftOpt = "Yes",
                    const QString& rightOpt= "No",
                    QWidget* parent = nullptr);
   // QLandingOptions(QWidget* _mainWidget,
//                    const QString& _prompt,
  //                  QObject* _game,);//for railroad
    QLabel* getPrompt()    const{return prompt;}
    QPushButton* getLeft() const{return left;  }
    QPushButton* getRight()const{return right; }

    ~QLandingOptions() override;
private:
    QLabel* prompt;
    QPushButton* left;
    QPushButton* right;
};


#endif // QLANDINGWINDOW_H
