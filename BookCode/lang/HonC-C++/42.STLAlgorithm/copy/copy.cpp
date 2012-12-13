/*++
    2012. 10. 24

    copy
    - 지정한 구간을 복사하는데 주로 일부 요소들을 다른 컨테이너로 복사하고 싶일 때 사용

    OutIt copy(InIt first, InIt last, OutIt result);
    BiIt copy_backward(BiIt first, BiIt last, BiIt result);
    => first~last사이의 모둔 요소를 result반복자 위치 이후에 복사

 --*/
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;


template<typename C> 
void dump(const char *desc, C c) 
{ 
    cout.width(12);
    cout << left << desc << "==> ";
    copy(c.begin(),c.end(),ostream_iterator<typename C::value_type>(cout," ")); 
    cout << endl; 
}

void main()
{
    char src[]="1234567890";
    char dest[]="abcdefghij";

    copy(&src[3],&src[7],&dest[5]);
    puts(dest);


    list<char> li;
    copy(&src[3],&src[7],back_inserter(li));
    dump("list",li);
}
