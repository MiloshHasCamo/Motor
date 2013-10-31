#include "Motor-Engine-Header.h"

int main ( int argc, char* argv [ ] )
{
	char* ans = new char[ 256 ];
	cout << "Are You Zohar?" << endl;
	cin >> ans;
	if( ans == "yes" || ans == "YES" )
	{
		cout << "Good, goodbye.." << endl;
		getchar( );
		return 0;
	}
}