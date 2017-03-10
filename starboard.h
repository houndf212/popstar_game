#ifndef STARBOARD_H
#define STARBOARD_H
#include <QtCore>
#include <QGraphicsScene>
#include <memory>
#include "graphicmatrix.h"
#include "matrixslice.h"

class StarBoard : public QObject
{
    Q_OBJECT
public:
    StarBoard();
    QGraphicsScene* get_scene() const { return m_scene.data(); }
private:
    void gen_board();
    void gen_graphic_matrix();

    void delete_group(const Group& group);
    void move_board(const Matrix &before, const Matrix &after);
private:
    Q_SLOT void onStarClicked();
private:
    Matrix m_matrix;
    QScopedPointer<MatrixSlice> m_slice;

    GraphicMatrix m_graphic_original_matrix;
    GraphicMatrix m_graphic_current_matrix;

    QScopedPointer<QGraphicsScene> m_scene;
private:
    typedef std::pair<Pos, Pos> MovedPos;
    static std::vector<MovedPos> find_move_pos(const Matrix& before, const Matrix& after);
    static QColor trans_color(int val);
    static const int SCALE = 40;
};

#endif // STARBOARD_H
