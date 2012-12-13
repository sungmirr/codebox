/*++
    2012. 10. 24

    copy
    - ������ ������ �����ϴµ� �ַ� �Ϻ� ��ҵ��� �ٸ� �����̳ʷ� �����ϰ� ���� �� ���

    OutIt copy(InIt first, InIt last, OutIt result);
    BiIt copy_backward(BiIt first, BiIt last, BiIt result);
    => first~last������ ��� ��Ҹ� result�ݺ��� ��ġ ���Ŀ� ����

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
