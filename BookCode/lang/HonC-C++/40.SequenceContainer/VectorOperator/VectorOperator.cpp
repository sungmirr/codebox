/*++
    2012.10.20

    40.시퀀스컨테이너, 연산자(737p)


    5. 벡터의 연산자&멤버함수
    대입 : =(전체), assign(일부구구만 복사)
    교환 : swap
    비교 : ==,!=, <,>,<=,>=
    요소참조 : [], at

    void assign(size_type count, const Type& val);  // val값을 count개를 반복적으로 복사
    void assign(Init first, InIt last);             // 반복자 구간의 요소를 벡터에 대입

    void swap(vector& Right);
    // 전역적으로 선언된 알고리즘 swap도 있다

    at함수는 범위를 점검하며 무효한 첨자일 경우 out_of_range예외를 발생
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
    puts(v1==v2 ? "같다":"다르다");
    puts(v1==v3 ? "같다":"다르다");
    v2.pop_back();
    puts(v1 > v2 ? "크다":"크지 않다");


    // at함수와 []
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
        cout << "벡터의 범위를 벗어났습니다." << endl;
    }
}
