This is Beta version 4.0. 
Fork QSqlTableModel and QTableView based on Qt 4.8.1

There is test application, that is working with SQLite3.

Main idea is realize wrapper above QSqlTableModel and QTableView, that have convenient relations fields, calculated fields and more ...!

This is free and opensource project (GPL license).

We are created PblSqlRelationalTableModel class inherited by QSqlTableModel.

sql_pbl directory contains classes of data model.

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
translateFieldNames;
relationField;

In future we dont concern about how to get id relation value because of this forever present into extended hidden field.

Base idea: class PblSqlRelationalTableModel adds to resulting table new extended fields that are not existing by default in the select sql query from a database. 
This is id field of relations, calculated fields (any data from other tables).

PblSqlRelationalTableModel let us setting field alignments, precisions (for double value). 

We added our own PblColumn class for convenient.

Next we created PblTableView class inherited by QTableView (view model).

PblTableView adds tool buttons for easy operations as insert, edit, remove rows.

PblTableView class is used funtionality of PblSqlRelationalTableModel.

PblTableView can search some text by all columns , including relation fields.

Also PblTableView class can select rows by certain field value.

PblSqlRelationalTableModel and PblTableView classes support all three Qt edit strategies. 

You can test it with our windows application (PblTableView.exe).

Our wrapper support three languages en, ru, zh. You can add wanted languages.

![image](https://user-images.githubusercontent.com/13850002/208103235-e752247a-e531-4d47-a54f-6eecfe9dba16.png)

![image](https://user-images.githubusercontent.com/13850002/208103476-d2d0c17a-2cbb-48bf-bfeb-b6c1bea4bc32.png)

![image](https://user-images.githubusercontent.com/13850002/205646576-f0c004a9-db6f-407a-b394-34aab209ea72.png)

![2022-12-08_19-44-00](https://user-images.githubusercontent.com/13850002/206512485-8a64e237-a8d8-4f55-8650-1a4c5968e0e7.png)

PblSqlRelationalTableModel + PblTableView are convinient template (wrapper) for quick creating database table structure.

For russian we have site https://kkmspb.ru/development/Qt/database-sql/Fork-Sql/

