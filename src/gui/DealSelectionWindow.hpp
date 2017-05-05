#ifndef PLAYWINDOW_HPP
#define PLAYWINDOW_HPP

#include <QWidget>
class QPushButton;
class QResizeEvent;
class QLineEdit;
class Game;

class DealSelectionWindow : public QWidget
{
	Q_OBJECT
	public:
		explicit DealSelectionWindow(QWidget *parent = 0);
		QLineEdit *seedTextBox;
		QPushButton *playButton;
	signals:
	public slots:
		void playThisDeal();
	protected:
		void resizeEvent(QResizeEvent *event) override;
		Game *game;
	private:
};

#endif