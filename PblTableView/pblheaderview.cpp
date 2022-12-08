#include "pblheaderview.h"
#include <QDebug>
#include <QPainter>

#include "PblSqlRelationalTableModel.h"

PblHeaderView::PblHeaderView(PblSqlRelationalTableModel * mdl_, Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent)
{
    mdl = mdl_;
}
void PblHeaderView::paintEvent(QPaintEvent *e)
{
    qDebug() << "PblHeaderView::paintEvent";

    qDebug() << "PblHeaderView headerData : " << mdl->headerData(0 , Qt::Horizontal,Qt::BackgroundRole);


    QHeaderView::paintEvent(e);
}

void PblHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{

    //Q_D(const QHeaderView);
    if (!rect.isValid())
        return;
    // get the state of the section
    QStyleOptionHeader opt;

    initStyleOption(&opt);

    QStyle::State state = QStyle::State_None;
    if (isEnabled())
        state |= QStyle::State_Enabled;
    if (window()->isActiveWindow())
        state |= QStyle::State_Active;
    /*if (d->clickableSections) {
        if (logicalIndex == d->hover)
            state |= QStyle::State_MouseOver;
        if (logicalIndex == d->pressed)
            state |= QStyle::State_Sunken;
        else if (d->highlightSelected) {
            if (d->sectionIntersectsSelection(logicalIndex))
                state |= QStyle::State_On;
            if (d->isSectionSelected(logicalIndex))
                state |= QStyle::State_Sunken;
        }

    }*/
    if (isSortIndicatorShown() && sortIndicatorSection() == logicalIndex)
        opt.sortIndicator = (sortIndicatorOrder() == Qt::AscendingOrder)
                ? QStyleOptionHeader::SortDown : QStyleOptionHeader::SortUp;

    // setup the style options structure
    QVariant textAlignment = mdl->headerData(logicalIndex, Qt::Horizontal, Qt::TextAlignmentRole);

    opt.rect = rect;
    opt.section = logicalIndex;
    opt.state |= state;
    opt.textAlignment = Qt::Alignment(textAlignment.isValid() ? Qt::Alignment(textAlignment.toInt()) : Qt::AlignCenter );

    opt.iconAlignment = Qt::AlignVCenter;
    opt.text = mdl->headerData(logicalIndex, Qt::Horizontal, Qt::DisplayRole).toString();
    /*if (d->textElideMode != Qt::ElideNone)
        opt.text = opt.fontMetrics.elidedText(opt.text, d->textElideMode , rect.width() - 4);*/

    QVariant variant = mdl->headerData(logicalIndex, Qt::Horizontal, Qt::DecorationRole);

    opt.icon = qvariant_cast<QIcon>(variant);

    if (opt.icon.isNull())
        opt.icon = qvariant_cast<QPixmap>(variant);

    QVariant foregroundBrush = mdl->headerData(logicalIndex, Qt::Horizontal,
                                               Qt::ForegroundRole);
    if (foregroundBrush.canConvert<QBrush>())
        opt.palette.setBrush(QPalette::ButtonText, qvariant_cast<QBrush>(foregroundBrush));

    QPointF oldBO = painter->brushOrigin();
    QVariant backgroundBrush = mdl->headerData(logicalIndex, Qt::Horizontal,
                                               Qt::BackgroundRole);
    if (backgroundBrush.canConvert<QBrush>()) {
        opt.palette.setBrush(QPalette::Button, qvariant_cast<QBrush>(backgroundBrush));
        opt.palette.setBrush(QPalette::Window, qvariant_cast<QBrush>(backgroundBrush));
        painter->setBrushOrigin(opt.rect.topLeft());

        qDebug() << "backgroundBrush " << backgroundBrush << " logicalIndex " << logicalIndex;
    }

    // the section position
    int visual = visualIndex(logicalIndex);
    Q_ASSERT(visual != -1);
    if (count() == 1)
        opt.position = QStyleOptionHeader::OnlyOneSection;
    else if (visual == 0)
        opt.position = QStyleOptionHeader::Beginning;
    else if (visual == count() - 1)
        opt.position = QStyleOptionHeader::End;
    else
        opt.position = QStyleOptionHeader::Middle;

    opt.orientation = Qt::Horizontal;

    // the selected position
    /* bool previousSelected = d->isSectionSelected(this->logicalIndex(visual - 1));

    bool nextSelected =  d->isSectionSelected(this->logicalIndex(visual + 1));

    if (previousSelected && nextSelected)
        opt.selectedPosition = QStyleOptionHeader::NextAndPreviousAreSelected;
    else if (previousSelected)
        opt.selectedPosition = QStyleOptionHeader::PreviousIsSelected;
    else if (nextSelected)
        opt.selectedPosition = QStyleOptionHeader::NextIsSelected;
    else
        opt.selectedPosition = QStyleOptionHeader::NotAdjacent;
    */
    // draw the section

    //style()->drawControl(QStyle::CE_Header, &opt, painter, this);

    //if (const QStyleOptionHeader *header = qstyleoption_cast<const QStyleOptionHeader *>(opt))
    //const QStyleOptionHeader *header = qstyleoption_cast<const QStyleOptionHeader *>(opt);

    QRegion clipRegion = painter->clipRegion();

    painter->setClipRect(opt.rect);

    //opt.icon = QIcon(":icon/img/btn-db/select-by-value-2-100x100.png");
    //opt.iconAlignment = Qt::AlignLeft;

    if(logicalIndex == 2)
        style()->drawControl(QStyle::CE_HeaderSection, &opt, painter, this);

    /*if(logicalIndex == 1)
        style()->drawControl(QStyle::CE_HeaderLabel, &opt, painter, this    );*/


    QStyleOptionHeader subopt = opt;

    subopt.rect = style()->subElementRect(QStyle::SE_HeaderLabel, &opt, this);

    if (subopt.rect.isValid())
        style()->drawControl(QStyle::CE_HeaderLabel, &subopt, painter, this);

    if (opt.sortIndicator != QStyleOptionHeader::None)
    {
        subopt.rect = style()->subElementRect(QStyle::SE_HeaderArrow, &opt, this);

        style()->drawPrimitive(QStyle::PE_IndicatorHeaderArrow, &subopt, painter, this);
    }
    painter->setClipRegion(clipRegion);


    painter->setBrushOrigin(oldBO);
}
/*
case CE_Header:

    break;*/
