#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
// ������֐��F��ʂ̍D���Ȉʒu�ɕ�����������悤�ɂȂ�
void karasuxy(int x,int y) {
    HANDLE hCOut;
    COORD Coord;
    hCOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Coord.X = (SHORT)x;
    Coord.Y = (SHORT)y;
    SetConsoleCursorPosition(hCOut, Coord);
}
int main() {
    int ws = 0; //while stop�̗�
    int data1 = 4;
    int uma1 = 0;  //�n�P��X���W���O�ɐݒ�i��ԍ��[����X�^�[�g�j
    int uma2 = 0;  //�n�Q��X���W���O�ɐݒ�i��ԍ��[����X�^�[�g�j
    int uma3 = 0;  //�n�R��X���W���O�ɐݒ�i��ԍ��[����X�^�[�g�j
    int b; //�����_���I��p
    int atari;
    char key;
    srand(time(NULL));
    printf("�_�[�r�[\n");
    printf("�����\�z����\n\n");
    printf("�y�E�w�L�[�F�㉺�̑I��\t�X�y�[�X�F���[�X�X�^�[�g");
    karasuxy(1,4); printf("�E�n�P");
    karasuxy(1,5); printf("�E�n�Q");
    karasuxy(1,6); printf("�E�n�R");
    while(ws==0) {
        karasuxy(8,data1); printf("��");
        if(kbhit()) {
            key = getch();
        } else key = 0; 
        if(key == 'x')  {
            karasuxy(8,data1); printf("  ");
            data1++;
            if(data1 == 7) {
                karasuxy(8,data1); printf("  ");
                data1 = 4;
                karasuxy(8,data1); printf("��");
            }
        }
        if(key == 'z') {
            karasuxy(8,data1); printf("  ");
            data1--;
            if(data1 == 3) {
                karasuxy(8,data1); printf("  ");
                data1 = 6;
                karasuxy(8,data1); printf("��");
            }
        }
        if(key == ' ') {
            ws = 1;   //���[�X�X�^�[�g
        }
    }
    ws = 0;
    Sleep(2500);   //���[�X���n�߂�O��2.5�b�قǒ�~
    while(ws == 0) {
        //���n�𓮂����O�ɂ��ׂĂ̔n���ɏ����Ă���
        //�n�P������
        karasuxy(uma1,9);printf(" ");    //(uma1,2)�̒n�_�̉摜�������i�X�y�[�X�œh��ւ���j
        //�n�Q������
        karasuxy(uma2,10);printf(" ");    //(uma2,3)�̒n�_�̉摜�������i�X�y�[�X�œh��ւ���j
        //�n�R������
        karasuxy(uma3,11);printf(" ");    //(uma2,3)�̒n�_�̉摜�������i�X�y�[�X�œh��ւ���j
        //�ǂ̔n�𓮂������������_���Ō��߂�
        b = rand()%10;
        switch(b) {
        case 0: uma1++; break;    //�n�P�𓮂���
        case 1: uma2++; break;    //�n�Q�𓮂���
        case 2: uma3++; break;    //�n�R�𓮂���
        }
        //�S�[���̐�������
        karasuxy(50,9);printf("|");  //(50,2)�̒n�_�ɃS�[���̐���`��
        karasuxy(50,10);printf("|");  //(50,3)�̒n�_�ɃS�[���̐���`��
        karasuxy(50,11);printf("|");  //(50,4)�̒n�_�ɃS�[���̐���`��
        //�n�P��`��
        karasuxy(uma1,9);printf("��");  //(uma1,2)�̒n�_�ɔn��`��
        karasuxy(uma2,10);printf("��");  //(uma2,3)�̒n�_�ɔn��`��
        karasuxy(uma3,11);printf("��");  //(uma3,4)�̒n�_�ɔn��`��
        //�Q�[������������̂Ől�H�I�Ƀt���[�Y�𔭐�������
        Sleep(20);
        if(uma1==50) ws=1;
        else if(uma2==50) ws=2;
        else if(uma3==50) ws=3;
    }
    //�����[�X���I�����while���I��������ƂɃ`�F�b�N����
    //atari���O�F�\�z�n�Y���A�P�F�\�z�A�^��
    atari = 0;  //�܂��̓n�Y���ɂ��Ă���
    if(ws==1 && data1==4) atari=1;    //�A�^���ɕύX
    if(ws==2 && data1==5) atari=1;    //�A�^���ɕύX
    if(ws==3 && data1==6) atari=1;    //�A�^���ɕύX
    //�ǂꂩ�P�ł�"�A�^��"���q�b�g������h�A�^���h�ƕ\��
    if(atari==0) MessageBox(NULL,"�n�Y��","����",MB_OK);
    if(atari==1) MessageBox(NULL,"�A�^��","����",MB_OK);
    
    getch();
    return 0;
}
