#ifndef PLAYWINDOW_HPP
#define PLAYWINDOW_HPP

#include <vector>
#include <QMainWindow>
#include <QGridLayout>
class QMenuBar;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class CardWidget;
class DealSelectionWindow;
class Game;
class CardWidget;

class PlayWindow : public QMainWindow
{
	Q_OBJECT
	public:
		explicit PlayWindow(QWidget *parent = Q_NULLPTR);
		~PlayWindow();
		void closeEvent(QCloseEvent *event);
		void createAllHandWidgets();
		void destroyAllHandWidgets();
		Game* getGame() const;
	signals:
	public slots:
	protected:
		void resizeEvent(QResizeEvent *event) override;
	private:
		DealSelectionWindow *dealSelectionWindow;
		QMenuBar *menuBar;
		QMenu *fileMenu;
		QWidget *centralWidget;
		Game *game;
		QGridLayout gridLayout;
		QVBoxLayout EWVLayout[2];	// Not pointers so we don't have to deal with the memory (PlayWindow is open iif these are needed)
		QHBoxLayout NSHLayout[2];
		QHBoxLayout *playersHLayout[4][4];	// Players, suits-1 (since clubs start at 1)
		std::vector<CardWidget*> handsWidgets[4];
};

#endif