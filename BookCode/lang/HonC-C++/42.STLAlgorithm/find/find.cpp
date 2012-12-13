/*++
    2012. 10. 24

    InIt find(InIt first, InIt last, const T&val);
    - �Է� �ݺ��� �� ���� �˻� ��� ������ �����Ͽ� �˻�
    - �˻��� ���� ����° �μ��� ����
    - ==������ ���
    - val�� �߰ߵ��� ������ last�� ����
 --*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void main()
{
    string names[]={"������","��ȫ��","������",
        "�迵��","������","�ڹ̿�","������"};
    vector<string> as(&names[0],&names[7]);
    vector<string>::iterator it;

    it=find(as.begin(),as.end(),"�ȼ���");
    if (it==as.end()) 
        cout << "����" << endl;
    else 
        cout << "�ִ�" << endl;

    for(it=as.begin();; ++it)
    {
        it=find(it, as.end(), "������");
        if(it==as.end()) break;
        cout << *it << endl;
    }
}