#ifndef TEXTDIALOG2_H
#define TEXTDIALOG2_H


#include <QDialog>
#include<QLabel>
#include<QcheckBox>
#include<QLineEdit>
#include<QTableWidget>
#include<QTextEdit>
#include<QDialogButtonBox>
#include<QPushButton>
#include <QComboBox>
class DetailsDialog2 : public QDialog
{
    Q_OBJECT

public:
    DetailsDialog2(QString ID_,QString con,const QString &title="文本编辑框", QWidget *parent=0);

public slots:
    void verify() ;
public:
    QString senderID() const;
    QString senderContent() const;
private:
    QLabel *IDLabel;
    QLineEdit *IDEdit;
    QLabel *contentLabel;
    QTextEdit *contentEdit;
    QDialogButtonBox *buttonBox;
    QString content;
    QString ID;
    bool isID=false;
    bool isID2=true;
};
#endif // TEXTDIALOG2_H
