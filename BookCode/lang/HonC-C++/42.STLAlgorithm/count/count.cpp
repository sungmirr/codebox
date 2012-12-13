/*++
    2012. 10. 24

    size_t count(InIt first, InIt last, const T& val);
    size_t count_if(InIt first, InIt last, UniPred F);

    => �ݺ��� �������� ������ ��(��ü)�� ��ġ�ϴ� ����� ������ ����

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
    printf("�� ���忡�� a�� %d�� �ֽ��ϴ�.\n",num);

    num = count_if(&str[0],&str[strlen(str)+1],bind2nd(greater<char>(),'t'));
    printf("�� ���忡�� t���� �� ū ���ڰ� %d�� �ֽ��ϴ�.\n",num);
}