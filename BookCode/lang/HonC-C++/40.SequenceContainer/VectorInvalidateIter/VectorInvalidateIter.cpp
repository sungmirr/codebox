/*++
    2012.10.20

    40.�����������̳�, �ݺ��� ��ȿȭ ����(735p)

    �ݺ����� ��ȿȭ ��Ģ�� �����̳� ���� �ٸ���
    ����Ʈ�� �ڽ��� �����ϴ� ��츦 �����ϰ� ��ȿȭ ������ ����
    
    STL���α׷��ֿ��� ����,������ �ݺ��ڸ� �ٽ� �����ϴ� ���� ����
--*/ 


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main()
{
    vector<int> vi;
    vector<int>::iterator it;
    for (int i=0;i<80;i++) 
        vi.push_back(i);


    it=find(vi.begin(),vi.end(),55);
    cout << *it << endl;

    vi.erase(it+1);
    cout << *it << endl;        // �տ�� ������ ��ȿȭ���� ����

    vi.erase(it-1);             // �޿�� ������ ��ȿȭ���� �߻�
    cout << *it << endl;

    vi.insert(vi.begin(), 1234);    // �տ�� �߰�, ��ȿȭ���� �߻�
}
