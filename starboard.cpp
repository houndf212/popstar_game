#include "starboard.h"
#include "matrixgenerator.h"
#include "matrixgame.h"
#include <iostream>

StarBoard::StarBoard()
{
    m_scene.reset( new QGraphicsScene(0, 0, m_matrix.col_size()*SCALE, m_matrix.col_size()*SCALE) );
    gen_board();
}

void StarBoard::gen_board()
{
    m_matrix = MatrixGenerator::gen(5);
    m_slice.reset(new MatrixSlice(m_matrix));
    gen_graphic_matrix();
}

void StarBoard::gen_graphic_matrix()
{
    for (int row=0; row<m_matrix.row_size(); ++row)
    {
        for (int col=0; col<m_matrix.col_size(); ++col)
        {
            Pos p(row, col);
            StarItem* star= new StarItem;
            connect(star, &StarItem::clicked, this, &StarBoard::onStarClicked);
            m_scene->addItem(star);

            m_graphic_original_matrix.set(p, star);
            m_graphic_current_matrix.set(p, star);

            QColor color = trans_color(m_matrix.get(p).val);
            star->setColor(color);
            star->set_original_pos(p);
            star->set_current_pos(p);
            star->setRect(0, 0, SCALE, SCALE);
            star->setPos(col*SCALE, row*SCALE);
        }
    }

}

void StarBoard::delete_group(const Group &group)
{
    for(auto p : group)
    {
        FlagVal v = m_matrix.get(p);
        Pos org = v.original_pos;

        StarItem* ss = m_graphic_current_matrix.get(p);
        ss->animate_delete(1000);

        Q_ASSERT(ss == m_graphic_original_matrix.get(org));

        m_graphic_original_matrix.set(org, nullptr);
        m_graphic_current_matrix.set(p, nullptr);
    }
}

void StarBoard::move_board(const Matrix &before, const Matrix &after)
{
    std::vector<StarBoard::MovedPos> vec = find_move_pos(before, after);
    for (auto s : vec)
    {
        Pos org = s.first;
        Pos p = s.second;
        StarItem* star = m_graphic_original_matrix.get(org);
        star->animate_move(QPointF(p.col*SCALE, p.row*SCALE), 1000);
        star->set_current_pos(p);
        m_graphic_current_matrix.set(p, star);
    }
}

void StarBoard::onStarClicked()
{
    StarItem* star = qobject_cast<StarItem*>(sender());
    Pos p = star->current_pos();

    std::cout <<"clicked: " << p <<std::endl;
    Q_ASSERT(star != nullptr);
    if (!m_slice->canClick(p))
        return;

    std::cout <<"clicked: " << p <<std::endl;
    Group group = m_slice->getGroup(p);
    delete_group(group);

    Matrix m = m_matrix;
    MatrixGame::removePosSet(m_matrix, group);
    std::cout<<m_matrix<<std::endl;

    move_board(m, m_matrix);

    m_slice.reset(new MatrixSlice(m_matrix));
}

std::vector<StarBoard::MovedPos> StarBoard::find_move_pos(const Matrix &before, const Matrix &after)
{
    std::vector<StarBoard::MovedPos> vec;
    for (int row=0; row<after.row_size(); ++row)
    {
        for (int col=0; col<after.col_size(); ++col)
        {
            Pos p(row, col);
            if (after.get(p).val == FlagVal::Blank)
                continue;
            Pos org_before = before.get(p).original_pos;
            Pos org_after = after.get(p).original_pos;
            if (org_before != org_after)
            {
                vec.push_back(MovedPos(org_after, p));
            }
        }
    }
    return vec;
}

QColor StarBoard::trans_color(int val)
{
    switch(val)
    {
    case 1:
        return Qt::yellow;
    case 2:
        return Qt::green;
    case 3:
        return Qt::blue;
    case 4:
        return Qt::red;
    case 5:
        return QColor(255, 192, 203); //pink
    default:
        return QColor(255, 192, 203);
    }
}
