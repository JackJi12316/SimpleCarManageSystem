#include <string>
#include <mysql.h>
using namespace std;

int sum_all_car();//�����ܺ�
float sum_all_mileage();//����ܺ�
void found_car();//����˾����������

//ɾ�������ĸ�������
string delete_driver(string str);
string delete_num(string str);

//�˵�����
int menu();
void after_menu(int);
void showdata();
void show_single();
void add_data();
void delete_data();

class car{
private:
    int no;//���  column[0]
    string head_num;//ͷ���ƺ�  column[1]
	string tail_num;//β���ƺ�  column[2]
    string driver;//˾��  column[3]
    string brand;//Ʒ��  column[4]
    float mileage;//���  column[5]
    float price;//�۸�  column[6]
public:
	void sum_mileage(string str);//��������̺�
	void sum_price(string str);//�������ʲ���ֵ�ܺ�
	void sum_driver(string str);//������˾�������ܺ�
	void sum_car(string str);//�����ͳ����ܺ�
	void add_car(string str);//���������ӳ���Ϣ
	void delete_car(string str);//������ɾ��������Ϣ
	bool connectsql(string str);//����չʾ
};
//ԽҰ��
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
//������
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
//����
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
//���ᳵ
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
//�����
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
