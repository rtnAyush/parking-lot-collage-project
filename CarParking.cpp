#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

class CarParking
{
private:
    int _size;
    int *slot_L;
    int *slot_R;

    int NumOfCars = 0;
    string colordata[9];
    bool isEmptySlot()
    {
        if (NumOfCars == _size)
        {
            return 0;
        }
        return 1;
    }
    bool already(string carNum)
    {
        ifstream f_read("DataBase.txt");
        string line;
        while (getline(f_read, line))
        {
            if (line.substr(0, line.length() - 3) == carNum)
            {
                return 1;
            }
        }
        f_read.close();
        return 0;
    }
    void cleanColor(string carNum)
    {
        for (int i = 0; i < 9; i++)
        {
            if (colordata[i].find(carNum) != string::npos)
            {
                colordata[i].erase(colordata[i].find(carNum), carNum.length() + 1);
            }
        }
    }
    void colorDataBase(string color, string carNum)
    {
        // 0.white,1.silver,2.brown,3.gray,4.black,5.red,6.blue,7.green,8.yellow/gold,other
        if (color == "white" || color == "White")
        {
            colordata[0].append(carNum);
            colordata[0].append(",");
        }
        else if (color == "silver" || color == "Silver")
        {
            colordata[1].append(carNum);
            colordata[1].append(",");
        }
        else if (color == "brown" || color == "Brown")
        {
            colordata[2].append(carNum);
            colordata[2].append(",");
        }
        else if (color == "gray" || color == "Gray")
        {
            colordata[3].append(carNum);
            colordata[3].append(",");
        }
        else if (color == "black" || color == "Black")
        {
            colordata[4].append(carNum);
            colordata[4].append(",");
        }
        else if (color == "red" || color == "Red")
        {
            colordata[5].append(carNum);
            colordata[5].append(",");
        }
        else if (color == "blue" || color == "Blue")
        {
            colordata[6].append(carNum);
            colordata[6].append(",");
        }
        else if (color == "green" || color == "Green")
        {
            colordata[7].append(carNum);
            colordata[7].append(",");
        }
        else if (color == "yellow" || color == "gold")
        {
            colordata[8].append(carNum);
            colordata[8].append(",");
        }
    }
    void renameEntry(string delete_line)
    {
        string line;
        vector<string> lines;
        ifstream f_read;
        f_read.open("DataBase.txt");
        while (getline(f_read, line))
        {
            lines.push_back(line);
        }
        f_read.close();
        ofstream f_write;
        f_write.open("DataBase.txt");
        for (int i = 0; i < lines.size(); i++)
        {
            if (lines[i] == delete_line)
            {
                delete_line = "unparked-" + delete_line;
                f_write << delete_line << endl;
            }
            else
            {
                f_write << lines[i] << endl;
            }
        }
        f_write.close();
    }

public:
    CarParking(int size)
    {
        _size = size;
        if (_size % 2)
        {
            slot_L = new int[(_size / 2) + 1];
            slot_R = new int[_size / 2];
            slot_L[(_size / 2)] = 0;
        }
        else
        {
            slot_L = new int[(_size / 2)];
            slot_R = new int[_size / 2];
        }
        fill_n(slot_L,_size/2,0);
        fill_n(slot_R,_size/2,0);
        ofstream DataBase("DataBase.txt");
        DataBase.close();
        cout << (char)26 << "Parking lot created." << endl;
    }

    void park(string restString)
    {
        string color = restString.substr(restString.find(" ") + 1, restString.length());
        string carNum = restString.substr(0, restString.find(" "));
        if (isEmptySlot() && !already(carNum))
        {
            colorDataBase(color, carNum);
            int i = 0, j = 0;
            while (slot_L[i] != 0 && i < _size / 2)
                i++;
            while (slot_R[j] != 0 && j < _size / 2)
                j++;
            // cout << i << "  " << j << endl;
            if (i <= j)
            {
                slot_L[i] = 1;
                NumOfCars++;
                carNum = carNum + "-" + "L" + to_string(i);
            }
            else
            {
                slot_R[j] = 1;
                NumOfCars++;
                carNum = carNum + "-" + "R" + to_string(j);
            }
            ofstream f_write("DataBase.txt", ios::app);
            f_write << carNum << endl;
            f_write.close();
            cout << (char)26 << "Your car is Successfully Park with token no:" << carNum << endl;
        }
        else if (already(carNum))
        {
            cout << (char)26 << "You have already parked your car" << endl;
        }
        else if (!isEmptySlot())
        {
            cout << (char)26 << "Parking is full,Please try other location." << endl;
        }
        else
        {
            cout << (char)26 << "CAN'T PARKED" << endl;
        }
    }
    void unPark(string carNum)
    {
        if (already(carNum))
        {
            string slot;
            ifstream f_read("DataBase.txt");
            string line;
            while (getline(f_read, line))
            {
                if (line.substr(0, line.length() - 3) == carNum)
                {
                    slot = line.substr(line.length() - 2);
                    renameEntry(line);
                }
            }
            f_read.close();
            if (slot[0] == 'L')
            {
                NumOfCars--;
                slot_L[stoi(slot.substr(1,2))] = 0;
            }
            else
            {
                NumOfCars--;
                slot_R[stoi(slot.substr(1,2))] = 0;
            }
            cout << (char)26 << carNum << " -> Car unparked" << endl;
            cleanColor(carNum);
        }
        else
            cout << (char)26 << "Car not exits." << endl;
    }
    void ViewDataBase()
    {
        cout << "|-----------------------|" << endl;
        cout << "  Number of cars :" << NumOfCars << endl;
        for (int k = 0; k < _size / 2; k++)
        {
            cout << slot_L[k] << "  ";
        }
        cout << endl;
        for (int k = 0; k < _size / 2; k++)
        {
            cout << slot_R[k] << "  ";
        }
        cout << endl;
        // for (int i = 0; i < 20; i++)
        // {
        //     cout << "  " << DataBase[i] << endl;
        // }
        cout << "|========================|" << endl;
    }

    void colorCheck(string color)
    {
        // 0.white,1.silver,2.brown,3.gray,4.black,5.red,6.blue,7.green,8.yellow/gold,other
        cout << "Avalable with color " << color << ":" << endl;
        if (color == "white" || color == "White")
        {
            (colordata[0][0] == ',' || colordata[0].empty()) ? cout << (char)26 << "No Car of this color." << endl : cout << colordata[0] << endl;
        }
        else if (color == "silver" || color == "Silver")
        {
            (colordata[1][0] == ',' || colordata[1].empty()) ? cout << (char)26 << "No Car of this color." << endl : cout << colordata[1] << endl;
        }
        else if (color == "brown" || color == "Brown")
        {
            (colordata[2][0] == ',' || colordata[2].empty()) ? cout << (char)26 << "No Car of this color." << endl : cout << colordata[2] << endl;
        }
        else if (color == "gray" || color == "Gray")
        {
            (colordata[3][0] == ',' || colordata[3].empty()) ? cout << (char)26 << "No Car of this color." << endl : cout << colordata[3] << endl;
        }
        else if (color == "black" || color == "Black")
        {
            (colordata[4][0] == ',' || colordata[4].empty()) ? cout << (char)26 << "No Car of this color." << endl : cout << colordata[4] << endl;
        }
        else if (color == "red" || color == "Red")
        {
            (colordata[5][0] == ',' || colordata[5].empty()) ? cout << (char)26 << "No Car of this color." << endl : cout << colordata[5] << endl;
        }
        else if (color == "blue" || color == "Blue")
        {
            (colordata[6][0] == ',' || colordata[6].empty()) ? cout << (char)26 << "No Car of this color." << endl : cout << colordata[6] << endl;
        }
        else if (color == "green" || color == "Green")
        {
            (colordata[7][0] == ',' || colordata[7].empty()) ? cout << (char)26 << "No Car of this color." << endl : cout << colordata[7] << endl;
        }
        else if (color == "yellow" || color == "gold")
        {
            (colordata[8][0] == ',' || colordata[8].empty()) ? cout << (char)26 << "No Car of this color." << endl : cout << colordata[8] << endl;
        }
        else
        {
            cout << (char)26 << "No Car of this color." << endl;
        }
    }
    void findSlot(string carNum)
    {
        if (already(carNum))
        {
            string slot;
            ifstream f_read("DataBase.txt");
            string line;
            while (getline(f_read, line))
            {
                if (line.substr(0, 8) == "unparked")
                {
                    continue;
                }
                else if (line.substr(0, line.length() - 3) == carNum)
                {
                    slot = line.substr(line.length() - 2);
                    cout << (char)26 << "Slot no. :" << slot << endl;
                    return;
                }
            }
            f_read.close();
        }
        cout << (char)26 << "Slot is empty." << endl;
    }
    void findcarNumber(string slot)
    {
        string carNum;
        ifstream f_read("DataBase.txt");
        string line;
        while (getline(f_read, line))
        {
            if (line.substr(0, 8) == "unparked")
            {
                cout << (char)26 << "Car does't parked." << endl;
                f_read.close();
                return;
            }
            if (line.substr(line.length() - 2, line.length()) == slot)
            {
                carNum = line.substr(0, line.length() - 3);
                cout << (char)26 << "Car Number is :" << carNum << endl;
                f_read.close();
                return;
            }
        }
        f_read.close();
        cout << (char)26 << "Car does't parked." << endl;
    }
};

void info()
{
    cout << "______________________________________\n";
    cout << "Commands are:" << endl;
    cout << "create_parking_lot\tfind_car_number KL01R6699" << endl;
    cout << "park KA01R9988 \t\t find_parking_slot L5 or R5" << endl;
    cout << "unpark KA01R9977\t\tfind_car blue" << endl;
    cout << "type 1 to exit\tfilename.txt" << endl;
    cout << "______________________________________\n";
}
int main()
{
    info();
    string s;
    getline(cin, s);
    if (s == "1")
    {
        return 0;
    }
    else if (s.find('.') == string::npos)
    {
        if (s.substr(0, s.find(" ")) == "create_parking_lot")
        {

            int size = stoi(s.substr(s.length() - 2));
            CarParking P2(size);

            while (1)
            {
                string input;
                getline(cin, input);
                if (input == "1")
                {
                    return 0;
                }
                else if (input.substr(0, input.find(" ")) == "park")
                {
                    string carNum = input.substr(input.find(" ") + 1, input.length());
                    P2.park(carNum);
                }
                else if (input.substr(0, input.find(" ")) == "unpark")
                {
                    string carNum = input.substr(input.find(" ") + 1, input.length());
                    P2.unPark(carNum);
                }
                else if (input.substr(0, input.find(" ")) == "find_car")
                {
                    string color = input.substr(input.find(" ") + 1, input.length());
                    P2.colorCheck(color);
                }
                else if (input.substr(0, input.find(" ")) == "find_parking_slot")
                {
                    string slot = input.substr(input.find(" ") + 1, input.length());
                    P2.findcarNumber(slot);
                }
                else if (input.substr(0, input.find(" ")) == "find_car_number")
                {
                    string carNum = input.substr(input.find(" ") + 1, input.length());
                    P2.findSlot(carNum);
                }
                else
                {
                    cout << (char)26 << "Plz enter vaild command" << endl;
                }
            }
        }
        else
        {
            cout << (char)26 << "No parking lot exits." << endl;
        }
    }
    else
    {
        ifstream file(s);
        string line;
        getline(file, line);
        if (line.substr(0, line.find(" ")) == "create_parking_lot")
        {
            int size = stoi(line.substr(line.length() - 2));
            CarParking P1(size);
            while (getline(file, line))
            {
                if (line.substr(0, line.find(" ")) == "park")
                {
                    string carNum = line.substr(line.find(" ") + 1, line.length());
                    P1.park(carNum);
                }
                else if (line.substr(0, line.find(" ")) == "unpark")
                {
                    string carNum = line.substr(line.find(" ") + 1, line.length());
                    P1.unPark(carNum);
                }
                else if (line.substr(0, line.find(" ")) == "find_car")
                {
                    string color = line.substr(line.find(" ") + 1, line.length());
                    P1.colorCheck(color);
                }
                else if (line.substr(0, line.find(" ")) == "find_parking_slot")
                {
                    string slot = line.substr(line.find(" ") + 1, line.length());
                    P1.findcarNumber(slot);
                }
                else if (line.substr(0, line.find(" ")) == "find_car_number")
                {
                    string carNum = line.substr(line.find(" ") + 1, line.length());
                    P1.findSlot(carNum);
                }
                else
                {
                    cout << (char)26 << "Plz enter vaild command" << endl;
                }
            }
            while (1)
            {
                string input;
                getline(cin, input);
                if (input == "1")
                {
                    return 0;
                }
                else if (input.substr(0, input.find(" ")) == "park")
                {
                    string carNum = input.substr(input.find(" ") + 1, input.length());
                    P1.park(carNum);
                }
                else if (input.substr(0, input.find(" ")) == "unpark")
                {
                    string carNum = input.substr(input.find(" ") + 1, input.length());
                    P1.unPark(carNum);
                }
                else if (input.substr(0, input.find(" ")) == "find_car")
                {
                    string color = input.substr(input.find(" ") + 1, input.length());
                    P1.colorCheck(color);
                }
                else if (input.substr(0, input.find(" ")) == "find_parking_slot")
                {
                    string slot = input.substr(input.find(" ") + 1, input.length());
                    P1.findcarNumber(slot);
                }
                else if (input.substr(0, input.find(" ")) == "find_car_number")
                {
                    string carNum = input.substr(input.find(" ") + 1, input.length());
                    P1.findSlot(carNum);
                }
                else
                {
                    cout << (char)26 << "Plz enter vaild command" << endl;
                }
            }
        }
        else
        {
            cout << (char)26 << "No parking lot exits." << endl;
        }
    }
    return 0;
}
