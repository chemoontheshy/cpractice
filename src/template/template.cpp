/**
 * @MachineName:$machinename$
 * @ProjectName:$projectname$
 * @ClassName: 
 * @Description: 
 * @Author: chemoontheshy
 * @Date: $time$
 */
#include <iostream>
using namespace std;

struct Person
{
	string	name;
	int		age;
};

int main() {
	//char carrots[20];
	//cout << "How many carrots do you have?" << endl;
	//cin.getline(carrots,20);
	//cout << "You have " << carrots <<" carrots." << endl;
	//int months[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	//cout << months[5] << endl;
	//char 
	//cout << UINT16_MAX << endl;
	//Person zhangsan;
	//zhangsan.age = 17;
	//zhangsan.name = "张三";
	//cout << zhangsan.name << "的年龄是" << zhangsan.age <<"岁。" << endl;
	
	//int tell[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//cout << tell[9] << endl;
	//cout << tell[0] << endl;
	//cout << &tell[0] << endl;
	//cout << &tell << endl;

	char animal[20] = "bear";
	const char* bird = "wren";
	char* ps;
	cout << animal << " and ";
	cout << bird << endl;
	//cout <<ps<<"\n"
	cout << animal << " at " << (int*)animal << endl;
	cout << " Enter a kind of animal: ";
	cin >> animal;
	ps = animal;
	cout << ps << "!\n";
	cout << " Before using strcpy():\n";
	cout << animal << " at " << (int*)animal << endl;
	cout << ps << " at " << (int*)ps << endl;
	ps = new char[strlen(animal) + 1];
	strcpy_s(ps, strlen(animal) + 1, animal);
	cout << "After using strcpy():\n";
	cout << animal << " at " << (int*)animal << endl;
	cout << ps << " at " << (int*)ps << endl;
	delete[] ps;
	return 0;
}