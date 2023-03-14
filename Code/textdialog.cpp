#include "textdialog.h"
#include<QMessageBox>
#include<QGridLayout>
#include <QCompleter>

DetailsDialog::DetailsDialog(QString sc,QString logiccon,const QString &title, QWidget *parent)
    : QDialog(parent)
{

    nameLabel = new QLabel(tr("组合逻辑:"));
    contentLabel = new QLabel(tr("描述:"));
    contentLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    nameEdit = new QLineEdit;
    contentEdit = new QTextEdit;
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DetailsDialog::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DetailsDialog::reject);

    logicEdit=new QTextEdit;
    addB =new QPushButton("增加",this) ;
    relationC=new QComboBox;
    notC=new QComboBox;
    connect(addB, &QPushButton::clicked, this, &DetailsDialog::pressbutton);

    m_Model = new QStandardItemModel(0, 1, this);
    m_completer = new QCompleter(textlogiclist, this);

    nameEdit->setCompleter(m_completer);

    connect(m_completer, SIGNAL(activated(const QString&)), this, SLOT(onEmailChoosed(const QString&)));
    connect(nameEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onTextChanged(const QString&)));

    /* QStringList rsl;
    rsl<<"None"<<"ADD"<<"OR";
    relationC->addItems(rsl);
    QMap<QString,int>rm;
    rm.insert("None",0);
    rm.insert("AND",1);
    rm.insert("OR",2);
    foreach(const QString &rsl,rm.keys(rsl))
        relationC->addItem(rsl,rm.value(rsl));

    QStringList nsl;
    nsl << tr("None") << tr("NOT") ;
    relationC->addItems(nsl);
    QMap<QString,int>nm;
    nm.insert("None",0);
    nm.insert("NOT",1);
    foreach(const QString &nsl,nm.keys(nsl))
        notC->addItem(nsl,nm.value(nsl));*/

    relationC->addItem("None");
    relationC->addItem("AND");
    relationC->addItem("OR");
    notC->addItem("None");
    notC->addItem("NOT");

    connect(relationC,SIGNAL(currentIndexChanged(int)),this,SLOT(rc_onchange(int)));
    connect(notC,SIGNAL(currentIndexChanged(int)),this,SLOT(nc_onchange(int)));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(contentLabel, 0, 0);
    mainLayout->addWidget(contentEdit, 1, 0,3,4);

    mainLayout->addWidget(nameLabel, 4, 0);
    mainLayout->addWidget(nameEdit, 5 ,2);
    mainLayout->addWidget(relationC, 5 ,0);
    mainLayout->addWidget(notC, 5 ,1);
    mainLayout->addWidget(addB, 5 ,3);
    mainLayout->addWidget(logicEdit, 6 ,0,3,4);
    mainLayout->addWidget(buttonBox, 9, 0, 1, 4);
    setLayout(mainLayout);

    setWindowTitle(title);
    con=sc;
    contentEdit->setText(con);
    logicEdit->setText(logiccon);
}

void DetailsDialog::changcon(QString sc){
    con=sc;
}
QString DetailsDialog::senderName() const
{
    return nameEdit->text();
}

QString DetailsDialog::senderContent() const
{
    return contentEdit->toPlainText();
}

QString DetailsDialog::senderLogic() const
{
    return logicEdit->toPlainText();
}

void DetailsDialog::verify()
{
    if (/*!nameEdit->text().isEmpty() && */!contentEdit->toPlainText().isEmpty()) {
        accept();
        return;
    }

    QMessageBox::StandardButton answer;
    answer = QMessageBox::warning(this, tr("Incomplete Form"),
        tr("没有编辑描述部分\n"
           "是否添加描述?"),
        QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::Yes)
        reject();
    else
        accept();
}

void DetailsDialog::pressbutton(){

    QString s=logicEdit->toPlainText();
    //int a=relationC->currentIndex();
    //int b=notC->currentIndex();
    if(a==1){
        s.append("AND ");
    }
    else if(a==2){
        s.append("OR ");
    }

    if(b==1){
        s.append("（NOT ");
    }


    s.append(nameEdit->text());
    //s.chop(1);
    if(b==1){
        s.append(")");
    }
    s.append(" ");
    logicEdit->setText(s);
    textlogiclist.append(nameEdit->text());
}


void DetailsDialog::rc_onchange(int ac){
    a=ac;
}

void DetailsDialog::nc_onchange(int bc){
    b=bc;
}

void DetailsDialog::onEmailChoosed(const QString& email)
{
    nameEdit->clear();    // 清除已存在的文本更新内容
    nameEdit->setText(email);
}

void DetailsDialog::onTextChanged(const QString& str)
{

    QStringList strlist;
    strlist << "@163.com" << "@qq.com" << "@gmail.com" << "@hotmail.com" << "@126.com";

    m_Model->removeRows(0, m_Model->rowCount());   // 先清楚已经存在的数据，不然的话每次文本变更都会插入数据，最后出现重复数据
    for (int i = 0; i < strlist.size(); ++i)
    {
        m_Model->insertRow(0);
        m_Model->setData(m_Model->index(0, 0), str + strlist.at(i));
    }
}


/*void DetailsDialog::setupItemsTable()
{
    relation << tr("T-shirt") << tr("Badge") << tr("Reference book")
          << tr("Coffee cup");

    itemsTable = new QTableWidget(relation.count(), 2);

    for (int row = 0; row < items.count(); ++row) {
        QTableWidgetItem *name = new QTableWidgetItem(items[row]);
        name->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemsTable->setItem(row, 0, name);
        QTableWidgetItem *quantity = new QTableWidgetItem("1");
        itemsTable->setItem(row, 1, quantity);
    }
}


QList<QPair<QString, int> > DetailsDialog::orderItems()
{
    QList<QPair<QString, int> > orderList;

    for (int row = 0; row < items.count(); ++row) {
        QPair<QString, int> item;
        item.first = itemsTable->item(row, 0)->text();
        int quantity = itemsTable->item(row, 1)->data(Qt::DisplayRole).toInt();
        item.second = qMax(0, quantity);
        orderList.append(item);
    }

    return orderList;
}*/
