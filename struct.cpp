#include "struct.h"
#include <iostream>

// 默认构造函数：初始化为合法的默认日期
Birthday::Birthday() : year(1900), month(1), day(1) {}

// 带参构造函数：初始化生日并验证合法性
Birthday::Birthday(int y, int m, int d) : year(y), month(m), day(d) {
    if (!isValid()) {
        // 打印错误信息代替抛出异常
        std::cerr << "Invalid birthday: ";
        if (month < 1 || month > 12)
            std::cerr << "Month must be between 1 and 12.";
        else if (day < 1 || day > 31)
            std::cerr << "Day must be between 1 and 31.";
        else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            std::cerr << "This month has only 30 days.";
        else if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > (isLeapYear ? 29 : 28))
                std::cerr << "February has fewer days in this year.";
        } else {
            std::cerr << "Date is out of range or invalid.";
        }
        std::cerr << std::endl;

        // 将非法日期重置为默认值
        year = 1900;
        month = 1;
        day = 1;
    }
}

// 验证日期是否合法
bool Birthday::isValid() const {
    // 快速排除非法月份和日期
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // 使用查表法优化天数判断
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDay = daysInMonth[month - 1];

    // 处理闰年情况
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        maxDay += isLeapYear ? 1 : 0;
    }

    return day <= maxDay;
}