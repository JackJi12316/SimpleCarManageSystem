#include <winsock2.h>
#include <Windows.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib, "ws2_32.lib")
#include "car.h"
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;


string table_name[5]={"bus","suv","truck","saloon","van"};



bool car::connectsql(string str){
	system("cls");
	MYSQL* con;
	//初始化数据库连接句柄
	MYSQL_RES *res;
	MYSQL_ROW column;
	string sqlstr="select * from ";
	sqlstr+=str;
    con = mysql_init(NULL);

    if(con==NULL){
        printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
        return false;
    }
	//连接数据库
    if(mysql_real_connect(con, "localhost", "root", "123456", "car", 3306,0, 0)==NULL){
        printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
        return false;
    }
	//设置数据库返回值编码格式
	if(mysql_set_character_set(con,"GBK")){ 
		printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
		return false;
	} 
	
	//执行sql语句，返回值为bool
	if (mysql_query(con,sqlstr.c_str())!=0) {
        printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
		return false;
	}
	//获得sql语句结束后返回的结果集
	if (!(res = mysql_store_result(con))){
		printf("Couldn't get result from %s\n", mysql_error(con));
		return false;
	}
	//定义一个字符串数组存储字段信息
	char *str_field[32];
	//在已知字段数量的情况下获取字段名
	for (int i = 0; i < 7; i++) {
		//返回一个所有字段结构的数组。
		str_field[i] = mysql_fetch_field(res)->name;
	}
	cout<<"***************************************************************************************************************"<<endl;
	//打印字段
	for (int i = 0; i < 7; i++)  
		printf("%10s\t", str_field[i]);
	printf("\n");
	cout<<endl;
	cout<<endl;
	//打印获取的数据
	//在已知字段数量情况下，获取并打印下一行
	while (column = mysql_fetch_row(res))  
	{
		printf("%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", 
			column[0], column[1], column[2], column[3], column[4], column[5], column[6]);//column是列数组  
	}
	cout<<"***************************************************************************************************************"<<endl;
	
	return true;
}



int sum_all_car(){
	int i;
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	string sqlstr;
	int count=0;

	//连接数据库

	conn = mysql_init(NULL);//初始化句柄
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);//连接数据库
	mysql_set_character_set(conn,"GBK");//设置编码格式
	mysql_query(conn,"set names gbk");//设置返回值编码格式

	//查询操作
	for(i=0;i<=4;i++){
		sqlstr="select count(*) from ";
		sqlstr+=table_name[i];
		mysql_query(conn, sqlstr.c_str());
		res = mysql_store_result(conn);
		while(column=mysql_fetch_row(res)){
			count++;
		}
	}
	//数据库关闭
	mysql_free_result(res);
	mysql_close(conn);
	return count;
}

float sum_all_mileage(){
	float count=0;
	int i;
	string sqlstr;
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;

	//连接数据库

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);
	mysql_set_character_set(conn,"GBK");
	mysql_query(conn,"set names gbk");

	for(i=0;i<=4;i++){
		sqlstr="select * from ";
		sqlstr+=table_name[i];
		mysql_query(conn, sqlstr.c_str());
		res = mysql_store_result(conn);
		while(column=mysql_fetch_row(res)){
			count+=atof(column[5]);
		}
	}

	//数据库关闭
	mysql_free_result(res);
	mysql_close(conn);

	return count;
}

void found_car(){
	system("cls");
	int i,n=0,j=0;
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	string sqlstr;
	string sqlstrl;
	string driver1;
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                  "<<"根据司机姓名进行查询操作"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"-----------------------------------------"<<endl;
	cout<<"Please input driver's name:";
	cin>>driver1;
	sqlstrl=" where driver='";
	sqlstrl+=driver1;
	sqlstrl+="'";
	cout<<"-----------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	
	
	//连接数据库

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);
	mysql_set_character_set(conn,"GBK");
	mysql_query(conn,"set names gbk");

	
	//进行查询
	for(i=0;i<=4;i++){
		res=NULL;
		sqlstr="select * from ";
		sqlstr+=table_name[i];
		sqlstr+=sqlstrl;
		mysql_query(conn, sqlstr.c_str());
		res = mysql_store_result(conn);
		column = mysql_fetch_row(res);
		if(column==NULL){
			continue;
		}
		char *str_field[32];
		//在已知字段数量的情况下获取字段名
		for (int i = 0; i < 7; i++) {
			//返回一个所有字段结构的数组。
			str_field[i] = mysql_fetch_field(res)->name;
		}
		cout<<"***************************************************************************************************************"<<endl;
		//打印字段
		for (int i = 0; i < 7; i++)  
			printf("%10s\t", str_field[i]);
		printf("\n");
		cout<<endl;
		cout<<endl;
		//打印获取的数据
		//在已知字段数量情况下，获取并打印下一行
		cout<<"-------------车型为"<<table_name[i]<<endl;
		while(j<mysql_num_rows(res)){
			printf("%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", 
				column[0], column[1], column[2], column[3], column[4], column[5], column[6]);//column是列数组
			j++;
		}
		cout<<"***************************************************************************************************************"<<endl;
		}

	//数据库关闭
	mysql_free_result(res);
	mysql_close(conn);
	cout<<endl;
	cout<<endl;
	cout<<"                         "<<"输入1返回菜单,其他键退出:";
	cin>>n;
	if(n==1){after_menu(menu());}
}
//Car
void car::sum_mileage(string str){
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	
	//连接数据库

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);
	mysql_set_character_set(conn,"GBK");
	mysql_query(conn,"set names gbk");

	string sqlstr="select SUM(mileage) from ";
	sqlstr+=str;

	mysql_query(conn, sqlstr.c_str());
	res = mysql_store_result(conn);

	while(column=mysql_fetch_row(res)){
		cout<<"-----------------车辆总里程(km)为"<<atof(column[0])<<endl;
	
	}

	//数据库关闭

	mysql_free_result(res);
	mysql_close(conn);
}

void car::sum_price(string str){
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	
	//连接数据库

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);
	mysql_set_character_set(conn,"GBK");
	mysql_query(conn,"set names gbk");

	string sqlstr="select SUM(price) from ";
	sqlstr+=str;

	mysql_query(conn, sqlstr.c_str());
	res = mysql_store_result(conn);

	while(column=mysql_fetch_row(res)){
		cout<<"-----------------车辆总价值(万元)为"<<atof(column[0])<<endl;
	}

	//数据库关闭
	mysql_free_result(res);
	mysql_close(conn);
}

void car::sum_driver(string str){
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	
	//连接数据库

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);
	mysql_set_character_set(conn,"GBK");
	mysql_query(conn,"set names gbk");

	string sqlstr="select DISTINCT count(driver) from ";
	sqlstr+=str;

	mysql_query(conn, sqlstr.c_str());
	res = mysql_store_result(conn);

	while(column=mysql_fetch_row(res)){
		cout<<"-----------------司机数量为"<<atof(column[0])<<endl;
	}

	//数据库关闭
	mysql_free_result(res);
	mysql_close(conn);
	
}

void car::sum_car(string str){
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	string sqlstr;
	int count=0;

	//连接数据库

	conn = mysql_init(NULL);//初始化句柄
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);//连接数据库
	mysql_set_character_set(conn,"GBK");//设置编码格式
	mysql_query(conn,"set names gbk");//设置返回值编码格式

	//查询操作
	sqlstr="select * from ";
	sqlstr+=str;
	mysql_query(conn, sqlstr.c_str());
	res = mysql_store_result(conn);
	count=mysql_num_rows(res);

	//数据库关闭
	mysql_free_result(res);
	mysql_close(conn);
	cout<<"-----------------车辆总数为"<<count<<endl;
}

void car::add_car(string str){
	system("cls");
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;

	//连接数据库

	conn = mysql_init(NULL);//初始化句柄
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);//连接数据库
	mysql_set_character_set(conn,"GBK");//设置编码格式
	mysql_query(conn,"set names gbk");//设置返回值编码格式

	string sqlstr="insert into ";
	string sqlstr2="(head_num,tail_num,driver,brand,mileage,price)";
	string sqlstrm=" values(";
	string c_head;
	string c_last;
	string driver;
	string brand;
	string mileage;
	string price;
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                     "<<"插入数据操作:"<<str<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"***************************************************************"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"input head_num:";cin>>c_head;
	cout<<"input last_num:";cin>>c_last;
	cout<<"input driver:";cin>>driver;
	cout<<"input brand:";cin>>brand;
	cout<<"input mileage:";cin>>mileage;
	cout<<"input pirce:";cin>>price;
	cout<<endl;
	cout<<endl;
	cout<<"***************************************************************"<<endl;
	sqlstr+=str;
	sqlstr+=sqlstr2;
	sqlstr+=sqlstrm;
	sqlstr+="'";
	sqlstr+=c_head;
	sqlstr+="'";
	sqlstr+=",";
	sqlstr+="'";
	sqlstr+=c_last;
	sqlstr+="'";
	sqlstr+=",";
	sqlstr+="'";
	sqlstr+=driver;
	sqlstr+="'";
	sqlstr+=",";
	sqlstr+="'";
	sqlstr+=brand;
	sqlstr+="'";
	sqlstr+=",";
	sqlstr+=mileage;
	sqlstr+=",";
	sqlstr+=price;
	sqlstr+=")";
	cout<<sqlstr;

	mysql_query(conn, sqlstr.c_str());

	cout<<"Add Data Success"<<endl;

	mysql_close(conn);
}

void car::delete_car(string str){
	system("cls");
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	string s;

	


	//连接数据库

	conn = mysql_init(NULL);//初始化句柄
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);//连接数据库
	mysql_set_character_set(conn,"GBK");//设置编码格式
	mysql_query(conn,"set names gbk");//设置返回值编码格式

	int n=0;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                     "<<"插入数据操作:"<<str<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************"<<endl;
	cout<<endl;
	cout<<"根据车牌号删除数据--input '1'"<<endl;
	cout<<"根据司机名字删除信息--input '2'"<<endl;
	cout<<endl;
	cout<<"*******************************************************"<<endl;
	cout<<"              "<<"please input:";
	cin>>n;
	system("cls");
	

	switch(n){
	case 1:s=delete_num(str);mysql_query(conn, s.c_str());cout<<"Delete Data Success!"<<endl;break;
	case 2:s=delete_driver(str);mysql_query(conn, s.c_str());cout<<"Delete Data Success!"<<endl;break;
	default:delete_car(str);
	}

	mysql_close(conn);

}

string delete_num(string str){
	string sqlstr="delete from ";
	sqlstr+=str;
	string head_num;
	string tail_num;
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                 "<<"根据车牌号进行删除数据操作:"<<str<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"------------------------------------------"<<endl;
	cout<<"input head_num";
	cin>>head_num;
	cout<<"input tail_num";
	cin>>tail_num;
	cout<<"------------------------------------------"<<endl;
	sqlstr+=" where head_num='";
	sqlstr+=head_num;
	sqlstr+="' and tail_num='";
	sqlstr+=tail_num;
	sqlstr+="'";
	return sqlstr;
}

string delete_driver(string str){
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                   "<<"根据司机进行删除数据操作:"<<str<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	string sqlstr="delete from ";
	sqlstr+=str;
	string driver2;
	cout<<"input driver";
	cin>>driver2;
	sqlstr+=" where driver='";
	sqlstr+=driver2;
	sqlstr+="'";
	return sqlstr;
}


//suv
void suv::sum_mileage(){
	string str="suv";
	car::sum_mileage(str);
}
void suv::sum_price(){
	string str="suv";
	car::sum_price(str);
}
void suv::sum_driver(){
	string str="suv";
	car::sum_driver(str);
}
void suv::sum_car(){
	string str="suv";
	car::sum_car(str);
}
void suv::add_car(){
	string str="suv";
	car::add_car(str);
}
void suv::delect_car(){
	string str="suv";
	car::delete_car(str);
}
void suv::connectsql(){
	string str="suv";
	car::connectsql(str);
}


//bus
void bus::sum_mileage(){
	string str="bus";
	car::sum_mileage(str);
}
void bus::sum_price(){
	string str="bus";
	car::sum_price(str);
}
void bus::sum_driver(){
	string str="bus";
	car::sum_driver(str);
}
void bus::sum_car(){
	string str="bus";
	car::sum_car(str);
}
void bus::add_car(){
	string str="bus";
	car::add_car(str);
}
void bus::delect_car(){
	string str="bus";
	car::delete_car(str);
}
void bus::connectsql(){
	string str="bus";
	car::connectsql(str);
}


//truck
void truck::sum_mileage(){
	string str="truck";
	car::sum_mileage(str);
}
void truck::sum_price(){
	string str="truck";
	car::sum_price(str);
}
void truck::sum_driver(){
	string str="truck";
	car::sum_driver(str);
}
void truck::sum_car(){
	string str="truck";
	car::sum_car(str);
}
void truck::add_car(){
	string str="truck";
	car::add_car(str);
}
void truck::delect_car(){
	string str="truck";
	car::delete_car(str);
}
void truck::connectsql(){
	string str="truck";
	car::connectsql(str);
}


//saloon
void saloon::sum_mileage(){
	string str="saloon";
	car::sum_mileage(str);
}
void saloon::sum_price(){
	string str="saloon";
	car::sum_price(str);
}
void saloon::sum_driver(){
	string str="saloon";
	car::sum_driver(str);
}
void saloon::sum_car(){
	string str="saloon";
	car::sum_car(str);
}
void saloon::add_car(){
	string str="saloon";
	car::add_car(str);
}
void saloon::delect_car(){
	string str="saloon";
	car::delete_car(str);
}
void saloon::connectsql(){
	string str="saloon";
	car::connectsql(str);
}


//van
void van::sum_mileage(){
	string str="van";
	car::sum_mileage(str);
}
void van::sum_price(){
	string str="van";
	car::sum_price(str);
}
void van::sum_driver(){
	string str="van";
	car::sum_driver(str);
}
void van::sum_car(){
	string str="van";
	car::sum_car(str);
}
void van::add_car(){
	string str="van";
	car::add_car(str);
}
void van::delect_car(){
	string str="van";
	car::delete_car(str);
}
void van::connectsql(){
	string str="van";
	car::connectsql(str);
}


int menu(){

	system("cls");
	
	int n=0;

	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                           "<<"welcome to Simple car management system"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<endl;
	cout<<"                         "<<"1.查看某种车型的数据表"<<endl;
	cout<<"                         "<<"2.查看车型统计数据"<<endl;
	cout<<"                         "<<"3.根据司机名字查询相关信息"<<endl;
	cout<<"                         "<<"4.增加数据"<<endl;
	cout<<"                         "<<"5.删除数据"<<endl;
	cout<<"                         "<<"按其他键退出"<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<"                         "<<"please input:";
	cin>>n;
	return n;
}

void after_menu(int x){

	switch(x){
	case 1:
		showdata();
		break;
	case 2:
		show_single();
		break;
	case 3:
		found_car();
		break;
	case 4:
		add_data();
		break;
	case 5:
		delete_data();
		break;
	default:exit(0);
	}
}

void showdata(){
	suv s;
	van v;
	saloon sl;
	truck t;
	bus b;
	int n=0;

	system("cls");
	int y;
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                 "<<"关于查看某种车型的所有数据"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<endl;
	cout<<"                         "<<"1.查看suv的数据表"<<endl;
	cout<<"                         "<<"2.查看bus的数据表"<<endl;
	cout<<"                         "<<"3.查看saloon的数据表"<<endl;
	cout<<"                         "<<"4.查看truck的数据表"<<endl;
	cout<<"                         "<<"5.查看van的数据表"<<endl;
	cout<<"                         "<<"0.返回菜单"<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<"                         "<<"please input:";
	cin>>y;
	switch(y){
	case 0:
		after_menu(menu());
		break;
	case 1:
		s.connectsql();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){showdata();}
		break;
	case 2:
		b.connectsql();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){showdata();}
		break;
	case 3:
		sl.connectsql();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){showdata();}
		break;
	case 4:
		t.connectsql();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){showdata();}
		break;
	case 5:
		v.connectsql();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){showdata();}
		break;
	default:showdata();
	}
}

void show_single(){
	system("cls");
	suv s;
	van v;
	saloon sl;
	truck t;
	bus b;
	int n=0;
	int y=0;

	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                           "<<"关于查看某种车型的单独的数据"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<endl;
	cout<<"                         "<<"1.查看suv的相关数据"<<endl;
	cout<<"                         "<<"2.查看bus的相关数据"<<endl;
	cout<<"                         "<<"3.查看saloon的相关数据"<<endl;
	cout<<"                         "<<"4.查看truck的相关数据"<<endl;
	cout<<"                         "<<"5.查看van的相关数据"<<endl;
	cout<<"                         "<<"6.查看所有汽车的相关数据"<<endl;
	cout<<"                         "<<"0.返回菜单"<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<"                         "<<"please input:";
	cin>>y;
	switch(y){
	case 0:
		after_menu(menu());
		break;
	case 1:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"                               "<<"关于SUV的数据展示"<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<endl;
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<endl;
		s.sum_car();
		s.sum_price();
		s.sum_mileage();
		s.sum_driver();
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 2:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"                                "<<"关于BUS的数据展示"<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<endl;
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<endl;
		b.sum_car();
		b.sum_price();
		b.sum_mileage();
		b.sum_driver();
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 3:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"                                  "<<"关于Saloon的数据展示"<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<endl;
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<endl;
		sl.sum_car();
		sl.sum_price();
		sl.sum_mileage();
		sl.sum_driver();
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 4:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"                                 "<<"关于Truck的数据展示"<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<endl;
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<endl;
		t.sum_car();
		t.sum_price();
		t.sum_mileage();
		t.sum_driver();
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 5:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"                                   "<<"关于Van的数据展示"<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<endl;
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<endl;
		v.sum_car();
		v.sum_price();
		v.sum_mileage();
		v.sum_driver();
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 6:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<endl;
		cout<<"----------------------公司车辆总数为  "<<sum_all_car()<<"  -----------------------------"<<endl;
		cout<<"----------------------公司车辆总里程(km)为  "<<sum_all_mileage()<<"  -----------------------------"<<endl;
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){show_single();}
		break;
	default:show_single();
	}
}

void add_data(){
	suv s;
	van v;
	saloon sl;
	truck t;
	bus b;
	int n=0;

	system("cls");
	int y;
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                   "<<"关于查看某种车型的所有数据"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<endl;
	cout<<"                         "<<"1.添加数据到SUV"<<endl;
	cout<<"                         "<<"2.添加数据到BUS"<<endl;
	cout<<"                         "<<"3.添加数据到Saloon"<<endl;
	cout<<"                         "<<"4.添加数据到Truck"<<endl;
	cout<<"                         "<<"5.添加数据到Van"<<endl;
	cout<<"                         "<<"0.返回菜单"<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<"                         "<<"please input:";
	cin>>y;
	switch(y){
	case 0:
		after_menu(menu());
		break;
	case 1:
		s.add_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){add_data();}
		break;
	case 2:
		b.add_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){add_data();}
		break;
	case 3:
		sl.add_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){add_data();}
		break;
	case 4:
		t.add_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){add_data();}
		break;
	case 5:
		v.add_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){add_data();}
		break;
	default:add_data();
	}
}

void delete_data(){
	suv s;
	van v;
	saloon sl;
	truck t;
	bus b;
	int n=0;

	system("cls");
	int y;
	cout<<endl;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                  "<<"进行删除某种车型的数据操作"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<endl;
	cout<<"                         "<<"1.删除一条SUV数据"<<endl;
	cout<<"                         "<<"2.删除一条BUS数据"<<endl;
	cout<<"                         "<<"3.删除一条Saloon数据"<<endl;
	cout<<"                         "<<"4.删除一条Truck数据"<<endl;
	cout<<"                         "<<"5.删除一条Van数据"<<endl;
	cout<<"                         "<<"0.返回菜单"<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<"                         "<<"please input:";
	cin>>y;
	switch(y){
	case 0:
		after_menu(menu());
		break;
	case 1:
		s.delect_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	case 2:
		b.delect_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	case 3:
		sl.delect_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	case 4:
		t.delect_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	case 5:
		v.delect_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"输入1返回上一步,其他键退出:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	default:delete_data();
	}
}