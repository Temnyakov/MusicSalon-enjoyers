#include "../include/authentication.h"

using namespace std;

int main() {
    cout<<"TESTS FOR authentication.cpp:"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    {
	cout<<"Test 1:"<<endl;
	sqlite3_database users_data(users_db_path);
	users_data.insert(users_db_create);
	if(m_log_in(users_data))
		cout<<"true"<<endl;
	else
		cout<<"false"<<endl;
    }
    {
	cout<<"Test 2:"<<endl;
	authenticate_user();
    }
    {
	cout<<"Test 3:"<<endl;
	
    }
    cout<<"TESTS FOR sqlite3_database.cpp:"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    {
        cout<<"Test 1:"<<endl;
    }
    {
        cout<<"Test 2:"<<endl;
        
    }
    {
        cout<<"Test 3:"<<endl;

    }
    cout<<"TESTS FOR aes128.cpp:"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    {
        cout<<"Test 1:"<<endl;
    }
    {
        cout<<"Test 2:"<<endl;

    }
    {
        cout<<"Test 3:"<<endl;

    }
    cout<<"TESTS FOR MD5.cpp:"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    {
        cout<<"Test 1:"<<endl;
    }
    {
        cout<<"Test 2:"<<endl;

    }
    {
        cout<<"Test 3:"<<endl;

    }

    return 0;
}
