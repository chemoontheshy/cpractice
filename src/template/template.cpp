/**
 * @MachineName:$machinename$
 * @ProjectName:$projectname$
 * @ClassName: 
 * @Description: 
 * @Author: chemoontheshy
 * @Date: $time$
 */
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Person
{
	string	name;
	int		age;
};

const int yInt(int& num) 
{
	num++;
	return num;
}

void file_it(ostream& os, double fo, const double fe[], int n);

const int LIMIT = 5;

int main() {
	

	ofstream fout;
	const char* fn = "ep-data.txt";
	fout.open(fn);
	if (!fout.is_open())
	{
		cout << "Can't open " << fn << ". Bye." << endl;
		exit(EXIT_FAILURE);
	}
	double objective;
	cout << "Enter the focal length of your"
		"telescope objective in mm: ";
	cin >> objective;
	double eps[LIMIT];
	cout << "Enter the focal lengths, in mm of" << LIMIT << "eyepieces:\n";
	for (int i = 0; i < LIMIT; i++)
	{
		cout << "Eyepice #" << i + 1 << ": ";
		cin >> eps[i];
	}
	file_it(fout, objective, eps, LIMIT);
	file_it(cout, objective, eps, LIMIT);
	cout << "Done\n";
	return 0;
}

void file_it(ostream& os, double fo, const double fe[], int n)
{
	// ��־��ʽ
	ios_base::fmtflags initial;
	// ���ø��ָ�ʽ��״̬
	// ios_base::fixed ����������ʹ�ö����ʾ����ģʽ
	initial = os.setf(ios_base::fixed);
	// ָ����ʾ����λС��
	os.precision(0);
	os << "Focal length of objective: " << fo << "mm\n";
	// ������������ʾС�����ģʽ
	os.setf(ios::showpoint);
	// ָ����ʾ����λС��
	os.precision(1);
	// ������һ���������ʹ�õ��ֶο�ȣ�Ĭ��0
	os.width(12);
	os << "f.l. eyspiece";
	os.width(15);
	os << "magnification" << endl;
	for (int i = 0; i < n; i++)
	{
		os.width(12);
		os << fe[i];
		os.width(15);
		os << int(fo / fe[i] + 0.5) << endl;
	}
	os.setf(initial);
	///LIFL
	/*
	*
	* 
	*/

}