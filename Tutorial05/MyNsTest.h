#include <NoesisGUI.h>
#include <stdio.h>
#include <vector>

class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest();
	~MyNsTest();
	//Noesis::StackPanel* diffusePanel_;
	//void MyNsTest::initCollectionView();
	
	void MyNsTest::MouseUpEvent(Noesis::BaseComponent* sender, const Noesis::Gui::MouseButtonEventArgs& e);
	void MyNsTest::myMouseButtonMove(Noesis::BaseComponent* sender, const  Noesis::Gui::MouseEventArgs& e);
	void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e);
	Noesis::Drawing::Thickness MyNsTest::getMovesMargin(Noesis::Point curPoint);
    Noesis::Gui::Button *button1_;
	NS_IMPLEMENT_INLINE_REFLECTION(MyNsTest, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyNsTest");
	}
};
class Player : public Noesis::BaseComponent
{
public:
	Player() {}
	Player(NsString name) : _name(name), _imageName("shenjian.png"){
		Noesis::Ptr<Noesis::BitmapImage> image = *new Noesis::BitmapImage("shenjian.png");
		auto x = image->GetDpiX();
		auto y = image->GetDpiY();
		auto width = image->GetWidth();
		auto height = image->GetHeight();
		FILE *f;
		fopen_s(&f, "resource\\shenjian.png", "rb");
		auto buffer_size = fseek(f, 0, SEEK_END);
		rewind(f);
		NsByte * buffer = static_cast<NsByte *>(malloc(sizeof(unsigned char)*buffer_size));
		fread(buffer, 1, buffer_size, f);
		Noesis::Ptr<Noesis::BitmapSource> source = Noesis::BitmapSource::Create(width, height, x, y, buffer, buffer_size, width / 8);
		// @BUG: buffer is not BGRA32 formatted. to be solved
		_brush = *new Noesis::ImageBrush(image.GetPtr());
	}

private:
	NsString _name;
	NsString _imageName;
	//Noesis::Ptr<Noesis::BitmapImage> _image;
	//BitmapImage _image;
	Noesis::Ptr<Noesis::ImageBrush> _brush;

	NS_IMPLEMENT_INLINE_REFLECTION(Player, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("Player");
		NsProp("Name1", &Player::_name);
		NsProp("Name2", &Player::_name);
		NsProp("ImageName", &Player::_imageName);
		NsProp("Brush", &Player::_brush);
	}

};

class DataModel3 : public Noesis::BaseComponent
{
public:
	DataModel3()
	{
		_players = *new Noesis::ObservableCollection<Player>;
		std::vector<NsString> nameVector{"Player1","Player2","Player3","Player4","Player5","Player6","Player7","Player8","Player9","Player10","Player11","Player12","Player13","Player14", "Player15"};
		//std::vector<NsString> btnNameVector{ "btnName1","btnName2","btnName3","btnName4","btnName5","btnName6","btnName7","btnName8","btnName9","btnName10","btnName11","btnName12","btnName13","btnName14", "btnName15" };
		//std::vector<NsString> imageName{"shenjian.png","dianchui.png"};
		for (NsInt i = 0; i < nameVector.size(); i++) {
			//NsString imgName = "";
			/*if (i % 2 == 0) {
				imgName = imageName[0];
			} 
			else {
				imgName = imageName[1];
			}*/
			Noesis::Ptr<Player> player = *new Player(nameVector[i]);
			_players->Add(player.GetPtr());
		}
	}

private:
	Noesis::Ptr< Noesis::ObservableCollection<Player> > _players;

	NS_IMPLEMENT_INLINE_REFLECTION(DataModel3, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("DataModel3");
		NsProp("Players", &DataModel3::_players);
	}
};