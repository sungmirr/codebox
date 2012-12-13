/*++
    2012. 10. 24

    size_t count(InIt first, InIt last, const T& val);
    size_t count_if(InIt first, InIt last, UniPred F);

    => 반복자 구간에서 지정한 값(객체)과 일치하는 요소의 개수를 센다

 --*/

#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

void main()
{
    const char *str="Oh baby baby,How was I supposed to know "
        "That something wasn't right here";
    size_t num;

    num = count(&str[0],&str[strlen(str)+1],'a');
    printf("이 문장에는 a가 %d개 있습니다.\n",num);

    num = count_if(&str[0],&str[strlen(str)+1],bind2nd(greater<char>(),'t'));
    printf("이 문장에는 t보다 더 큰 문자가 %d개 있습니다.\n",num);
}