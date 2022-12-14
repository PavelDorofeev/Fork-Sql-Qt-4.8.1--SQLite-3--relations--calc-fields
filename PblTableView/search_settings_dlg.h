#ifndef SEARCH_SETTINGS_DLG
#define SEARCH_SETTINGS_DLG

#include <QDialog>

namespace Ui {
class Search_Settings_Dlg;
}

class PblSqlRelationalTableModel;
class PblTableView;

class Search_Settings_Dlg : public QDialog
{
    Q_OBJECT
    
public:

    struct FIND_SETTINGS
    {
        enum SEARCH_TYPE
        {
            SEARCH_UNDEFINED_TYPE,
            SEARCH_TEXT,
            SEARCH_NUMBER,
            SEARCH_RELATION_TEXT
        };

        int searchedField;
        bool caseSensitive;
        bool exactly;

        SEARCH_TYPE seachType;

        FIND_SETTINGS():
            searchedField(-1),
            caseSensitive(false),
            exactly(false),
            seachType(SEARCH_UNDEFINED_TYPE)

        {

        }

        bool operator != (const FIND_SETTINGS& other) const
        {
            return  searchedField != other.searchedField
                    || caseSensitive != other.caseSensitive
                    || exactly != other.exactly;
        }
    };

    explicit Search_Settings_Dlg(PblSqlRelationalTableModel * mdl_,
                      PblTableView * view,
                      QWidget *parent = 0);
    ~Search_Settings_Dlg();
    
    void accept();
    //int searchedField;
    //bool caseSensitive;
    //bool exactly;

    FIND_SETTINGS find_settings;

    void setSettings(FIND_SETTINGS);

signals:
    void sig_setFilter(QString);
    void sig_setSettings(FIND_SETTINGS);
public slots:
    void cmb_Fields_currentIndexChanged(int);

private slots:


private:
    Ui::Search_Settings_Dlg *ui;
    QString tableName;
    PblTableView * view;
    PblSqlRelationalTableModel *mdl;

};

#endif // SEARCH_SETTINGS_DLG

