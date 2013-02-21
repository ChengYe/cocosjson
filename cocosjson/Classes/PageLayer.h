#include "libjson.h"
#include "cocos2d.h"
USING_NS_CC;
#include <fstream>
using namespace std;

class PageLayer : public CCLayer
{
public:
	PageLayer(JSONNODE* n);
	~PageLayer();

	void Parse(JSONNODE *n);
	json_number GetCurPageLen();

protected:
	void PageParse(JSONNODE *n_page);

	void soundarrayParse(JSONNODE* n_soundarray);
	void soundParse(JSONNODE *n_sound);

	void animationarrayParse(JSONNODE* n_animationarray);
	void animationParse(JSONNODE *n_animation);

	void animatearrayParse(JSONNODE* n_animatearray);
	void animateParse(JSONNODE *n_animate);

	void encodefilename(json_char* des, json_char* sou);
	void wcsTostr(char* chr, json_char* wchr);
	void strTowcs(json_char* wchr, char* chr);

private:
	CCSprite* pImg;
	json_number pagelen;

	int pageindex;
	int soundindex;
	int animationindex;
	int animateindex;
};