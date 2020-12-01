// ============================================================================
// ������main
// ˵��������ģ����ѯ���Ƽ���ȷ����
// ��ע��
// ��д���쾰��(jingzhou_xu@163.com)
// ��֯��δ��������(Future Studio)
// ���ڣ�2005.12.1
// =============================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>

#include "dictionary.h"

using namespace std;

void lower( string& s );
string strip_punct( const string& s );
void check_spelling( ifstream& in, Dictionary& dict );


int main( int argc, char* argv[] ) 
{

	// ��������в������ԣ���ʾ������Ϣ
	if (argc != 3) 
	{
		cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
		return EXIT_FAILURE;
	}

	ifstream inf(argv[2]);
	if (! inf) 
	{
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}

	// ��ʼ�����ֵ䵽��ϣ����
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);

	check_spelling(inf, d);

	inf.close();

	// ����ʱ����ͣ����
	system("pause");

	return EXIT_SUCCESS;
}

// ������ȫ����ĸ�������������ֵ��в����Ƿ���ȷ����ȷ�����������
// ������������ֱ��ȫ��������Ϊֹ
void AllLetter_Swap( int nPos, const string& word, Dictionary& dict )
{
	// ֱ���������һ����ĸ�������ݹ�
	if( nPos == word.length() )
		return;

	string strWord;
	char chLetter = word[nPos];
	for( int j = nPos+1; j < word.length(); ++j )
	{
		// �ָ�ԭʼ����ֵ
		strWord			= word;

		// ����ָ��nPosλ���������ĸ
		strWord[nPos]	= strWord[j];
		strWord[j]		= chLetter;

		// �ֵ��в��ң��ҵ����
		if( dict.search( strWord ) )
			cout << "\t\t" << strWord << endl;
	}

	// �ݹ����
	AllLetter_Swap( nPos+1, word, dict);
}

// ��������������ĸ���������ֵ��в����Ƿ���ȷ����ȷ�����������
// ������������ֱ���������ĸ������Ϊֹ
void AdjacentLetter_Swap( const string& word, Dictionary& dict )
{
	string strWord;
	for( int nPos = 0; nPos < word.length()-1; ++nPos )
	{
		// �ָ�ԭʼ����ֵ
		strWord	= word;

		// ��������ĸ����(��ǰ��ĸ�����ں���һ����ĸ����)
		char chLetter	= word[nPos];
		strWord[nPos]	= strWord[nPos+1];
		strWord[nPos+1]	= chLetter;

		// �ֵ��в��ң��ҵ����
		if( dict.search( strWord ) )
			cout << "\t\t" << strWord << endl;
	}
}

// ���ɾ��������ÿ����ĸ�����ֵ��в����Ƿ���ȷ����ȷ�����
void RemoveLetter( const string& word, Dictionary& dict )
{
	vector<string> vecWord;		// ���ɾ��������ĸ����ȷ���ʵ�����,���ڱ������ظ�����ȷ�������
	string strWord;
	for( int nPos = 0; nPos < word.length(); ++nPos )
	{
		// �ָ�ԭʼ����ֵ
		strWord	= word;

		// ɾ��һ����ĸ
		strWord.erase( nPos, 1 );

		// �ֵ��в��ң��ҵ����
		if( dict.search( strWord ) )
		{
			// ��ǰһ����ȷ���ʵ������в��ң�������ڵĻ������������ѹ�뵽����
			vector<string>::iterator Iter = vecWord.begin();
			for( ; Iter != vecWord.end(); ++Iter )
			{
				if( (*Iter) == strWord )
					break;
			}

			// ���򲻴��ڣ���ѹ�����ȷ���ʵ����鲢���
			if( Iter == vecWord.end() )
			{
				vecWord.push_back( strWord );
				cout << "\t\t" << strWord << endl;
			}
		}
	}
}

// ����滻������ÿ����ĸΪ����һ����ĸ�����ֵ��в����Ƿ���ȷ����ȷ�����
void ReplaceLetter( const string& word, Dictionary& dict )
{
	string strWord;
	string strAlpha = "abcdefghigklmnopqrstuvwxyz";		// 26��Сд��ĸ
	for( int nPos = 0; nPos < word.length(); ++nPos )
	{
		// ��������ν�ÿλ��ĸ��26����ĸ���棬�ж��Ƿ���ȷ����
		for( int nAlpha = 0; nAlpha < strAlpha.length(); ++nAlpha )
		{
			// �ָ�ԭʼ����ֵ
			strWord	= word;
			
			// ������strWord��nPosλ�ÿ�ʼ��1����ĸ������ĸ��
			// strAlpha�е�nAlphaλ�ÿ�ʼ��1����ĸ����
			strWord.replace( nPos, 1, strAlpha, nAlpha, 1 );

			// �ֵ��в��ң��ҵ����
			if( dict.search( strWord ) )
				cout << "\t\t" << strWord << endl;
		}
	
	}
}

// ����ڵ���������λ�ã���������һ����ĸ�����ֵ��в����Ƿ���ȷ����ȷ�����
void InsertLetter( const string& word, Dictionary& dict )
{
	vector<string> vecWord;								// ��Ų��뵥����ĸ����ȷ���ʵ�����,���ڱ������ظ�����ȷ�������
	string strWord;
	string strAlpha = "abcdefghigklmnopqrstuvwxyz";		// 26��Сд��ĸ
	for( int nPos = 0; nPos < word.length(); ++nPos )
	{
		// �����������ÿ��λ���в���26����ĸ��һ�����ж��Ƿ���ȷ����
		for( int nAlpha = 0; nAlpha < strAlpha.length(); ++nAlpha )
		{
			// �ָ�ԭʼ����ֵ
			strWord	= word;
			
			// �ӵ���strWord��nPosλ�ÿ�ʼ��������ĸ��
			// strAlpha�е�nAlphaλ�ÿ�ʼ��1����ĸ
			strWord.insert( nPos, strAlpha, nAlpha, 1 );

			// �ֵ��в��ң��ҵ����
			if( dict.search( strWord ) )
			{
				// ��ǰһ����ȷ���ʵ������в��ң�������ڵĻ������������ѹ�뵽����
				vector<string>::iterator Iter = vecWord.begin();
				for( ; Iter != vecWord.end(); ++Iter )
				{
					if( (*Iter) == strWord )
						break;
				}
					
				// ���򲻴��ڣ���ѹ�����ȷ���ʵ����鲢���
				if( Iter == vecWord.end() )
				{
					vecWord.push_back( strWord );
					cout << "\t\t" << strWord << endl;
				}
			}
		}
	
	}
}

// �������ϣ�����ֵ���գ�����ƴд���
void check_spelling( ifstream& in, Dictionary& dict ) 
{

	int line_number = 0;

	while (in) 
	{

		line_number++;

		// �Ӳ����ļ��ж���һ��
		string line;
		getline(in, line);

		// �������з���stringstream��
  	    stringstream ss (stringstream::in | stringstream::out);
		ss << line;

		// ����stringstream��һ���ַ�����ÿһ�����Զ���ȡ������word��
		string word;
		while (ss >> word) 
		{
			// ����ȡ������ת��Сд����ȥ�����ܴ��ڵ�β�����
			lower( word );
            word = strip_punct( word );

			// �ڹ�ϣ�ֵ��������������Ƿ���ڣ����ڱ�ʾ�õ�����ȷ��
			// ֱ�ӽ�������ѭ������ȡ��һ�������ظ����ϲ���
			if( dict.search( word ) )
				continue;

			// �������ֵ���û�ҵ�����ʾ�õ����Ǵ���ģ�������Ƽ����������ȷ�ĵ���
			cout << "line " << line_number << ": '" << word << "'" << endl;
			cout << "\t" << "suggestions:" << endl;

			// 1. ������ȫ����ĸ�����������ж��Ƿ���ȷ����
//			AllLetter_Swap( 0, word, dict );
			// 1. ��������������ĸ�������ж��Ƿ���ȷ����
			AdjacentLetter_Swap( word, dict );

			// 2. ɾ�������е�����ĸ���ж��Ƿ���ȷ����
			RemoveLetter( word, dict );

			// 3. ����滻������ÿ����ĸΪ������ĸ���ж��Ƿ���ȷ����
			ReplaceLetter( word, dict );

			// 4. ����ڵ���������λ�ã���������һ����ĸ���ж��Ƿ���ȷ����
			InsertLetter( word, dict );
		}

	}

}

// �������ַ���ת��ΪСд�ַ���
void lower( string& s ) 
{
	for (int i = 0; i < s.length(); i++) 
	{
		s[i] = tolower(s[i]);
	}
}

// ɾ�������ַ���β�����ܴ��ڵı�����
string strip_punct( const string& s ) 
{

	if ( ispunct(s[s.length() - 1]) ) 
	{
		return s.substr (0, s.length() - 1);
	}
	else 
	{
		return s;
	}
}
