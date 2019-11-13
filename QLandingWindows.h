#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QLabel>

#include <string>

class QGridLayout;


class QLandingWindow: public QWidget {
Q_OBJECT


public: 

QLandingWindow(QWidget* parent = nullptr);

QLandingWindow(QWidget* _mainWidget, QWidget* parent = nullptr);


virtual ~QLandingWindow() =default;

protected:

QGridLayout* layout;
QWidget* mainWidget;



};

class QLandingOptions : public QLandingWindow {
   Q_OBJECT

public :
    QLandingOptions(QWidget* _mainWidget,
                    const QString& _prompt,
                    const QString& leftOpt,
                    const QString& rightOpt,
                    QWidget* parent = nullptr);

    QLabel* getPrompt()    const{return prompt;}
    QPushButton* getLeft() const{return left;  }
    QPushButton* getRight()const{return right; }

//    void paintEvent(QPaintEvent* ) override;

private:
    QLabel* prompt;
    QPushButton* left;
    QPushButton* right;

};
