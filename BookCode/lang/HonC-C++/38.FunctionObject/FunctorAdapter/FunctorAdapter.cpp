/*++
    2012.10.17

    38.�Լ���ü, ����� (671p)  
    
    ========================================================================================================
    ������� ����
    - ������Ʈ �����(component adapter) : ����, ť, �켱���� ť
    - �ݺ��� �����(iterator adapter) : ������ �ݺ���
    - �Լ���ü �����(functor adapter) : ������, ���δ�, �Լ������;����

    �Լ���ü �����
    - �Լ� ��ü�� ����� �����ϱ� ���� �μ�Ÿ�԰� ��ȯ���� Ÿ���� �ʿ���
    - �׷��� STL������ functional ��� ���Ͽ� unary_function, binary_function ���ø� Ŭ������ ������
    - ����ͺ��Լ���ü(Adaptable Functor)�� ������� ������ ���ø� Ŭ������ ��ӹ޾� ����

    ����ͺ� �Լ���ü
    - �Լ���ü�� �μ�Ÿ�԰� ��ȯ���� argument_type�� result_type���� �̸����� ȹ��ȭ�Ͽ� Ÿ�� ����
    - �Ʒ� �� ���ø� Ŭ������ ��ӹ����� �̸� ��ӵ� �̸����� ���ǵǾ� ����ʹ� ��ӵ� �̸����� �ش� 
      ������ ���� ��´�
    template<class Arg, class Result>
    struct unary_function
    {
        typedef Arg argument_type;
        typedef Result result_type;
    }
    template<class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    }

    plus, greater���� �̸� �����Ǵ� �Լ���ü���� ��� ����ͺ� �Լ���ü�̴�
    ========================================================================================================

    ������
    - bool�� �����ϴ� ������ �Լ� ��ü�� �� ����� �ݴ�� ������ �Լ���ü
    - not1 : UniPred�� ����
      not2 : BinPred�� ����

    ���δ�
    - ����ϰ��� �ϴ� �Լ� ��ü�� ���� �䱸�Ǵ� �Լ� ��ü�� �ٸ��� ���δ� ����� ���
    - ���� �Լ� ��ü�� ������ �� �μ��� Ư���� ������ �����Ͽ� ���� �Լ� ��ü�� ��ȯ 
      bind1st(���װ�ü, ������)
      bind2nd(���װ�ü, ������)

    �Լ� ������ �����
    - �Ϲ� �Լ��� ������ �Լ� �����͸� �Լ� ��üó�� ����
    - �Լ������ʹ� ��ü�� �ƴϹǷ� ����Ϳ� ������ �� ����
      ptr_fun

    cf>
    greater<int>() : �ΰ��� ���Ͽ� ���� ���� ���� ������ �� ū���� �����ϴ� ���� ������
    less_equal<int>() : ���� �����ڷ� ������ ������ ����
    

    å�� ����� ���� ���....Ȯ��!!!!
--*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

// unary adaptable functor
struct IsMulti3 : public unary_function<int, bool>
{
    // typedef int argument_type;
    // typedef bool result_type;
    bool operator()(const int a) const
    {
        return (a%3 == 0);
    }
};


// binary adaptable funtor
// string�� ��ҹ��� ���о��� �������� ����
struct compare : public binary_function<string, string, bool>
{
    bool operator()(const string &a, const string &b) const
    {
        return stricmp(a.c_str(), b.c_str()) < 0;
    }
};

// ����������
struct IsMulti : public binary_function<int,int,bool>
{
    bool operator()(const int a, const int b) const
    {
        return (a%b == 0);
    }
};

// �Լ�������
bool IsMultiFunc(int a, int b)
{
    return (a%b == 0);
}


void main()
{
    int ari[]={1,2,3,4,5,6,7,8,9,10};
    vector<int> vi(&ari[0],&ari[10]);
    vector<int>::iterator it;

    for(it=vi.begin();;++it)
    {
        it = find_if(it, vi.end(), IsMulti3());
        if(it==vi.end()) break;
        cout << *it << "��(��) �ִ�" << endl;
    }

    // IsMulti3�� ���ϰ��� ������ 3�� ����� �ƴ� ���Ҹ� ���
    cout << "-------------------------------" << endl;
    for(it=vi.begin();;++it)
    {
        it = find_if(it, vi.end(), not1(IsMulti3()));
        if(it==vi.end()) break;
        cout << *it << "��(��) �ִ�" << endl;
    }

    // not2
    cout << "-------------------------------" << endl;
    string names[]={"STL","MFC","owl","html","pascal","Ada",
        "Delphi","C/C++","Python","basic"};
    vector<string> vs(&names[0],&names[10]);

    sort(vs.begin(), vs.end(), not2(compare()));
    vector<string>::iterator vIt;
    for(vIt=vs.begin(); vIt!=vs.end(); ++vIt)
        cout << *vIt << endl;

    // ���װ�ü IsMulti
    cout << "-------------------------------" << endl;
    IsMulti IM;
    if(IM(6,3))
        cout << "6�� 3�� ����̴�." << endl;
    if(IM(9,2))
        cout << "9�� 2�� ����̴�." << endl;

    // bind2nd
    // �̻������ڸ� ���������ڷ� ����
    cout << "bind2nd-------------------------------" << endl;
    for(it=vi.begin();;++it)
    {
        // IsMulti�� �ι�° �μ��� 3���� �����Ͽ� ���������ڷ� ��ȯ 
        //it=find_if(it, vi.end(), bind2nd(IsMulti(), 3));
        //it=find_if(it, vi.end(), bind2nd(greater<int>(), 5));
        //it=find_if(it, vi.end(), bind2nd(less_equal<int>(),5));   // less_equal�� ����������
        it=find_if(it, vi.end(), not1(bind2nd(less_equal<int>(),5)));
        if(it==vi.end()) break;
        cout << *it << "��(��) �ִ�" << endl;
    }   

    // �Լ������͸� �Լ���ü�� ��ȯ�ϴ� �����
    cout << "ptr_fun-------------------------------" << endl;
    for(it=vi.begin();;++it)
    {
        it = find_if(it, vi.end(), bind2nd(ptr_fun(IsMultiFunc), 3));
        if(it == vi.end()) break;
        cout << *it << "��(��) �ִ�" << endl;
    }
}