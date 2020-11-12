// Author: Sneha Sirnam
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;
struct Results
{
    int bibnumber;
    string name;
    double distance;
    string time;
};

double avgSpeed(double,string);
double funcForHrs(string);

double funcForHrs(string time)
{

    string hh,mm,ss;
    stringstream sin(time);
    getline(sin,hh,':');
    getline(sin,mm,':');
    sin>>ss;
    int hrs,mins,secs;

    istringstream(hh)>> hrs;
    istringstream(mm)>> mins;
    istringstream(ss)>> secs;
    int totalTimeInSeconds=hrs*3600+(mins*60)+secs;
    double totalTimeInHrs=(double)totalTimeInSeconds/3600;

    return totalTimeInHrs;
}

double avgSpeed(double distance,string time)
{

    double totalTime = funcForHrs(time);
    double avgSpeedMileperHr=distance/totalTime;
    return avgSpeedMileperHr;

}

void showArray( Results array[], int size)
{
    cout << setw(5)<< "BibNum" <<setw(10)<< "Name"<<
         setw(20)<< "Distance" <<setw(12)<< "Time"
         <<setw(17)<<"Avg Spd"<<endl;
    for (int count = 0; count < size; count++)
    {
        cout<< fixed << setprecision(1);
        cout << setw(5)<< array[count].bibnumber<<setw(15)
             << array[count].name<<setw(15)
             << array[count].distance <<setw(15)
             << array[count].time<<setw(15)
             <<avgSpeed(array[count].distance,array[count].time)
             <<endl;
    }

}

void bubbleSort(Results array[], int size)
{
    bool swap;
    Results temp;
    do
    {
        swap = false;
        for (int count = 0; count < (size - 1); count++)
        {
            if (array[count].bibnumber > array[count + 1].bibnumber)
            {
                temp = array[count];
                array[count] = array[count + 1];
                array[count + 1]= temp;
                swap = true;
            }
        }
    }
    while (swap);
}

void bubbleSortDistanceTime(Results array[], int size)
{
    bool swap;
    Results temp;
    do
    {
        swap = false;
        for (int count = 0; count < (size - 1); count++)
        {
            if (array[count].distance < array[count + 1].distance)
            {
                temp = array[count];
                array[count] = array[count + 1];
                array[count + 1]= temp;
                swap = true;
            }
            else if(array[count].distance == array[count + 1].distance)
            {
                double t1=funcForHrs(array[count].time);
                double t2=funcForHrs(array[count+1].time);
                if(t1>t2)
                {
                    temp = array[count];
                    array[count] = array[count + 1];
                    array[count + 1]= temp;
                    swap = true;

                }
            }
        }
    }
    while (swap);
}

int searchList(Results list[], int numElems, string value)
{
    int index = 0;
    int position = -1;
    bool found = false;
    while (index < numElems && !found)
    {
        string enteredValue = list[index].name;

        if (enteredValue==value)
        {
            found = true;
            position = index;
        }
        index++;
    }
    return position;
}

int binarySearch(Results array[], int size, int value)
{
    int first = 0,
        last = size - 1,
        middle,
        position = -1;
    bool found = false;
    while (!found && first <= last)
    {
        middle = (first + last) / 2;
        if (array[middle].bibnumber == value)
        {
            found = true;
            position = middle;
        }
        else if (array[middle].bibnumber > value)
            last = middle - 1;
        else
            first = middle + 1;
    }
    return position;
}

int main()
{
    ifstream fin;
    Results resultarray[100];
    int i=0,choice;

    fin.open("dataset.txt");

    while (fin>>resultarray[i].bibnumber)

    {
        fin>>ws;
        getline(fin,resultarray[i].name);
        fin>>resultarray[i].distance;
        fin>>ws;
        getline(fin,resultarray[i].time);
        i++;
    }
    int actualCount=i;
    do
    {
        cout << "\n\t\tMenu\n\n"
             << "1. Display Results sorted by bib number\n"
             << "2. Display Results sorted by distance, then time\n"
             << "3. Lookup a bib number given a name\n"
             << "4. Lookup a result by bib number\n"
             << "5. Quit the Program\n"
             << "Enter your choice: ";
        cin >> choice;
        while (choice < 1 || choice > 5)
        {
            cout << "Please enter a valid menu choice: ";
            cin >> choice;
        }
        if (choice != 5)
        {
            switch (choice)
            {
            case 1:
                bubbleSort(resultarray, actualCount);
                showArray(resultarray,actualCount);
                break;
            case 2:
                bubbleSortDistanceTime(resultarray,actualCount);
                showArray(resultarray,actualCount);
                break;
            case 3:
            {
                string racername;
                int found;
                cout<<"Enter name of a racer to look for:" ;
                cin.ignore();
                getline(cin,racername);
                found = searchList(resultarray, actualCount,racername );
                if (found == -1)
                    cout << "Name of the racer entered is incorrect";
                else
                {
                    cout << "The number of the racer with name "
                         << resultarray[found].name<< " is: ";
                    cout << resultarray[found].bibnumber << endl;
                }

                break;
            }
            case 4:
                int bibno,foundvalue;
                cout << "Enter number of a racer to look for:";
                cin >>bibno ;
                bubbleSort(resultarray, actualCount);
                foundvalue = binarySearch(resultarray, actualCount, bibno);
                if (foundvalue == -1)
                    cout << "No racer found with number: "<<bibno<<endl;
                else
                {
                    cout<<fixed<<setprecision(1);
                    cout << setw(5)<< resultarray[foundvalue].bibnumber
                    <<setw(15)<< resultarray[foundvalue].name
                    <<setw(15)<< resultarray[foundvalue].distance
                    <<setw(15)<< resultarray[foundvalue].time
                    <<setw(15)<<avgSpeed(resultarray[foundvalue].distance,
                                    resultarray[foundvalue].time)<< endl;
                }

                break;

            }
        }
    }
    while (choice!=5);
    cout<<"Exiting the program...";

    return 0;

}
