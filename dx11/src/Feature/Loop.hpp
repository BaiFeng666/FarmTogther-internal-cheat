#pragma once
namespace Loop 
{

	void LockGold(int gold)
	{
		if (g_config::bLockGold)	//Ëø¶¨½ð±Ò
		{
			if(auto currency = Feature::GetLocalCurrency())
			{
				currency->Gold = g_config::iLockGold;
			}
			else
				g_config::bLockGold = false;
		}
	}

	void Update()
	{
		LockGold(g_config::iLockGold);
	}
}