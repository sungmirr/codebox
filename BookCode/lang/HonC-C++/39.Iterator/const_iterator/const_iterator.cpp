/*++
    2012.10.19

    39.�ݺ���, ����ݺ��� (718p)
    
    ����ݺ���
    - ������۷����� �����ϹǷ� ���� ������ �� ����, ���� ���� �ִ�
    - ����ݺ��ڰ� ����Ű�� �������, �ݺ��� ��ü�� ����� �̴ϹǷ� ���ķ� �̵� ����
    - ��������̳ʸ� �μ��� �޴� �Լ� ������ �����̳ʴ� ������� ������, ����ݺ��ڸ� ��밡��
    ex) vector<int>::const_iterator cit = vi.begin();
--*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ��� �����̳ʸ� �μ��� �޴� �Լ�
int vectorsum(const vector<int> &cvt)
{
    vector<int>::const_iterator cit;
    int sum=0;

    for(cit=cvt.begin(); cit!=cvt.end(); ++cit)
        sum += *cit;

    //*cit = 1234;  //����

    find(cvt.begin(), cvt.end(), 60);     // ��밡��
    //sort(cvt.begin(), cvt.end());       // ����
    return sum;
}

void main()
{
    int ari[] = {80, 98, 75, 60, 100};
    vector<int> vi(&ari[0], &ari[5]);

    int sum;
    sum = vectorsum(vi);
    printf("�� ���� %d�Դϴ�\n", sum);
}