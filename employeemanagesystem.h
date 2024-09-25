#pragma once 
#include <string>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include "fstream"
#define FILENAME "EmpFile.txt"
using namespace std;
class Ems {
public:
    Ems();
    void ShowMenu();
    void ExitSystem();
    void initEmp();
    void AddEmp();
    void Save();
    void ShowEmp();
    int IsExist(int id);
    void DelEmp();
    void ModEmp();
    void FindEmp();
    void SortEmp();
    void ClearAll();
    int GetEmpNum();
    ~Ems();
    int m_EmpNum;
    Worker ** m_EmpArray;
    bool m_FileIsEmpty = false; //判断文件是否为空

};