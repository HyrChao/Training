//2017/05/19
//By Chao
//拾取金币类

#include "ARG.h"
#include "GoldPickup.h"

AGoldPickup::AGoldPickup()
{
	int gold = 100;//初始掉落金币
}

void AGoldPickup::OnPickedUp()
{

	Super::OnPickedUp();//执行父类PickUp函数，销毁物体
}


