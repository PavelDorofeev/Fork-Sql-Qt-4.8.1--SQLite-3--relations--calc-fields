#ifndef SECTION_SETTINGS_DLG_H
#define SECTION_SETTINGS_DLG_H

#include <QDialog>
#include <QRadioButton>
#include <QIntValidator>

#include "qp/qp.h"

namespace Ui {
class SectionSettingsDlg;
}

class SectionSettingsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SectionSettingsDlg( const qp::db::CELL_STYLE &stl ,
                                 const qp::db::CELL_STYLE &def,
                                 QWidget *parent = 0);
    ~SectionSettingsDlg();

    qp::db::CELL_STYLE defaultStyle;
    qp::db::CELL_STYLE currStyles;

    QIntValidator iVal;

    int defaultPointSz;
    int defaultPixelSz;

private slots:

    void on_chk_hor_left_toggled(bool checked);

    void on_chk_hor_left_clicked(bool checked);

    void on_chk_hor_right_clicked(bool checked);

    void on_chk_ver_top_clicked(bool checked);

    void on_chk_ver_bottom_clicked(bool checked);

    void on_chk_center_clicked(bool checked);

    void on_ledt_fntWeight_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

    void on_chk_fnt_bold_clicked(bool checked);

    void on_chk_fnt_normal_clicked(bool checked);

    void on_chk_fnt_light_clicked(bool checked);

    void on_chk_fnt_demibold_clicked(bool checked);

    void on_chk_fnt_black_clicked(bool checked);


    void on_rbtn_brown_clicked(bool checked);

    void on_rbtn_red_clicked(bool checked);

    void on_rbtn_green_clicked(bool checked);

    void on_rbtn_blue_clicked(bool checked);

    void on_rbtn_size_normal_clicked();

    void on_rbtn_size_0_7_clicked(bool checked);

    void on_rbtn_size_1_5_clicked(bool checked);

    void on_spb_pointSize_valueChanged(int arg1);

    void on_spb_pixelSize_valueChanged(int arg1);

    void on_rbtn_size_2_0_clicked();


    void on_rbtn_size_0_5_clicked(bool checked);

    void on_ledt_color_editingFinished();

    void on_rbtn_orig_clicked();

private:
    Ui::SectionSettingsDlg *ui;

    QFont currFnt;

    void recalculate_align();
    void recalculate_font();

    bool isHorAlign();
    bool isVertAlign();
    void setColor();
    void setFontSize(double kf );

    QHash< QRadioButton* , QColor> colors;
    QHash< QRadioButton* , double> sizes;
    QHash< QRadioButton* , QFont::Weight > weights;
};

#endif // SECTION_SETTINGS_DLG_H
