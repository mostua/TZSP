#ifndef OPTIONS_H
#define OPTIONS_H


#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QSpinBox>
#include <QList>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTextEdit>
#include "../model/model.h"

class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(QWidget *parent = 0);

signals:

public slots:

private:
    /*Widgety odpowiedzialne za layout*/
    QGridLayout *optionLayout;
    QGroupBox *squareTypeBox;
    QGroupBox *algorithmStrategyBox;
    QGroupBox *selectionTypeBox;
    QGroupBox *reproductionTypeBox;
    QGroupBox *mutationTypeBox;
    /*Grupy przycisków do wyboru parametrów symulacji */
    QRadioButton* squareTypeButtons[2];
    QRadioButton* algorithmStrategyButtons[2];
    QRadioButton* selectionTypeButtons[3];
    QRadioButton* reproductionTypeButtons[3];
    QRadioButton* mutationTypeButtons[2];
    /*Formularz do wyboru rozmiaru kwadratu*/
    QLabel *squareSizeText;
    QSpinBox *squareSizeBox;
    /*Formularz do wyboru parametru alpha */
    QLabel *alphaSizeText;
    QSpinBox *alphaSizeBox;
    /*Formularz do wyboru parametru mi */
    QLabel *miSizeText;
    QSpinBox *miSizeBox;
    /*Literki greckie */
    QChar mi;
    QChar alpha;
    void createWidgetItems();
    void setWidgetLayout();
};

#endif // OPTIONS_H
