#ifndef QP_VERTHEADERVIEW_H
#define QP_VERTHEADERVIEW_H

#include "qp/sql/tableview/qp_abstractitemview.h"
#include "qp/qp.h"


QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

#ifndef QT_NO_ITEMVIEWS

class QpVertHeaderViewPrivate;
class QStyleOptionHeader;
class QpHorHeaderView;

#include "qp/dll_qp_global.h"

class  LIB_PREFIX_QP QpVertHeaderView : public QpAbstractItemView
{
    Q_OBJECT
    Q_PROPERTY(bool showSortIndicator READ isSortIndicatorShown WRITE setSortIndicatorShown)
    Q_PROPERTY(bool highlightSections READ highlightSections WRITE setHighlightSections)
    Q_PROPERTY(bool stretchLastSection READ stretchLastSection WRITE setStretchLastSection)
    Q_PROPERTY(bool cascadingSectionResizes READ cascadingSectionResizes WRITE setCascadingSectionResizes)
    Q_PROPERTY(int defaultSectionSize READ defaultSectionSize WRITE setDefaultSectionSize)
    Q_PROPERTY(int minimumSectionSize READ minimumSectionSize WRITE setMinimumSectionSize)
    Q_PROPERTY(Qt::Alignment defaultAlignment READ defaultAlignment WRITE setDefaultAlignment)
    Q_ENUMS(ResizeMode)

public:

    enum ResizeMode
    {
        Interactive,
        Stretch,
        Fixed,
        ResizeToContents,
        Custom = Fixed
    };

    explicit QpVertHeaderView( const QpHorHeaderView &Horizontal,
                          //Qt::Orientation orientation,
                          QWidget *parent = 0);

    virtual ~QpVertHeaderView();


    void setModel(QAbstractItemModel *model);

    static const bool  debug_paint;
    static const bool  debug_size;
    static const bool  debug_scroll;
    static const bool  debug_init;
    static const bool  debug_select;
    static const bool  debug_visualIndexAt_Y;
    static const bool  debug_mdl_signals;
    //int row_heigth() const;

    int is_rowSelected( int row ) const;

    //void set_sectionCount( int cnt);
    //Qt::Orientation orientation() const;
    int offset() const;
    int length() const;
    QSize sizeHint() const;
    int sectionSizeHint(int logicalIndex) const;


    QString tblName() const;

    int visualIndexAt_Y(int y) const;
    int logicalIndexAt(int y) const;

    inline int logicalIndexAt(int x, int y) const;
    inline int logicalIndexAt(const QPoint &pos) const;

    int sectionSize(int logicalIndex) const;
    int sectionPosition(int logicalIndex) const;
    int sectionViewportPosition(int logicalIndex) const;

    void moveSection(int from, int to);
    void swapSections(int first, int second);
    void resizeSection(int logicalIndex, int size);
    void resizeSections(QpVertHeaderView::ResizeMode mode);

    bool isSectionHidden(int logicalIndex) const;
    void setSectionHidden(int logicalIndex, bool hide);
    int hiddenSectionCount() const;

    inline void hideSection(int logicalIndex);
    inline void showSection(int logicalIndex);

    int count() const;
    int visualIndex(int logicalIndex) const;
    int logicalIndex(int visualIndex) const;

    void setMovable(bool movable);
    bool isMovable() const;

    void setClickable(bool clickable);
    bool isClickable() const;

    void setHighlightSections(bool highlight);
    bool highlightSections() const;

    void setResizeMode(ResizeMode mode);
    void setResizeMode(int logicalIndex, ResizeMode mode);
    ResizeMode resizeMode(int logicalIndex) const;
    int stretchSectionCount() const;

    void setSortIndicatorShown(bool show);
    bool isSortIndicatorShown() const;

    void setSortIndicator(int logicalIndex, Qt::SortOrder order);
    int sortIndicatorSection() const;
    Qt::SortOrder sortIndicatorOrder() const;

    bool stretchLastSection() const;
    void setStretchLastSection(bool stretch);

    bool cascadingSectionResizes() const;
    void setCascadingSectionResizes(bool enable);

    int defaultSectionSize() const;
    void setDefaultSectionSize(int size);

    int minimumSectionSize() const;
    void setMinimumSectionSize(int size);

    Qt::Alignment defaultAlignment() const;
    void setDefaultAlignment(Qt::Alignment alignment);

    bool sectionsMoved() const;
    bool sectionsHidden() const;

#ifndef QT_NO_DATASTREAM
    QByteArray saveState() const;
    bool restoreState(const QByteArray &state);
#endif

    void reset();
    void doItemsLayout();

public Q_SLOTS:
    void setOffset(int offset);
    void setOffsetToSectionPosition(int visualIndex);
    void setOffsetToLastSection();
    void headerDataChanged(Qt::Orientation orientation, int logicalFirst, int logicalLast);
    void slot_sectionsTmplChanged( );
    void slot_rowsAboutToBeInserted(const QModelIndex &index, int start ,int end);

Q_SIGNALS:
    void sectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex);
    void sectionResized(int logicalIndex, int oldSize, int newSize);
    void sectionPressed(int logicalIndex);
    void sectionClicked(int logicalIndex);
    void sectionEntered(int logicalIndex);
    void sectionDoubleClicked(int logicalIndex);
    void sectionCountChanged(int oldCount, int newCount);
    void sectionHandleDoubleClicked(int logicalIndex);
    void sectionAutoResize(int logicalIndex, QpVertHeaderView::ResizeMode mode);
    void geometriesChanged();
    void sortIndicatorChanged(int logicalIndex, Qt::SortOrder order);

protected Q_SLOTS:
    void updateSection(int logicalIndex);
    void resizeSections();
    void sectionsInserted(const QModelIndex &parent, int logicalFirst, int logicalLast);
    void sectionsAboutToBeRemoved(const QModelIndex &parent, int logicalFirst, int logicalLast);

protected:
    QpVertHeaderView(QpVertHeaderViewPrivate &dd,
                     //Qt::Orientation orientation,
                     QWidget *parent = 0);
    void init();

    void initializeSections();
    void initializeSections(int start, int end);
    void currentChanged(const QModelIndex &current, const QModelIndex &old);

    bool event(QEvent *e);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    bool viewportEvent(QEvent *e);

    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    virtual QSize sectionSizeFromContents(int logicalIndex) const;

    int horizontalOffset() const;
    int verticalOffset() const;
    void updateGeometries();
    void scrollContentsBy(int dx, int dy);

    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void rowsInserted(const QModelIndex &parent, int start, int end);

    QRect visualRect(const QModelIndex &index) const;
    void scrollTo(const QModelIndex &index, QpAbstractItemView::ScrollHint hint);

    qp::db::SECTION index_At(const QPoint &p) const;
    QModelIndex indexAt(const QPoint &p) const;
    bool isIndexHidden(const QModelIndex &index) const;

    QModelIndex moveCursor(CursorAction, Qt::KeyboardModifiers);
    void setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags flags);
    QRegion visualRegionForSelection(const QItemSelection &selection) const;
    void initStyleOption(QStyleOptionHeader *option) const;

private:
    Q_PRIVATE_SLOT(d_func(), void _q_sectionsRemoved(const QModelIndex &parent, int logicalFirst, int logicalLast))
    Q_PRIVATE_SLOT(d_func(), void _q_layoutAboutToBeChanged())
    Q_DECLARE_PRIVATE(QpVertHeaderView)
    Q_DISABLE_COPY(QpVertHeaderView)
};

inline int QpVertHeaderView::logicalIndexAt(int ax, int ay) const
{
    return logicalIndexAt(ay);
}

inline int QpVertHeaderView::logicalIndexAt(const QPoint &apos) const
{ return logicalIndexAt(apos.x(), apos.y()); }

inline void QpVertHeaderView::hideSection(int alogicalIndex)
{ setSectionHidden(alogicalIndex, true); }

inline void QpVertHeaderView::showSection(int alogicalIndex)
{ setSectionHidden(alogicalIndex, false); }

#endif // QT_NO_ITEMVIEWS

QT_END_NAMESPACE

QT_END_HEADER

#endif // QP_VERTHEADERVIEW_H
