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

![image](https://user-images.githubusercontent.com/13850002/208140021-5a0527c1-2024-4acd-ac59-29ec62b8a369.png)

![image](https://user-images.githubusercontent.com/13850002/208140613-5d76a0e8-590a-40e0-ac5c-f9262b415030.png)

PblSqlRelationalTableModel + PblTableView are convinient template (wrapper) for quick creating database table structure.

For russian we have site https://kkmspb.ru/development/Qt/database-sql/Fork-Sql/

