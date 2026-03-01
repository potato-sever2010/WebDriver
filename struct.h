#ifndef STRUCT_H
#define STRUCT_H

// Birthday 结构体定义
struct Birthday {
    int year;   // 年份
    int month;  // 月份 (1-12)
    int day;    // 日期 (1-31)

    // 默认构造函数
    Birthday();

    // 带参数的构造函数
    Birthday(int y, int m, int d);

    // 验证日期是否合法
    bool isValid() const;
};

#endif // STRUCT_H