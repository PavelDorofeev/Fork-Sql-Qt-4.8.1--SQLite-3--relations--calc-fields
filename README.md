This is a development of QSqlTableModel and QTableView classes made on Qt 4.8.1 . Beta version 9.0.x.x 

This project is a free and opensource project (GPL license).

The main idea is to implement a shell over QSqlTableModel and QTableView, which has convenient link fields, calculated fields and much more, a list box, a checkbox, date fields,... And all this is configured in one config.cpp file.

We created the PblSqlRelationalTableModel class inherited from QSqlTableModel. 


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

In the future, we don't worry about how to get the value of the id relation, because it is always present in the extended hidden field.

The main idea: The PblSqlRelationalTableModel class adds new extended fields to the resulting table, which by default do not exist in the select sql query from the database. 
This is the link ID field, calculated fields (any data from other tables)

PblSqlRelationalTableModel let us setting field alignments, precisions (for double value). 

Next we created PblTableView class inherited by QTableView (view model).

PblTableView adds tool buttons for easy operations as insert, edit, remove rows.

PblTableView class is used funtionality of PblSqlRelationalTableModel.

PblTableView can search some text by all columns , including relation fields.

Also PblTableView class can select rows by certain field value.

PblSqlRelationalTableModel and PblTableView classes support all three Qt edit strategies. 

You can test it with our windows application (PblTableView.exe).

Our wrapper support three languages en, ru, zh. You can add wanted languages.

Our classes support all three editing strategies.

There is a test application, that is working with SQLite3. 

![image](https://user-images.githubusercontent.com/13850002/224092105-3db143f7-ac30-4af7-8527-7caaff401d68.png)


![image](https://user-images.githubusercontent.com/13850002/224092221-d4ff4ce9-64c0-45b0-a2b1-2388a783ad75.png)

![image](https://user-images.githubusercontent.com/13850002/224092294-0f924a9b-2d12-491f-83c5-017e204cb691.png)


PblSqlRelationalTableModel + PblTableView are convinient template (wrapper) for quick creating database table structure.

PblTableDlg is universal table dialog with control buttons that contains PblSqlRelationalTableModel and PblTableView.

You can inherit PblTableDlg (with PblSqlRelationalTableModel and PblTableView inside) and than reimplement any virtual functions (PblTableDlg , PblSqlRelationalTableModel and PblTableView) but look at protected constructor which used as PblTableDlg( new ..., new ..., ...). It is important. 

We have a site https://kkmspb.ru/development/Qt/database-sql/Fork-Sql/ (ru)

Basic idea is in a reimplementation function selectStatement that generated query to db. And second idea id to add new function translateFieldNames that clear and replace some fields name and its value before update or insert into table. 
![image](https://user-images.githubusercontent.com/13850002/221420422-6b88a03d-884c-45ad-ab08-4c0005a55bac.png)

We add second level of abstration our development - class PblSqlRelationalTableModel2. This is adds internal operations into table with binding fields, i.g. price*qty=price. PblSqlRelationalTableModel2 inherited form PblSqlRelationalTableModel. 

Demo video on youtube: https://youtu.be/vUrVNU1h_rY

Setting relation is easy and just call one function:
setRelation( PblSqlRelation( mdl->baseRec.indexOf("productName"),
							"goods" ,
							"id" ,
							"productName") );

Binding tow relation columns for sub accounting needs call one function:

setSubAccount( mdl->fieldIndex("productName") ,
	mdl->fieldIndex("sub"),
	"goods_id",
	"sub_on");
  

