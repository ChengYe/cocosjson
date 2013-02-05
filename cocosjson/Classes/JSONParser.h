#include "libjson.h"
#include "cocos2d.h"
USING_NS_CC;
#include <fstream>
using namespace std;

class JSONParser : public CCLayer
{
public:
	virtual void onEnter();
	static CCScene* scene();
	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(JSONParser);

public:
	JSONParser();
	~JSONParser();
	void Parse(JSONNODE *n);
	void PageParse(JSONNODE *n_page);

protected:
	void soundParse(JSONNODE *n_sound);
	void animationParse(JSONNODE *n_animation);
	void animateParse(JSONNODE *n_animate);
	void encodefilename(json_char* des, json_char* sou);
	int sizeoffile(wifstream& jsonfile);

private:
	wofstream output;
	json_char *pJSON;
	JSONNODE *file_n;
	int pageindex;
	int soundindex;
	int animationindex;
	int animateindex;
};