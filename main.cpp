/* AFTER INPUTING THE YEAR USE GETLINE FOR THE REST OF INFO, ALLOWS FOR MULTIPLE STRING VALUES WHILE SIMUTANIOUSLY IGNORING COMMAS

    goal(12/25/2015-12/27/2015)

    //format the output
    //get weekDay, month, day and year using cin()
    //and then compare them to pcWeek, pcMonth, pcDay, pcYear
    //thinking about leaving weekDay, month, day and year under one vairable using getline() and then adding pc string variables AND THEN comparing
    //example: getline(schedule, dates) which would containg something like Thu Oct 27 2015 and then adding pcWeek + pcMonth + pcDay + pcYear and comparing
    //dont really have to get the year since months dont repeat, just keep the file updated per season

    //function: converting system int dates to strings i.e switch case, data input from file

    //problems to fix: need to find a way to update the file via the internet that works on windows too

*/

#include <iostream>
#include <stdlib.h> //for system() function
#include <unistd.h> //for changing directories
#include <sys/stat.h> //for stat() function
#include <fstream>
#include <ctime>
#include <sstream> //for stringstream: convert int to string
#include <vector>

using namespace std;

void weekConvert(int &tempWeek_, string &pcWeek_); //converts tempWeek
void monthConvert(int &tempMonth_, string &pcMonth_); //converts tempMonth
void dataInput(ifstream &schedule_, vector<string> &weekDay_, vector<string> &time_, vector<string> &box_, vector<string> &team1_, vector<string> &team1Score_, vector<string> &team2_,
vector<string> &team2Score_, vector<string> &OT_, vector<string> &notes_, string userString); //gets data from file
int main()
{
    int changeDir, newDir;
    ifstream schedule;
    string a, b, c, userString; //to ignore first three lines
    vector<string> weekDay, times, box, team1, team1Score, team2, team2Score, OT, notes;
    string pcWeek, pcMonth, pcDay, pcYear; //system dates
    string pcDate; //final string for system date
    int tempMonth, tempYear, tempDay, tempWeek, i = 0;
    stringstream convertYear, convertDay;

    time_t t = time(0);   // get time now
    struct tm *now = localtime( &t );

    tempWeek = (now->tm_wday);
    tempMonth = (now->tm_mon + 1);
    tempDay = (now->tm_mday);
    tempYear = (now->tm_year + 1900);

    weekConvert(tempWeek, pcWeek); //converts tempWeek
    monthConvert(tempMonth, pcMonth); //converts tempMonth

    convertYear << tempYear; //converts years to string
    pcYear = convertYear.str();

    convertDay << tempDay; //converts days to string
    pcDay = convertDay.str();

    pcDate = pcWeek + " " + pcMonth + " " + pcDay + " " + pcYear;

    //newDir = system("mkdir NBAschedule"); //linux only command
    //changeDir = chdir("/home/dan/NBAschedule/"); //linux only command

    system("wget https://raw.githubusercontent.com/dm117/NBA-terminal/master/schedule.csv");

    schedule.open("schedule.csv");

    if (schedule.is_open())
    {

        getline(schedule, a);
        getline(schedule, b);
        getline(schedule, c);

        dataInput(schedule, weekDay, times, box, team1, team1Score, team2, team2Score, OT, notes, userString); //first read of the file

        do
        {
            if (weekDay[i] != pcDate)
            {
                dataInput(schedule, weekDay, times, box, team1, team1Score, team2, team2Score, OT, notes, userString); //calling the function if system date doesnt match
            }
            else
            {
                cout << weekDay[i] << endl;
                cout << times[i] << endl;
                cout << team1[i] << " " << team1Score[i] << endl;
                cout << team2[i] << " " << team2Score[i] << endl;
                cout << OT[i] << endl;
                cout << notes[i] << endl;
                cout << "\n" << endl;

                dataInput(schedule, weekDay, times, box, team1, team1Score, team2, team2Score, OT, notes, userString); //calling the input function

            }
            i++;

        }while(!schedule.eof());

        schedule.close();
    }
    else
    {
        cout << "Try running the program again, couldn't open the file" << endl;
    }

    cout << "\nEnd of program" << endl;
    cout << pcDate << endl;

    return 0;
}

void weekConvert(int &tempWeek_, string &pcWeek_)
{
    switch ( tempWeek_ )
    {
    case 0:
        pcWeek_ = "Sun";
        break;
    case 1:
        pcWeek_ = "Mon";
        break;
    case 2:
        pcWeek_ = "Tue";
        break;
    case 3:
        pcWeek_ = "Wed";
        break;
    case 4:
        pcWeek_ = "Thu";
        break;
    case 5:
        pcWeek_ = "Fri";
        break;
    case 6:
        pcWeek_ = "Sat";
        break;
    default:
        cout<<"ERROR GETTING DAY OF THE WEEK\n";
        break;
    }
}

void monthConvert(int &tempMonth_, string &pcMonth_)
{
    switch ( tempMonth_ )
    {
    case 1:
        pcMonth_ = "Jan";
        break;
    case 2:
        pcMonth_ = "Feb";
        break;
    case 3:
        pcMonth_ = "March";
        break;
    case 4:
        pcMonth_ = "Apr";
        break;
    case 5:
        pcMonth_ = "May";
        break;
    case 6:
        pcMonth_ = "Jun";
        break;
    case 7:
        pcMonth_ = "Jul";
        break;
    case 8:
        pcMonth_ = "Aug";
        break;
    case 9:
        pcMonth_ = "Sep";
        break;
    case 10:
        pcMonth_ = "Oct";
        break;
    case 11:
        pcMonth_ = "Nov";
        break;
    case 12:
        pcMonth_ = "Dec";
        break;
    default:
        cout<<"ERROR\n";
        break;
    }
}

void dataInput(ifstream &schedule_, vector<string> &weekDay_, vector<string> &time_, vector<string> &box_, vector<string> &team1_, vector<string> &team1Score_, vector<string> &team2_,
vector<string> &team2Score_, vector<string> &OT_, vector<string> &notes_, string userString_) //gets data from file
{

    getline(schedule_, userString_, ',');
    weekDay_.push_back(userString_);

    getline(schedule_, userString_, ',');
    time_.push_back(userString_);

    getline(schedule_, userString_, ',');
    box_.push_back(userString_);

    getline(schedule_, userString_, ',');
    team1_.push_back(userString_);

    getline(schedule_, userString_, ',');
    team1Score_.push_back(userString_);

    getline(schedule_, userString_, ',');
    team2_.push_back(userString_);

    getline(schedule_, userString_, ',');
    team2Score_.push_back(userString_);

    getline(schedule_, userString_, ',');
    OT_.push_back(userString_);

    getline(schedule_, userString_);
    notes_.push_back(userString_);

}

/*--------------------------------------------THIS WILL BE USE LATER TO CHECK IF THE DIRECTORY ALREADY EXISTS------------
struct stat statbuf;
int isDir = 0;
if (stat("/NBAschedule", &statbuf) != -1) {
   if (S_ISDIR(statbuf.st_mode)) {
      isDir = 1;
   }
} else {

       here you might check errno for the reason, ENOENT will mean the path
       was bad, ENOTDIR means part of the path is not a directory, EACCESS
       would mean you can't access the path. Regardless, from the point of
       view of your app, the path is not a directory if stat fails.

}

//Source: https://www.quora.com/How-do-I-check-if-a-directory-exists-in-Linux-using-C++
--------------------------------------------THIS WILL BE USE LATER TO CHECK IF THE DIRECTORY ALREADY EXISTS------------*/

