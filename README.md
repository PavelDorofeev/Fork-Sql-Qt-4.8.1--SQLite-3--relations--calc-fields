This is a development of QSqlTableModel and QTableView classes made on Qt 4.8.1 . Beta version 9.0.x.x 

This project is a free and opensource project (GPL license).

The main idea is to implement a shell over QSqlTableModel and QTableView, which has convenient link fields, calculated fields and much more, a list box, a checkbox, date fields,... And all this is configured in one config.cpp file.

We created the QpSqlTableModel class inherited from QSqlTableModel. 


QpSqlTableModel overrides QSqlTableModel class functions:
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

The main idea: The QpSqlTableModel class adds new extended fields to the resulting table, which by default do not exist in the select sql query from the database. 
This is the link ID field, calculated fields (any data from other tables)

QpSqlTableModel let us setting field alignments, precisions (for double value). 

Next we created QpTableView class inherited by QTableView (view model).

QpTableView adds tool buttons for easy operations as insert, edit, remove rows.

QpTableView class is used funtionality of QpSqlTableModel.

QpTableView can search some text by all columns , including relation fields.

Also QpTableView class can select rows by certain field value.

QpSqlTableModel and QpTableView classes support all three Qt edit strategies. 

You can test it with our windows application (QpTableView.exe).

Our wrapper support three languages en, ru, zh. You can add wanted languages.

Our classes support all three editing strategies.

There is a test application, that is working with SQLite3. 

![image](https://user-images.githubusercontent.com/13850002/224092105-3db143f7-ac30-4af7-8527-7caaff401d68.png)


![image](https://user-images.githubusercontent.com/13850002/224092221-d4ff4ce9-64c0-45b0-a2b1-2388a783ad75.png)

![image](https://user-images.githubusercontent.com/13850002/224092294-0f924a9b-2d12-491f-83c5-017e204cb691.png)


QpSqlTableModel + QpTableView are convinient template (wrapper) for quick creating database table structure.

QpTableDlg is universal table dialog with control buttons that contains QpSqlTableModel and QpTableView.

You can inherit QpTableDlg (with QpSqlTableModel and QpTableView inside) and than reimplement any virtual functions (QpTableDlg , QpSqlTableModel and QpTableView) but look at protected constructor which used as QpTableDlg( new ..., new ..., ...). It is important. 

We have a site https://kkmspb.ru/development/Qt/database-sql/Fork-Sql/ (ru)

Basic idea is in a reimplementation function selectStatement that generated query to db. And second idea id to add new function translateFieldNames that clear and replace some fields name and its value before update or insert into table. 
![image](https://user-images.githubusercontent.com/13850002/221420422-6b88a03d-884c-45ad-ab08-4c0005a55bac.png)

We add second level of abstration our development - class QpSqlTableModel2. This is adds internal operations into table with binding fields, i.g. price*qty=price. QpSqlTableModel2 inherited form QpSqlTableModel. 

Demo video on youtube: https://youtu.be/vUrVNU1h_rY

Setting relation is easy and just call one function:
setRelation( QpSqlRelation( "productName",
							"goods" ,
							"id" ,
							"productName") );

Binding tow relation columns for sub accounting needs call one function:

setSubAccount( productName" ,
	"sub",
	"goods_id",
	"sub_on");
  

