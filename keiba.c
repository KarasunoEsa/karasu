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
    int a = 0;//while�̃��[�v����
    int uma1 = 0;//�n�P��X���W���O�ɐݒ�i��ԍ��[����X�^�[�g�j
    int uma2 = 0;//�n�Q��X���W���O�ɐݒ�i��ԍ��[����X�^�[�g�j
    int b;//�����_���I��p
    srand(time(NULL));
    printf("���J���X�̃_�[�r�[\n");
    while(a == 0) {
        //���n�𓮂����O�ɂ��ׂĂ̔n���ɏ����Ă���
        //�n�P������
        karasuxy(uma1,2);printf(" "); //(uma1,2)�̒n�_�̉摜�������i�X�y�[�X�œh��ւ���j
        //�n�Q������
        karasuxy(uma2,3);printf(" "); //(uma2,3)�̒n�_�̉摜�������i�X�y�[�X�œh��ւ���j
        //�ǂ̔n�𓮂������������_���Ō��߂�
        b = rand()%10;
        switch(b) {
        case 0: uma1++; break;//�n�P�𓮂���
        case 1: uma2++; break;//�n�Q�𓮂���
        }
        //�S�[���̐�������
        karasuxy(50,2);printf("|");//(40,2)�̒n�_�ɃS�[���̐���`��
        karasuxy(50,3);printf("|");//(40,2)�̒n�_�ɃS�[���̐���`��
        //�n�P��`��
        karasuxy(uma1,2);printf("��");//(uma1,2)�̒n�_�ɔn��`��
        karasuxy(uma2,3);printf("��");//(uma2,3)�̒n�_�ɔn��`��
        //�Q�[������������̂Ől�H�I�Ƀt���[�Y�𔭐�������
        Sleep(20);
        if(uma1 == 50 || uma2 == 50){
            printf("\n\n�S�[��");
            MessageBeep(MB_OK);
        }
        //�����̔n��50�𒴂����Ƃ��A�E�o���������~
        if(uma1 ==  50 || uma2 == 50) a = 1;
    }
    getch();
    return 0;
}
