#include "Common.hpp"
#include "WelcomeWindow.hpp"
#include "DealSelectionWindow.hpp"
#include <QPushButton>
#include <QApplication>
#include <QResizeEvent>

WelcomeWindow::WelcomeWindow(QWidget *parent): QWidget(parent)
{
	setTitle(this);
	
	// Background
	setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
	QPixmap tmpBackground("./images/LibreBridge.png");
	background = tmpBackground.scaled(500, 150, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, background);
	this->setPalette(palette);

	// quitButton
	quitButton = new QPushButton("Quit", this);
	quitButton->setGeometry(10, 10, 80, 30);
	quitButton->setFixedSize(150, 50);
	quitButton->setToolTip("Panus");
	QFont font("Courier");
	quitButton->setFont(font);
	QIcon icon("./images/LibreBridge.ico");
	quitButton->setIcon(icon);
	connect(quitButton, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));

	// playButton
	playButton = new QPushButton("Play", this);
	playButton->setGeometry(170, 10, 80, 30);
	playButton->setFixedSize(150, 50);
	connect(playButton, SIGNAL (clicked()), this, SLOT (startLocalGame()));
}

void WelcomeWindow::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
	
	// Resize background image
	QSize size = event->size();
	QPixmap tmpBackground("./images/LibreBridge.png");
	background = tmpBackground.scaled(size.width(), size.height(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, background);
	this->setPalette(palette);
}

void WelcomeWindow::startLocalGame()
{
	this->close();
	playWindow = new DealSelectionWindow();
	playWindow->show();
}