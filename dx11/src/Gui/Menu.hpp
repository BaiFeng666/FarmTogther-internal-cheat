#pragma once
namespace Menu
{
	void Draw()
	{
		if (g_config::bMenuVisible)
		{
			ImGui::SetNextWindowSize(ImVec2(250, 300), ImGuiCond_Once);
			ImGui::Begin(CN("一起玩农场 BFCheat"));

			/*ImGui::Columns(3);
			ImGui::SetColumnWidth(0, 100);
			ImGui::SetColumnWidth(1, 100);*/

			if (ImGui::BeginTabBar("MyTabBar")) {
				if (ImGui::BeginTabItem(CN("- 货币 -"))) {
					if (auto currency = Feature::GetLocalCurrency())
					{
						ImGui::Columns(2);
						ImGui::Text(CN("金币: %d"), currency->Gold); 
						ImGui::Text(CN("钻石: %d"), currency->Diamond); 
						ImGui::NextColumn();
						ImGui::Text(CN("徽章: %d"), currency->Badge);
						ImGui::Text(CN("票子: %d"), currency->Coupon);
						ImGui::Columns(1); // 恢复为一列
					}
					else {
						ImGui::Columns(2);
						ImGui::Text(CN("金币: ??"));
						ImGui::Text(CN("钻石: ??"));
						ImGui::NextColumn();
						ImGui::Text(CN("徽章: ??"));
						ImGui::Text(CN("票子: ??"));
						ImGui::Columns(1); // 恢复为一列
					}

					// 添加间隔
					ImGui::Spacing();

					if (ImGui::Button(CN("增加金币 10k"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Gold = currency->Gold + 10000;
						}
					}

					ImGui::SameLine();

					if (ImGui::Button(CN("减少金币 10k"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Gold = currency->Gold - 10000;
						}
					}

					if (ImGui::Button(CN("增加钻石 1k")))
					{
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Diamond = currency->Diamond + 1000;
						}
					}

					ImGui::SameLine();

					if (ImGui::Button(CN("减少钻石 1k"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Diamond = currency->Diamond - 1000;
						}
					}

					if (ImGui::Button(CN("增加徽章 10")))
					{
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Badge = currency->Badge + 10;
						}
					}

					ImGui::SameLine();

					if (ImGui::Button(CN("减少徽章 10"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Badge = currency->Badge - 10;
						}
					}

					if (ImGui::Button(CN("增加票子 10")))
					{
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Coupon = currency->Coupon + 10;
						}
					}

					ImGui::SameLine();

					if (ImGui::Button(CN("减少票子 10"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Coupon = currency->Coupon - 10;
						}
					}

					if (ImGui::Checkbox(CN("锁定金币"), &g_config::bLockGold))
					{
						if (auto currency = Feature::GetLocalCurrency()) {
							g_config::iLockGold = currency->Gold;
						}
						else {
							g_config::bLockGold = false;
						}
					}
					if (ImGui::IsItemHovered(3)) ImGui::SetTooltip(CN("保持你的金币不变"));

					static char gold_amount[16] = "0"; // 定义一个字符串来存储用户输入的金币数量

					ImGui::InputText("##gold", gold_amount, sizeof(gold_amount), ImGuiInputTextFlags_CharsDecimal);

					ImGui::SameLine();
					if (ImGui::Button(CN("修改金币"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Gold = atoi(gold_amount) * 1000;
						}
					}
					if (ImGui::IsItemHovered(3)) ImGui::SetTooltip(CN("单位：K"));
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem(CN("- 资源 -"))) {
					if (auto resource = Feature::GetLocalResource())
					{
						ImGui::Columns(3);
						ImGui::Text(CN("蔬菜: %d"), resource->Vegetable);
						ImGui::Text(CN("水果: %d"), resource->Fruit);
						ImGui::Text(CN("谷物: %d"), resource->Cereal);
						ImGui::NextColumn();
						ImGui::Text(CN("葡萄: %d"), resource->Grape);
						ImGui::Text(CN("蘑菇: %d"), resource->Mushroom);
						ImGui::Text(CN("坚果: %d"), resource->Nut);
						ImGui::NextColumn();
						ImGui::Text(CN("牛奶: %d"), resource->Milk);
						ImGui::Text(CN("鸡蛋: %d"), resource->Egg);
						ImGui::Text(CN("鱼儿: %d"), resource->Fish);
						ImGui::NextColumn();
						ImGui::Text(CN("布料: %d"), resource->Cloth);
						ImGui::Text(CN("鲜花: %d"), resource->Flower);
						ImGui::Text(CN("香料: %d"), resource->Spice);
						ImGui::NextColumn();
						ImGui::Text(CN("蜂蜜: %d"), resource->Honey);
						ImGui::Text(CN("果酱: %d"), resource->Jam);
						ImGui::Text(CN("奶酪: %d"), resource->Cheese);
						ImGui::Columns(1); // 恢复为一列

					}
					else {
						ImGui::Columns(3);
						ImGui::Text(CN("蔬菜: ??"));
						ImGui::Text(CN("水果: ??"));
						ImGui::Text(CN("谷物: ??"));
						ImGui::Text(CN("葡萄: ??"));
						ImGui::Text(CN("蘑菇: ??"));
						ImGui::Text(CN("坚果: ??"));
						ImGui::Text(CN("牛奶: ??"));
						ImGui::Text(CN("鸡蛋: ??"));
						ImGui::Text(CN("鱼儿: ??"));
						ImGui::Text(CN("布料: ??"));
						ImGui::Text(CN("鲜花: ??"));
						ImGui::Text(CN("香料: ??"));
						ImGui::Text(CN("蜂蜜: ??"));
						ImGui::Text(CN("果酱: ??"));
						ImGui::Text(CN("奶酪: ??"));
						ImGui::Columns(1); // 恢复为一列
					}
					ImGui::EndTabItem();
				}
			}


			ImGui::End();
		}
	}
}
