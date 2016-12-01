#include <NoesisGUI.h>
#include <vector>
class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest();
	~MyNsTest();
	Noesis::Grid *gridTop_;
	std::vector<std::string> gridTopData_;
	void reloadView();
	void OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e);
	NS_IMPLEMENT_INLINE_REFLECTION(MyNsTest, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyNsTest");
	}
};