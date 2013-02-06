#include "libjson.h"
#include "cocos2d.h"
USING_NS_CC;
#include <fstream>
using namespace std;

class JSONParser : public CCLayer
{
public:
	virtual void onEnter();
	virtual void onExit();
	static CCScene* scene();
	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(JSONParser);

public:
	JSONParser();
	~JSONParser();
	void Parse(JSONNODE *n);
	void PageParse(JSONNODE *n_page);

protected:
	void soundarrayParse(JSONNODE* n_soundarray);
	void soundParse(JSONNODE *n_sound);

	void animationarrayParse(JSONNODE* n_animationarray);
	void animationParse(JSONNODE *n_animation);

	void animatearrayParse(JSONNODE* n_animatearray);
	void animateParse(JSONNODE *n_animate);

	void encodefilename(json_char* des, json_char* sou);
	int sizeoffile(wifstream& jsonfile);
	void wcsTostr(char* chr, json_char* wchr);
	void strTowcs(json_char* wchr, char* chr);

private:
	wofstream output;
	json_char *pJSON;
	JSONNODE *file_n;
	CCSprite* pImg;
	int pageindex;
	int soundindex;
	int animationindex;
	int animateindex;
};