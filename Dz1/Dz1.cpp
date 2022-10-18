// Dz1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

string Hex_to_Bin(const char& c)
{
    switch (c) {
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'A': return "1010";
    case 'B': return "1011";
    case 'C': return "1100";
    case 'D': return "1101";
    case 'E': return "1110";
    case 'F': return "1111";
    //case '.': return ".";
    };
}
void Invert_String(string& s)
{
    string temp;
    for (int i = 0; i < s.size(); i++)
    {
        temp += s[s.size() - i - 1];
    }
    s = temp;
}
uint8_t Bin_to_int8(const string& s)
{
    uint8_t temp = 0;
    for (int i = 0; i < 8; i++)
    {
        if (s[i] == '1')
        {
            temp += pow(2, i);
        }
    }
    //cout << (int) temp;
    return temp;
}
float Bin_to_float(const string& s)
{
    
    string bin_bytes[4];
    uint8_t uint8_bytes[4];
    float* result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bin_bytes[i] += s[i * 8 + j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        Invert_String(bin_bytes[i]);
        uint8_bytes[i] = Bin_to_int8(bin_bytes[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        uint8_bytes[i] = Bin_to_int8(bin_bytes[3 - i]);
    }
    result = reinterpret_cast<float*>(uint8_bytes);
    return *result;
}
struct PNI_Trax {
    PNI_Trax()
    {
        kHeading = 1234;
        kPitch = 1234;
        kRoll = 1234;
        kHeadingStatus = '-';
        for (int i = 0; i < 4; i++)
        {
            kQuaternion[i] = 1234;
        }
        kDistortion_ready = 0;
        CalStatus_ready = 0;
        kTemperature = 1234;
        kAccelX = 1234;
        kAccelY = 1234;
        kAccelZ = 1234;
        kMagX = 1234;
        kMagY = 1234;
        kMagZ = 1234;
        kGyroX = 1234;
        kGyroY = 1234;
        kGyroZ = 1234;
    }

    void fill (const string& package)
    {
        char temp_char = 0;
        string bin_package;
        uint8_t temp_int8 = 0;
        int i = 0;
        int byte_count = 1;
        for (int i = 0; i < package.size(); i++)
        {
            bin_package += Hex_to_Bin(package[i]);
        }
        while (i < bin_package.size() - 1)
        {
            string temp;
            uint8_t ID;
            bool* temp_bool = 0;
            for (int j = 0; j < byte_count * 8; j++)
            {
                temp += bin_package[i + j];
            }
            Invert_String(temp);
            ID = Bin_to_int8(temp);
            //cout << "ID is = " << (int)ID << endl;
            i += 8;
            temp = "";
            switch ((int)ID)
            {
            case 5:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kHeading = Bin_to_float(temp);
                i += 32;
                break;
            case 24:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kPitch = Bin_to_float(temp);
                i += 32;
                break;
            case 25:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kRoll = Bin_to_float(temp);
                i += 32;
                break;
            case 79: 
                for (int j = 0; j < 8; j++)
                {
                    temp += bin_package[i + j];
                }
                Invert_String(temp);
                kHeadingStatus = (char)Bin_to_int8(temp);
                //cout << "a.kHeadingStatus position" << i / 4 << endl;
                i += 8;
                break;
            case 77:
                for (int n = 0; n < 4; n++)
                {
                    temp = "";
                    for (int j = 0; j < 32; j++)
                    {
                        temp += bin_package[i + j];
                    }
                    kQuaternion[n] = Bin_to_float(temp);
                    i += 32;
                }
                break;
            case 7:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kTemperature = Bin_to_float(temp);
                i += 32;
                break;
            case 8:
                for (int j = 0; j < 8; j++)
                {
                    temp += bin_package[i + j];
                }
                Invert_String(temp);
                if ((int)Bin_to_int8(temp) == 0)
                {
                    kDistortion = false;
                }
                else
                {
                    kDistortion = true;
                }
                i += 8;
                kDistortion_ready = 1;
                break;
            case 9:
                for (int j = 0; j < 8; j++)
                {
                    temp += bin_package[i + j];
                }
                Invert_String(temp);
                if ((int)Bin_to_int8(temp) == 0)
                {
                    kCalStatus = false;
                }
                else
                {
                    kCalStatus = true;
                }
                i += 8;
                CalStatus_ready = 1;
                break;
            case 21:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kAccelX = Bin_to_float(temp);
                i += 32;
                break;
            case 22:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kAccelY = Bin_to_float(temp);
                i += 32;
                break;
            case 23:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kAccelZ = Bin_to_float(temp);
                i += 32;
                break;
            case 27:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kMagX = Bin_to_float(temp);
                i += 32;
                break;
            case 28:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kMagY = Bin_to_float(temp);
                i += 32;
                break;
            case 29:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kMagZ = Bin_to_float(temp);
                i += 32;
                break;
            case 74:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kGyroX = Bin_to_float(temp);
                i += 32;
                break;
            case 75:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kGyroY = Bin_to_float(temp);
                i += 32;
                break;
            case 76:
                for (int j = 0; j < 32; j++)
                {
                    temp += bin_package[i + j];
                }
                kGyroZ = Bin_to_float(temp);
                i += 32;
                break;
            }

        }
    }

    void get()
    {
        if(kHeading != 1234)
            cout << "kHeading = " << kHeading << endl;
        else 
            cout << "kHeading = " << "-" << endl;

        if (kPitch != 1234)
            cout << "kPitch = " << kPitch << endl;
        else
            cout << "kPitch = " << "-" << endl;

        if (kRoll != 1234)
            cout << "kRoll = " << kRoll << endl;
        else
            cout << "kRoll = " << "-" << endl;

       if (kHeadingStatus == 0)
           cout << "kHeadingStatus = " << '0' << endl;
       else
            cout << "kHeadingStatus = " << kHeadingStatus << endl;
        
            if (kQuaternion[0] != 1234)
            {
                for (int i = 0; i < 4; i++)
                {
                    cout << "kQuaternion[" << i << "] = " << kQuaternion[i] << endl;
                }
            }
            else
                cout << "kQuaternion = -" << endl;

        if (kTemperature != 1234)
            cout << "kTemperature = " << kTemperature << endl;
        else
            cout << "kTemperature = " << "-" << endl;

        if (kDistortion_ready != 0)
        {
            if (kDistortion == 0)
                cout << "kDistortion = false" << endl;
            else
                cout << "kDistortion = true" << endl;
        }
        else 
            cout << "kDistortion = -" << endl;
        
        if ( CalStatus_ready != 0)
        {
            if (kCalStatus == 0)
                cout << "kCalStatus = false" << endl;
            else
                cout << "kCalStatus = true" << endl;
        }
        else
            cout << "kCalStatus = -" << endl;

        if ((int) kAccelX != 1234)
            cout << "kAccelX = " << kAccelX << endl;
        else
            cout << "kAccelX = " << "-" << endl;
        
        if (kAccelY != 1234)
            cout << "kAccelY = " << kAccelY << endl;
        else
            cout << "kAccelY = " << "-" << endl;
        
        if (kAccelZ != 1234)
            cout << "kAccelZ = " << kAccelZ << endl;
        else
            cout << "kAccelZ = " << "-" << endl;
       
        if (kMagX != 1234)
            cout << "kMagX = " << kMagX << endl;
        else
            cout << "kMagX = " << "-" << endl;

        if (kMagY != 1234)
            cout << "kMagY = " << kMagY << endl;
        else
            cout << "kMagY = " << "-" << endl;

        if (kMagZ != 1234)
            cout << "kMagZ = " << kMagZ << endl;
        else
            cout << "kMagZ = " << "-" << endl;
        
        if (kGyroX != 1234)
            cout << "kGyroX = " << kGyroX << endl;
        else
            cout << "kGyroX = " << "-" << endl;

        if (kGyroY != 1234)
            cout << "kGyroY = " << kGyroY << endl;
        else
            cout << "kGyroY = " << "-" << endl;

        if (kGyroZ != 1234)
            cout << "kGyroZ = " << kGyroZ << endl;
        else
            cout << "kGyroZ = " << "-" << endl;
    }
    private:
    float kHeading;
    float kPitch;
    float kRoll;
    char kHeadingStatus;
    float kQuaternion[4];
    float kTemperature;
    int kDistortion_ready;
    bool kDistortion;
    int CalStatus_ready;
    bool kCalStatus;
    float kAccelX;
    float kAccelY;
    float kAccelZ;
    float kMagX;
    float kMagY;
    float kMagZ;
    float kGyroX;
    float kGyroY;
    float kGyroZ;

};
int main()
{
    string package;
    PNI_Trax a;
    int close_console;
    cin >> package;
    a.fill(package);
    a.get();
    cout << "Enter any number to close the console" << endl;
    cin >> close_console;
    return 0;
}


