/*++
    2012. 10. 24

    InIt find_if(InIt first, InIt last, UniPred F);
    - find�� ==������ �̿�, find_if�� �����Լ� ��ü F�� ��
 --*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct HasYoung 
{
    bool operator()(string who) const
    {
        return (who.find("��") != string::npos);
    }
};

void main()
{
    string names[]={"������","��ȫ��","������",
        "�迵��","������","�ڹ̿�","������"};
    vector<string> as(&names[0],&names[7]);
    vector<string>::iterator it;

    for(it=as.begin();;++it)
    {
        it=find_if(it, as.end(), HasYoung());
        if(it==as.end())
            break;
        cout << *it << "��(��) �ִ�." << endl;
    }
}