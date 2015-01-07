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
#include "../model/settings.h"

class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(QWidget *parent = 0);
    Settings::squareType getSquareType();
    Settings::selectionType getSelectionType();
    Settings::algorithmType getAlgorithmType();
    Settings::mutationType getMutationType();
    Settings::reproductionType getReproductionType();
    int getLambda();
    int getMi();
    int getSquareSize();
signals:
    void squareSizeChanged(int);
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
    QLabel *lambdaSizeText;
    QSpinBox *lambdaSizeBox;
    /*Formularz do wyboru parametru mi */
    QLabel *miSizeText;
    QSpinBox *miSizeBox;
    /*Literki greckie */
    QChar mi;
    QChar lambda;
    void createWidgetItems();
    void createConnections();
    void setWidgetLayout();
};



#endif // OPTIONS_H
