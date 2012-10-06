/*++
    2012.10.06

    31.2 NoneTYpeArgument(373p)
     - 타입이 아닌 상수를 템플릿 인수로 전달
     
     이외 Default Template 인수
     template <typename T=int>
     class PosValue
     { ... };

     PosValue<> iv(1,2,3);
 --*/

#include "Turboc.h"

// 클래스 템플릿의 비타입인수
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

// 함수 템플릿의 비타입인수
template<int N>
void func(void)
{
    int ar[N];

    printf("배열 크기 = %d\n", N);
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
    ari = ari2   // 에러, 서로 다른 자료형
    */

    /*
    int size=5;
    Array<int,size> ari3;       // 상수만 가능
    */
    const int c_size = 10;
    Array<int, c_size> ari4;
}