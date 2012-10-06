/*++
    2012.10.06

    31.1 SwapArray(358p)
       일반타입의 Swap함수와 다른 방식으로 동작
       그래서 SwapArray따로 작성
       SwapArray의 템플릿 함수명을 Swap으로 중복 정의 가능
       => 템플릿끼리도 오버로딩 가능함
 --*/


#include <Turboc.h>

template <typename T>
void SwapArray(T *pa, T *pb, int num)
{
    T *pt;
    pt = (T *)malloc(num * sizeof(T));
    for(int i=0; i < num; ++i)
    {
        pt[i] = pa[i];
        pa[i] = pb[i];
        pb[i] = pt[i];
    }
    /*
    memcpy(tt, pa, num*sizeof(T));
    memcpy(pa, pb, num*sizeof(T));
    memcpy(pb, tt, num*sizeof(T));
    */

    free(pt);
}

void main()
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    char c[]="문자열";
    char d[]="string";

    SwapArray(a, b, sizeof(a)/sizeof(a[0]));
    printf("c=%s, d=%s\n", c, d);
    SwapArray(c, d, sizeof(c)/sizeof(c[0]));
    printf("c=%s, d=%s\n", c, d);
}