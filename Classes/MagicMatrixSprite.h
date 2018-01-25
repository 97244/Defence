#pragma once
#include "DefenderGameLayer.h"
//此类是魔法矩阵
class MagicMatrixSprite :public Node {
public:
	MagicMatrixSprite();
	~MagicMatrixSprite();
	CC_SYNTHESIZE(float, hurt, Hurt);// 伤害值
	CC_SYNTHESIZE(bool, avail, Avail);//是否可用  
	CC_PROPERTY(bool, activation, Activation);// 是否激活魔法阵
											  // 注意一点图片必须放在缓存里面
	static MagicMatrixSprite* createWithPic(char* pMagicPic, char* pMagicPicBg); // 第一个参数CD 的比较暗淡的图片 第二个是比亮的图片  
	CC_SYNTHESIZE(float, mana, Mana);// 消耗魔法值
	void runMagicCDAnimation();// 执行魔法CD 动画
	CC_SYNTHESIZE(char*, speciaPicName, SpeciaPicName);// 图片的名字
	CC_SYNTHESIZE(char*, speciaFileName, SpeciaFileName);// plist 文件的名字
	CC_SYNTHESIZE(char*, speciaName, SpeciaName);//特效的通用名字
	CC_SYNTHESIZE(int, speciaCount, SpeciaCount);//特效的图片的张数
	CC_SYNTHESIZE(Point, anchorPo, AnchorPo);// 当前魔法特效的相对位置
	CC_SYNTHESIZE(Rect, hurtRect, HurtRect);//收到的魔法攻击范围
	void runSpecial(DefenderGameLayer* layer,Point point);//执行播放当前技能特效的动画
	void initialization();// 重新初始当前的魔法阵
private:
	bool setUpdateView(char* pMagicPic, char* pMagicPicBg);
	ProgressTimer *ptss;// 魔法阵的CD 动画
	void runMagicCDAnimationCallBack(Node* pSed);
	void runSpecialCallBack(Node* pSend);
	void detectMagic(float ti);// 检测当前魔法是否够用

};