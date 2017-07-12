#include "gamewindow.h"

GameWindow::GameWindow()
{
    m_board = new StarBoard(this);
    m_view = new GraphicsView(m_board->get_scene());

    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->resize(600, 600);

    m_score = new QLabel;
    connect(m_board, &StarBoard::sig_score_changed, this, &GameWindow::onScore);

    m_btn = new QPushButton("Reset");
    connect(m_btn, &QPushButton::clicked, m_board, &StarBoard::reset);

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget(m_score);
    hlayout->addStretch();
    hlayout->addWidget(m_btn);

    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout);
    vlayout->addWidget(m_view);
    setLayout(vlayout);

    connect(m_board, &StarBoard::sig_over, this, &GameWindow::onOver);
    m_board->reset();
}

void GameWindow::onScore()
{
    const QString tt ="score: %1, left: %2";
    const ScoreCalc* s = m_board->get_scoreptr();
    int sc = s->getScore();
    int lf = s->getLeft();
    m_score->setText(tt.arg(sc).arg(lf));
}

void GameWindow::onOver()
{
    m_score->setText(m_score->text() + ", game over.");
}
