#include "pch.h" 
#include "CppUnitTest.h" 
#include "C:\Users\Даниил Михайлович\source\repos\AISD_CW_sem4\AISD_CW_sem4\AISD_CW_sem4.cpp" 
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

ifstream file_1(R"(C:\Users\Даниил Михайлович\source\repos\AISD_CW_sem4\AISD_CW_sem4\data.txt)");
gleipnir<char> v;

string s_1 = read(file_1);

namespace tests
{
	TEST_CLASS(tests)
	{
	public:
		TEST_METHOD(size)
		{
			fill_vertexes_list(v, s_1);
			Assert::IsTrue(v.size() == 6);
		}
		TEST_METHOD(find_vertex)
		{
			char sym = 'P';
			fill_vertexes_list(v, s_1);
			Assert::IsTrue(v.find(sym));
		}
		TEST_METHOD(max_flow)
		{
			int** matrix = get_capacity_matrix(s_1, v);
			fill_vertexes_list(v, s_1);
			Assert::IsTrue(5 == edmonds_karp_alg(matrix, 'S', 'T', v));
		}
	};
}
