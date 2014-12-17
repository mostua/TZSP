#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QMap>
#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <qcustomplot-source/qcustomplot.h>
#include <QVBoxLayout>

#define MAIN_WINDOW_HEIGHT 600
#define MAIN_WINDOW_WIDTH 800
#define MAX_SQUARE_SIZE 8


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addIterationToFitnessFunction(double iteration, double best, double average, int graph);


private slots:
    void simulationButtonPressed();

signals:
    void startSimulation(unsigned int size);

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QHBoxLayout *centralWidgetLayout;
    QWidget *optionWidget;
    QWidget *resultWidget;

    /*tab layout*/
    QTabWidget *tabLayout;

    /*central layout elements*/
    QGridLayout *optionLayout;
    QGridLayout *graphLayout;

    /*option layout elements*/
    QGroupBox *squareTypeBox;
    QGroupBox *algorithmStrategyBox;
    QGroupBox *selectionTypeBox;
    QGroupBox *reproductionTypeBox;
    QGroupBox *mutationTypeBox;

    QRadioButton* squareTypeButtons[2];
    QRadioButton* algorithmStrategyButtons[2];
    QRadioButton* selectionTypeButtons[3];
    QRadioButton* reproductionTypeButtons[3];
    QRadioButton* mutationTypeButtons[2];

    QLabel *squareSizeText;
    QSpinBox *squareSizeBox;
    QList<QVBoxLayout *> *boxLayouts;
    QList<QRadioButton *> *buttonList;
    QGroupBox *simulationTypeGroup;
    QGridLayout *simulationTypeLayout;
    QList<QRadioButton *> *simulationTypeButtonList;
    QList<QSpinBox *> *simulationTypeBoxList;
    QPushButton *beginButton;
    QTableWidget *squareResultTable;
    QTextEdit *chartSubstitue; //namiastka wykresu

    QGroupBox* simulationOptionsBox;
    QRadioButton* simulationOptionsButtons[3];
    QSpinBox* simulationOptionsSpinBoxes[2];
    QGroupBox* chartTypeBox;
    QRadioButton* chartTypeButtons[2];

    /*graph widget layout*/
    QCustomPlot *graphWidget;

    QMenu *fileMenu;

    /*actions*/
    QAction *saveResults;

    /*logically devided create functions */
    void createItemsForCentralWidget();
    void createItemsForResultWidget();
    void createItemsForOptionLayout();
    void createItemsForGraphLayout();
    void createItemsForGroupBoxes();
    void createConnections();
};

#endif // MAINWINDOW_H
