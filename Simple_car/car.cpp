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
	//��ʼ�����ݿ����Ӿ��
	MYSQL_RES *res;
	MYSQL_ROW column;
	string sqlstr="select * from ";
	sqlstr+=str;
    con = mysql_init(NULL);

    if(con==NULL){
        printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
        return false;
    }
	//�������ݿ�
    if(mysql_real_connect(con, "localhost", "root", "123456", "car", 3306,0, 0)==NULL){
        printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
        return false;
    }
	//�������ݿⷵ��ֵ�����ʽ
	if(mysql_set_character_set(con,"GBK")){ 
		printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
		return false;
	} 
	
	//ִ��sql��䣬����ֵΪbool
	if (mysql_query(con,sqlstr.c_str())!=0) {
        printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
		return false;
	}
	//���sql�������󷵻صĽ����
	if (!(res = mysql_store_result(con))){
		printf("Couldn't get result from %s\n", mysql_error(con));
		return false;
	}
	//����һ���ַ�������洢�ֶ���Ϣ
	char *str_field[32];
	//����֪�ֶ�����������»�ȡ�ֶ���
	for (int i = 0; i < 7; i++) {
		//����һ�������ֶνṹ�����顣
		str_field[i] = mysql_fetch_field(res)->name;
	}
	cout<<"***************************************************************************************************************"<<endl;
	//��ӡ�ֶ�
	for (int i = 0; i < 7; i++)  
		printf("%10s\t", str_field[i]);
	printf("\n");
	cout<<endl;
	cout<<endl;
	//��ӡ��ȡ������
	//����֪�ֶ���������£���ȡ����ӡ��һ��
	while (column = mysql_fetch_row(res))  
	{
		printf("%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", 
			column[0], column[1], column[2], column[3], column[4], column[5], column[6]);//column��������  
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

	//�������ݿ�

	conn = mysql_init(NULL);//��ʼ�����
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);//�������ݿ�
	mysql_set_character_set(conn,"GBK");//���ñ����ʽ
	mysql_query(conn,"set names gbk");//���÷���ֵ�����ʽ

	//��ѯ����
	for(i=0;i<=4;i++){
		sqlstr="select count(*) from ";
		sqlstr+=table_name[i];
		mysql_query(conn, sqlstr.c_str());
		res = mysql_store_result(conn);
		while(column=mysql_fetch_row(res)){
			count++;
		}
	}
	//���ݿ�ر�
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

	//�������ݿ�

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

	//���ݿ�ر�
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
	cout<<"                                  "<<"����˾���������в�ѯ����"<<endl;
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
	
	
	//�������ݿ�

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);
	mysql_set_character_set(conn,"GBK");
	mysql_query(conn,"set names gbk");

	
	//���в�ѯ
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
		//����֪�ֶ�����������»�ȡ�ֶ���
		for (int i = 0; i < 7; i++) {
			//����һ�������ֶνṹ�����顣
			str_field[i] = mysql_fetch_field(res)->name;
		}
		cout<<"***************************************************************************************************************"<<endl;
		//��ӡ�ֶ�
		for (int i = 0; i < 7; i++)  
			printf("%10s\t", str_field[i]);
		printf("\n");
		cout<<endl;
		cout<<endl;
		//��ӡ��ȡ������
		//����֪�ֶ���������£���ȡ����ӡ��һ��
		cout<<"-------------����Ϊ"<<table_name[i]<<endl;
		while(j<mysql_num_rows(res)){
			printf("%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", 
				column[0], column[1], column[2], column[3], column[4], column[5], column[6]);//column��������
			j++;
		}
		cout<<"***************************************************************************************************************"<<endl;
		}

	//���ݿ�ر�
	mysql_free_result(res);
	mysql_close(conn);
	cout<<endl;
	cout<<endl;
	cout<<"                         "<<"����1���ز˵�,�������˳�:";
	cin>>n;
	if(n==1){after_menu(menu());}
}
//Car
void car::sum_mileage(string str){
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	
	//�������ݿ�

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);
	mysql_set_character_set(conn,"GBK");
	mysql_query(conn,"set names gbk");

	string sqlstr="select SUM(mileage) from ";
	sqlstr+=str;

	mysql_query(conn, sqlstr.c_str());
	res = mysql_store_result(conn);

	while(column=mysql_fetch_row(res)){
		cout<<"-----------------���������(km)Ϊ"<<atof(column[0])<<endl;
	
	}

	//���ݿ�ر�

	mysql_free_result(res);
	mysql_close(conn);
}

void car::sum_price(string str){
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	
	//�������ݿ�

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);
	mysql_set_character_set(conn,"GBK");
	mysql_query(conn,"set names gbk");

	string sqlstr="select SUM(price) from ";
	sqlstr+=str;

	mysql_query(conn, sqlstr.c_str());
	res = mysql_store_result(conn);

	while(column=mysql_fetch_row(res)){
		cout<<"-----------------�����ܼ�ֵ(��Ԫ)Ϊ"<<atof(column[0])<<endl;
	}

	//���ݿ�ر�
	mysql_free_result(res);
	mysql_close(conn);
}

void car::sum_driver(string str){
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	
	//�������ݿ�

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);
	mysql_set_character_set(conn,"GBK");
	mysql_query(conn,"set names gbk");

	string sqlstr="select DISTINCT count(driver) from ";
	sqlstr+=str;

	mysql_query(conn, sqlstr.c_str());
	res = mysql_store_result(conn);

	while(column=mysql_fetch_row(res)){
		cout<<"-----------------˾������Ϊ"<<atof(column[0])<<endl;
	}

	//���ݿ�ر�
	mysql_free_result(res);
	mysql_close(conn);
	
}

void car::sum_car(string str){
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;
	string sqlstr;
	int count=0;

	//�������ݿ�

	conn = mysql_init(NULL);//��ʼ�����
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);//�������ݿ�
	mysql_set_character_set(conn,"GBK");//���ñ����ʽ
	mysql_query(conn,"set names gbk");//���÷���ֵ�����ʽ

	//��ѯ����
	sqlstr="select * from ";
	sqlstr+=str;
	mysql_query(conn, sqlstr.c_str());
	res = mysql_store_result(conn);
	count=mysql_num_rows(res);

	//���ݿ�ر�
	mysql_free_result(res);
	mysql_close(conn);
	cout<<"-----------------��������Ϊ"<<count<<endl;
}

void car::add_car(string str){
	system("cls");
	MYSQL* conn=NULL;
	MYSQL_RES *res;
	MYSQL_ROW column;

	//�������ݿ�

	conn = mysql_init(NULL);//��ʼ�����
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);//�������ݿ�
	mysql_set_character_set(conn,"GBK");//���ñ����ʽ
	mysql_query(conn,"set names gbk");//���÷���ֵ�����ʽ

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
	cout<<"                                     "<<"�������ݲ���:"<<str<<endl;
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

	


	//�������ݿ�

	conn = mysql_init(NULL);//��ʼ�����
	mysql_real_connect(conn, "localhost", "root", "123456", "car", 3306,0, 0);//�������ݿ�
	mysql_set_character_set(conn,"GBK");//���ñ����ʽ
	mysql_query(conn,"set names gbk");//���÷���ֵ�����ʽ

	int n=0;
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                     "<<"�������ݲ���:"<<str<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************"<<endl;
	cout<<endl;
	cout<<"���ݳ��ƺ�ɾ������--input '1'"<<endl;
	cout<<"����˾������ɾ����Ϣ--input '2'"<<endl;
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
	cout<<"                                 "<<"���ݳ��ƺŽ���ɾ�����ݲ���:"<<str<<endl;
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
	cout<<"                                   "<<"����˾������ɾ�����ݲ���:"<<str<<endl;
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
	cout<<"                         "<<"1.�鿴ĳ�ֳ��͵����ݱ�"<<endl;
	cout<<"                         "<<"2.�鿴����ͳ������"<<endl;
	cout<<"                         "<<"3.����˾�����ֲ�ѯ�����Ϣ"<<endl;
	cout<<"                         "<<"4.��������"<<endl;
	cout<<"                         "<<"5.ɾ������"<<endl;
	cout<<"                         "<<"���������˳�"<<endl;
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
	cout<<"                                 "<<"���ڲ鿴ĳ�ֳ��͵���������"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<endl;
	cout<<"                         "<<"1.�鿴suv�����ݱ�"<<endl;
	cout<<"                         "<<"2.�鿴bus�����ݱ�"<<endl;
	cout<<"                         "<<"3.�鿴saloon�����ݱ�"<<endl;
	cout<<"                         "<<"4.�鿴truck�����ݱ�"<<endl;
	cout<<"                         "<<"5.�鿴van�����ݱ�"<<endl;
	cout<<"                         "<<"0.���ز˵�"<<endl;
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
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){showdata();}
		break;
	case 2:
		b.connectsql();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){showdata();}
		break;
	case 3:
		sl.connectsql();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){showdata();}
		break;
	case 4:
		t.connectsql();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){showdata();}
		break;
	case 5:
		v.connectsql();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
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
	cout<<"                           "<<"���ڲ鿴ĳ�ֳ��͵ĵ���������"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<endl;
	cout<<"                         "<<"1.�鿴suv���������"<<endl;
	cout<<"                         "<<"2.�鿴bus���������"<<endl;
	cout<<"                         "<<"3.�鿴saloon���������"<<endl;
	cout<<"                         "<<"4.�鿴truck���������"<<endl;
	cout<<"                         "<<"5.�鿴van���������"<<endl;
	cout<<"                         "<<"6.�鿴�����������������"<<endl;
	cout<<"                         "<<"0.���ز˵�"<<endl;
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
		cout<<"                               "<<"����SUV������չʾ"<<endl;
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
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 2:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"                                "<<"����BUS������չʾ"<<endl;
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
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 3:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"                                  "<<"����Saloon������չʾ"<<endl;
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
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 4:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"                                 "<<"����Truck������չʾ"<<endl;
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
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 5:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"                                   "<<"����Van������չʾ"<<endl;
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
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){show_single();}
		break;
	case 6:
		system("cls");
		cout<<endl;
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<endl;
		cout<<"----------------------��˾��������Ϊ  "<<sum_all_car()<<"  -----------------------------"<<endl;
		cout<<"----------------------��˾���������(km)Ϊ  "<<sum_all_mileage()<<"  -----------------------------"<<endl;
		cout<<endl;
		cout<<"*******************************************************************************************************"<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
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
	cout<<"                                   "<<"���ڲ鿴ĳ�ֳ��͵���������"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<endl;
	cout<<"                         "<<"1.������ݵ�SUV"<<endl;
	cout<<"                         "<<"2.������ݵ�BUS"<<endl;
	cout<<"                         "<<"3.������ݵ�Saloon"<<endl;
	cout<<"                         "<<"4.������ݵ�Truck"<<endl;
	cout<<"                         "<<"5.������ݵ�Van"<<endl;
	cout<<"                         "<<"0.���ز˵�"<<endl;
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
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){add_data();}
		break;
	case 2:
		b.add_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){add_data();}
		break;
	case 3:
		sl.add_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){add_data();}
		break;
	case 4:
		t.add_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){add_data();}
		break;
	case 5:
		v.add_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
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
	cout<<"                                  "<<"����ɾ��ĳ�ֳ��͵����ݲ���"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"*******************************************************************************************************"<<endl;
	cout<<endl;
	cout<<"                         "<<"1.ɾ��һ��SUV����"<<endl;
	cout<<"                         "<<"2.ɾ��һ��BUS����"<<endl;
	cout<<"                         "<<"3.ɾ��һ��Saloon����"<<endl;
	cout<<"                         "<<"4.ɾ��һ��Truck����"<<endl;
	cout<<"                         "<<"5.ɾ��һ��Van����"<<endl;
	cout<<"                         "<<"0.���ز˵�"<<endl;
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
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	case 2:
		b.delect_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	case 3:
		sl.delect_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	case 4:
		t.delect_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	case 5:
		v.delect_car();
		cout<<endl;
		cout<<endl;
		cout<<"                         "<<"����1������һ��,�������˳�:";
		cin>>n;
		if(n==1){delete_data();}
		break;
	default:delete_data();
	}
}