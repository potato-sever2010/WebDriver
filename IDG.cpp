#include "IDG.h"
#include "struct.h"
#include <chrono>
#include <iostream>
#include <cstring> // 替换 string.h 为 cstring

struct ID {
    char IDc[18] = {}; // 身份证号
    char sex;          // 性别 ('m' 或 'f')
    bool isTrue = false; // 是否有效身份证
    bool isAdult = false; // 是否成年
    Birthday birthday;   // 生日信息
    uint8_t age = 0;     // 年龄

    ID(const char* inID, int nowyear) {
        memcpy(IDc, inID, 18); // 拷贝身份证号
        isTrue = isValidID(IDc); // 验证身份证有效性
        if (!isTrue) {
            std::cerr << "Invalid ID number!" << std::endl;
            return;
        }

        // 提取生日信息
        birthday.year = (IDc[6] - '0') * 1000 + (IDc[7] - '0') * 100 + (IDc[8] - '0') * 10 + (IDc[9] - '0');
        birthday.month = (IDc[10] - '0') * 10 + (IDc[11] - '0');
        birthday.day = (IDc[12] - '0') * 10 + (IDc[13] - '0');
		birthday.isValid();
        // 计算年龄
        age = nowyear - birthday.year;

        // 判断性别
        sex = (IDc[16] % 2 == 1) ? 'm' : 'f';

        // 判断是否成年
        isAdult = birthday.isValid() && age >= 18;
    }
};

// 校验码表
constexpr char check_code[11] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};

// 生成18位身份证号
char* IDG18(const char* inID) {
    if (strlen(inID) != 17) {
        std::cerr << "错误：输入必须是17位身份证号码！" << std::endl;
        return nullptr;
    }

    // 计算校验码
    char checkCode = check_code[
        (7 * (inID[0] - '0') + 9 * (inID[1] - '0') + 10 * (inID[2] - '0') +
         5 * (inID[3] - '0') + 8 * (inID[4] - '0') + 4 * (inID[5] - '0') +
         2 * (inID[6] - '0') + 1 * (inID[7] - '0') + 6 * (inID[8] - '0') +
         3 * (inID[9] - '0') + 7 * (inID[10] - '0') + 9 * (inID[11] - '0') +
         10 * (inID[12] - '0') + 5 * (inID[13] - '0') + 8 * (inID[14] - '0') +
         4 * (inID[15] - '0') + 2 * (inID[16] - '0')) % 11];

    // 构造完整身份证号
    static char outID[19]; // 使用静态数组避免悬空指针
    memcpy(outID, inID, 17);
    outID[17] = checkCode;
    outID[18] = '\0';

    return outID;
}

// 验证18位身份证号
bool isValidID(const char* inID) {
    if (strlen(inID) != 18) {
        std::cerr << "错误：输入必须是18位身份证号码！" << std::endl;
        return false;
    }

    // 计算期望校验码
    char expectedCheckCode = check_code[
        (7 * (inID[0] - '0') + 9 * (inID[1] - '0') + 10 * (inID[2] - '0') +
         5 * (inID[3] - '0') + 8 * (inID[4] - '0') + 4 * (inID[5] - '0') +
         2 * (inID[6] - '0') + 1 * (inID[7] - '0') + 6 * (inID[8] - '0') +
         3 * (inID[9] - '0') + 7 * (inID[10] - '0') + 9 * (inID[11] - '0') +
         10 * (inID[12] - '0') + 5 * (inID[13] - '0') + 8 * (inID[14] - '0') +
         4 * (inID[15] - '0') + 2 * (inID[16] - '0')) % 11];

    return inID[17] == expectedCheckCode;
}