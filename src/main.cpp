//DxLib�̎Q�l�ɂ��Ă�������
//����URL�̓T���v���v���O�����̃y�[�W�ł�
//http://dxlib.o.oo7.jp/dxprogram.html
//����URL�̓��t�@�����X�̃y�[�W�ł�
//http://dxlib.o.oo7.jp/dxfunc.html

#include "DxLib.h"

enum Window
{
	Width = 1024,
	Height = 1024
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// �c�w���C�u��������������(�G���[���N�����璼���ɏI��)
	if (DxLib_Init() == -1)		return -1;			

	//�E����ʂɕ`�悷��
	SetDrawScreen(DX_SCREEN_BACK);

	//���C�����[�v
	//while��()�ɂ���ProcessMessage�������ƁA����ɓ����Ȃ��Ȃ�
	while (ProcessMessage() == 0) {

		//��ʂ���������
		ClearDrawScreen();



		//�I���e��ʂƃE����ʂ����ւ���
		ScreenFlip();
	}

	//�c�w���C�u�����g�p�̏I������
	DxLib_End();

	//�\�t�g�̏I�� 
	return 0;
}