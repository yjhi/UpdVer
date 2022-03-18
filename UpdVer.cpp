// UpdVer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include <string>
#include<list>
using namespace std;

std::string strLine = "";

void DoWork(std::string file, string ver)
{
	FILE *f = NULL;

	fopen_s(&f, file.c_str(), "r+");

	if (f)
	{
		cout << file << "----->读取打开文件成功" << endl;
		ifstream reader(f);

		std::list<string> lines;

		while (getline(reader, strLine))
		{
			lines.push_back(strLine);
		}

		std::list<string>::iterator it = lines.begin();

		string nowVer = "";

		for (; it != lines.end(); it++)
		{
			strLine = *it;
			if (strLine.find("[assembly: AssemblyVersion(") == 0)
			{
				cout <<"版本信息:"<< *it << endl;
				nowVer = "[assembly: AssemblyVersion(\"";
				nowVer.append(ver);
				nowVer.append("\")]");
				*it = nowVer;

			}
			else if(strLine.find("[assembly: AssemblyFileVersion(") == 0)
			{
				cout << *it << endl;
				nowVer = "[assembly: AssemblyFileVersion(\"";
				nowVer.append(ver);
				nowVer.append("\")]");
				*it = nowVer;
				
			}

		}

		fclose(f);
		cout << file << "----->读取文件成功" << endl;
		f = NULL;

		fopen_s(&f, file.c_str(), "w");

		if (f)
		{
			ofstream writer(f);
			cout << file << "----->写入打开文件成功" << endl;

			it = lines.begin();

			for (; it != lines.end(); it++)
			{
				strLine = *it;
				if (strLine.find("[assembly: AssemblyVersion(") == 0)
				{	
					cout << "版本信息:" << *it << endl;
				}
				else if (strLine.find("[assembly: AssemblyFileVersion(") == 0)
				{
					cout << "版本信息:" << *it << endl;
				}
				
				writer << strLine<<endl;
			}

			cout << file << "----->写入件成功" << endl;

			fclose(f);

		}
		else {
			cout << file << "----->写入打开文件失败" << endl;
		}
	}
	else {
		cout << file << "----->读取打开文件失败" << endl;
	}
	


}
int main(int argc,char **argv)
{
		if (argc > 2)
		{
			std::cout << "[PATH]" << argv[1]<< std::endl;
			std::cout << "[VER]" << argv[2]<<std::endl;

			std::string ver = string(argv[2]);

			FILE *f=NULL;
			fopen_s(&f, argv[1], "r");

			if (f)
			{
				ifstream reader(f);

				std::list<string> lines;

				while(getline(reader, strLine))
				{
					lines.push_back(strLine);
				}

				std::list<string>::iterator it = lines.begin();
				int icount = 0;
				for (; it!=lines.end(); it++)
				{
					cout << ++icount << "..........................................................................."<< endl;
					cout << "文件:" << *it << "\n版本号:" << ver << endl;
					DoWork(*it, ver);
				}

				fclose(f);
			}

		}
		else {

			std::cout << "参数错误..." << std::endl;
		}
	
		std::cout << "输入任意字符退出." << std::endl;
		char c;
		std::cin >> c;

	    return 0;
}
