/*++
    2012.10.20

    40.�����������̳�, ������(737p)


    5. ������ ������&����Լ�
    ���� : =(��ü), assign(�Ϻα����� ����)
    ��ȯ : swap
    �� : ==,!=, <,>,<=,>=
    ������� : [], at

    void assign(size_type count, const Type& val);  // val���� count���� �ݺ������� ����
    void assign(Init first, InIt last);             // �ݺ��� ������ ��Ҹ� ���Ϳ� ����

    void swap(vector& Right);
    // ���������� ����� �˰��� swap�� �ִ�

    at�Լ��� ������ �����ϸ� ��ȿ�� ÷���� ��� out_of_range���ܸ� �߻�
    const_reference at(size_type pos) const;
    reference at(size_type pos);
--*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename C> 
void dump(const char *desc, const C& c) 
{ 
    cout.width(12);
    cout << left << desc << "==> ";
    copy(c.begin(),c.end(),ostream_iterator<typename C::value_type>(cout," ")); 
    cout << endl; 
}

void main()
{
    int ari[]={1,2,3,4,5};
    vector<int> vi(&ari[0],&ari[5]);

    vector<int>vi2;
    vi2=vi;
    dump("vi2",vi2);

    vector<int>vi3;
    vi3.assign(vi.begin()+1,vi.end()-1);
    dump("vi3",vi3);


    const char str[]="abcdefghijklmnopqrstuvwxyz";
    vector<char> vc1(&str[0],&str[5]);
    vector<char> vc2(&str[5],&str[19]);

    dump("before vc1",vc1);
    dump("before vc2",vc2);
    //vc1.swap(vc2);	
    swap(vc1, vc2);
    dump("after vc1",vc1);
    dump("after vc2",vc2);


    const char *st="0123456789";
    vector<char> v1(&st[0],&st[10]);
    vector<char> v2;
    vector<char> v3;

    v2=v1;
    puts(v1==v2 ? "����":"�ٸ���");
    puts(v1==v3 ? "����":"�ٸ���");
    v2.pop_back();
    puts(v1 > v2 ? "ũ��":"ũ�� �ʴ�");


    // at�Լ��� []
    cout<<"--------------------------\n";
    int ar[]={1,2,3,4,5};
    vector<int> vvi(&ar[0],&ar[5]);

    try 
    {
        //cout << vi[10] << endl;
        cout << vvi.at(10) << endl;
    } 
    catch(out_of_range e) 
    {
        cout << "������ ������ ������ϴ�." << endl;
    }
}
