#include <NoesisGUI.h>
#include <vector>
class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest();
	~MyNsTest();
	std::vector<std::string> gridTopData_;
	void reloadView();
	
	NS_IMPLEMENT_INLINE_REFLECTION(MyNsTest, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyNsTest");
	}
};