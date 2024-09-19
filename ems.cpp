#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include "employeemanagesystem.h"
#include <iostream>
using namespace std;
void test() {
    Worker * worker = NULL;
    worker = new Employee(1, "张珊" , 1);
    worker->ShowInfo();
    delete worker;
    
    Manager * manager = NULL;
    manager = new Manager(2, "李四" , 2);
    manager->ShowInfo();
    delete manager;
    
    Boss * boss = NULL;
    boss = new Boss(3, "王五" , 3);
    boss->ShowInfo();
    delete boss;
}
int main() {
    Ems em;
    int choice = 0;
    while (true)
    {
        em.ShowMenu();
        cout << "请输入你的选择: " << endl;
        cin >> choice;
        switch (choice)
        {
        case 0:
            em.ExitSystem();
            break;
        case 1:
            em.AddEmp();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break; 
        case 6:
            break; 
        case 7:
            break;  
        default:
            break;
        }
    }
    
    
    // test();
    return 0;
 
}