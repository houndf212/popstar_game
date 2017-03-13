#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QtWidgets>
#include "graphicsview.h"
#include "starboard.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow();
private:
    Q_SLOT void onScore();
    Q_SLOT void onOver();
private:
    StarBoard* m_board;
    GraphicsView *m_view;
    QLabel* m_score;
    QPushButton* m_btn;
};

#endif // GAMEWINDOW_H
