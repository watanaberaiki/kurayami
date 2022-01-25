#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1B_31_���^�i�x���C�L:";

// �E�B���h�E����
const int WIN_WIDTH = 640;

// �E�B���h�E�c��
const int WIN_HEIGHT = 640;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int block = LoadGraph("block.png");

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	int map[20][20] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	enum direction {
		Down,//0
		Left,//1
		Up,//2
		Right//3
	};
	//�����؂�ւ�
	int scene = Down;

	//��
	int startX[4] = { 200 ,640,200,0};
	int startY[4] = { 0 ,300,640,300};
	int endX[4] = { 200 ,0,200,640};
	int endY[4] = { 640 ,300,0,300};
	int startXMap[4] = { };
	int startYMap[4] = {};
	int endXMap[4] = { };
	int endYMap[4] = {};
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//
		
		// �X�V����
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			if (scene==Right) {
				scene = Down;
			}
			else {
				scene += 1;
			}
		}
		for (int i = 0; i < 4; i++) {
			startXMap[i] = startX[i] / 32;
			startYMap[i] = startY[i] / 32;
			endXMap[i] = endX[i] / 32;
			endYMap[i] = endY[i] / 32;
		}
		// �`�揈��
		
		//�È�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 10);
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				if (map[y][x] == 1) {
					DrawGraph(x * 32, y * 32, block, true);
				}
			}
		}

		
		switch(scene) {

			//�ォ�牺�̌�
		case Down:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int x = -2; x < 3; x++) {
				for (int i = startYMap[Down]; i < endYMap[Down]; i++) {
					if (map[i][startXMap[Down] - x] == 1) {
						DrawGraph((startXMap[Down] - x) * 32, i * 32, block, true);
					}
				}
			}

			//���F
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawLine(startX[Down], startY[Down], endX[Down], endY[Down], GetColor(0, 128, 128), 50);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawLine(startX[Down], startY[Down], endX[Down], endY[Down], GetColor(0, 128, 128), 35);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawLine(startX[Down], startY[Down], endX[Down], endY[Down], GetColor(255, 255, 255), 10);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "%d", startXMap[Down]);
			DrawFormatString(30, 650, GetColor(255, 255, 255), "%d", startYMap[Down]);
			DrawFormatString(50, 650, GetColor(255, 255, 255), "%d", endXMap[Down]);
			DrawFormatString(70, 650, GetColor(255, 255, 255), "%d", endYMap[Down]);
			break;
			
			//�E���獶�̌�
		case Left:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int y = -2; y < 3; y++) {
				for (int i = startXMap[Left]; i >= endXMap[Left]; i--) {
					if (map[startYMap[Left]-y][i] == 1) {
						DrawGraph( i * 32,(startYMap[Left] - y) * 32, block, true);
					}
				}
			}

			//���F
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawLine(startX[Left], startY[Left], endX[Left], endY[Left], GetColor(0, 128, 128), 50);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawLine(startX[Left], startY[Left], endX[Left], endY[Left], GetColor(0, 128, 128), 35);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawLine(startX[Left], startY[Left], endX[Left], endY[Left], GetColor(255, 255, 255), 10);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "%d", startXMap[Left]);
			DrawFormatString(30, 650, GetColor(255, 255, 255), "%d", startYMap[Left]);
			DrawFormatString(50, 650, GetColor(255, 255, 255), "%d", endXMap[Left]);
			DrawFormatString(70, 650, GetColor(255, 255, 255), "%d", endYMap[Left]);
			break;


			//�������̌�
		case Up:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int x = -2; x < 3; x++) {
				for (int i = startYMap[Up]; i >= endYMap[Up]; i--) {
					if (map[i][startXMap[Up] - x] == 1) {
						DrawGraph((startXMap[Up] - x) * 32, i * 32, block, true);
					}
				}
			}

			//���F
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawLine(startX[Up], startY[Up], endX[Up], endY[Up], GetColor(0, 128, 128), 50);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawLine(startX[Up], startY[Up], endX[Up], endY[Up], GetColor(0, 128, 128), 35);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawLine(startX[Up], startY[Up], endX[Up], endY[Up], GetColor(255, 255, 255), 10);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "%d", startXMap[Up]);
			DrawFormatString(30, 650, GetColor(255, 255, 255), "%d", startYMap[Up]);
			DrawFormatString(50, 650, GetColor(255, 255, 255), "%d", endXMap[Up]);
			DrawFormatString(70, 650, GetColor(255, 255, 255), "%d", endYMap[Up]);
			break;

		case Right:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int y = -2; y < 3; y++) {
				for (int i = startXMap[Right]; i < endXMap[Right]; i++) {
					if (map[startYMap[Right] - y][i] == 1) {
						DrawGraph(i * 32, (startYMap[Right] - y) * 32, block, true);
					}
				}
			}

			//���F
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawLine(startX[Right], startY[Right], endX[Right], endY[Right], GetColor(0, 128, 128), 50);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawLine(startX[Right], startY[Right], endX[Right], endY[Right], GetColor(0, 128, 128), 35);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawLine(startX[Right], startY[Right], endX[Right], endY[Right], GetColor(255, 255, 255), 10);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "%d", startXMap[Right]);
			DrawFormatString(30, 650, GetColor(255, 255, 255), "%d", startYMap[Right]);
			DrawFormatString(50, 650, GetColor(255, 255, 255), "%d", endXMap[Right]);
			DrawFormatString(70, 650, GetColor(255, 255, 255), "%d", endYMap[Right]);
			break;
		}
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
