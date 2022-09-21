#include <iostream>
#include <string>
using namespace std; 	

enum msgD{
	LEG,
	ARM,
	Null};

msgD strTomsgD(string str){
	/* tolower(str); */
	if (str == "leg" ) return LEG;
	else if (str == "arm" ) return ARM;
	return Null;
}
int main(int argc, char *argv[])
{
	string msg;
	msgD dat;
	cin>>msg;
	dat = strTomsgD(msg);	
	if(dat == LEG){
		cout<<"legf";
	}
	if(dat == ARM){
		cout<<"armp";
	}
	
	return 0;
}
