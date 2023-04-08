#pragma once
namespace Menu
{
	void Draw()
	{
		if (g_config::bMenuVisible)
		{
			ImGui::SetNextWindowSize(ImVec2(250, 300), ImGuiCond_Once);
			ImGui::Begin(CN("һ����ũ�� BFCheat"));

			/*ImGui::Columns(3);
			ImGui::SetColumnWidth(0, 100);
			ImGui::SetColumnWidth(1, 100);*/

			if (ImGui::BeginTabBar("MyTabBar")) {
				if (ImGui::BeginTabItem(CN("- ���� -"))) {
					if (auto currency = Feature::GetLocalCurrency())
					{
						ImGui::Columns(2);
						ImGui::Text(CN("���: %d"), currency->Gold); 
						ImGui::Text(CN("��ʯ: %d"), currency->Diamond); 
						ImGui::NextColumn();
						ImGui::Text(CN("����: %d"), currency->Badge);
						ImGui::Text(CN("Ʊ��: %d"), currency->Coupon);
						ImGui::Columns(1); // �ָ�Ϊһ��
					}
					else {
						ImGui::Columns(2);
						ImGui::Text(CN("���: ??"));
						ImGui::Text(CN("��ʯ: ??"));
						ImGui::NextColumn();
						ImGui::Text(CN("����: ??"));
						ImGui::Text(CN("Ʊ��: ??"));
						ImGui::Columns(1); // �ָ�Ϊһ��
					}

					// ��Ӽ��
					ImGui::Spacing();

					if (ImGui::Button(CN("���ӽ�� 10k"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Gold = currency->Gold + 10000;
						}
					}

					ImGui::SameLine();

					if (ImGui::Button(CN("���ٽ�� 10k"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Gold = currency->Gold - 10000;
						}
					}

					if (ImGui::Button(CN("������ʯ 1k")))
					{
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Diamond = currency->Diamond + 1000;
						}
					}

					ImGui::SameLine();

					if (ImGui::Button(CN("������ʯ 1k"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Diamond = currency->Diamond - 1000;
						}
					}

					if (ImGui::Button(CN("���ӻ��� 10")))
					{
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Badge = currency->Badge + 10;
						}
					}

					ImGui::SameLine();

					if (ImGui::Button(CN("���ٻ��� 10"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Badge = currency->Badge - 10;
						}
					}

					if (ImGui::Button(CN("����Ʊ�� 10")))
					{
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Coupon = currency->Coupon + 10;
						}
					}

					ImGui::SameLine();

					if (ImGui::Button(CN("����Ʊ�� 10"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Coupon = currency->Coupon - 10;
						}
					}

					if (ImGui::Checkbox(CN("�������"), &g_config::bLockGold))
					{
						if (auto currency = Feature::GetLocalCurrency()) {
							g_config::iLockGold = currency->Gold;
						}
						else {
							g_config::bLockGold = false;
						}
					}
					if (ImGui::IsItemHovered(3)) ImGui::SetTooltip(CN("������Ľ�Ҳ���"));

					static char gold_amount[16] = "0"; // ����һ���ַ������洢�û�����Ľ������

					ImGui::InputText("##gold", gold_amount, sizeof(gold_amount), ImGuiInputTextFlags_CharsDecimal);

					ImGui::SameLine();
					if (ImGui::Button(CN("�޸Ľ��"))) {
						if (auto currency = Feature::GetLocalCurrency()) {
							currency->Gold = atoi(gold_amount) * 1000;
						}
					}
					if (ImGui::IsItemHovered(3)) ImGui::SetTooltip(CN("��λ��K"));
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem(CN("- ��Դ -"))) {
					if (auto resource = Feature::GetLocalResource())
					{
						ImGui::Columns(3);
						ImGui::Text(CN("�߲�: %d"), resource->Vegetable);
						ImGui::Text(CN("ˮ��: %d"), resource->Fruit);
						ImGui::Text(CN("����: %d"), resource->Cereal);
						ImGui::NextColumn();
						ImGui::Text(CN("����: %d"), resource->Grape);
						ImGui::Text(CN("Ģ��: %d"), resource->Mushroom);
						ImGui::Text(CN("���: %d"), resource->Nut);
						ImGui::NextColumn();
						ImGui::Text(CN("ţ��: %d"), resource->Milk);
						ImGui::Text(CN("����: %d"), resource->Egg);
						ImGui::Text(CN("���: %d"), resource->Fish);
						ImGui::NextColumn();
						ImGui::Text(CN("����: %d"), resource->Cloth);
						ImGui::Text(CN("�ʻ�: %d"), resource->Flower);
						ImGui::Text(CN("����: %d"), resource->Spice);
						ImGui::NextColumn();
						ImGui::Text(CN("����: %d"), resource->Honey);
						ImGui::Text(CN("����: %d"), resource->Jam);
						ImGui::Text(CN("����: %d"), resource->Cheese);
						ImGui::Columns(1); // �ָ�Ϊһ��

					}
					else {
						ImGui::Columns(3);
						ImGui::Text(CN("�߲�: ??"));
						ImGui::Text(CN("ˮ��: ??"));
						ImGui::Text(CN("����: ??"));
						ImGui::Text(CN("����: ??"));
						ImGui::Text(CN("Ģ��: ??"));
						ImGui::Text(CN("���: ??"));
						ImGui::Text(CN("ţ��: ??"));
						ImGui::Text(CN("����: ??"));
						ImGui::Text(CN("���: ??"));
						ImGui::Text(CN("����: ??"));
						ImGui::Text(CN("�ʻ�: ??"));
						ImGui::Text(CN("����: ??"));
						ImGui::Text(CN("����: ??"));
						ImGui::Text(CN("����: ??"));
						ImGui::Text(CN("����: ??"));
						ImGui::Columns(1); // �ָ�Ϊһ��
					}
					ImGui::EndTabItem();
				}
			}


			ImGui::End();
		}
	}
}
