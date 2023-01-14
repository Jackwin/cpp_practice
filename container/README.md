
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