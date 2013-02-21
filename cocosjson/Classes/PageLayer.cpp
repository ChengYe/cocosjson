#include "PageLayer.h"
#include "libjson.h"
#include <iostream>
using namespace std;

#define FILENAME 64

PageLayer::PageLayer(JSONNODE *n)
{
	PageParse(n);
}

PageLayer::~PageLayer()
{
	pImg->autorelease();
}

void PageLayer::Parse(JSONNODE *n)
{
	if (n == NULL){
		wcout<<L"Invalid JSON Node from parse"<<endl;
		return;
	}

	pageindex = 0;
	JSONNODE_ITERATOR i = json_begin(n);
	while (i != json_end(n)){
		if (*i == NULL){
			wcout<<L"Invalid JSON Node from parse"<<endl;
			return;
		}

		if (json_type(*i) == JSON_NODE){
			pageindex++;
			PageParse(*i);
		}
		++i;
	}
}

json_number PageLayer::GetCurPageLen()
{
	return pagelen;
}

void PageLayer::PageParse(JSONNODE *n_page)
{
	if (n_page == NULL){
		wcout<<L"Invalid JSON Node from pageparse"<<endl;
		return;
	}

	JSONNODE_ITERATOR i_page = json_begin(n_page);
	while (i_page != json_end(n_page)){
		if (*i_page == NULL){
			wcout<<L"Invalid JSON Node from pageparse"<<endl;
			return;
		}

		json_char *node_name = json_name(*i_page);
		if (wcscmp(node_name, L"sound") == 0){
			wcout<<L"page["<<pageindex<<L"]------"<<L"sound node found"<<endl;
			soundindex = 0;
			soundarrayParse(*i_page);
		}
		else if (wcscmp(node_name, L"animation") == 0){
			wcout<<L"page["<<pageindex<<L"]------"<<L"animation node found"<<endl;
			animationindex = 0;
			animationarrayParse(*i_page);
		}
		else if (wcscmp(node_name, L"length") == 0){
			pagelen = json_as_float(*i_page);
			wcout<<L"page["<<pageindex<<L"]------"<<L"length node found"<<endl;
		}
		else if (wcscmp(node_name, L"bgcolor") == 0){
			wcout<<L"page["<<pageindex<<L"]------"<<L"bgcolor node found"<<endl;
		}

		// cleanup and increment the iterator
		json_free(node_name);
		++i_page;
	}
}

//------------
//sound
//------------
void PageLayer::soundarrayParse(JSONNODE *n_soundarray)
{
	if (n_soundarray == NULL){
		wcout<<L"Invalid JSON Node from soundarrayparse"<<endl;
		return;
	}

	JSONNODE_ITERATOR i_soundarray = json_begin(n_soundarray);
	while (i_soundarray != json_end(n_soundarray)){
		if (*i_soundarray == NULL){
			wcout<<L"Invalid JSON Node from soundarrayparse"<<endl;
			return;
		}

		if (json_type(*i_soundarray) == JSON_NODE){
			soundindex++;
			soundParse(*i_soundarray);
		}
		++i_soundarray;
	}
}

void PageLayer::soundParse(JSONNODE *n_sound)
{
	if (n_sound == NULL){
		wcout<<L"Invalid JSON Node from soundparse"<<endl;
		return;
	}

	JSONNODE_ITERATOR i_sound = json_begin(n_sound);
	while (i_sound != json_end(n_sound)){
		if (*i_sound == NULL){
			wcout<<L"Invalid JSON Node from soundparse"<<endl;
			return;
		}

		json_char *node_name = json_name(*i_sound);
		if (wcscmp(node_name, L"length") == 0)
			//output<<L"["<<soundindex<<L"] "<<L"length: "<<json_as_float(*i_sound)<<endl;
			;
		else if (wcscmp(node_name, L"isoff") == 0)
			//output<<L"["<<soundindex<<L"] "<<L"isoff: "<<json_as_bool(*i_sound)<<endl;
			;
		//wchar_t to char conversion later
		else if (wcscmp(node_name, L"title") == 0)
			//output<<L"["<<soundindex<<L"] "<<L"title: "<<json_as_string(*i_sound)<<endl;
			;
		else if (wcscmp(node_name, L"type") == 0)
			//output<<L"["<<soundindex<<L"] "<<L"type: "<<json_as_string(*i_sound)<<endl;
			;
		else if (wcscmp(node_name, L"filename") == 0)
			//output<<L"["<<soundindex<<L"] "<<L"filename: "<<json_as_string(*i_sound)<<endl;
			;
		else if (wcscmp(node_name, L"start") == 0)
			//output<<L"["<<soundindex<<L"] "<<L"start: "<<json_as_float(*i_sound)<<endl;
			;
		else if (wcscmp(node_name, L"loop") == 0)
			//output<<L"["<<soundindex<<L"] "<<L"loop: "<<json_as_bool(*i_sound)<<endl;
			;
		else if (wcscmp(node_name, L"soundLength") == 0)
			//output<<L"["<<soundindex<<L"] "<<L"soundLength: "<<json_as_float(*i_sound)<<endl;
			;
		json_free(node_name);

		++i_sound;
	}
}

//------------
//animation
//------------
void PageLayer::animationarrayParse(JSONNODE *n_animationarray)
{
	if (n_animationarray == NULL){
		wcout<<L"Invalid JSON Node from animationarrayparse"<<endl;
		return;
	}

	JSONNODE_ITERATOR i_animationarray = json_begin(n_animationarray);
	while (i_animationarray != json_end(n_animationarray)){
		if (*i_animationarray == NULL){
			wcout<<L"Invalid JSON Node from animationarrayparse"<<endl;
			return;
		}

		json_char *node_name = json_name(*i_animationarray);
		if (json_type(*i_animationarray) == JSON_NODE){
			animationindex++;
			animationParse(*i_animationarray);
		}
		++i_animationarray;
	}
}

void PageLayer::animationParse(JSONNODE *n_animation)
{
	if (n_animation == NULL){
		wcout<<L"Invalid JSON Node from animationparse"<<endl;
		return;
	}

	JSONNODE_ITERATOR i_animation = json_begin(n_animation);
	//CCSprite* pImg;
	json_char imgfile[FILENAME];
	encodefilename(imgfile, json_as_string(*(i_animation+8)));
	char img[FILENAME];
	wcsTostr(img, imgfile);
	pImg = CCSprite::create(img);
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	//pImg->setPosition(ccp(size.width / 2, size.height / 2));
	pImg->setPosition(ccp(json_as_float(*i_animation), json_as_float(*(i_animation+3))));
	pImg->setScaleX(json_as_float(*(i_animation+10)));
	pImg->setScaleY(json_as_float(*(i_animation+11)));
	pImg->_setZOrder(json_as_int(*(i_animation+14)));
	this->addChild(pImg);
	//pImg->release();
	if (json_type(*(i_animation+9)) == JSON_ARRAY)
		animatearrayParse(*(i_animation+9));

	//------------
	//for parsing only
	//------------

	//while (i_animation != json_end(n_animation)){
	//	if (*i_animation == NULL){
	//		wcout<<L"Invalid JSON Node from animationparse"<<endl;
	//		return;
	//	}
	//	
	//	json_char *node_name = json_name(*i_animation);
	//	if (wcscmp(node_name, L"x") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"x: "<<json_as_float(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"length") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"length: "<<json_as_float(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"a") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"a: "<<json_as_float(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"y") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"y: "<<json_as_float(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"type") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"type: "<<json_as_string(*i_animation)<<endl;
	//	//wchar_t to char conversion later
	//	else if (wcscmp(node_name, L"name") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"name: "<<json_as_string(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"start") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"start: "<<json_as_float(*i_animation)<<endl;
	//	//------------
	//	//spelling error "resouce--->resource"
	//	//------------
	//	else if (wcscmp(node_name, L"resouce_type") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"resource_type: "<<json_as_string(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"pic") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"pic: "<<json_as_string(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"scalex") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"scalex: "<<json_as_float(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"scaley") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"scaley: "<<json_as_float(*i_animation)<<endl;
	//	//------------
	//	//modification later
	//	else if (wcscmp(node_name, L"shock") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"shock: "<<json_as_string(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"event") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"event: "<<json_as_string(*i_animation)<<endl;
	//	//------------
	//	else if (wcscmp(node_name, L"zindex") == 0)
	//		output<<L"["<<animationindex<<L"] "<<L"zindex: "<<json_as_int(*i_animation)<<endl;
	//	else if (wcscmp(node_name, L"animate") == 0){
	//		output<<L"animate: "<<endl;
	//		animateindex = 0;
	//		if (json_type(*i_animation) == JSON_ARRAY)
	//			animatearrayParse(*i_animation);
	//		output<<L"\\animate: "<<endl;
	//	}
	//	json_free(node_name);

	//	++i_animation;
	//}
}

//------------
//animate
//------------
void PageLayer::animatearrayParse(JSONNODE *n_animatearray)
{
	if (n_animatearray == NULL){
		wcout<<L"Invalid JSON Node from animatearrayparse"<<endl;
		return;
	}

	JSONNODE_ITERATOR i_animatearray = json_begin(n_animatearray);
	while (i_animatearray != json_end(n_animatearray)){
		if (*i_animatearray == NULL){
			wcout<<L"Invalid JSON Node from animatearrayparse"<<endl;
			return;
		}

		if (json_type(*i_animatearray) == JSON_NODE){
			animateindex++;
			animateParse(*i_animatearray);
		}
		++i_animatearray;
	}
}

void PageLayer::animateParse(JSONNODE *n_animate)
{
	if (n_animate == NULL){
		wcout<<L"Invalid JSON Node from animateparse"<<endl;
		return;
	}

	JSONNODE_ITERATOR i_animate = json_begin(n_animate);
	CCActionInterval* moveaction = CCMoveBy::create(json_as_float(*(i_animate+6)), CCPointMake(json_as_float(*(i_animate)), json_as_float(*(i_animate+2))));
	pImg->runAction(moveaction);
	CCActionInterval* scaleaction = CCScaleBy::create(json_as_float(*(i_animate+6)), json_as_float(*(i_animate+4)), json_as_float(*(i_animate+5)));
	pImg->runAction(scaleaction);

	//------------
	//for parsing only
	//------------

	//while (i_animate != json_end(n_animate)){
	//	if (*i_animate == NULL){
	//		wcout<<L"Invalid JSON Node from animateparse"<<endl;
	//		return;
	//	}

	//	json_char *node_name = json_name(*i_animate);
	//	if (wcscmp(node_name, L"x") == 0)
	//		output<<L"["<<animateindex<<L"] "<<L"x: "<<json_as_float(*i_animate)<<endl;
	//	else if (wcscmp(node_name, L"a") == 0)
	//		output<<L"["<<animateindex<<L"] "<<L"a: "<<json_as_float(*i_animate)<<endl;
	//	else if (wcscmp(node_name, L"y") == 0)
	//		output<<L"["<<animateindex<<L"] "<<L"y: "<<json_as_float(*i_animate)<<endl;
	//	else if (wcscmp(node_name, L"hd") == 0)
	//		output<<L"["<<animateindex<<L"] "<<L"hd: "<<json_as_float(*i_animate)<<endl;
	//	else if (wcscmp(node_name, L"scalex") == 0)
	//		output<<L"["<<animateindex<<L"] "<<L"scalex: "<<json_as_float(*i_animate)<<endl;
	//	else if (wcscmp(node_name, L"scaley") == 0)
	//		output<<L"["<<animateindex<<L"] "<<L"scaley: "<<json_as_float(*i_animate)<<endl;
	//	else if (wcscmp(node_name, L"len") == 0)
	//		output<<L"["<<animateindex<<L"] "<<L"len: "<<json_as_float(*i_animate)<<endl;
	//	else if (wcscmp(node_name, L"spEftid") == 0)
	//		output<<L"["<<animateindex<<L"] "<<L"spEftid: "<<json_as_bool(*i_animate)<<endl;
	//	else if (wcscmp(node_name, L"id") == 0)
	//		output<<L"["<<animateindex<<L"] "<<L"id: "<<json_as_int(*i_animate)<<endl;
	//	json_free(node_name);

	//	++i_animate;
	//}
}

void PageLayer::encodefilename(json_char* des, json_char* sou)
{
	json_char* dotpos = wcschr(sou, L'.');
	wcsncpy(des, sou,dotpos - sou);
	des[dotpos - sou] = '\0';
	wcscat(des, ++dotpos);
}

void PageLayer::wcsTostr(char* chr, json_char* wchr)
{
	size_t converted;
	wcstombs_s(&converted, chr, FILENAME, wchr, _TRUNCATE);
}

void PageLayer::strTowcs(json_char* wchr, char* chr)
{
	size_t converted;
	mbstowcs_s(&converted, wchr, FILENAME, chr, _TRUNCATE);
}