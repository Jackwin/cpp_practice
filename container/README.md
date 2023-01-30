
# std::array

与`std::vector`相比，`std::array`是定长的，如果元素个数是固定的，优先考虑使用`std::array`

`std::vector`是变长的，随着元素个数的增多不断扩容。如果容器变长之后删除了一些元素，容器不会自动释放空间，需要手动使用 `shrink_to_fit()` 释放这部分内存


# std::queue

`queue`是类FIFO式的队，服从先进先出的规则，数据只能从头部出，从尾部插入。
支持的操作为
1. empty() 判断是否为空
2. push() 元素从队的尾部插入
3. pop() 首元素出队
4. front() 获得队首部的数据
5. back() 获得队尾部的数据
6. size() 队中数据元素的个数


# std::deque
`std::deque`是双端队列，可以向两端发展，是由一段一段连续的空间构成，缺点是向中间插入元素费时，需要移动其他元素

支持的操作：
1. size()
2. max_size()
3. resize()
4. empty() 判断是否为空
5. shrink_to_fit()缩减容器大小适配数据量
6. push_front()头部添加元素
7. push_back() 尾部添加元素
8. insert(iterator, const T& x) 指定位置添加元素
9. insert(iterator it, iterator first, iterator last) 插入另一个向量的 [forst,last] 间的数据
10. pop_front() 删除第一个元素
11. pop_back() 删除尾部元素
12. erase(iterator it) 删除任意位置的一个元素
13. erase(iterator first, iterator last) 删除
14. clear() 清空
15. front() 访问第一个元素 
16. back() 访问尾部元素
17. at(int i) 访问第i个元素，会判断是否越界；deque[i] 访问第i个元素，不判断是否越界
18. begin() 首部迭代器指针  end()尾部迭代器指针 


# unorder_map

unorder_map以key-value的方式存储数据对<key,value>,存储时根据key的hash值判断是否相同，unorder_map内部的元素是无序的

支持的操作：
1. 迭代器 begin()返回迭代器的头部，end()返回迭代器的尾部
2. empty() 容器是否为空，size()容器中元素的个数，max_size()最大数量的元素
3. Modifier
- clear()清空容器
- insert() 插入。将元素对象传递给insert(),这些对象被拷贝到容器中
- emplace() 构造元素。调用emplace()是将参数传给元素类型的构造函数，emplace使用这些元素在容器所属的内存中直接构造元素。emplace()和insert()相比，通过构造的方式进行元素的插入，减少了内存拷贝和移动

# 时间字符串和时间戳的转换

时间戳：格林威治时间1970年01月01日00时00分00秒(北京时间1970年01月01日08时00分00秒)起至现在的总秒数,数据类型为time_t类型，是一个长整数

时间字符串: 2023-1-23 19:00:00，数据类型为tm结构体
```C++
struct tm {
        int tm_sec;     /* seconds after the minute - [0,59] */
        int tm_min;     /* minutes after the hour - [0,59] */
        int tm_hour;    /* hours since midnight - [0,23] */
        int tm_mday;    /* day of the month - [1,31] */
        int tm_mon;     /* months since January - [0,11] */
        int tm_year;    /* years since 1900 */
        int tm_wday;    /* days since Sunday - [0,6] */
        int tm_yday;    /* days since January 1 - [0,365] */
        int tm_isdst;   /* daylight savings time flag */
        };
time_t time(time_t *t);// 转为从1970年01月01日开始的秒数

char *asctime(const struct tm *tm); //将tm结构体中的时间转换为字符串时间

struct tm *gmtime(const time_t *timep); //将time_t表示的时间转换为没有经过时区转换的UTC时间，是一个struct tm结构指针 

struct tm *localtime(const time_t *timep); //和gmtime类似，但是它是经过时区转换的时间。

time_t mktime(struct tm *tm); //将struct tm 结构的时间转换为从1970年至今的秒数

int gettimeofday(struct timeval *tv, struct timezone *tz); //返回当前距离1970年的秒数和微妙数，后面的tz是时区，一般不用

double difftime(time_t time1, time_t time2); //返回两个时间相差的秒数

```

```C++
//<ctime>
// 根据format中的格式化规则，将tm结构体中的时间转为字符串时间，存在str中，比如将本地时间转为字符串时间
//
size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr)
```
|格式符号|解释|范例|
|---|---|---|
|%a|	缩写的星期几名称|	Sun|
|%A|	完整的星期几名称|	Sunday|
|%b|	缩写的月份名称|	Mar|
|%B|	完整的月份名称|	March|
|%c|	日期和时间表示法|	Sun Aug 19 02:56:02 2012|
|%d|	一月中的第几天（01-31）|	19|
|%H|	24 小时格式的小时（00-23）|	14|
|%I|	12 小时格式的小时（01-12）|	05|
|%j|	一年中的第几天（001-366）|	231|
|%m|	十进制数表示的月份（01-12）|	08|
|%M|	分（00-59）|	55|
|%p|	AM 或 PM 名称	|PM|
|%S|	秒（00-61）|	02|
|%U|	一年中的第几周,以第一个星期日作为第一周的第一天（00-53）|	33|
|%w|	十进制数表示的星期几，星期日表示为 0（0-6）|	4|
|%W|	一年中的第几周,以第一个星期一作为第一周的第一天（00-53）|	34|
|%x|	日期表示法|	08/19/12|
|%X|	时间表示法|	02:50:06|
|%y|	年份，最后两个数字（00-99）|	01|
|%Y|	年份	|2012|
|%Z|	时区的名称或缩写|	CDT|
|%%|	一个 % 符号 |	%|
