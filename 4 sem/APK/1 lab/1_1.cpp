#include <windows.h>
#include <iostream>
#include <sstream>

using namespace std;

HANDLE COM_Port_1;
LPCTSTR Port_Name_1 = "COM1";
HANDLE COM_Port_2;
LPCTSTR Port_Name_2 = "COM2";

void Read_from_COM()
{
    DWORD Size;
    char Received_Char;
    ReadFile(COM_Port_2, &Received_Char, 1, &Size, 0);
    if (Size > 0)
    {
        cout << Received_Char;
    }
}

int main()
{
	COM_Port_1 = ::CreateFile(Port_Name_1, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    COM_Port_2 = ::CreateFile(Port_Name_2, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (COM_Port_1 == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            cerr << "COM-port does not exist!\n";
        }
        cerr << "Some other error.\n";
    }

    DCB Serial_Params = { 0 };
    Serial_Params.DCBlength = sizeof(Serial_Params);
    if (!GetCommState(COM_Port_1, &Serial_Params))
    {
        cerr << "Getting state error.\n";
    }
    Serial_Params.BaudRate = CBR_9600;
    Serial_Params.ByteSize = 8;
    Serial_Params.StopBits = ONESTOPBIT;
    Serial_Params.Parity = NOPARITY;
    if (!SetCommState(COM_Port_2, &Serial_Params))
    {
        cerr << "Error setting serial port state.\n";
    }

    char data = 'W';
    DWORD Size = sizeof(data);
    DWORD Bytes_Written;

    BOOL Ret = WriteFile(COM_Port_1, &data, Size, &Bytes_Written, NULL);

    cout << Size << " Bytes in string. " << Bytes_Written << " Bytes sended. " << endl;

    Sleep(10);
    Read_from_COM();

    cout<< " " <<endl;

    CloseHandle(COM_Port_1);
    CloseHandle(COM_Port_2);
    cout << "Handlers closed";


    return 0;
}
