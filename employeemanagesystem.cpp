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
void Ems::ShowEmp() {
    if (this->m_FileIsEmpty) {
        cout << "文件不存在, 或记录为空!" << endl;
    }
    else {
        for (size_t i = 0; i < m_EmpNum; i++) {
            this->m_EmpArray[i]->ShowInfo();
        }   
    }   
}
int Ems::IsExist(int id) {
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}
void Ems::DelEmp() {
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空!" << endl;
    }
    else
    {
        cout << "请输入需要删除的职工号: " << endl;
        int id = 0;
        cin >> id;
        int index = this->IsExist(id);
        if (index != -1) {
            delete this->m_EmpArray[index]; //可以不写, 直接用后面的值覆盖要删除的位置的值就好
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;
            this->m_FileIsEmpty = false;
            cout << "删除成功!" << endl;
            this->Save();
        }
    }
}
void Ems::ModEmp() {
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空!" << endl;
    }
    else
    {
        cout << "请输入需要修改的职工编号: " << endl;
        int id = 0;
        cin >> id;
        int ret = this->IsExist(id);
        if (ret != -1)
        {
            delete this->m_EmpArray[ret];
            int newId = 0;
            string newName = "";
            int dSelect = 0;
            cout << "查到: " << id << "号职工, 请输入新职工号: " << endl;
            cin >> newId;
            cout << "请输入新职工姓名: " << endl;
            cin >> newName;
            cout << "请选择新职工的岗位: " << endl;
            cout << "1. 普通员工" << endl;
            cout << "2. 经理" << endl;
            cout << "3. 老板" << endl;
            cin >> dSelect;
            Worker * worker = NULL;
            switch (dSelect) 
            {
            case 1:
                worker = new Employee(newId, newName, dSelect);
                break;
            case 2:
                worker = new Manager(newId, newName, dSelect);
                break;
            case 3:
                worker = new Boss(newId, newName, dSelect);
                break;
            default:
                break;
            }
            this->m_EmpArray[ret] = worker;
            cout << "修改成功!" << endl;
            this->Save();
        }
        else
        {
            cout << "查无此人!" << endl;
        }
    } 
}
void Ems::FindEmp() {
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空!" << endl;
    }
    else
    {
        cout << "请输入查找的方式: " << endl;
        cout << "1、按照职工查找" << endl;
        cout << "2、按姓名查找" << endl;
        int choice = 0;
        cin >> choice;
        if (choice == 1) {
            int id;
            cout << "请输入需要查找的职工号: " << endl;
            cin >> id;
            int ret = this->IsExist(id);
            if (ret!= -1) {
                cout << "查找成功!该职工信息如下: " << endl;
                this->m_EmpArray[ret]->ShowInfo();
            }
            else
            {
                cout << "查找失败, 查无此人! " << endl;
            } 
        }
        else if (choice == 2) {
            string name;
            cout << "请你输入查找的姓名: " << endl;
            cin >> name;
            bool flag = false;
            for (int i = 0; i < m_EmpNum; i++)
            {
                if (m_EmpArray[i]->m_Name == name)
                {
                    cout << "查找成功, 职工编号为: " << m_EmpArray[i]->m_Id << " 号的信息如下: " << endl;
                    flag = true;
                    this->m_EmpArray[i]->ShowInfo();
                }  
            }
            if (flag == false)
            {
                cout << "查无失败, 查无此人!" << endl;
            } 
        }
        else
        {
            cout << "输入选项有误" << endl;
        }  
    }    
}
void Ems::SortEmp() {
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空!" << endl;
    }
    else
    {
        cout << "请选择排序方式: " << endl;
        cout << "1.按职工号进行升序" << endl;
        cout << "2.按职工号进行降序" << endl;
        int select = 0;
        cin >> select;
        for (int i = 0; i < m_EmpNum; i++)
        {
            int minOrMax = i;
            for (int j = i + 1; j < m_EmpNum; j++)
            {
                if (select == 1) //升序
                {
                    if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else //降序
                {
                    if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    } 
                }
            }
            if (i != minOrMax)
            {
                Worker * temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
            }
        }
        cout << "排序成功, 排序后结果为: " << endl;
        this->Save();
        this->ShowEmp();
    }
}
void Ems::ClearAll() {
    cout << "确认清空?" << endl;
    cout << "1. 确认" << endl;
    cout << "2. 取消" << endl;
    int choice = 0;
    cin >> choice;
    if (choice == 1) {
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i] != NULL)
                {
                    delete this->m_EmpArray[i];
                }
            }
            this->m_EmpNum = 0;
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_FileIsEmpty = true;
        }
        cout << "清空成功! " << endl;
    }
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