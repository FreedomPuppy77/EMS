#include "manager.h"
#include <iostream>
using namespace std;
Manager::Manager(int id, string name, int dId) {
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}
void Manager::ShowInfo() {
    cout << "职工编号: " << this->m_Id 
         << "\t职工姓名: " << this->m_Name 
         << "\t岗位: " << this->GetDeptName() 
         << "\t岗位职责: 完成老板交给的任务, 并下发任务给员工!" << endl; 
}
string Manager::GetDeptName() {
    return string("经理");
}