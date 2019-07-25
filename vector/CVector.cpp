#include <iostream>
#include <string>
using namespace std;

template<typename T>
class CVector{
private:
	T *first;
	int capacity;
	int size;
private:
	// 重新分配内存空间大小,改变capacity的大小,size大小不变
	void reserve(int newCapacity);
public:
	CVector();
	CVector(int len);
	CVector(int len, T t);
	CVector(T *begin, T *end);
	~CVector();
	T& operator[](int pos);
	CVector<T> &operator=(const CVector<T> &other);
	T *begin();
	T *end();
	T *find(const T &t);
	T back();
	int Size(){ return size; }
	int Capacity() { return capacity; }
	void clear();
	bool empty();
	void erase(T *pos);
	void erase(T *begin, T *end);
	void pop_back();
	void push_back(const T& t);
	T* insert(T *pos,const T &t);
	T* insert(T *pos, T *otherbegin, T  *otherend);
};

template<typename T>
T * CVector<T>::find(const T &t)
{
	for (int i = 0; i < size; i++){
		if (first[i] == t){
			//printf("%p %p  %d\n", first, first + i,i);
			return first + i;
		}

	}
	return end();
}


// 重新分配内存空间,已存在的数据复制到新的空间中
template<typename T>
void CVector<T>::reserve(int newCapacity)
{
	if (newCapacity < size)
		return;
	/*保存原有的指针地址*/
	T *tmp = first;
	/*为对象重新分配更大的内存空间*/
	first = new T[newCapacity];
	//把原来的数据拷贝回来
	for (int i = 0; i < size; i++){
		first[i] = tmp[i];
	}
	//内存空间大小发生变化，但是size没有变
	capacity = newCapacity;
	//删除原有的地址空间
	delete []tmp;
}

// 没参数的默认构造函数
template<typename T>
CVector<T>::CVector() :first(NULL), capacity(0), size(0)
{
}

//在指定地址pos之前插入另外一个向量的地址范围[otherbegin,otherend)中的元素
template<typename T>
T* CVector<T>::insert(T *pos, T *otherbegin, T *otherend)
{
	// 计算需要复制的元素个数
	int len = otherend - otherbegin;
	// 计算将要插入的下标地址
	int int_pos = pos - first;
	int tmp;
	if (len > 0 && int_pos >= 0 && int_pos <= size){
		//空间不足 则扩容空间
		if (capacity - size < len)
			reserve(2*capacity+len);
		tmp = size + len-1;
		//将待插入地址的数据往后移动
		while (tmp >= int_pos+len){
			first[tmp] = first[tmp - len];
			tmp--;
		}
		//对腾出来的空间赋值
		for (int i = 0; i < len; i++){
			first[int_pos + i] = *(otherbegin + i);
		}
		size += len;
		return first + int_pos;
	}
	return NULL;
}

template<typename T>
T* CVector<T>::insert(T *pos,const T &t)
{
	// 计算指针偏移量
	int int_pos = pos - first;
	int tmp;
	// 如果合法 则进行指针操作.
	if (int_pos >= 0 && int_pos <= size){
		//如果容量不足,扩容两倍空间
		if (size == capacity)
			reserve(2 * capacity + 1);
		tmp = size;
		//将待插入地址的数据往后移动
		while (tmp > int_pos){
			first[tmp] = first[tmp - 1];
			tmp--;
		}
		//对腾出来的空间赋值
		first[int_pos] = t;
		//元素个数+1
		size++;
		//返回新插入的元素地址
		return first + int_pos;
	}
	return NULL;
}

template<typename T>
void CVector<T>::push_back(const T &t)
{
	//判断是否还有空间
	if (size == capacity){
		//如果内存空间不够，在现有基础上扩容一倍
		reserve(2 * capacity + 1);
	}
	first[size++] = t;
}

//在cvector后面删除一个数据,无返回值
template<typename T>
void CVector<T>::pop_back()
{
	// 判断元素是否
	if (size > 0){
		size--;
	}
}

template<typename T>
void CVector<T>::erase(T *begin, T *end)
{
	int pos_begin = begin - first ;
	int pos_end = end - first;
	//判断是否合法
	if (pos_end > pos_begin && pos_begin >= 0 && pos_end <= size){
		//删除地址后的元素从后往前移动
		for (int i = pos_begin,j = pos_end; j < size ; i++,j++)
			first[i] = first[j];
		//大小-1
		size -=(end-begin);
	}
}

//删除指定地址的元素
template<typename T>
void CVector<T>::erase(T *pos)
{
	// 计算指针偏移量
	int int_pos = pos - first;
	//printf("%p %p %d %d %d\n", pos, first,pos-first,sizeof(T), int_pos);
	// 判断是否合法
	if (int_pos >= 0 && int_pos < size){
		//删除地址后的元素从后往前移动
		for (int i = int_pos; i < size - 1; i++)
			first[i] = first[i + 1];
		//大小-1
		size--;
	}
}

// 判断是否为空
template<typename T>
bool CVector<T>::empty()
{
	return size == 0;
}

/*删除所有元素,使向量成为空向量*/
template<typename T>
void CVector<T>::clear()
{
	if (first != NULL)
		delete []first;
	first = NULL;
	capacity = 0;
	size = 0;
}

//获取最后一个元素的值
template<typename T>
T CVector<T>::back()
{
	return first[size-1];
}

template<typename T>
T * CVector<T>::begin()
{
	return first;
}

template<typename T>
T * CVector<T>::end()
{
	return first + size;
}

//重载赋值操作符 
template<typename T>
CVector<T> & CVector<T>::operator=(const CVector<T> &other)
{
	//防止与本身发生拷贝
	if (this != &other){
		delete[]first;
		size = other.size;
		capacity = other.capacity;
		first = new T[capacity];
		for (int i = 0; i < size; i++){
			first[i] = other.first[i];
		}
	}
	return *this;
}

// 重载下标操作符
template<typename T>
T& CVector<T>::operator[](int pos)
{
	return first[pos];
}

template<typename T>
CVector<T>::~CVector()
{
	clear();
}

//创建一个CVector对象,内容是[begin,end)之间的数据
template<typename T>
CVector<T>::CVector(T *begin, T *end)
{
	capacity = end - begin;
	size = 0;
	first = new T[capacity];
	while (begin < end){
		first[size] = *begin;
		size++;
		begin++;
	}
}

//创建一个长度为len的 CVector,并且值为t
template<typename T>
CVector<T>::CVector(int len, T t) :capacity(len), size(len)
{
	first = new T[capacity];
	for (int i = 0; i < size; i++)
		first[i] = t;
}

//创建一个长度为len的 CVector
template<typename T>
CVector<T>::CVector(int len) :capacity(len), size(0)
{
	first = new T[capacity];
}


template<typename T>
void PrintCVector(std::string desc,CVector<T> &vec){
	T *begin = vec.begin();
	cout << desc.c_str() << endl;
	cout << "大小:" << vec.Size() << "  容量:" << vec.Capacity() << endl;
	for (; begin != vec.end(); begin++)
		std::cout << *begin << " ";
	std::cout << std::endl;
}

int main(){
	// 测试构造函数
	cout << "测试构造函数:" << endl;
	CVector<int> vec;
	PrintCVector<int>("测试1:", vec);
	CVector<int> vec1(5);
	PrintCVector<int>("测试2:", vec1);
	CVector<int> vec2(5,9);
	PrintCVector<int>("测试3:", vec2);
	int buf[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	CVector<int> vec3(buf+2,buf+6);
	PrintCVector<int>("测试4:", vec3);

	cout << "\n\n测试重载下表运算符:" << endl;
	cout << "vec3 第二个字符为:" << vec3[1] << endl;
	vec3[1] = 120;
	cout << "修改后vec3 第二个字符为:" << vec3[1] << endl;

	CVector<int> vec4;
	vec4= vec3;
	PrintCVector<int>("\n\n测试赋值运算符重载:", vec4);

	int *begin = vec4.begin();
	cout << "\n测试begin,vec4的第一个元素为:" << *begin << endl;
	int last = vec4.back();
	cout << "测试back,vec4的最后一个元素为:" << last << endl;

	cout << "\n\n测试empty():" << endl;
	if (vec.empty())
		cout << "vec 是空的" << endl;
	if (!vec4.empty())
		cout << "vec4 非空" << endl;

	cout << "\n\n测试clear():" << endl;
	vec4.clear();
	if (vec4.empty())
		cout << "clear()之后vec4 是空的" << endl;

	//void erase(T *pos);
	//void erase(T *begin, T *end);
	//void pop_back();
	//void push_back(const T& t);
	//T* insert(T *pos, const T &t);
	//T* insert(T *pos, T *otherbegin, T  *otherend);

	cout << "\n\n测试push_back:" << endl;
	CVector<int> vec5;
	vec5.push_back(11);
	PrintCVector<int>("push_back 11后:", vec5);
	vec5.push_back(22);
	PrintCVector<int>("push_back 22后:", vec5);
	vec5.push_back(33);
	PrintCVector<int>("push_back 33后:", vec5);
	vec5.push_back(44);
	PrintCVector<int>("push_back 44后:", vec5);
	vec5.push_back(55);
	PrintCVector<int>("push_back 55后:", vec5);

	cout << "\n\n测试pop_back:" << endl;
	CVector<int> vec6;
	vec6= vec5;
	vec6.pop_back();
	PrintCVector<int>("pop_back 后:", vec6);

	
	cout << "\n\n测试erase:" << endl;
	CVector<int> vec7;
	vec7= vec5;
	vec7.erase(vec7.find(33));
	PrintCVector<int>("erase 33 后:", vec7);

	CVector<int> vec8;
	vec8= vec5;
	vec8.erase(vec8.find(33),vec8.end());
	PrintCVector<int>("erase 33以后的数据:", vec8);

	cout << "\n\n测试insert:" << endl;
	CVector<int> vec9;
	for (int i = 0; i < 10; i++)
		vec9.insert(vec9.begin(), i);
	PrintCVector<int>("insert 0-9 后:", vec9);
	vec9.insert(vec9.find(6), buf + 2, buf + 4);
	PrintCVector<int>("在6前面插入 3,4 后:", vec9);
	//getchar();
	return 0;
}