/*++
    2012.10.19

    39.�ݺ���, ������ݺ��� (720p)
    
    ������ݺ���
    - ����� �ݺ��ڳ� �������� �ݺ��ڿ� ����͸� �����Ͽ� ����
      ++,--������ �ݴ�� ����
    - �� �����̳ʴ� ���� �ΰ��� ������ �ݺ��� Ÿ�� ����
      reverse_iterator
      const_reverse_iterator
    - ������ �ݺ��ڴ� rbegin, rend��� �Լ��� ��´�
          [0],  [1],  [2],  [3]
      rend                 rbegin  
          begin                  end    

    - ������ �ݺ�����base()����Լ� : ������ ������ �ݺ��� ����
      ����,���� �Լ����� ������ �ݺ��ڸ� �޾Ƶ����� �ʴ´�. ������ �˻��� ��ġ�� � �۾��� �ϰ� ������ ���������� ��ȯ
      ������ �˻� �� ������ �˻��ϰ� ������
--*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main()
{
    int ari[] = {1, 2, 3, 4, 5};
    vector<int> vi(&ari[0], &ari[5]);
    vector<int>::reverse_iterator rit;
    for(rit=vi.rbegin(); rit!=vi.rend(); ++rit)
        cout << *rit << endl;

    // find�Լ��� ������ �ݺ��ڸ� �޾Ƶ��δ�
    cout << "-------------------------------" << endl;
    int ari2[]={6,2,9,2,7};
    vector<int> vi2(&ari[0],&ari[5]);

    puts(find(vi.begin(), vi.end(), 2) == vi.end() ? "����." : "�ִ�.");
    puts(find(vi.rbegin(), vi.rend(), 2) == vi.rend() ? "����." : "�ִ�.");

    // ������ݺ����� base����Լ�
    cout << "-------------------------------" << endl;
    const char *str="c++ standard template library";
    vector<char> vc(&str[0],&str[strlen(str)]);
    
    vector<char>::reverse_iterator rit3;
    vector<char>::iterator bit3, it3;
    rit3=find(vc.rbegin(), vc.rend(), 't');  // find���� ������ݺ��� ����� ���ϰ��� ������ݺ���
    bit3 = rit3.base();
    it3=find(bit3, vc.end(), 'a');
    if(it3!=vc.end())
        cout << "�˻� ���=" << *it3 << endl;
}