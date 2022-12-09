This is Beta version 3.0. 
Fork Sql Qt 4.8.1 SQLite3 relations, calculated fields (2022г.)
Free and opensource project.

We are created PblSqlRelationalTableModel class inherited by QSqlTableModel.

sql_pbl directory is building as part of Qt Soources 4.8.1 (with sql.pro). This is important because of inherited by private Qt classes.
We are add new funtionality of Data Model - convinient extrenal relations, calculated field by other table and ...

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

Base idea: class PblSqlRelationalTableModel adds to resulting table new extended fields that are not existing by default in the select sql query from a database. 
This is id field of relations, calculated fields (any data from other tables).

Next we created PblTableView class inherited by QTableView.
PblTableView adds tool buttons for easy operations as insert, edit, remove rows.
PblTableView class is used funtionality of PblSqlRelationalTableModel.
PblTableView can search some text by all columns , including relation fields.
Also PblTableView class can select rows by certain field value.

PblSqlRelationalTableModel and PblTableView classes support all Qt edit strategies. You can test it with our windows application (PblTableView.exe).

![image](https://user-images.githubusercontent.com/13850002/205646872-74742583-bde1-483e-9575-3bbc4d9578da.png)

![image](https://user-images.githubusercontent.com/13850002/205646946-abed5808-3518-4eca-a8d3-04a5678da9c4.png)

![image](https://user-images.githubusercontent.com/13850002/205646576-f0c004a9-db6f-407a-b394-34aab209ea72.png)

![2022-12-08_19-44-00](https://user-images.githubusercontent.com/13850002/206512485-8a64e237-a8d8-4f55-8650-1a4c5968e0e7.png)


PblSqlRelationalTableModel + PblTableView are convinient template for create database table structure.

For russian we have site https://kkmspb.ru/development/Qt/database-sql/Fork-Sql/


