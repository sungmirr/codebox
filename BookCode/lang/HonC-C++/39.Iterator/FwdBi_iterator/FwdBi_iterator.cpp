/*++
    2012.10.19

    39.�ݺ���, ������ݺ���, �����ݺ��� (701p)
    
    Foward Iterator
    - ����� ��� ����
    - ++���� ����
    - --���� �Ұ���
    - ����¹ݺ��ڿ� �ٸ����� ���� ��ġ�� ������ �а� ���� �ִ�
    - ex) search�˰���, �˻���󱸰��� ������ ��ġ�ϴ� �κ��� ã�� ������ �����̳��� �� ��Ҹ� ������ ����
          strstr�Լ��� ������ ����
    - ��� STL �����̳ʰ� ����
    

    Bidirectional Iterator
    - ++����, --���� ����
    - list�� �����ݺ��� ����

    void replace(FwdIt first, FwdIt last, const Type& Old, const Type& New);
    void reverse(BiIt first, BiIt last);

--*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename C>
void dump(const char *desc, C &c)
{
    cout.width(12);
    cout << left << desc << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout," "));
    cout << endl;
}

void main()
{
    int ari[]={78,85,95,93,86,60,72,99,56,85};
    vector<int> vi(&ari[0],&ari[10]);

    dump("����", vi);
    replace(vi.begin(), vi.end(), 85, 100);
    dump("��ü��",vi);
    reverse(vi.begin(), vi.end());
    dump("��������",vi);
}