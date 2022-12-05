This is Beta version 3.0. Fork-Sql-Qt-4.8.1--SQLite-3--relations--calc-fields 2022г.

We are created PblSqlRelationalTableModel class inherited by QSqlTableModeland.

sql_pbl directory is building as part of Qt Soources 4.8.1 (with sql.pro). This is important.
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

Next we added PblSqlRelation and PblSqlRecord classes for support new functionality of PblSqlRelationalTableModel class.

Base idea: class PblSqlRelationalTableModel adds to resulting table new extended fields that are not existing in the database. 
This is id field of relations, calculated fields by data of other table.

Next we created PblTableView class inherited by QTableView.
PblTableView adds tool buttons for easy operations as insert, edit, remove rows.
PblTableView class  is used funtionality of PblSqlRelationalTableModel.
PblTableView can search some text by all columns , including relation fields.
Also PblTableView class can select rows by certain field value.

PblSqlRelationalTableModel and PblTableView classes support all Qt edit strategies. You can test it with our windows application (PblTableView.exe).

![image](https://user-images.githubusercontent.com/13850002/205646872-74742583-bde1-483e-9575-3bbc4d9578da.png)

![image](https://user-images.githubusercontent.com/13850002/205646946-abed5808-3518-4eca-a8d3-04a5678da9c4.png)

![image](https://user-images.githubusercontent.com/13850002/205646576-f0c004a9-db6f-407a-b394-34aab209ea72.png)



