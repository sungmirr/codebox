/*++
    2012.10.7

    36.표준라이브러리, 파일입출력(592p)

    ifstream, ofstream의 open함수
    void open(const char *_Filename,ios_base::openmode _Mode = ios_base::in,int _Prot = (int)ios_base::_Openprot)
    void open(const char *_Filename, ios_base::open_mode _Mode)

    open할때 파일모드는 ios_base에 정의된 상수로 지정
    ios_base::out    출력용으로 파일을 연다
    ios_base::in     입력용으로 파일을 연다
    ios_base::app    파일 끝에 데이터를 덧붙인다
    ios_base::ate    파일 열자마자 파일 끝으로 fp를 보낸다, fp를 임의 위치로 옮길 수 있다
    ios_base::trunc  파일이 존재할 경우 크기를 0으로 만든다
    ios_base::binary 이진 모드로 연다

    ios_base::binary 파일 모드가 이진 모드일경우, read, wirte함수 사용!!!
    _Myt& read(_Elem *_Str, streamsize _Count)
    _Myt&  write(const _Elem *_Str, streamsize _Count)

    ios_base::ate 입,출력용 파일의 fp이동
    seekg
    seekp
    
--*/

#include "Turboc.h"
#include <iostream>
#include <fstream>
using namespace std;

void main()
{
    ifstream ifs("C:\\dummy.txt", ios_base::in | ios_base::binary);
    if(!ifs.is_open())
    {
        cout << "원본 파일이 없습니다." << endl;
        return;
    }
    ofstream ofs("C:\\dummy2.txt", ios_base::out | ios_base::trunc | ios_base::binary);
    char buf[100000];
    int nread;

    while(1)
    {
        ifs.read(buf, sizeof(buf));
        nread = ifs.gcount();               // read 함수가 실제로 읽은 바이트수
        if(nread==0) break;
        ofs.write(buf, nread);
    }

    ifs.close();
    ofs.close();
}
