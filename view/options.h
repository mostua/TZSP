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
#include <QSlider>
#include <QCheckBox>
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

private slots:
    void setMinPropabilityValue(int);
    void setMaxPropabilityValue(int);
    void setMinimumCut(int);
private:
    /*Widgety odpowiedzialne za layout*/
    QGridLayout *optionLayout;
    QGroupBox *squareTypeBox;
    QGroupBox *algorithmStrategyBox;
    QGroupBox *selectionTypeBox;
    QGroupBox *reproductionTypeBox;
    QGroupBox *mutationTypeBox;
    QGroupBox *optimalizationBox;
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
    /*Formularz przedziału prawdopodbienstwa */
    QLabel *minPropabilityText;
    QLabel *maxPropabilityText;
    QSlider *minPropabilitySlider;
    QSlider *maxPropabilitySlider;
    QLabel *minPropabilityValue;
    QLabel *maxPropabilityValue;
    /*Formularz maks iteracji */
    QLabel *maxIteratonText;
    QSpinBox *matIterationBox;
    /*Formularz optymalizacji */
    QCheckBox *cutPopulationCheckBox;
    QSpinBox *cutPopulationValue;
    QCheckBox *addRandomIndividualsCheckBox;
    QLabel *addRandomIndividualsHowManyText;
    QSpinBox *addRandomIndividualsHowManyValue;
    QLabel *addRandomIndividualsHowFrequentText;
    QSpinBox *addRandomIndividualsHowFrequentValue;
    /*Literki greckie */
    QChar mi;
    QChar lambda;
    void createWidgetItems();
    void createConnections();
    void setWidgetLayout();
};



#endif // OPTIONS_H
