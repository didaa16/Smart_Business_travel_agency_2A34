#include "mainwindow_hotel.h"
#include "ui_mainwindow_hotel.h"

mainwindow_hotel::mainwindow_hotel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow_hotel)
{
    ui->setupUi(this);
    ui->addid->setValidator(new QIntValidator (0,99999999,this));
    ui->addnum->setValidator(new QIntValidator);
    ui->id->setValidator(new QIntValidator (0,99999999,this));
    ui->num->setValidator(new QIntValidator);
    ui->affichage->setModel(Htmp.afficher());
    int ret=A.connect_arduino(); // lancer la connexion à arduino
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }
}

mainwindow_hotel::~mainwindow_hotel()
{
    delete ui;
}

void mainwindow_hotel::on_pushButton_7_clicked() //AJOUT
{
    int id = ui->addid->text().toInt();
    QString nom = ui->addnom->text();
    QString adresse = ui->addadress->text();
    double num = ui->addnum->text().toInt();
    float prix = ui->addprix->text().toFloat();
    QString classe = ui->addclasse->currentText();
    Hotel H(id,nom,adresse,num,prix,classe);
    bool test = H.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Ajout non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    ui->addid->clear();
    ui->addnom->clear();
    ui->addadress->clear();
    ui->addnum->clear();
    ui->addprix->clear();
    ui->addclasse->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(1);
    ui->affichage->setModel(Htmp.afficher()); //AFFICHAGE AUTO
}

void mainwindow_hotel::on_pushButton_13_clicked() //SUPPRIMER
{
    int id = ui->id->text().toInt();
    bool test=Htmp.supprimer(id);
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Suppression non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    ui->id->clear();
    ui->nom->clear();
    ui->adresse->clear();
    ui->num->clear();
    ui->prix->clear();
    ui->classe2->setCurrentIndex(0);
    ui->classe1->clear();
    ui->affichage->setModel(Htmp.afficher());//AFFICHAGE AUTO
}

void mainwindow_hotel::on_pushButton_12_clicked() //MODIFIER
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QString adresse = ui->adresse->text();
    double num = ui->num->text().toInt();
    float prix = ui->prix->text().toFloat();
    QString classe = ui->classe2->currentText();
    Hotel H(id,nom,adresse,num,prix,classe);
    bool test = H.modifier();
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("MAJ effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("MAJ non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    ui->id->clear();
    ui->nom->clear();
    ui->adresse->clear();
    ui->num->clear();
    ui->prix->clear();
    ui->classe2->setCurrentIndex(0);
    ui->classe1->clear();
    ui->affichage->setModel(Htmp.afficher());//AFFICHAGE AUTO
}

void mainwindow_hotel::on_affichage_clicked(const QModelIndex &index) //SELECT FROM TABLE
{
    QString val=ui->affichage->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from Hotel where id=:val or nom=:val or adresse=:val or num=:val or prix=:val or classe=:val");
    qry.bindValue(":val",val);
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->id->setText(qry.value(0).toString());
            ui->id_reco->setText(qry.value(0).toString());
            ui->nom->setText(qry.value(1).toString());
            ui->adresse->setText(qry.value(2).toString());
            ui->num->setText(qry.value(3).toString());
            ui->prix->setText(qry.value(4).toString());
            ui->classe1->setText(qry.value(5).toString());
            QString infos = (" Id : \t" + qry.value(0).toString() + "\n Nom : \t" + qry.value(1).toString() +"\n Adresse : \t"+ qry.value(2).toString() + "\n N°Tel : \t" +qry.value(3).toString() + "\n Prix : \t"+ qry.value(4).toString() + "\n Classe : \t"+ qry.value(5).toString());
            ui->PDF->setText(infos);
        }
    }
        else
        {
           QMessageBox::warning(this,"error","no information");
        }
}

void mainwindow_hotel::on_rechercher_textChanged(const QString &arg1) //RECHERCHER
{
    ui->affichage->setModel(Htmp.afficherrecherche(arg1));
}

void mainwindow_hotel::on_linecomboBox_5_currentIndexChanged(int index) //TRI
{
    QSqlQueryModel * model = new QSqlQueryModel();
    switch (index)
    {
    case 1:
        model->setQuery("Select * from Hotel ORDER BY id ASC");
        ui->affichage->setModel(model);
        break;
    case 2:
        model->setQuery("Select * from Hotel ORDER BY id DESC");
        ui->affichage->setModel(model);
        break;
    case 3:
        model->setQuery("Select * from Hotel ORDER BY nom ASC");
        ui->affichage->setModel(model);
        break;
    case 4:
        model->setQuery("Select * from Hotel ORDER BY nom DESC");
        ui->affichage->setModel(model);
        break;
    case 5:
        model->setQuery("Select * from Hotel ORDER BY classe ASC");
        ui->affichage->setModel(model);
        break;
    case 6:
        model->setQuery("Select * from Hotel ORDER BY classe DESC");
        ui->affichage->setModel(model);
        break;
    case 7:
        model->setQuery("Select * from Hotel ORDER BY prix ASC");
        ui->affichage->setModel(model);
        break;
    case 8:
        model->setQuery("Select * from Hotel ORDER BY prix DESC");
        ui->affichage->setModel(model);
        break;
    }
}

void mainwindow_hotel::on_pushButton_16_clicked() //RECOMMENDATION
{
    int somme,moy;
    somme = ((ui->aa->currentIndex()) + (ui->bb->currentIndex()) + (ui->cc->currentIndex()) + (ui->dd->currentIndex()) + (ui->ee->currentIndex()) + (ui->ff->currentIndex()) + (ui->gg->currentIndex()) + (ui->hh->currentIndex()) + (ui->ii->currentIndex()) + (ui->jj->currentIndex()) + (ui->kk->currentIndex()));
    moy = somme/11;
    Htmp.set_reco(moy);
    QString total;
    switch (moy)
    {
    case 0:
        total = "0";
        break;
    case 1:
        total = "1";
        break;
    case 2:
        total = "2";
        break;
    case 3:
        total = "3";
        break;
    case 4:
        total = "4";
        break;
    case 5:
        total = "5";
        break;
    }
    ui->total->setText(total);
    int id = ui->id_reco->text().toInt();
    QString nom = ui->nom->text();
    QString adresse = ui->adresse->text();
    int num = ui->num->text().toInt();
    float prix = ui->prix->text().toFloat();
    QString classe = ui->total->text();
    Hotel h(id,nom,adresse,num,prix,classe);

    bool test = h.modifier_classe();
    if (test)
    {
            QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Classification effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Classification non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
    ui->affichage->setModel(Htmp.afficher()); //AFFICHAGE AUTO
    ui->tabWidget->setCurrentIndex(1);
    QString test1 = h.aclasse();
    if(test1=="1")
    {
        QString alerte = ("ATTENTION! "+ nom);
        QByteArray x=alerte.toUtf8();
        qDebug() << x ;
        A.write_to_arduino(x);

    }
    else if (test1 =="5")
    {
        QString alerte = ("CONGRATS! "+ nom);
        QByteArray x=alerte.toUtf8();
        qDebug() << x ;
        A.write_to_arduino(x);
    }
}

void mainwindow_hotel::on_pushButton_pdf_2_clicked() //PDF
{
    QPrinter printer;
    printer.setPrinterName("Hotel");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec() == QDialog::Rejected) return;
    ui->PDF->print(&printer);
}

void mainwindow_hotel::on_pushButton_14_clicked() //BOUTON STATS
{
    s = new stats_hotel ();
    s->setWindowTitle("MOST CLASSES SAVED");
    s->pie();
    s->show();
}

void mainwindow_hotel::on_pushButton_9_clicked() //RETOUR D'AJOUT
{
    mainwindow_hotel::hide();
}

void mainwindow_hotel::on_pushButton_19_clicked() //RETOUR D'AFFICHAGE
{
    ui->tabWidget->setCurrentIndex(0);
}

void mainwindow_hotel::on_pushButton_17_clicked() //RETOUR DE RECOMMENDATION
{
    ui->tabWidget->setCurrentIndex(1);
}

void mainwindow_hotel::on_pushButton_18_clicked() //RETOUR DE PDF
{
    ui->tabWidget->setCurrentIndex(1);
}
