/*++
    2012.10.19

    39.�ݺ���, ���Թݺ��� (713p)
    
    1-1 ���Թݺ��� Ÿ�� ����(Ŭ�������ø�)
    insert_iterator<Container> 
     - insert����Լ��� ����Ͽ� �߰��� ����
     - ��� �����̳ʿ��� ��� ����
     - ������ �μ��� �����̳ʿ� ���� ��ġ�� �����ϴ� �ݺ��� ����
    front_insert_iterator<Container> 
     - push_front����Լ��� ����� ���ο� ����
     - ����Ʈ, ��ũ���� ���, ���ʹ� ���Ұ�
    back_insert_iterator<Container>
     - push_back����Լ��� ����� ���� �߰�
     - ��� �����̳ʿ��� ��밡��



    1-2 ���Թݺ��ڸ� �����Ͽ� �����ϴ� ���ø��Լ�
    insert_iterator<Container> inserter(Container& Cont, Iterator it);      // ����1: �����̳�, ����2: ������ġ
    front_insert_iterator<Container> front_inserter(Container& Cont);
    back_insert_iterator<Container> back_inserter(Container& Cont);

    ex) insert_iterator<Container> insit = inserter(vi, vi.begin()+2);
--*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

template<typename C>
void dump(const char *name, C &c)
{
    cout.width(12);
    cout << left << name << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " "));
    cout << endl;
}

void main()
{
    int ari[] = {1,2,3,4,5};
    int ari2[] = {6,7,8,9,10,11,12,13,14,15};

    vector<int> vi(&ari[0], &ari[5]);
    vector<int>::iterator it;
    it = find(vi.begin(), vi.end(), 4);
    // �����Ҷ� vi �����̳��� �뷮�� �Ѿ�� ���� �߻�
    //copy(&ari2[0], &ari2[10], it);   //����
    // dump("������", vi);          
    

    // Insert Iterator�� ����� ����
    //insert_iterator<vector<int> > iit(vi, it);
    insert_iterator<vector<int> > iit(vi, find(vi.begin(), vi.end(), 4));
    copy(&ari2[0], &ari2[10], iit);     
    //*iit = 99;
    //*iit = 100;
    dump("������", vi);
 

    // inserter
    cout << "----------------------------------------\n";
    copy(&ari2[0], &ari2[10], inserter(vi, find(vi.begin(), vi.end(), 4)));
    dump("������", vi);

    // revcopy
    cout << "----------------------------------------\n";
    list<int> li;
    copy(&ari[0], &ari[5], front_inserter(li));
    copy(li.begin(), li.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // �Է°��� ������ �������� ���� ��� insertȰ��
    cout << "----------------------------------------\n";
    cout << "input int(ctrl+z) : ";
    vector<int> vi2;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vi2));
    copy(vi2.begin(), vi2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

}