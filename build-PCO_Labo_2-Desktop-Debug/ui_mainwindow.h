/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QLineEdit *inputNbChars;
    QLineEdit *inputSalt;
    QLineEdit *inputHash;
    QLineEdit *inputThreads;
    QHBoxLayout *horizontalLayout_2;
    QProgressBar *progressBar;
    QPushButton *btnCrack;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(701, 106);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setWindowOpacity(1.000000000000000);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(8, 8, 8, 8);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(8);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 2);
        horizontalLayout_3->setStretch(2, 6);
        horizontalLayout_3->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_3);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 8, -1, -1);
        inputNbChars = new QLineEdit(centralwidget);
        inputNbChars->setObjectName(QString::fromUtf8("inputNbChars"));

        horizontalLayout->addWidget(inputNbChars);

        inputSalt = new QLineEdit(centralwidget);
        inputSalt->setObjectName(QString::fromUtf8("inputSalt"));

        horizontalLayout->addWidget(inputSalt);

        inputHash = new QLineEdit(centralwidget);
        inputHash->setObjectName(QString::fromUtf8("inputHash"));

        horizontalLayout->addWidget(inputHash);

        inputThreads = new QLineEdit(centralwidget);
        inputThreads->setObjectName(QString::fromUtf8("inputThreads"));

        horizontalLayout->addWidget(inputThreads);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 6);
        horizontalLayout->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(8);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 8, -1, -1);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setCursor(QCursor(Qt::ArrowCursor));
        progressBar->setAutoFillBackground(false);
        progressBar->setValue(0);
        progressBar->setInvertedAppearance(false);

        horizontalLayout_2->addWidget(progressBar);

        btnCrack = new QPushButton(centralwidget);
        btnCrack->setObjectName(QString::fromUtf8("btnCrack"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnCrack->sizePolicy().hasHeightForWidth());
        btnCrack->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(btnCrack);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "mD5 cr4cK3R 0f T3h D34th", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Pass length", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Salt", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "MD5 Hash", nullptr));
        label->setText(QApplication::translate("MainWindow", "Threads", nullptr));
        inputNbChars->setText(QApplication::translate("MainWindow", "4", nullptr));
        inputSalt->setText(QString());
        inputHash->setText(QApplication::translate("MainWindow", "65eab40bf1bcd5c82c6d9e02abea5ed3", nullptr));
        inputThreads->setText(QApplication::translate("MainWindow", "4", nullptr));
        btnCrack->setText(QApplication::translate("MainWindow", "Crack !", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
