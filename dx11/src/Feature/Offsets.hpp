#pragma once
//ָ��ƫ��
namespace Offsets
{
#define currency_Address 0x14D63A8	//���һ���ַ

#define of_currency1 0x110
#define of_currency2 0x60
#define of_currency3 0x80
#define of_currency4 0x40
#define of_currency5 0x1C8
#define of_currency6 0x88

#define resource_Address 0x14D10A0	//��Դ����ַ
#define of_resource1 0x28
#define of_resource2 0x10
#define of_resource3 0x88
#define of_resource4 0x10
#define of_resource5 0xD8
#define of_resource6 0x8

	struct Currency
	{
		char pa_0000[0x1E0];
		int  Gold; //0x1E0
		char pa_01E4[4];
		int  Diamond; //0x1E8
		char pa_01EC[4];
		int  Badge; //0x1F0
		char pa_01F4[4];
		int  Coupon; //0x1F8
	};

	struct Resource
	{
		char pa_0000[0x158];
		int Spice;		//0x158	����
		char pa_0158[36];
		int UnKnow1;	//0x180
		char pa_0180[36];
		int Mushroom;	//0x1A8	Ģ��
		char pa_01A8[36];
		int Jam;		//0x1D0 ����
		char pa_01D0[36];
		int Cheese;		//0x1F8 ����
		char pa_01F8[36];
		int Cloth;		//0x220 ����
		char pa_0220[36];
		int Honey;		//0x248 ����
		char pa_0248[36];
		int Fish;		//0x270 ��
		char pa_0270[36];
		int Egg;		//0x298 ����
		char pa_0298[36];
		int Milk;		//0x2C0 ţ��
		char pa_02C0[36];
		int Nut;		//0x2E8 ���
		char pa_02E8[36];
		int Cereal;		//0x310 ����
		char pa_0310[36];
		int Flower;		//0x338 ��
		char pa_0338[36];
		int Grape;		//0x360 ����
		char pa_0360[36];
		int Vegetable;	//0x388 �߲�
		char pa_0388[36];
		int Fruit;		//0x3B0 ˮ��
	};
}