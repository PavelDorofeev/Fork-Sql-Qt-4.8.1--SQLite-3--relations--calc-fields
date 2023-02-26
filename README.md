This is a development of QSqlTableModel and QTableView classes made on Qt 4.8.1 . Beta version 9.0.x.x 

This is a free and opensource project (GPL license).

Main idea is realize wrapper above QSqlTableModel and QTableView, that has a convenient relations fields, calculated fields and more, combo box, chekbox , date fields,... And all this configure in one config.cpp file.

We are created PblSqlRelationalTableModel class inherited by QSqlTableModel. Our classes support all three edit strategies.

PblSqlRelationalTableModel overrides QSqlTableModel class functions:
setTable;
select;
flags;
data;
setData;
updateRowInTable;
insertRowIntoTable;
selectStatement;
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

There is a test application, that is working with SQLite3. 

![image](https://user-images.githubusercontent.com/13850002/208140021-5a0527c1-2024-4acd-ac59-29ec62b8a369.png)

![image](https://user-images.githubusercontent.com/13850002/208140613-5d76a0e8-590a-40e0-ac5c-f9262b415030.png)

PblSqlRelationalTableModel + PblTableView are convinient template (wrapper) for quick creating database table structure.

PblTableDlg is universal table dialog with control buttons that contains PblSqlRelationalTableModel and PblTableView.

You can inherit PblTableDlg (with PblSqlRelationalTableModel and PblTableView inside) and than reimplement any virtual functions (PblTableDlg , PblSqlRelationalTableModel and PblTableView) but look at protected constructor which used as PblTableDlg( new ..., new ..., ...). It is important. 

We have a site https://kkmspb.ru/development/Qt/database-sql/Fork-Sql/ (ru)

Basic idea is in a reimplementation function selectStatement that generated query to db. And second idea id to add new function translateFieldNames that clear and replace some fields name and its value before update or insert into table. 
![image](https://user-images.githubusercontent.com/13850002/221420422-6b88a03d-884c-45ad-ab08-4c0005a55bac.png)

We add second level of abstration our development - class PblSqlRelationalTableModel2. This is adds internal operations into table with binding fields, i.g. price*qty=price. PblSqlRelationalTableModel2 inherited form PblSqlRelationalTableModel. 


