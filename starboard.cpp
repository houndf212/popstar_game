#include "starboard.h"
#include "matrixgenerator.h"
#include "matrixgame.h"
#include <iostream>
#include <string>
#include "matrixinput.h"

StarBoard::StarBoard(QObject *parent)
    :QObject(parent)
{
    m_scene = new QGraphicsScene(0, 0, m_matrix.col_size()*SCALE, m_matrix.col_size()*SCALE, this);
    reset();
}

void StarBoard::reset()
{
    gen_board();
    gen_graphic_matrix();
    m_score = ScoreCalc();
    Q_EMIT sig_score_changed();
    m_slice.reset(new MatrixSlice(m_matrix));
    if (m_slice->isOver())
        Q_EMIT sig_over();
}

void StarBoard::gen_board()
{
    m_matrix = MatrixGenerator::gen(5);
    //test
//    QString str =
//            " 2  1  4  1  4  1  2  4  4  1 "
//            " 4  1  3  1  3  4  3  2  1  3 "
//            " 4  4  3  3  1  2  4  2  4  4 "
//            " 1  2  3  3  3  2  1  2  3  4 "
//            " 2  3  3  2  4  4  3  3  1  4 "
//            " 3  3  1  3  4  1  1  4  1  1 "
//            " 2  1  4  4  2  4  3  4  4  1 "
//            " 1  1  3  2  2  3  2  3  4  4 "
//            " 4  2  1  2  2  1  3  1  2  1 "
//            " 2  1  2  4  1  3  4  1  4  1 "
//            ;
//    str = str.replace(" ", "");
//    m_matrix = MatrixInput::fromString(str.toStdString());
}

void StarBoard::gen_graphic_matrix()
{
    //first clear
    QList<QGraphicsItem *> items = m_scene->items();
    for (auto it : items)
    {
//        StarItem* star = dynamic_cast<StarItem*>(it);
//        Q_ASSERT(star!=nullptr);
//        star->animate_delete(500);
        delete it;
    }

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
//    std::cout<<m_matrix<<std::endl;
}

void StarBoard::delete_group(const Group &group)
{
    for(auto p : group)
    {
        FlagVal v = m_matrix.get(p);
        Pos org = v.original_pos;

        StarItem* star = m_graphic_current_matrix.get(p);
        Q_ASSERT(star!=nullptr);
        star->animate_delete(500);
        star->set_current_pos(Pos(-1, -1));

        Q_ASSERT(star == m_graphic_original_matrix.get(org));

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

        Q_ASSERT(star!=nullptr);
        star->set_current_pos(p);
        m_graphic_current_matrix.set(p, star);
        star->animate_move(QPointF(p.col*SCALE, p.row*SCALE), 1000);

    }
}

void StarBoard::onStarClicked()
{
    StarItem* star = qobject_cast<StarItem*>(sender());
    Q_ASSERT(star!=nullptr);
    Pos p = star->current_pos();

//    std::cout <<"signal clicked: " << p <<std::endl;
    Q_ASSERT(star != nullptr);
    if (!m_slice->canClick(p))
        return;

//    std::cout <<"clicked: " << p <<"org: "<<star->original_pos()<<std::endl;

    Group group = m_slice->getGroup(p);

    delete_group(group);

    Matrix m = m_matrix;
    int n = MatrixGame::removePosSet(m_matrix, group);
    m_score.put(p, m.get(p), n);
    Q_EMIT sig_score_changed();

//    std::cout<<m_matrix<<std::endl;

    move_board(m, m_matrix);

    m_slice.reset(new MatrixSlice(m_matrix));
    if (m_slice->isOver())
        Q_EMIT sig_over();
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
            { continue; }

            Q_ASSERT(after.get(p).val!=FlagVal::Unflaged);
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
