#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QApplication>
#include <QResizeEvent>
#include <QGridLayout>
#include <QLabel>
#include <vector>
#include <iostream>
#include "CardWidget.hpp"
#include "Common.hpp"
#include "PlayWindow.hpp"
#include "DealSelectionWindow.hpp"
#include "BidWindow.hpp"
#include "CardLayout.hpp"
#include "../Card.hpp"
#include "../Game.hpp"
#include "../Misc.hpp"

using namespace std;

PlayWindow::PlayWindow(QWidget *parent): QMainWindow(parent)
{
	randomizeSeed();
	game = new Game();
	game->findNextDeal();
	
	// This window
	centralWidget = new QWidget(this);
	setTitle(this);
	setObjectName("playWindow"); // Otherwise all its children inherit the background color
	setStyleSheet("#playWindow {background-color: green;}");
	setCentralWidget(centralWidget);
	cardsAreClickable = false;
	
	// Menu
	/*menuBar = new QMenuBar(centralWidget);
	QMenu *fileMenu = new QMenu("File");
	fileMenu->addMenu(new QMenu("menu1_SubMenu"));
	menuBar->addMenu(fileMenu);*/
	
	createAllHandWidgets();
	
	dealInfoLabel = new QLabel("test", this);
	gridLayout.addWidget(dealInfoLabel, 0, 2);
	gridLayout.setAlignment(dealInfoLabel, Qt::AlignRight);
	updateDealInfoLabel();
	
	/*QPushButton* test = new QPushButton("test");
	test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	gridLayout.addWidget(test, 1, 1);*/
		
	gridLayout.setColumnStretch(1, 1);
	gridLayout.setRowStretch(1, 1);
	centralWidget->setLayout(&gridLayout);
	show();
	
	dealSelectionWindow = new DealSelectionWindow(this);
	dealSelectionWindow->show();
}

PlayWindow::~PlayWindow()
{
	destroyAllHandWidgets();
}

void PlayWindow::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
}

void PlayWindow::closeEvent(QCloseEvent *event)
{
	QWidget::closeEvent(event);
}

void PlayWindow::createAllHandWidgets()
{
	for(int i=0; i<4; i++) createHandWidgets((Position)i);
}

void PlayWindow::createHandWidgets(Position p)
{
	Player *player = game->getPlayers()[p];
	cardLayouts[p] = new CardLayout(player, &handsWidgets[p]);
	for (auto &card : player->getHand())
	{
		CardWidget* cardWidget = new CardWidget(card, this);
		cardLayouts[p]->addWidget(cardWidget);
		handsWidgets[p].push_back(cardWidget);
	}
	if(p == North)	gridLayout.addLayout(cardLayouts[p], 0, 1);
	if(p == East)	gridLayout.addLayout(cardLayouts[p], 1, 2);
	if(p == South)	gridLayout.addLayout(cardLayouts[p], 2, 1);
	if(p == West)	gridLayout.addLayout(cardLayouts[p], 1, 0);
}

void PlayWindow::destroyAllHandWidgets()
{
	for(int i=0; i<4; i++) destroyHandWidgets((Position)i);
}

void PlayWindow::destroyHandWidgets(Position p)
{
	for (auto &cardWidget : handsWidgets[p])
	{
		delete cardWidget;
	}
	handsWidgets[p].clear();
	if(cardLayouts[p])
	{
		delete cardLayouts[p];
		cardLayouts[p] = NULL;
	}
}

void PlayWindow::startBidding()
{
	bidWindow = new BidWindow(this);
	bidWindow->show();
	//delete dealSelectionWindow;
}

Game* PlayWindow::getGame() const
{
	return game;
}

bool PlayWindow::getCardsAreClickable() const
{
	return cardsAreClickable;
}

void PlayWindow::updateDealInfoLabel()
{
	QString dealNumber = QString("Deal: ") + QString::number(getSeed());
	QString dealer = QString("Dealer: ") + QString::fromStdString(positionToString(game->getDealer()));
	QString vulnerability = QString("Vulnerable: ") + QString::fromStdString(vulnerabilityToString(game->getVulnerability()));
	dealInfoLabel->setText(dealNumber + "\n" + dealer + "\n" + vulnerability);
}