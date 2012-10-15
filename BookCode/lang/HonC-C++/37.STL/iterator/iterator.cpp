/*++
    2012.10.15

    37.STL����(638p)

    �ݺ���
     - ��ȸ����� �Ϲ�ȭ�ϱ� ���� ����ϴ� ����
     - ������ or [] or ��ü(::iterator)
     
     - �����̳ʿ���ϳ��� ����Ŵ, *,++.--,����,�� ������ ����
     - �����ʹ� �� ����� ��� �����Ƿ� �� ��ü�� �Ϻ��� �ݺ��ڷ� ��� STL�˰��� ��밡��
     - ��� �����̳ʴ� �������� ���������� �����ϴ� begin, end��� �Լ� ����
--*/
#include <iostream>
#include <vector>
#include <list>
using namespace std;

// �ݺ��ڸ� �Ϲ�ȭ �Ͽ� ����ϴ� Print ���ø� �Լ�
template <typename IT>
void Print(IT s, IT e)
{
    IT it;
    for(it=s; it!=e; ++it)
        printf("%d\n", *it);
}

void main()
{
    // �����͸� �ݺ��ڷ� ���
    int ari[]={1,2,3,4,5};
    int *it;
    for(it=&ari[0]; it!=&ari[5]; ++it)
        printf("%d\n", *it);

    // �ݺ��ڻ��
    cout << "-------------------------------\n";
    vector<int> vi(&ari[0], &ari[5]);
    vector<int>::iterator vIt;
    for(vIt=vi.begin(); vIt!=vi.end(); ++vIt)
        printf("%d\n", *vIt);


    // �ݺ��ڸ� ���� ��� �Ǵ� �Ϲ�ȭ
    cout << "-------------------------------\n";
    list<int> li(&ari[0], &ari[5]);

    Print(&ari[0], &ari[5]);
    Print(vi.begin(), vi.end());
    Print(li.begin(), li.end());
}

