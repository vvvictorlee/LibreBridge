#include "Common.hpp"
#include "WelcomeWindow.hpp"
#include "PlayWindow.hpp"
#include <QPushButton>
#include <QApplication>
#include <QResizeEvent>

WelcomeWindow::WelcomeWindow(QWidget *parent): QWidget(parent)
{	
	// Background
	setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
	QPixmap tmpBackground("./images/LibreBridge.png");
	background = tmpBackground.scaled(MIN_WIDTH, MIN_HEIGHT, Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, background);
	this->setPalette(palette);

	// quitButton
	quitButton = new QPushButton("Quit", this);
	quitButton->setGeometry(10, 110, 100, 30);
	/*quitButton->setFixedSize(100, 30);
	quitButton->setToolTip("Panus");
	QFont font("Courier");
	quitButton->setFont(font);
	QIcon icon("./images/LibreBridge.ico");
	quitButton->setIcon(icon);*/
	connect(quitButton, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));

	// playButton
	playButton = new QPushButton("Play", this);
	playButton->setGeometry(10, 50, 100, 30);
	playButton->setFocus();
	playButton->setDefault(true);
	connect(playButton, SIGNAL (clicked()), this, SLOT (startLocalGame()));
	
	setTitle(this);
	show();
	centerWindow(this);
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
	playWindow = new PlayWindow();
	copyWindowGeometry(this, playWindow);
	this->close();
}