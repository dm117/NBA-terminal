/*

-----------------termcolor library used for color output-----------------
Copyright (c) 2013 by Igor Kalnitsky
license BSD, see LICENSE for details
-------------------------------------------------------------------------

NBA-terminal is a simple open-source, simplistic terminal application that displays the NBA schedule for the day.
Copyright (c) 2013, Daniel Maria All rights reserved.
License BSD, see LICENSE for details

problems to fix: need to find a way to download the file via the internet that works on windows too

*/

#include <iostream>
#include <stdlib.h> //for system() function
#include <unistd.h> //for changing directories
#include <sys/stat.h> //for stat() function
#include <fstream>
#include <ctime>
#include <sstream> //for stringstream: convert int to string
#include <vector>
#include <iomanip> //output manipulators
#include "termcolor.hpp" //header only library for colored output

using namespace std;

void weekConvert(int &tempWeek_, string &pcWeek_); //converts tempWeek
void monthConvert(int &tempMonth_, string &pcMonth_); //converts tempMonth
void dataInput(ifstream &schedule_, vector<string> &weekDay_, vector<string> &time_, vector<string> &box_, vector<string> &team1_, vector<string> &team1Score_, vector<string> &team2_,
vector<string> &team2Score_, vector<string> &OT_, vector<string> &notes_, string userString); //gets data from file
void outFunction(vector<string> &team_, vector<int> &placeHolder_, int &numb);
int main()
{
    int changeDir, newDir;
    ifstream schedule;
    string a, b, c, userString; //to ignore first three lines
    vector<string> weekDay, times, box, team1, team1Score, team2, team2Score, OT, notes;
    vector<int> placeHolder;
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
                placeHolder.push_back(i); //holds the location of today's games

                dataInput(schedule, weekDay, times, box, team1, team1Score, team2, team2Score, OT, notes, userString); //calling the input function
            }

            i++; //put this int the else statement and delete the output then print out formatted date after the loop

        }while(!schedule.eof());

        schedule.close();

        int one = 0;
        int two = 0;
        int three = 0;
        int four = 0;
        int five = 0;
        int six = 0;
        int seven = 0;
        int y = 0;
        int i = 0;
        int z = 2;

        for(i; i < placeHolder.size(); i++)
        {
            cout << termcolor::cyan << setw(30) << left << weekDay[placeHolder[i]] << setw(5) << " ";//22
	    cout << termcolor::reset;

            if (i == placeHolder.size() - 1)
                {
                    y = 1;

                        if(placeHolder.size()%2)
                        {
                            z = 1;
                        }
                }

            if(y == 1)
            {

                cout << endl;
                for(int x = 0; x < z; x++) //need to find a way to continue
                {
                    cout << termcolor::cyan << setw(30) << left << times[placeHolder[one]] << setw(5) << " ";//29
		    cout << termcolor::reset;
                    one++;
                }
                cout << endl;
		for(int x = 0; x < z; x++)
                {
			outFunction(team1,placeHolder,two);
			two++;              				
                }
                for(int x = 0; x < z; x++)
                {
                    cout << team1Score[placeHolder[three]];
                    three++;
                }
                cout << endl;
                for(int x = 0; x < z; x++)
                {
                    //cout << setw(30) << left << team2[placeHolder[four]] << setw(5) << " ";//23
		    outFunction(team2,placeHolder,four);
                    four++;
                }

                for(int x = 0; x < z; x++)
                {
                    cout << team2Score[placeHolder[five]];
                    five++;
                }
                cout << endl;
                for(int x = 0; x < z; x++)
                {
                    cout << OT[placeHolder[six]];
                    six++;
                }
                cout << endl;
                for(int x = 0; x < z; x++)
                {
                    cout << notes[placeHolder[seven]];
                    seven++;
                }

                y = 0;

                cout << "\n\n" << endl;
            }
            else
            {
                y++;
            }
        }
        
        cout << "\nAll times are in EST" << endl;

    }
    else
    {
        cout << "Couldn't find the file, downloading now...please re-run the program" << endl;
        system("wget https://raw.githubusercontent.com/dm117/NBA-terminal/master/schedule.csv");
        cout << termcolor::on_red << "\n\nDownloaded file, re-run the program..." << endl;
	cout << termcolor::reset << endl;
    }

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
void outFunction(vector<string> &team1_, vector<int> &placeHolder_, int &two_)
{
	if (team1_[placeHolder_[two_]] == "Miami Heat" || team1_[placeHolder_[two_]] == "Toronto Raptors" || team1_[placeHolder_[two_]] == "Chicago Bulls" || team1_[placeHolder_[two_]] == "Atlanta Hawks" || team1_[placeHolder_[two_]] == "Portland Trail Blazers" || team1_[placeHolder_[two_]] == "Los Angeles Clippers" || team1_[placeHolder_[two_]] == "Houston Rockets" || team1_[placeHolder_[two_]] == "Phoenix Suns")
	{
		cout <<  termcolor::red << setw(30) << left << team1_[placeHolder_[two_]] << setw(5) << " ";//22
	}
	else if (team1_[placeHolder_[two_]] == "New York Knicks" || team1_[placeHolder_[two_]] == "Detroit Pistons" || team1_[placeHolder_[two_]] == "Orlando Magic" || team1_[placeHolder_[two_]] == "Washington Wizards" || team1_[placeHolder_[two_]] == "Oklahoma City Thunder" || team1_[placeHolder_[two_]] == "Utah Jazz" || team1_[placeHolder_[two_]] == "Dallas Mavericks" || team1_[placeHolder_[two_]] == "Memphis Grizzlies")
	{
		cout << termcolor::blue << setw(30) << left << team1_[placeHolder_[two_]] << setw(5) << " ";//22
	}
	else if (team1_[placeHolder_[two_]] == "Boston Celtics" || team1_[placeHolder_[two_]] == "Milwaukee Bucks" || team1_[placeHolder_[two_]] == "Minnesota Timberwolves")
	{
		cout << termcolor::green << setw(30) << left << team1_[placeHolder_[two_]] << setw(5) << " ";//22
	}
	else if (team1_[placeHolder_[two_]] == "Cleveland Cavaliers" || team1_[placeHolder_[two_]] == "Indiana Pacers" || team1_[placeHolder_[two_]] == "Denver Nuggets" || team1_[placeHolder_[two_]] == "Golden State Warriors" || team1_[placeHolder_[two_]] == "Los Angeles Lakers")
	{
		cout << termcolor::yellow << setw(30) << left << team1_[placeHolder_[two_]] << setw(5) << " ";//22		
	}
	else if (team1_[placeHolder_[two_]] == "Charlotte Hornets" || team1_[placeHolder_[two_]] == "Sacramento Kings")
	{
		cout << termcolor::magenta << setw(30) << left << team1_[placeHolder_[two_]] << setw(5) << " ";//22		
	}
	else if (team1_[placeHolder_[two_]] == "Brooklyn Nets" || team1_[placeHolder_[two_]] == "Philadelphia 76ers" || team1_[placeHolder_[two_]] == "New Orleans Pelicans" || team1_[placeHolder_[two_]] == "San Antonio Spurs")
	{
		cout << termcolor::white << setw(30) << left << team1_[placeHolder_[two_]] << setw(5) << " ";//22		
	}
		
		cout << termcolor::reset;
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

