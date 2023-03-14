#include<textdialog3.h>
#include<idpool.h>
#include<QGridLayout>
#include<QMessageBox>


DetailsDialog3::DetailsDialog3(QString input_,QString ID_,QString con,const QString &title, QWidget *parent)
    : QDialog(parent)
{

    IDLabel = new QLabel(tr("节点ID:"));
    contentLabel = new QLabel(tr("描述:"));
    InputLabel = new QLabel(tr("端口ID（REF）:"));
    contentLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    IDEdit = new QLineEdit;
    InputEdit = new QLineEdit;
    contentEdit = new QTextEdit;
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DetailsDialog3::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DetailsDialog3::reject);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(IDLabel, 0, 0);
    mainLayout->addWidget(IDEdit, 1, 0);
    mainLayout->addWidget(InputEdit,7,0);
    mainLayout->addWidget(InputLabel, 6, 0);
    mainLayout->addWidget(contentLabel, 2, 0);
    mainLayout->addWidget(contentEdit, 3,0,3,1);
    mainLayout->addWidget(buttonBox, 8, 0, 1, 1);
    setLayout(mainLayout);

    setWindowTitle(title);
    content=con;
    ID=ID_;
    input=input_;
    contentEdit->setText(content);
    IDEdit->setText(ID);
    InputEdit->setText(input);
}


QString DetailsDialog3::senderID() const
{
    return ID;
}

QString DetailsDialog3::senderContent() const
{
    return contentEdit->toPlainText();
}

QString DetailsDialog3::senderInput()const
{
    return input;
}
void DetailsDialog3::verify()
{
    QString s_i;
    s_i.append(InputEdit->text());
    if(input!=s_i){
        isInput=isNorm(s_i);
        if(!isInput){
            QMessageBox::StandardButton answer;
            answer = QMessageBox::warning(this, tr("修改后的REF不合法"),
                tr("修改后的REF格式不正确\n"
                   "应以0x为开头的16进制\n"
                   "是否放弃修改?"),
                QMessageBox::Yes | QMessageBox::No);

            if (answer == QMessageBox::Yes)
                InputEdit->setText(input);
        }
        else
            input=s_i;
    }
    QString str;
    str.append(IDEdit->text());
   // str.chop(1);
    if(str==ID){
        accept();
        return;
    }
    else{
       isID2=isNorm(str);
        if(isID2==true){
         isID=isRepeat(str);
        }
    }
    if (!isID && !contentEdit->toPlainText().isEmpty()&&isID2) {
        ID=str;
        accept();
        return;
    }
    else if(!isID2){
        QMessageBox::StandardButton answer;
        answer = QMessageBox::warning(this, tr("修改后的节点ID不合法"),
            tr("修改后的节点ID格式不正确\n"
               "应以0x为开头的16进制\n"
               "是否放弃修改?"),
            QMessageBox::Yes | QMessageBox::No);

        if (answer == QMessageBox::Yes)
            IDEdit->setText(ID);
        //else
            //reject();
    }

    else if(isID){
        QMessageBox::StandardButton answer;
        answer = QMessageBox::warning(this, tr("修改后的ID不合法"),
            tr("修改后的节点ID与已有ID重复\n"
               "是否放弃修改?"),
            QMessageBox::Yes | QMessageBox::No);

        if (answer == QMessageBox::Yes)
            IDEdit->setText(ID);
       // else
           // reject();

    }
    if(contentEdit->toPlainText().isEmpty()){
    QMessageBox::StandardButton answer;
    answer = QMessageBox::warning(this, tr("文本框没有描述部分"),
        tr("没有编辑描述部分的文本框会被自动删除\n"
           "是否添加描述?"),
        QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::No)
        reject();
   // else
        //accept();
    }
}

