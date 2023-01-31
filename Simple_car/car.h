#include <string>
#include <mysql.h>
using namespace std;

int sum_all_car();//车辆总和
float sum_all_mileage();//里程总和
void found_car();//根据司机查找汽车

//删除函数的辅助函数
string delete_driver(string str);
string delete_num(string str);

//菜单函数
int menu();
void after_menu(int);
void showdata();
void show_single();
void add_data();
void delete_data();

class car{
private:
    int no;//编号  column[0]
    string head_num;//头车牌号  column[1]
	string tail_num;//尾车牌号  column[2]
    string driver;//司机  column[3]
    string brand;//品牌  column[4]
    float mileage;//里程  column[5]
    float price;//价格  column[6]
public:
	void sum_mileage(string str);//单车型里程和
	void sum_price(string str);//单车型资产价值总和
	void sum_driver(string str);//单车型司机人数总和
	void sum_car(string str);//单车型车辆总和
	void add_car(string str);//单车型增加车信息
	void delete_car(string str);//单车型删除车辆信息
	bool connectsql(string str);//数据展示
};
//越野车
class suv:public car{
public:
	void sum_mileage();
	void sum_price();
	void sum_driver();
	void sum_car();
	void add_car();
	void delect_car();
	void connectsql();
};
//公交车
class bus:public car{
public:
	void sum_mileage();
	void sum_price();
	void sum_driver();
	void sum_car();
	void add_car();
	void delect_car();
	void connectsql();
};
//卡车
class truck:public car{
public:
	void sum_mileage();
	void sum_price();
	void sum_driver();
	void sum_car();
	void add_car();
	void delect_car();
	void connectsql();
};
//三厢车
class saloon:public car{
public:
	void sum_mileage();
	void sum_price();
	void sum_driver();
	void sum_car();
	void add_car();
	void delect_car();
	void connectsql();
};
//面包车
class van:public car{
public:
	void sum_mileage();
	void sum_price();
	void sum_driver();
	void sum_car();
	void add_car();
	void delect_car();
	void connectsql();
};
