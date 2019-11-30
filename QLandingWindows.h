#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QLabel>

#include <string>

class MainWindow;
class QGridLayout;




/**
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
/**
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
/**
    A window class for use in displaying a message where a player doesn't have any options.
    For example, landing on a tile and having to pay rent, drawing a card that forces an action, etc.
     displays its elements in a column.
*/
class QLandNoOptions: public QLandingWindow {
public:
    QLandNoOptions(QWidget* _mainWidget,
                   const QString& _message,
                   QObject* _game,
                   const QString& buttonText= "Okay",
                   QWidget* parent = nullptr);

    ~QLandNoOptions() override;

private:
    QLabel* message;
    QPushButton* button;

};
