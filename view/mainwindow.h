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
    void addIteration(QString value);
private slots:
    void simulationButtonPressed();

signals:
    void startSimulation(unsigned int size);

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QGridLayout *centralWidgetLayout;
    QGridLayout *optionLayout;
    QWidget *graphWidget;
    QList<QGroupBox *> *boxList;
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
    QMenu *fileMenu;
    QAction *saveResults;

    void createItemsForCentralWidget();
    void createItemsForOptionLayout();
    void createItemsForGroupBoxes();
    void createConnections();
};

#endif // MAINWINDOW_H
