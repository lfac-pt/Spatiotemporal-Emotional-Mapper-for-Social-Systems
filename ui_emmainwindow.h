/********************************************************************************
** Form generated from reading UI file 'emmainwindow.ui'
**
** Created: Fri 21. Jan 22:56:00 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMMAINWINDOW_H
#define UI_EMMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EMMainWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QGroupBox *mapGroupBox;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *mapLayout;
    QGroupBox *agentInfoGroupBox;
    QLabel *label;
    QLabel *nAgentLabel;
    QLabel *label_3;
    QLabel *label_4;
    QListWidget *goalListWidget;
    QListWidget *emotionListWidget;
    QLabel *label_2;
    QTextBrowser *coordsTextBrowser;
    QListWidget *beliefsListWidget;
    QLabel *label_6;
    QPushButton *emotionsPlotPushButton;
    QPushButton *goalsPlotPushButton;
    QPushButton *beliefsPlotPushButton;
    QCheckBox *emotionsPlotCheckBox;
    QCheckBox *goalPlotCheckBox;
    QCheckBox *beliefsPlotCheckBox;
    QPushButton *emotionsPlotAllPushButton;
    QGroupBox *controlsGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QSlider *zoomHorizontalSlider;
    QPushButton *playPauseButton;
    QPushButton *stopButton;
    QSpinBox *frameRateSpinBox;
    QLabel *frameRateLabel;
    QTextBrowser *currentTimeTextBrowser;
    QSlider *mapSlider;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *exportButton;

    void setupUi(QWidget *EMMainWindow)
    {
        if (EMMainWindow->objectName().isEmpty())
            EMMainWindow->setObjectName(QString::fromUtf8("EMMainWindow"));
        EMMainWindow->resize(746, 626);
        horizontalLayout = new QHBoxLayout(EMMainWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        mapGroupBox = new QGroupBox(EMMainWindow);
        mapGroupBox->setObjectName(QString::fromUtf8("mapGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mapGroupBox->sizePolicy().hasHeightForWidth());
        mapGroupBox->setSizePolicy(sizePolicy);
        mapGroupBox->setMinimumSize(QSize(550, 500));
        horizontalLayout_3 = new QHBoxLayout(mapGroupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        mapLayout = new QVBoxLayout();
        mapLayout->setObjectName(QString::fromUtf8("mapLayout"));

        horizontalLayout_3->addLayout(mapLayout);


        gridLayout->addWidget(mapGroupBox, 0, 0, 1, 1);

        agentInfoGroupBox = new QGroupBox(EMMainWindow);
        agentInfoGroupBox->setObjectName(QString::fromUtf8("agentInfoGroupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(agentInfoGroupBox->sizePolicy().hasHeightForWidth());
        agentInfoGroupBox->setSizePolicy(sizePolicy1);
        agentInfoGroupBox->setMinimumSize(QSize(170, 500));
        label = new QLabel(agentInfoGroupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 21, 16));
        nAgentLabel = new QLabel(agentInfoGroupBox);
        nAgentLabel->setObjectName(QString::fromUtf8("nAgentLabel"));
        nAgentLabel->setGeometry(QRect(24, 20, 111, 16));
        label_3 = new QLabel(agentInfoGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(9, 90, 46, 13));
        label_4 = new QLabel(agentInfoGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 200, 46, 13));
        goalListWidget = new QListWidget(agentInfoGroupBox);
        goalListWidget->setObjectName(QString::fromUtf8("goalListWidget"));
        goalListWidget->setGeometry(QRect(10, 220, 151, 111));
        emotionListWidget = new QListWidget(agentInfoGroupBox);
        emotionListWidget->setObjectName(QString::fromUtf8("emotionListWidget"));
        emotionListWidget->setGeometry(QRect(10, 110, 151, 71));
        label_2 = new QLabel(agentInfoGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 41, 16));
        coordsTextBrowser = new QTextBrowser(agentInfoGroupBox);
        coordsTextBrowser->setObjectName(QString::fromUtf8("coordsTextBrowser"));
        coordsTextBrowser->setGeometry(QRect(50, 40, 111, 31));
        beliefsListWidget = new QListWidget(agentInfoGroupBox);
        beliefsListWidget->setObjectName(QString::fromUtf8("beliefsListWidget"));
        beliefsListWidget->setGeometry(QRect(10, 366, 151, 111));
        label_6 = new QLabel(agentInfoGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 345, 46, 13));
        emotionsPlotPushButton = new QPushButton(agentInfoGroupBox);
        emotionsPlotPushButton->setObjectName(QString::fromUtf8("emotionsPlotPushButton"));
        emotionsPlotPushButton->setGeometry(QRect(81, 83, 40, 23));
        goalsPlotPushButton = new QPushButton(agentInfoGroupBox);
        goalsPlotPushButton->setObjectName(QString::fromUtf8("goalsPlotPushButton"));
        goalsPlotPushButton->setGeometry(QRect(81, 193, 40, 23));
        beliefsPlotPushButton = new QPushButton(agentInfoGroupBox);
        beliefsPlotPushButton->setObjectName(QString::fromUtf8("beliefsPlotPushButton"));
        beliefsPlotPushButton->setGeometry(QRect(81, 340, 40, 23));
        emotionsPlotCheckBox = new QCheckBox(agentInfoGroupBox);
        emotionsPlotCheckBox->setObjectName(QString::fromUtf8("emotionsPlotCheckBox"));
        emotionsPlotCheckBox->setGeometry(QRect(123, 86, 70, 17));
        goalPlotCheckBox = new QCheckBox(agentInfoGroupBox);
        goalPlotCheckBox->setObjectName(QString::fromUtf8("goalPlotCheckBox"));
        goalPlotCheckBox->setGeometry(QRect(123, 196, 70, 17));
        beliefsPlotCheckBox = new QCheckBox(agentInfoGroupBox);
        beliefsPlotCheckBox->setObjectName(QString::fromUtf8("beliefsPlotCheckBox"));
        beliefsPlotCheckBox->setGeometry(QRect(123, 343, 70, 17));
        emotionsPlotAllPushButton = new QPushButton(agentInfoGroupBox);
        emotionsPlotAllPushButton->setObjectName(QString::fromUtf8("emotionsPlotAllPushButton"));
        emotionsPlotAllPushButton->setGeometry(QRect(53, 83, 29, 23));

        gridLayout->addWidget(agentInfoGroupBox, 0, 1, 1, 1);

        controlsGroupBox = new QGroupBox(EMMainWindow);
        controlsGroupBox->setObjectName(QString::fromUtf8("controlsGroupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(controlsGroupBox->sizePolicy().hasHeightForWidth());
        controlsGroupBox->setSizePolicy(sizePolicy2);
        controlsGroupBox->setMinimumSize(QSize(581, 100));
        controlsGroupBox->setMaximumSize(QSize(16777215, 100));
        gridLayout_2 = new QGridLayout(controlsGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(controlsGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        zoomHorizontalSlider = new QSlider(controlsGroupBox);
        zoomHorizontalSlider->setObjectName(QString::fromUtf8("zoomHorizontalSlider"));
        zoomHorizontalSlider->setMaximumSize(QSize(100, 16777215));
        zoomHorizontalSlider->setMaximum(20);
        zoomHorizontalSlider->setValue(10);
        zoomHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(zoomHorizontalSlider, 0, 1, 1, 1);

        playPauseButton = new QPushButton(controlsGroupBox);
        playPauseButton->setObjectName(QString::fromUtf8("playPauseButton"));
        playPauseButton->setMinimumSize(QSize(40, 35));
        playPauseButton->setMaximumSize(QSize(40, 35));

        gridLayout_2->addWidget(playPauseButton, 0, 5, 1, 1);

        stopButton = new QPushButton(controlsGroupBox);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setMinimumSize(QSize(40, 35));
        stopButton->setMaximumSize(QSize(40, 35));

        gridLayout_2->addWidget(stopButton, 0, 6, 1, 1);

        frameRateSpinBox = new QSpinBox(controlsGroupBox);
        frameRateSpinBox->setObjectName(QString::fromUtf8("frameRateSpinBox"));
        frameRateSpinBox->setMaximum(400);

        gridLayout_2->addWidget(frameRateSpinBox, 0, 8, 1, 1);

        frameRateLabel = new QLabel(controlsGroupBox);
        frameRateLabel->setObjectName(QString::fromUtf8("frameRateLabel"));
        frameRateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(frameRateLabel, 0, 9, 1, 1);

        currentTimeTextBrowser = new QTextBrowser(controlsGroupBox);
        currentTimeTextBrowser->setObjectName(QString::fromUtf8("currentTimeTextBrowser"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(currentTimeTextBrowser->sizePolicy().hasHeightForWidth());
        currentTimeTextBrowser->setSizePolicy(sizePolicy3);
        currentTimeTextBrowser->setMinimumSize(QSize(100, 30));
        currentTimeTextBrowser->setMaximumSize(QSize(100, 30));

        gridLayout_2->addWidget(currentTimeTextBrowser, 0, 11, 1, 1);

        mapSlider = new QSlider(controlsGroupBox);
        mapSlider->setObjectName(QString::fromUtf8("mapSlider"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(mapSlider->sizePolicy().hasHeightForWidth());
        mapSlider->setSizePolicy(sizePolicy4);
        mapSlider->setMaximum(1000);
        mapSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(mapSlider, 2, 0, 1, 12);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 7, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 10, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 4, 1, 1);

        exportButton = new QPushButton(controlsGroupBox);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setMinimumSize(QSize(50, 35));
        exportButton->setMaximumSize(QSize(50, 35));

        gridLayout_2->addWidget(exportButton, 0, 2, 1, 1);


        gridLayout->addWidget(controlsGroupBox, 1, 0, 1, 2);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(EMMainWindow);

        QMetaObject::connectSlotsByName(EMMainWindow);
    } // setupUi

    void retranslateUi(QWidget *EMMainWindow)
    {
        EMMainWindow->setWindowTitle(QApplication::translate("EMMainWindow", "Emotion Mapper", 0, QApplication::UnicodeUTF8));
        mapGroupBox->setTitle(QApplication::translate("EMMainWindow", "Map", 0, QApplication::UnicodeUTF8));
        agentInfoGroupBox->setTitle(QApplication::translate("EMMainWindow", "Agent info", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EMMainWindow", "N:", 0, QApplication::UnicodeUTF8));
        nAgentLabel->setText(QString());
        label_3->setText(QApplication::translate("EMMainWindow", "Emotions", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("EMMainWindow", "Goals", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EMMainWindow", "Coords:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("EMMainWindow", "Beliefs", 0, QApplication::UnicodeUTF8));
        emotionsPlotPushButton->setText(QApplication::translate("EMMainWindow", "Plot", 0, QApplication::UnicodeUTF8));
        goalsPlotPushButton->setText(QApplication::translate("EMMainWindow", "Plot", 0, QApplication::UnicodeUTF8));
        beliefsPlotPushButton->setText(QApplication::translate("EMMainWindow", "Plot", 0, QApplication::UnicodeUTF8));
        emotionsPlotCheckBox->setText(QApplication::translate("EMMainWindow", "Add", 0, QApplication::UnicodeUTF8));
        goalPlotCheckBox->setText(QApplication::translate("EMMainWindow", "Add", 0, QApplication::UnicodeUTF8));
        beliefsPlotCheckBox->setText(QApplication::translate("EMMainWindow", "Add", 0, QApplication::UnicodeUTF8));
        emotionsPlotAllPushButton->setText(QApplication::translate("EMMainWindow", "All", 0, QApplication::UnicodeUTF8));
        controlsGroupBox->setTitle(QApplication::translate("EMMainWindow", "Controls", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("EMMainWindow", "Zoom", 0, QApplication::UnicodeUTF8));
        playPauseButton->setText(QString());
        stopButton->setText(QString());
        frameRateLabel->setText(QApplication::translate("EMMainWindow", "frame/sec", 0, QApplication::UnicodeUTF8));
        exportButton->setText(QApplication::translate("EMMainWindow", "Export", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EMMainWindow: public Ui_EMMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMMAINWINDOW_H
