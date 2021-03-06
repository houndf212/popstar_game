#ifndef STARBOARD_H
#define STARBOARD_H
#include <QtCore>
#include <QGraphicsScene>
#include <memory>
#include "graphicmatrix.h"
#include "matrixslice.h"
#include "scorecalc.h"

class StarBoard : public QObject
{
    Q_OBJECT
public:
    explicit StarBoard(QObject* parent=nullptr);
    QGraphicsScene* get_scene() const { return m_scene; }
    const ScoreCalc* get_scoreptr() const { return &m_score; }
    Q_SIGNAL void sig_over();
    Q_SIGNAL void sig_score_changed();
    Q_SLOT void reset();
private:
    void gen_board();
    void gen_graphic_matrix();

    void delete_group(const PosVec& group);
    void move_board(const Matrix &before, const Matrix &after);
private:
    Q_SLOT void onStarClicked();
private:
    ScoreCalc m_score;
    Matrix m_matrix;
    QScopedPointer<MatrixSlice> m_slice;

    GraphicMatrix m_graphic_original_matrix;
    GraphicMatrix m_graphic_current_matrix;

    QGraphicsScene* m_scene;
private:
    typedef std::pair<Pos, Pos> MovedPos;
    static std::vector<MovedPos> find_move_pos(const Matrix& before, const Matrix& after);
    static QColor trans_color(int val);
    static const int SCALE = 40;
};

#endif // STARBOARD_H
