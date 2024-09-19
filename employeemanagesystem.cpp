#include "employeemanagesystem.h"
#include <iostream>
using namespace std;
Ems::Ems() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    //文件不存在的情况
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        this->m_EmpNum = 0;//初始化人数
        this->m_FileIsEmpty = true;
        this->m_EmpArray = NULL;
        ifs.close();
        return;
    }
    //文件存在, 并且没有记录
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        cout << "文件为空!" << endl;
        this->m_EmpNum = 0;//初始化人数
        this->m_FileIsEmpty = true;
        this->m_EmpArray = NULL;
        ifs.close();
        return;
    }
    int num = this->GetEmpNum();
    cout << "职工个数为: " << num << endl; //测试代码
    this->m_EmpNum = num;
    	//根据职工数创建数组
	this->m_EmpArray = new Worker *[this->m_EmpNum];
	//初始化职工
	initEmp();

	//测试代码
	// for (int i = 0; i < m_EmpNum; i++)
	// {
	// 	cout << "职工号： " << this->m_EmpArray[i]->m_Id
	// 		<< " 职工姓名： " << this->m_EmpArray[i]->m_Name
	// 		<< " 部门编号： " << this->m_EmpArray[i]->m_DeptId << endl;
	// }
}
void Ems::ShowMenu() {
    cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
void Ems::initEmp() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int dId;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId )
    {
        Worker *worker = NULL;
        if (dId == 1)
        {
            worker = new Employee(id, name, dId);
        }
        else if (dId == 2)
        {
            worker = new Manager(id, name, dId);
        }
        else
        {
            worker = new Boss(id, name, dId);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    
}
void Ems::AddEmp() {
    cout << "请输入增加员工的数量: " << endl;
    int AddNum = 0;
    cin >> AddNum;
    if (AddNum > 0)
    {
        int NewSize = this->m_EmpNum + AddNum;
        Worker **newspace = new Worker*[NewSize];
        if (this->m_EmpArray != NULL) {
            for (int i = 0; i < this->m_EmpNum; i++) {
                newspace[i] = this->m_EmpArray[i];
            }
        }
        for (int i = 0; i < AddNum; i++) {
            int id;
            string name;
            int dSelect;
            cout << "请输入第" << i + 1 << "个新职工的编号: " << endl;
            cin >> id;
            cout << "请输入第" << i + 1 << "个新职工的姓名: " << endl;
            cin >> name;
            cout << "请选择该职工的岗位: " << endl;
            cout << "1. 普通员工" << endl;
            cout << "2. 经理" << endl;
            cout << "3. 老板" << endl;
            cin >> dSelect;
            Worker *worker = NULL;
            switch (dSelect) {
                case 1:
                    worker = new Employee(id, name, 1);
                    break;
                case 2:
                    worker = new Manager(id, name, 2);
                    break;
                case 3:
                    worker = new Boss(id, name, 3);
                    break;
                default:
                    break;
            }
            newspace[this->m_EmpNum + i] = worker;
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = newspace;
        this->m_EmpNum = NewSize;
        this->m_FileIsEmpty = false; //更新职工不为空
        cout << "成功添加" << AddNum << "个新职工！" << endl;
        this->Save();
    }
    else {
        cout << "输入有误, 请重新输入!" << endl;
    }
}
void Ems::ExitSystem() {
    cout << "欢迎下次使用！" << endl;
    exit(0);
}
void Ems::Save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " " 
            << this->m_EmpArray[i]->m_Name << " " 
            << this->m_EmpArray[i]->m_DeptId << endl;
    }
    ofs.close();
}
int Ems::GetEmpNum() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int dId;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        num ++;
    }
    ifs.close();
    return num;
}
Ems::~Ems() {
    if (this->m_EmpArray != NULL)
    {
        delete[] this->m_EmpArray;
    } 
}