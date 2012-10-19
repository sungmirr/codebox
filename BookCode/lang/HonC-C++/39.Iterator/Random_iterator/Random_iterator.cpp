/*++
    2012.10.19

    39.�ݺ���, �������ٹݺ��� (704p)
    
    Random Iterator
    - �ֻ��� ������ �ݺ���
    - +n����,-n����,[]����, +=����, -=���� ����
      ������ ���ҿ� ����ð��� �̵�����
    - �迭ó�� ������ ��ġ�� ��ġ�Ǵ� �����̳ʿ��� �������ٹݺ��� ����
      �ݺ��ڳ��� ��Һ� ����
    - ex) ����, ���� �迭�� ��ġ�� ������ ������
          sort, binary_search ���� ���� ���� �ݺ��� ���


    cf) list�� ���������� �Ұ����ϹǷ� �����ݺ���(BiIt) ����
        - +���� �Ұ���, ��Һ� �Ұ���
        - �ݺ��� ���� ������ ���� ������ ��� ���� ���� �� ����
        - ���� ������ �����ϰ� �Ϸ��� �Ʒ� �� �Լ� �̿�
          void advance(InIt &first, int off);
          int distance(InIt first, InIt last);

          // ������尡 ũ��
          void advance(InIt &first, int off)
          {
          for(;off>0;--off) { ++first; }
          for(;off<0;++off) { --first; }
          }

    �����̳ʴ� �ڽ��� �����ϴ� �ݺ����� ���� ���
    �˰����� �䱸�ϴ� �ּ��� �ݺ��� ���
--*/

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

void main()
{
    int ari[] = {1,2,3,4,5,6,7};
    list<int> li(&ari[0], &ari[7]);
    list<int>::iterator it;

    it=li.begin();
    printf("%d\n", *it);
    printf("%d\n", *(++it));
    //printf("%d\n", it[3]);    // ����

    //it+=3;                    // ����
    advance(it, 3);
    printf("%d\n", *it);
    //printf("�Ÿ�=%d\n", li.end()-li.begin());   // ����
    printf("�Ÿ�=%d\n", distance(li.begin(), li.end()));  


    // �������� �ݺ��ڸ� �䱸�ϴ� sort�˰��� ����Ʈ�� ����� �ݺ��� ����
    //sort(li.begin(), li.end());    // ����
}

