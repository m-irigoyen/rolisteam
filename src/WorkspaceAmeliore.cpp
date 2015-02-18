/***************************************************************************
 *	Copyright (C) 2007 by Romain Campioni   			   *
 *	Copyright (C) 2009 by Renaud Guezennec                             *
 *   http://renaudguezennec.homelinux.org/accueil,3.html                   *
 *                                                                         *
 *   rolisteam is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <QtGui>

#include "WorkspaceAmeliore.h"
#include "constantesGlobales.h"

//#include <QTextStream>

#define GRAY_SCALE 191
/********************************************************************/
/* Constructeur                                                     */
/********************************************************************/	
WorkspaceAmeliore::WorkspaceAmeliore(QWidget *parent)
: QWorkspace(parent)
{
    m_init = Initialisation::getInstance();
    QString fichierImage = QDir::homePath() + "/." + m_init->getApplicationName() + "/" + m_init->getApplicationName() + ".bmp";

    if (!QFile::exists(fichierImage))
    {
        fichierImage = ":/resources/icones/fond workspace macos.bmp";
    }

    m_color.setRgb(GRAY_SCALE,GRAY_SCALE,GRAY_SCALE);
    m_background.setColor(m_color);
    setBackground(m_background);


    m_variableSizeBackground = new QPixmap(this->size());

    m_variableSizeBackground->fill(m_color);
    QPainter painter(m_variableSizeBackground);


    m_backgroundPicture = new QPixmap(fichierImage);

    painter.drawPixmap(0,0,m_backgroundPicture->width(),m_backgroundPicture->height(),*m_backgroundPicture);
    this->setBackground(QBrush(*m_variableSizeBackground));
}

/********************************************************************/
/* Redessine le fond                                                */
/********************************************************************/	
/*void WorkspaceAmeliore::paintEvent(QPaintEvent *event)
{
	// Creation du painter pour pouvoir dessiner
	QPainter painter(this);

	// On calcule l'intersection de la zone a repeindre avec la taille de l'image
	QRect zoneARecopier = event->rect().intersected(QRect(0, 0, imageFond->width(), imageFond->height()));

	// Si la zone n'est pas vide, on recopie l'image de fond dans le workspace
	if (!zoneARecopier.isEmpty())
		painter.drawImage(zoneARecopier, *imageFond, zoneARecopier);


    QWorkspace::paintEvent(event);
}*/
void WorkspaceAmeliore::resizeEvent ( QResizeEvent * event )
{
    Q_UNUSED(event);
    if((m_variableSizeBackground)&&(m_variableSizeBackground->size()==this->size()))
    {
        return;
    }

    delete m_variableSizeBackground;

    m_variableSizeBackground = new QPixmap(this->size());
    m_variableSizeBackground->fill(m_color);
    QPainter painter(m_variableSizeBackground);

    painter.drawPixmap(0,0,m_backgroundPicture->width(),m_backgroundPicture->height(),*m_backgroundPicture);
    this->setBackground(QBrush(*m_variableSizeBackground));

    QWorkspace::resizeEvent(event);
}
