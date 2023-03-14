#ifndef TEXTDIALOG3_H
#define TEXTDIALOG3_H


#include <QDialog>
#include<QLabel>
#include<QcheckBox>
#include<QLineEdit>
#include<QTableWidget>
#include<QTextEdit>
#include<QDialogButtonBox>
#include<QPushButton>
#include <QComboBox>
class DetailsDialog3 : public QDialog
{
    Q_OBJECT

public:
    DetailsDialog3(QString input_,QString ID_,QString con,const QString &title="文本编辑框", QWidget *parent=0);

public slots:
    void verify() ;
public:
    QString senderID() const;
    QString senderContent() const;
    QString senderInput()const;
private:
    QLabel *InputLabel;
    QLineEdit *InputEdit;
    QLabel *IDLabel;
    QLineEdit *IDEdit;
    QLabel *contentLabel;
    QTextEdit *contentEdit;
    QDialogButtonBox *buttonBox;
    QString content;
    QString ID;
    bool isID=false;
    bool isID2=true;
    QString input;
    bool isInput=false;
};
#endif // TEXTDIALOG3_H
