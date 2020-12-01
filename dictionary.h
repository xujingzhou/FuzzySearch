// ============================================================================
// 类名：Dictionary
// 说明：从hashset哈希表派生，导入字典并进行保存的字典类
// 备注：
// 编写：徐景周(jingzhou_xu@163.com)
// 组织：未来工作室(Future Studio)
// 日期：2005.12.1
// =============================================================================
#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#pragma warning(disable:4786)		// 屏蔽掉VC6编释STL时出现的4786号警告消息

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function
{
public:
    hash_function() {}

	// 哈希散列涵数，返回计算后的散列地址
    unsigned int operator()( const string& s )  const 
	{
		
       unsigned int h	= 0;
	   const char* pStr = s.c_str();

	   // 置乘法器为hashset类中素数数组prime_list中第一个元素值(53)
	   for( ; *pStr; ++pStr )
		   h = prime_list[0] * h + *pStr;

	   return h;
    }
};

class equality
{
public:
    equality() {}
    bool  operator()( const string& A, const string& B )  const 
	{
		return  (A == B);
    }
};

class Dictionary: public HashSet<string, hash_function, equality> 
{
public:

	// 导入字典文件(wordlist.txt)内容到哈希表中
    Dictionary( string strFilename ) : HashSet<string, hash_function, equality>()
	{
		// 打开字典文件
		ifstream inf( strFilename.c_str() );
		if( !inf ) 
		{
			cerr << "Could not open dictionary:" << strFilename << "\n";
			return;
		}

		while( inf ) 
		{
			// 从输入文件流中读取一行
			string line;
			getline(inf, line);

			// 将从字典文件中读取的每一行插入哈希表中(父类HashSet中)
			insert( line );

			// 输出导入字典的过程
//			cout << line << endl;
		}
	}

};

#endif
