#ifndef CARDHLAYOUT_HPP
#define CARDHLAYOUT_HPP

#include <QtWidgets>
#include <QList>

class CardHLayout : public QLayout
{
	public:
		CardHLayout(QWidget *parent = Q_NULLPTR, Qt::Alignment alignment = Qt::Alignment());
		~CardHLayout();

		void addItem(QLayoutItem *item);
		int count() const;
		QSize sizeHint() const;
		QSize minimumSize() const;
		QLayoutItem *itemAt(int) const;
		QLayoutItem *takeAt(int);
		void setGeometry(const QRect &rect);
		int spacing() const;

	private:
		QList<QLayoutItem*> list;
		Qt::Alignment alignment;
};

#endif