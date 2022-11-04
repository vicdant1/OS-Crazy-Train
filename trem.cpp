#include "trem.h"
#include <QtCore>

// Semaphores
sem_t sem0,sem1, sem2, sem3, sem4, sem5, sem6;

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 200;

    sem_init(&sem0, 0, 0);
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);
    sem_init(&sem4, 0, 0);
    sem_init(&sem5, 0, 0);
    sem_init(&sem6, 0, 0);
}

void Trem::setSpeed(int value)
{
    this->velocidade = value;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        if(velocidade == 200)
            while(velocidade == 200)
                msleep(1);

        switch(ID){
        case 1:     //Trem 1
            if(y == 60)
            {
                if(x == 410)
                    sem_wait(&sem0);
                if(x < 430)
                    x += 10;
            }

            if(y < 180)
            {
                if(x == 430 && y == 160)
                    sem_wait(&sem2);

                if(x == 430)
                    y+= 10;
            }

            if(y == 180)
            {
                if(x == 260)
                    sem_post(&sem2);

                if(x > 160)
                    x -= 10;

                if(x == 400)
                    sem_post(&sem0);
            }

            if(x == 160 && y > 60)
                y-=10;

            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2

            if(y == 60)
            {
                if(x == 450)
                    sem_post(&sem0);

                if(x < 700)
                    x += 10;
            }

            if(y < 180)
            {
                if(y == 160 && x == 700)
                    sem_wait(&sem4);

                if(x == 700)
                    y += 10;
            }

            if(y == 180)
            {
                if(x == 540)
                    sem_post(&sem4);

                if(x > 430)
                    x -= 10;

                if(x == 450)
                    sem_wait(&sem0);
            }

            if(x == 430 && y > 60)
            {
                y -= 10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;

        case 3: //Trem 3
            if(y == 180)
            {
                if(x == 270)
                    sem_wait(&sem5);

                if(x < 290)
                    x += 10;
            }

            if(y < 300)
            {
                if(x == 290)
                    y += 10;
            }

            if(y == 300)
            {
                if(x == 270)
                    sem_post(&sem5);

                if(x > 20)
                    x -= 10;
            }

            if(x == 20 && y > 180)
                y -= 10;

            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4

            if(y == 180)
            {
                if(x == 450)
                    sem_post(&sem2);
                if(x == 310)
                    sem_post(&sem5);

                if(x == 550)
                    sem_wait(&sem6);

                if(x < 570)
                    x += 10;
            }

            if(y < 300)
            {
                if(x == 570)
                    y += 10;
            }

            if(y == 300)
            {
                if(x == 310)
                    sem_wait(&sem5);
                if(x == 540)
                    sem_post(&sem6);

                if(x > 290)
                    x -= 10;
            }

            if(x == 290 && y > 180)
            {
                if(y == 200)
                    sem_wait(&sem2);

                y -= 10;
            }

            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5

            if(y == 180)
            {
                if(x == 590)
                    sem_post(&sem6);

                if(x < 840)
                    x += 10;

                if(x == 730)
                    sem_post(&sem4);
            }

            if(y < 300)
            {
                if(x == 840)
                    y += 10;
            }

            if(y == 300)
            {
                if(x == 590)
                {
                    sem_wait(&sem6);
                    sem_wait(&sem4);
                }

                if(x > 570)
                    x -= 10;
            }

            if(x == 570 && y > 180)
                y -= 10;

            emit updateGUI(ID, x,y);    //Emite um sinal
            break;

        default:
            break;
        }
        msleep(velocidade);
    }

    sem_destroy(&sem0);
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem3);
    sem_destroy(&sem4);
    sem_destroy(&sem5);
    sem_destroy(&sem6);
}




