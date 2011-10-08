/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri 14. Jan 22:04:33 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QGroupBox *mapGroupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QGroupBox *agentInfoGroupBox;
    QLabel *label;
    QLabel *nAgentLabel;
    QLabel *label_3;
    QLabel *label_4;
    QListWidget *goalListWidget;
    QListWidget *emotionListWidget;
    QLabel *label_2;
    QLabel *coordsLabel;
    QGroupBox *controlsGroupBox;
    QPushButton *playPauseButton;
    QPushButton *stopButton;
    QLabel *currentTimeLabel;
    QLabel *frameRateLabel;
    QSlider *mapSlider;
    QSpinBox *frameRateSpinBox;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(613, 413);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(613, 413));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 0, 591, 369));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        mapGroupBox = new QGroupBox(layoutWidget);
        mapGroupBox->setObjectName(QString::fromUtf8("mapGroupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mapGroupBox->sizePolicy().hasHeightForWidth());
        mapGroupBox->setSizePolicy(sizePolicy2);
        mapGroupBox->setMinimumSize(QSize(451, 281));
        verticalLayoutWidget = new QWidget(mapGroupBox);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 431, 251));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setSpacing(6);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);

        gridLayout->addWidget(mapGroupBox, 0, 0, 1, 1);

        agentInfoGroupBox = new QGroupBox(layoutWidget);
        agentInfoGroupBox->setObjectName(QString::fromUtf8("agentInfoGroupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(agentInfoGroupBox->sizePolicy().hasHeightForWidth());
        agentInfoGroupBox->setSizePolicy(sizePolicy3);
        agentInfoGroupBox->setMinimumSize(QSize(120, 281));
        label = new QLabel(agentInfoGroupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 21, 16));
        nAgentLabel = new QLabel(agentInfoGroupBox);
        nAgentLabel->setObjectName(QString::fromUtf8("nAgentLabel"));
        nAgentLabel->setGeometry(QRect(20, 20, 21, 16));
        label_3 = new QLabel(agentInfoGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 46, 13));
        label_4 = new QLabel(agentInfoGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 140, 46, 13));
        goalListWidget = new QListWidget(agentInfoGroupBox);
        goalListWidget->setObjectName(QString::fromUtf8("goalListWidget"));
        goalListWidget->setGeometry(QRect(10, 160, 101, 111));
        emotionListWidget = new QListWidget(agentInfoGroupBox);
        emotionListWidget->setObjectName(QString::fromUtf8("emotionListWidget"));
        emotionListWidget->setGeometry(QRect(10, 60, 101, 71));
        label_2 = new QLabel(agentInfoGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 20, 41, 16));
        coordsLabel = new QLabel(agentInfoGroupBox);
        coordsLabel->setObjectName(QString::fromUtf8("coordsLabel"));
        coordsLabel->setGeometry(QRect(80, 20, 41, 16));

        gridLayout->addWidget(agentInfoGroupBox, 0, 1, 1, 1);

        controlsGroupBox = new QGroupBox(layoutWidget);
        controlsGroupBox->setObjectName(QString::fromUtf8("controlsGroupBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(controlsGroupBox->sizePolicy().hasHeightForWidth());
        controlsGroupBox->setSizePolicy(sizePolicy4);
        controlsGroupBox->setMinimumSize(QSize(581, 75));
        playPauseButton = new QPushButton(controlsGroupBox);
        playPauseButton->setObjectName(QString::fromUtf8("playPauseButton"));
        playPauseButton->setGeometry(QRect(250, 10, 30, 30));
        stopButton = new QPushButton(controlsGroupBox);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setGeometry(QRect(300, 10, 30, 30));
        currentTimeLabel = new QLabel(controlsGroupBox);
        currentTimeLabel->setObjectName(QString::fromUtf8("currentTimeLabel"));
        currentTimeLabel->setGeometry(QRect(520, 15, 51, 20));
        currentTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        frameRateLabel = new QLabel(controlsGroupBox);
        frameRateLabel->setObjectName(QString::fromUtf8("frameRateLabel"));
        frameRateLabel->setGeometry(QRect(443, 15, 51, 20));
        frameRateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        mapSlider = new QSlider(controlsGroupBox);
        mapSlider->setObjectName(QString::fromUtf8("mapSlider"));
        mapSlider->setGeometry(QRect(9, 44, 561, 20));
        mapSlider->setMaximum(1000);
        mapSlider->setOrientation(Qt::Horizontal);
        frameRateSpinBox = new QSpinBox(controlsGroupBox);
        frameRateSpinBox->setObjectName(QString::fromUtf8("frameRateSpinBox"));
        frameRateSpinBox->setGeometry(QRect(400, 15, 42, 22));
        frameRateSpinBox->setMaximum(400);

        gridLayout->addWidget(controlsGroupBox, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 613, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Emotion Mapper", 0, QApplication::UnicodeUTF8));
        mapGroupBox->setTitle(QApplication::translate("MainWindow", "Map", 0, QApplication::UnicodeUTF8));
        agentInfoGroupBox->setTitle(QApplication::translate("MainWindow", "Agent info", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "N:", 0, QApplication::UnicodeUTF8));
        nAgentLabel->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Emotions", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Goals", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Coords:", 0, QApplication::UnicodeUTF8));
        coordsLabel->setText(QString());
        controlsGroupBox->setTitle(QApplication::translate("MainWindow", "Controls", 0, QApplication::UnicodeUTF8));
        playPauseButton->setText(QString());
        stopButton->setText(QString());
        currentTimeLabel->setText(QApplication::translate("MainWindow", "0 sec", 0, QApplication::UnicodeUTF8));
        frameRateLabel->setText(QApplication::translate("MainWindow", "frame/sec", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
