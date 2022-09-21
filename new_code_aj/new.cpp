/* #include <iostream> */
/* #include <cctype> */
/* #include <string> */
using namespace std; 	

enum msgD{
	LEG,
	ARM };

msgD strTomsgD(string str){
	/* tolower(str); */
	if (str == "leg" ) return LEG;
	if (str == "arm" ) return ARM;
}

string msg;
switch (strTomsgD(msg)){
	case LEG: 
		break;
	case ARM:
		break;
	default:
		Serial.println("Command Not Found !");
}
