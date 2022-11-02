#include "trem.h"
#include <QtCore>

sem_t site1,site2,site3,site4,site5,site6,site7;
//Construtor
Trem::Trem(int ID, int x, int y)
{
    this->ID = ID;
    this->y = y;
    this->x = x;
    this->velocidade = 200;

    sem_init(&site1,0,0);
    sem_init(&site2,0,0);
    sem_init(&site3,0,0);
    sem_init(&site4,0,1);
    sem_init(&site5,0,0);
    sem_init(&site6,0,1);
    sem_init(&site7,0,0);
}

void Trem::setTrainVelocity(int value)
{
    this->velocidade = value;
}

void Trem::run()
{
    while(true){
        if(velocidade == 200)
            while(velocidade == 200) msleep(1);

        switch(ID)
        {
        case 1:     //Trem 1
            if (y == 20 && x < 330)
            {
                if (x == 310)
                    sem_wait(&site1);

                x+=10;
            }
            else if (x == 330 && y < 140)
            {
                if(y == 120)
                    sem_wait(&site3);

                y+=10;
            }
            else if (x > 60 && y == 140){
                if( x == 310)
                    sem_post(&site1);
                if(x == 190)
                    sem_post(&site3);

                x-=10;
            }
            else
                y-=10;

            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 20 && x < 600)
            {
                if(x == 350)
                    sem_post(&site1);

                if(x == 580)
                {
                    sem_wait(&site5);
                    sem_wait(&site2);
                }
                x+=10;
            }
            else if (x == 600 && y < 140)
                y+=10;
            else if (x > 330 && y == 140)
            {
                if(x == 600)
                    sem_post(&site2);
                if(x == 500)
                {
                    sem_wait(&site1);
                    sem_wait(&site4);
                }
                if(x == 460)
                    sem_post(&site5);

                x-=10;
            }
            else
            {
                if( y == 120 )
                    sem_post(&site4);

                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 20 && x < 870)
            {
                if(x == 600)
                    sem_post(&site2);

                x+=10;
            }
            else if (x == 870 && y < 140)
                y+=10;
            else if (x > 600 && y == 140)
            {
                if(x == 770)
                    sem_wait(&site6);

                if(x == 620)
                    sem_wait(&site2);

                x-=10;
            }
            else
            {
                if(y == 120)
                    sem_post(&site6);

                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 140 && x < 480)
            {
                if(x == 310)
                    sem_wait(&site4);

                if(x == 350)
                    sem_post(&site3);

                if(x == 460)
                    sem_wait(&site7);

                x+=10;
            }
            else if (x == 480 && y < 260)
            {
                if(y == 160)
                    sem_post(&site4);

                y+=10;
            }
            else if (x > 210 && y == 260)
            {
                if( x == 480)
                    sem_post(&site7);

                x-=10;
            }
            else
            {
                if(y == 160)
                    sem_wait(&site3);

                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 140 && x < 750)
            {
                if(x == 500)
                    sem_post(&site7);

                if(x == 580)
                    sem_wait(&site6);

                if(x == 620)
                    sem_post(&site5);

                x+=10;
            }
            else if (x == 750 && y < 260)
            {
                if(y == 240)
                    sem_post(&site6);

                y+=10;
            }
            else if (x > 480 && y == 260)
            {
                if(x == 500)
                {
                    sem_wait(&site5);
                    sem_wait(&site7);
                }

                x-=10;
            }
            else
                y-=10;

            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(this->velocidade);
    }


    sem_destroy(&site1);
    sem_destroy(&site2);
    sem_destroy(&site3);
    sem_destroy(&site4);
    sem_destroy(&site5);
    sem_destroy(&site6);
    sem_destroy(&site7);
}
