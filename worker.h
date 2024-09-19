#pragma once
#include <iostream>
#include <string>
using namespace std;
class Worker {
public:
    virtual void ShowInfo() = 0; // 纯虚函数
    virtual string GetDeptName() = 0;
    int m_Id;
    string m_Name;
    int m_DeptId;
};