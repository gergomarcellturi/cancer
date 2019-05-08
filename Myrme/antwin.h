// BHAX Myrmecologist
//
// Copyright (C) 2019
// Norbert Bátfai, batfai.norbert@inf.unideb.hu
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// https://bhaxor.blog.hu/2018/09/26/hangyaszimulaciok
// https://bhaxor.blog.hu/2018/10/10/myrmecologist
// 

#ifndef ANTWIN_H
#define ANTWIN_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QString>
#include <QCloseEvent>
#include <QColor>
#include "antthread.h"
#include "ant.h"
#include <string>
#include <iostream>

class AntWin : public QMainWindow
{
    Q_OBJECT

public:
    AntWin(int width = 100, int height = 75,
           int delay = 120, int numAnts = 100,
           int pheromone = 10, int nbhPheromon = 3,
           int evaporation = 2, int cellDef = 1,
           int min = 2, int max = 50,
           int cellAntMax = 4, QWidget *parent = 0);

    AntThread* antThread;



    void screenshot()
    {




        for ( int i=0; i<height; ++i ) {
            for ( int j=0; j<width; ++j ) {

            double rel = 255.0/max;

            szin = qRgb(255, 255-grid[i][j]*rel, 255-grid[i][j]*rel);
            for (int end = 0; end < cellWidth; end++)
            {
                for (int me = 0; me <cellHeight; me++)
                {

                    image->setPixel(end+j*cellWidth,me+i*cellHeight, szin);
                }
            }



            if ( grid[i][j] != min )
            {

                szin = qRgb(255 - grid[i][j]*rel,
                            255 - grid[i][j]*rel, 255);

               for (int end = 0; end < cellWidth; end++)
                {
                    image->setPixel(end+j*cellWidth, i*cellHeight,szin);

                    for (int me = 0; me <cellHeight; me++)
                    {

                        image->setPixel(j*cellWidth,me+i*cellHeight, szin);
                    }
                }

            }

            szin = qRgb(0,
                       0, 255);

            for (int end = 0; end < cellWidth; end++)
             {
                 image->setPixel(end+j*cellWidth, i*cellHeight,szin);

                 for (int me = 0; me <cellHeight; me++)
                 {

                     image->setPixel(j*cellWidth,me+i*cellHeight, szin);
                 }
             }


            for ( auto h: *ants) {


                szin = qRgb(0, 0, 0);
                for (int end = 1; end < cellWidth-2; end++)
                {
                    for (int me = 1; me <cellHeight-2; me++)
                    {

                        image->setPixel(end+h.x*cellWidth+1,me+h.y*cellHeight+1, szin);
                    }
                }



            }





            }
         }

    }


    void closeEvent ( QCloseEvent *event ) {

        antThread->finish();
        antThread->wait();
        event->accept();
    }

    void keyPressEvent ( QKeyEvent *event )
    {

        if ( event->key() == Qt::Key_P ) {
            antThread->pause();
        } else if ( event->key() == Qt::Key_Q
                    ||  event->key() == Qt::Key_Escape ) {
            close();
        }

        else if (event->key() == Qt::Key_S)
        {



            screenshot();

            ++ShotNum;
            QString name ="hangya"+QString::number(ShotNum)+".png";
            image->save( name);

        }



    }

    virtual ~AntWin();
    void paintEvent(QPaintEvent*);

private:

    int ***grids;
    int **grid;
    int gridIdx;
    int cellWidth;
    int cellHeight;
    int width;
    int height;
    int max;
    int min;
    Ants* ants;
    int ShotNum;
    QImage *image;
    QRgb szin;

public slots :
    void step ( const int &);

};

#endif
