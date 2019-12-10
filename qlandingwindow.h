#ifndef QLANDINGWINDOW_H
#define QLANDINGWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QLayout>
#include <string>

class MainWindow;

//generates a QDialog showing the no-option statement, delete on closed
void NoOptionWindow(QWidget*parent, QString statement);


/*
Base class for my custom popup windows.
Stores a gridlayout and a QWidget.
Displays QWidget in 0,0 of GridLayout.
Registers window to tempObjects in a mainWindow for memory management.
*/
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



/*
   A window class for use in displaying a message that allows the player two options.
    For example, buying a property or not buying a property.
      displays its elements in a column.
*/
class QLandingOptions : public QLandingWindow {
   Q_OBJECT

public :
    QLandingOptions(QWidget* _mainWidget,
                    const QString& _prompt,
                    QObject* _game,
                    const QString& leftOpt = "Yes",
                    const QString& rightOpt= "No",
                    QWidget* parent = nullptr);

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
