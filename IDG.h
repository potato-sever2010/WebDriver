#ifndef IDG_H
#define IDG_H

#include <cstdint>
#include "struct.h"

// 身份证校验码表
extern const char check_code[11];

// ID 结构体定义
struct ID {
    char IDc[18];       // 身份证号码（18位）
    char sex;           // 性别 ('m' 或 'f')
    bool isTrue;        // 是否为有效身份证
    bool isMale;        // 是否为男性
    Birthday birthday;  // 生日信息
    uint8_t age;        // 年龄

    // 构造函数：从输入字符串初始化身份证信息
    ID(const char* inID);
};

// 函数声明
char* IDG18(const char* inID);     // 生成18位身份证号码
bool isValidID(const char* inID);  // 验证身份证号码是否合法

#endif // IDG_H