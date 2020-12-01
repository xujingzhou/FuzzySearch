// ============================================================================
// ������Dictionary
// ˵������hashset��ϣ�������������ֵ䲢���б�����ֵ���
// ��ע��
// ��д���쾰��(jingzhou_xu@163.com)
// ��֯��δ��������(Future Studio)
// ���ڣ�2005.12.1
// =============================================================================
#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#pragma warning(disable:4786)		// ���ε�VC6����STLʱ���ֵ�4786�ž�����Ϣ

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

	// ��ϣɢ�к��������ؼ�����ɢ�е�ַ
    unsigned int operator()( const string& s )  const 
	{
		
       unsigned int h	= 0;
	   const char* pStr = s.c_str();

	   // �ó˷���Ϊhashset������������prime_list�е�һ��Ԫ��ֵ(53)
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

	// �����ֵ��ļ�(wordlist.txt)���ݵ���ϣ����
    Dictionary( string strFilename ) : HashSet<string, hash_function, equality>()
	{
		// ���ֵ��ļ�
		ifstream inf( strFilename.c_str() );
		if( !inf ) 
		{
			cerr << "Could not open dictionary:" << strFilename << "\n";
			return;
		}

		while( inf ) 
		{
			// �������ļ����ж�ȡһ��
			string line;
			getline(inf, line);

			// �����ֵ��ļ��ж�ȡ��ÿһ�в����ϣ����(����HashSet��)
			insert( line );

			// ��������ֵ�Ĺ���
//			cout << line << endl;
		}
	}

};

#endif
