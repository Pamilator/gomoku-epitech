#include "goban.h"

#include "EachInTurnRule.h"
#include "DoubleThree.h"
#include "NotEmptyRule.h"
#include "TakingRules.h"
#include "VictoryCapturesRule.h"
#include "VictoryAlignment.h"
#include "Finished.h"

GobanQt::GobanQt(QMainWindow *parent, QPixmap Image) :
    QLabel(parent)
{
    this->setPixmap(Image);
    this->playerTurn = false;
    unsigned int x = 1;
    unsigned int y = 1;
    unsigned short id = 0;
    for (unsigned short i = 0; i < 19; ++i)
    {
        for (unsigned short j = 0; j < 19; ++j)
        {
            this->square[id].x = x;
            this->square[id].y = y;
            this->square[id].isEmpty = false;
            this->square[id].rect = QRect(x, y, 18, 18);
            this->square[id].image = new QLabel(this);
            this->square[id].image->setMinimumHeight(18);
            this->square[id].image->setMinimumWidth(18);
            ++id;
            x += 19;
        }
        x = 1;
        y += 19;
    }

    Goban *  goban = new Goban();
    this->referrer =  new Referrer(*goban);
    this->referrer->addPrePlayRule(*(new Rules::EachInTurnRule()));
    this->referrer->addPrePlayRule(*(new Rules::DoubleThree()));
    this->referrer->addPrePlayRule(*(new Rules::NotEmptyRule()));
    Rules::TakingRules * tkrule = new Rules::TakingRules();
    this->referrer->addPlayRule(*tkrule);
    this->referrer->addPostPlayRule(*(new Rules::VictoryCapturesRule(*tkrule)));
    this->referrer->addPostPlayRule(*(new Rules::VictoryAlignment()));
}

GobanQt::~GobanQt()
{
    for (unsigned short i = 0; i < 361; ++i)
        delete this->square[i].image;
}

void GobanQt::mousePressEvent(QMouseEvent* e)
{
    Goban::PION_TYPE pion;
    QString pionImg;
    if (e->button() == Qt::LeftButton)
    {
        if (!playerTurn)
        {
            pion = Goban::BLACK;
            pionImg = ":/new/prefix1/pionNoir.png";
        }
        else
        {
            pion = Goban::RED;
            pionImg = ":/new/prefix1/pionBlanc.png";
        }
        for (unsigned short i = 0; i < 361; ++i)
        {
            if (this->square[i].y <= e->y() && this->square[i].x <= e->x() && (18 + this->square[i].x) >= e->x() && (this->square[i].y + 18) >= e->y())
            {
                if (!this->square[i].isEmpty)
                {
                    if (this->referrer->CanPlay(pion, i % 19, i / 19))
                    {
                        this->referrer->Play();
                        this->square[i].isEmpty = true;
                        this->square[i].image->setPixmap(QPixmap(pionImg));
                        this->square[i].image->move(this->square[i].x, this->square[i].y);
                        this->informations = i;
                        playerTurn = !playerTurn;
                        emit clicked();
                        this->referrer->AfterPlay();
                        break;
                    }
                }
            }
        }

        this->coordinates = this->referrer->GetListOfTurn().front().captures;
        std::for_each(this->coordinates.begin(), this->coordinates.end(),
                [this](std::pair<unsigned int, unsigned int> & p)
        {
            unsigned int stoneToDelete = p.first + (p.second * 19);
            this->square[stoneToDelete].isEmpty = true;
            this->square[stoneToDelete].image->clear();
        });

        if (this->referrer->GameFinished())
        {
            pion = this->referrer->Winner();
            Finished finish;
            finish.exec();
        }
    }
}

int GobanQt::getInformation(void) const
{
    return this->informations;
}

bool GobanQt::getPlayerTurn(void) const
{
    return this->playerTurn;
}
