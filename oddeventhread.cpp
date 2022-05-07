/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

std::mutex m;
std::condition_variable con;
bool flag = false;
int count = 10;
void printEven(){
    int i=0;
    while(i<=count){
        std::unique_lock<std::mutex> l(m);
        con.wait(l,[](){return !flag;});
        cout<<i<<endl;
        i = i+2;
        flag = true;
        con.notify_one();
    }
}

void printOdd(){
    int i=1;
    while(i<=count){
        std::unique_lock<std::mutex> l(m);
        con.wait(l,[](){return flag;});
        cout<<i<<endl;
        i = i+2;
        flag = false;
        con.notify_one();
    }
}
int main()
{
    //cout<<"Hello World";
    std::thread st(&printEven);
    std::thread st1(&printOdd);
    /*
    {
        std::unique_lock<std::mutex> l(m);
        cout<<"inside here here here....";
        flag = true;
        con.notify_one();
    }
    */
    st.join();
    st1.join();
    return 0;
}
