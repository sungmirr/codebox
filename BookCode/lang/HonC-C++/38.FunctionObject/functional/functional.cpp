/*++
    2012.10.17

    38.�Լ���ü, �̸� ���ǵ� �Լ���ü(662p) 
    - functional ������Ͽ� �Լ���ü�� �� ���� ��ũ��, Ÿ�Ե��� ����

    <�̸� ���ǵ� �Լ���ü�� ����Ʈ>
    plus            �� �μ��� ���� ��� �� ����
    minus           
    multiplies
    divides
    modulus
    negate          �μ� �ϳ��� ���޹޾� ��ȣ�� �ݴ��
    eqaul_to        �� �ȼ��� ������ ���Ͽ� ����� boolŸ������ ����
    not_eqaul_to    
    greater         ù��° �μ��� �ι�° �μ����� ū�� ����
    less
    greater_equal
    less_eaual
    logical_and     �� �μ��� ����(&&) ����� ����
    logical_or
    logical_not     �μ� �ϳ��� ���޹޾� ������(!)�� ����


    void sort(RanIt first, RanIt last);         // <�����ڷ� ��Ҹ� ���ϹǷ� �ø����� ����
    void sort(RanIt first, RanIt last, BinPred F);  // BinPred : bool����, ����

--*/
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


// ��ҹ��� ���о��� ���ĺ������� ���ڿ��� ������������ ����
struct compare
{
    bool operator()(const string &a, const string &b) const
    {
        return stricmp(a.c_str(), b.c_str()) < 0;
    }
};

void main()
{
    int a=1,b=2;
    int c;

    // plus<int> P;
    // c = P(a,b);
    c = plus<int>()(a,b);   // ����Ʈ������ ȣ�⹮���� �ӽð�ü�� ����
                            // ������ �ӽð�ü���� ()������ ȣ��
    cout << c << endl;
    

    cout << "--------------------------------" << endl;
    string names[]={"STL","MFC","owl","html","pascal","Ada",
        "Delphi","C/C++","Python","basic"};
    vector<string> vs(&names[0],&names[10]);

    //sort(vs.begin(), vs.end());                       // <������.. ��������
    sort(vs.begin(), vs.end(), greater<string>());      // >������.. ��������

    vector<string>::iterator it;
    for(it=vs.begin(); it!=vs.end(); ++it)
        cout << *it << endl;


    cout << "--------------------------------" << endl;
    sort(vs.begin(), vs.end(), compare());
    for(it=vs.begin(); it!=vs.end(); ++it)
        cout << *it << endl;
}