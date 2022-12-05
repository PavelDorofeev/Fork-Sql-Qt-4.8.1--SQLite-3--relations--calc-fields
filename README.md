# Fork-Sql-Qt-4.8.1--SQLite-3--relations--calc-fields
We are created PblSqlRelationalTableModel class inherited by QSqlTableModel

sql_pbl directory is building as part of Qt Soources 4.8.1 (with sql.pro).
This is add new funtionality of Data Model - convinient extrenal relations, calculated field by other table and ...

PblSqlRelationalTableModel overrides QSqlTableModel class functions:
setTable;
select;
setData;
updateRowInTable;
insertRowIntoTable;
selectStatment;
orderByClause;

We add functions like in the QSqlRelationalTableModel class for compatibility:
setRelation;

Class PblSqlRelationalTableModel adds to resulting table new extended fields that are not existing in the database.


