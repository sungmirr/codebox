/*++
    2012.10.23

    40. ���������̳�, ���տ���(795p)

    ���տ���˰���
    - ������,������,������,��Ī������,���� ���� ���� ���� ���� ���� ��� ����
    - ���� �˰��� �Լ��� ������ �����̳ʿ� �Բ� ��� ����
    - �ش� �����̳ʴ� ȿ������ ������ ������ ���� �ݵ�� ���ĵ� ���·� ���
    


    // [first1~last1)�� [first2~last2)������ ���հ��� ������ ������ result�� ���
    // �Է¹ݺ������� �� ���� �ʿ� ���� ���ı� ���ͳ� ����Ʈ ������ ��밡��
    // result���� ������ �����̳ʿ� ������尡��, ����� ������ �ְų� back_inserter�� ���
    OutIt set_union(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt result);
    OutIt set_intersection(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt result);     
    OutIt set_difference(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt result);
    OutIt set_sysmmetric_difference(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt result);
    bool include(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2);         // �ιݺ��� ������ ���԰��迡 �ִ��� ����
--*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

template<typename C>
void dump(const char *desc, const C &c)
{
    cout.width(12);
    cout << left << desc << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " "));
    cout << endl;
}

void main()
{
    int i;
    int ar1[]={7,0,0,6,2,9,1,9,1,4,9,2,0};
    int ar2[]={9,1,7,6,0,0,4,0,5,1,8};
    set<int> s1;
    for (i=0;i<sizeof(ar1)/sizeof(ar1[0]);i++) {
        s1.insert(ar1[i]);
    }
    set<int> s2;
    for (i=0;i<sizeof(ar2)/sizeof(ar2[0]);i++) {
        s2.insert(ar2[i]);
    }


    vector<int> v;
    set_union(s1.begin(),s1.end(),s2.begin(),s2.end(),back_inserter(v));
    dump("������", v);

    v.clear();
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),back_inserter(v));
    dump("������", v);

    v.clear();
    set_difference(s1.begin(),s1.end(),s2.begin(),s2.end(),back_inserter(v));
    dump("������", v);

    v.clear();
    set_symmetric_difference(s1.begin(),s1.end(),s2.begin(),s2.end(),back_inserter(v));
    dump("��Ī��", v);
}