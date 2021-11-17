#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Create_LineEdits(int count)
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->widget(1)->setGeometry(0,0,800,500);
    update();

    for(int i = 0; i < count; i++)
    {
        SourcePathDeclerationLabel<<new QLabel(ui->stackedWidget->widget(1));
        SourcePathsLineEdits<< new QLineEdit(ui->stackedWidget->widget(1));
        SourcePathDeclerationLabel.last()->setGeometry(175,(i+2)*50,75,25);
        SourcePathDeclerationLabel.last()->setText("Katman "+QString::number(i)+":");
        SourcePathDeclerationLabel.last()->setFont(QFont( "Times New Roman", 12, QFont::Bold));
        SourcePathsLineEdits.last()->setGeometry(250,(i+2)*50,350,25);
        SourcePathsLineEdits.last()->show();
        SourcePathDeclerationLabel.last()->show();
        update();
    }
    ResultsPathLineEdit=new QLineEdit(ui->stackedWidget->widget(1));
    ResultsPathLineEdit->setGeometry(250,(count+2)*50,350,25);
    QLabel  *ResultsPathDeclerationLabel=new QLabel(ui->stackedWidget->widget(1));
    ResultsPathDeclerationLabel->setGeometry(175,(count+2)*50,75,25);
    ResultsPathDeclerationLabel->setText("KAYIT YOLU");
    ResultsPathDeclerationLabel->setFont(QFont( "Times New Roman", 10, QFont::Bold));
    ResultsPathDeclerationLabel->setStyleSheet("QLabel {color : white; }");
    ResultsPathDeclerationLabel->show();
    ResultsPathLineEdit->show();

    GetAllPathsButton=new QPushButton(ui->stackedWidget->widget(1));
    GetAllPathsButton->setGeometry(375,50*(count+3),100,40);
    GetAllPathsButton->setText("Kaynak Yolları Al");
    connect(this->GetAllPathsButton,SIGNAL(released()),this,SLOT(clicked_GetAllPath()));
    GetAllPathsButton->show();
    update();

    ui->enter_btn->setEnabled(false);
    ui->layer_count_spinbox->setEnabled(false);
}
QStringList Widget::Read_Images_Name(QString Directory_Path)
{
    QDir directory(Directory_Path);
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.png",QDir::Files);
    return images;
}

int Widget::Generate_Random_Number(int begin_point, int end_point)
{
    std::uniform_int_distribution<int> distribution(begin_point,end_point-1);
    int randomnumber=distribution(*QRandomGenerator::global());
    return randomnumber;
}

bool Widget::Check_Image_Exist()
{
    return true;
}

void Widget::on_enter_btn_released()
{
    Create_LineEdits(int(ui->layer_count_spinbox->value()));
    layer_count=int(ui->layer_count_spinbox->value());
}

void Widget::clicked_GetAllPath(){
    //QStringList result =Read_Images("D:/emre_NFT/base_monkey/base");
    for(int i=0;i<SourcePathsLineEdits.length();i++){
        QStringList result =Read_Images_Name(SourcePathsLineEdits.at(i)->text());
        for(int size=0;size<result.length();size++){
            result[size]=SourcePathsLineEdits.at(i)->text()+"\\"+result[size];
        }
        SourcePaths <<result;
        qDebug()<<result;
    }
    this->GetAllPathsButton->setEnabled(false);
    for(int count=0;count<SourcePathsLineEdits.length();count++){
        SourcePathsLineEdits.at(count)->setEnabled(false);
    }
    ui->stackedWidget->setCurrentIndex(2);
    //    ReadButton=new QPushButton(ui->stackedWidget->widget(2));
    //    ReadButton->setFont(QFont( "Times New Roman", 12, QFont::Bold));
    //    ReadButton->setText("OKU");
    //    ReadButton->setGeometry(350,100,100,40);
    //    ReadButton->show();
    StartButton=new QPushButton(ui->stackedWidget->widget(2));
    StartButton->setFont(QFont( "Times New Roman", 12, QFont::Bold));
    StartButton->setText("BAŞLA");
    StartButton->setGeometry(350,200,100,40);
    StartButton->show();
    StartButton->setEnabled(true);
    for(int val=0;val<SourcePaths.length();val++){
        max_res=max_res*SourcePaths.at(val).length();
    }
    QLabel *res_info=new QLabel(ui->stackedWidget->widget(2));
    res_info->setFont(QFont( "Times New Roman", 12, QFont::Bold));
    res_info->setText("Maximum Üretilebilecek NFT sayısı->"+QString::number(max_res));
    res_info->setGeometry(200,350,300,40);
    res_info->setAlignment(Qt::AlignCenter);
    res_info->show();

    QLabel *input_info=new QLabel(ui->stackedWidget->widget(2));
    input_info->setFont(QFont( "Times New Roman", 12, QFont::Bold));
    input_info->setText("Kaç adet NFT üretmek istiyorsunuz->");
    input_info->setGeometry(200,50,300,40);
    input_info->setAlignment(Qt::AlignCenter);
    input_info->show();

    Enter_NFT_Size= new QLineEdit(ui->stackedWidget->widget(2));
    Enter_NFT_Size->setGeometry(500,50,80,40);
    Enter_NFT_Size->show();


    update();
    connect(this->StartButton,SIGNAL(released()),this,SLOT(paste_all_layer()));
    //connect(this->ReadButton,SIGNAL(released()),this,SLOT(read_all_images()));
}

void Widget::paste_all_layer(){
    if(Enter_NFT_Size->text().toInt()<=max_res){
        if(input_info!=NULL){
            input_info->setText("Girilen NFT sayısı legal.");
        }
        for(;;){
            QString currentimagedata;
            for(int i=0;i<SourcePaths.length();i++){
                if(i==SourcePaths.length()-1){
                    currentimagedata.append(QString::number(Generate_Random_Number(0,SourcePaths.at(i).length())));
                    qDebug()<<"data:"<<currentimagedata;
                }
                else{
                    currentimagedata.append(QString::number(Generate_Random_Number(0,SourcePaths.at(i).length()))+"-");
                    qDebug()<<"data:"<<currentimagedata;
                }
            }
            if(ExistingImages.length()==Enter_NFT_Size->text().toInt()){
                break;
            }
            if(!ExistingImages.contains(currentimagedata)){
                ExistingImages.append(currentimagedata);
            }
        }
        qDebug()<<"All result"<<ExistingImages;
        qDebug()<<"size"<<ExistingImages.length();
        NFT_Results_Producer();
    }
    else{
        input_info=new QLabel(ui->stackedWidget->widget(2));
        input_info->setFont(QFont( "Times New Roman", 12, QFont::Bold));
        input_info->setText("Maksimum oluşturabileceğiniz NFT sayısı->"+QString::number(max_res)+"\nLütfen Tekrar Deneyiniz");
        input_info->setGeometry(150,400,500,80);
        input_info->setAlignment(Qt::AlignCenter);
        input_info->show();
    }
}
QPixmap Widget::Paste_Image_to_Another_Image(QString background_image_url, QString source_image_url)
{
    QPixmap background(background_image_url), source(source_image_url);
    QPixmap result(background.width(), background.height());
    result.fill(Qt::transparent);
    QPainter painter(&result);
    painter.drawPixmap(0, 0, background);
    painter.drawPixmap(0, 0, source);
    QString filename="new"+QString::number(result_counter)+".png";
    //Save_Image(filename,result);
    result_counter+=1;
    Current_Images.append(result);
    return result;
}
void Widget::Save_Image(QString image_path,QPixmap result_image)
{
    QFile file(image_path);
    file.open(QIODevice::WriteOnly);
    result_image.save(&file, "PNG");
}

void Widget::NFT_Results_Producer()
{
    for(int nft_count=0;nft_count<Enter_NFT_Size->text().toInt();nft_count++){
        QList<QPixmap> Current_Pasted_Images;
        QString Current_Filename;
        for(int current_count=0;current_count<layer_count;current_count++){
            qDebug()<<SourcePaths.at(current_count).at(ExistingImages.at(nft_count).split("-").at(current_count).toInt());
            Current_Pasted_Images<<Convert_QPixmap( SourcePaths.at(current_count).at(ExistingImages.at(nft_count).split("-").at(current_count).toInt()));
            if(current_count!=layer_count-1){
                Current_Filename.append(SourcePaths.at(current_count).at(ExistingImages.at(nft_count).split("-").at(current_count).toInt()).split("\\").last().replace(".png","")+"_");
            }else{
                Current_Filename.append(SourcePaths.at(current_count).at(ExistingImages.at(nft_count).split("-").at(current_count).toInt()).split("\\").last().replace(".png",""));
            }
        }
        QPixmap temp_image=*new QPixmap;
        for(int j=0;j<Current_Pasted_Images.length()-1;j++){
            if(j==0){
                temp_image=Paste_Image_to_Another_Image_withouturl(Current_Pasted_Images.at(j),Current_Pasted_Images.at(j+1));
            }
            else{
                temp_image=Paste_Image_to_Another_Image_withouturl(temp_image,Current_Pasted_Images.at(j+1));
            }
        }
        QString filename=ResultsPathLineEdit->text()+"\\"+"Result"+QString::number(nft_count)+"_"+Current_Filename+".png";
        Save_Image(filename,temp_image);
        Current_Pasted_Images.clear();
        Current_Filename.clear();
    }
    //write_data_json_file();
}
QPixmap Widget::Convert_QPixmap(QString Source_Path)
{
    QPixmap Result_Pixmap(Source_Path);
    return Result_Pixmap;
}

QPixmap Widget::Paste_Image_to_Another_Image_withouturl(QPixmap background_image, QPixmap source_image)
{
    QPixmap result(background_image.width(), background_image.height());
    result.fill(Qt::transparent);
    QPainter painter(&result);
    painter.drawPixmap(0, 0, background_image);
    painter.drawPixmap(0, 0, source_image);
    return result;
}

void Widget::write_data_json_file()
{
    qDebug()<<"11111";
    QStringList ResultNames= Read_Images_Name(ResultsPathLineEdit->text());
    QJsonDocument document;
    QJsonObject content;
    for(int count=0;count<ResultNames.length();count++){
        QJsonObject CurrentObject;
        for(int i=1;i<=layer_count;i++){
            CurrentObject.insert(QString(ResultNames.at(count).split("_").at(i).split("-").at(1)).replace(".png","").toUpper(),QString(ResultNames.at(count).split("_").at(i).split("-").at(0)).replace(".png",""));
        }
        content.insert(ResultNames.at(count).split("_").at(0),CurrentObject);
    }
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QFile file("Data.json");
    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream iStream( &file );
        iStream.setCodec( "utf-8" );
        iStream << bytes;
        file.close();
    }
    else
    {
        qDebug()<< "file open failed: ";
    }
}

void Widget::on_pushButton_clicked()
{
    write_data_json_file();
}

