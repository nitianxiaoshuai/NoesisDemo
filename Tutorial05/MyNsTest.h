#include <NoesisGUI.h>
#include<wpframework.h>
#include <stdio.h>
#include <vector>
#include<D3D11.h>
class MyNsTesta : public Noesis::Grid
{
public:
	MyNsTesta();
	~MyNsTesta();
	NS_IMPLEMENT_INLINE_REFLECTION(MyNsTesta, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyNsTesta");
	}
};
class Player : public Noesis::BaseComponent
{
public:
	Player() {}
	Player(NsString name) : _name(name) {}

private:
	NsString _name;


	NS_IMPLEMENT_INLINE_REFLECTION(Player, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("Player");
		NsProp("Name", &Player::_name);

	}

};

class ImageN : public Noesis::BaseComponent {
public:
	ImageN() {};
	ImageN( NsString imageName) : _imageName(imageName) {}
	NsString _imageName;

	NS_IMPLEMENT_INLINE_REFLECTION(ImageN, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("ImageN");
		NsProp("ImageName", &ImageN::_imageName);
	}
};

class DataModel3 : public Noesis::BaseComponent
{
public:
	DataModel3()
	{
		_players = *new Noesis::ObservableCollection<Player>;
		std::vector<NsString> nameVector{ "DDL","ssss2","DFG3","PPDLer4","PLKKJ","Pl" };

		for (NsInt i = 0; i < nameVector.size(); i++) {
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




class DataModel4 : public Noesis::BaseComponent
{
public:
	DataModel4()
	{
		_imageN = *new Noesis::ObservableCollection<ImageN>;
		std::vector<NsString> imageNameV{ "hudie.png","shenjian.png","anmie.png","dapao.png" };
		for (NsInt i = 0; i < imageNameV.size(); i++) {
			Noesis::Ptr<ImageN> img = *new ImageN(imageNameV[i]);
			_imageN->Add(img.GetPtr());
		}
		

		_images = *new Noesis::ObservableCollection<Noesis::Image>;
		std::vector<Noesis::Ptr<Noesis::BitmapImage>> imgeV{ getImages("hudie.png"),getImages("hudie.png"), getImages("hudie.png"), getImages("hudie.png")};
		
		
	}
private:
	Noesis::Ptr< Noesis::ObservableCollection<ImageN> > _imageN;
	Noesis::Ptr<Noesis::ObservableCollection<Noesis::Image> > _images;

	Noesis::Ptr<Noesis::BitmapImage> getImages(NsString str)
	{
		Noesis::Ptr<Noesis::BitmapImage> image = *new Noesis::BitmapImage("dapao.png");
		auto x = image->GetDpiX();
		auto y = image->GetDpiY();
		auto width = image->GetWidth();
		auto height = image->GetHeight();
		return image;
	};

	NS_IMPLEMENT_INLINE_REFLECTION(DataModel4, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("DataModel4");
		NsProp("ImageNN", &DataModel4::_imageN);
		NsProp("ImageS", &DataModel4::_images);
	}
};
