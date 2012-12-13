/*++
    2012.10.23

    40. ���������̳�, ��� ����(789p)

    set�� ����Լ� find�� �������(<������)���� �˻��� Ű�� ã�´�
    find�˰��� �Լ��� ���ϼ�(==������)���� �˻��� Ű�� ã�´�

    ���ϼ�(equality) 
    - ==�����ڻ��
    - �� ���� ������ ������ �˻�,��ü�� ��� ��� ����� ��ġ�ϴ��� �˻��Ҷ� ���

    ���(equivalent)
    - <�������� ����
    - !(a<b) && !(b<a)
    - !Comp(a,b) && !Comp(b,a)  // Comp�� ��������ǰ�ü
    - �� ���� ���� ������ �����Ǵ��� �˻�

    cf)int, double���� Ÿ���� ��ü ��ü�� Ű�̹Ƿ� ����� ���ϼ��� ������ �� ���� ���� ����ص� �������
       ��ü�� Ư�� ����� �ϳ��� Ű�� ����� ��� ���ϼ��� ����� �ٸ���

    cf)�����(<������)�� ���Ǵ� ��� ��������� Ű�̴�

--*/

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

class President
{
public:
    int Id;
    string Name;
    string Addr;

    President(int aId,char *aName, char *aAddr) 
        : Id(aId), Name(aName), Addr(aAddr) { }

    void OutPresident() 
    {
        printf("Id:%d, �̸�:%s, �ּ�:%s\n",Id,Name.c_str(),Addr.c_str());
    }

    // ���, find����Լ����� ���
    // Id������ ����, Id�� Ű
    bool operator<(const President &Other) const 
    {
        return Id < Other.Id;
    }

    // ���ϼ�, find�˰����Լ����� ���
    bool operator==(const President &Other) 
    {
        return (Id==Other.Id && Name==Other.Name && Addr==Other.Addr);
    }
};

void main()
{
    set<President> King;
    set<President>::iterator it;
    King.insert(President(516,"������","���۵�"));
    King.insert(President(1212,"����ȯ","����"));
    King.insert(President(629,"���¿�","����"));
    King.insert(President(3030,"�迵��","�󵵵�"));
    King.insert(President(1234,"�����","����"));

    for(it=King.begin(); it!=King.end(); ++it)
        (*it).OutPresident();


    President ZeroThree(3030,"�ƹ���","�ƹ�����");
    // ���find
    it = King.find(ZeroThree);
    if(it!=King.end())
    {
        cout << "�˻��Ǿ���" << endl;
        (*it).OutPresident(); 
    }

    // ����find
    it = find(King.begin(), King.end(), ZeroThree);
    if(it!=King.end())
    {
        cout << "�˻��Ǿ���" << endl;
        it->OutPresident();//(*it).OutPresident(); 
    }
}