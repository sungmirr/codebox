/*++
    2012.10.06

    31.2 NoneTYpeArgument(373p)
     - Ÿ���� �ƴ� ����� ���ø� �μ��� ����
     
     �̿� Default Template �μ�
     template <typename T=int>
     class PosValue
     { ... };

     PosValue<> iv(1,2,3);
 --*/

#include "Turboc.h"

// Ŭ���� ���ø��� ��Ÿ���μ�
template <typename T, int N>
class Array
{
private:
    T ar[N];

public:
    void SetAt(int n, T v)
    {
        if(n<N && n>=0)
            ar[n] = v;
    }
    
    T GetAt(int n)
    {
        return (n<N && n>=0 ? ar[n] : 0);
    }
};

// �Լ� ���ø��� ��Ÿ���μ�
template<int N>
void func(void)
{
    int ar[N];

    printf("�迭 ũ�� = %d\n", N);
}

void main()
{
    Array<int,5> ari;

    ari.SetAt(1, 1234);
    ari.SetAt(1000,5678);

    printf("%d\n", ari.GetAt(1));
    printf("%d\n", ari.GetAt(5));

    func<3>();
    func<5>();

    /*
    Array<int,10> ari2;
    ari = ari2   // ����, ���� �ٸ� �ڷ���
    */

    /*
    int size=5;
    Array<int,size> ari3;       // ����� ����
    */
    const int c_size = 10;
    Array<int, c_size> ari4;
}