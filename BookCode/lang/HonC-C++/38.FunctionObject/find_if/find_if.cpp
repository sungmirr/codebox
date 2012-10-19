/*++
    2012.10.17

    38.�Լ���ü, �˰����� ����(658p) 

    - find�� �ݺ��ڰ��� �� ��° �μ��� ������ ���� ==�����ڷ� ��
    - find_if�� �Լ���ü�� ��Ҹ� ���� ��
      InIt find_if(InIt first, InIt last, UniPred F);
      bool�� �����ϴ� �Լ���ü�� ������(Predicate)��� �Ѵ�
--*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct IsKim
{
    bool operator()(const string &name) const       // stirng�� ū ��ü�̹Ƿ� ������ ���� ������ ������尡 ũ��
    {                                               // �׷��� ���۷����� ���޹޴´�, int���� �ܼ� Ÿ���� �������̳� ���۷��������̳� �����̾���
        //return (strncmp(name.c_str(),"��",2) == 0 );
        return (name.compare(0,2,"��",2)==0);
    }
};

void main()
{
    string names[]={"�̼���","���﹮","�庸��","������",
        "�ż���","��ȫ��","������","�̼���","������","������"};
    vector<string> vs(&names[0],&names[10]);
    vector<string>::iterator it;

    it = find_if(vs.begin(), vs.end(), IsKim());
    if (it==vs.end()) 
        cout << "����." << endl;
    else 
        cout << *it << "��(��) �ִ�." << endl;

 
    // ��� �谡 ã��
    cout << "------------------------------\n";
    for(it=vs.begin(); ; ++it)
    {
        it=find_if(it, vs.end(), IsKim());
        if(it==vs.end())    break;
        cout << *it << endl;
    }
}